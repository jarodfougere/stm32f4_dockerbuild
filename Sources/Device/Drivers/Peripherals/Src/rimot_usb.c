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

#include "ATTRIBUTE_PORTABILITY_HEADER.h"

#include <stdint.h>
#include <stdlib.h>

#include "rimot_usb_register_masks.h"
#include "rimot_bus_region_offsets.h"

#include "rimot_pin_aliases.h"
#include "rimot_LL_debug.h"
#include "rimot_register_padding.h"


#include "rimot_interrupts.h"
#include "rimot_rcc.h"

#include "cmsis_compiler.h"

#define USB_OTG_FS_PERIPH_BASE 0x50000000UL

#define USB_OTG_FIFO_SIZE 0x1000UL
#define USB_OTG_FS_HOST_MAX_CHANNEL_NBR 8U
#define USB_OTG_FS_MAX_IN_ENDPOINTS 4U   /* Including EP0 */
#define USB_OTG_FS_MAX_OUT_ENDPOINTS 4U  /* Including EP0 */
#define USB_OTG_FS_TOTAL_FIFO_SIZE 1280U /* in Bytes */
#define USB_OTG_FS ((USB_t *)USB_OTG_FS_PERIPH_BASE)



/* 
 * We subtract word alignment (in bytes) because
 * the compiler needs to align the lower field 
 * of the padded region 
 */

struct __usb_reg_overlay
{
    /* USB CORE REGS */
    volatile uint32_t GOTCTL;             /* 0x0000  */
    volatile uint32_t GOTGINT;            /* 0x0004  */
    volatile uint32_t GAHBCFG;            /* 0x0008  */
    volatile uint32_t GUSBCFG;            /* 0x000C  */
    volatile uint32_t GRSTCTL;            /* 0x0010  */
    volatile uint32_t GINTSTS;            /* 0x0014  */
    volatile uint32_t GINTMSK;            /* 0x0018  */
    volatile uint32_t GRXSTSR;            /* 0x001C  */
    volatile uint32_t GRXSTSP;            /* 0x0020  */
    volatile uint32_t GRXFSIZ;            /* 0x0024  */
    volatile uint32_t DIEPTXF0_HNPTXFSIZ; /* 0x0028  */
    volatile uint32_t HNPTXSTS;           /* 0x002c  */

    PAD_WITH_BYTES(0x002c, 0x0038);

    volatile uint32_t GCCFG; /* 0x0038  */
    volatile uint32_t CID;   /* 0x003C  */

    PAD_WITH_BYTES(0x0100, 0x003C);

    volatile uint32_t HPTXFSIZ;    /* 0x0100  */
    volatile uint32_t DIEPTXF[15]; /* 0x0104  */

    PAD_WITH_BYTES(0x013C, 0x0400);

    /* USB HOST CFG REGS */
    volatile uint32_t HCFG;  /* 0x0400  */
    volatile uint32_t HFIR;  /* 0x0404  */
    volatile uint32_t HFNUM; /* 0x0408  */

    PAD_WITH_BYTES(0x0410, 0x0408);

    volatile uint32_t HPTXSTS;  /* 0x0410  */
    volatile uint32_t HAINT;    /* 0x0414  */
    volatile uint32_t HAINTMSK; /* 0x0418  */

    PAD_WITH_BYTES(0x0440, 0x0418);

    volatile uint32_t HPRT; /* 0x0440  */

    PAD_WITH_BYTES(0x0500, 0x0440);

    /* HOST CHANNELS */
    struct
    {
        volatile uint32_t CHAR;   /* 0x0500 + (0x0020 * ch_idx)   */
        volatile uint32_t SPLIT;  /* 0x0504 + (0X0020 * ch_idx)   */
        volatile uint32_t INT;    /* 0x0508 + (0x0020 * ch_idx)   */
        volatile uint32_t INTMSK; /* 0x050c + (0x0020 * ch_idx)   */
        volatile uint32_t TSIZ;   /* 0x0510 + (0x0020 * ch_idx)   */
        volatile uint32_t DMA;    /* 0x0514 + (0x0020 * ch_idx)   */

        PAD_WITH_BYTES(0x0520, 0x0514);

    } HC[USB_OTG_FS_HOST_MAX_CHANNEL_NBR];

    PAD_WITH_BYTES(0x05fc, 0x0800);

    /* DEVICE CONFIG REGISTERS */
    volatile uint32_t DCFG; /* 0x0800  */
    volatile uint32_t DCTL; /* 0x0804  */
    volatile uint32_t DSTS; /* 0x0808  */

    PAD_WITH_BYTES(0X0808, 0x0810);

    volatile uint32_t DIEPMSK;  /* 0x0810  */
    volatile uint32_t DOEPMSK;  /* 0x0814  */
    volatile uint32_t DAINT;    /* 0x0818  */
    volatile uint32_t DAINTMSK; /* 0x081c  */

    PAD_WITH_BYTES(0x081c, 0x0828);

    volatile uint32_t DVBUSDIS;   /* 0x0828  */
    volatile uint32_t DVBUSPULSE; /* 0x082c  */
    volatile uint32_t DTHRCTL;    /* 0x0830  */
    volatile uint32_t DIEPEMPMSK; /* 0x0834  */
    volatile uint32_t DEACHINT;   /* 0x0838  */
    volatile uint32_t DEACHMSK;   /* 0x083C  */

    PAD_WITH_BYTES(0x083c, 0x844);

    volatile uint32_t DINEP1MSK; /* 0x0844  */

    PAD_WITH_BYTES(0x0884, 0x844);

    volatile uint32_t DOUTEP1MSK; /* 0x0884  */

    PAD_WITH_BYTES(0x0884, 0x0900);

    /* Device IN endpoints */
    struct
    {
        volatile uint32_t CTL; /* 0x0900 + (0x0020 * EP_idx)   */

        PAD_WITH_BYTES(0x0900, 0x0908);

        volatile uint32_t INT; /* 0x0908 + (0x0020 * EP_idx)   */

        PAD_WITH_BYTES(0x0908, 0x0910);

        volatile uint32_t SIZ;    /* 0x0910 + (0x0020 * EP_idx)   */
        volatile uint32_t DMA;    /* 0x0914 + (0x0020 * EP_idx)   */
        volatile uint32_t TXFSTS; /* 0x0918 + (0x0020 * EP_idx)   */

        PAD_WITH_BYTES(0x0918, 0x0920);

    } DIEP[USB_OTG_FS_MAX_IN_ENDPOINTS];

    PAD_WITH_BYTES(0x097c, 0x0b00);

    /* Device IN endpoints */
    struct
    {
        volatile uint32_t CTL; /* 0x0b00 + (0x0020 * EP_idx)   */

        PAD_WITH_BYTES(0x0900, 0x0908);

        volatile uint32_t INT; /* 0x0b08 + (0x0020 * EP_idx)   */

        PAD_WITH_BYTES(0x0908, 0x0910);

        volatile uint32_t SIZ;    /* 0x0b10 + (0x0020 * EP_idx)   */
        volatile uint32_t DMA;    /* 0x0b14 + (0x0020 * EP_idx)   */
        volatile uint32_t TXFSTS; /* 0x0b18 + (0x0020 * EP_idx)   */

        PAD_WITH_BYTES(0x0918, 0x0920);
    } DOEP[USB_OTG_FS_MAX_OUT_ENDPOINTS];

    PAD_WITH_BYTES(0X0B7c, 0x0E00);

    volatile uint32_t PCGCTL; /* 0x0e00 */

    PAD_WITH_BYTES(0x0e00, 0x1000);

    struct
    {
        /* Push/Pop to this region */
        volatile uint8_t buf[USB_OTG_FIFO_SIZE];
    } DFIFO[8];

    PAD_WITH_BYTES(0X8cfc, 0x20000);

    struct
    {
        /* Fifo for diagnostic info */
        volatile uint8_t buf[128000]; /* 128 kB */
    } DRW_FIFO;
};

static void (*DelayFunc)(uint32_t);

void usbInjectDelayFunc(void (*delayFunc)(uint32_t))
{
    LL_ASSERT(NULL != delayFunc);
    DelayFunc = delayFunc;
}

void USBD_Delay(uint32_t ms)
{
    if (DelayFunc != NULL)
    {
        DelayFunc(ms);
    }
}

/**
 * @brief This function handles wakeup of the USB Peripheral in OTG mode
 * 
 */
void OTG_FS_WKUP_IRQHandler(void)
{
}

void OTG_FS_IRQHandler(void)
{
}
