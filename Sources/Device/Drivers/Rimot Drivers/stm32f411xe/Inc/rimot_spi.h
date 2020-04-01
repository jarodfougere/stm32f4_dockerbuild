#ifndef RIMOT_MCU_SPI
#define RIMOT_MCU_SPI
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

/* SPI PERIPHERAL REGISTER STRUCTURE */
struct spi_regs
{
  hw_reg CR1;     /* control register 1 (not used in I2S mode) */
  hw_reg CR2;     /* control register                          */
  hw_reg SR;      /* status register                           */
  hw_reg DR;      /* data register                             */
  hw_reg CRCPR;   /* CRC polynomial reg (not used in I2S mode) */
  hw_reg RXCRCR;  /* RX CRC register (not used in I2S mode)    */
  hw_reg TXCRCR;  /* TX CRC register (not used in I2S mode)    */
  hw_reg I2SCFGR; /* I2S mode configuration register           */
  hw_reg I2SPR;   /* I2S mode prescaler register               */
};

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_SPI */