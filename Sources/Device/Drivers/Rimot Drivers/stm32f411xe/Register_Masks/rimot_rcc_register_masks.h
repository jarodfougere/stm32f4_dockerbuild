#ifndef RIMOT_RCC_REGISTER_MASKS
#define RIMOT_RCC_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/********************  BIT DEFINITION FOR RCC::CR   ********************/
#define CR_HSION_POS                   (0U)                                
#define CR_HSION_MSK                   (0X1UL << CR_HSION_POS)          
#define CR_HSION                       CR_HSION_MSK                    
#define CR_HSIRDY_POS                  (1U)                                
#define CR_HSIRDY_MSK                  (0X1UL << CR_HSIRDY_POS)         
#define CR_HSIRDY                      CR_HSIRDY_MSK                   

#define CR_HSITRIM_POS                 (3U)                                
#define CR_HSITRIM_MSK                 (0X1FUL << CR_HSITRIM_POS)       
#define CR_HSITRIM                     CR_HSITRIM_MSK                  
#define CR_HSITRIM_0                   (0X01UL << CR_HSITRIM_POS)       
#define CR_HSITRIM_1                   (0X02UL << CR_HSITRIM_POS)       
#define CR_HSITRIM_2                   (0X04UL << CR_HSITRIM_POS)       
#define CR_HSITRIM_3                   (0X08UL << CR_HSITRIM_POS)       
#define CR_HSITRIM_4                   (0X10UL << CR_HSITRIM_POS)       

#define CR_HSICAL_POS                  (8U)                                
#define CR_HSICAL_MSK                  (0XFFUL << CR_HSICAL_POS)        
#define CR_HSICAL                      CR_HSICAL_MSK                   
#define CR_HSICAL_0                    (0X01UL << CR_HSICAL_POS)        
#define CR_HSICAL_1                    (0X02UL << CR_HSICAL_POS)        
#define CR_HSICAL_2                    (0X04UL << CR_HSICAL_POS)        
#define CR_HSICAL_3                    (0X08UL << CR_HSICAL_POS)        
#define CR_HSICAL_4                    (0X10UL << CR_HSICAL_POS)        
#define CR_HSICAL_5                    (0X20UL << CR_HSICAL_POS)        
#define CR_HSICAL_6                    (0X40UL << CR_HSICAL_POS)        
#define CR_HSICAL_7                    (0X80UL << CR_HSICAL_POS)        

#define CR_HSEON_POS                   (16U)                               
#define CR_HSEON_MSK                   (0X1UL << CR_HSEON_POS)          
#define CR_HSEON                       CR_HSEON_MSK                    
#define CR_HSERDY_POS                  (17U)                               
#define CR_HSERDY_MSK                  (0X1UL << CR_HSERDY_POS)         
#define CR_HSERDY                      CR_HSERDY_MSK                   
#define CR_HSEBYP_POS                  (18U)                               
#define CR_HSEBYP_MSK                  (0X1UL << CR_HSEBYP_POS)         
#define CR_HSEBYP                      CR_HSEBYP_MSK                   
#define CR_CSSON_POS                   (19U)                               
#define CR_CSSON_MSK                   (0X1UL << CR_CSSON_POS)          
#define CR_CSSON                       CR_CSSON_MSK                    
#define CR_PLLON_POS                   (24U)                               
#define CR_PLLON_MSK                   (0X1UL << CR_PLLON_POS)          
#define CR_PLLON                       CR_PLLON_MSK                    
#define CR_PLLRDY_POS                  (25U)                               
#define CR_PLLRDY_MSK                  (0X1UL << CR_PLLRDY_POS)         
#define CR_PLLRDY                      CR_PLLRDY_MSK                   
/*
 * @BRIEF SPECIFIC DEVICE FEATURE DEFINITIONS (NOT PRESENT ON ALL DEVICES IN THE STM32F4 SERIE)
 */
#define PLLI2S_SUPPORT                                                     

#define CR_PLLI2SON_POS                (26U)                               
#define CR_PLLI2SON_MSK                (0X1UL << CR_PLLI2SON_POS)       
#define CR_PLLI2SON                    CR_PLLI2SON_MSK                 
#define CR_PLLI2SRDY_POS               (27U)                               
#define CR_PLLI2SRDY_MSK               (0X1UL << CR_PLLI2SRDY_POS)      
#define CR_PLLI2SRDY                   CR_PLLI2SRDY_MSK                

/********************  BIT DEFINITION FOR RCC::PLLCFGR   ***************/
#define PLLCFGR_PLLM_POS               (0U)                                
#define PLLCFGR_PLLM_MSK               (0X3FUL << PLLCFGR_PLLM_POS)     
#define PLLCFGR_PLLM                   PLLCFGR_PLLM_MSK                
#define PLLCFGR_PLLM_0                 (0X01UL << PLLCFGR_PLLM_POS)     
#define PLLCFGR_PLLM_1                 (0X02UL << PLLCFGR_PLLM_POS)     
#define PLLCFGR_PLLM_2                 (0X04UL << PLLCFGR_PLLM_POS)     
#define PLLCFGR_PLLM_3                 (0X08UL << PLLCFGR_PLLM_POS)     
#define PLLCFGR_PLLM_4                 (0X10UL << PLLCFGR_PLLM_POS)     
#define PLLCFGR_PLLM_5                 (0X20UL << PLLCFGR_PLLM_POS)     

#define PLLCFGR_PLLN_POS               (6U)                                
#define PLLCFGR_PLLN_MSK               (0X1FFUL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN                   PLLCFGR_PLLN_MSK                
#define PLLCFGR_PLLN_0                 (0X001UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_1                 (0X002UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_2                 (0X004UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_3                 (0X008UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_4                 (0X010UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_5                 (0X020UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_6                 (0X040UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_7                 (0X080UL << PLLCFGR_PLLN_POS)    
#define PLLCFGR_PLLN_8                 (0X100UL << PLLCFGR_PLLN_POS)    

#define PLLCFGR_PLLP_POS               (16U)                               
#define PLLCFGR_PLLP_MSK               (0X3UL << PLLCFGR_PLLP_POS)      
#define PLLCFGR_PLLP                   PLLCFGR_PLLP_MSK                
#define PLLCFGR_PLLP_0                 (0X1UL << PLLCFGR_PLLP_POS)      
#define PLLCFGR_PLLP_1                 (0X2UL << PLLCFGR_PLLP_POS)      

#define PLLCFGR_PLLSRC_POS             (22U)                               
#define PLLCFGR_PLLSRC_MSK             (0X1UL << PLLCFGR_PLLSRC_POS)    
#define PLLCFGR_PLLSRC                 PLLCFGR_PLLSRC_MSK              
#define PLLCFGR_PLLSRC_HSE_POS         (22U)                               
#define PLLCFGR_PLLSRC_HSE_MSK         (0X1UL << PLLCFGR_PLLSRC_HSE_POS) 
#define PLLCFGR_PLLSRC_HSE             PLLCFGR_PLLSRC_HSE_MSK          
#define PLLCFGR_PLLSRC_HSI             0X00000000U                         

#define PLLCFGR_PLLQ_POS               (24U)                               
#define PLLCFGR_PLLQ_MSK               (0XFUL << PLLCFGR_PLLQ_POS)      
#define PLLCFGR_PLLQ                   PLLCFGR_PLLQ_MSK                
#define PLLCFGR_PLLQ_0                 (0X1UL << PLLCFGR_PLLQ_POS)      
#define PLLCFGR_PLLQ_1                 (0X2UL << PLLCFGR_PLLQ_POS)      
#define PLLCFGR_PLLQ_2                 (0X4UL << PLLCFGR_PLLQ_POS)      
#define PLLCFGR_PLLQ_3                 (0X8UL << PLLCFGR_PLLQ_POS)      


/********************  BIT DEFINITION FOR RCC::CFGR   ******************/

#define CFGR_SW_POS                    (0U)                                
#define CFGR_SW_MSK                    (0X3UL << CFGR_SW_POS)           
#define CFGR_SW                        CFGR_SW_MSK                     
#define CFGR_SW_0                      (0X1UL << CFGR_SW_POS)           
#define CFGR_SW_1                      (0X2UL << CFGR_SW_POS)           

#define CFGR_SW_HSI                    0X00000000U                         
#define CFGR_SW_HSE                    0X00000001U                         
#define CFGR_SW_PLL                    0X00000002U                         


#define CFGR_SWS_POS                   (2U)                                
#define CFGR_SWS_MSK                   (0X3UL << CFGR_SWS_POS)          
#define CFGR_SWS                       CFGR_SWS_MSK                    
#define CFGR_SWS_0                     (0X1UL << CFGR_SWS_POS)          
#define CFGR_SWS_1                     (0X2UL << CFGR_SWS_POS)          

#define CFGR_SWS_HSI                   0X00000000U                         
#define CFGR_SWS_HSE                   0X00000004U                         
#define CFGR_SWS_PLL                   0X00000008U                         


#define CFGR_HPRE_POS                  (4U)                                
#define CFGR_HPRE_MSK                  (0XFUL << CFGR_HPRE_POS)         
#define CFGR_HPRE                      CFGR_HPRE_MSK                   
#define CFGR_HPRE_0                    (0X1UL << CFGR_HPRE_POS)         
#define CFGR_HPRE_1                    (0X2UL << CFGR_HPRE_POS)         
#define CFGR_HPRE_2                    (0X4UL << CFGR_HPRE_POS)         
#define CFGR_HPRE_3                    (0X8UL << CFGR_HPRE_POS)         

#define CFGR_HPRE_DIV1                 0X00000000U                         
#define CFGR_HPRE_DIV2                 0X00000080U                         
#define CFGR_HPRE_DIV4                 0X00000090U                         
#define CFGR_HPRE_DIV8                 0X000000A0U                         
#define CFGR_HPRE_DIV16                0X000000B0U                         
#define CFGR_HPRE_DIV64                0X000000C0U                         
#define CFGR_HPRE_DIV128               0X000000D0U                         
#define CFGR_HPRE_DIV256               0X000000E0U                         
#define CFGR_HPRE_DIV512               0X000000F0U                         


#define CFGR_PPRE1_POS                 (10U)                               
#define CFGR_PPRE1_MSK                 (0X7UL << CFGR_PPRE1_POS)        
#define CFGR_PPRE1                     CFGR_PPRE1_MSK                  
#define CFGR_PPRE1_0                   (0X1UL << CFGR_PPRE1_POS)        
#define CFGR_PPRE1_1                   (0X2UL << CFGR_PPRE1_POS)        
#define CFGR_PPRE1_2                   (0X4UL << CFGR_PPRE1_POS)        

#define CFGR_PPRE1_DIV1                0X00000000U                         
#define CFGR_PPRE1_DIV2                0X00001000U                         
#define CFGR_PPRE1_DIV4                0X00001400U                         
#define CFGR_PPRE1_DIV8                0X00001800U                         
#define CFGR_PPRE1_DIV16               0X00001C00U                         


#define CFGR_PPRE2_POS                 (13U)                               
#define CFGR_PPRE2_MSK                 (0X7UL << CFGR_PPRE2_POS)        
#define CFGR_PPRE2                     CFGR_PPRE2_MSK                  
#define CFGR_PPRE2_0                   (0X1UL << CFGR_PPRE2_POS)        
#define CFGR_PPRE2_1                   (0X2UL << CFGR_PPRE2_POS)        
#define CFGR_PPRE2_2                   (0X4UL << CFGR_PPRE2_POS)        

#define CFGR_PPRE2_DIV1                0X00000000U                         
#define CFGR_PPRE2_DIV2                0X00008000U                         
#define CFGR_PPRE2_DIV4                0X0000A000U                         
#define CFGR_PPRE2_DIV8                0X0000C000U                         
#define CFGR_PPRE2_DIV16               0X0000E000U                         


#define CFGR_RTCPRE_POS                (16U)                               
#define CFGR_RTCPRE_MSK                (0X1FUL << CFGR_RTCPRE_POS)      
#define CFGR_RTCPRE                    CFGR_RTCPRE_MSK                 
#define CFGR_RTCPRE_0                  (0X01UL << CFGR_RTCPRE_POS)      
#define CFGR_RTCPRE_1                  (0X02UL << CFGR_RTCPRE_POS)      
#define CFGR_RTCPRE_2                  (0X04UL << CFGR_RTCPRE_POS)      
#define CFGR_RTCPRE_3                  (0X08UL << CFGR_RTCPRE_POS)      
#define CFGR_RTCPRE_4                  (0X10UL << CFGR_RTCPRE_POS)      


#define CFGR_MCO1_POS                  (21U)                               
#define CFGR_MCO1_MSK                  (0X3UL << CFGR_MCO1_POS)         
#define CFGR_MCO1                      CFGR_MCO1_MSK                   
#define CFGR_MCO1_0                    (0X1UL << CFGR_MCO1_POS)         
#define CFGR_MCO1_1                    (0X2UL << CFGR_MCO1_POS)         

#define CFGR_I2SSRC_POS                (23U)                               
#define CFGR_I2SSRC_MSK                (0X1UL << CFGR_I2SSRC_POS)       
#define CFGR_I2SSRC                    CFGR_I2SSRC_MSK                 

#define CFGR_MCO1PRE_POS               (24U)                               
#define CFGR_MCO1PRE_MSK               (0X7UL << CFGR_MCO1PRE_POS)      
#define CFGR_MCO1PRE                   CFGR_MCO1PRE_MSK                
#define CFGR_MCO1PRE_0                 (0X1UL << CFGR_MCO1PRE_POS)      
#define CFGR_MCO1PRE_1                 (0X2UL << CFGR_MCO1PRE_POS)      
#define CFGR_MCO1PRE_2                 (0X4UL << CFGR_MCO1PRE_POS)      

#define CFGR_MCO2PRE_POS               (27U)                               
#define CFGR_MCO2PRE_MSK               (0X7UL << CFGR_MCO2PRE_POS)      
#define CFGR_MCO2PRE                   CFGR_MCO2PRE_MSK                
#define CFGR_MCO2PRE_0                 (0X1UL << CFGR_MCO2PRE_POS)      
#define CFGR_MCO2PRE_1                 (0X2UL << CFGR_MCO2PRE_POS)      
#define CFGR_MCO2PRE_2                 (0X4UL << CFGR_MCO2PRE_POS)      

#define CFGR_MCO2_POS                  (30U)                               
#define CFGR_MCO2_MSK                  (0X3UL << CFGR_MCO2_POS)         
#define CFGR_MCO2                      CFGR_MCO2_MSK                   
#define CFGR_MCO2_0                    (0X1UL << CFGR_MCO2_POS)         
#define CFGR_MCO2_1                    (0X2UL << CFGR_MCO2_POS)         

/********************  BIT DEFINITION FOR RCC::CIR   *******************/
#define CIR_LSIRDYF_POS                (0U)                                
#define CIR_LSIRDYF_MSK                (0X1UL << CIR_LSIRDYF_POS)       
#define CIR_LSIRDYF                    CIR_LSIRDYF_MSK                 
#define CIR_LSERDYF_POS                (1U)                                
#define CIR_LSERDYF_MSK                (0X1UL << CIR_LSERDYF_POS)       
#define CIR_LSERDYF                    CIR_LSERDYF_MSK                 
#define CIR_HSIRDYF_POS                (2U)                                
#define CIR_HSIRDYF_MSK                (0X1UL << CIR_HSIRDYF_POS)       
#define CIR_HSIRDYF                    CIR_HSIRDYF_MSK                 
#define CIR_HSERDYF_POS                (3U)                                
#define CIR_HSERDYF_MSK                (0X1UL << CIR_HSERDYF_POS)       
#define CIR_HSERDYF                    CIR_HSERDYF_MSK                 
#define CIR_PLLRDYF_POS                (4U)                                
#define CIR_PLLRDYF_MSK                (0X1UL << CIR_PLLRDYF_POS)       
#define CIR_PLLRDYF                    CIR_PLLRDYF_MSK                 
#define CIR_PLLI2SRDYF_POS             (5U)                                
#define CIR_PLLI2SRDYF_MSK             (0X1UL << CIR_PLLI2SRDYF_POS)    
#define CIR_PLLI2SRDYF                 CIR_PLLI2SRDYF_MSK              

#define CIR_CSSF_POS                   (7U)                                
#define CIR_CSSF_MSK                   (0X1UL << CIR_CSSF_POS)          
#define CIR_CSSF                       CIR_CSSF_MSK                    
#define CIR_LSIRDYIE_POS               (8U)                                
#define CIR_LSIRDYIE_MSK               (0X1UL << CIR_LSIRDYIE_POS)      
#define CIR_LSIRDYIE                   CIR_LSIRDYIE_MSK                
#define CIR_LSERDYIE_POS               (9U)                                
#define CIR_LSERDYIE_MSK               (0X1UL << CIR_LSERDYIE_POS)      
#define CIR_LSERDYIE                   CIR_LSERDYIE_MSK                
#define CIR_HSIRDYIE_POS               (10U)                               
#define CIR_HSIRDYIE_MSK               (0X1UL << CIR_HSIRDYIE_POS)      
#define CIR_HSIRDYIE                   CIR_HSIRDYIE_MSK                
#define CIR_HSERDYIE_POS               (11U)                               
#define CIR_HSERDYIE_MSK               (0X1UL << CIR_HSERDYIE_POS)      
#define CIR_HSERDYIE                   CIR_HSERDYIE_MSK                
#define CIR_PLLRDYIE_POS               (12U)                               
#define CIR_PLLRDYIE_MSK               (0X1UL << CIR_PLLRDYIE_POS)      
#define CIR_PLLRDYIE                   CIR_PLLRDYIE_MSK                
#define CIR_PLLI2SRDYIE_POS            (13U)                               
#define CIR_PLLI2SRDYIE_MSK            (0X1UL << CIR_PLLI2SRDYIE_POS)   
#define CIR_PLLI2SRDYIE                CIR_PLLI2SRDYIE_MSK             

#define CIR_LSIRDYC_POS                (16U)                               
#define CIR_LSIRDYC_MSK                (0X1UL << CIR_LSIRDYC_POS)       
#define CIR_LSIRDYC                    CIR_LSIRDYC_MSK                 
#define CIR_LSERDYC_POS                (17U)                               
#define CIR_LSERDYC_MSK                (0X1UL << CIR_LSERDYC_POS)       
#define CIR_LSERDYC                    CIR_LSERDYC_MSK                 
#define CIR_HSIRDYC_POS                (18U)                               
#define CIR_HSIRDYC_MSK                (0X1UL << CIR_HSIRDYC_POS)       
#define CIR_HSIRDYC                    CIR_HSIRDYC_MSK                 
#define CIR_HSERDYC_POS                (19U)                               
#define CIR_HSERDYC_MSK                (0X1UL << CIR_HSERDYC_POS)       
#define CIR_HSERDYC                    CIR_HSERDYC_MSK                 
#define CIR_PLLRDYC_POS                (20U)                               
#define CIR_PLLRDYC_MSK                (0X1UL << CIR_PLLRDYC_POS)       
#define CIR_PLLRDYC                    CIR_PLLRDYC_MSK                 
#define CIR_PLLI2SRDYC_POS             (21U)                               
#define CIR_PLLI2SRDYC_MSK             (0X1UL << CIR_PLLI2SRDYC_POS)    
#define CIR_PLLI2SRDYC                 CIR_PLLI2SRDYC_MSK              

#define CIR_CSSC_POS                   (23U)                               
#define CIR_CSSC_MSK                   (0X1UL << CIR_CSSC_POS)          
#define CIR_CSSC                       CIR_CSSC_MSK                    

/********************  BIT DEFINITION FOR RCC::AHB1RSTR   **************/
#define AHB1RSTR_GPIOARST_POS          (0U)                                
#define AHB1RSTR_GPIOARST_MSK          (0X1UL << AHB1RSTR_GPIOARST_POS) 
#define AHB1RSTR_GPIOARST              AHB1RSTR_GPIOARST_MSK           
#define AHB1RSTR_GPIOBRST_POS          (1U)                                
#define AHB1RSTR_GPIOBRST_MSK          (0X1UL << AHB1RSTR_GPIOBRST_POS) 
#define AHB1RSTR_GPIOBRST              AHB1RSTR_GPIOBRST_MSK           
#define AHB1RSTR_GPIOCRST_POS          (2U)                                
#define AHB1RSTR_GPIOCRST_MSK          (0X1UL << AHB1RSTR_GPIOCRST_POS) 
#define AHB1RSTR_GPIOCRST              AHB1RSTR_GPIOCRST_MSK           
#define AHB1RSTR_GPIODRST_POS          (3U)                                
#define AHB1RSTR_GPIODRST_MSK          (0X1UL << AHB1RSTR_GPIODRST_POS) 
#define AHB1RSTR_GPIODRST              AHB1RSTR_GPIODRST_MSK           
#define AHB1RSTR_GPIOERST_POS          (4U)                                
#define AHB1RSTR_GPIOERST_MSK          (0X1UL << AHB1RSTR_GPIOERST_POS) 
#define AHB1RSTR_GPIOERST              AHB1RSTR_GPIOERST_MSK           
#define AHB1RSTR_GPIOHRST_POS          (7U)                                
#define AHB1RSTR_GPIOHRST_MSK          (0X1UL << AHB1RSTR_GPIOHRST_POS) 
#define AHB1RSTR_GPIOHRST              AHB1RSTR_GPIOHRST_MSK           
#define AHB1RSTR_CRCRST_POS            (12U)                               
#define AHB1RSTR_CRCRST_MSK            (0X1UL << AHB1RSTR_CRCRST_POS)   
#define AHB1RSTR_CRCRST                AHB1RSTR_CRCRST_MSK             
#define AHB1RSTR_DMA1RST_POS           (21U)                               
#define AHB1RSTR_DMA1RST_MSK           (0X1UL << AHB1RSTR_DMA1RST_POS)  
#define AHB1RSTR_DMA1RST               AHB1RSTR_DMA1RST_MSK            
#define AHB1RSTR_DMA2RST_POS           (22U)                               
#define AHB1RSTR_DMA2RST_MSK           (0X1UL << AHB1RSTR_DMA2RST_POS)  
#define AHB1RSTR_DMA2RST               AHB1RSTR_DMA2RST_MSK            

/********************  BIT DEFINITION FOR RCC::AHB2RSTR   **************/
#define AHB2RSTR_OTGFSRST_POS          (7U)                                
#define AHB2RSTR_OTGFSRST_MSK          (0X1UL << AHB2RSTR_OTGFSRST_POS) 
#define AHB2RSTR_OTGFSRST              AHB2RSTR_OTGFSRST_MSK           
/********************  BIT DEFINITION FOR RCC::AHB3RSTR   **************/


/********************  BIT DEFINITION FOR RCC::APB1RSTR   **************/
#define APB1RSTR_TIM2RST_POS           (0U)                                
#define APB1RSTR_TIM2RST_MSK           (0X1UL << APB1RSTR_TIM2RST_POS)  
#define APB1RSTR_TIM2RST               APB1RSTR_TIM2RST_MSK            
#define APB1RSTR_TIM3RST_POS           (1U)                                
#define APB1RSTR_TIM3RST_MSK           (0X1UL << APB1RSTR_TIM3RST_POS)  
#define APB1RSTR_TIM3RST               APB1RSTR_TIM3RST_MSK            
#define APB1RSTR_TIM4RST_POS           (2U)                                
#define APB1RSTR_TIM4RST_MSK           (0X1UL << APB1RSTR_TIM4RST_POS)  
#define APB1RSTR_TIM4RST               APB1RSTR_TIM4RST_MSK            
#define APB1RSTR_TIM5RST_POS           (3U)                                
#define APB1RSTR_TIM5RST_MSK           (0X1UL << APB1RSTR_TIM5RST_POS)  
#define APB1RSTR_TIM5RST               APB1RSTR_TIM5RST_MSK            
#define APB1RSTR_WWDGRST_POS           (11U)                               
#define APB1RSTR_WWDGRST_MSK           (0X1UL << APB1RSTR_WWDGRST_POS)  
#define APB1RSTR_WWDGRST               APB1RSTR_WWDGRST_MSK            
#define APB1RSTR_SPI2RST_POS           (14U)                               
#define APB1RSTR_SPI2RST_MSK           (0X1UL << APB1RSTR_SPI2RST_POS)  
#define APB1RSTR_SPI2RST               APB1RSTR_SPI2RST_MSK            
#define APB1RSTR_SPI3RST_POS           (15U)                               
#define APB1RSTR_SPI3RST_MSK           (0X1UL << APB1RSTR_SPI3RST_POS)  
#define APB1RSTR_SPI3RST               APB1RSTR_SPI3RST_MSK            
#define APB1RSTR_USART2RST_POS         (17U)                               
#define APB1RSTR_USART2RST_MSK         (0X1UL << APB1RSTR_USART2RST_POS) 
#define APB1RSTR_USART2RST             APB1RSTR_USART2RST_MSK          
#define APB1RSTR_I2C1RST_POS           (21U)                               
#define APB1RSTR_I2C1RST_MSK           (0X1UL << APB1RSTR_I2C1RST_POS)  
#define APB1RSTR_I2C1RST               APB1RSTR_I2C1RST_MSK            
#define APB1RSTR_I2C2RST_POS           (22U)                               
#define APB1RSTR_I2C2RST_MSK           (0X1UL << APB1RSTR_I2C2RST_POS)  
#define APB1RSTR_I2C2RST               APB1RSTR_I2C2RST_MSK            
#define APB1RSTR_I2C3RST_POS           (23U)                               
#define APB1RSTR_I2C3RST_MSK           (0X1UL << APB1RSTR_I2C3RST_POS)  
#define APB1RSTR_I2C3RST               APB1RSTR_I2C3RST_MSK            
#define APB1RSTR_PWRRST_POS            (28U)                               
#define APB1RSTR_PWRRST_MSK            (0X1UL << APB1RSTR_PWRRST_POS)   
#define APB1RSTR_PWRRST                APB1RSTR_PWRRST_MSK             

/********************  BIT DEFINITION FOR RCC::APB2RSTR   **************/
#define APB2RSTR_TIM1RST_POS           (0U)                                
#define APB2RSTR_TIM1RST_MSK           (0X1UL << APB2RSTR_TIM1RST_POS)  
#define APB2RSTR_TIM1RST               APB2RSTR_TIM1RST_MSK            
#define APB2RSTR_USART1RST_POS         (4U)                                
#define APB2RSTR_USART1RST_MSK         (0X1UL << APB2RSTR_USART1RST_POS) 
#define APB2RSTR_USART1RST             APB2RSTR_USART1RST_MSK          
#define APB2RSTR_USART6RST_POS         (5U)                                
#define APB2RSTR_USART6RST_MSK         (0X1UL << APB2RSTR_USART6RST_POS) 
#define APB2RSTR_USART6RST             APB2RSTR_USART6RST_MSK          
#define APB2RSTR_ADCRST_POS            (8U)                                
#define APB2RSTR_ADCRST_MSK            (0X1UL << APB2RSTR_ADCRST_POS)   
#define APB2RSTR_ADCRST                APB2RSTR_ADCRST_MSK             
#define APB2RSTR_SDIORST_POS           (11U)                               
#define APB2RSTR_SDIORST_MSK           (0X1UL << APB2RSTR_SDIORST_POS)  
#define APB2RSTR_SDIORST               APB2RSTR_SDIORST_MSK            
#define APB2RSTR_SPI1RST_POS           (12U)                               
#define APB2RSTR_SPI1RST_MSK           (0X1UL << APB2RSTR_SPI1RST_POS)  
#define APB2RSTR_SPI1RST               APB2RSTR_SPI1RST_MSK            
#define APB2RSTR_SPI4RST_POS           (13U)                               
#define APB2RSTR_SPI4RST_MSK           (0X1UL << APB2RSTR_SPI4RST_POS)  
#define APB2RSTR_SPI4RST               APB2RSTR_SPI4RST_MSK            
#define APB2RSTR_SYSCFGRST_POS         (14U)                               
#define APB2RSTR_SYSCFGRST_MSK         (0X1UL << APB2RSTR_SYSCFGRST_POS) 
#define APB2RSTR_SYSCFGRST             APB2RSTR_SYSCFGRST_MSK          
#define APB2RSTR_TIM9RST_POS           (16U)                               
#define APB2RSTR_TIM9RST_MSK           (0X1UL << APB2RSTR_TIM9RST_POS)  
#define APB2RSTR_TIM9RST               APB2RSTR_TIM9RST_MSK            
#define APB2RSTR_TIM10RST_POS          (17U)                               
#define APB2RSTR_TIM10RST_MSK          (0X1UL << APB2RSTR_TIM10RST_POS) 
#define APB2RSTR_TIM10RST              APB2RSTR_TIM10RST_MSK           
#define APB2RSTR_TIM11RST_POS          (18U)                               
#define APB2RSTR_TIM11RST_MSK          (0X1UL << APB2RSTR_TIM11RST_POS) 
#define APB2RSTR_TIM11RST              APB2RSTR_TIM11RST_MSK           
#define APB2RSTR_SPI5RST_POS           (20U)                               
#define APB2RSTR_SPI5RST_MSK           (0X1UL << APB2RSTR_SPI5RST_POS)  
#define APB2RSTR_SPI5RST               APB2RSTR_SPI5RST_MSK            

/********************  BIT DEFINITION FOR RCC::AHB1ENR   ***************/
#define AHB1ENR_GPIOAEN_POS            (0U)                                
#define AHB1ENR_GPIOAEN_MSK            (0X1UL << AHB1ENR_GPIOAEN_POS)   
#define AHB1ENR_GPIOAEN                AHB1ENR_GPIOAEN_MSK             
#define AHB1ENR_GPIOBEN_POS            (1U)                                
#define AHB1ENR_GPIOBEN_MSK            (0X1UL << AHB1ENR_GPIOBEN_POS)   
#define AHB1ENR_GPIOBEN                AHB1ENR_GPIOBEN_MSK             
#define AHB1ENR_GPIOCEN_POS            (2U)                                
#define AHB1ENR_GPIOCEN_MSK            (0X1UL << AHB1ENR_GPIOCEN_POS)   
#define AHB1ENR_GPIOCEN                AHB1ENR_GPIOCEN_MSK             
#define AHB1ENR_GPIODEN_POS            (3U)                                
#define AHB1ENR_GPIODEN_MSK            (0X1UL << AHB1ENR_GPIODEN_POS)   
#define AHB1ENR_GPIODEN                AHB1ENR_GPIODEN_MSK             
#define AHB1ENR_GPIOEEN_POS            (4U)                                
#define AHB1ENR_GPIOEEN_MSK            (0X1UL << AHB1ENR_GPIOEEN_POS)   
#define AHB1ENR_GPIOEEN                AHB1ENR_GPIOEEN_MSK             
#define AHB1ENR_GPIOHEN_POS            (7U)                                
#define AHB1ENR_GPIOHEN_MSK            (0X1UL << AHB1ENR_GPIOHEN_POS)   
#define AHB1ENR_GPIOHEN                AHB1ENR_GPIOHEN_MSK             
#define AHB1ENR_CRCEN_POS              (12U)                               
#define AHB1ENR_CRCEN_MSK              (0X1UL << AHB1ENR_CRCEN_POS)     
#define AHB1ENR_CRCEN                  AHB1ENR_CRCEN_MSK               
#define AHB1ENR_DMA1EN_POS             (21U)                               
#define AHB1ENR_DMA1EN_MSK             (0X1UL << AHB1ENR_DMA1EN_POS)    
#define AHB1ENR_DMA1EN                 AHB1ENR_DMA1EN_MSK              
#define AHB1ENR_DMA2EN_POS             (22U)                               
#define AHB1ENR_DMA2EN_MSK             (0X1UL << AHB1ENR_DMA2EN_POS)    
#define AHB1ENR_DMA2EN                 AHB1ENR_DMA2EN_MSK              
/********************  BIT DEFINITION FOR RCC::AHB2ENR   ***************/
/*
 * @BRIEF SPECIFIC DEVICE FEATURE DEFINITIONS (NOT PRESENT ON ALL DEVICES IN THE STM32F4 SERIE)
 */
#define AHB2_SUPPORT                   

#define AHB2ENR_OTGFSEN_POS            (7U)                                
#define AHB2ENR_OTGFSEN_MSK            (0X1UL << AHB2ENR_OTGFSEN_POS)   
#define AHB2ENR_OTGFSEN                AHB2ENR_OTGFSEN_MSK             

/********************  BIT DEFINITION FOR RCC::APB1ENR   ***************/
#define APB1ENR_TIM2EN_POS             (0U)                                
#define APB1ENR_TIM2EN_MSK             (0X1UL << APB1ENR_TIM2EN_POS)    
#define APB1ENR_TIM2EN                 APB1ENR_TIM2EN_MSK              
#define APB1ENR_TIM3EN_POS             (1U)                                
#define APB1ENR_TIM3EN_MSK             (0X1UL << APB1ENR_TIM3EN_POS)    
#define APB1ENR_TIM3EN                 APB1ENR_TIM3EN_MSK              
#define APB1ENR_TIM4EN_POS             (2U)                                
#define APB1ENR_TIM4EN_MSK             (0X1UL << APB1ENR_TIM4EN_POS)    
#define APB1ENR_TIM4EN                 APB1ENR_TIM4EN_MSK              
#define APB1ENR_TIM5EN_POS             (3U)                                
#define APB1ENR_TIM5EN_MSK             (0X1UL << APB1ENR_TIM5EN_POS)    
#define APB1ENR_TIM5EN                 APB1ENR_TIM5EN_MSK              
#define APB1ENR_WWDGEN_POS             (11U)                               
#define APB1ENR_WWDGEN_MSK             (0X1UL << APB1ENR_WWDGEN_POS)    
#define APB1ENR_WWDGEN                 APB1ENR_WWDGEN_MSK              
#define APB1ENR_SPI2EN_POS             (14U)                               
#define APB1ENR_SPI2EN_MSK             (0X1UL << APB1ENR_SPI2EN_POS)    
#define APB1ENR_SPI2EN                 APB1ENR_SPI2EN_MSK              
#define APB1ENR_SPI3EN_POS             (15U)                               
#define APB1ENR_SPI3EN_MSK             (0X1UL << APB1ENR_SPI3EN_POS)    
#define APB1ENR_SPI3EN                 APB1ENR_SPI3EN_MSK              
#define APB1ENR_USART2EN_POS           (17U)                               
#define APB1ENR_USART2EN_MSK           (0X1UL << APB1ENR_USART2EN_POS)  
#define APB1ENR_USART2EN               APB1ENR_USART2EN_MSK            
#define APB1ENR_I2C1EN_POS             (21U)                               
#define APB1ENR_I2C1EN_MSK             (0X1UL << APB1ENR_I2C1EN_POS)    
#define APB1ENR_I2C1EN                 APB1ENR_I2C1EN_MSK              
#define APB1ENR_I2C2EN_POS             (22U)                               
#define APB1ENR_I2C2EN_MSK             (0X1UL << APB1ENR_I2C2EN_POS)    
#define APB1ENR_I2C2EN                 APB1ENR_I2C2EN_MSK              
#define APB1ENR_I2C3EN_POS             (23U)                               
#define APB1ENR_I2C3EN_MSK             (0X1UL << APB1ENR_I2C3EN_POS)    
#define APB1ENR_I2C3EN                 APB1ENR_I2C3EN_MSK              
#define APB1ENR_PWREN_POS              (28U)                               
#define APB1ENR_PWREN_MSK              (0X1UL << APB1ENR_PWREN_POS)     
#define APB1ENR_PWREN                  APB1ENR_PWREN_MSK               

/********************  BIT DEFINITION FOR RCC::APB2ENR   ***************/
#define APB2ENR_TIM1EN_POS             (0U)                                
#define APB2ENR_TIM1EN_MSK             (0X1UL << APB2ENR_TIM1EN_POS)    
#define APB2ENR_TIM1EN                 APB2ENR_TIM1EN_MSK              
#define APB2ENR_USART1EN_POS           (4U)                                
#define APB2ENR_USART1EN_MSK           (0X1UL << APB2ENR_USART1EN_POS)  
#define APB2ENR_USART1EN               APB2ENR_USART1EN_MSK            
#define APB2ENR_USART6EN_POS           (5U)                                
#define APB2ENR_USART6EN_MSK           (0X1UL << APB2ENR_USART6EN_POS)  
#define APB2ENR_USART6EN               APB2ENR_USART6EN_MSK            
#define APB2ENR_ADC1EN_POS             (8U)                                
#define APB2ENR_ADC1EN_MSK             (0X1UL << APB2ENR_ADC1EN_POS)    
#define APB2ENR_ADC1EN                 APB2ENR_ADC1EN_MSK              
#define APB2ENR_SDIOEN_POS             (11U)                               
#define APB2ENR_SDIOEN_MSK             (0X1UL << APB2ENR_SDIOEN_POS)    
#define APB2ENR_SDIOEN                 APB2ENR_SDIOEN_MSK              
#define APB2ENR_SPI1EN_POS             (12U)                               
#define APB2ENR_SPI1EN_MSK             (0X1UL << APB2ENR_SPI1EN_POS)    
#define APB2ENR_SPI1EN                 APB2ENR_SPI1EN_MSK              
#define APB2ENR_SPI4EN_POS             (13U)                               
#define APB2ENR_SPI4EN_MSK             (0X1UL << APB2ENR_SPI4EN_POS)    
#define APB2ENR_SPI4EN                 APB2ENR_SPI4EN_MSK              
#define APB2ENR_SYSCFGEN_POS           (14U)                               
#define APB2ENR_SYSCFGEN_MSK           (0X1UL << APB2ENR_SYSCFGEN_POS)  
#define APB2ENR_SYSCFGEN               APB2ENR_SYSCFGEN_MSK            
#define APB2ENR_TIM9EN_POS             (16U)                               
#define APB2ENR_TIM9EN_MSK             (0X1UL << APB2ENR_TIM9EN_POS)    
#define APB2ENR_TIM9EN                 APB2ENR_TIM9EN_MSK              
#define APB2ENR_TIM10EN_POS            (17U)                               
#define APB2ENR_TIM10EN_MSK            (0X1UL << APB2ENR_TIM10EN_POS)   
#define APB2ENR_TIM10EN                APB2ENR_TIM10EN_MSK             
#define APB2ENR_TIM11EN_POS            (18U)                               
#define APB2ENR_TIM11EN_MSK            (0X1UL << APB2ENR_TIM11EN_POS)   
#define APB2ENR_TIM11EN                APB2ENR_TIM11EN_MSK             
#define APB2ENR_SPI5EN_POS             (20U)                               
#define APB2ENR_SPI5EN_MSK             (0X1UL << APB2ENR_SPI5EN_POS)    
#define APB2ENR_SPI5EN                 APB2ENR_SPI5EN_MSK              

/********************  BIT DEFINITION FOR RCC::AHB1LPENR   *************/
#define AHB1LPENR_GPIOALPEN_POS        (0U)                                
#define AHB1LPENR_GPIOALPEN_MSK        (0X1UL << AHB1LPENR_GPIOALPEN_POS) 
#define AHB1LPENR_GPIOALPEN            AHB1LPENR_GPIOALPEN_MSK         
#define AHB1LPENR_GPIOBLPEN_POS        (1U)                                
#define AHB1LPENR_GPIOBLPEN_MSK        (0X1UL << AHB1LPENR_GPIOBLPEN_POS) 
#define AHB1LPENR_GPIOBLPEN            AHB1LPENR_GPIOBLPEN_MSK         
#define AHB1LPENR_GPIOCLPEN_POS        (2U)                                
#define AHB1LPENR_GPIOCLPEN_MSK        (0X1UL << AHB1LPENR_GPIOCLPEN_POS) 
#define AHB1LPENR_GPIOCLPEN            AHB1LPENR_GPIOCLPEN_MSK         
#define AHB1LPENR_GPIODLPEN_POS        (3U)                                
#define AHB1LPENR_GPIODLPEN_MSK        (0X1UL << AHB1LPENR_GPIODLPEN_POS) 
#define AHB1LPENR_GPIODLPEN            AHB1LPENR_GPIODLPEN_MSK         
#define AHB1LPENR_GPIOELPEN_POS        (4U)                                
#define AHB1LPENR_GPIOELPEN_MSK        (0X1UL << AHB1LPENR_GPIOELPEN_POS) 
#define AHB1LPENR_GPIOELPEN            AHB1LPENR_GPIOELPEN_MSK         
#define AHB1LPENR_GPIOHLPEN_POS        (7U)                                
#define AHB1LPENR_GPIOHLPEN_MSK        (0X1UL << AHB1LPENR_GPIOHLPEN_POS) 
#define AHB1LPENR_GPIOHLPEN            AHB1LPENR_GPIOHLPEN_MSK         
#define AHB1LPENR_CRCLPEN_POS          (12U)                               
#define AHB1LPENR_CRCLPEN_MSK          (0X1UL << AHB1LPENR_CRCLPEN_POS) 
#define AHB1LPENR_CRCLPEN              AHB1LPENR_CRCLPEN_MSK           
#define AHB1LPENR_FLITFLPEN_POS        (15U)                               
#define AHB1LPENR_FLITFLPEN_MSK        (0X1UL << AHB1LPENR_FLITFLPEN_POS) 
#define AHB1LPENR_FLITFLPEN            AHB1LPENR_FLITFLPEN_MSK         
#define AHB1LPENR_SRAM1LPEN_POS        (16U)                               
#define AHB1LPENR_SRAM1LPEN_MSK        (0X1UL << AHB1LPENR_SRAM1LPEN_POS) 
#define AHB1LPENR_SRAM1LPEN            AHB1LPENR_SRAM1LPEN_MSK         
#define AHB1LPENR_DMA1LPEN_POS         (21U)                               
#define AHB1LPENR_DMA1LPEN_MSK         (0X1UL << AHB1LPENR_DMA1LPEN_POS) 
#define AHB1LPENR_DMA1LPEN             AHB1LPENR_DMA1LPEN_MSK          
#define AHB1LPENR_DMA2LPEN_POS         (22U)                               
#define AHB1LPENR_DMA2LPEN_MSK         (0X1UL << AHB1LPENR_DMA2LPEN_POS) 
#define AHB1LPENR_DMA2LPEN             AHB1LPENR_DMA2LPEN_MSK          


/********************  BIT DEFINITION FOR RCC::AHB2LPENR   *************/
#define AHB2LPENR_OTGFSLPEN_POS        (7U)                                
#define AHB2LPENR_OTGFSLPEN_MSK        (0X1UL << AHB2LPENR_OTGFSLPEN_POS) 
#define AHB2LPENR_OTGFSLPEN            AHB2LPENR_OTGFSLPEN_MSK         

/********************  BIT DEFINITION FOR RCC::AHB3LPENR   *************/

/********************  BIT DEFINITION FOR RCC::APB1LPENR   *************/
#define APB1LPENR_TIM2LPEN_POS         (0U)                                
#define APB1LPENR_TIM2LPEN_MSK         (0X1UL << APB1LPENR_TIM2LPEN_POS) 
#define APB1LPENR_TIM2LPEN             APB1LPENR_TIM2LPEN_MSK          
#define APB1LPENR_TIM3LPEN_POS         (1U)                                
#define APB1LPENR_TIM3LPEN_MSK         (0X1UL << APB1LPENR_TIM3LPEN_POS) 
#define APB1LPENR_TIM3LPEN             APB1LPENR_TIM3LPEN_MSK          
#define APB1LPENR_TIM4LPEN_POS         (2U)                                
#define APB1LPENR_TIM4LPEN_MSK         (0X1UL << APB1LPENR_TIM4LPEN_POS) 
#define APB1LPENR_TIM4LPEN             APB1LPENR_TIM4LPEN_MSK          
#define APB1LPENR_TIM5LPEN_POS         (3U)                                
#define APB1LPENR_TIM5LPEN_MSK         (0X1UL << APB1LPENR_TIM5LPEN_POS) 
#define APB1LPENR_TIM5LPEN             APB1LPENR_TIM5LPEN_MSK          
#define APB1LPENR_WWDGLPEN_POS         (11U)                               
#define APB1LPENR_WWDGLPEN_MSK         (0X1UL << APB1LPENR_WWDGLPEN_POS) 
#define APB1LPENR_WWDGLPEN             APB1LPENR_WWDGLPEN_MSK          
#define APB1LPENR_SPI2LPEN_POS         (14U)                               
#define APB1LPENR_SPI2LPEN_MSK         (0X1UL << APB1LPENR_SPI2LPEN_POS) 
#define APB1LPENR_SPI2LPEN             APB1LPENR_SPI2LPEN_MSK          
#define APB1LPENR_SPI3LPEN_POS         (15U)                               
#define APB1LPENR_SPI3LPEN_MSK         (0X1UL << APB1LPENR_SPI3LPEN_POS) 
#define APB1LPENR_SPI3LPEN             APB1LPENR_SPI3LPEN_MSK          
#define APB1LPENR_USART2LPEN_POS       (17U)                               
#define APB1LPENR_USART2LPEN_MSK       (0X1UL << APB1LPENR_USART2LPEN_POS) 
#define APB1LPENR_USART2LPEN           APB1LPENR_USART2LPEN_MSK        
#define APB1LPENR_I2C1LPEN_POS         (21U)                               
#define APB1LPENR_I2C1LPEN_MSK         (0X1UL << APB1LPENR_I2C1LPEN_POS) 
#define APB1LPENR_I2C1LPEN             APB1LPENR_I2C1LPEN_MSK          
#define APB1LPENR_I2C2LPEN_POS         (22U)                               
#define APB1LPENR_I2C2LPEN_MSK         (0X1UL << APB1LPENR_I2C2LPEN_POS) 
#define APB1LPENR_I2C2LPEN             APB1LPENR_I2C2LPEN_MSK          
#define APB1LPENR_I2C3LPEN_POS         (23U)                               
#define APB1LPENR_I2C3LPEN_MSK         (0X1UL << APB1LPENR_I2C3LPEN_POS) 
#define APB1LPENR_I2C3LPEN             APB1LPENR_I2C3LPEN_MSK          
#define APB1LPENR_PWRLPEN_POS          (28U)                               
#define APB1LPENR_PWRLPEN_MSK          (0X1UL << APB1LPENR_PWRLPEN_POS) 
#define APB1LPENR_PWRLPEN              APB1LPENR_PWRLPEN_MSK           

/********************  BIT DEFINITION FOR RCC::APB2LPENR   *************/
#define APB2LPENR_TIM1LPEN_POS         (0U)                                
#define APB2LPENR_TIM1LPEN_MSK         (0X1UL << APB2LPENR_TIM1LPEN_POS) 
#define APB2LPENR_TIM1LPEN             APB2LPENR_TIM1LPEN_MSK          
#define APB2LPENR_USART1LPEN_POS       (4U)                                
#define APB2LPENR_USART1LPEN_MSK       (0X1UL << APB2LPENR_USART1LPEN_POS) 
#define APB2LPENR_USART1LPEN           APB2LPENR_USART1LPEN_MSK        
#define APB2LPENR_USART6LPEN_POS       (5U)                                
#define APB2LPENR_USART6LPEN_MSK       (0X1UL << APB2LPENR_USART6LPEN_POS) 
#define APB2LPENR_USART6LPEN           APB2LPENR_USART6LPEN_MSK        
#define APB2LPENR_ADC1LPEN_POS         (8U)                                
#define APB2LPENR_ADC1LPEN_MSK         (0X1UL << APB2LPENR_ADC1LPEN_POS) 
#define APB2LPENR_ADC1LPEN             APB2LPENR_ADC1LPEN_MSK          
#define APB2LPENR_SDIOLPEN_POS         (11U)                               
#define APB2LPENR_SDIOLPEN_MSK         (0X1UL << APB2LPENR_SDIOLPEN_POS) 
#define APB2LPENR_SDIOLPEN             APB2LPENR_SDIOLPEN_MSK          
#define APB2LPENR_SPI1LPEN_POS         (12U)                               
#define APB2LPENR_SPI1LPEN_MSK         (0X1UL << APB2LPENR_SPI1LPEN_POS) 
#define APB2LPENR_SPI1LPEN             APB2LPENR_SPI1LPEN_MSK          
#define APB2LPENR_SPI4LPEN_POS         (13U)                               
#define APB2LPENR_SPI4LPEN_MSK         (0X1UL << APB2LPENR_SPI4LPEN_POS) 
#define APB2LPENR_SPI4LPEN             APB2LPENR_SPI4LPEN_MSK          
#define APB2LPENR_SYSCFGLPEN_POS       (14U)                               
#define APB2LPENR_SYSCFGLPEN_MSK       (0X1UL << APB2LPENR_SYSCFGLPEN_POS) 
#define APB2LPENR_SYSCFGLPEN           APB2LPENR_SYSCFGLPEN_MSK        
#define APB2LPENR_TIM9LPEN_POS         (16U)                               
#define APB2LPENR_TIM9LPEN_MSK         (0X1UL << APB2LPENR_TIM9LPEN_POS) 
#define APB2LPENR_TIM9LPEN             APB2LPENR_TIM9LPEN_MSK          
#define APB2LPENR_TIM10LPEN_POS        (17U)                               
#define APB2LPENR_TIM10LPEN_MSK        (0X1UL << APB2LPENR_TIM10LPEN_POS) 
#define APB2LPENR_TIM10LPEN            APB2LPENR_TIM10LPEN_MSK         
#define APB2LPENR_TIM11LPEN_POS        (18U)                               
#define APB2LPENR_TIM11LPEN_MSK        (0X1UL << APB2LPENR_TIM11LPEN_POS) 
#define APB2LPENR_TIM11LPEN            APB2LPENR_TIM11LPEN_MSK         
#define APB2LPENR_SPI5LPEN_POS         (20U)                               
#define APB2LPENR_SPI5LPEN_MSK         (0X1UL << APB2LPENR_SPI5LPEN_POS) 
#define APB2LPENR_SPI5LPEN             APB2LPENR_SPI5LPEN_MSK          

/********************  BIT DEFINITION FOR RCC::BDCR   ******************/
#define BDCR_LSEON_POS                 (0U)                                
#define BDCR_LSEON_MSK                 (0X1UL << BDCR_LSEON_POS)        
#define BDCR_LSEON                     BDCR_LSEON_MSK                  
#define BDCR_LSERDY_POS                (1U)                                
#define BDCR_LSERDY_MSK                (0X1UL << BDCR_LSERDY_POS)       
#define BDCR_LSERDY                    BDCR_LSERDY_MSK                 
#define BDCR_LSEBYP_POS                (2U)                                
#define BDCR_LSEBYP_MSK                (0X1UL << BDCR_LSEBYP_POS)       
#define BDCR_LSEBYP                    BDCR_LSEBYP_MSK                 
#define BDCR_LSEMOD_POS                (3U)                                
#define BDCR_LSEMOD_MSK                (0X1UL << BDCR_LSEMOD_POS)       
#define BDCR_LSEMOD                    BDCR_LSEMOD_MSK                 

#define BDCR_RTCSEL_POS                (8U)                                
#define BDCR_RTCSEL_MSK                (0X3UL << BDCR_RTCSEL_POS)       
#define BDCR_RTCSEL                    BDCR_RTCSEL_MSK                 
#define BDCR_RTCSEL_0                  (0X1UL << BDCR_RTCSEL_POS)       
#define BDCR_RTCSEL_1                  (0X2UL << BDCR_RTCSEL_POS)       

#define BDCR_RTCEN_POS                 (15U)                               
#define BDCR_RTCEN_MSK                 (0X1UL << BDCR_RTCEN_POS)        
#define BDCR_RTCEN                     BDCR_RTCEN_MSK                  
#define BDCR_BDRST_POS                 (16U)                               
#define BDCR_BDRST_MSK                 (0X1UL << BDCR_BDRST_POS)        
#define BDCR_BDRST                     BDCR_BDRST_MSK                  

/********************  BIT DEFINITION FOR RCC::CSR   *******************/
#define CSR_LSION_POS                  (0U)                                
#define CSR_LSION_MSK                  (0X1UL << CSR_LSION_POS)         
#define CSR_LSION                      CSR_LSION_MSK                   
#define CSR_LSIRDY_POS                 (1U)                                
#define CSR_LSIRDY_MSK                 (0X1UL << CSR_LSIRDY_POS)        
#define CSR_LSIRDY                     CSR_LSIRDY_MSK                  
#define CSR_RMVF_POS                   (24U)                               
#define CSR_RMVF_MSK                   (0X1UL << CSR_RMVF_POS)          
#define CSR_RMVF                       CSR_RMVF_MSK                    
#define CSR_BORRSTF_POS                (25U)                               
#define CSR_BORRSTF_MSK                (0X1UL << CSR_BORRSTF_POS)       
#define CSR_BORRSTF                    CSR_BORRSTF_MSK                 
#define CSR_PINRSTF_POS                (26U)
#define CSR_PINRSTF_MSK                (0X1UL << CSR_PINRSTF_POS)       
#define CSR_PINRSTF                    CSR_PINRSTF_MSK
#define CSR_PORRSTF_POS                (27U)                               
#define CSR_PORRSTF_MSK                (0X1UL << CSR_PORRSTF_POS)       
#define CSR_PORRSTF                    CSR_PORRSTF_MSK                 
#define CSR_SFTRSTF_POS                (28U)                               
#define CSR_SFTRSTF_MSK                (0X1UL << CSR_SFTRSTF_POS)       
#define CSR_SFTRSTF                    CSR_SFTRSTF_MSK                 
#define CSR_IWDGRSTF_POS               (29U)
#define CSR_IWDGRSTF_MSK               (0X1UL << CSR_IWDGRSTF_POS)      
#define CSR_IWDGRSTF                   CSR_IWDGRSTF_MSK
#define CSR_WWDGRSTF_POS               (30U)                               
#define CSR_WWDGRSTF_MSK               (0X1UL << CSR_WWDGRSTF_POS)      
#define CSR_WWDGRSTF                   CSR_WWDGRSTF_MSK                
#define CSR_LPWRRSTF_POS               (31U)                               
#define CSR_LPWRRSTF_MSK               (0X1UL << CSR_LPWRRSTF_POS)      
#define CSR_LPWRRSTF                   CSR_LPWRRSTF_MSK


/********************  BIT DEFINITION FOR RCC::SSCGR   *****************/
#define SSCGR_MODPER_POS               (0U)                                
#define SSCGR_MODPER_MSK               (0X1FFFUL << SSCGR_MODPER_POS)   
#define SSCGR_MODPER                   SSCGR_MODPER_MSK                
#define SSCGR_INCSTEP_POS              (13U)                               
#define SSCGR_INCSTEP_MSK              (0X7FFFUL << SSCGR_INCSTEP_POS)  
#define SSCGR_INCSTEP                  SSCGR_INCSTEP_MSK               
#define SSCGR_SPREADSEL_POS            (30U)                               
#define SSCGR_SPREADSEL_MSK            (0X1UL << SSCGR_SPREADSEL_POS)   
#define SSCGR_SPREADSEL                SSCGR_SPREADSEL_MSK             
#define SSCGR_SSCGEN_POS               (31U)                               
#define SSCGR_SSCGEN_MSK               (0X1UL << SSCGR_SSCGEN_POS)      
#define SSCGR_SSCGEN                   SSCGR_SSCGEN_MSK                

/********************  BIT DEFINITION FOR RCC::PLLI2SCFGR   ************/
#define PLLI2SCFGR_PLLI2SM_POS         (0U)                                
#define PLLI2SCFGR_PLLI2SM_MSK         (0X3FUL << PLLI2SCFGR_PLLI2SM_POS) 
#define PLLI2SCFGR_PLLI2SM             PLLI2SCFGR_PLLI2SM_MSK          
#define PLLI2SCFGR_PLLI2SM_0           (0X01UL << PLLI2SCFGR_PLLI2SM_POS) 
#define PLLI2SCFGR_PLLI2SM_1           (0X02UL << PLLI2SCFGR_PLLI2SM_POS) 
#define PLLI2SCFGR_PLLI2SM_2           (0X04UL << PLLI2SCFGR_PLLI2SM_POS) 
#define PLLI2SCFGR_PLLI2SM_3           (0X08UL << PLLI2SCFGR_PLLI2SM_POS) 
#define PLLI2SCFGR_PLLI2SM_4           (0X10UL << PLLI2SCFGR_PLLI2SM_POS) 
#define PLLI2SCFGR_PLLI2SM_5           (0X20UL << PLLI2SCFGR_PLLI2SM_POS) 

#define PLLI2SCFGR_PLLI2SN_POS         (6U)                                
#define PLLI2SCFGR_PLLI2SN_MSK         (0X1FFUL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN             PLLI2SCFGR_PLLI2SN_MSK          
#define PLLI2SCFGR_PLLI2SN_0           (0X001UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_1           (0X002UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_2           (0X004UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_3           (0X008UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_4           (0X010UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_5           (0X020UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_6           (0X040UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_7           (0X080UL << PLLI2SCFGR_PLLI2SN_POS) 
#define PLLI2SCFGR_PLLI2SN_8           (0X100UL << PLLI2SCFGR_PLLI2SN_POS) 

#define PLLI2SCFGR_PLLI2SR_POS         (28U)                               
#define PLLI2SCFGR_PLLI2SR_MSK         (0X7UL << PLLI2SCFGR_PLLI2SR_POS) 
#define PLLI2SCFGR_PLLI2SR             PLLI2SCFGR_PLLI2SR_MSK          
#define PLLI2SCFGR_PLLI2SR_0           (0X1UL << PLLI2SCFGR_PLLI2SR_POS) 
#define PLLI2SCFGR_PLLI2SR_1           (0X2UL << PLLI2SCFGR_PLLI2SR_POS) 
#define PLLI2SCFGR_PLLI2SR_2           (0X4UL << PLLI2SCFGR_PLLI2SR_POS) 

/********************  BIT DEFINITION FOR RCC::DCKCFGR   ***************/

#define DCKCFGR_TIMPRE_POS             (24U)                               
#define DCKCFGR_TIMPRE_MSK             (0X1UL << DCKCFGR_TIMPRE_POS)    
#define DCKCFGR_TIMPRE                 DCKCFGR_TIMPRE_MSK       

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RCC_REGISTER_MASKS */