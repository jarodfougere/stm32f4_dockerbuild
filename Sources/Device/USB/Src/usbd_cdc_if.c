/**
 * @file usbd_cdc_if.c
 * @author Carl Mattatall
 * @brief  This file implements the USB CDC class interface
 * using STM32USB Low Level drivers. The interface
 * supports additional line encodings and request/responses
 * for the OTG Peripheral. It was built using the GPIO controller
 * usbd_cdc_if.c as a reference. This is NOT to be confused with
 * the name of the template file template generated using 
 * STM32MXCUBE software (which as I have unfortunately learned, 
 * shares the exact same name).
 * 
 * @version 0.3
 * @date 2020-03-19
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h> /* memcpy */

#if defined(MCU_APP)
#include "drivers.h"
#endif /* MCU_APP */
#include "usbd_cdc_if.h"


/* 
 * FIFO buffer is the OUT endpoint for the OTG device peripheral. 
 * (out endpoint for CDC interface means MCU-facing.)
 * (the IN endpoint for CDC interface would be facing the outpost)
 * 
 * bytes received at IN device endpoint end up automatically in this buffer.
 */
#define CDC_RX_FIFO_SIZE 2*CDC_DATA_FS_MAX_PACKET_SIZE /* safety factor of 2 */

/* The ring buffer will store MULTIPLE command strings */
#define CDC_IF_BUF_SIZE 2048

/* We need to replace the delimiter of corrupted data with something... */
#define CORRUPTED_DATA_DELIM_REPLACEMENT '!'

/******************************************
 * Compile-time buffer size safety checks *
 ******************************************/
#if (CDC_RX_FIFO_SIZE < CDC_DATA_FS_MAX_PACKET_SIZE) /* FIFO SIZE CHECK */
#error CDC_RX_FIFO_SIZE IS NOT LARGE TO COMPLY WITH USB FS PACKET SIZE SPECS
#endif /* FIFO SIZE CHECK */
#if (CDC_IF_BUF_SIZE < CDC_RX_FIFO_SIZE ) /* RING SIZE CHECK */
#error CDC INTERFACE RING BUFFER CANNOT FIT A SINGLE INTERFACE FIFO COPY.
#endif /* RING SIZE CHECK */

struct multibuf
{
    uint8_t buf[CDC_IF_BUF_SIZE];    /* Contiguous byte array for data  */
    uint8_t *out;                    /* Read out from here              */
    uint8_t *in;                     /* Write into here                 */
};

struct cdc_rx_endpoint
{   
    uint8_t fifo[CDC_RX_FIFO_SIZE];   /* FIFO BUFFER                          */
    struct multibuf ring;             /* Ring buffer of command strings       */
    uint8_t num_payloads;             /* Num command strings in buffer        */
    struct cdc_user_if user;          /* Exposed user interface               */
};

struct cdc_tx_endpoint
{   
    struct multibuf lin;              /* Linear buffer of payloads           */
    uint8_t num_payloads;             /* Num command strings in buffer       */
    struct cdc_user_if user;          /* Exposed user interface              */
};

struct USB_CDC_interface
{
    struct cdc_tx_endpoint tx;                  /* The transmitting endpoint */
    struct cdc_rx_endpoint rx;                  /* The receiving endpoint    */
    USBD_CDC_LineCodingTypeDef Linecoding;      /* The configured linecoding */
};

/* INTERFACE INSTANCE */
static struct USB_CDC_interface cdc = 
{
    .tx = 
    {   
        .lin = 
        {
            .buf = {0},
            .out = NULL,
            .in =  NULL,
        },

        .user = 
        {
            .delim = '\0',
            .buf = NULL,
            .bufSize = 0,
            .callback = NULL,
            .cbParam  = NULL,
        },
    },
    
    .rx = 
    {   
        .fifo = {0},
        .ring = 
        {
            .buf = {0},
            .out = NULL,
            .in =  NULL,
        },

        .user = 
        {
            .delim = '\0',
            .buf = NULL,
            .bufSize = 0,
            .callback = NULL,
            .cbParam  = NULL,
        },
    },

    .Linecoding = 
    {
        .bitrate    = USB_CDC_DEFAULT_BAUDRATE,
        .format     = USB_CDC_DEFAULT_STOPBITS,
        .paritytype = USB_CDC_DEFAULT_PARITY,
        .datatype   = USB_CDC_DEFAULT_DATABITS,
    },
};


/**
 * @brief Perform a union overlay assignement test to determine
 *        Endianness of the microcontroller memory. Ideally
 *        this would be known at compile time but the runtime
 *        check has been implemented anyway.
 *        
 *        It's not guaranteed that all compilation toolchains
 *        have information on the target architecture's
 *        endianness so for safety and portability the endian
 *        check is performed at runtime.
 * 
 * @return int8_t : 0 if little endian, !0 if big endian.
 */
static int8_t CDC_isDeviceLittleEndian(void);


/**
 * @brief Peek the next address for a ring buffer's IN pointer.
 * @param Buf The ring buffer to iterate
 * @return int8_t* The address of the next position for the IN ptr.
 */
static uint8_t* nextRingInPtr(const struct multibuf *Buf);


/**
 * @brief Peek the next address for a ring buffer's OUTS pointer
 * @param Buf The ring buffer to iterate
 * @return int8_t* The address of the next position for the OUT ptr.
 */
static uint8_t* nextRingOutPtr(const struct multibuf *Buf);


/**
 * @brief Get the End Ptr of a multibuf's array memory
 * 
 * @param Buf the multibuf in question
 * @return int8_t address of the end pointer of the buf's memory.
 */
static uint8_t* getEndPtr(const struct multibuf *Buf);


static uint8_t* getEndPtr(const struct multibuf *Buf)
{   
#if !defined(NDEBUG)
    if(NULL == Buf)
    {
        while(1)
        {
            /* 
             * Hang forever. 
             * Release doesnt check Buf existence because this is a private
             * worker function. Assume programmer is not an idiot.
             */
        }
    }
#endif /* DEBUG BUILD */

    /* 
     * Ideally I'd like the compiler to inline the
     * entire function during optimization. Can't portably
     * indicate this though. gnu-eabi-armcc lets me, but iccarm/iccasm doesnt.
     */
    return (uint8_t*)(Buf->buf + sizeof(Buf->buf));
}


static uint8_t* nextRingOutPtr(const struct multibuf *Buf)
{   
    uint8_t *nextPtr;
#if !defined(NDEBUG)
    if(NULL == Buf)
    {
        while(1)
        {
            /* 
             * Hang forever. 
             * Release doesnt check Buf existence because this is a private
             * worker function. Assume programmer is not an idiot.
             */
        }
    }
#endif /* DEBUG BUILD */

    /* Check wrap condition and return next pointer */
    if((Buf->out + 1) == getEndPtr(Buf))
    {
        nextPtr = (uint8_t*)Buf->buf;
    }
    else
    {
        nextPtr = (uint8_t*)Buf->out + 1;
    }
    return nextPtr;
}


static uint8_t* nextRingInPtr(const struct multibuf *Buf)
{   
    uint8_t* nextPtr;
#if !defined(NDEBUG)
    if(NULL == Buf)
    {
        while(1)
        {
            /* 
             * Hang forever. 
             * Release doesnt check Buf existence because this is a private
             * worker function. Assume programmer is not an idiot.
             */
        }
    }
#endif /* DEBUG BUILD */

    /* Check wrap condition and return next pointer. */
    if((Buf->in + 1) == getEndPtr(Buf))
    {
        nextPtr = (uint8_t*)Buf->buf;
    }
    else
    {
        nextPtr = (uint8_t*)Buf->in + 1;
    }
    return nextPtr;
}


/******************************/
/* LOW-LEVEL FACING FUNCTIONS */
/******************************/
static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);

/* 
 * These 4 Funcs are called automatically as part of the exception call stack 
 * generated by HAL_PCD_IRQ_HANDLER for the OTG Peripheral. 
 * 
 * In practice, if you compile with high optimization, these are just called 
 * directly via branch prediction using the interrupt register bits from the
 *  OTG_periph::CR and OTG_periph::SR. 
 * 
 * By the time the USB peripheral enumerates, the interrupt call stack has 
 * already occurred enough to fully saturate the branch prediction circuit in 
 * hardware (we dont have to worry about the callstack bloat caused by PCD 
 * module or HAL APIs).
 */
USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
    CDC_Init_FS,
    CDC_DeInit_FS,
    CDC_Control_FS,
    CDC_Receive_FS
};

/* ALIASED OVERLAY ON THE USG OTG PERIPHERAL ADDRESSES */
extern USBD_HandleTypeDef hUsbDeviceFS;


/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{   
    
#if defined(MCU_APP)
    /* init endpoint FIFOs */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, cdc.tx.lin.buf, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, cdc.rx.fifo);

    /* init ring buffers */
    cdc.rx.ring.in  = cdc.rx.ring.buf;
    cdc.rx.ring.out = cdc.rx.ring.buf;
    cdc.tx.lin.in  = cdc.tx.lin.buf;
    cdc.tx.lin.out = cdc.tx.lin.buf;
#else
#endif /* MCU_APP */

    /* 
     * User must inject their application buffers before 
     * initializing the CDC endpoints.
     */
    if((cdc.tx.user.buf == NULL) || (cdc.rx.user.buf == NULL))
    {
        return USBD_FAIL;
    }
    else
    {
        return USBD_OK;
    }
}


/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
#if defined(MCU_APP)
#else
#endif /* MCU_APP */
    return (USBD_OK);
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd:  Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else
  *  USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{   
    switch (cmd)
    {
    case CDC_SEND_ENCAPSULATED_COMMAND:

        break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

        break;

    case CDC_SET_COMM_FEATURE:

        break;

    case CDC_GET_COMM_FEATURE:

        break;

    case CDC_CLEAR_COMM_FEATURE:

        break;
    case CDC_SET_LINE_CODING:
    /***************************************************************************
     * @brief The table below describes the necessary structure and
     * bit fields to enumerate the USB peripheral as a CDC class dev 
     * (class sub descriptor) once the usb OTG peripheral has enumerated
     * as a base USB device AND the CDC class request descriptor packet
     * has been sent by the host.
     * 
     * |------------------------------------------------------------------|
     * |              USB CDC line coding structure and format            |
     * |--------+-------------+--------------+---------+------------------|
     * | Offset |    Field    | Size (bytes) |  Value  |  Description     |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Data terminal    |
     * |   0    |  dwDTERate  |       4      | number  | rate in bits per |
     * |        |             |              |         | second           |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Num Stop bits    |
     * |   4    | bCharFormat |       1      | number  | 0: 1 stop bit    |
     * |        |             |              |         | 1: 1.5 stop bits |
     * |        |             |              |         | 2: 2 stop bits   |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Parity:          |
     * |        |             |              |         | 0: None          |
     * |   5    | bParityType |      1       | number  | 1: Odd           |
     * |        |             |              |         | 2: Even          |
     * |        |             |              |         | 3: Mark          |
     * |        |             |              |         | 3: Space         |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Num data bits    |
     * |   6    | bDataBits   |      1       | number  | Valid values are |
     * |        |             |              |         | 5, 6, 7, 8, 16   |
     * |--------+-------------+--------------+---------+------------------|
     **************************************************************************/
        if(0 == CDC_isDeviceLittleEndian())
        {
            cdc.Linecoding.bitrate =    (uint32_t)  (pbuf[0]          |
                                                    (pbuf[1] << 8)    |
                                                    (pbuf[2] << 16)   |
                                                    (pbuf[3] << 24));
        }
        else
        {
            cdc.Linecoding.bitrate = (uint32_t)((pbuf[0] << 24) |
                                                (pbuf[1] << 16) |
                                                (pbuf[2] << 8)  |
                                                (pbuf[3]));
        }

        /* These are single bytes and don't depend on platform endianness */
        cdc.Linecoding.format      = pbuf[4];
        cdc.Linecoding.paritytype  = pbuf[5];
        cdc.Linecoding.datatype    = pbuf[6];
        break;
    case CDC_GET_LINE_CODING:
        if(0 == CDC_isDeviceLittleEndian())
        {
            pbuf[0] = (uint8_t)(cdc.Linecoding.bitrate);
            pbuf[1] = (uint8_t)(cdc.Linecoding.bitrate >> 8);
            pbuf[2] = (uint8_t)(cdc.Linecoding.bitrate >> 16);
            pbuf[3] = (uint8_t)(cdc.Linecoding.bitrate >> 24);
        }
        else
        {
            pbuf[0] = (uint8_t)(cdc.Linecoding.bitrate >> 24);
            pbuf[1] = (uint8_t)(cdc.Linecoding.bitrate >> 16);
            pbuf[2] = (uint8_t)(cdc.Linecoding.bitrate >> 8);
            pbuf[3] = (uint8_t)(cdc.Linecoding.bitrate);
        }

        /* These are single bytes and don't depend on platform endianness */
        pbuf[4] = cdc.Linecoding.format;
        pbuf[5] = cdc.Linecoding.paritytype;
        pbuf[6] = cdc.Linecoding.datatype;
        break;
    case CDC_SET_CONTROL_LINE_STATE:
        break;
    case CDC_SEND_BREAK:

        break;
    default:
#if !defined(NDEBUG)
        while(1)
        {
            /* possible label omission by programmer. hang forever */
        }
#else
        break;
#endif /* DEBUG BUILD */
    }
    return (USBD_OK);
}


/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *         
  * @note   This function will block any OUT packet reception on USB endpoint
  *         until exiting this function. If you exit this function before
  *         transfer is complete on CDC interface (ie. using DMA controller) 
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received (caller provided). 
  *              This is the rx fifo exposed to the lowest level drivers 
  * 
  * @param  Len: Upon return, contains number of bytes that 
  *              would have been copied if the provided buffer was large
  *              enough. Caller must provide *Len on input with desired number
  *              of bytes to be copied. Lower level drivers will handle the 
  *              case wherein fifo couldn't hold the entire packet coming
  *              through the interface IN endpoint.
  * 
  * @retval Result of the operation: USBD_OK if all operations are OK, else
  *         USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{   
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, cdc.rx.fifo);
    USBD_CDC_ReceivePacket(&hUsbDeviceFS);
    uint32_t i = 0;
    int8_t overrun_flag = 0;
    int8_t status = USBD_OK;
    do
    {   
        /* copy byte and check for terminator */
        if((*cdc.rx.ring.in = Buf[i]) == cdc.rx.user.delim)
        {
            *cdc.rx.ring.in = '\0';
            cdc.rx.num_payloads++;
            cdc.rx.user.callback(cdc.rx.user.cbParam);
        }

        /* Check data overwrite conditions */
        uint8_t *nextInPtr = nextRingInPtr(&cdc.rx.ring);
        if(nextInPtr == cdc.rx.ring.out)
        {
            if(cdc.rx.num_payloads > 0)
            {
                cdc.rx.num_payloads--;
                overrun_flag = 1;
            }
            else
            {
                /* 
                 * Ideally, OUT ptr should always be catching IN ptr.
                 * 
                 * If IN ptr catches OUT ptr. Either:
                 *   a) There are payloads set (in which case we are 
                 *      overwriting an unread payload - hence the setting
                 *       of the overrun flag).
                 * 
                 *   b) There are no payloads set. IN ptr has wrapped the 
                 *      entire buffer during the receive process. At the 
                 *      start of the receive process, inptr was == outptr
                 *      and everything in front of outptr was garbage. 
                 * 
                 *      As inptr kept advancing, bytes were copied into the 
                 *      command string ring buffer.
                 * 
                 *      Finally, when inptr wrapped all the way around to catch
                 *      up to outptr, the number of undelimited bytes received
                 *      will be equal to the size of the ring buffer.
                 * 
                 *      Thus, inptr is JUST about to overwrite the start
                 *      of its own payload.
                 * 
                 *      The only fix for this scenario is to increase the 
                 *      size of the ring buffer. To prevent the overwrite,
                 *      we exit the receive callback early.
                 */

                /* Set value of Len so exception frame caller knows not 
                all the bytes from rx FIFO made it into the ring buffer */

                *cdc.rx.ring.in = '\0'; /* nul-terminate */
                cdc.rx.ring.in = nextInPtr;

                /* NOTE THAT WE DO #### NOT #### SET STATUS TO FAILURE */
                break;
            }
        }   

        /* Advance the input pointer */
        cdc.rx.ring.in = nextInPtr; 
    }   while(++i < *Len);

    /* Ring buffer not big enough for full FIFO packet */
    if(i != *Len)
    {
        status = USBD_FAIL;
    }

    /* Check for and handle data overrun (need to realign outptr ptr) */
    if(overrun_flag)
    {   
        i = 0;
        do
        {   
            /* Advance OUT ptr */
            cdc.rx.ring.out = nextRingOutPtr(&cdc.rx.ring);

            /* Found end of corrupted command string */
            if(*cdc.rx.ring.out == '\0')
            {   
                /* Remove the nul character delimiting corrupted string */
                *cdc.rx.ring.out = CORRUPTED_DATA_DELIM_REPLACEMENT;

                /* Advance OUT ptr to next uncorrupted command string */
                cdc.rx.ring.out = nextRingOutPtr(&cdc.rx.ring);
                break;
            }
        }   while(++i < sizeof(cdc.rx.ring.buf));

        /* Ring buffer contains undelimited garbage. 
         * Best we can do is reset the buffer pointers.
         */
        if(i == sizeof(cdc.rx.ring.buf))
        {   
            cdc.rx.ring.out = cdc.rx.ring.buf;
            cdc.rx.ring.in  = cdc.rx.ring.buf;
            status = USBD_FAIL;
        }
    }
    return status;
}


uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len)
{
    uint8_t result = USBD_OK;
    if ((0 == Len) || (NULL == Buf)) /* Idiotproofing */
    {
        result = USBD_FAIL;
    }
    else
    {
#if defined(MCU_APP)
        result = USBD_OK;

        USBD_CDC_HandleTypeDef *hcdc =
            (USBD_CDC_HandleTypeDef *)hUsbDeviceFS.pClassData;

        /* if peripheral is busy transmitting */
        if (hcdc->TxState != 0)
        {
            /* simply return. caller can decide if they want to block or not */
            return USBD_BUSY;
        }

        /* transfer payload into tx buffer and transmit */
        USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
        result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
#else
        result = printf("[USB CDC] : %s", Buf) > 0 ? USBD_OK : USBD_FAIL;
#endif
    }
    return result;
}


int8_t CDC_transmit_payload(void)
{   
    uint8_t status = 0;
    if(cdc.tx.num_payloads > 0) /* only transmit if payloads are queued */
    {   
        uint16_t len = strlen((const char*)cdc.tx.lin.out);
        status = CDC_Transmit_FS(cdc.tx.lin.out, len);
        if(USBD_OK == status)
        {   
            /* reduce num payloads */
            cdc.tx.num_payloads--;

            /* advance output pointer to end of transmitted string */
            cdc.tx.lin.out += len;

            /* advance output point to start of next transmitable string */
            cdc.tx.lin.out++;

#if !defined(NDEBUG)
            if(cdc.tx.num_payloads == 0)
            {
                if(cdc.tx.lin.in != cdc.tx.lin.out)
                {
                    while(1)
                    {
                        /* hang forever. A pointer alignment error occurred. */
                        /* programmer to find and fix bug */
                    }
                }
            }
#endif /* DEBUG BUILD */
        }
    }
    return status;
}


int8_t CDC_set_payload(int *Len)
{   
    int8_t   status = USBD_OK;
    if(NULL == Len)
    {
        status = USBD_FAIL;
    }
    else
    {
        if(*Len > 0)
        {   
            if(cdc.tx.num_payloads == 0)
            {
                /* Reset pointers */
                cdc.tx.lin.out = cdc.tx.lin.buf;
                cdc.tx.lin.in  = cdc.tx.lin.buf;
            }

            /* If we can make some extra room at the head for the payload */
            else if(cdc.tx.lin.out != cdc.tx.lin.buf)
            {   
                /* Realign data */
                memcpy( cdc.tx.lin.buf, 
                        cdc.tx.lin.out, 
                        cdc.tx.lin.in - cdc.tx.lin.out);

                /* Realign pointers */
                cdc.tx.lin.in = (uint8_t*)( cdc.tx.lin.buf + 
                                            (cdc.tx.lin.out - cdc.tx.lin.buf));

                cdc.tx.lin.out = cdc.tx.lin.buf;
            }

            /* Now check if our desired payload can fit into the TX endpoint */
            int bytes_free = (int)(getEndPtr(&cdc.tx.lin) - cdc.tx.lin.in);
            if(bytes_free > *Len)
            {   
                /* If it can fit, load the payload */
                if(NULL == memcpy(cdc.tx.lin.in, cdc.tx.user.buf, *Len))
                {   
                    /* 
                     * We couldn't fit it all in or HW shut us down 
                     * (data seg page fault for VERY large buffers)
                    */
                    *Len = bytes_free; 
                    status = USBD_FAIL;
                }
                else
                {   
                    /* If it fit, increase payloads and advance IN ptr */
                    cdc.tx.num_payloads++;
                    cdc.tx.lin.in += *Len;
                    *cdc.tx.lin.in = '\0'; /* Nul terminate */
                }
            }
            else
            {   
                /* Nothing we can do to load the string. payload won't fit */
                status = USBD_FAIL;

                /* We can at least set len to allow caller to compare # bytes that WOULD fit with how many they WANT to fit */
                *Len = bytes_free; 
            }
        }
        else
        {   
            *Len = 0;
            status = USBD_FAIL;
        }
    }
    return status;
}



unsigned int CDC_peek_num_payloads_out(void)
{
    return cdc.tx.num_payloads;
}


void CDC_setUserRxEndPt(const struct cdc_user_if *user)
{
    cdc.rx.user.buf      = user->buf;
    cdc.rx.user.bufSize  = user->bufSize;
    cdc.rx.user.delim    = user->delim;
    cdc.rx.user.callback = user->callback;
    cdc.rx.user.cbParam  = user->cbParam;
}


void CDC_setUserTxEndPt(const struct cdc_user_if *user)
{
    cdc.tx.user.buf      = user->buf;
    cdc.tx.user.bufSize  = user->bufSize;
    cdc.tx.user.delim    = user->delim;
    cdc.tx.user.callback = user->callback;
    cdc.tx.user.cbParam  = user->cbParam;
}


int CDC_getCommandString(void)
{   
    int status = 0;
    if(cdc.rx.num_payloads > 0) /* only copy if we actually have data */
    {
        unsigned int i = 0;
        do
        {   
            /* Load next byte and test for EOS */
            if((cdc.rx.user.buf[i] = *cdc.rx.ring.out) == '\0')
            {
                cdc.rx.num_payloads--;
                cdc.rx.ring.out++; /* move outptr to start of next payload */
                break;
            }

            if(cdc.rx.ring.out == cdc.rx.ring.in)
            {   
                status = 1;
#if !defined(NDEBUG)
                while(1)
                {
                    /* This is an error.
                     * We get here only when we've lost track of the number of 
                     * payloads stored in the ring buffer.
                     * Hang here so programmer can inspect of CDC module logic.
                     */
                }
#else 
                break;
#endif /* DEBUG BUILD */
            }

            /* Advance out Pointer */
            cdc.rx.ring.out = nextRingOutPtr(&cdc.rx.ring);
        }   while(++i < cdc.rx.user.bufSize);

        /* User buffer doesn't have enough space */
        if(i >= cdc.rx.user.bufSize)
        {
            status = 1;
        }
    }
    else
    {
        status = 1;
    }
    return status;
}


static int8_t CDC_isDeviceLittleEndian(void)
{   
    union 
    {
        uint32_t integer;
        uint8_t  bytes[4];
    }   overlay;

    overlay.integer = 1;
    if(1 == overlay.bytes[0])
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

