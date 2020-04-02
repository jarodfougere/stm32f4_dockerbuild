#ifndef RIMOT_MCU_USART
#define RIMOT_MCU_USART
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_region_base_addresses.h"

#define USART1_BASE (APB2PERIPH_BASE + 0x1000UL)
#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)
#define USART6_BASE (APB2PERIPH_BASE + 0x1400UL)


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

#define USART1 ((struct usart_regs*) USART1_BASE)
#define USART2 ((struct usart_regs*) USART2_BASE)
#define USART6 ((struct usart_regs*) USART6_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_USART */