#ifndef RIMOT_MCU_USB_OTG_CONFIG
#define RIMOT_MCU_USB_OTG_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage*/

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

/* 
 * TODO: DEFINE RELATIVE TO AHB2 (WHICH IS WHERE MCU ADDRESSES FROM)
 * [APRIL 2, 2020]
 */ 
#define OSG_OTG_PERIPH_BASE (0x50000000UL)

/*
 * These are here so I have values in the comments
 * that I can check against when verifying memory
 * alignment and overlay of the peripheral structure.
 * 
 * The structure is quite large and the likelihood
 * that I made a mistake is real. 
 * 
 * PERIPHERAL MEMORY MAP ON PAGE 694 OF REFERENCE MANUAL
 * 
 * USB_OTG_GLOBAL_BASE        (0x000UL)
 * USB_OTG_DEVICE_BASE        (0x800UL)
 * USB_OTG_IN_ENDPOINT_BASE   (0x900UL)
 * USB_OTG_OUT_ENDPOINT_BASE  (0xB00UL)
 * USB_OTG_EP_REG_SIZE        (0x20UL)
 * USB_OTG_HOST_BASE          (0x400UL)
 * USB_OTG_HOST_PORT_BASE     (0x440UL)
 * USB_OTG_HOST_CHANNEL_BASE  (0x500UL)
 * USB_OTG_HOST_CHANNEL_SIZE  (0x20UL)
 * USB_OTG_PCGCCTL_BASE       (0xE00UL)
 * USB_OTG_FIFO_BASE          (0x1000UL)
 *
 */

#define USB_OTG_FIFO_SIZE 0x1000UL

/*************************************************/
/* SEE REFERENCE MANUAL PAGE 649 FOR MORE DETAIL */
/*************************************************/ 
#define USB_OTG_HW_DEBUG_MSG_FIFO_SIZE  0x20000 /* 128Kbyte */



struct USB_OTG_REGISTERS_global
{
    hw_reg CTL;    /* Control and status register */
    hw_reg INT;    /* Interrupt register */
    hw_reg AHBCFG; /* AHB Configuration register */
    hw_reg RSTCTL; /* Reset Register */
    hw_reg INTSTS; /* Global core interrupt register */
    hw_reg INTMSK; /* Global interrupt mask register */
    hw_reg RXSTSR; /* Receive status status read register */
    hw_reg RXSTSP; /* OTG status status pop register */
    hw_reg RXFSIZ; /* Receive FIFO size register */
    union
    {
        /* Host non-periodic transmit FIFO size register */
        hw_reg HNPTXFSIZ; /* REF MANUAL PAGE 695. USE THIS IS HOST MODE */

        /* 
         * Endpoint 0 
         * Transmit 
         * Fifo Size 
         * Register.
         * 
         * REF MANUAL 
         * PAGE 695.
         * 
         * USE THIS IN
         * DEVICE MODE
         */
        hw_reg DIEPTXF0;    
    }      TXFIFOSZ;    /* Non-periodic Transmit fifo size register         */
    hw_reg HNPTXSTS;    /* Non-period Transmit FIFO queue / status register */
    pad32 Reserved1; /* Reserved                                         */
    pad32 Reserved2; /* Reserved                                         */
    hw_reg GCCFG;       /* General core configuration register              */
    hw_reg CID;         /* Core ID Register                                 */
    sw_byte Res[48];   /* Reserved                                         */
    hw_reg HPTXFSIZ;    /* Host periodic transmit fifo size register        */
    union               /* Device IN endpoint x tx fifo size registers      */
    {
        hw_reg _array[3];
        struct
        {
            hw_reg DIEPTXF1; 
            hw_reg DIEPTXF2; 
            hw_reg DIEPTXF3; 
        } _struct;
    }   DIEPTXFx;   
};


struct USB_OTG_HOST_CHANNEL
{
    hw_reg CHAR;      /* Host channel characteristics register */
    hw_reg SPLIT;     /* Host channel split control register   */
    hw_reg INT;       /* Host channel interrupt register       */
    hw_reg INTMSK;    /* Host channel interrupt mask register  */
    hw_reg TSIZ;      /* Host channel transfer size register   */
    hw_reg DMA;       /* Host channel DMA address register     */
    pad32 RESERVED1; /* Reserved                              */
    pad32 RESERVED2; /* Reserved                              */
};

struct USB_OTG_REGISTERS_host
{
    hw_reg CFG;         /* Host configuration register                     */
    hw_reg FIR;         /* Host frame interval register                    */
    hw_reg FNUM;        /* Host frame number / frame remaining register    */
    hw_reg PTXSTS;      /* Host periodic tx fifo queue / status register   */
    hw_reg AINT;        /* Host all channels interrupt register            */
    hw_reg AINTMSK;     /* Host all channels interrupt mask register       */
    pad32 RESERVED1;  /* Reserved                                        */
    pad32 RESERVED2;  /* Reserved                                        */
    pad32 RESERVED3;  /* Reserved                                        */
    pad32 RESERVED4;  /* Reserved                                        */
    pad32 RESERVED5;  /* Reserved                                        */
    pad32 RESERVED6;  /* Reserved                                        */
    pad32 RESERVED7;  /* Reserved                                        */
    pad32 RESERVED8;  /* Reserved                                        */
    pad32 RESERVED9;  /* Reserved                                        */
    pad32 RESERVED10; /* Reserved                                        */
    hw_reg PRT;          /* Host port control and status register           */
    struct USB_OTG_HOST_CHANNEL HC[8]; /* Channels    */
};


struct USB_OTG_DEV_EP
{
    hw_reg CTL;         /* Device IN endpoint control register              */
    pad32 Reserved1; /* Reserved                                         */  
    hw_reg INT;         /* Device IN endpoint interrupt register            */
    pad32 Reserved2; /* Reserved                                         */  
    hw_reg SIZ;         /* Device IN endpoint size register                 */
    hw_reg DMA;         /* Device IN endpoint DMA address register          */
    hw_reg TXFSTS;      /* Device IN endpoint transmit fifo status register */
    pad32 Reserved3; /* Reserved                                         */
};

struct USB_OTG_REGISTERS_device
{
    hw_reg CFG;         /* Device configuration register                    */
    hw_reg CTL;         /* Device control register                          */
    hw_reg STS;         /* Device status register                           */
    pad32 RESERVED1; /* Reserved                                         */
    hw_reg IEPMSK;      /* Device IN endpoint common interrupt mask reg     */
    hw_reg OEPMSK;      /* Device OUT endpoint common interrupt mask reg    */
    hw_reg AINT;        /* Device all endpoints interrupt register          */
    hw_reg AINTMSK;     /* Device all endpoints interrupt mask register     */
    pad32 RESERVED2; /* Reserved                                         */
    pad32 RESERVED3; /* Reserved                                         */
    hw_reg VBUSDIS;     /* Device VBUS discharge time register              */
    hw_reg VBUSPULSE;   /* Device VBUS pulsing time register                */
    pad32 RESERVED4; /* Reserved                                         */
    hw_reg IEPEMPMSK;   /* Device IN endpoint FIFO empty interrupt mask reg */
    pad32 RES[0xCB]; /* Reserved. 0x8F8 - 0x834                          */

    /* Device IN endpoints */
    struct              
    {
        hw_reg CTL;         /* Device IN endpoint control register          */
        pad32 Reserved1; /* Reserved                                     */  
        hw_reg INT;         /* Device IN endpoint interrupt register        */
        pad32 Reserved2; /* Reserved                                     */  
        hw_reg SIZ;         /* Device IN endpoint size register             */
        hw_reg DMA;         /* Device IN endpoint DMA address register      */
        hw_reg TXFSTS;      /* Device IN endpoint transmit fifo status reg  */
        pad32 Reserved3; /* Reserved                                     */
    }   EPIN[4];  

    /* Device OUT endpoints */
    struct 
    {
        hw_reg CTL;         /* Device IN endpoint control register          */
        pad32 Reserved1; /* Reserved                                     */  
        hw_reg INT;         /* Device IN endpoint interrupt register        */
        pad32 Reserved2; /* Reserved                                     */  
        hw_reg SIZ;         /* Device IN endpoint size register             */
        hw_reg DMA;         /* Device IN endpoint DMA address register      */
        hw_reg TXFSTS;      /* Device IN endpoint transmit fifo status reg  */
        pad32 Reserved3; /* Reserved                                     */
    }   EPOUT[4];  
};


struct USB_OTG_DFIFO_stack
{
    union 
    {
        sw_byte bytes[USB_OTG_FIFO_SIZE];
        sw_reg words[USB_OTG_FIFO_SIZE/MCU_BYTES_PER_WORD];
    }   fifo[8];
};

struct USB_OTG_REGISTERS_clock
{
    hw_reg CTL; /* pOWER AND CLOCK GATING CONTROL REGISTER */
    sw_byte RESERVED1[506];
};


struct USB_OTG
{
    struct USB_OTG_REGISTERS_global global; /* GLOBAL REGISTERS     */
    struct USB_OTG_REGISTERS_host   host;   /* HOST REGISTERS       */
    struct USB_OTG_REGISTERS_device device; /* DEVICE REGISTERS     */
    struct USB_OTG_DFIFO_stack      fifo;   /* FIFO STACK            */
    struct USB_OTG_REGISTERS_clock  clock;  /* CLOCK CFG REGISTERS  */
};


#define OSG_OTG ((struct USB_OTG*) OSG_OTG_PERIPH_BASE)


#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */