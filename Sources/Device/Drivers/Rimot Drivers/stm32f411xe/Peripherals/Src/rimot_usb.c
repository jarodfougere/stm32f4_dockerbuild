/**
 * @file rimot_usb.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the usb otg 
 * peripheral on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated. All rights reserved.
 * 
 * This software is licensed under the Berkley Software Distribution (BSD) 
 * 3-Clause license. Redistribution and use in source and binary forms, 
 * with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE. 
 */

#if 0

#include "ATTRIBUTE_PORTABILITY_HEADER.h"

#include <stdint.h>
#include <stdlib.h>

#include "rimot_usb_register_masks.h"
#include "rimot_bus_region_offsets.h"

#include "rimot_usb.h"
#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"

#include "rimot_interrupts.h"
#include "rimot_rcc.h"

#include "cmsis_compiler.h"

#include "usbd_def.h"

/**
 * @todo HONESTLY, THIS ENTIRE MODULE IS JUST A BURNING DUMPSTER FIRE,
 * 
 * IT WORKS, BUT ITS A MESS. WASN'T GIVEN PROPER TIME
 * TO DESIGN A CLEAN SOFTWARE ARCHITECTURE
 */

#define USB_OTG_PERIPH_BASE (0x50000000UL)

#define _USB ((USB_t *)USB_OTG_PERIPH_BASE)

/** 
 * @todo There are definitely A TON more functions that should be static
 *  but I haven't had time to go through this file and refactor/cleanup
 */
static int usbFlushTxFifo(uint32_t num);
static int usbFlushRxFifo(void);
static int usbCoreReset(void);
static void usbSetOTGDevSpeed(USB_OTG_SPEED_t speed);
static void usbWritePkt(uint8_t *src, uint8_t epnum, uint16_t len);
static void usbDriveVBUS(uint8_t state);
static void usbHostDoPing(uint8_t chnum);
static USBD_DEVSPEED_TYPE_t usbGetDevSpeed(void);

static int usbLLInitInternal(void);

static int usbDriverWriteEmptyTxFifo(uint32_t epnum);
static void usbDriverOutXferCpltCallBack(uint32_t epnum);
static void usbDriverOUTEndPointSetupPacket(uint32_t epnum);

static void usbDeviceDriverSetTxFifo(usbDriverHandle_t *driver,
                                     uint8_t fifo, 
                                     uint16_t size);

static void usbDeviceDriverSetRxFifo(usbDriverHandle_t *driver, uint16_t size);

static usbDriverHandle_t usbDriver;


/* 
 *  The most minimal resource acquisition semantic 
 *  I could make work. Luckily I was able to find an
 *  implementation that lets me keep ISR preEmption
 *  enabled so I don't have to play all sorts of games
 *  with the NVIC.
 * 
 *  These should stay macro expansions and not 
 *  inline functions because the entire purpose
 *  of them is to abort the current stack frame
 *  if a lock cannot be acquired. 
 */
#define __USB_DRIVER_ACQUIRE_LOCK(__driverPtr)               \
    do                                                       \
    {                                                        \
        if ((__driverPtr)->mutex == USB_DRIVER_MUTEX_locked) \
        {                                                    \
            (__driverPtr)->state = USB_DRIVER_STATE_busy;    \
            return 1;                                        \
        }                                                    \
        else                                                 \
        {                                                    \
            (__driverPtr)->mutex = USB_DRIVER_MUTEX_locked;  \
        }                                                    \
                                                             \
    } while (0)

#define __USB_DRIVER_RELEASE_LOCK(__driverPtr)                 \
    do                                                         \
    {                                                          \
        if ((__driverPtr)->mutex == USB_DRIVER_MUTEX_unlocked) \
        {                                                      \
            (__driverPtr)->state = USB_DRIVER_STATE_busy;      \
            return 1;                                          \
        }                                                      \
        else                                                   \
        {                                                      \
            (__driverPtr)->mutex = USB_DRIVER_MUTEX_unlocked;  \
        }                                                      \
                                                               \
    } while (0)



void usbDriver_LinkDeviceDriverHandle(void* devDriverHandle)
{   
    LL_ASSERT(NULL != devDriverHandle);
    USBD_HandleTypeDef *pdev = (USBD_HandleTypeDef*)devDriverHandle;
    usbDriver.pData = (void*)pdev;
}


void usbEnableGlobalInterrupt(void)
{
    _USB->GAHBCFG |= GAHBCFG_GINT;
}

void usbDisableGlobalInterrupt(void)
{
    _USB->GAHBCFG &= ~GAHBCFG_GINT;
}


int usbCoreInit(void)
{   
    int status = 0;
    _USB->GUSBCFG |= GUSBCFG_PHYSEL;

    /* Reset after a PHY select and set Host mode as a default */
    status = usbCoreReset();

    if (usbDriver.Init.bat_charging_ena == 0U)
    {
        /* Activate the USB tranceiver */
        _USB->GCCFG |= GCCFG_PWRDWN;
    }
    else
    {
        /* Deactivate the USB Transceiver */
        _USB->GCCFG &= ~GCCFG_PWRDWN;
    }
    return status;
}


static int usbCoreReset(void)
{   
    int status = 0;
    uint32_t cnt = 0;
    do
    {
        if(++cnt > 200000U)
        {
            status = 1;
            break;
        }
    }   while(!(_USB->GRSTCTL & GRSTCTL_AHBIDL));

    /* Initiate soft reset */
    _USB->GRSTCTL |= GRSTCTL_CSRST;

    /* Wait for hardware to clear the soft reset bit */
    cnt = 0;
    do
    {
        if(++cnt > 20000000U)
        {
            status = 2;
            break;
        }
    }   while((_USB->GRSTCTL & GRSTCTL_CSRST) == GRSTCTL_CSRST);
    return status;
}


static void usbSetOTGDevSpeed(USB_OTG_SPEED_t speed)
{       
    /* semsorcard target MCU's only support 
    FS mode with their embedded peripheral */
#if defined(STM32F411RE) || defined(STM32F411VE)
    LL_ASSERT(speed == USB_OTG_SPEED_full);
#endif 
    _USB->DCFG |= ((speed << DCFG_DSPD_POS) & DCFG_DSPD);
}



static const USBD_DEVSPEED_TYPE_t DSTS_ENUMSPD_to_SPDTYP[] = 
{   
    [USBD_DSTS_ENUMSPD_PHYBITS_highSpeed_30_60] = USBD_DEVSPEED_TYPE_hs,
    [USBD_DSTS_ENUMSPD_PHYBITS_fullSpeed_30_60] = USBD_DEVSPEED_TYPE_fs,
    [USBD_DSTS_ENUMSPD_PHYBITS_fullSpeed_48]    = USBD_DEVSPEED_TYPE_fs,
    [USBD_DSTS_ENUMSPD_PHYBITS_lowSpeed_6]      = USBD_DEVSPEED_TYPE_ls,
};


static USBD_DEVSPEED_TYPE_t usbGetDevSpeed(void)
{
    uint32_t speedBits = ((_USB->DSTS & DSTS_ENUMSPD) >> DSTS_ENUMSPD_POS);
    switch (speedBits)
    {
        case USBD_DSTS_ENUMSPD_PHYBITS_highSpeed_30_60:
        case USBD_DSTS_ENUMSPD_PHYBITS_fullSpeed_30_60:
        case USBD_DSTS_ENUMSPD_PHYBITS_fullSpeed_48:
        case USBD_DSTS_ENUMSPD_PHYBITS_lowSpeed_6:
        {
            return DSTS_ENUMSPD_to_SPDTYP[speedBits];
        }
        break;
        default:
        {   
            /* Default assumption is FS (thats what peripheral dflts to) */
            return USBD_DEVSPEED_TYPE_fs;
        }
    }
}



void usbSetTurnaroundTime(USBD_DEVSPEED_TYPE_t speed)
{   
    uint32_t hclk = rccGetHClkFreq();
    uint32_t tunraround_bits;
    if(USBD_DEVSPEED_TYPE_fs == speed)
    {
        if ((hclk >= 14200000U) && (hclk < 15000000U))
        {
            /* hclk Clock Range between 14.2-15 MHz */
            tunraround_bits = 0xFU;
        }
        else if ((hclk >= 15000000U) && (hclk < 16000000U))
        {
            /* hclk Clock Range between 15-16 MHz */
            tunraround_bits = 0xEU;
        }
        else if ((hclk >= 16000000U) && (hclk < 17200000U))
        {
            /* hclk Clock Range between 16-17.2 MHz */
            tunraround_bits = 0xDU;
        }
        else if ((hclk >= 17200000U) && (hclk < 18500000U))
        {
            /* hclk Clock Range between 17.2-18.5 MHz */
            tunraround_bits = 0xCU;
        }
        else if ((hclk >= 18500000U) && (hclk < 20000000U))
        {
            /* hclk Clock Range between 18.5-20 MHz */
            tunraround_bits = 0xBU;
        }
        else if ((hclk >= 20000000U) && (hclk < 21800000U))
        {
            /* hclk Clock Range between 20-21.8 MHz */
            tunraround_bits = 0xAU;
        }
        else if ((hclk >= 21800000U) && (hclk < 24000000U))
        {
            /* hclk Clock Range between 21.8-24 MHz */
            tunraround_bits = 0x9U;
        }
        else if ((hclk >= 24000000U) && (hclk < 27700000U))
        {
            /* hclk Clock Range between 24-27.7 MHz */
            tunraround_bits = 0x8U;
        }
        else if ((hclk >= 27700000U) && (hclk < 32000000U))
        {
            /* hclk Clock Range between 27.7-32 MHz */
            tunraround_bits = 0x7U;
        }
        else /* if(hclk >= 32000000) */
        {
            /* hclk Clock Range between 32-200 MHz */
            tunraround_bits = 0x6U;
        }
    }
    else
    {
        tunraround_bits = 9u;
    }

    /* update turnaround register val */
    _USB->GUSBCFG &= ~GUSBCFG_TRDT;
    _USB->GUSBCFG |= ((tunraround_bits << GUSBCFG_TRDT_POS) & GUSBCFG_TRDT);
}


void usbSetMode(USB_OTG_MODE_t mode)
{
    _USB->GUSBCFG &= ~(GUSBCFG_FHMOD | GUSBCFG_FDMOD);
    switch(mode)
    {
        case USB_OTG_MODE_host:
        {
            _USB->GUSBCFG |= GUSBCFG_FHMOD;
        }
        break;
        case USB_OTG_MODE_device:
        {
            _USB->GUSBCFG |= GUSBCFG_FDMOD;
        }
        break;
        case USB_OTG_MODE_drd:
        {
            /** @todo IMPLEMENT DRD HANDLER */
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }
    USBD_Delay(50U);
}


static int usbFlushTxFifo(uint32_t num)
{   
    int status = 0;
    _USB->GRSTCTL = (GRSTCTL_TXFFLSH | (num << GRSTCTL_TXFNUM_POS));
    uint32_t count = 0U;
    do
    {
        if (++count > 200000U)
        {
            status = 1;
            break;
        }
    } while ((_USB->GRSTCTL & GRSTCTL_TXFFLSH) == GRSTCTL_TXFFLSH);
    return status;
}


static int usbFlushRxFifo(void)
{   
    int status = 0;
    uint32_t count = 0;
    _USB->GRSTCTL = GRSTCTL_RXFFLSH;
    do
    {
        if (++count > 200000U)
        {   
            status = 1;
            break;
        }
    } while ((_USB->GRSTCTL & GRSTCTL_RXFFLSH) == GRSTCTL_RXFFLSH);
    return status;
}


int usbDeviceModeInit(void)
{
    int status = 0;
    unsigned i;


    /* clear device in endpt tx fifo sizes */
    for(i = 0; i < 15; i++)
    {
        _USB->DIEPTXF[i] = 0;
    }

    if(usbDriver.Init.vbus_sensing_enable == 0)
    {
        /*
         * Disable HW VBUS sensing. 
         * VBUS is internally considered to be always
         * at VBUS-Valid level (5V).
         * 
         * (FOR EMBEDDED SENSOR CARD, WE DO NOT WANT TO DO THIS)
         */
        _USB->GCCFG |= GCCFG_NOVBUSSENS;
        _USB->GCCFG &= ~GCCFG_VBUS_B_SEN;   /* note: "B" bus -> device */
        _USB->GCCFG &= ~GCCFG_VBUS_A_SEN;   /* note: "A" bus -> host   */
    }
    else
    {
        /* Enable HW VBUS sensing */
        _USB->GCCFG &= ~GCCFG_NOVBUSSENS;
        _USB->GCCFG |= GCCFG_VBUS_B_SEN;
    }

    /* restart the clk */
    _USB->PCGCTL = 0;

    /* Device mode optimal framing configuration */
    _USB->DCFG |= USBD_DCFG_FRAME_INTERVAL_80;

    usbSetOTGDevSpeed(USB_OTG_SPEED_full);

    /* FLUSH ALL THE TX FIFOS (0x10 == all of em) */
    if(0 != usbFlushTxFifo(0x10))
    {
        status = 1;
    }

    /* flush the RX fifo */
    if(0 != usbFlushRxFifo())
    {
        status = 2;
    }


    /* clear any pending device interrupts */
    _USB->DIEPMSK  = 0;
    _USB->DOEPMSK  = 0;
    _USB->DAINTMSK = 0;

    /* IN ENDPOINTS */
    for(i = 0; i < usbDriver.Init.dev_endpoints; i++)
    {
        if((_USB->DIEP[i].CTL & DIEPCTL_EPENA) == DIEPCTL_EPENA)
        {   
            /* Case for the very first endpoint */
            if(0 == i)
            {
                _USB->DIEP[i].CTL = DIEPCTL_SNAK;
            }
            _USB->DIEP[i].CTL |= DIEPCTL_EPDIS;
        }
        else
        {   
            _USB->DIEP[i].CTL = 0;
        }

        _USB->DIEP[i].SIZ = 0;
        _USB->DIEP[i].INT = 0xfb7f;
    }

    /* OUT ENDPOINTS */
    for(i = 0; i < usbDriver.Init.dev_endpoints; i++)
    {
        if((_USB->DOEP[i].CTL & DOEPCTL_EPENA) == DOEPCTL_EPENA)
        {   
            /* Case for the very first endpoint */
            if(0 == i)
            {
                _USB->DOEP[i].CTL = DOEPCTL_SNAK;
            }

            _USB->DOEP[i].CTL |= DOEPCTL_EPDIS;
        }
        else
        {   
            _USB->DOEP[i].CTL = 0;
        }

        _USB->DOEP[i].SIZ = 0;
        _USB->DOEP[i].INT = 0xfb7f;
    }

    _USB->DIEPMSK &= ~(DIEPMSK_TXFURM);

    /* Disable interrupts */
    _USB->GINTMSK = 0;

    /* Clear any pending interrupts */
    _USB->GINTSTS = 0xBFFFFFFFU;

    /* Enable DEVICE interrupts ONLY */
    _USB->GINTMSK = 
                    (GINTMSK_RXFLVLM         |  /* Receive FIFO evt     */
                     GINTMSK_USBSUSPM        |  /* remote Suspend       */
                     GINTMSK_USBRST          |  /* Host reset           */
                     GINTMSK_ENUMDNEM        |  /* Enum endpt req       */
                     GINTMSK_IEPINT          |  /* In endpt irq         */
                     GINTMSK_OEPINT          |  /* out endpt irq        */
                     GINTMSK_IISOIXFRM       |  /* bad isoc pkt IN msk  */
                     GINTMSK_PXFRM_IISOOXFRM |  /* bad isoc plt OUT msk */
                     GINTMSK_WUIM            ); /* remote wakeup        */

    if(usbDriver.Init.vbus_sensing_enable)
    {
        _USB->GINTMSK |= (GINTMSK_SRQIM | GINTMSK_OTGINT);
    }

    if(usbDriver.Init.Sof_enable)
    {
        _USB->GINTMSK |= GINTMSK_SOFM;  
    }

    return status;
}


int usbActivateEndpoint(usbEndPoint_t *ep)
{
    int status = 0;
    uint32_t num = (uint32_t)ep->num;
    uint32_t type = (uint32_t)ep->type;
    uint32_t epPos = (uint32_t)(1 << (num & __EP_ADDR_MSK));
    if(ep->is_in)
    {
        _USB->DAINTMSK |= (DAINTMSK_IEPM & (epPos << DAINTMSK_IEPM_POS));

        /* If endpoint not enabled, enable it */
        if(!(_USB->DIEP[num].CTL & DIEPCTL_USBAEP))
        {
            _USB->DIEP[num].CTL |= 
                ((ep->maxpacket << DIEPCTL_MPSIZ_POS) & DIEPCTL_MPSIZ);

            _USB->DIEP[num].CTL |= 
                ((type << DIEPCTL_EPTYP_POS) & DIEPCTL_EPTYP);

            _USB->DIEP[num].CTL |= 
                ((num << DIEPCTL_TXFNUM_POS) & DIEPCTL_TXFNUM); 

            _USB->DIEP[num].CTL |= DIEPCTL_SD0PID_SEVNFRM;
            _USB->DIEP[num].CTL |= DIEPCTL_USBAEP;
        }
    }
    else
    {
        _USB->DAINTMSK |= (DAINTMSK_OEPM & (epPos << DAINTMSK_OEPM_POS));

        /* If endpoint not enabled, enable it */
        if(!(_USB->DOEP[num].CTL & DOEPCTL_USBAEP))
        {
            _USB->DOEP[num].CTL |= 
                ((ep->maxpacket << DOEPCTL_MPSIZ_POS) & DOEPCTL_MPSIZ);
                                        
            _USB->DOEP[num].CTL |= 
                ((type << DOEPCTL_EPTYP_POS) & DOEPCTL_EPTYP);

            _USB->DOEP[num].CTL |= DOEPCTL_SD0PID_SEVNFRM;
            _USB->DOEP[num].CTL |= DOEPCTL_USBAEP;
        }
    }
    return status;
}


void usbDeactivateEndpoint(usbEndPoint_t *ep)
{
    uint32_t epnum = ep->num;
    uint32_t epPos = (uint32_t)(1 << (epnum & __EP_ADDR_MSK));
    if(ep->is_in)
    {
        _USB->DEACHMSK &= ~(DAINTMSK_IEPM & (epPos << DAINTMSK_IEPM_POS));
        _USB->DAINTMSK &= ~(DAINTMSK_IEPM & (epPos << DAINTMSK_IEPM_POS));
        _USB->DIEP[epnum].CTL &= ~(DIEPCTL_USBAEP         |
                                   DIEPCTL_MPSIZ          |
                                   DIEPCTL_TXFNUM         |
                                   DIEPCTL_SD0PID_SEVNFRM |
                                   DIEPCTL_EPTYP          );
    }
    else
    {   
        _USB->DEACHMSK &= ~(DAINTMSK_OEPM & (epPos << DAINTMSK_OEPM_POS));
        _USB->DAINTMSK &= ~(DAINTMSK_OEPM & (epPos << DAINTMSK_OEPM_POS));
        _USB->DOEP[epnum].CTL &= ~(DOEPCTL_USBAEP         |
                                   DOEPCTL_MPSIZ          |
                                   DOEPCTL_SD0PID_SEVNFRM |
                                   DOEPCTL_EPTYP          );
    }
}



void usbStartEndPointXfer(usbEndPoint_t *ep)
{
    uint32_t num = (uint32_t)ep->num;

    if(ep->is_in)
    {   
        _USB->DIEP[num].SIZ &= ~DIEPTSIZ_PKTCNT;
        _USB->DIEP[num].SIZ &= ~DIEPTSIZ_XFRSIZ;

        /* Case of 0 length (payload length, not descriptor length) packet */
        if(ep->xfer_len == 0)
        {
            _USB->DIEP[num].SIZ |= DIEPTSIZ_PKTCNT & (1 << DIEPTSIZ_PKTCNT_POS);
        }
        else
        {   
            /* Program the transfer size and packet count
             * as follows: xfersize = N * maxpacket +
             * short_packet pktcnt = N + (short_packet
             * exist ? 1 : 0)
             */
            _USB->DIEP[num].SIZ |= 
                    DIEPTSIZ_PKTCNT & 
                    ((((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket)) 
                        << DIEPTSIZ_PKTCNT_POS);

            _USB->DIEP[num].SIZ |= (DIEPTSIZ_XFRSIZ & ep->xfer_len);

            /* iF THE ENDPOINT IS ISOCHRONOUS */
            if(ep->type == USB_EPTYPE_isoc)
            {
                _USB->DIEP[num].SIZ &= ~DIEPTSIZ_MULCNT;
                _USB->DIEP[num].SIZ |=  DIEPTSIZ_MULCNT & 
                                        (1 << DIEPTSIZ_MULCNT_POS);

                
            }
        }

        _USB->DIEP[num].CTL |= (DIEPCTL_CNAK | DIEPCTL_EPENA);

        /* If endpoint is isochronous */
        if(ep->type != USB_EPTYPE_isoc)
        {
            if(ep->xfer_len > 0)
            {
                _USB->DIEPEMPMSK |= (1 << ((uint32_t)ep->num & __EP_ADDR_MSK));
            }
        }
        else
        {   
            /* Start of frame check */
            if(_USB->DSTS & ( 1 << DSTS_FNSOF_POS) == 0)
            {
                _USB->DIEP[num].CTL |= DIEPCTL_SODDFRM;
            }
            else
            {
                _USB->DIEP[num].CTL |= DIEPCTL_SD0PID_SEVNFRM;
            }

            usbWritePkt(ep->xfer_buff, ep->num, ep->xfer_len);
        }
    }
    else
    {
        /* OUT ENDPOINT */
        _USB->DOEP[num].SIZ &= ~DIEPTSIZ_XFRSIZ;
        _USB->DOEP[num].SIZ &= ~DIEPTSIZ_PKTCNT;

        if(ep->xfer_len == 0)
        {
            _USB->DOEP[num].SIZ |= DOEPTSIZ_XFRSIZ & ep->maxpacket;
            _USB->DOEP[num].SIZ |= DOEPTSIZ_PKTCNT & (1 << DOEPTSIZ_PKTCNT_POS);
        }
        else
        {
            uint16_t pktCnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1) / ep->maxpacket);

            _USB->DOEP[num].SIZ |=  DOEPTSIZ_PKTCNT & 
                                    (uint32_t)(pktCnt << DOEPTSIZ_PKTCNT_POS);
            
            _USB->DOEP[num].SIZ |=  DOEPTSIZ_XFRSIZ & 
                                    (uint32_t)(ep->maxpacket *pktCnt); 
        }

        if (ep->type == USB_EPTYPE_isoc)
        {   
            /* Start of frame check */
            if(_USB->DSTS & (1 << DSTS_FNSOF_POS) == 0)
            {
                _USB->DOEP[num].CTL |= DOEPCTL_SODDFRM;
            }
            else
            {
                _USB->DOEP[num].CTL |= DOEPCTL_SD0PID_SEVNFRM;
                
            }
        }

        /* Enable endpt */
        _USB->DOEP[num].CTL |= (DOEPCTL_CNAK | DOEPCTL_EPENA);
    }
}


void usbEndPoint0StartXfer(usbEndPoint_t* ep)
{
    uint32_t num = ep->num;
    if(ep->is_in)
    {   
        _USB->DIEP[num].SIZ &= ~DIEPTSIZ_XFRSIZ;
        _USB->DIEP[num].SIZ &= ~DIEPTSIZ_PKTCNT;

        if(0 == ep->xfer_len)
        {
            _USB->DIEP[num].SIZ |= DIEPTSIZ_PKTCNT & (1 << DIEPTSIZ_PKTCNT_POS);
        }
        else
        {
            if (ep->xfer_len > ep->maxpacket)
            {
                ep->xfer_len = ep->maxpacket;
            }

            _USB->DIEP[num].SIZ |= DIEPTSIZ_PKTCNT & (1 << DIEPTSIZ_PKTCNT_POS);
            _USB->DIEP[num].SIZ |= DIEPTSIZ_XFRSIZ & ep->xfer_len;


            _USB->DIEP[num].CTL |= (DIEPCTL_CNAK | DIEPCTL_EPENA);

            if(ep->xfer_len > 0)
            {
                _USB->DIEPEMPMSK |= (1 << (num & __EP_ADDR_MSK));
            }
        }
    }
    else
    {
        if(ep->xfer_len > 0)
        {
            ep->xfer_len = ep->maxpacket;
        }

        _USB->DOEP[num].SIZ |= DOEPTSIZ_PKTCNT & (1 << DOEPTSIZ_PKTCNT_POS);
        _USB->DOEP[num].SIZ |= DOEPTSIZ_XFRSIZ & ep->maxpacket;
        _USB->DOEP[num].CTL |= (DOEPCTL_CNAK | DOEPCTL_EPENA);
    }
}


static void usbWritePkt(uint8_t *src, uint8_t epnum, uint16_t len)
{   
    LL_ASSERT(NULL != src);
    uint32_t *pSrc = (uint32_t*)src;
    uint32_t wordcnt;
    uint32_t i;
                                /* 
                                 *  This addition part is because last 
                                 *  3 bytes have to be word aligned.
                                 */
    wordcnt = (uint32_t)(len + ((sizeof(wordcnt) - sizeof(*src)))) 
                                    / sizeof(wordcnt);

    for(i = 0; i < wordcnt; i++)
    {   
        /* PLEASE DON'T TOUCH THIS                                        */
        /* This is very critical. Took FOREVER to get it to work reliably */
        *(volatile uint32_t*)(_USB->DFIFO[i].buf)=__UNALIGNED_UINT32_READ(pSrc);
        pSrc++;
    }
}


void* usbReadPkt(uint8_t *dst, uint16_t len)
{
    uint32_t *dstPtr = (uint32_t*)dst;

    /* alignment setup + padding */       
    const uint32_t wordCnt = (((uint32_t)len + 3U) / 4U); 
    unsigned i;                      
    for(i = 0; i < wordCnt; i++)
    {   
        /* 
         * Don't touch this unless you REALLY REALLY understand how 
         * the arm ISA handles access alignment exceptions under the hood 
         */
        volatile uint32_t * addr;
        addr = (volatile uint32_t*)&_USB->DFIFO[i].buf[0];
        __UNALIGNED_UINT32_WRITE(dstPtr, *addr);
        dstPtr++;
    }

    /* Caller can use retval to check if expected pkt was fully rxed */
    return (void*)dstPtr;
}


int usbSetEndPointStall(usbEndPoint_t *ep)
{   
    int status = 0;
    uint32_t num = ep->num;

    if (ep->is_in == 1U)
    {   
        if(_USB->DIEP[num].CTL & DIEPCTL_EPENA)
        {
            if(num != 0)
            {
                _USB->DIEP[num].CTL &= ~DIEPCTL_EPDIS;
            }
            _USB->DIEP[num].CTL |= DIEPCTL_STALL;
        }
    }
    else
    {
        if((_USB->DOEP[num].CTL & DOEPCTL_EPENA) == 0)
        {
            if(num != 0)
            {
                _USB->DOEP[num].CTL &= ~DOEPCTL_EPDIS;
            }
            _USB->DOEP[num].CTL |= DOEPCTL_STALL;
        }
    }
    return status;
}



int usbClearEndPointStall(usbEndPoint_t *ep)
{   
    int status = 0;
    uint32_t num = ep->num;
    if(ep->is_in)
    {
        _USB->DIEP[num].CTL &= ~DIEPCTL_STALL;
        if((ep->type == USB_EPTYPE_intr) || (ep->type == USB_EPTYPE_bulk))
        {
            _USB->DIEP[num].CTL |= DIEPCTL_SD0PID_SEVNFRM;
        }
    }
    else
    {
        _USB->DOEP[num].CTL &= ~DOEPCTL_STALL;
        if((ep->type == USB_EPTYPE_intr) || (ep->type == USB_EPTYPE_bulk))

        {
            _USB->DIEP[num].CTL |= DOEPCTL_SD0PID_SEVNFRM;
        }
    }
    return status;
}




int usbStopDevice(void)
{   
    int status = 0;
    unsigned i;
    unsigned max = sizeof(_USB->DIEP)/sizeof(_USB->DIEP[0]);
    for(i = 0; i < max; i++)
    {   
        /* Clear pending interrupts for the endpoints */
        _USB->DIEP[i].INT = 0xFB7FU;
        _USB->DOEP[i].INT = 0xFB7FU;
    }

    /* Mask all new interrupts */
    _USB->DIEPMSK = 0;
    _USB->DOEPMSK = 0;
    _USB->DAINTMSK = 0;

    if(0 != usbFlushRxFifo())
    {
        status = 1;
    }

    if(0 != usbFlushTxFifo(0x10))
    {
        status = 2;
    }

    return status;
}



void usbSetDeviceAddress(uint8_t address)
{
    _USB->DCFG &= ~DCFG_DAD;
    _USB->DCFG |= ((uint32_t)address << DCFG_DAD_POS) & DCFG_DAD;

}


void usbDeviceConnect(void)
{
    _USB->DCTL &= ~DCTL_SDIS;
    USBD_Delay(3U);
}


void usbDeviceDisconnect(void)
{                   
    _USB->DCTL |= DCTL_SDIS;
    USBD_Delay(3U);

}


uint32_t usbReadInterrupts(void)
{
    uint32_t tmp = 0;
    tmp = _USB->GINTSTS;
    tmp &= _USB->GINTMSK;
    return tmp;
}


uint32_t usbDeviceReadAllEndPointInterrupts(uint8_t is_in)
{
    uint32_t tmp = 0;

    /* Get Device Interrupts */
    tmp = _USB->DAINT;
    tmp &= _USB->DAINTMSK;

    if(is_in)
    {
        tmp &= DAINT_IEPINT;
        tmp >>= DAINT_IEPINT_POS;
    }
    else
    {
        tmp &= DAINT_OEPINT;
        tmp >>= DAINT_OEPINT_POS;
    }
    return tmp;
}



uint32_t usbDeviceReadOutEndPointInterrupt(uint8_t epnum)
{   
    uint32_t tmp = 0;
    tmp = _USB->DOEP[epnum].INT;
    tmp &= _USB->DOEPMSK;
    return tmp;
}


uint32_t usbDeviceReadInEndPointInterrupt(uint8_t epnum)
{
    uint32_t tmp = 0;
    uint32_t msk = 0;
    uint32_t emp = 0;
    msk = _USB->DIEPMSK;
    emp = _USB->DIEPEMPMSK;
    msk |= (emp >> (epnum & __EP_ADDR_MSK) & 1U) << 7U;
    tmp = _USB->DIEP[epnum].INT & msk;
    return tmp;
}


void usbClearInterrupts(uint32_t interrupts)
{
    _USB->GINTSTS |= interrupts;
}



uint32_t usbGetMode(void)
{
    return ((_USB->GINTSTS & GINTSTS_CMOD) >> GINTSTS_CMOD_POS);
}


void usbActivateSetup(void)
{
    _USB->DIEP[0].CTL &= ~DIEPCTL_MPSIZ;

    if((_USB->DSTS & DSTS_ENUMSPD) == USBD_DSTS_ENUMSPD_PHYBITS_lowSpeed_6)
    {
        _USB->DIEP[0].CTL |= 3U;
    }

    _USB->DCTL |= DCTL_CGINAK;
}


int usbOEP0Start(uint8_t *psetup)
{
    int status = 0;
    uint32_t gSNPSid = *(volatile uint32_t*)(&_USB->CID + 0x1U);

    if(gSNPSid > USB_OTG_CORE_ID_300A)
    {
        if((_USB->DOEP[0].CTL & DOEPCTL_EPENA) == DOEPCTL_EPENA)
        {
            return status;
        }
    }
    else
    {
        _USB->DOEP[0].SIZ = 0;
        _USB->DOEP[0].SIZ |= (DOEPTSIZ_PKTCNT & (0x1U << DOEPTSIZ_PKTCNT_POS));
        _USB->DOEP[0].SIZ |= (3U * 8U);
        _USB->DOEP[0].SIZ |= DOEPTSIZ_STUPCNT;
    }

    return status;
}



static void usbDriveVBUS(uint8_t state)
{
    volatile uint32_t hostPort = 0;
    hostPort = _USB->HPRT;

    hostPort &= ~(  HPRT_PENA    |
                    HPRT_PCDET   |
                    HPRT_PENCHNG |
                    HPRT_POCCHNG );

    /* If VBUS is disabled when it shouldn't be, enable it */
    if(((hostPort & HPRT_PPWR) == 0U) && (1 == state))
    {
        _USB->HPRT = hostPort | HPRT_PPWR;
    }

    /* If VBUS is enabled when it shouldn't be, disable it */
    if (((hostPort & HPRT_PPWR) == HPRT_PPWR) && (state == 0U))
    {
        _USB->HPRT = ((~HPRT_PPWR) & hostPort);
    }
}


void usbHostInit(usbOTGConfig_t cfg)
{
    /* restart PHY clock */
    _USB->PCGCTL = 0;

    /*
     * Disable HW VBUS sensing. 
     * 
     * VBUS is internally considered to be always
     * at VBUS-Valid level (5V).
     */
    _USB->GCCFG |= GCCFG_NOVBUSSENS;
    _USB->GCCFG &= ~GCCFG_VBUS_B_SEN;
    _USB->GCCFG &= ~GCCFG_VBUS_A_SEN;

    if(_USB->CID & (1u << 8) != 0)
    {
        if(cfg.speed == USB_OTG_SPEED_full)
        {   
            _USB->HCFG |= HCFG_FSLSS;
        }
        else
        {   
            /* Set default max speed to support HS spec           */
            /** WARNING: HW DOESN'T SUPPORT HS SPEED ON STM32F411 */
            _USB->HCFG &= ~HCFG_FSLSS;
        }
        
    }

    /* Make sure the FIFOs are flushed. */
    (void)usbFlushTxFifo(0x10U); /* all Tx FIFOs */
    (void)usbFlushRxFifo();

    /*
     * Clear pending host channel interrupts
     * and disable future interrupts 
     */
    unsigned i;
    for( i = 0; i < cfg.Host_channels; i++)
    {
        _USB->HC[i].INT = 0xffffffff;
        _USB->HC[i].INTMSK = 0;
    }

    usbDriveVBUS(1);

    USBD_Delay(200U);
    
    /* clear and disable interrupts */
    _USB->GINTSTS = 0xffffffff;
    _USB->GINTMSK = 0;
    
    if(_USB->CID & (1u << 8) != 0)
    {   
        /* Set RX fifo size */
        _USB->GRXFSIZ = 0x200U;
        _USB->DIEPTXF0_HNPTXFSIZ = (uint32_t)((0x100 << NPTXFD_POS) & NPTXFD); 
        _USB->DIEPTXF0_HNPTXFSIZ |= (uint32_t)0x200U;

        _USB->HPTXFSIZ = (uint32_t)((0xE0U << HPTXFSIZ_PTXFD_POS) 
                                        & HPTXFSIZ_PTXFD);

        _USB->HPTXFSIZ |= (uint32_t)0x300U;
    }
    else
    {   
        /* Set RX fifo size */
        _USB->GRXFSIZ = 0x80U;

        _USB->DIEPTXF0_HNPTXFSIZ = (uint32_t)((0x60U << NPTXFD_POS) & NPTXFD); 
        _USB->DIEPTXF0_HNPTXFSIZ |= (uint32_t)0x80U;
        
        _USB->HPTXFSIZ = (uint32_t)((0x40U <<  HPTXFSIZ_PTXFD_POS) & HPTXFSIZ_PTXFD);
        _USB->HPTXFSIZ |= (uint32_t)0x300U;

        /* Enable interrupts HOST mode interrupts */
        _USB->GINTMSK |= 
              (GINTMSK_RXFLVLM        | 
              GINTMSK_PRTIM           |
              GINTMSK_HCIM            |
              GINTMSK_SOFM            |
              GINTSTS_DISCINT         |
              GINTMSK_PXFRM_IISOOXFRM |
              GINTMSK_WUIM            );
    }
}


void usbHostInitFull_orLow_Speed_ClkSel(uint8_t freq)
{
    _USB->HCFG &= ~HCFG_FSLSPCS;
    _USB->HCFG |= ((uint32_t)freq) & HCFG_FSLSPCS;

    switch(freq)
    {
        case USBH_HCFG_FREQ_48MHZ:
        {
            _USB->HFIR = 48000U;
        }
        break;
        case USBH_HCFG_FREQ_30_60MHZ:
        {
            _USB->HFIR = 60000U;
        }
        break;
        case USBH_HCFG_FREQ_6MHZ:
        {
            _USB->HFIR = 6000U;
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
    }
}


static void usbHostDoPing(uint8_t chnum)
{   
    uint32_t num_packets = 1U;
    _USB->HC[chnum].TSIZ = (num_packets << HCTSIZ_PKTCNT_POS) & HCTSIZ_PKTCNT;
    _USB->HC[chnum].TSIZ |= HCTSIZ_DOPING;

    uint32_t tmp = _USB->HC[chnum].CHAR;
    tmp &= ~HCCHAR_CHDIS;
    tmp |= HCCHAR_CHENA;
    _USB->HC[chnum].CHAR = tmp;
}


void usbHostResetPort(void)
{
    volatile uint32_t hostPort = 0;
    hostPort = _USB->HPRT;

    hostPort &= ~(HPRT_PENA    | 
                  HPRT_PCDET   |
                  HPRT_PENCHNG | 
                  HPRT_POCCHNG );

    /* Reset host port AFTER other parameters have been cfged */
    _USB->HPRT = (HPRT_PRST | hostPort);

    /* Application MUST wait at least 20ms before clearing reset bit */
    USBD_Delay(20U);

    _USB->HPRT = ((~HPRT_PRST) & hostPort);

    USBD_Delay(20U);
}



uint32_t usbHostGetSpeed(void)
{
    volatile uint32_t hostPort = 0;
    hostPort = _USB->HPRT;
    return (hostPort & HPRT_PSPD) >> HPRT_PSPD_POS;
}

uint32_t usbHostGetCurrentFrameNum(void)
{
    return ((_USB->HFNUM & HFNUM_FRNUM) >> HFNUM_FRNUM_POS);
}



void usbHostChannelInit(uint8_t chnum,
                       uint8_t epnum,
                       uint8_t devAddr,
                       uint8_t speed,
                       uint8_t eptype,
                       uint16_t mps)
{
    uint32_t HCcharEpDir    = 0;
    uint32_t HCcharLowSpeed = 0;

    /* Clear old interrupt conditions for this host channel. */
    _USB->HC[chnum].INT = 0xFFFFFFFFU;

    switch(eptype)
    {   
        case USB_EPTYPE_ctl: /* fallthrough */
        case USB_EPTYPE_bulk:
        {
            _USB->HC[chnum].INTMSK = (HCINTMSK_XFRCM |
                                     HCINTMSK_STALLM |
                                     HCINTMSK_TXERRM |
                                     HCINTMSK_DTERRM |
                                     HCINTMSK_AHBERR |
                                     HCINTMSK_NAKM   );

            if((epnum & 0x80U) == 0x80U)
            {
                _USB->HC[chnum].INTMSK |= HCINTMSK_BBERRM;
            }
            else
            {
                if ((_USB->CID & (0x1U << 8)) != 0U)
                {
                    _USB->HC[chnum].INTMSK |= (HCINTMSK_NYET | HCINTMSK_ACKM);
                }
            }
        } 
        break;
        case USB_EPTYPE_intr:
        {
            _USB->HC[chnum].INTMSK = (HCINTMSK_XFRCM |
                                     HCINTMSK_STALLM |
                                     HCINTMSK_TXERRM |
                                     HCINTMSK_DTERRM |
                                     HCINTMSK_NAKM   |
                                     HCINTMSK_AHBERR |
                                     HCINTMSK_FRMORM );

            if((epnum & 0x80U) == 0x80u)
            {
                _USB->HC[chnum].INTMSK |= HCINTMSK_BBERRM;
            }
        }
        break;
        case USB_EPTYPE_isoc:
        {   
            _USB->HC[chnum].INTMSK = (HCINTMSK_XFRCM  |
                                      HCINTMSK_ACKM   |
                                      HCINTMSK_AHBERR |
                                      HCINTMSK_FRMORM );

            if((epnum & 0x80U) == 0x80u)
            {
                _USB->HC[chnum].INTMSK |= HCINTMSK_TXERRM;
                _USB->HC[chnum].INTMSK |= HCINTMSK_BBERRM;

            }
        }
        break;
        default:
        {
            LL_ASSERT(0);
        }
        break;
    }

    /* Enable the top level host channel interrupt. */
    _USB->HAINTMSK |= 1UL << (chnum & __EP_ADDR_MSK);

    /* Make sure host channel interrupts are enabled. */
    _USB->GINTMSK |= GINTMSK_HCIM;

    /* Program the HCCHAR register */
    if ((epnum & 0x80U) == 0x80U)
    {
        HCcharEpDir = (0x1U << HCCHAR_EPDIR_POS) & HCCHAR_EPDIR;
    }
    else
    {
        HCcharEpDir = 0U;
    }


    if (speed == USBH_HPRT_PRTSPD_ls)
    {
        HCcharLowSpeed = (0x1U << HCCHAR_LSDEV_POS) & HCCHAR_LSDEV;
    }
    else
    {
        HCcharLowSpeed = 0U;
    }

    /* configure channel address register parameters */

    _USB->HC[chnum].CHAR = 
        (((uint32_t)devAddr << HCCHAR_DAD_POS) & HCCHAR_DAD);

    _USB->HC[chnum].CHAR |= 
        (((((uint32_t)epnum) & 0x7FU) << HCCHAR_EPNUM_POS) & HCCHAR_EPNUM);

    _USB->HC[chnum].CHAR |= 
        ((((uint32_t)eptype) << HCCHAR_EPTYP_POS) & HCCHAR_EPTYP);
    
    _USB->HC[chnum].CHAR |=
        ((((uint32_t)mps) << HCCHAR_MPSIZ_POS) & HCCHAR_MPSIZ);

    _USB->HC[chnum].CHAR |= HCcharEpDir;

    _USB->HC[chnum].CHAR |= HCcharLowSpeed;

    if(eptype == USB_EPTYPE_intr)
    {
        _USB->HC[chnum].CHAR |= HCCHAR_ODDFRM;
    }
}



int usbHostChannelStartXfer(usbHostChannel_t *ch)
{
    int status = 0;
    uint32_t num = ch->ch_num;
    volatile uint32_t tmp = 0;
    uint8_t isOddParity = 0;
    uint16_t wordCnt = 0;
    uint16_t num_packets;
    uint16_t max_hc_pkt_count = 256U;

    if (((_USB->CID & (0x1U << 8)) != 0U) && (USBH_HPRT_PRTSPD_hs == ch->speed))
    {
        if ((ch->do_ping == 1U))
        {   
            usbHostDoPing(num);
            return status;
        }
    }

    if(ch->xfer_len > 0)
    {
        num_packets = (uint16_t)(ch->xfer_len + ch->max_packet - 1);
        num_packets = (uint16_t)(num_packets / ch->max_packet); 

        if(num_packets > max_hc_pkt_count)
        {
            num_packets = max_hc_pkt_count;
            ch->xfer_len = (uint32_t)num_packets * ch->max_packet;
        }
    }
    else
    {
        num_packets = 1;
    }
    
    if(ch->ep_is_in)
    {
        ch->xfer_len = (uint32_t)num_packets * ch->max_packet;

    }

    _USB->HC[num].TSIZ = (ch->xfer_len & HCTSIZ_XFRSIZ) |
                         (((uint32_t)num_packets << HCTSIZ_PKTCNT_POS) & 
                         HCTSIZ_PKTCNT) |
                         (((uint32_t)ch->data_pid << HCTSIZ_DPID_POS) & 
                         HCTSIZ_DPID);

    _USB->HC[num].DMA = (uint32_t)ch->xfer_buff;

    isOddParity = ((_USB->HFNUM & 1U) ? 0 : 1U);
    _USB->HC[num].CHAR &= ~HCCHAR_ODDFRM;
    _USB->HC[num].CHAR |= isOddParity << HCCHAR_ODDFRM_POS;

    tmp = _USB->HC[num].CHAR;
    tmp &= ~HCCHAR_CHDIS;

    /* set endpt direction */
    if(ch->ep_is_in)
    {
        tmp |= HCCHAR_EPDIR;
    }
    else
    {
        tmp &= ~HCCHAR_EPDIR;
    }

    /* Activate endpt */
    tmp |= HCCHAR_CHENA;
    _USB->HC[num].CHAR = tmp;

    if(!ch->ep_is_in && (ch->xfer_len > 0))
    {   
        wordCnt = (uint16_t)((ch->xfer_len + 3)/ 4);
        switch(ch->ep_type)
        {
            case USB_EPTYPE_ctl:
            case USB_EPTYPE_bulk:
            {
               /* check if payload will fit */
               if(wordCnt > (_USB->HNPTXSTS & 0xFFFFU))
               {
                    /* need to process data in nptxfempty interrupt */
                    _USB->GINTMSK |= GINTMSK_NPTXFEM;
               }
            }
            break;
            case USB_EPTYPE_intr:
            case USB_EPTYPE_isoc:
            {
                    /* check if there is enough space in FIFO space */
                    if (wordCnt > (_USB->HPTXSTS & 0xFFFFU)) 
                    {
                        /* split the transfer into multiple packets */
                        _USB->GINTMSK |= GINTMSK_PTXFEM;
                    }
            }
            break;
            default:
            {
                LL_ASSERT(0);
            }
            break;
        }

        /* Write packet into the Tx FIFO. */
        usbWritePkt(ch->xfer_buff, ch->ch_num, (uint16_t)ch->xfer_len);
    }
    return status;
}


uint32_t usbHostChannelReadInterrupt(void)
{
    return (_USB->HAINT & 0xFFFFu);
}



int usbHostChannelHalt(uint8_t chnum)
{   
    int status = 0;
    uint32_t epType = (_USB->HC[chnum].CHAR & HCCHAR_EPTYP) >> HCCHAR_EPTYP_POS;
    uint32_t count = 0;

    /* Check for space in the request queue to issue the halt. */
    if ((epType == USB_EPTYPE_ctl) || (epType == USB_EPTYPE_bulk))
    {   
        /* Disable t he channel */
        _USB->HC[chnum].CHAR |= HCCHAR_CHDIS;

        if ((_USB->HNPTXSTS & (0xFFU << 16)) == 0U)
        {
            _USB->HC[chnum].CHAR &= ~HCCHAR_CHENA;
            _USB->HC[chnum].CHAR |= HCCHAR_CHENA;
            _USB->HC[chnum].CHAR &= ~HCCHAR_EPDIR;
            do
            {
                if (++count > 1000U)
                {   
                    status = 1;
                    break;
                }
            }   while ((_USB->HC[chnum].CHAR & HCCHAR_CHENA) == HCCHAR_CHENA);
        }
        else
        {
            _USB->HC[chnum].CHAR |= HCCHAR_CHENA;
        }
    }
    else
    {
        _USB->HC[chnum].CHAR |= HCCHAR_CHDIS;

        if ((_USB->HPTXSTS & (0xFFU << 16)) == 0U)
        {
            _USB->HC[chnum].CHAR &= ~HCCHAR_CHENA;
            _USB->HC[chnum].CHAR |= HCCHAR_CHENA;
            _USB->HC[chnum].CHAR &= ~HCCHAR_EPDIR;

            count = 0;
            do
            {
                if (++count > 1000U)
                {   
                    status = 1;
                    break;
                }
            }   while ((_USB->HC[chnum].CHAR & HCCHAR_CHENA) == HCCHAR_CHENA);
        }
        else
        {
            _USB->HC[chnum].CHAR |= HCCHAR_CHENA;
        }
    }
    return status;
}


int usbHostStop(void)
{   
    int status = 0;
    uint32_t count = 0;
    uint32_t value = 0;
    unsigned i;

    usbDisableGlobalInterrupt();

    usbFlushRxFifo();
    usbFlushTxFifo(0x10); /* All fifos */

    /* Flush out any leftover queued requests. */
    for (i = 0U; i <= 15U; i++)
    {
        value = _USB->HC[i].CHAR;
        value |= HCCHAR_CHDIS;
        value &= ~HCCHAR_CHENA;
        value &= ~HCCHAR_EPDIR;
        _USB->HC[i].CHAR = value;
    }


    /* Halt all channels to put them into a known state. */
    for (i = 0U; i <= 15U; i++)
    {
        value = _USB->HC[i].CHAR;

        value |= HCCHAR_CHDIS;
        value |= HCCHAR_CHENA;
        value &= ~HCCHAR_EPDIR;
        _USB->HC[i].CHAR = value;

        count = 0;
        do
        {
            if (++count > 1000U)
            {   
                status = 1;
                break;
            }
        }   while ((_USB->HC[i].CHAR & HCCHAR_CHENA) == HCCHAR_CHENA);
    }


    /* Clear any pending Host interrupts */
    _USB->HAINT = 0xFFFFFFFFU;
    _USB->GINTSTS = 0xFFFFFFFFU;
    usbEnableGlobalInterrupt();
    return status;
}


void usbActivateRemoteWakeup(void)
{
    if((_USB->DSTS & DSTS_SUSPSTS) == DSTS_SUSPSTS)
    {
        _USB->DCTL |= DCTL_RWUSIG;
    }
}


void usbDeactivateRemoteWakeup(void)
{
    _USB->DCTL &= ~(DCTL_RWUSIG);
}


int usbLLDriverInit(void)
{   
    int status = 0;
    usbDriver.Instance = _USB;
    usbDriver.Init.dev_endpoints = __USB_OTG_FS_MAX_DEVICE_ENDPTS;
    usbDriver.Init.speed = USBD_DEVSPEED_TYPE_fs;
    usbDriver.Init.Sof_enable = 0;
    usbDriver.Init.low_power_enable = 0;
    usbDriver.Init.lpm_enable = 0;

    /* we want to detect when outpost wakes up */
    usbDriver.Init.vbus_sensing_enable = 1; 
    usbDriver.Init.use_dedicated_ep1 = 0;

    if(0 != usbLLInitInternal())
    {
        status = 1;
    }

    usbDeviceDriverSetRxFifo(&usbDriver, 0x80);
    usbDeviceDriverSetTxFifo(&usbDriver, 0, 0x40);
    usbDeviceDriverSetTxFifo(&usbDriver, 1, 0x80);
    return status;
}









/**
 * @brief This function handles wakeup of the USB Peripheral in OTG mode
 * 
 */
void OTG_FS_WKUP_IRQHandler(void)
{

}




void usbDriver_setPhyInitFunc(void (*physicalLayerInitFunc)(void))
{
    usbDriver.PHYinitFunc = physicalLayerInitFunc;
}

void usbDriver_setAllocatorFunc(void *(*allocatorFunc)(size_t))
{
    LL_ASSERT(allocatorFunc != NULL);
    usbDriver.AllocFunc = allocatorFunc;
}


void usbDriver_setDeallocatorFunc(void (*deallocatorFunc)(void*))
{
    LL_ASSERT(deallocatorFunc != NULL);
    usbDriver.DeallocFunc = deallocatorFunc;
}


void usbDriver_setMemsetFunc(void *(*memsetFunc)(void*, int, size_t))
{
    LL_ASSERT(memsetFunc != NULL);
    usbDriver.MemsetFunc = memsetFunc;
}


void usbDriver_setDelayFunc(void (*delayFunc)(uint32_t))
{
    LL_ASSERT(NULL != delayFunc);
    usbDriver.DelayFunc = delayFunc;
}


void USBD_Delay(uint32_t ms)
{
    if(usbDriver.DeallocFunc != NULL)
    {
        usbDriver.DelayFunc(ms);
    }
}


void* USBD_malloc(size_t size)
{   
    void* ptr = NULL;
    if(usbDriver.AllocFunc != NULL)
    {
        ptr = usbDriver.AllocFunc(size);
    }
    return ptr;
}


void USBD_free(void *ptr)
{
    if(usbDriver.DeallocFunc != NULL)
    {
        usbDriver.DeallocFunc(ptr);
    }
}


void* USBD_memset(void *ptr, int value, size_t num)
{   
    void* ret = NULL;
    if(usbDriver.MemsetFunc != NULL)
    {
        ret = usbDriver.MemsetFunc(ptr, value, num);
    }
    return ret;
}


void USBD_PhyInit(void)
{
    if(usbDriver.PHYinitFunc != NULL)
    {
        usbDriver.PHYinitFunc();
    }
}


static int usbLLInitInternal(void)
{   
    int status = 0;
    unsigned i = 0;

    if(usbDriver.state == USB_DRIVER_STATE_reset)
    {   
        LL_ASSERT(NULL != usbDriver.PHYinitFunc);
        usbDriver.PHYinitFunc();
    }

    usbDriver.state = USB_DRIVER_STATE_busy;

    usbDisableGlobalInterrupt();

    if(0 != usbCoreInit())
    {
        return 1;
    }

    usbSetMode(USB_OTG_MODE_device);

    /* Init IN ENDPOINTS */
    for (i = 0U; i < usbDriver.Init.dev_endpoints; i++)
    {
        /* Init ep structure */
        usbDriver.IN_ep[i].is_in       = 1U;
        usbDriver.IN_ep[i].num         = i;
        usbDriver.IN_ep[i].tx_fifo_num = i;
        
        /* Control until ep is activated */
        usbDriver.IN_ep[i].type      = USB_EPTYPE_ctl;
        usbDriver.IN_ep[i].maxpacket = 0U;
        usbDriver.IN_ep[i].xfer_buff = 0U;
        usbDriver.IN_ep[i].xfer_len  = 0U;
    }

    /* Init OUT ENDPOINTS */
    for (i = 0U; i < usbDriver.Init.dev_endpoints; i++)
    {
        usbDriver.OUT_ep[i].is_in = 0U;
        usbDriver.OUT_ep[i].num = i;

        /* Control until ep is activated */
        usbDriver.OUT_ep[i].type = USB_EPTYPE_ctl;
        usbDriver.OUT_ep[i].maxpacket = 0U;
        usbDriver.OUT_ep[i].xfer_buff = 0U;
        usbDriver.OUT_ep[i].xfer_len  = 0U;
    }

    if(0 != usbDeviceModeInit())
    {
        usbDriver.state = USB_DRIVER_STATE_error;
        usbDriver.ErrorCode = 2;

        return usbDriver.ErrorCode;
    }

    usbDriver.USB_Address = 0;
    usbDriver.state = USB_DRIVER_STATE_ready;

    if(0 == status)
    {
        usbDeviceDisconnect();
    }

    return status;
}


static void usbDeviceDriverSetTxFifo(usbDriverHandle_t *driver, 
                                     uint8_t fifo, 
                                     uint16_t size)
{   
    uint8_t i = 0;
    uint32_t offset = driver->Instance->GRXFSIZ;
    if(0 == fifo)
    {
        usbDriver.Instance->DIEPTXF0_HNPTXFSIZ = 
            (((((uint32_t)size)) << DIEPTXF_INEPTXFD_POS) | offset);
    }
    else
    {   
        /* Initial offset from EP0. Add other EP TXFIFO offsets after */
        offset += 
            (usbDriver.Instance->DIEPTXF0_HNPTXFSIZ >> DIEPTXF_INEPTXFD_POS);

        for(i = 0; i < (fifo - 1); i++)
        {   
            offset += (usbDriver.Instance->DIEPTXF[i] >> DIEPTXF_INEPTXFD_POS);
        }

        usbDriver.Instance->DIEPTXF[fifo - 1] = 
            (((uint32_t)size << DIEPTXF_INEPTXFD_POS) | offset);
    }
}


static void usbDeviceDriverSetRxFifo(usbDriverHandle_t *driver, uint16_t size)
{
    driver->Instance->GRXFSIZ = (uint32_t)size;
}


int usbDriverStart(void)
{      
    __USB_DRIVER_ACQUIRE_LOCK(&usbDriver);
    usbDeviceConnect();
    __COMPILER_BARRIER();
    usbEnableGlobalInterrupt();
    __USB_DRIVER_RELEASE_LOCK(&usbDriver);
    return 0;
}


int usbDriverStop(void)
{   
    __USB_DRIVER_ACQUIRE_LOCK(&usbDriver);
    usbDisableGlobalInterrupt();
    __COMPILER_BARRIER();
    (void)usbStopDevice();
    usbDeviceDisconnect();
    __USB_DRIVER_RELEASE_LOCK(&usbDriver);
    return 0;
}


static void usbDriverOUTEndPointSetupPacket(uint32_t epnum)
{
    uint32_t gSNPSiD = *(volatile uint32_t *)(&usbDriver.Instance->CID + 0x1U);
    uint32_t DoepintReg = usbDriver.Instance->DOEP[epnum].INT;

    if ((gSNPSiD == USB_OTG_CORE_ID_310A) &&
            ((DoepintReg & DOEPINT_STPKTRX) == DOEPINT_STPKTRX))
    {   
        usbDriver.Instance->DOEP[epnum].INT = DOEPINT_STPKTRX;
    }

    usbDeviceDriver_SetupStageCallback(&usbDriver);
}




static void usbDriverOutXferCpltCallBack(uint32_t epnum)
{
    uint32_t gSNPSiD = *(volatile uint32_t *)(&_USB->CID + 0x1U);
    uint32_t DoepintReg = _USB->DOEP[epnum].INT;

    if (gSNPSiD == USB_OTG_CORE_ID_310A)
    {
        /* This is a setup packet */
        if ((DoepintReg & DOEPINT_STPKTRX) == DOEPINT_STPKTRX)
        {   
                _USB->DOEP[epnum].INT = DOEPINT_STPKTRX;
        }
        else
        {
            if ((DoepintReg & DOEPINT_OTEPSPR) == DOEPINT_OTEPSPR)
            {   
                /* Clear the interrupt */
                usbDriver.Instance->DOEP[epnum].INT = DOEPINT_OTEPSPR;
            }

            usbDeviceDriver_DataOutStageCallback(&usbDriver, (uint8_t)epnum);
        }
    }
    else
    {
        usbDeviceDriver_DataOutStageCallback(&usbDriver, (uint8_t)epnum);
    }
}



void usbGatePhyClock(void)
{   
    usbDisableGlobalInterrupt();
    __COMPILER_BARRIER();
    volatile uint32_t tmp = _USB->PCGCTL;
    tmp |= PCGCCTL_STOPCLK;
    _USB->PCGCTL = tmp;
    __COMPILER_BARRIER();
    usbEnableGlobalInterrupt();
}


void usbUngatePhyClock(void)
{   
    usbDisableGlobalInterrupt();
    __COMPILER_BARRIER();
    volatile uint32_t tmp = _USB->PCGCTL;
    tmp &= ~PCGCCTL_STOPCLK;
    _USB->PCGCTL = tmp;
    __COMPILER_BARRIER();
    usbEnableGlobalInterrupt();
}






static int usbDriverWriteEmptyTxFifo(uint32_t epnum)
{   
    int status = 0;
    usbEndPoint_t *ep;
    uint32_t len;
    uint32_t words;
    uint32_t fifoemptymsk;

    ep = &usbDriver.IN_ep[epnum];
    if(ep->xfer_count > ep->xfer_len)
    {
        status = 1;
    }
    else
    {
        len = ep->xfer_len - ep->xfer_count;

        if(len > ep->maxpacket)
        {
            len = ep->maxpacket;
        }

        words = (len + 3U) / 4U;

        while ((
        (usbDriver.Instance->DIEP[epnum].TXFSTS & DTXFSTS_INEPTFSAV) >= words) 
        && (ep->xfer_count < ep->xfer_len) 
        && (ep->xfer_len != 0U))
        {
            /* Write the FIFO */
            len = ep->xfer_len - ep->xfer_count;

            if (len > ep->maxpacket)
            {
                len = ep->maxpacket;
            }
            words = (len + 3U) / 4U;
            
            usbWritePkt(ep->xfer_buff, epnum, len);
            ep->xfer_buff += len;
            ep->xfer_count += len;
        }

        if (ep->xfer_len <= ep->xfer_count)
        {
            fifoemptymsk = (uint32_t)(0x1UL << (epnum & __EP_ADDR_MSK));
            usbDriver.Instance->DIEPEMPMSK &= ~fifoemptymsk;
        }
    }
    return status;
}
























/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
#if USE_VENDOR_USB_DRIVER == 1
    HAL_PCD_IRQHandler(PCD_HandleTypeDef *hpcd);
#else
    /* Endpoints are only allowed to preEmpt when mutex is available */
    /* (since They'll have to acquire it to gain access to a FIFO )  */

    uint32_t i;
    uint32_t ep_intr;
    uint32_t epint;
    uint32_t epnum;
    uint32_t fifoemptymsk;
    uint32_t tmp;
    usbEndPoint_t *ep = NULL;

    USB_OTG_MODE_t mode = (USB_OTG_MODE_t)usbGetMode();
    if(USB_OTG_MODE_device == mode)
    {   
        
        if(0 == usbReadInterrupts())
        {
            return;
        }

        /* Mode mismanagement interrupt */
        if(usbReadInterrupts() & GINTSTS_MMIS) 
        {   
            /* Ack the exception and exit. Handling past here is UB */
            usbClearInterrupts(GINTSTS_MMIS);
            return;
        }

        /* if OUT endpoint generated the interrupt */
        if((usbReadInterrupts() & GINTSTS_OEPINT) == GINTSTS_OEPINT)
        {
            epnum = 0;
            ep_intr = usbDeviceReadOutEndPointInterrupt(epnum);

            while(ep_intr)
            {
                if(ep_intr & 0x1U)
                {
                    epint = usbDeviceReadOutEndPointInterrupt(epnum);

                    if ((epint & DOEPINT_XFRC) == DOEPINT_XFRC)
                    {   
                        _USB->DOEP[epnum].INT = DOEPINT_XFRC;
                        usbDriverOutXferCpltCallBack(epnum);
                    }

                    if ((epint & DOEPINT_STUP) == DOEPINT_STUP)
                    {
                        /* Class B setup phase done for prev decoded setup */
                        usbDriverOUTEndPointSetupPacket(epnum);
                        _USB->DOEP[epnum].INT = DOEPINT_STUP;
                    }

                    if ((epint & DOEPINT_OTEPDIS) == DOEPINT_OTEPDIS)
                    {

                        _USB->DOEP[epnum].INT = DOEPINT_OTEPDIS;
                    }

                    /* Clear Status Phase Received interrupt */
                    if ((epint & DOEPINT_OTEPSPR) == DOEPINT_OTEPSPR)
                    {
                        _USB->DOEP[epnum].INT = DOEPINT_OTEPSPR;
                    }

                    /* Clear OUT NAK interrupt */
                    if ((epint & DOEPINT_NAK) == DOEPINT_NAK)
                    {
                        _USB->DOEP[epnum].INT = DOEPINT_NAK;

                    }
                }
                epnum++;
                ep_intr >>= 1;
            }
        }

        /* if IN endpoint generated the interrupt */
        if((usbReadInterrupts() & GINTSTS_IEPINT) == GINTSTS_IEPINT)
        {   
            epnum = 0;
            ep_intr = usbDeviceReadOutEndPointInterrupt(epnum);
            while(ep_intr)
            {   
                if(ep_intr & 1U)
                {
                    epint = usbDeviceReadOutEndPointInterrupt(epnum);

                    if ((epint & DIEPINT_XFRC) == DIEPINT_XFRC)
                    {   
                        fifoemptymsk = 
                            (uint32_t)(0x1UL << (epnum & __EP_ADDR_MSK));

                        _USB->DIEPEMPMSK &= ~fifoemptymsk;

                        usbDeviceDriver_DataInStageCallback(&usbDriver,
                                                            (uint8_t)epnum);
                        _USB->DIEP[epnum].INT = DIEPINT_XFRC;
                    }

                    if ((epint & DIEPINT_TOC) == DIEPINT_TOC)
                    {   
                        _USB->DIEP[epnum].INT = DIEPINT_TOC;
                    }

                    if ((epint & DIEPINT_ITTXFE) == DIEPINT_ITTXFE)
                    {
                        _USB->DIEP[epnum].INT = DIEPINT_ITTXFE;

                    }

                    if ((epint & DIEPINT_INEPNE) == DIEPINT_INEPNE)
                    {
                        _USB->DIEP[epnum].INT = DIEPINT_INEPNE;
                        
                    }

                    if ((epint & DIEPINT_EPDISD) == DIEPINT_EPDISD)
                    {
                        _USB->DIEP[epnum].INT = DIEPINT_EPDISD;
                        
                    }
                    
                    if ((epint & DIEPINT_TXFE) == DIEPINT_TXFE)
                    {   
                        usbDriverWriteEmptyTxFifo(epnum);
                    }
                }
                epnum++;
                ep_intr >>= 1;
            }
        }

        /* WAKEUP INTERRUPT */
        if((usbReadInterrupts() & GINTSTS_WKUINT) == GINTSTS_WKUINT)
        {   
            
            _USB->DCTL &= ~DCTL_RWUSIG;

            if (usbDriver.LPM_State == USB_DRIVER_LPM_l1)
            {
                usbDriver.LPM_State = USB_DRIVER_LPM_l0;

                /** @todo IMPLEMENT WEAK FUNCTION 
                 * userUSBdeviceDriver_lowPowerEntryCallback();
                 */
                /* This lets user implent cb for entry to low pwoer mode */
            }
            else
            {
                usbDeviceDriver_ResumeCallback(&usbDriver);
            }

            _USB->GINTSTS &= GINTSTS_WKUINT;
        }


        /* SUSPEND INTERRUPT */
        if((usbReadInterrupts() & GINTSTS_USBSUSP) == GINTSTS_USBSUSP)
        {
            if((_USB->DSTS & DSTS_SUSPSTS) == DSTS_SUSPSTS)
            {   

                /**
                 * @todo IMPLEMENT WEAK FUNCTION 
                 * userUSBdeviceDriver_SuspendCallback();
                 */
            }
            _USB->GINTSTS &= GINTSTS_USBSUSP;
        }
        

        /* Handle Reset Interrupt */
        if((usbReadInterrupts() & GINTSTS_USBRST) == GINTSTS_USBRST)
        {
            _USB->DCTL &= ~DCTL_RWUSIG;
            usbFlushTxFifo(0x10); /* Flush all Fifos */

            for(i = 0; i < usbDriver.Init.dev_endpoints; i++)
            {
                _USB->DIEP[i].INT = 0xFB7FU;
                _USB->DIEP[i].CTL &= ~DIEPCTL_STALL;
                _USB->DOEP[i].INT = 0xFB7FU;
                _USB->DOEP[i].CTL &= ~DOEPCTL_STALL;
            }
            _USB->DAINTMSK |= 0x10001U;

            if (usbDriver.Init.use_dedicated_ep1 != 0U)
            {   

                _USB->DOUTEP1MSK |= DOEPMSK_STUPM |
                                    DOEPMSK_XFRCM |
                                    DOEPMSK_EPDM;

                _USB->DINEP1MSK |= DIEPMSK_TOM   |
                                   DIEPMSK_XFRCM |
                                   DIEPMSK_EPDM;
            }
            else
            {
                _USB->DOEPMSK |= DOEPMSK_STUPM    |
                                 DOEPMSK_XFRCM    |
                                 DOEPMSK_EPDM     |
                                 DOEPMSK_OTEPSPRM |
                                 DOEPMSK_NAKM;

                _USB->DIEPMSK |= DIEPMSK_TOM   |
                                 DIEPMSK_XFRCM |
                                 DIEPMSK_EPDM;
            }

            /* Set Default Address to 0 */
            _USB->DCFG &= ~DCFG_DAD;

            /* setup EP0 to receive SETUP packets */
            usbOEP0Start((uint8_t*)usbDriver.Setup);


            /* Clear reset interrupt */
            _USB->GINTSTS &= GINTSTS_USBRST;
        }


        /* Enumeration Done interrupt */
        if((usbReadInterrupts() & GINTSTS_ENUMDNE) == GINTSTS_ENUMDNE)
        {
            usbActivateSetup();

            /* Get the speed at which peripheral negotiated with host */
            usbDriver.Init.speed = (uint32_t)usbGetDevSpeed();

/* Our target mcus can only suppport FS mode */
#if defined(STM32F411RE) || defined(STM32F411VE)
            LL_ASSERT(usbDriver.Init.speed == USBD_DEVSPEED_TYPE_fs);
#endif 
            /* 
             * Set the turnaround time based on 
             * the RCC config and enumerated speed
             */
            usbSetTurnaroundTime((USBD_DEVSPEED_TYPE_t)usbDriver.Init.speed);

            usbDeviceDriver_ResetCallback(&usbDriver);

            _USB->GINTSTS &= GINTSTS_ENUMDNE;
        }

        /* At least 1 packet in RX Fifo */
        if((usbReadInterrupts() & GINTSTS_RXFLVL) == GINTSTS_RXFLVL)
        {   
            /* Mask interrupt */
            _USB->GINTMSK &= ~GINTSTS_RXFLVL;

            tmp = _USB->GRXSTSP;

            ep = &usbDriver.OUT_ep[tmp & GRXSTSP_EPNUM];

            if(GINTSTS_RXFLVL_data_update == 
            (( tmp & GRXSTSP_PKTSTS) >> GRXSTSP_PKTSTS_POS))
            {   
                if((tmp & GRXSTSP_BCNT) != 0)
                {   
                    usbReadPkt(ep->xfer_buff, 
                        (uint16_t)((tmp & GRXSTSP_BCNT) >> GRXSTSP_BCNT_POS));

                    ep->xfer_buff += ((tmp & GRXSTSP_BCNT) >> GRXSTSP_BCNT_POS);
                    ep->xfer_count +=((tmp & GRXSTSP_BCNT) >> GRXSTSP_BCNT_POS);
                    
                }
            }
            else if(GINTSTS_RXFLVL_stup_update ==
            ((tmp & GRXSTSP_PKTSTS) >> GRXSTSP_PKTSTS_POS))
            {
                usbReadPkt((uint8_t*)usbDriver.Setup, 8U);
                ep->xfer_count +=((tmp & GRXSTSP_BCNT) >> GRXSTSP_BCNT_POS);
            }
            else if(GINTSTS_RXFLVL_gout_nak ==
            ((tmp & GRXSTSP_PKTSTS) >> GRXSTSP_PKTSTS_POS))
            {
                /** @todo IMPLEMENT */
            }            
            else if(GINTSTS_RXFLVL_xfer_cplt ==
            ((tmp & GRXSTSP_PKTSTS) >> GRXSTSP_PKTSTS_POS))
            {
                /** @todo IMPLEMENT */

            }
            else if(GINTSTS_RXFLVL_stup_cplt ==
            ((tmp & GRXSTSP_PKTSTS) >> GRXSTSP_PKTSTS_POS))
            {
                /** @todo IMPLEMENT */

            }
            else
            {
                
                /* ... */
            }

            /* Unmask the interrupt */
            _USB->GINTMSK |= GINTSTS_RXFLVL;
        }

        /* Start of frame interrupt */
        if((usbReadInterrupts() & GINTSTS_SOF) == GINTSTS_SOF)
        {   
            if(usbDriver.Init.Sof_enable)
            {
                usbDeviceDriver_SOFCallback(&usbDriver);
            }
            _USB->GINTSTS &= GINTSTS_SOF;
        }

        /* Handle Incomplete ISO IN Interrupt */
        if((usbReadInterrupts() & GINTSTS_IISOIXFR) == GINTSTS_IISOIXFR)
        {   
            epnum = 0;
            usbDeviceDriver_ISOINIncompleteCallback(&usbDriver, (uint8_t)epnum);
            _USB->GINTSTS &= GINTSTS_IISOIXFR;
        }
        
        /* Handle Incomplete ISO OUT Interrupt */
        if((usbReadInterrupts() & GINTSTS_PXFR_INCOMPISOOUT) ==
        (GINTSTS_PXFR_INCOMPISOOUT))
        {
            epnum = 0;
            usbDeviceDriver_ISOOUTIncompleteCallback(&usbDriver,(uint8_t)epnum);
            _USB->GINTSTS &= GINTSTS_PXFR_INCOMPISOOUT;
        }
        
        /* Handle Connection event Interrupt */
        if((usbReadInterrupts() & GINTSTS_SRQINT) == GINTSTS_SRQINT)
        {
            usbDeviceDriver_ConnectCallback(&usbDriver);
            _USB->GINTSTS &= GINTSTS_SRQINT;
        }

        /* OTG protocol change / disconnect evt */
        if((usbReadInterrupts() & GINTSTS_OTGINT) == GINTSTS_OTGINT)
        {
            tmp = _USB->GOTGINT;

            if((tmp & GOTGINT_SEDET) == GOTGINT_SEDET)
            {
                usbDeviceDriver_DisconnectCallback(&usbDriver);
            }
            _USB->GOTGINT |= tmp;
        }
    }
    else if(USB_OTG_MODE_host == mode)
    {
        /** @todo IMPLEMENT */
    }
    else if(USB_OTG_MODE_drd == mode)
    {
        /** @todo IMPLEMENT */
    }
    else
    {
        /* if we get here it's very bad */
        if(usbReadInterrupts() & GINTSTS_MMIS) 
        {   
            usbClearInterrupts(GINTSTS_MMIS);
        }
        else
        {
            /* 
             *  If we get here its even worse. Something
             *  may be fundamentally wrong with hardware
             *  or clocking. mode-mismanage exception
             *  did not fire. 
             */
            LL_ASSERT(0);   /* In debug build, hang forever */
        }
    }
#endif 
}




int usbDeviceDriver_CloseEndpoint(usbDriverHandle_t *driver, uint8_t ep_addr)
{
    usbEndPoint_t *ep;

    if ((ep_addr & 0x80U) == 0x80U)
    {
        ep = &driver->IN_ep[ep_addr & __EP_ADDR_MSK];
        ep->is_in = 1U;
    }
    else
    {
        ep = &driver->OUT_ep[ep_addr & __EP_ADDR_MSK];
        ep->is_in = 0U;
    }
    ep->num = ep_addr & __EP_ADDR_MSK;

    __USB_DRIVER_ACQUIRE_LOCK(driver);
    usbDeactivateEndpoint(ep);
    __USB_DRIVER_RELEASE_LOCK(driver);
    return 0;
}


int usbDeviceDriver_FlushEndpoint(usbDriverHandle_t *driver, uint8_t ep_addr)
{   
    int status = 0;
    __USB_DRIVER_ACQUIRE_LOCK(driver);
    if ((ep_addr & 0x80U) == 0x80U)
    {   
        uint32_t epMsk = (uint32_t)(ep_addr & __EP_ADDR_MSK);
        status = usbFlushTxFifo(epMsk);
    }
    else
    {   
        status = usbFlushRxFifo();
    }
    __USB_DRIVER_RELEASE_LOCK(driver);
    return status;
}


int usbDeviceDriver_StallEndpoint(usbDriverHandle_t *driver, uint8_t ep_addr)
{   
    int status = 0;
    usbEndPoint_t *ep;
    
    if((uint32_t)(ep_addr & __EP_ADDR_MSK) > driver->Init.dev_endpoints)
    {   
        /* Attempting to stall an unconfigured/enabled EP */
        status = 1;
    }
    else
    {   
        /* dETERMINE EP TYPE */
        if ((0x80U & ep_addr) == 0x80U)
        {
            ep = &driver->IN_ep[(uint32_t)(ep_addr & __EP_ADDR_MSK)];
            ep->is_in = 1U;
        }
        else
        {
            ep = &driver->OUT_ep[(uint32_t)ep_addr];
            ep->is_in = 0U;
        }

        ep->is_stall = 1U;
        ep->num = ep_addr & __EP_ADDR_MSK;

        __USB_DRIVER_ACQUIRE_LOCK(driver);
        if(0 != usbSetEndPointStall(ep))
        {
            status = 1;     
        }
        else if((ep_addr & __EP_ADDR_MSK) == 0U)
        {
            if(0 != usbOEP0Start((uint8_t*)driver->Setup))
            {
                status = 2;  
            }
        }
        __USB_DRIVER_RELEASE_LOCK(driver);
    }
    return status;
}


int usbDeviceDriver_ClrStalledEndpoint(usbDriverHandle_t *driver,
                                       uint8_t ep_addr)
{
    int status = 0;
    usbEndPoint_t *ep;
    
    if((uint32_t)(ep_addr & __EP_ADDR_MSK) > driver->Init.dev_endpoints)
    {   
        /* Attempting to stall an unconfigured/enabled EP */
        status = 1;
    }
    else
    {   
        /* DETERMINE EP TYPE */
        if ((0x80U & ep_addr) == 0x80U)
        {
            ep = &driver->IN_ep[(uint32_t)(ep_addr & __EP_ADDR_MSK)];
            ep->is_in = 1U;
        }
        else
        {
            ep = &driver->OUT_ep[(uint32_t)ep_addr];
            ep->is_in = 0U;
        }

        ep->is_stall = 0U;
        ep->num = ep_addr & __EP_ADDR_MSK;

        __USB_DRIVER_ACQUIRE_LOCK(driver);
        if(0 != usbClearEndPointStall(ep))
        {
            status = 1;     
        }
        __USB_DRIVER_RELEASE_LOCK(driver);
    }
    return status;
}



int usbDeviceDriver_DeviceConnect(usbDriverHandle_t* driver)
{   
    __USB_DRIVER_ACQUIRE_LOCK(driver);
    usbDeviceConnect();
    __USB_DRIVER_RELEASE_LOCK(driver);
    return 0;
}


int usbDeviceDriver_DeviceDisconnect(usbDriverHandle_t* driver)
{
    __USB_DRIVER_ACQUIRE_LOCK(driver);
    usbDeviceDisconnect();
    __USB_DRIVER_RELEASE_LOCK(driver);
    return 0;
}



int usbDeviceDriver_setDeviceAddress(usbDriverHandle_t* driver, uint8_t addr)
{
    __USB_DRIVER_ACQUIRE_LOCK(driver);
    usbSetDeviceAddress(addr);
    __USB_DRIVER_RELEASE_LOCK(driver);
    return 0;
}



int usbDeviceDriver_OpenEndpoint(usbDriverHandle_t* driver, 
                                 uint8_t ep_addr, 
                                 uint16_t ep_mps, 
                                 uint8_t ep_type)
{
    int status = 0;
    usbEndPoint_t *ep;
    if ((ep_addr & 0x80U) == 0x80U)
    {
        ep = &driver->IN_ep[ep_addr & __EP_ADDR_MSK];
        ep->is_in = 1U;
    }
    else
    {
        ep = &driver->OUT_ep[ep_addr & __EP_ADDR_MSK];
        ep->is_in = 0U;
    }

    ep->num = ep_addr & __EP_ADDR_MSK;
    ep->maxpacket = ep_mps;
    ep->type = ep_type;

    if (ep->is_in != 0U)
    {
        /* Assign a Tx FIFO */
        ep->tx_fifo_num = ep->num;
    }

    /* Set initial data PID. */
    if (ep_type == USB_EPTYPE_bulk)
    {
        ep->data_pid_start = 0U;
    }

   __USB_DRIVER_ACQUIRE_LOCK(driver);
    if(0 != usbActivateEndpoint(ep))
    {
        status = 2;
    }
    /* 
     * WARNING: There is an edge case wherein the activation
     * AND lock release fail here. In this case, the returned
     * status will be 1, not 2 since lock return occurs before
     * status return. Caller should check the driver state 
     * field if !0 return is called from driver::openEP
     */
   __USB_DRIVER_RELEASE_LOCK(driver);
    return status;
}



void usbDeviceDriver_EP_Transmit(usbDriverHandle_t* driver, 
                                     uint8_t ep_addr, 
                                     uint8_t *pBuf, 
                                     uint32_t len)
{
    usbEndPoint_t *ep = &driver->IN_ep[ep_addr & __EP_ADDR_MSK];
    ep->xfer_buff = pBuf;
    ep->xfer_len = len;
    ep->xfer_count = 0;
    ep->is_in = 1;
    ep->num = ep_addr & __EP_ADDR_MSK;

    if ((ep_addr & __EP_ADDR_MSK) == 0U)
    {   
        usbEndPoint0StartXfer(ep);

    }
    else
    {   
        usbStartEndPointXfer(ep);

    }

}


void usbDeviceDriver_EP_Receive(usbDriverHandle_t *driver, 
                                uint8_t ep_addr, 
                                uint8_t *pBuf, 
                                uint32_t len)
{
    usbEndPoint_t *ep = &driver->OUT_ep[ep_addr & __EP_ADDR_MSK];
    ep->xfer_buff = pBuf;
    ep->xfer_len = len;
    ep->xfer_count = 0;
    ep->num = ep_addr & __EP_ADDR_MSK;

    if((ep_addr & __EP_ADDR_MSK) == 0)
    {
        usbEndPoint0StartXfer(ep);
    }
    else
    {
        usbStartEndPointXfer(ep);
    }
}


uint32_t usbDeviceDriver_GetEPRxCnt(usbDriverHandle_t* driver, uint8_t ep_addr)
{
    return driver->OUT_ep[ep_addr & __EP_ADDR_MSK].xfer_count;
}

#endif
