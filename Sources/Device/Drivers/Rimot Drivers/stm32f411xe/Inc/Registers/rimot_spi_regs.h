#ifndef RIMOT_MCU_SPI
#define RIMOT_MCU_SPI
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_register_field_sizes.h"
#include "rimot_bus_region_offsets.h"

#define SPI1_BASE (APB2PERIPH_BASE + 0x3000UL)
#define SPI2_BASE (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE (APB1PERIPH_BASE + 0x3C00UL)
#define SPI4_BASE (APB2PERIPH_BASE + 0x3400UL)
#define SPI5_BASE (APB2PERIPH_BASE + 0x5000UL)

#define I2S2ext_BASE (APB1PERIPH_BASE + 0x3400UL)
#define I2S3ext_BASE (APB1PERIPH_BASE + 0x4000UL)



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

#define _SPI1 ((struct spi_regs*) SPI1_BASE)
#define _SPI2 ((struct spi_regs*) SPI2_BASE)
#define _SPI3 ((struct spi_regs*) SPI3_BASE)
#define _SPI4 ((struct spi_regs*) SPI4_BASE)
#define _SPI5 ((struct spi_regs*) SPI5_BASE)

#define _I2S2ext ((struct spi_regs*) I2S2ext_BASE)
#define _I2S2ext ((struct spi_regs*) I2S2ext_BASE)
#define _I2S3ext ((struct spi_regs*) I2S3ext_BASE)


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_SPI */