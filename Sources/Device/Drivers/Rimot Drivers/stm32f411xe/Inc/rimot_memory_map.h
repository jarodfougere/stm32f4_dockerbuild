#ifndef RIMOT_PERIPHERAL_MEMORY_MAP
#define RIMOT_PERIPHERAL_MEMORY_MAP
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#include "rimot_peripheral_regs.h"

#include "rimot_adc.h"
#include "rimot_dma.h"
#include "rimot_flash_controller.h"
#include "rimot_gpio.h"
#include "rimot_rcc.h"
#include "rimot_rtc.h"
#include "rimot_spi.h"
#include "rimot_i2c.h"
#include "rimot_otg_usb_config.h"
#include "rimot_watchdog.h"
#include "rimot_system_regs.h"
#include "rimot_usart.h"

/*
 *  ALL THIS INFO CAN BE FOUND. PAGE 36
 */


/*!< FLASH(up to 1 MB) base address in the alias region */
#define FLASH_BASE            0x08000000UL 

/*!< SRAM1(128 KB) base address in the alias region */
#define SRAM1_BASE            0x20000000UL 

/*!< Peripheral base address in the alias region  */
#define PERIPH_BASE           0x40000000UL

/*!< SRAM1(128 KB) base address in the bit-band region  */
#define SRAM1_BB_BASE         0x22000000UL 

/*!< Peripheral base address in the bit-band region  */
#define PERIPH_BB_BASE        0x42000000UL 

/*!< Backup SRAM(4 KB) base address in the bit-band region  */
#define BKPSRAM_BB_BASE       0x42480000UL 

/*!< FLASH end address */                              
#define FLASH_END             0x0807FFFFUL 

/*!< Base address of : (up to 528 Bytes) embedded FLASH OTP Area  */
#define FLASH_OTP_BASE        0x1FFF7800UL 

/*!< End address of : (up to 528 Bytes) embedded FLASH OTP Area  */
#define FLASH_OTP_END         0x1FFF7A0FUL 

/**********************************
 * FOR PERIPHERAL MEMORY MAP,
 * SEE PAGE 39 OF STM32F411XE 
 * REFERENCE MANUAL
 *********************************/

struct peripherals
{
    struct USB_OTG          *USB;
    struct adc_periph       *adc;
    struct adc_common       *adc_common;
    struct iwdg_regs        *iwdg;
    struct rtc_regs         *rtc;
    struct dma_peripheral   *dma2;
    struct dma_peripheral   *dma1;
    struct flash_controller *flash_controller;
    struct rcc_regs         *rcc;
    struct gpio_periph      *gpioH; /* Don't ask me why FG ports aren't in */
                                    /* there,  Datasheet goes abcde->h     */
    struct gpio_periph      *gpioE;
    struct gpio_periph      *gpioD;
    struct gpio_periph      *gpioC;
    struct gpio_periph      *gpioB;
    struct gpio_periph      *gpioA;
};




#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_PERIPHERAL_MEMORY_MAP */
