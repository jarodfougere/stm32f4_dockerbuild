#ifndef RIMOT_SYSCFG_REGISTER_MASKS
#define RIMOT_SYSCFG_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/******************  BIT DEFINITION FOR SYSCFG::MEMRMP   ***************/
#define MEMRMP_MEM_MODE_POS           (0U)                              
#define MEMRMP_MEM_MODE_MSK           (0X3UL << MEMRMP_MEM_MODE_POS) 
#define MEMRMP_MEM_MODE               MEMRMP_MEM_MODE_MSK        
#define MEMRMP_MEM_MODE_0             (0X1UL << MEMRMP_MEM_MODE_POS) 
#define MEMRMP_MEM_MODE_1             (0X2UL << MEMRMP_MEM_MODE_POS) 

/******************  BIT DEFINITION FOR SYSCFG::PMC   ******************/
#define PMC_ADC1DC2_POS               (16U)                             
#define PMC_ADC1DC2_MSK               (0X1UL << PMC_ADC1DC2_POS)  
#define PMC_ADC1DC2                   PMC_ADC1DC2_MSK            

/*****************  BIT DEFINITION FOR SYSCFG::EXTICR1   ***************/
#define EXTICR1_EXTI0_POS             (0U)                              
#define EXTICR1_EXTI0_MSK             (0XFUL << EXTICR1_EXTI0_POS) 
#define EXTICR1_EXTI0                 EXTICR1_EXTI0_MSK          
#define EXTICR1_EXTI1_POS             (4U)                              
#define EXTICR1_EXTI1_MSK             (0XFUL << EXTICR1_EXTI1_POS) 
#define EXTICR1_EXTI1                 EXTICR1_EXTI1_MSK          
#define EXTICR1_EXTI2_POS             (8U)                              
#define EXTICR1_EXTI2_MSK             (0XFUL << EXTICR1_EXTI2_POS) 
#define EXTICR1_EXTI2                 EXTICR1_EXTI2_MSK          
#define EXTICR1_EXTI3_POS             (12U)                             
#define EXTICR1_EXTI3_MSK             (0XFUL << EXTICR1_EXTI3_POS) 
#define EXTICR1_EXTI3                 EXTICR1_EXTI3_MSK  

/**
  *    EXTI0 CONFIGURATION  
  */
#define EXTICR1_EXTI0_PA              0X0000U                           
#define EXTICR1_EXTI0_PB              0X0001U                           
#define EXTICR1_EXTI0_PC              0X0002U                           
#define EXTICR1_EXTI0_PD              0X0003U                           
#define EXTICR1_EXTI0_PE              0X0004U                           
#define EXTICR1_EXTI0_PH              0X0007U                           

/**
  *    EXTI1 CONFIGURATION  
  */
#define EXTICR1_EXTI1_PA              0X0000U                           
#define EXTICR1_EXTI1_PB              0X0010U                           
#define EXTICR1_EXTI1_PC              0X0020U                           
#define EXTICR1_EXTI1_PD              0X0030U                           
#define EXTICR1_EXTI1_PE              0X0040U                           
#define EXTICR1_EXTI1_PH              0X0070U                           

/**
  *    EXTI2 CONFIGURATION  
  */
#define EXTICR1_EXTI2_PA              0X0000U                           
#define EXTICR1_EXTI2_PB              0X0100U                           
#define EXTICR1_EXTI2_PC              0X0200U                           
#define EXTICR1_EXTI2_PD              0X0300U                           
#define EXTICR1_EXTI2_PE              0X0400U                           
#define EXTICR1_EXTI2_PH              0X0700U                           

/**
  *    EXTI3 CONFIGURATION  
  */
#define EXTICR1_EXTI3_PA              0X0000U                           
#define EXTICR1_EXTI3_PB              0X1000U                           
#define EXTICR1_EXTI3_PC              0X2000U                           
#define EXTICR1_EXTI3_PD              0X3000U                           
#define EXTICR1_EXTI3_PE              0X4000U                           
#define EXTICR1_EXTI3_PH              0X7000U                           

/*****************  BIT DEFINITION FOR SYSCFG::EXTICR2   ***************/
#define EXTICR2_EXTI4_POS             (0U)                              
#define EXTICR2_EXTI4_MSK             (0XFUL << EXTICR2_EXTI4_POS) 
#define EXTICR2_EXTI4                 EXTICR2_EXTI4_MSK          
#define EXTICR2_EXTI5_POS             (4U)                              
#define EXTICR2_EXTI5_MSK             (0XFUL << EXTICR2_EXTI5_POS) 
#define EXTICR2_EXTI5                 EXTICR2_EXTI5_MSK          
#define EXTICR2_EXTI6_POS             (8U)                              
#define EXTICR2_EXTI6_MSK             (0XFUL << EXTICR2_EXTI6_POS) 
#define EXTICR2_EXTI6                 EXTICR2_EXTI6_MSK          
#define EXTICR2_EXTI7_POS             (12U)                             
#define EXTICR2_EXTI7_MSK             (0XFUL << EXTICR2_EXTI7_POS) 
#define EXTICR2_EXTI7                 EXTICR2_EXTI7_MSK          

/**
  *    EXTI4 CONFIGURATION  
  */
#define EXTICR2_EXTI4_PA              0X0000U                           
#define EXTICR2_EXTI4_PB              0X0001U                           
#define EXTICR2_EXTI4_PC              0X0002U                           
#define EXTICR2_EXTI4_PD              0X0003U                           
#define EXTICR2_EXTI4_PE              0X0004U                           
#define EXTICR2_EXTI4_PH              0X0007U                           

/**
  *    EXTI5 CONFIGURATION  
  */
#define EXTICR2_EXTI5_PA              0X0000U                           
#define EXTICR2_EXTI5_PB              0X0010U                           
#define EXTICR2_EXTI5_PC              0X0020U                           
#define EXTICR2_EXTI5_PD              0X0030U                           
#define EXTICR2_EXTI5_PE              0X0040U                           
#define EXTICR2_EXTI5_PH              0X0070U                           

/**
  *    EXTI6 CONFIGURATION  
  */
#define EXTICR2_EXTI6_PA              0X0000U                           
#define EXTICR2_EXTI6_PB              0X0100U                           
#define EXTICR2_EXTI6_PC              0X0200U                           
#define EXTICR2_EXTI6_PD              0X0300U                           
#define EXTICR2_EXTI6_PE              0X0400U                           
#define EXTICR2_EXTI6_PH              0X0700U                           

/**
  *    EXTI7 CONFIGURATION  
  */
#define EXTICR2_EXTI7_PA              0X0000U                           
#define EXTICR2_EXTI7_PB              0X1000U                           
#define EXTICR2_EXTI7_PC              0X2000U                           
#define EXTICR2_EXTI7_PD              0X3000U                           
#define EXTICR2_EXTI7_PE              0X4000U                           
#define EXTICR2_EXTI7_PH              0X7000U                           

/*****************  BIT DEFINITION FOR SYSCFG::EXTICR3   ***************/
#define EXTICR3_EXTI8_POS             (0U)                              
#define EXTICR3_EXTI8_MSK             (0XFUL << EXTICR3_EXTI8_POS) 
#define EXTICR3_EXTI8                 EXTICR3_EXTI8_MSK          
#define EXTICR3_EXTI9_POS             (4U)                              
#define EXTICR3_EXTI9_MSK             (0XFUL << EXTICR3_EXTI9_POS) 
#define EXTICR3_EXTI9                 EXTICR3_EXTI9_MSK          
#define EXTICR3_EXTI10_POS            (8U)                              
#define EXTICR3_EXTI10_MSK            (0XFUL << EXTICR3_EXTI10_POS) 
#define EXTICR3_EXTI10                EXTICR3_EXTI10_MSK         
#define EXTICR3_EXTI11_POS            (12U)                             
#define EXTICR3_EXTI11_MSK            (0XFUL << EXTICR3_EXTI11_POS) 
#define EXTICR3_EXTI11                EXTICR3_EXTI11_MSK         

/**
  *    EXTI8 CONFIGURATION  
  */
#define EXTICR3_EXTI8_PA              0X0000U                           
#define EXTICR3_EXTI8_PB              0X0001U                           
#define EXTICR3_EXTI8_PC              0X0002U                           
#define EXTICR3_EXTI8_PD              0X0003U                           
#define EXTICR3_EXTI8_PE              0X0004U                           
#define EXTICR3_EXTI8_PH              0X0007U                           

/**
  *    EXTI9 CONFIGURATION  
  */
#define EXTICR3_EXTI9_PA              0X0000U                           
#define EXTICR3_EXTI9_PB              0X0010U                           
#define EXTICR3_EXTI9_PC              0X0020U                           
#define EXTICR3_EXTI9_PD              0X0030U                           
#define EXTICR3_EXTI9_PE              0X0040U                           
#define EXTICR3_EXTI9_PH              0X0070U                           

/**
  *    EXTI10 CONFIGURATION  
  */
#define EXTICR3_EXTI10_PA             0X0000U                           
#define EXTICR3_EXTI10_PB             0X0100U                           
#define EXTICR3_EXTI10_PC             0X0200U                           
#define EXTICR3_EXTI10_PD             0X0300U                           
#define EXTICR3_EXTI10_PE             0X0400U                           
#define EXTICR3_EXTI10_PH             0X0700U                           

/**
  *    EXTI11 CONFIGURATION  
  */
#define EXTICR3_EXTI11_PA             0X0000U                           
#define EXTICR3_EXTI11_PB             0X1000U                           
#define EXTICR3_EXTI11_PC             0X2000U                           
#define EXTICR3_EXTI11_PD             0X3000U                           
#define EXTICR3_EXTI11_PE             0X4000U                           
#define EXTICR3_EXTI11_PH             0X7000U                           

/*****************  BIT DEFINITION FOR SYSCFG::EXTICR4   ***************/
#define EXTICR4_EXTI12_POS            (0U)                              
#define EXTICR4_EXTI12_MSK            (0XFUL << EXTICR4_EXTI12_POS) 
#define EXTICR4_EXTI12                EXTICR4_EXTI12_MSK         
#define EXTICR4_EXTI13_POS            (4U)                              
#define EXTICR4_EXTI13_MSK            (0XFUL << EXTICR4_EXTI13_POS) 
#define EXTICR4_EXTI13                EXTICR4_EXTI13_MSK         
#define EXTICR4_EXTI14_POS            (8U)                              
#define EXTICR4_EXTI14_MSK            (0XFUL << EXTICR4_EXTI14_POS) 
#define EXTICR4_EXTI14                EXTICR4_EXTI14_MSK         
#define EXTICR4_EXTI15_POS            (12U)                             
#define EXTICR4_EXTI15_MSK            (0XFUL << EXTICR4_EXTI15_POS) 
#define EXTICR4_EXTI15                EXTICR4_EXTI15_MSK         

/**
  *    EXTI12 CONFIGURATION  
  */
#define EXTICR4_EXTI12_PA             0X0000U                           
#define EXTICR4_EXTI12_PB             0X0001U                           
#define EXTICR4_EXTI12_PC             0X0002U                           
#define EXTICR4_EXTI12_PD             0X0003U                           
#define EXTICR4_EXTI12_PE             0X0004U                           
#define EXTICR4_EXTI12_PH             0X0007U                           

/**
  *    EXTI13 CONFIGURATION  
  */
#define EXTICR4_EXTI13_PA             0X0000U                           
#define EXTICR4_EXTI13_PB             0X0010U                           
#define EXTICR4_EXTI13_PC             0X0020U                           
#define EXTICR4_EXTI13_PD             0X0030U                           
#define EXTICR4_EXTI13_PE             0X0040U                           
#define EXTICR4_EXTI13_PH             0X0070U                           

/**
  *    EXTI14 CONFIGURATION  
  */
#define EXTICR4_EXTI14_PA             0X0000U                           
#define EXTICR4_EXTI14_PB             0X0100U                           
#define EXTICR4_EXTI14_PC             0X0200U                           
#define EXTICR4_EXTI14_PD             0X0300U                           
#define EXTICR4_EXTI14_PE             0X0400U                           
#define EXTICR4_EXTI14_PH             0X0700U                           

/**
  *    EXTI15 CONFIGURATION  
  */
#define EXTICR4_EXTI15_PA             0X0000U                           
#define EXTICR4_EXTI15_PB             0X1000U                           
#define EXTICR4_EXTI15_PC             0X2000U                           
#define EXTICR4_EXTI15_PD             0X3000U                           
#define EXTICR4_EXTI15_PE             0X4000U                           
#define EXTICR4_EXTI15_PH             0X7000U                           

/******************  BIT DEFINITION FOR SYSCFG::CMPCR   ****************/
#define CMPCR_CMP_PD_POS              (0U)                              
#define CMPCR_CMP_PD_MSK              (0X1UL << CMPCR_CMP_PD_POS) 
#define CMPCR_CMP_PD                  CMPCR_CMP_PD_MSK           
#define CMPCR_READY_POS               (8U)                              
#define CMPCR_READY_MSK               (0X1UL << CMPCR_READY_POS)  
#define CMPCR_READY                   CMPCR_READY_MSK            

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_SYSCFG_REGISTER_MASKS */