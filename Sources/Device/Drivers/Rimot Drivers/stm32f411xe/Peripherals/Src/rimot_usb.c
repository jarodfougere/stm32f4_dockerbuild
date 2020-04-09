/**
 * @file rimot_usb.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This source module provides a low level driver for the usb otg 
 * peripheral on the stm32f411re microcontroller
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include "rimot_usb_otg.h"
#include "rimot_usb_register_masks.h"
#include "rimot_register_bit_ops.h"
#include "rimot_pin_aliases.h"
#include "rimot_bus_region_offsets.h"

#include "rimot_LL_debug.h"

#define USB_OTG_FS_HOST_MAX_CHANNEL_NBR                8U
#define USB_OTG_FS_MAX_IN_ENDPOINTS                    4U    /* Including EP0 */
#define USB_OTG_FS_MAX_OUT_ENDPOINTS                   4U    /* Including EP0 */
#define USB_OTG_FS_TOTAL_FIFO_SIZE                     1280U /* in Bytes */


typedef struct USB_OTG_peripheral USB;

#define OSG_OTG_PERIPH_BASE (0x50000000UL)

#define USB_OTG_FIFO_SIZE 0x1000UL

/*************************************************/
/* SEE REFERENCE MANUAL PAGE 649 FOR MORE DETAIL */
/*************************************************/ 


/* REGISTER MAP PAGE 754 REFERENCE MANUAL */
struct USB_OTG_peripheral
{   
    /* USB CORE REGS */
    hw_reg GOCTL;                       /* 0x0000  */
    hw_reg GOTGINT;                     /* 0x0004  */
    hw_reg GAHBCFG;                     /* 0x0008  */
    hw_reg GUSBCFG;                     /* 0x000C  */
    hw_reg GRSTCTL;                     /* 0x0010  */
    hw_reg GINTSTS;                     /* 0x0014  */
    hw_reg GINTMSK;                     /* 0x0018  */
    hw_reg GRXSTSR;                     /* 0x001C  */
    hw_reg GRXSTSP;                     /* 0x0020  */
    hw_reg GRXFSIZ;                     /* 0x0024  */
    union  {                            
    hw_reg HNPTXFSIZ;                   /* 0x0028  */
    hw_reg DIEPTXF0;                    /* 0x0028  */
    }      TXFIFOSZ;                    
    hw_reg HNPTXSTS;                    /* 0x002c  */ 
    PAD_BETWEEN(USB, 0x0038,0x002C);    
    hw_reg GCCFG;                       /* 0x0038  */
    hw_reg CID;                         /* 0x003C  */
    PAD_BETWEEN(USB, 0x0100,0x003c);    
    hw_reg HPTXFSIZ;                    /* 0x0100  */
    hw_reg DIEPTXF1;                    /* 0x0104  */
    hw_reg DIEPTXF2;                    /* 0x0108  */
    hw_reg DIEPTXF3;                    /* 0x010C  */

    /* PAD BETWEEN GLOBAL AND HOST CFG REGISTERS   */
    PAD_BETWEEN(USB,0x400, 0x10c);         

    /* USB HOST CFG REGS */
    hw_reg HCFG;                        /* 0x0400  */
    hw_reg HFIR;                        /* 0x0404  */
    hw_reg HFNUM;                       /* 0x0408  */
    PAD_BETWEEN(USB, 0x0410, 0x0408);   
    hw_reg HPTXSTS;                     /* 0x0410  */
    hw_reg HAINT;                       /* 0x0414  */
    hw_reg HAINTMSK;                    /* 0x0418  */
    PAD_BETWEEN(USB, 0x0440, 0x0418);   
    hw_reg HPRT;                        /* 0x0440  */

    /* PAD BETWEEN HOST CFG AND CHANNEL REGISTERS  */
    PAD_BETWEEN(USB, 0x0500, 0x0440);       

    /* HOST CHANNELS */
    struct {                            
    hw_reg CHAR;                        /* 0x0500 + (0x0020 * ch_idx)   */
    hw_reg SPLIT;                       /* 0x0504 + (0X0020 * ch_idx)   */     
    hw_reg INT;                         /* 0x0508 + (0x0020 * ch_idx)   */
    hw_reg INTMSK;                      /* 0x050c + (0x0020 * ch_idx)   */
    hw_reg TSIZ;                        /* 0x0510 + (0x0020 * ch_idx)   */
    hw_reg DMA;                         /* 0x0514 + (0x0020 * ch_idx)   */
    PAD_BETWEEN(USB, 0x0520, 0x0514);   /* PAD TO NEXT STRUCT IN ARRAY  */
    } HC[USB_OTG_FS_HOST_MAX_CHANNEL_NBR];

    /* PAD BETWEEN HOST CHANNEL REGISTERS AND DEVICE CONFIG REIGSTERS */
    PAD_BETWEEN(USB, 0x05f4, 0x0800);

    /* DEVICE CONFIG REGISTERS */
    hw_reg DCFG;                        /* 0x0800  */
    hw_reg DCTL;                        /* 0x0804  */
    hw_reg DSTS;                        /* 0x0808  */
    PAD_BETWEEN(USB, 0X0808, 0X0810);   
    hw_reg DIEPMSK;                     /* 0x0810  */
    hw_reg DOEPMSK;                     /* 0x0814  */
    hw_reg DAINT;                       /* 0x0818  */
    hw_reg DAINTMSK;                    /* 0x081c  */
    PAD_BETWEEN(USB, 0x081c, 0x0828);   
    hw_reg DVBUSDIS;                    /* 0x0828  */
    hw_reg DVBUSPULSE;                  /* 0x082c  */
    PAD_BETWEEN(USB, 0x082c, 0x0834);   
    hw_reg DIEPEMPMSK;                  /* 0x0834  */


    /* PAD BETWEEN DEVICE CONFIG REGISTERS AND DEVICE IN ENDPOINTS */
    PAD_BETWEEN(USB, 0x0834, 0x0900);                  

    /* Device IN endpoints */
    struct              
    {
        hw_reg CTL;                         /* 0x0900 + (0x0020 * EP_idx)   */  
        PAD_BETWEEN(USB, 0x0900, 0x0908);
        hw_reg INT;                         /* 0X0908 + (0x0020 * EP_idx)   */
        PAD_BETWEEN(USB, 0x0908, 0x0910);
        hw_reg SIZ;                         /* 0X0910 + (0x0020 * EP_idx)   */
        hw_reg DMA;                         /* 0X0914 + (0x0020 * EP_idx)   */
        hw_reg TXFSTS;                      /* 0X0918 + (0x0020 * EP_idx)   */
        PAD_BETWEEN(USB, 0x0918, 0x0920);   /* PAD TO NEXT STRUCT IN ARRAY  */
    }   DIEP[USB_OTG_FS_MAX_IN_ENDPOINTS];  

    /* AFTER ENDPOINT INDEX 3, WE ARE AT OFFSET 0x0980 */
    /* PAD BETWEEN IN ENDPOINT AND OUT ENDPOINT REGISTERS */
    PAD_BETWEEN(USB, 0x0980, 0x0b00);
    
    /* Device IN endpoints */
    struct              
    {
        hw_reg CTL;                         /* 0x0b00 + (0x0020 * EP_idx)   */  
        PAD_BETWEEN(USB, 0x0900, 0x0908);
        hw_reg INT;                         /* 0X0b08 + (0x0020 * EP_idx)   */
        PAD_BETWEEN(USB, 0x0908, 0x0910);
        hw_reg SIZ;                         /* 0X0b10 + (0x0020 * EP_idx)   */
        hw_reg DMA;                         /* 0X0b14 + (0x0020 * EP_idx)   */
        hw_reg TXFSTS;                      /* 0X0b18 + (0x0020 * EP_idx)   */
        PAD_BETWEEN(USB, 0x0918, 0x0920);   /* PAD TO NEXT STRUCT           */
    }   DOEP[USB_OTG_FS_MAX_OUT_ENDPOINTS];  

    /* AFTER ENDPOINT INDEX 3, WE ARE AT OFFSET 0X0B80 */
    /* PAD BETWEEN DEVICE OUT ENDPOINT REGISTERS AND USB POWER CONTROL REGI */
    PAD_BETWEEN(USB, 0X0B80, 0X0E00);


    hw_reg PCGCTL;  /* 0x0e00 */

    PAD_BETWEEN(USB, 0x0e00, 0x1000);

    struct
    {
        hw_byte buf[USB_OTG_FIFO_SIZE];
    }   FIFO[8];


    /* AFTER INDEX 7 OF THE FIFOS, WE ARE AT OFFSET 0x9000 */
    /* PAD BETWEEN END OF FIFO AND START OF DFIFO (DEBUG MSG) */
    PAD_BETWEEN(USB, 0X9000, 0X20000);

    struct
    {   
        hw_byte buf[0x20000]; 
        
    }   DFIFO;
};

#define _USB ((struct USB_OTG*) OSG_OTG_PERIPH_BASE)




/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
    //HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

/**
 * @brief This function handles wakeup of the USB Peripheral in OTG mode
 * 
 */
void OTG_FS_WKUP_IRQHandler(void)
{

}
