#ifndef RIMOT_RCC_DRIVER
#define RIMOT_RCC_DRIVER
#ifdef __cplusplus
extern "C" {
#endif /* C linkage  */

#include <stdint.h>

/* Legacy Alias */
#define HAL_RCC_GetHCLKFreq rccGetSystemCoreClock

typedef enum
{   
    RCC_PLL_Q_DIV_2  = 2,
    RCC_PLL_Q_DIV_3  = 3,
    RCC_PLL_Q_DIV_4  = 4,
    RCC_PLL_Q_DIV_5  = 5,
    RCC_PLL_Q_DIV_6  = 6,
    RCC_PLL_Q_DIV_7  = 7,
    RCC_PLL_Q_DIV_8  = 8,
    RCC_PLL_Q_DIV_9  = 9,
    RCC_PLL_Q_DIV_10 = 10,
    RCC_PLL_Q_DIV_11 = 11,
    RCC_PLL_Q_DIV_12 = 12,
    RCC_PLL_Q_DIV_13 = 13,
    RCC_PLL_Q_DIV_14 = 14,
    RCC_PLL_Q_DIV_15 = 15,
}   RCC_PLL_Q_DIV_t;


typedef enum
{
    RCC_PLL_P_DIV_2 = 0,
    RCC_PLL_P_DIV_4 = 1,
    RCC_PLL_P_DIV_6 = 2,
    RCC_PLL_P_DIV_8 = 3,
}   RCC_PLL_P_DIV_t;



typedef enum
{
    RCC_PLLSRC_hsi,
    RCC_PLLSRC_hse,
}   RCC_PLLSRC_t;


typedef enum
{   
    RCC_APB_CLK_DIV_1  = 0x0U,
    RCC_APB_CLK_DIV_2  = 0X4U,
    RCC_APB_CLK_DIV_4  = 0X5U,
    RCC_APB_CLK_DIV_8  = 0X6U,
    RCC_APB_CLK_DIV_16 = 0X7U,
}   RCC_APB_CLK_DIV_t;


typedef enum
{
    RCC_PERIPH_CLOCK_adc,
    RCC_PERIPH_CLOCK_gpioa,
    RCC_PERIPH_CLOCK_gpiob,
    RCC_PERIPH_CLOCK_gpioc,
    RCC_PERIPH_CLOCK_gpiod,
    RCC_PERIPH_CLOCK_gpioe,
    RCC_PERIPH_CLOCK_gpioh,
    RCC_PERIPH_CLOCK_dma1,
    RCC_PERIPH_CLOCK_dma2,
    RCC_PERIPH_CLOCK_crc,
    RCC_PERIPH_CLOCK_usb,
    RCC_PERIPH_CLOCK_pwr,
    RCC_PERIPH_CLOCK_i2c3,
    RCC_PERIPH_CLOCK_i2c2,
    RCC_PERIPH_CLOCK_i2c1,
    RCC_PERIPH_CLOCK_usart1,
    RCC_PERIPH_CLOCK_usart2,
    RCC_PERIPH_CLOCK_usart6,
    RCC_PERIPH_CLOCK_spi5,
    RCC_PERIPH_CLOCK_spi4,
    RCC_PERIPH_CLOCK_spi3,
    RCC_PERIPH_CLOCK_spi2,
    RCC_PERIPH_CLOCK_spi1,
    RCC_PERIPH_CLOCK_wwdg,
    RCC_PERIPH_CLOCK_tim5,
    RCC_PERIPH_CLOCK_tim4,
    RCC_PERIPH_CLOCK_tim3,
    RCC_PERIPH_CLOCK_tim2,
    RCC_PERIPH_CLOCK_tim1,
    RCC_PERIPH_CLOCK_tim11,
    RCC_PERIPH_CLOCK_tim10,
    RCC_PERIPH_CLOCK_tim9,
    RCC_PERIPH_CLOCK_syscfg,
    RCC_PERIPH_CLOCK_sdio,
}   RCC_PERIPH_CLOCK_t;


typedef enum
{
    RCC_APB_NUM_1,
    RCC_APB_NUM_2,
}   RCC_APB_NUM_t;



typedef enum
{   
    RCC_HCLK_DIV_1      = 0,
    RCC_HCLK_DIV_2      = 0x8,
    RCC_HCLK_DIV_4      = 0x9,
    RCC_HCLK_DIV_8      = 0xa,
    RCC_HCLK_DIV_16     = 0xb,
    RCC_HCLK_DIV_64     = 0xc,
    RCC_HCLK_DIV_128    = 0xd,
    RCC_HCLK_DIV_256    = 0xe,
    RCC_HCLK_DIV_512    = 0xf,
}   RCC_HCLK_DIV_t;


typedef enum
{
    RCC_SYSCLK_SOURCE_hsi = 0,
    RCC_SYSCLK_SOURCE_hse = 1,
    RCC_SYSCLK_SOURCE_pll = 2,
}   RCC_SYSCLK_SOURCE_t;


typedef enum
{   
    RCC_HSE_MODE_feedback = 0,
    RCC_HSE_MODE_bypass   = 1,
}   RCC_HSE_MODE_t;


/* Event types that can cause RCC_IRQhandler to occur                       */
/* The enum value is position of the interrupt enable bit in RCC::CIR       */
/* Note that hardware always has Clock Security IRQ event trigger enabled   */
typedef enum
{   
    RCC_CLK_RDY_lsi    = 8,
    RCC_CLK_RDY_lse    = 9,
    RCC_CLK_RDY_hsi    = 10,
    RCC_CLK_RDY_hse    = 11,
    RCC_CLK_RDY_pll    = 12,
    RCC_CLK_RDY_plli2s = 13,
}   RCC_CLK_RDY_t;


typedef enum
{
    RCC_MCO2_SRC_sysclk = 0,
    RCC_MCO2_SRC_plli2s = 1,
    RCC_MCO2_SRC_hse    = 2,
    RCC_MCO2_SRC_pll    = 3,
}   RCC_MCO2_SRC_t;


typedef enum
{
    RCC_MCO_PRESCALER_1 = 0,
    RCC_MCO_PRESCALER_2 = 4,
    RCC_MCO_PRESCALER_3 = 5,
    RCC_MCO_PRESCALER_4 = 6,
    RCC_MCO_PRESCALER_5 = 7,
}   RCC_MCO_PRESCALER_t;


typedef enum
{
    RCC_RESET_brownout = 25, /* Brownout threshhold reset            */
    RCC_RESET_nrst     = 26, /* hardwre reset via nrst pin           */
    RCC_RESET_onOff    = 27, /* Power up / power down reset          */
    RCC_RESET_soft     = 28, /* Software initiated soft reset        */
    RCC_RESET_iwdg     = 29, /* Independent watchdog initiated reset */
    RCC_RESET_wwdg     = 30, /* window watchdog initiated reset      */
    RCC_RESET_lowpwr   = 31, /* Change to low power mode reset       */
}   RCC_RESET_t;



typedef enum
{   
    /* BIT VALUES OF 0 AND 1 ARE NOT ALLOWED */
    RCC_HSE_RTC_DIV_2 = 2,
    RCC_HSE_RTC_DIV_3,
    RCC_HSE_RTC_DIV_4,
    RCC_HSE_RTC_DIV_5,
    RCC_HSE_RTC_DIV_6,
    RCC_HSE_RTC_DIV_7,
    RCC_HSE_RTC_DIV_8,
    RCC_HSE_RTC_DIV_9,
    RCC_HSE_RTC_DIV_10,
    RCC_HSE_RTC_DIV_11,
    RCC_HSE_RTC_DIV_12,
    RCC_HSE_RTC_DIV_13,
    RCC_HSE_RTC_DIV_14,
    RCC_HSE_RTC_DIV_15,
    RCC_HSE_RTC_DIV_16,
    RCC_HSE_RTC_DIV_17,
    RCC_HSE_RTC_DIV_18,
    RCC_HSE_RTC_DIV_19,
    RCC_HSE_RTC_DIV_20,
    RCC_HSE_RTC_DIV_21,
    RCC_HSE_RTC_DIV_22,
    RCC_HSE_RTC_DIV_23,
    RCC_HSE_RTC_DIV_24,
    RCC_HSE_RTC_DIV_25,
    RCC_HSE_RTC_DIV_26,
    RCC_HSE_RTC_DIV_27,
    RCC_HSE_RTC_DIV_28,
    RCC_HSE_RTC_DIV_29,
    RCC_HSE_RTC_DIV_30,
    RCC_HSE_RTC_DIV_31,
}   RCC_HSE_RTC_DIV_t;


/**
 * @fn rccEnablePeriphClock
 * @brief Enable the bus clock for a given peripheral
 * 
 * @param clock one of RCC_PERIPH_CLOCK_t
 */
void rccEnablePeriphClock(RCC_PERIPH_CLOCK_t clock);


/**
 * @fn rccDisablePeriphClock
 * @brief Disable the bus clock for a given peripheral
 * 
 * @param clock one of RCC_PERIPH_CLOCK_t
 */
void rccDisablePeriphClock(RCC_PERIPH_CLOCK_t clock);


/**
 * @fn rcc_enablePLL
 * @brief Enable the phase-locked-loop 100MHz internal oscillator.
 * 
 * @return int 0 if enabled successfully, 1 if unable to stabilize PLL
 */
int rcc_enablePLL(void);


            
void rcc_set_PLL_Q_Div(RCC_PLL_Q_DIV_t div);
int rcc_enableHSI(void);
int rcc_enableHSE(void);
int rcc_enablePLL(void);
void rcc_set_PLLSRC(RCC_PLLSRC_t in);
void rcc_set_PLL_P_Div(RCC_PLL_P_DIV_t div);
void rcc_set_PLL_N_Mul(unsigned int mul);


/**
 * @fn rcc_set_PLL_M_Div
 * @brief set the PLL::M scaling coefficient
 * 
 * @param mul the M division factor for PLL. Must be between
 */
void rcc_set_PLL_M_Div(unsigned int mul);


/**
 * @fn rcc_set_APB_clock_Div
 * @brief set the prescaler for a given APB bus clock
 * 
 * @param num one of RCC_APB_NUM_t. The APB to configure.
 * @param div one of RCC_APB_CLK_DIV_t. The prescaler to apply.
 */
void rcc_set_APB_clock_Div(RCC_APB_NUM_t num, RCC_APB_CLK_DIV_t div);


/**
 * @fn rcc_set_HClk_Div
 * @brief set the prescaler for HCLK (AHB primary bus clock signal)
 * @param div one of RCC_HCLK_DIV_t
 */
void rcc_set_HClk_Div(RCC_HCLK_DIV_t div);


/**
 * @fn rcc_set_SysClkSrc
 * @brief set the source of the system clock
 * @param src one of RCC_SYSCLK_SOURCE_t
 */
void rcc_set_SysClkSrc(RCC_SYSCLK_SOURCE_t src);


/**
 * @fn rcc_get_SysClkSrc
 * @brief get the configured source for the system clock
 * @return RCC_SYSCLK_SOURCE_t one of RCC_SYSCLK_SOURCE_t
 */
RCC_SYSCLK_SOURCE_t rcc_get_SysClkSrc(void);


/**
 * @fn rcc_ensable_ClkRdy_IRQ
 * @brief enable the RCC IRQ exception when a given clock becomes stable
 * 
 * @param evt one of RCC_CLK_RDY_t
 */
void rcc_enable_ClkRdy_IRQ(RCC_CLK_RDY_t evt);


/**
 * @fn rcc_disable_ClkRdy_IRQ
 * @brief Disable the RCC IRQ exception when a given clock becomes stable
 * 
 * @param evt one of RCC_CLK_RDY_t
 */
void rcc_disable_ClkRdy_IRQ(RCC_CLK_RDY_t evt);


/**
 * @fn rcc_setHSEmode
 * @brief configure the HSE control registers to use feedback or input 
 * for the external high speed clock
 * 
 * @param mode one of RCC_HSE_MODE_t
 */
void rcc_setHSEmode(RCC_HSE_MODE_t mode);


/**
 * @fn rcc_setMCO2_Src
 * @brief configure the source for MCO2
 * 
 * @param src one of RCC_MCO2_SRC_t
 */
void rcc_setMCO2_Src(RCC_MCO2_SRC_t src);


/**
 * @fn rcc_setMCO2_Prescaler
 * @brief configure the prescaler for master clock out signal
 * 
 * @param scale one of RCC_MCO_PRESCALER_t
 */
void rcc_setMCO2_Prescaler(RCC_MCO_PRESCALER_t scale);


/**
 * @fn rccSystemCoreClockUpdate
 * @brief Update the value of the systemCoreClock (SysClk freq in Hz)
 * variable based on the rcc register values
 */
void rccSystemCoreClockUpdate(void);


/**
 * @brief check if HSE is stable
 * 
 * @return int 1 if stable, 0 if not stable
 */
int rcc_HSE_isReady(void);


/**
 * @brief check if HSI is stable
 * 
 * @return int 1 if stable, 0 if not stable
 */
int rcc_HSI_isReady(void);


/**
 * @brief check if PLL is stable
 * 
 * @return int 1 if stable, 0 if not stable
 */
int rcc_PLL_isReady(void);


/**
 * @fn rccGetSystemCoreClock
 * @brief get the value of the sysClk frequency in Hz
 * 
 * @return uint32_t the sysClk frequency in Hz
 */
uint32_t rccGetSystemCoreClock(void);


/**
 * @fn rccGetHClkFreq
 * @brief get the frequency of the HClk in Hz
 * 
 * @return uint32_t the frequency of the HClk in Hz
 */
uint32_t rccGetHClkFreq(void);


/**
 * @fn rccCoreInit
 * @brief Initializes the bare minimum busses in RCC registers to 
 * configure mcu system parameters
 */
void rccCoreInit(void);


/**
 * @fn rccSetRTC_HSE_Div
 * @brief set the prescaler for the RTC when HSE is used as the input to RTC
 * @param div one of RCC_HSE_RTC_DIV_t
 */
void rccSetRTC_HSE_Div(RCC_HSE_RTC_DIV_t div);


#ifdef __cplusplus
}
#endif /* C linkage  */
#endif /* RIMOT_RCC_DRIVER  */
