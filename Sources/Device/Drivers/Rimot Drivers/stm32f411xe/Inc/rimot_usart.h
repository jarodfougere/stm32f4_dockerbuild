#ifndef RIMOT_MCU_USART
#define RIMOT_MCU_USART
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

/* USART PERIPHERAL REGISTER OVERLAY */
struct usart_regs
{
  hw_reg SR;   /* Status register                   */
  hw_reg DR;   /* Data register                     */
  hw_reg BRR;  /* Baud rate register                */
  hw_reg CR1;  /* Control register 1                */
  hw_reg CR2;  /* Control register 2                */
  hw_reg CR3;  /* Control register 3                */
  hw_reg GTPR; /* Guard time and prescaler register */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_USART */