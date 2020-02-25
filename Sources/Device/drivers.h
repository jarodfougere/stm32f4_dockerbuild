/*
This is a generic inclusion header for the drivers.

It's easier to do it this way and let the linker purge dead code
than to manually build each HAL source module and link

*/ 


#ifndef RIMOT_DRIVERS
#define RIMOT_DRIVERS

#ifdef MCU_APP

#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_exti.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_can.h"
#include "stm32f4xx_hal_crc.h"
#include "stm32f4xx_hal_cryp.h" 
#include "stm32f4xx_hal_smbus.h"
#include "stm32f4xx_hal_dma2d.h"
#include "stm32f4xx_hal_dac.h"
#include "stm32f4xx_hal_dcmi.h"
#include "stm32f4xx_hal_eth.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_sram.h"
#include "stm32f4xx_hal_nor.h"
#include "stm32f4xx_hal_nand.h"
#include "stm32f4xx_hal_pccard.h"
#include "stm32f4xx_hal_sdram.h"
#include "stm32f4xx_hal_hash.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_i2s.h"
#include "stm32f4xx_hal_iwdg.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_rng.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_sai.h"
#include "stm32f4xx_hal_sd.h"
#include "stm32f4xx_hal_mmc.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_irda.h"
#include "stm32f4xx_hal_smartcard.h"
#include "stm32f4xx_hal_wwdg.h"
#include "stm32f4xx_hal_pcd.h"
#include "stm32f4xx_hal_hcd.h"
#include "stm32f4xx_hal_dsi.h"
#include "stm32f4xx_hal_qspi.h"
#include "stm32f4xx_hal_cec.h"
#include "stm32f4xx_hal_fmpi2c.h"
#include "stm32f4xx_hal_spdifrx.h"
#include "stm32f4xx_hal_dfsdm.h"
#include "stm32f4xx_hal_lptim.h"

#endif /* MCU_APP */

#endif /* RIMOT_DRIVERS */