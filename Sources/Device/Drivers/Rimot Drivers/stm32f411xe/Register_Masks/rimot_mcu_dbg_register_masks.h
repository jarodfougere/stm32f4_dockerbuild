#ifndef RIMOT_MCU_DBG_REGISTER_MASKS
#define RIMOT_MCU_DBG_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/********************  BIT DEFINITION FOR DBGMCU::IDCODE   *************/
#define IDCODE_DEV_ID_POS                  (0U)                 
#define IDCODE_DEV_ID_MSK                  (0XFFFUL << IDCODE_DEV_ID_POS) 
#define IDCODE_DEV_ID                      IDCODE_DEV_ID_MSK  
#define IDCODE_REV_ID_POS                  (16U)                
#define IDCODE_REV_ID_MSK                  (0XFFFFUL << IDCODE_REV_ID_POS) 
#define IDCODE_REV_ID                      IDCODE_REV_ID_MSK  

/********************  BIT DEFINITION FOR DBGMCU::CR   *****************/
#define CR_DBG_SLEEP_POS                   (0U)                 
#define CR_DBG_SLEEP_MSK                   (0X1UL << CR_DBG_SLEEP_POS) 
#define CR_DBG_SLEEP                       CR_DBG_SLEEP_MSK   
#define CR_DBG_STOP_POS                    (1U)                 
#define CR_DBG_STOP_MSK                    (0X1UL << CR_DBG_STOP_POS) 
#define CR_DBG_STOP                        CR_DBG_STOP_MSK   
#define CR_DBG_STANDBY_POS                 (2U)                 
#define CR_DBG_STANDBY_MSK                 (0X1UL << CR_DBG_STANDBY_POS) 
#define CR_DBG_STANDBY                     CR_DBG_STANDBY_MSK 
#define CR_TRACE_IOEN_POS                  (5U)                 
#define CR_TRACE_IOEN_MSK                  (0X1UL << CR_TRACE_IOEN_POS) 
#define CR_TRACE_IOEN                      CR_TRACE_IOEN_MSK  

#define CR_TRACE_MODE_POS                  (6U)                 
#define CR_TRACE_MODE_MSK                  (0X3UL << CR_TRACE_MODE_POS) 
#define CR_TRACE_MODE                      CR_TRACE_MODE_MSK  
#define CR_TRACE_MODE_0                    (0X1UL << CR_TRACE_MODE_POS) 
#define CR_TRACE_MODE_1                    (0X2UL << CR_TRACE_MODE_POS) 

/********************  BIT DEFINITION FOR DBGMCU::APB1_FZ   ************/
#define APB1_FZ_DBG_TIM2_STOP_POS          (0U)                 
#define APB1_FZ_DBG_TIM2_STOP_MSK          (0X1UL << APB1_FZ_DBG_TIM2_STOP_POS) 
#define APB1_FZ_DBG_TIM2_STOP              APB1_FZ_DBG_TIM2_STOP_MSK 
#define APB1_FZ_DBG_TIM3_STOP_POS          (1U)                 
#define APB1_FZ_DBG_TIM3_STOP_MSK          (0X1UL << APB1_FZ_DBG_TIM3_STOP_POS) 
#define APB1_FZ_DBG_TIM3_STOP              APB1_FZ_DBG_TIM3_STOP_MSK 
#define APB1_FZ_DBG_TIM4_STOP_POS          (2U)                 
#define APB1_FZ_DBG_TIM4_STOP_MSK          (0X1UL << APB1_FZ_DBG_TIM4_STOP_POS) 
#define APB1_FZ_DBG_TIM4_STOP              APB1_FZ_DBG_TIM4_STOP_MSK 
#define APB1_FZ_DBG_TIM5_STOP_POS          (3U)                 
#define APB1_FZ_DBG_TIM5_STOP_MSK          (0X1UL << APB1_FZ_DBG_TIM5_STOP_POS) 
#define APB1_FZ_DBG_TIM5_STOP              APB1_FZ_DBG_TIM5_STOP_MSK 
#define APB1_FZ_DBG_RTC_STOP_POS           (10U)                
#define APB1_FZ_DBG_RTC_STOP_MSK           (0X1UL << APB1_FZ_DBG_RTC_STOP_POS) 
#define APB1_FZ_DBG_RTC_STOP               APB1_FZ_DBG_RTC_STOP_MSK 
#define APB1_FZ_DBG_WWDG_STOP_POS          (11U)                
#define APB1_FZ_DBG_WWDG_STOP_MSK          (0X1UL << APB1_FZ_DBG_WWDG_STOP_POS) 
#define APB1_FZ_DBG_WWDG_STOP              APB1_FZ_DBG_WWDG_STOP_MSK 
#define APB1_FZ_DBG_IWDG_STOP_POS          (12U)                
#define APB1_FZ_DBG_IWDG_STOP_MSK          (0X1UL << APB1_FZ_DBG_IWDG_STOP_POS) 
#define APB1_FZ_DBG_IWDG_STOP              APB1_FZ_DBG_IWDG_STOP_MSK 
#define APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_POS (21U)    
            
#define APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_MSK (0X1UL << \
                                           APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_POS) 

#define APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT     APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_MSK 
#define APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_POS (22U) 

#define APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_MSK (0X1UL << \
                                           APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_POS) 

#define APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT     APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_MSK 
#define APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_POS (23U) 

#define APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_MSK (0X1UL << \
                                           APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_POS) 

#define APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT     APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_MSK 

/********************  BIT DEFINITION FOR DBGMCU::APB2_FZ   ************/
#define APB2_FZ_DBG_TIM1_STOP_POS          (0U)                 
#define APB2_FZ_DBG_TIM1_STOP_MSK          (0X1UL << APB2_FZ_DBG_TIM1_STOP_POS) 
#define APB2_FZ_DBG_TIM1_STOP              APB2_FZ_DBG_TIM1_STOP_MSK 
#define APB2_FZ_DBG_TIM9_STOP_POS          (16U) 

#define APB2_FZ_DBG_TIM9_STOP_MSK          (0X1UL << APB2_FZ_DBG_TIM9_STOP_POS) 
#define APB2_FZ_DBG_TIM9_STOP              APB2_FZ_DBG_TIM9_STOP_MSK 
#define APB2_FZ_DBG_TIM10_STOP_POS         (17U)    

#define APB2_FZ_DBG_TIM10_STOP_MSK         (0X1UL << \
                                           APB2_FZ_DBG_TIM10_STOP_POS) 

#define APB2_FZ_DBG_TIM10_STOP             APB2_FZ_DBG_TIM10_STOP_MSK 
#define APB2_FZ_DBG_TIM11_STOP_POS         (18U)      

#define APB2_FZ_DBG_TIM11_STOP_MSK         (0X1UL << \
                                           APB2_FZ_DBG_TIM11_STOP_POS)

#define APB2_FZ_DBG_TIM11_STOP             APB2_FZ_DBG_TIM11_STOP_MSK 

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_MCU_DBG_REGISTER_MASKS */