#ifndef RIMOT_MCU_USB_OTG_CONFIG
#define RIMOT_MCU_USB_OTG_CONFIG
#ifdef __cplusplus
extern "C" {
#endif /* C linkage*/

#include "rimot_peripheral_regs.h"

/*************************************************/
/* SEE REFERENCE MANUAL PAGE 649 FOR MORE DETAIL */
/*************************************************/ 
#define USB_OTG_FIFO_SIZE               0x1000  /* 4Kbyte   */
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
    mcu_word Reserved1; /* Reserved                                         */
    mcu_word Reserved2; /* Reserved                                         */
    hw_reg GCCFG;       /* General core configuration register              */
    hw_reg CID;         /* Core ID Register                                 */
    mcu_byte Res[48];   /* Reserved                                         */
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
    mcu_word RESERVED1; /* Reserved                              */
    mcu_word RESERVED2; /* Reserved                              */
};

struct USB_OTG_REGISTERS_host
{
    hw_reg CFG;         /* Host configuration register                     */
    hw_reg FIR;         /* Host frame interval register                    */
    hw_reg FNUM;        /* Host frame number / frame remaining register    */
    hw_reg PTXSTS;      /* Host periodic tx fifo queue / status register   */
    hw_reg AINT;        /* Host all channels interrupt register            */
    hw_reg AINTMSK;     /* Host all channels interrupt mask register       */
    mcu_word RESERVED1;  /* Reserved                                        */
    mcu_word RESERVED2;  /* Reserved                                        */
    mcu_word RESERVED3;  /* Reserved                                        */
    mcu_word RESERVED4;  /* Reserved                                        */
    mcu_word RESERVED5;  /* Reserved                                        */
    mcu_word RESERVED6;  /* Reserved                                        */
    mcu_word RESERVED7;  /* Reserved                                        */
    mcu_word RESERVED8;  /* Reserved                                        */
    mcu_word RESERVED9;  /* Reserved                                        */
    mcu_word RESERVED10; /* Reserved                                        */
    hw_reg PRT;          /* Host port control and status register           */
    struct USB_OTG_HOST_CHANNEL HC[8]; /* Channels    */
};


struct USB_OTG_DEV_EP
{
    hw_reg CTL;         /* Device IN endpoint control register              */
    mcu_word Reserved1; /* Reserved                                         */  
    hw_reg INT;         /* Device IN endpoint interrupt register            */
    mcu_word Reserved2; /* Reserved                                         */  
    hw_reg SIZ;         /* Device IN endpoint size register                 */
    hw_reg DMA;         /* Device IN endpoint DMA address register          */
    hw_reg TXFSTS;      /* Device IN endpoint transmit fifo status register */
    mcu_word Reserved3; /* Reserved                                         */
};

struct USB_OTG_REGISTERS_device
{
    hw_reg CFG;         /* Device configuration register                    */
    hw_reg CTL;         /* Device control register                          */
    hw_reg STS;         /* Device status register                           */
    mcu_word RESERVED1; /* Reserved                                         */
    hw_reg IEPMSK;      /* Device IN endpoint common interrupt mask reg     */
    hw_reg OEPMSK;      /* Device OUT endpoint common interrupt mask reg    */
    hw_reg AINT;        /* Device all endpoints interrupt register          */
    hw_reg AINTMSK;     /* Device all endpoints interrupt mask register     */
    mcu_word RESERVED2; /* Reserved                                         */
    mcu_word RESERVED3; /* Reserved                                         */
    hw_reg VBUSDIS;     /* Device VBUS discharge time register              */
    hw_reg VBUSPULSE;   /* Device VBUS pulsing time register                */
    mcu_word RESERVED4; /* Reserved                                         */
    hw_reg IEPEMPMSK;   /* Device IN endpoint FIFO empty interrupt mask reg */
    mcu_word RES[0xCB]; /* Reserved. 0x8F8 - 0x834                          */

    /* Device IN endpoints */
    struct              
    {
        hw_reg CTL;         /* Device IN endpoint control register          */
        mcu_word Reserved1; /* Reserved                                     */  
        hw_reg INT;         /* Device IN endpoint interrupt register        */
        mcu_word Reserved2; /* Reserved                                     */  
        hw_reg SIZ;         /* Device IN endpoint size register             */
        hw_reg DMA;         /* Device IN endpoint DMA address register      */
        hw_reg TXFSTS;      /* Device IN endpoint transmit fifo status reg  */
        mcu_word Reserved3; /* Reserved                                     */
    }   EPIN[4];  

    /* Device OUT endpoints */
    struct 
    {
        hw_reg CTL;         /* Device IN endpoint control register          */
        mcu_word Reserved1; /* Reserved                                     */  
        hw_reg INT;         /* Device IN endpoint interrupt register        */
        mcu_word Reserved2; /* Reserved                                     */  
        hw_reg SIZ;         /* Device IN endpoint size register             */
        hw_reg DMA;         /* Device IN endpoint DMA address register      */
        hw_reg TXFSTS;      /* Device IN endpoint transmit fifo status reg  */
        mcu_word Reserved3; /* Reserved                                     */
    }   EPOUT[4];  
};


struct USB_OTG_DFIFO_stack
{
    union 
    {
        mcu_byte bytes[USB_OTG_FIFO_SIZE];
        mcu_word words[USB_OTG_FIFO_SIZE/MCU_BYTES_PER_WORD];
    }   fifo[8];
};

struct USB_OTG_REGISTERS_clock
{
    hw_reg CTL; /* pOWER AND CLOCK GATING CONTROL REGISTER */
    mcu_byte RESERVED1[506];
};


struct USB_OTG
{
    struct USB_OTG_REGISTERS_global global; /* GLOBAL REGISTERS     */
    struct USB_OTG_REGISTERS_host   host;   /* HOST REGISTERS       */
    struct USB_OTG_REGISTERS_device device; /* DEVICE REGISTERS     */
    struct USB_OTG_DFIFO_stack      stack;  /* FIFO STACK           */
    struct USB_OTG_REGISTERS_clock  clock;  /* CLOCK CFG REGISTERS  */
};

#ifdef __cplusplus
}
#endif /* C linkage*/
#endif /* RIMOT_MCU_USB_OTG_CONFIG */