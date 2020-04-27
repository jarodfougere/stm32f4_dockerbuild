#ifndef RIMOT_GPIO_REGISTER_MASKS
#define RIMOT_GPIO_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/******************  BITS DEFINITION FOR GPIO::MODER   *****************/
#define MODER_POS(pin)  (2 * (pin))
#define MODER_MSK(pin)  (0x3UL << (MODER_POS((pin))))
#define MODER(pin)      ((MODER_MSK((pin))))

/******************  BITS DEFINITION FOR GPIO::OTYPER   ****************/
#define OTYPER_POS(pin)             ((pin))
#define OTYPER_MSK(pin)             (0x1UL << (OTYPER_POS((pin))))
#define OTYPER(pin)                 ((OTYPER_MSK((pin))))

/******************  BITS DEFINITION FOR GPIO::OSPEEDR   ***************/
#define OSPEEDR_POS(pin)            ((2 * (pin)))
#define OSPEEDR_MSK(pin)            (0x3UL << (OSPEEDR_POS((pin))))
#define OSPEEDR(pin)                ((OSPEEDR_MSK((pin))))

/******************  BITS DEFINITION FOR GPIO::PUPDR   *****************/
#define PUPDR_POS(pin)              ((2 * (pin)))
#define PUPDR_MSK(pin)              (0x3UL << (PUPDR_POS((pin))))
#define PUPDR(pin)                  ((PUPDR_MSK((pin))))  


/******************  BITS DEFINITION FOR GPIO::IDR   *******************/
#define IDR_POS(pin)                ((pin))
#define IDR_MSK(pin)                (0x1UL << (IDR_POS((pin))))
#define IDR(pin)                    ((IDR_MSK((pin))))

/******************  BITS DEFINITION FOR GPIO::ODR   *******************/
#define ODR_POS(pin)                ((pin))
#define ODR_MSK(pin)                (0x1UL << (ODR_POS((pin))))
#define ODR(pin)                    ((ODR_MSK((pin))))

/******************  BITS DEFINITION FOR GPIO::BSRR   ******************/
#define BSRR_SET_POS(pin)           (((pin)))
#define BSRR_SET_MSK(pin)           (0x1UL << (BSRR_SET_POS((pin))))
#define BSRR_SET(pin)               ((BSRR_SET_MSK((pin))))

#define BSRR_RST_POS(pin)           ((16UL + (pin)))
#define BSRR_RST_MSK(pin)           (0X1UL << (BSRR_RST_POS((pin))))
#define BSRR_RST(pin)               ((BSRR_RST_MSK((pin))))

/****************** BIT DEFINITION FOR GPIO::LCKR  *********************/
#define LCKR_LCK0_POS               (0U)                                  
#define LCKR_LCK0_MSK               (0X1UL << LCKR_LCK0_POS)          
#define LCKR_LCK0                   LCKR_LCK0_MSK                    
#define LCKR_LCK1_POS               (1U)                                  
#define LCKR_LCK1_MSK               (0X1UL << LCKR_LCK1_POS)          
#define LCKR_LCK1                   LCKR_LCK1_MSK                    
#define LCKR_LCK2_POS               (2U)                                  
#define LCKR_LCK2_MSK               (0X1UL << LCKR_LCK2_POS)          
#define LCKR_LCK2                   LCKR_LCK2_MSK                    
#define LCKR_LCK3_POS               (3U)                                  
#define LCKR_LCK3_MSK               (0X1UL << LCKR_LCK3_POS)          
#define LCKR_LCK3                   LCKR_LCK3_MSK                    
#define LCKR_LCK4_POS               (4U)                                  
#define LCKR_LCK4_MSK               (0X1UL << LCKR_LCK4_POS)          
#define LCKR_LCK4                   LCKR_LCK4_MSK                    
#define LCKR_LCK5_POS               (5U)                                  
#define LCKR_LCK5_MSK               (0X1UL << LCKR_LCK5_POS)          
#define LCKR_LCK5                   LCKR_LCK5_MSK                    
#define LCKR_LCK6_POS               (6U)                                  
#define LCKR_LCK6_MSK               (0X1UL << LCKR_LCK6_POS)          
#define LCKR_LCK6                   LCKR_LCK6_MSK                    
#define LCKR_LCK7_POS               (7U)                                  
#define LCKR_LCK7_MSK               (0X1UL << LCKR_LCK7_POS)          
#define LCKR_LCK7                   LCKR_LCK7_MSK                    
#define LCKR_LCK8_POS               (8U)                                  
#define LCKR_LCK8_MSK               (0X1UL << LCKR_LCK8_POS)          
#define LCKR_LCK8                   LCKR_LCK8_MSK                    
#define LCKR_LCK9_POS               (9U)                                  
#define LCKR_LCK9_MSK               (0X1UL << LCKR_LCK9_POS)          
#define LCKR_LCK9                   LCKR_LCK9_MSK                    
#define LCKR_LCK10_POS              (10U)                                 
#define LCKR_LCK10_MSK              (0X1UL << LCKR_LCK10_POS)         
#define LCKR_LCK10                  LCKR_LCK10_MSK                   
#define LCKR_LCK11_POS              (11U)                                 
#define LCKR_LCK11_MSK              (0X1UL << LCKR_LCK11_POS)         
#define LCKR_LCK11                  LCKR_LCK11_MSK                   
#define LCKR_LCK12_POS              (12U)                                 
#define LCKR_LCK12_MSK              (0X1UL << LCKR_LCK12_POS)         
#define LCKR_LCK12                  LCKR_LCK12_MSK                   
#define LCKR_LCK13_POS              (13U)                                 
#define LCKR_LCK13_MSK              (0X1UL << LCKR_LCK13_POS)         
#define LCKR_LCK13                  LCKR_LCK13_MSK                   
#define LCKR_LCK14_POS              (14U)                                 
#define LCKR_LCK14_MSK              (0X1UL << LCKR_LCK14_POS)         
#define LCKR_LCK14                  LCKR_LCK14_MSK                   
#define LCKR_LCK15_POS              (15U)                                 
#define LCKR_LCK15_MSK              (0X1UL << LCKR_LCK15_POS)         
#define LCKR_LCK15                  LCKR_LCK15_MSK                   
#define LCKR_LCKK_POS               (16U)                                 
#define LCKR_LCKK_MSK               (0X1UL << LCKR_LCKK_POS)          
#define LCKR_LCKK                   LCKR_LCKK_MSK                    


/************ BIT DEFINITION FOR GPIO::AFRL AND GPIO::AFRH *************/
#define AFRL_PINBIT_MAX 7 /* AFRL only controls pins 0-> 8 */

#define AFR_POS(bit)                (4 * (((bit) > (AFRL_PINBIT_MAX)) ?     \
                                    ((bit) - (AFRL_PINBIT_MAX + 1)) : (bit)))
#define AFR_MSK(bit)                (0xFUL << (AFR_POS((bit))))
#define AFR(bit)                    ((AFR_MSK((bit))))


/****************** BIT DEFINITION FOR GPIO::AFRL  *********************/
#define AFRL_AFSEL0_POS             (0U)                                  
#define AFRL_AFSEL0_MSK             (0XFUL << AFRL_AFSEL0_POS)        
#define AFRL_AFSEL0                 AFRL_AFSEL0_MSK                  
#define AFRL_AFSEL0_0               (0X1UL << AFRL_AFSEL0_POS)        
#define AFRL_AFSEL0_1               (0X2UL << AFRL_AFSEL0_POS)        
#define AFRL_AFSEL0_2               (0X4UL << AFRL_AFSEL0_POS)        
#define AFRL_AFSEL0_3               (0X8UL << AFRL_AFSEL0_POS)        
#define AFRL_AFSEL1_POS             (4U)                                  
#define AFRL_AFSEL1_MSK             (0XFUL << AFRL_AFSEL1_POS)        
#define AFRL_AFSEL1                 AFRL_AFSEL1_MSK                  
#define AFRL_AFSEL1_0               (0X1UL << AFRL_AFSEL1_POS)        
#define AFRL_AFSEL1_1               (0X2UL << AFRL_AFSEL1_POS)        
#define AFRL_AFSEL1_2               (0X4UL << AFRL_AFSEL1_POS)        
#define AFRL_AFSEL1_3               (0X8UL << AFRL_AFSEL1_POS)        
#define AFRL_AFSEL2_POS             (8U)                                  
#define AFRL_AFSEL2_MSK             (0XFUL << AFRL_AFSEL2_POS)        
#define AFRL_AFSEL2                 AFRL_AFSEL2_MSK                  
#define AFRL_AFSEL2_0               (0X1UL << AFRL_AFSEL2_POS)        
#define AFRL_AFSEL2_1               (0X2UL << AFRL_AFSEL2_POS)        
#define AFRL_AFSEL2_2               (0X4UL << AFRL_AFSEL2_POS)        
#define AFRL_AFSEL2_3               (0X8UL << AFRL_AFSEL2_POS)        
#define AFRL_AFSEL3_POS             (12U)                                 
#define AFRL_AFSEL3_MSK             (0XFUL << AFRL_AFSEL3_POS)        
#define AFRL_AFSEL3                 AFRL_AFSEL3_MSK                  
#define AFRL_AFSEL3_0               (0X1UL << AFRL_AFSEL3_POS)        
#define AFRL_AFSEL3_1               (0X2UL << AFRL_AFSEL3_POS)        
#define AFRL_AFSEL3_2               (0X4UL << AFRL_AFSEL3_POS)        
#define AFRL_AFSEL3_3               (0X8UL << AFRL_AFSEL3_POS)        
#define AFRL_AFSEL4_POS             (16U)                                 
#define AFRL_AFSEL4_MSK             (0XFUL << AFRL_AFSEL4_POS)        
#define AFRL_AFSEL4                 AFRL_AFSEL4_MSK                  
#define AFRL_AFSEL4_0               (0X1UL << AFRL_AFSEL4_POS)        
#define AFRL_AFSEL4_1               (0X2UL << AFRL_AFSEL4_POS)        
#define AFRL_AFSEL4_2               (0X4UL << AFRL_AFSEL4_POS)        
#define AFRL_AFSEL4_3               (0X8UL << AFRL_AFSEL4_POS)        
#define AFRL_AFSEL5_POS             (20U)                                 
#define AFRL_AFSEL5_MSK             (0XFUL << AFRL_AFSEL5_POS)        
#define AFRL_AFSEL5                 AFRL_AFSEL5_MSK                  
#define AFRL_AFSEL5_0               (0X1UL << AFRL_AFSEL5_POS)        
#define AFRL_AFSEL5_1               (0X2UL << AFRL_AFSEL5_POS)        
#define AFRL_AFSEL5_2               (0X4UL << AFRL_AFSEL5_POS)        
#define AFRL_AFSEL5_3               (0X8UL << AFRL_AFSEL5_POS)        
#define AFRL_AFSEL6_POS             (24U)                                 
#define AFRL_AFSEL6_MSK             (0XFUL << AFRL_AFSEL6_POS)        
#define AFRL_AFSEL6                 AFRL_AFSEL6_MSK                  
#define AFRL_AFSEL6_0               (0X1UL << AFRL_AFSEL6_POS)        
#define AFRL_AFSEL6_1               (0X2UL << AFRL_AFSEL6_POS)        
#define AFRL_AFSEL6_2               (0X4UL << AFRL_AFSEL6_POS)        
#define AFRL_AFSEL6_3               (0X8UL << AFRL_AFSEL6_POS)        
#define AFRL_AFSEL7_POS             (28U)                                 
#define AFRL_AFSEL7_MSK             (0XFUL << AFRL_AFSEL7_POS)        
#define AFRL_AFSEL7                 AFRL_AFSEL7_MSK                  
#define AFRL_AFSEL7_0               (0X1UL << AFRL_AFSEL7_POS)        
#define AFRL_AFSEL7_1               (0X2UL << AFRL_AFSEL7_POS)        
#define AFRL_AFSEL7_2               (0X4UL << AFRL_AFSEL7_POS)        
#define AFRL_AFSEL7_3               (0X8UL << AFRL_AFSEL7_POS)        


/****************** BIT DEFINITION FOR GPIO::AFRH  *********************/
#define AFRH_AFSEL8_POS             (0U)                                  
#define AFRH_AFSEL8_MSK             (0XFUL << AFRH_AFSEL8_POS)        
#define AFRH_AFSEL8                 AFRH_AFSEL8_MSK                  
#define AFRH_AFSEL8_0               (0X1UL << AFRH_AFSEL8_POS)        
#define AFRH_AFSEL8_1               (0X2UL << AFRH_AFSEL8_POS)        
#define AFRH_AFSEL8_2               (0X4UL << AFRH_AFSEL8_POS)        
#define AFRH_AFSEL8_3               (0X8UL << AFRH_AFSEL8_POS)        
#define AFRH_AFSEL9_POS             (4U)                                  
#define AFRH_AFSEL9_MSK             (0XFUL << AFRH_AFSEL9_POS)        
#define AFRH_AFSEL9                 AFRH_AFSEL9_MSK                  
#define AFRH_AFSEL9_0               (0X1UL << AFRH_AFSEL9_POS)        
#define AFRH_AFSEL9_1               (0X2UL << AFRH_AFSEL9_POS)        
#define AFRH_AFSEL9_2               (0X4UL << AFRH_AFSEL9_POS)        
#define AFRH_AFSEL9_3               (0X8UL << AFRH_AFSEL9_POS)        
#define AFRH_AFSEL10_POS            (8U)                                  
#define AFRH_AFSEL10_MSK            (0XFUL << AFRH_AFSEL10_POS)       
#define AFRH_AFSEL10                AFRH_AFSEL10_MSK                 
#define AFRH_AFSEL10_0              (0X1UL << AFRH_AFSEL10_POS)       
#define AFRH_AFSEL10_1              (0X2UL << AFRH_AFSEL10_POS)       
#define AFRH_AFSEL10_2              (0X4UL << AFRH_AFSEL10_POS)       
#define AFRH_AFSEL10_3              (0X8UL << AFRH_AFSEL10_POS)       
#define AFRH_AFSEL11_POS            (12U)                                 
#define AFRH_AFSEL11_MSK            (0XFUL << AFRH_AFSEL11_POS)       
#define AFRH_AFSEL11                AFRH_AFSEL11_MSK                 
#define AFRH_AFSEL11_0              (0X1UL << AFRH_AFSEL11_POS)       
#define AFRH_AFSEL11_1              (0X2UL << AFRH_AFSEL11_POS)       
#define AFRH_AFSEL11_2              (0X4UL << AFRH_AFSEL11_POS)       
#define AFRH_AFSEL11_3              (0X8UL << AFRH_AFSEL11_POS)       
#define AFRH_AFSEL12_POS            (16U)                                 
#define AFRH_AFSEL12_MSK            (0XFUL << AFRH_AFSEL12_POS)       
#define AFRH_AFSEL12                AFRH_AFSEL12_MSK                 
#define AFRH_AFSEL12_0              (0X1UL << AFRH_AFSEL12_POS)       
#define AFRH_AFSEL12_1              (0X2UL << AFRH_AFSEL12_POS)       
#define AFRH_AFSEL12_2              (0X4UL << AFRH_AFSEL12_POS)       
#define AFRH_AFSEL12_3              (0X8UL << AFRH_AFSEL12_POS)       
#define AFRH_AFSEL13_POS            (20U)                                 
#define AFRH_AFSEL13_MSK            (0XFUL << AFRH_AFSEL13_POS)       
#define AFRH_AFSEL13                AFRH_AFSEL13_MSK                 
#define AFRH_AFSEL13_0              (0X1UL << AFRH_AFSEL13_POS)       
#define AFRH_AFSEL13_1              (0X2UL << AFRH_AFSEL13_POS)       
#define AFRH_AFSEL13_2              (0X4UL << AFRH_AFSEL13_POS)       
#define AFRH_AFSEL13_3              (0X8UL << AFRH_AFSEL13_POS)       
#define AFRH_AFSEL14_POS            (24U)                                 
#define AFRH_AFSEL14_MSK            (0XFUL << AFRH_AFSEL14_POS)       
#define AFRH_AFSEL14                AFRH_AFSEL14_MSK                 
#define AFRH_AFSEL14_0              (0X1UL << AFRH_AFSEL14_POS)       
#define AFRH_AFSEL14_1              (0X2UL << AFRH_AFSEL14_POS)       
#define AFRH_AFSEL14_2              (0X4UL << AFRH_AFSEL14_POS)       
#define AFRH_AFSEL14_3              (0X8UL << AFRH_AFSEL14_POS)       
#define AFRH_AFSEL15_POS            (28U)                                 
#define AFRH_AFSEL15_MSK            (0XFUL << AFRH_AFSEL15_POS)       
#define AFRH_AFSEL15                AFRH_AFSEL15_MSK                 
#define AFRH_AFSEL15_0              (0X1UL << AFRH_AFSEL15_POS)       
#define AFRH_AFSEL15_1              (0X2UL << AFRH_AFSEL15_POS)       
#define AFRH_AFSEL15_2              (0X4UL << AFRH_AFSEL15_POS)       
#define AFRH_AFSEL15_3              (0X8UL << AFRH_AFSEL15_POS)       


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_GPIO_REGISTER_MASKS */
