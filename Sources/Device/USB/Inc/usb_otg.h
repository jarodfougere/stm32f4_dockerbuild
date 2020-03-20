#ifndef RIMOT_USB_OTG_OVERLAY
#define RIMOT_USB_OTG_OVERLAY
#ifdef __cplusplus
extern "C" {
#endif /* | C linkage */
#include <stdint.h>


/* STATES FOR USB OTG PERIPHERAL */
typedef enum
{
    OTG_STATE_reset   = 0x00,
    OTG_STATE_ready   = 0x01,
    OTG_STATE_error   = 0x02,
    OTG_STATE_busy    = 0x03,
    OTG_STATE_timeout = 0x04,
}   OTG_STATE_t;

/* Low Power Mode config for USB OTG PERIPHERAL */
typedef enum
{
    OTG_LPM_on        = 0x00,
    OTG_LPM_sleep     = 0x01,
    OTG_LPM_suspend   = 0x02,
    OTG_LPM_off       = 0x03,
}   OTG_LPM_t;


/* TODO: FORMAT THE CODE SO ITS PRETTY LIKE THE DEVICE REGISTER OVERLAY */
typedef struct
{   
    /* | USB_OTG Control and Status reg          000h */
    volatile uint32_t GOTGCTL;

    /* | USB_OTG Interrupt reg                   004h */    
    volatile uint32_t GOTGINT;              

    /* | Core AHB Configuration reg              008h */
    volatile uint32_t GAHBCFG;              

    /* | Core USB Configuration reg              00Ch */
    volatile uint32_t GUSBCFG;              

    /* | Core Reset reg                          010h */
    volatile uint32_t GRSTCTL;              

    /* | Core Interrupt reg                      014h */
    volatile uint32_t GINTSTS;              

    /* | Core Interrupt Mask reg                 018h */
    volatile uint32_t GINTMSK;              

    /* | Receive Sts Q Read reg                  01Ch */
    volatile uint32_t GRXSTSR;              

    /* | Receive Sts Q Read & POP reg            020h */
    volatile uint32_t GRXSTSP;              

    /* | Receive FIFO Size reg                   024h */
    volatile uint32_t GRXFSIZ;             

    /* | EP0 / Non Periodic Tx FIFO Size reg     028h */
    volatile uint32_t DIEPTXF0_HNPTXFSIZ;   

    /* | Non Periodic Tx FIFO/Queue Sts reg           02Ch */
    volatile uint32_t HNPTXSTS;             

    /* | Reserved                                     030h */
    uint32_t Reserved30[2];             

    /* | General Purpose IO reg                  038h */
    volatile uint32_t GCCFG;                

    /* | User ID reg                             03Ch */
    volatile uint32_t CID;                  

    /* | Reserved                           | 0x40-0xFF */
    uint32_t  Reserved40[48];           

    /* | Host Periodic Tx FIFO Size Reg               100h */
    volatile uint32_t HPTXFSIZ;             

    /* |  Periodic Transmit FIFO                      |*/
    volatile uint32_t DIEPTXF[0x0F];        
}   USB_OTG_core;


/* | USB OTG PERIPHERAL DEVICE REGISTER OVERLAY STRUCTURE */
typedef struct                        /* +---------------------------+-------|*/
{                                     /* | DESCRIPTION               |OFFSET |*/
    /*                                   |---------------------------+-------|*/
    volatile uint32_t DCFG;           /* | Configuration reg         | 0x800 |*/
    volatile uint32_t DCTL;           /* | Control reg               | 0x804 |*/
    volatile uint32_t DSTS;           /* | Status reg (Read Only)    | 0x808 |*/
    uint32_t          Reserved0C;     /* | Reserved                  | 0x80C |*/
    volatile uint32_t DIEPMSK;        /* | IN Endpt Mask             | 0x810 |*/
    volatile uint32_t DOEPMSK;        /* | OUT Endpt Mask            | 0x814 |*/
    volatile uint32_t DAINT;          /* | All Endpts Interrupt Reg  | 0x818 |*/
    volatile uint32_t DAINTMSK;       /* | All Endpts Interrupt Mask | 0x81C |*/
    uint32_t          Reserved20;     /* | Reserved                  | 0x820 |*/
    uint32_t          Reserved9;      /* | Reserved                  | 0x824 |*/
    volatile uint32_t DVBUSDIS;       /* | VBUS discharge reg        | 0x828 |*/
    volatile uint32_t DVBUSPULSE;     /* | VBUS Pulse reg            | 0x82C |*/
    volatile uint32_t DTHRCTL;        /* | Threshold                 | 0x830 |*/
    volatile uint32_t DIEPEMPMSK;     /* | Empty msk                 | 0x834 |*/
    volatile uint32_t DEACHINT;       /* | Dedicated EP interrupt    | 0x838 |*/
    volatile uint32_t DEACHMSK;       /* | Dedicated EP mask         | 0x83C |*/
    uint32_t          Reserved40;     /* | Dedicated EP mask         | 0x840 |*/
    volatile uint32_t DINEP1MSK;      /* | Dedicated EP mask         | 0x844 |*/
    uint32_t          Reserved44[15]; /* | Reserved                  | 0x848 |*/
    /*                                   | Reserved                  | 0x84C |*/
    /*                                   | Reserved                  | 0x850 |*/
    /*                                   | Reserved                  | 0x854 |*/
    /*                                   | Reserved                  | 0x858 |*/
    /*                                   | Reserved                  | 0x85C |*/
    /*                                   | Reserved                  | 0x860 |*/
    /*                                   | Reserved                  | 0x864 |*/
    /*                                   | Reserved                  | 0x868 |*/
    /*                                   | Reserved                  | 0x86C |*/
    /*                                   | Reserved                  | 0x870 |*/
    /*                                   | Reserved                  | 0x874 |*/
    /*                                   | Reserved                  | 0x878 |*/
    /*                                   | Reserved                  | 0x87C |*/
    volatile uint32_t DOUTEP1MSK;     /* | Dedicated EP mask         | 0x884 |*/
}   USB_OTG_dev; /*                      |---------------------------+-------|*/

/* Get the masked global interrupt bits */
#define USB_OTG_GET_INTERRUPTS(core) \
(uint32_t) (((((USB_OTG_core*)core)->GINTSTS) & ((USB_OTG_core*)core)->GINTMSK))



#ifdef __cplusplus
}
#endif /* | C linkage */
#endif /* | RIMOT_USB_OTG_OVERLAY */