#ifndef RIMOT_TIMER_REGISTER_MASKS
#define RIMOT_TIMER_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BIT DEFINITION FOR TIM::CR1   ********************/
#define CR1_CEN_POS           (0U)                                         
#define CR1_CEN_MSK           (0X1UL << CR1_CEN_POS)                    
#define CR1_CEN               CR1_CEN_MSK                              
#define CR1_UDIS_POS          (1U)                                         
#define CR1_UDIS_MSK          (0X1UL << CR1_UDIS_POS)                   
#define CR1_UDIS              CR1_UDIS_MSK                             
#define CR1_URS_POS           (2U)                                         
#define CR1_URS_MSK           (0X1UL << CR1_URS_POS)                    
#define CR1_URS               CR1_URS_MSK                              
#define CR1_OPM_POS           (3U)                                         
#define CR1_OPM_MSK           (0X1UL << CR1_OPM_POS)                    
#define CR1_OPM               CR1_OPM_MSK                              
#define CR1_DIR_POS           (4U)                                         
#define CR1_DIR_MSK           (0X1UL << CR1_DIR_POS)                    
#define CR1_DIR               CR1_DIR_MSK                              

#define CR1_CMS_POS           (5U)                                         
#define CR1_CMS_MSK           (0X3UL << CR1_CMS_POS)                    
#define CR1_CMS               CR1_CMS_MSK                              
#define CR1_CMS_0             (0X1UL << CR1_CMS_POS)                    
#define CR1_CMS_1             (0X2UL << CR1_CMS_POS)                    

#define CR1_ARPE_POS          (7U)                                         
#define CR1_ARPE_MSK          (0X1UL << CR1_ARPE_POS)                   
#define CR1_ARPE              CR1_ARPE_MSK                             

#define CR1_CKD_POS           (8U)                                         
#define CR1_CKD_MSK           (0X3UL << CR1_CKD_POS)                    
#define CR1_CKD               CR1_CKD_MSK                              
#define CR1_CKD_0             (0X1UL << CR1_CKD_POS)                    
#define CR1_CKD_1             (0X2UL << CR1_CKD_POS)                    

/*******************  BIT DEFINITION FOR TIM::CR2   ********************/
#define CR2_CCPC_POS          (0U)                                         
#define CR2_CCPC_MSK          (0X1UL << CR2_CCPC_POS)                   
#define CR2_CCPC              CR2_CCPC_MSK                             
#define CR2_CCUS_POS          (2U)                                         
#define CR2_CCUS_MSK          (0X1UL << CR2_CCUS_POS)                   
#define CR2_CCUS              CR2_CCUS_MSK                             
#define CR2_CCDS_POS          (3U)                                         
#define CR2_CCDS_MSK          (0X1UL << CR2_CCDS_POS)                   
#define CR2_CCDS              CR2_CCDS_MSK                             

#define CR2_MMS_POS           (4U)                                         
#define CR2_MMS_MSK           (0X7UL << CR2_MMS_POS)                    
#define CR2_MMS               CR2_MMS_MSK                              
#define CR2_MMS_0             (0X1UL << CR2_MMS_POS)                    
#define CR2_MMS_1             (0X2UL << CR2_MMS_POS)                    
#define CR2_MMS_2             (0X4UL << CR2_MMS_POS)                    

#define CR2_TI1S_POS          (7U)                                         
#define CR2_TI1S_MSK          (0X1UL << CR2_TI1S_POS)                   
#define CR2_TI1S              CR2_TI1S_MSK                             
#define CR2_OIS1_POS          (8U)                                         
#define CR2_OIS1_MSK          (0X1UL << CR2_OIS1_POS)                   
#define CR2_OIS1              CR2_OIS1_MSK                             
#define CR2_OIS1N_POS         (9U)                                         
#define CR2_OIS1N_MSK         (0X1UL << CR2_OIS1N_POS)                  
#define CR2_OIS1N             CR2_OIS1N_MSK                            
#define CR2_OIS2_POS          (10U)                                        
#define CR2_OIS2_MSK          (0X1UL << CR2_OIS2_POS)                   
#define CR2_OIS2              CR2_OIS2_MSK                             
#define CR2_OIS2N_POS         (11U)                                        
#define CR2_OIS2N_MSK         (0X1UL << CR2_OIS2N_POS)                  
#define CR2_OIS2N             CR2_OIS2N_MSK                            
#define CR2_OIS3_POS          (12U)                                        
#define CR2_OIS3_MSK          (0X1UL << CR2_OIS3_POS)                   
#define CR2_OIS3              CR2_OIS3_MSK                             
#define CR2_OIS3N_POS         (13U)                                        
#define CR2_OIS3N_MSK         (0X1UL << CR2_OIS3N_POS)                  
#define CR2_OIS3N             CR2_OIS3N_MSK                            
#define CR2_OIS4_POS          (14U)                                        
#define CR2_OIS4_MSK          (0X1UL << CR2_OIS4_POS)                   
#define CR2_OIS4              CR2_OIS4_MSK                             

/*******************  BIT DEFINITION FOR TIM::SMCR   *******************/
#define SMCR_SMS_POS          (0U)                                         
#define SMCR_SMS_MSK          (0X7UL << SMCR_SMS_POS)                   
#define SMCR_SMS              SMCR_SMS_MSK                             
#define SMCR_SMS_0            (0X1UL << SMCR_SMS_POS)                   
#define SMCR_SMS_1            (0X2UL << SMCR_SMS_POS)                   
#define SMCR_SMS_2            (0X4UL << SMCR_SMS_POS)                   

#define SMCR_TS_POS           (4U)                                         
#define SMCR_TS_MSK           (0X7UL << SMCR_TS_POS)                    
#define SMCR_TS               SMCR_TS_MSK                              
#define SMCR_TS_0             (0X1UL << SMCR_TS_POS)                    
#define SMCR_TS_1             (0X2UL << SMCR_TS_POS)                    
#define SMCR_TS_2             (0X4UL << SMCR_TS_POS)                    

#define SMCR_MSM_POS          (7U)                                         
#define SMCR_MSM_MSK          (0X1UL << SMCR_MSM_POS)                   
#define SMCR_MSM              SMCR_MSM_MSK                             

#define SMCR_ETF_POS          (8U)                                         
#define SMCR_ETF_MSK          (0XFUL << SMCR_ETF_POS)                   
#define SMCR_ETF              SMCR_ETF_MSK                             
#define SMCR_ETF_0            (0X1UL << SMCR_ETF_POS)                   
#define SMCR_ETF_1            (0X2UL << SMCR_ETF_POS)                   
#define SMCR_ETF_2            (0X4UL << SMCR_ETF_POS)                   
#define SMCR_ETF_3            (0X8UL << SMCR_ETF_POS)                   

#define SMCR_ETPS_POS         (12U)                                        
#define SMCR_ETPS_MSK         (0X3UL << SMCR_ETPS_POS)                  
#define SMCR_ETPS             SMCR_ETPS_MSK                            
#define SMCR_ETPS_0           (0X1UL << SMCR_ETPS_POS)                  
#define SMCR_ETPS_1           (0X2UL << SMCR_ETPS_POS)                  

#define SMCR_ECE_POS          (14U)                                        
#define SMCR_ECE_MSK          (0X1UL << SMCR_ECE_POS)                   
#define SMCR_ECE              SMCR_ECE_MSK                             
#define SMCR_ETP_POS          (15U)                                        
#define SMCR_ETP_MSK          (0X1UL << SMCR_ETP_POS)                   
#define SMCR_ETP              SMCR_ETP_MSK                             

/*******************  BIT DEFINITION FOR TIM::DIER   *******************/
#define DIER_UIE_POS          (0U)                                         
#define DIER_UIE_MSK          (0X1UL << DIER_UIE_POS)                   
#define DIER_UIE              DIER_UIE_MSK                             
#define DIER_CC1IE_POS        (1U)                                         
#define DIER_CC1IE_MSK        (0X1UL << DIER_CC1IE_POS)                 
#define DIER_CC1IE            DIER_CC1IE_MSK                           
#define DIER_CC2IE_POS        (2U)                                         
#define DIER_CC2IE_MSK        (0X1UL << DIER_CC2IE_POS)                 
#define DIER_CC2IE            DIER_CC2IE_MSK                           
#define DIER_CC3IE_POS        (3U)                                         
#define DIER_CC3IE_MSK        (0X1UL << DIER_CC3IE_POS)                 
#define DIER_CC3IE            DIER_CC3IE_MSK                           
#define DIER_CC4IE_POS        (4U)                                         
#define DIER_CC4IE_MSK        (0X1UL << DIER_CC4IE_POS)                 
#define DIER_CC4IE            DIER_CC4IE_MSK                           
#define DIER_COMIE_POS        (5U)                                         
#define DIER_COMIE_MSK        (0X1UL << DIER_COMIE_POS)                 
#define DIER_COMIE            DIER_COMIE_MSK                           
#define DIER_TIE_POS          (6U)                                         
#define DIER_TIE_MSK          (0X1UL << DIER_TIE_POS)                   
#define DIER_TIE              DIER_TIE_MSK                             
#define DIER_BIE_POS          (7U)                                         
#define DIER_BIE_MSK          (0X1UL << DIER_BIE_POS)                   
#define DIER_BIE              DIER_BIE_MSK                             
#define DIER_UDE_POS          (8U)                                         
#define DIER_UDE_MSK          (0X1UL << DIER_UDE_POS)                   
#define DIER_UDE              DIER_UDE_MSK                             
#define DIER_CC1DE_POS        (9U)                                         
#define DIER_CC1DE_MSK        (0X1UL << DIER_CC1DE_POS)                 
#define DIER_CC1DE            DIER_CC1DE_MSK                           
#define DIER_CC2DE_POS        (10U)                                        
#define DIER_CC2DE_MSK        (0X1UL << DIER_CC2DE_POS)                 
#define DIER_CC2DE            DIER_CC2DE_MSK                           
#define DIER_CC3DE_POS        (11U)                                        
#define DIER_CC3DE_MSK        (0X1UL << DIER_CC3DE_POS)                 
#define DIER_CC3DE            DIER_CC3DE_MSK                           
#define DIER_CC4DE_POS        (12U)                                        
#define DIER_CC4DE_MSK        (0X1UL << DIER_CC4DE_POS)                 
#define DIER_CC4DE            DIER_CC4DE_MSK                           
#define DIER_COMDE_POS        (13U)                                        
#define DIER_COMDE_MSK        (0X1UL << DIER_COMDE_POS)                 
#define DIER_COMDE            DIER_COMDE_MSK                           
#define DIER_TDE_POS          (14U)                                        
#define DIER_TDE_MSK          (0X1UL << DIER_TDE_POS)                   
#define DIER_TDE              DIER_TDE_MSK                             

/********************  BIT DEFINITION FOR TIM::SR   ********************/
#define SR_UIF_POS            (0U)                                         
#define SR_UIF_MSK            (0X1UL << SR_UIF_POS)                     
#define SR_UIF                SR_UIF_MSK                               
#define SR_CC1IF_POS          (1U)                                         
#define SR_CC1IF_MSK          (0X1UL << SR_CC1IF_POS)                   
#define SR_CC1IF              SR_CC1IF_MSK                             
#define SR_CC2IF_POS          (2U)                                         
#define SR_CC2IF_MSK          (0X1UL << SR_CC2IF_POS)                   
#define SR_CC2IF              SR_CC2IF_MSK                             
#define SR_CC3IF_POS          (3U)                                         
#define SR_CC3IF_MSK          (0X1UL << SR_CC3IF_POS)                   
#define SR_CC3IF              SR_CC3IF_MSK                             
#define SR_CC4IF_POS          (4U)                                         
#define SR_CC4IF_MSK          (0X1UL << SR_CC4IF_POS)                   
#define SR_CC4IF              SR_CC4IF_MSK                             
#define SR_COMIF_POS          (5U)                                         
#define SR_COMIF_MSK          (0X1UL << SR_COMIF_POS)                   
#define SR_COMIF              SR_COMIF_MSK                             
#define SR_TIF_POS            (6U)                                         
#define SR_TIF_MSK            (0X1UL << SR_TIF_POS)                     
#define SR_TIF                SR_TIF_MSK                               
#define SR_BIF_POS            (7U)                                         
#define SR_BIF_MSK            (0X1UL << SR_BIF_POS)                     
#define SR_BIF                SR_BIF_MSK                               
#define SR_CC1OF_POS          (9U)                                         
#define SR_CC1OF_MSK          (0X1UL << SR_CC1OF_POS)                   
#define SR_CC1OF              SR_CC1OF_MSK                             
#define SR_CC2OF_POS          (10U)                                        
#define SR_CC2OF_MSK          (0X1UL << SR_CC2OF_POS)                   
#define SR_CC2OF              SR_CC2OF_MSK                             
#define SR_CC3OF_POS          (11U)                                        
#define SR_CC3OF_MSK          (0X1UL << SR_CC3OF_POS)                   
#define SR_CC3OF              SR_CC3OF_MSK                             
#define SR_CC4OF_POS          (12U)                                        
#define SR_CC4OF_MSK          (0X1UL << SR_CC4OF_POS)                   
#define SR_CC4OF              SR_CC4OF_MSK                             

/*******************  BIT DEFINITION FOR TIM::EGR   ********************/
#define EGR_UG_POS            (0U)                                         
#define EGR_UG_MSK            (0X1UL << EGR_UG_POS)                     
#define EGR_UG                EGR_UG_MSK                               
#define EGR_CC1G_POS          (1U)                                         
#define EGR_CC1G_MSK          (0X1UL << EGR_CC1G_POS)                   
#define EGR_CC1G              EGR_CC1G_MSK                             
#define EGR_CC2G_POS          (2U)                                         
#define EGR_CC2G_MSK          (0X1UL << EGR_CC2G_POS)                   
#define EGR_CC2G              EGR_CC2G_MSK                             
#define EGR_CC3G_POS          (3U)                                         
#define EGR_CC3G_MSK          (0X1UL << EGR_CC3G_POS)                   
#define EGR_CC3G              EGR_CC3G_MSK                             
#define EGR_CC4G_POS          (4U)                                         
#define EGR_CC4G_MSK          (0X1UL << EGR_CC4G_POS)                   
#define EGR_CC4G              EGR_CC4G_MSK                             
#define EGR_COMG_POS          (5U)                                         
#define EGR_COMG_MSK          (0X1UL << EGR_COMG_POS)                   
#define EGR_COMG              EGR_COMG_MSK                             
#define EGR_TG_POS            (6U)                                         
#define EGR_TG_MSK            (0X1UL << EGR_TG_POS)                     
#define EGR_TG                EGR_TG_MSK                               
#define EGR_BG_POS            (7U)                                         
#define EGR_BG_MSK            (0X1UL << EGR_BG_POS)                     
#define EGR_BG                EGR_BG_MSK                               

/******************  BIT DEFINITION FOR TIM::CCMR1   *******************/
#define CCMR1_CC1S_POS        (0U)                                         
#define CCMR1_CC1S_MSK        (0X3UL << CCMR1_CC1S_POS)                 
#define CCMR1_CC1S            CCMR1_CC1S_MSK                           
#define CCMR1_CC1S_0          (0X1UL << CCMR1_CC1S_POS)                 
#define CCMR1_CC1S_1          (0X2UL << CCMR1_CC1S_POS)                 

#define CCMR1_OC1FE_POS       (2U)                                         
#define CCMR1_OC1FE_MSK       (0X1UL << CCMR1_OC1FE_POS)                
#define CCMR1_OC1FE           CCMR1_OC1FE_MSK                          
#define CCMR1_OC1PE_POS       (3U)                                         
#define CCMR1_OC1PE_MSK       (0X1UL << CCMR1_OC1PE_POS)                
#define CCMR1_OC1PE           CCMR1_OC1PE_MSK                          

#define CCMR1_OC1M_POS        (4U)                                         
#define CCMR1_OC1M_MSK        (0X7UL << CCMR1_OC1M_POS)                 
#define CCMR1_OC1M            CCMR1_OC1M_MSK                           
#define CCMR1_OC1M_0          (0X1UL << CCMR1_OC1M_POS)                 
#define CCMR1_OC1M_1          (0X2UL << CCMR1_OC1M_POS)                 
#define CCMR1_OC1M_2          (0X4UL << CCMR1_OC1M_POS)                 

#define CCMR1_OC1CE_POS       (7U)                                         
#define CCMR1_OC1CE_MSK       (0X1UL << CCMR1_OC1CE_POS)                
#define CCMR1_OC1CE           CCMR1_OC1CE_MSK                          

#define CCMR1_CC2S_POS        (8U)                                         
#define CCMR1_CC2S_MSK        (0X3UL << CCMR1_CC2S_POS)                 
#define CCMR1_CC2S            CCMR1_CC2S_MSK                           
#define CCMR1_CC2S_0          (0X1UL << CCMR1_CC2S_POS)                 
#define CCMR1_CC2S_1          (0X2UL << CCMR1_CC2S_POS)                 

#define CCMR1_OC2FE_POS       (10U)                                        
#define CCMR1_OC2FE_MSK       (0X1UL << CCMR1_OC2FE_POS)                
#define CCMR1_OC2FE           CCMR1_OC2FE_MSK                          
#define CCMR1_OC2PE_POS       (11U)                                        
#define CCMR1_OC2PE_MSK       (0X1UL << CCMR1_OC2PE_POS)                
#define CCMR1_OC2PE           CCMR1_OC2PE_MSK                          

#define CCMR1_OC2M_POS        (12U)                                        
#define CCMR1_OC2M_MSK        (0X7UL << CCMR1_OC2M_POS)                 
#define CCMR1_OC2M            CCMR1_OC2M_MSK                           
#define CCMR1_OC2M_0          (0X1UL << CCMR1_OC2M_POS)                 
#define CCMR1_OC2M_1          (0X2UL << CCMR1_OC2M_POS)                 
#define CCMR1_OC2M_2          (0X4UL << CCMR1_OC2M_POS)                 

#define CCMR1_OC2CE_POS       (15U)                                        
#define CCMR1_OC2CE_MSK       (0X1UL << CCMR1_OC2CE_POS)                
#define CCMR1_OC2CE           CCMR1_OC2CE_MSK                          

/*----------------------------------------------------------------------------*/

#define CCMR1_IC1PSC_POS      (2U)                                         
#define CCMR1_IC1PSC_MSK      (0X3UL << CCMR1_IC1PSC_POS)               
#define CCMR1_IC1PSC          CCMR1_IC1PSC_MSK                         
#define CCMR1_IC1PSC_0        (0X1UL << CCMR1_IC1PSC_POS)               
#define CCMR1_IC1PSC_1        (0X2UL << CCMR1_IC1PSC_POS)               

#define CCMR1_IC1F_POS        (4U)                                         
#define CCMR1_IC1F_MSK        (0XFUL << CCMR1_IC1F_POS)                 
#define CCMR1_IC1F            CCMR1_IC1F_MSK                           
#define CCMR1_IC1F_0          (0X1UL << CCMR1_IC1F_POS)                 
#define CCMR1_IC1F_1          (0X2UL << CCMR1_IC1F_POS)                 
#define CCMR1_IC1F_2          (0X4UL << CCMR1_IC1F_POS)                 
#define CCMR1_IC1F_3          (0X8UL << CCMR1_IC1F_POS)                 

#define CCMR1_IC2PSC_POS      (10U)                                        
#define CCMR1_IC2PSC_MSK      (0X3UL << CCMR1_IC2PSC_POS)               
#define CCMR1_IC2PSC          CCMR1_IC2PSC_MSK                         
#define CCMR1_IC2PSC_0        (0X1UL << CCMR1_IC2PSC_POS)               
#define CCMR1_IC2PSC_1        (0X2UL << CCMR1_IC2PSC_POS)               

#define CCMR1_IC2F_POS        (12U)                                        
#define CCMR1_IC2F_MSK        (0XFUL << CCMR1_IC2F_POS)                 
#define CCMR1_IC2F            CCMR1_IC2F_MSK                           
#define CCMR1_IC2F_0          (0X1UL << CCMR1_IC2F_POS)                 
#define CCMR1_IC2F_1          (0X2UL << CCMR1_IC2F_POS)                 
#define CCMR1_IC2F_2          (0X4UL << CCMR1_IC2F_POS)                 
#define CCMR1_IC2F_3          (0X8UL << CCMR1_IC2F_POS)                 

/******************  BIT DEFINITION FOR TIM::CCMR2   *******************/
#define CCMR2_CC3S_POS        (0U)                                         
#define CCMR2_CC3S_MSK        (0X3UL << CCMR2_CC3S_POS)                 
#define CCMR2_CC3S            CCMR2_CC3S_MSK                           
#define CCMR2_CC3S_0          (0X1UL << CCMR2_CC3S_POS)                 
#define CCMR2_CC3S_1          (0X2UL << CCMR2_CC3S_POS)                 

#define CCMR2_OC3FE_POS       (2U)                                         
#define CCMR2_OC3FE_MSK       (0X1UL << CCMR2_OC3FE_POS)                
#define CCMR2_OC3FE           CCMR2_OC3FE_MSK                          
#define CCMR2_OC3PE_POS       (3U)                                         
#define CCMR2_OC3PE_MSK       (0X1UL << CCMR2_OC3PE_POS)                
#define CCMR2_OC3PE           CCMR2_OC3PE_MSK                          

#define CCMR2_OC3M_POS        (4U)                                         
#define CCMR2_OC3M_MSK        (0X7UL << CCMR2_OC3M_POS)                 
#define CCMR2_OC3M            CCMR2_OC3M_MSK                           
#define CCMR2_OC3M_0          (0X1UL << CCMR2_OC3M_POS)                 
#define CCMR2_OC3M_1          (0X2UL << CCMR2_OC3M_POS)                 
#define CCMR2_OC3M_2          (0X4UL << CCMR2_OC3M_POS)                 

#define CCMR2_OC3CE_POS       (7U)                                         
#define CCMR2_OC3CE_MSK       (0X1UL << CCMR2_OC3CE_POS)                
#define CCMR2_OC3CE           CCMR2_OC3CE_MSK                          

#define CCMR2_CC4S_POS        (8U)                                         
#define CCMR2_CC4S_MSK        (0X3UL << CCMR2_CC4S_POS)                 
#define CCMR2_CC4S            CCMR2_CC4S_MSK                           
#define CCMR2_CC4S_0          (0X1UL << CCMR2_CC4S_POS)                 
#define CCMR2_CC4S_1          (0X2UL << CCMR2_CC4S_POS)                 

#define CCMR2_OC4FE_POS       (10U)                                        
#define CCMR2_OC4FE_MSK       (0X1UL << CCMR2_OC4FE_POS)                
#define CCMR2_OC4FE           CCMR2_OC4FE_MSK                          
#define CCMR2_OC4PE_POS       (11U)                                        
#define CCMR2_OC4PE_MSK       (0X1UL << CCMR2_OC4PE_POS)                
#define CCMR2_OC4PE           CCMR2_OC4PE_MSK                          

#define CCMR2_OC4M_POS        (12U)                                        
#define CCMR2_OC4M_MSK        (0X7UL << CCMR2_OC4M_POS)                 
#define CCMR2_OC4M            CCMR2_OC4M_MSK                           
#define CCMR2_OC4M_0          (0X1UL << CCMR2_OC4M_POS)                 
#define CCMR2_OC4M_1          (0X2UL << CCMR2_OC4M_POS)                 
#define CCMR2_OC4M_2          (0X4UL << CCMR2_OC4M_POS)                 

#define CCMR2_OC4CE_POS       (15U)                                        
#define CCMR2_OC4CE_MSK       (0X1UL << CCMR2_OC4CE_POS)                
#define CCMR2_OC4CE           CCMR2_OC4CE_MSK                          

/*----------------------------------------------------------------------------*/

#define CCMR2_IC3PSC_POS      (2U)                                         
#define CCMR2_IC3PSC_MSK      (0X3UL << CCMR2_IC3PSC_POS)               
#define CCMR2_IC3PSC          CCMR2_IC3PSC_MSK                         
#define CCMR2_IC3PSC_0        (0X1UL << CCMR2_IC3PSC_POS)               
#define CCMR2_IC3PSC_1        (0X2UL << CCMR2_IC3PSC_POS)               

#define CCMR2_IC3F_POS        (4U)                                         
#define CCMR2_IC3F_MSK        (0XFUL << CCMR2_IC3F_POS)                 
#define CCMR2_IC3F            CCMR2_IC3F_MSK                           
#define CCMR2_IC3F_0          (0X1UL << CCMR2_IC3F_POS)                 
#define CCMR2_IC3F_1          (0X2UL << CCMR2_IC3F_POS)                 
#define CCMR2_IC3F_2          (0X4UL << CCMR2_IC3F_POS)                 
#define CCMR2_IC3F_3          (0X8UL << CCMR2_IC3F_POS)                 

#define CCMR2_IC4PSC_POS      (10U)                                        
#define CCMR2_IC4PSC_MSK      (0X3UL << CCMR2_IC4PSC_POS)               
#define CCMR2_IC4PSC          CCMR2_IC4PSC_MSK                         
#define CCMR2_IC4PSC_0        (0X1UL << CCMR2_IC4PSC_POS)               
#define CCMR2_IC4PSC_1        (0X2UL << CCMR2_IC4PSC_POS)               

#define CCMR2_IC4F_POS        (12U)                                        
#define CCMR2_IC4F_MSK        (0XFUL << CCMR2_IC4F_POS)                 
#define CCMR2_IC4F            CCMR2_IC4F_MSK                           
#define CCMR2_IC4F_0          (0X1UL << CCMR2_IC4F_POS)                 
#define CCMR2_IC4F_1          (0X2UL << CCMR2_IC4F_POS)                 
#define CCMR2_IC4F_2          (0X4UL << CCMR2_IC4F_POS)                 
#define CCMR2_IC4F_3          (0X8UL << CCMR2_IC4F_POS)                 

/*******************  BIT DEFINITION FOR TIM::CCER   *******************/
#define CCER_CC1E_POS         (0U)                                         
#define CCER_CC1E_MSK         (0X1UL << CCER_CC1E_POS)                  
#define CCER_CC1E             CCER_CC1E_MSK                            
#define CCER_CC1P_POS         (1U)                                         
#define CCER_CC1P_MSK         (0X1UL << CCER_CC1P_POS)                  
#define CCER_CC1P             CCER_CC1P_MSK                            
#define CCER_CC1NE_POS        (2U)                                         
#define CCER_CC1NE_MSK        (0X1UL << CCER_CC1NE_POS)                 
#define CCER_CC1NE            CCER_CC1NE_MSK                           
#define CCER_CC1NP_POS        (3U)                                         
#define CCER_CC1NP_MSK        (0X1UL << CCER_CC1NP_POS)                 
#define CCER_CC1NP            CCER_CC1NP_MSK                           
#define CCER_CC2E_POS         (4U)                                         
#define CCER_CC2E_MSK         (0X1UL << CCER_CC2E_POS)                  
#define CCER_CC2E             CCER_CC2E_MSK                            
#define CCER_CC2P_POS         (5U)                                         
#define CCER_CC2P_MSK         (0X1UL << CCER_CC2P_POS)                  
#define CCER_CC2P             CCER_CC2P_MSK                            
#define CCER_CC2NE_POS        (6U)                                         
#define CCER_CC2NE_MSK        (0X1UL << CCER_CC2NE_POS)                 
#define CCER_CC2NE            CCER_CC2NE_MSK                           
#define CCER_CC2NP_POS        (7U)                                         
#define CCER_CC2NP_MSK        (0X1UL << CCER_CC2NP_POS)                 
#define CCER_CC2NP            CCER_CC2NP_MSK                           
#define CCER_CC3E_POS         (8U)                                         
#define CCER_CC3E_MSK         (0X1UL << CCER_CC3E_POS)                  
#define CCER_CC3E             CCER_CC3E_MSK                            
#define CCER_CC3P_POS         (9U)                                         
#define CCER_CC3P_MSK         (0X1UL << CCER_CC3P_POS)                  
#define CCER_CC3P             CCER_CC3P_MSK                            
#define CCER_CC3NE_POS        (10U)                                        
#define CCER_CC3NE_MSK        (0X1UL << CCER_CC3NE_POS)                 
#define CCER_CC3NE            CCER_CC3NE_MSK                           
#define CCER_CC3NP_POS        (11U)                                        
#define CCER_CC3NP_MSK        (0X1UL << CCER_CC3NP_POS)                 
#define CCER_CC3NP            CCER_CC3NP_MSK                           
#define CCER_CC4E_POS         (12U)                                        
#define CCER_CC4E_MSK         (0X1UL << CCER_CC4E_POS)                  
#define CCER_CC4E             CCER_CC4E_MSK                            
#define CCER_CC4P_POS         (13U)                                        
#define CCER_CC4P_MSK         (0X1UL << CCER_CC4P_POS)                  
#define CCER_CC4P             CCER_CC4P_MSK                            
#define CCER_CC4NP_POS        (15U)                                        
#define CCER_CC4NP_MSK        (0X1UL << CCER_CC4NP_POS)                 
#define CCER_CC4NP            CCER_CC4NP_MSK                           

/*******************  BIT DEFINITION FOR TIM::CNT   ********************/
#define CNT_CNT_POS           (0U)                                             
#define CNT_CNT_MSK           (0XFFFFFFFFUL << CNT_CNT_POS)                 
#define CNT_CNT               CNT_CNT_MSK                                  

/*******************  BIT DEFINITION FOR TIM::PSC   ********************/
#define PSC_PSC_POS           (0U)                                         
#define PSC_PSC_MSK           (0XFFFFUL << PSC_PSC_POS)                 
#define PSC_PSC               PSC_PSC_MSK                              

/*******************  BIT DEFINITION FOR TIM::ARR   ********************/
#define ARR_ARR_POS           (0U)                                         
#define ARR_ARR_MSK           (0XFFFFFFFFUL << ARR_ARR_POS)             
#define ARR_ARR               ARR_ARR_MSK                              

/*******************  BIT DEFINITION FOR TIM::RCR   ********************/
#define RCR_REP_POS           (0U)                                         
#define RCR_REP_MSK           (0XFFUL << RCR_REP_POS)                   
#define RCR_REP               RCR_REP_MSK                              

/*******************  BIT DEFINITION FOR TIM::CCR1   *******************/
#define CCR1_CCR1_POS         (0U)                                         
#define CCR1_CCR1_MSK         (0XFFFFUL << CCR1_CCR1_POS)               
#define CCR1_CCR1             CCR1_CCR1_MSK                            

/*******************  BIT DEFINITION FOR TIM::CCR2   *******************/
#define CCR2_CCR2_POS         (0U)                                         
#define CCR2_CCR2_MSK         (0XFFFFUL << CCR2_CCR2_POS)               
#define CCR2_CCR2             CCR2_CCR2_MSK                            

/*******************  BIT DEFINITION FOR TIM::CCR3   *******************/
#define CCR3_CCR3_POS         (0U)                                         
#define CCR3_CCR3_MSK         (0XFFFFUL << CCR3_CCR3_POS)               
#define CCR3_CCR3             CCR3_CCR3_MSK                            

/*******************  BIT DEFINITION FOR TIM::CCR4   *******************/
#define CCR4_CCR4_POS         (0U)                                         
#define CCR4_CCR4_MSK         (0XFFFFUL << CCR4_CCR4_POS)               
#define CCR4_CCR4             CCR4_CCR4_MSK                            

/*******************  BIT DEFINITION FOR TIM::BDTR   *******************/
#define BDTR_DTG_POS          (0U)                                         
#define BDTR_DTG_MSK          (0XFFUL << BDTR_DTG_POS)                  
#define BDTR_DTG              BDTR_DTG_MSK                             
#define BDTR_DTG_0            (0X01UL << BDTR_DTG_POS)                  
#define BDTR_DTG_1            (0X02UL << BDTR_DTG_POS)                  
#define BDTR_DTG_2            (0X04UL << BDTR_DTG_POS)                  
#define BDTR_DTG_3            (0X08UL << BDTR_DTG_POS)                  
#define BDTR_DTG_4            (0X10UL << BDTR_DTG_POS)                  
#define BDTR_DTG_5            (0X20UL << BDTR_DTG_POS)                  
#define BDTR_DTG_6            (0X40UL << BDTR_DTG_POS)                  
#define BDTR_DTG_7            (0X80UL << BDTR_DTG_POS)                  

#define BDTR_LOCK_POS         (8U)                                         
#define BDTR_LOCK_MSK         (0X3UL << BDTR_LOCK_POS)                  
#define BDTR_LOCK             BDTR_LOCK_MSK                            
#define BDTR_LOCK_0           (0X1UL << BDTR_LOCK_POS)                  
#define BDTR_LOCK_1           (0X2UL << BDTR_LOCK_POS)                  

#define BDTR_OSSI_POS         (10U)                                        
#define BDTR_OSSI_MSK         (0X1UL << BDTR_OSSI_POS)                  
#define BDTR_OSSI             BDTR_OSSI_MSK                            
#define BDTR_OSSR_POS         (11U)                                        
#define BDTR_OSSR_MSK         (0X1UL << BDTR_OSSR_POS)                  
#define BDTR_OSSR             BDTR_OSSR_MSK                            
#define BDTR_BKE_POS          (12U)                                        
#define BDTR_BKE_MSK          (0X1UL << BDTR_BKE_POS)                   
#define BDTR_BKE              BDTR_BKE_MSK                             
#define BDTR_BKP_POS          (13U)                                        
#define BDTR_BKP_MSK          (0X1UL << BDTR_BKP_POS)                   
#define BDTR_BKP              BDTR_BKP_MSK                             
#define BDTR_AOE_POS          (14U)                                        
#define BDTR_AOE_MSK          (0X1UL << BDTR_AOE_POS)                   
#define BDTR_AOE              BDTR_AOE_MSK                             
#define BDTR_MOE_POS          (15U)                                        
#define BDTR_MOE_MSK          (0X1UL << BDTR_MOE_POS)                   
#define BDTR_MOE              BDTR_MOE_MSK                             

/*******************  BIT DEFINITION FOR TIM::DCR   ********************/
#define DCR_DBA_POS           (0U)                                         
#define DCR_DBA_MSK           (0X1FUL << DCR_DBA_POS)                   
#define DCR_DBA               DCR_DBA_MSK                              
#define DCR_DBA_0             (0X01UL << DCR_DBA_POS)                   
#define DCR_DBA_1             (0X02UL << DCR_DBA_POS)                   
#define DCR_DBA_2             (0X04UL << DCR_DBA_POS)                   
#define DCR_DBA_3             (0X08UL << DCR_DBA_POS)                   
#define DCR_DBA_4             (0X10UL << DCR_DBA_POS)                   

#define DCR_DBL_POS           (8U)                                         
#define DCR_DBL_MSK           (0X1FUL << DCR_DBL_POS)                   
#define DCR_DBL               DCR_DBL_MSK                              
#define DCR_DBL_0             (0X01UL << DCR_DBL_POS)                   
#define DCR_DBL_1             (0X02UL << DCR_DBL_POS)                   
#define DCR_DBL_2             (0X04UL << DCR_DBL_POS)                   
#define DCR_DBL_3             (0X08UL << DCR_DBL_POS)                   
#define DCR_DBL_4             (0X10UL << DCR_DBL_POS)                   

/*******************  BIT DEFINITION FOR TIM::DMAR   *******************/
#define DMAR_DMAB_POS         (0U)                                         
#define DMAR_DMAB_MSK         (0XFFFFUL << DMAR_DMAB_POS)               
#define DMAR_DMAB             DMAR_DMAB_MSK                            

/*******************  BIT DEFINITION FOR TIM::OR   *********************/
#define OR_TI1_RMP_POS        (0U)                                          
#define OR_TI1_RMP_MSK        (0X3UL << OR_TI1_RMP_POS)                 
#define OR_TI1_RMP            OR_TI1_RMP_MSK                           
#define OR_TI1_RMP_0          (0X1UL << OR_TI1_RMP_POS)                 
#define OR_TI1_RMP_1          (0X2UL << OR_TI1_RMP_POS)                 

#define OR_TI4_RMP_POS        (6U)                                         
#define OR_TI4_RMP_MSK        (0X3UL << OR_TI4_RMP_POS)                 
#define OR_TI4_RMP            OR_TI4_RMP_MSK                           
#define OR_TI4_RMP_0          (0X1UL << OR_TI4_RMP_POS)                 
#define OR_TI4_RMP_1          (0X2UL << OR_TI4_RMP_POS)                 
#define OR_ITR1_RMP_POS       (10U)                                        
#define OR_ITR1_RMP_MSK       (0X3UL << OR_ITR1_RMP_POS)                
#define OR_ITR1_RMP           OR_ITR1_RMP_MSK                          
#define OR_ITR1_RMP_0         (0X1UL << OR_ITR1_RMP_POS)                
#define OR_ITR1_RMP_1         (0X2UL << OR_ITR1_RMP_POS)                

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_TIMER_REGISTER_MASKS */