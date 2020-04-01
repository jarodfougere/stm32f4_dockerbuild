#ifndef RIMOT_MCU_RTC
#define RIMOT_MCU_RTC
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

/* REAL TIME CLOCK REGISTERS */
typedef struct rtc_regs
{
  hw_reg TR;         /* time register                           */
  hw_reg DR;         /* date register                           */
  hw_reg CR;         /* control register                        */
  hw_reg ISR;        /* initialization and status register      */
  hw_reg PRER;       /* prescaler register                      */
  hw_reg WUTR;       /* wakeup timer register                   */
  hw_reg CALIBR;     /* calibration register                    */
  hw_reg ALRMAR;     /* alarm A register                        */
  hw_reg ALRMBR;     /* alarm B register                        */
  hw_reg WPR;        /* write protection register               */
  hw_reg SSR;        /* sub second register                     */
  hw_reg SHIFTR;     /* shift control register                  */
  hw_reg TSTR;       /* time stamp time register                */
  hw_reg TSDR;       /* time stamp date register                */
  hw_reg TSSSR;      /* time-stamp sub second register          */
  hw_reg CALR;       /* calibration register                    */
  hw_reg TAFCR;      /* tamper and alt function config register */
  hw_reg ALRMASSR;   /* alarm A sub second register             */
  hw_reg ALRMBSSR;   /* alarm B sub second register             */
  mcu_word RESERVED; /* Reserved                                */
  hw_reg BKPR[20];   /* Backup registers                        */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_RTC */