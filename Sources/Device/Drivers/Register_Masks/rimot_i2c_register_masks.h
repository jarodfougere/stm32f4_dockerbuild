#ifndef RIMOT_I2C_REGISTER_MASKS
#define RIMOT_I2C_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BIT DEFINITION FOR I2C::CR1   ********************/
#define CR1_PE_POS            (0U)                                         
#define CR1_PE_MSK            (0X1UL << CR1_PE_POS)                     
#define CR1_PE                CR1_PE_MSK                               
#define CR1_SMBUS_POS         (1U)                                         
#define CR1_SMBUS_MSK         (0X1UL << CR1_SMBUS_POS)                  
#define CR1_SMBUS             CR1_SMBUS_MSK                            
#define CR1_SMBTYPE_POS       (3U)                                         
#define CR1_SMBTYPE_MSK       (0X1UL << CR1_SMBTYPE_POS)                
#define CR1_SMBTYPE           CR1_SMBTYPE_MSK                          
#define CR1_ENARP_POS         (4U)                                         
#define CR1_ENARP_MSK         (0X1UL << CR1_ENARP_POS)                  
#define CR1_ENARP             CR1_ENARP_MSK                            
#define CR1_ENPEC_POS         (5U)                                         
#define CR1_ENPEC_MSK         (0X1UL << CR1_ENPEC_POS)                  
#define CR1_ENPEC             CR1_ENPEC_MSK                            
#define CR1_ENGC_POS          (6U)                                         
#define CR1_ENGC_MSK          (0X1UL << CR1_ENGC_POS)                   
#define CR1_ENGC              CR1_ENGC_MSK                             
#define CR1_NOSTRETCH_POS     (7U)                                         
#define CR1_NOSTRETCH_MSK     (0X1UL << CR1_NOSTRETCH_POS)              
#define CR1_NOSTRETCH         CR1_NOSTRETCH_MSK                        
#define CR1_START_POS         (8U)                                         
#define CR1_START_MSK         (0X1UL << CR1_START_POS)                  
#define CR1_START             CR1_START_MSK                            
#define CR1_STOP_POS          (9U)                                         
#define CR1_STOP_MSK          (0X1UL << CR1_STOP_POS)                   
#define CR1_STOP              CR1_STOP_MSK                             
#define CR1_ACK_POS           (10U)                                        
#define CR1_ACK_MSK           (0X1UL << CR1_ACK_POS)                    
#define CR1_ACK               CR1_ACK_MSK                              
#define CR1_POS_POS           (11U)                                        
#define CR1_POS_MSK           (0X1UL << CR1_POS_POS)                    
#define CR1_POS               CR1_POS_MSK                              
#define CR1_PEC_POS           (12U)                                        
#define CR1_PEC_MSK           (0X1UL << CR1_PEC_POS)                    
#define CR1_PEC               CR1_PEC_MSK                              
#define CR1_ALERT_POS         (13U)                                        
#define CR1_ALERT_MSK         (0X1UL << CR1_ALERT_POS)                  
#define CR1_ALERT             CR1_ALERT_MSK                            
#define CR1_SWRST_POS         (15U)                                        
#define CR1_SWRST_MSK         (0X1UL << CR1_SWRST_POS)                  
#define CR1_SWRST             CR1_SWRST_MSK                            

/*******************  BIT DEFINITION FOR I2C::CR2   ********************/
#define CR2_FREQ_POS          (0U)                                         
#define CR2_FREQ_MSK          (0X3FUL << CR2_FREQ_POS)                  
#define CR2_FREQ              CR2_FREQ_MSK                             
#define CR2_FREQ_0            (0X01UL << CR2_FREQ_POS)                  
#define CR2_FREQ_1            (0X02UL << CR2_FREQ_POS)                  
#define CR2_FREQ_2            (0X04UL << CR2_FREQ_POS)                  
#define CR2_FREQ_3            (0X08UL << CR2_FREQ_POS)                  
#define CR2_FREQ_4            (0X10UL << CR2_FREQ_POS)                  
#define CR2_FREQ_5            (0X20UL << CR2_FREQ_POS)                  

#define CR2_ITERREN_POS       (8U)                                         
#define CR2_ITERREN_MSK       (0X1UL << CR2_ITERREN_POS)                
#define CR2_ITERREN           CR2_ITERREN_MSK                          
#define CR2_ITEVTEN_POS       (9U)                                         
#define CR2_ITEVTEN_MSK       (0X1UL << CR2_ITEVTEN_POS)                
#define CR2_ITEVTEN           CR2_ITEVTEN_MSK                          
#define CR2_ITBUFEN_POS       (10U)                                        
#define CR2_ITBUFEN_MSK       (0X1UL << CR2_ITBUFEN_POS)                
#define CR2_ITBUFEN           CR2_ITBUFEN_MSK                          
#define CR2_DMAEN_POS         (11U)                                        
#define CR2_DMAEN_MSK         (0X1UL << CR2_DMAEN_POS)                  
#define CR2_DMAEN             CR2_DMAEN_MSK                            
#define CR2_LAST_POS          (12U)                                        
#define CR2_LAST_MSK          (0X1UL << CR2_LAST_POS)                   
#define CR2_LAST              CR2_LAST_MSK                             

/*******************  BIT DEFINITION FOR I2C::OAR1   *******************/
#define OAR1_ADD1_7           0X000000FEU                                  
#define OAR1_ADD8_9           0X00000300U                                  

#define OAR1_ADD0_POS         (0U)                                         
#define OAR1_ADD0_MSK         (0X1UL << OAR1_ADD0_POS)                  
#define OAR1_ADD0             OAR1_ADD0_MSK                            
#define OAR1_ADD1_POS         (1U)                                         
#define OAR1_ADD1_MSK         (0X1UL << OAR1_ADD1_POS)                  
#define OAR1_ADD1             OAR1_ADD1_MSK                            
#define OAR1_ADD2_POS         (2U)                                         
#define OAR1_ADD2_MSK         (0X1UL << OAR1_ADD2_POS)                  
#define OAR1_ADD2             OAR1_ADD2_MSK                            
#define OAR1_ADD3_POS         (3U)                                         
#define OAR1_ADD3_MSK         (0X1UL << OAR1_ADD3_POS)                  
#define OAR1_ADD3             OAR1_ADD3_MSK                            
#define OAR1_ADD4_POS         (4U)                                         
#define OAR1_ADD4_MSK         (0X1UL << OAR1_ADD4_POS)                  
#define OAR1_ADD4             OAR1_ADD4_MSK                            
#define OAR1_ADD5_POS         (5U)                                         
#define OAR1_ADD5_MSK         (0X1UL << OAR1_ADD5_POS)                  
#define OAR1_ADD5             OAR1_ADD5_MSK                            
#define OAR1_ADD6_POS         (6U)                                         
#define OAR1_ADD6_MSK         (0X1UL << OAR1_ADD6_POS)                  
#define OAR1_ADD6             OAR1_ADD6_MSK                            
#define OAR1_ADD7_POS         (7U)                                         
#define OAR1_ADD7_MSK         (0X1UL << OAR1_ADD7_POS)                  
#define OAR1_ADD7             OAR1_ADD7_MSK                            
#define OAR1_ADD8_POS         (8U)                                         
#define OAR1_ADD8_MSK         (0X1UL << OAR1_ADD8_POS)                  
#define OAR1_ADD8             OAR1_ADD8_MSK                            
#define OAR1_ADD9_POS         (9U)                                         
#define OAR1_ADD9_MSK         (0X1UL << OAR1_ADD9_POS)                  
#define OAR1_ADD9             OAR1_ADD9_MSK                            

#define OAR1_ADDMODE_POS      (15U)                                        
#define OAR1_ADDMODE_MSK      (0X1UL << OAR1_ADDMODE_POS)               
#define OAR1_ADDMODE          OAR1_ADDMODE_MSK                         

/*******************  BIT DEFINITION FOR I2C::OAR2   *******************/
#define OAR2_ENDUAL_POS       (0U)                                         
#define OAR2_ENDUAL_MSK       (0X1UL << OAR2_ENDUAL_POS)                
#define OAR2_ENDUAL           OAR2_ENDUAL_MSK                          
#define OAR2_ADD2_POS         (1U)                                         
#define OAR2_ADD2_MSK         (0X7FUL << OAR2_ADD2_POS)                 
#define OAR2_ADD2             OAR2_ADD2_MSK                            

/********************  BIT DEFINITION FOR I2C::DR   ********************/
#define DR_DR_POS             (0U)                                         
#define DR_DR_MSK             (0XFFUL << DR_DR_POS)                     
#define DR_DR                 DR_DR_MSK                                

/*******************  BIT DEFINITION FOR I2C::SR1   ********************/
#define SR1_SB_POS            (0U)                                         
#define SR1_SB_MSK            (0X1UL << SR1_SB_POS)                     
#define SR1_SB                SR1_SB_MSK                               
#define SR1_ADDR_POS          (1U)                                         
#define SR1_ADDR_MSK          (0X1UL << SR1_ADDR_POS)                   
#define SR1_ADDR              SR1_ADDR_MSK                             
#define SR1_BTF_POS           (2U)                                         
#define SR1_BTF_MSK           (0X1UL << SR1_BTF_POS)                    
#define SR1_BTF               SR1_BTF_MSK                              
#define SR1_ADD10_POS         (3U)                                         
#define SR1_ADD10_MSK         (0X1UL << SR1_ADD10_POS)                  
#define SR1_ADD10             SR1_ADD10_MSK                            
#define SR1_STOPF_POS         (4U)                                         
#define SR1_STOPF_MSK         (0X1UL << SR1_STOPF_POS)                  
#define SR1_STOPF             SR1_STOPF_MSK                            
#define SR1_RXNE_POS          (6U)                                         
#define SR1_RXNE_MSK          (0X1UL << SR1_RXNE_POS)                   
#define SR1_RXNE              SR1_RXNE_MSK                             
#define SR1_TXE_POS           (7U)                                         
#define SR1_TXE_MSK           (0X1UL << SR1_TXE_POS)                    
#define SR1_TXE               SR1_TXE_MSK                              
#define SR1_BERR_POS          (8U)                                         
#define SR1_BERR_MSK          (0X1UL << SR1_BERR_POS)                   
#define SR1_BERR              SR1_BERR_MSK                             
#define SR1_ARLO_POS          (9U)                                         
#define SR1_ARLO_MSK          (0X1UL << SR1_ARLO_POS)                   
#define SR1_ARLO              SR1_ARLO_MSK                             
#define SR1_AF_POS            (10U)                                        
#define SR1_AF_MSK            (0X1UL << SR1_AF_POS)                     
#define SR1_AF                SR1_AF_MSK                               
#define SR1_OVR_POS           (11U)                                        
#define SR1_OVR_MSK           (0X1UL << SR1_OVR_POS)                    
#define SR1_OVR               SR1_OVR_MSK                              
#define SR1_PECERR_POS        (12U)                                        
#define SR1_PECERR_MSK        (0X1UL << SR1_PECERR_POS)                 
#define SR1_PECERR            SR1_PECERR_MSK                           
#define SR1_TIMEOUT_POS       (14U)                                        
#define SR1_TIMEOUT_MSK       (0X1UL << SR1_TIMEOUT_POS)                
#define SR1_TIMEOUT           SR1_TIMEOUT_MSK                          
#define SR1_SMBALERT_POS      (15U)                                        
#define SR1_SMBALERT_MSK      (0X1UL << SR1_SMBALERT_POS)               
#define SR1_SMBALERT          SR1_SMBALERT_MSK                         

/*******************  BIT DEFINITION FOR I2C::SR2   ********************/
#define SR2_MSL_POS           (0U)                                         
#define SR2_MSL_MSK           (0X1UL << SR2_MSL_POS)                    
#define SR2_MSL               SR2_MSL_MSK                              
#define SR2_BUSY_POS          (1U)                                         
#define SR2_BUSY_MSK          (0X1UL << SR2_BUSY_POS)                   
#define SR2_BUSY              SR2_BUSY_MSK                             
#define SR2_TRA_POS           (2U)                                         
#define SR2_TRA_MSK           (0X1UL << SR2_TRA_POS)                    
#define SR2_TRA               SR2_TRA_MSK                              
#define SR2_GENCALL_POS       (4U)                                         
#define SR2_GENCALL_MSK       (0X1UL << SR2_GENCALL_POS)                
#define SR2_GENCALL           SR2_GENCALL_MSK                          
#define SR2_SMBDEFAULT_POS    (5U)                                         
#define SR2_SMBDEFAULT_MSK    (0X1UL << SR2_SMBDEFAULT_POS)             
#define SR2_SMBDEFAULT        SR2_SMBDEFAULT_MSK                       
#define SR2_SMBHOST_POS       (6U)                                         
#define SR2_SMBHOST_MSK       (0X1UL << SR2_SMBHOST_POS)                
#define SR2_SMBHOST           SR2_SMBHOST_MSK                          
#define SR2_DUALF_POS         (7U)                                         
#define SR2_DUALF_MSK         (0X1UL << SR2_DUALF_POS)                  
#define SR2_DUALF             SR2_DUALF_MSK                            
#define SR2_PEC_POS           (8U)                                         
#define SR2_PEC_MSK           (0XFFUL << SR2_PEC_POS)                   
#define SR2_PEC               SR2_PEC_MSK                              

/*******************  BIT DEFINITION FOR I2C::CCR   ********************/
#define CCR_CCR_POS           (0U)                                         
#define CCR_CCR_MSK           (0XFFFUL << CCR_CCR_POS)                  
#define CCR_CCR               CCR_CCR_MSK                              
#define CCR_DUTY_POS          (14U)                                        
#define CCR_DUTY_MSK          (0X1UL << CCR_DUTY_POS)                   
#define CCR_DUTY              CCR_DUTY_MSK                             
#define CCR_FS_POS            (15U)                                        
#define CCR_FS_MSK            (0X1UL << CCR_FS_POS)                     
#define CCR_FS                CCR_FS_MSK                               

/******************  BIT DEFINITION FOR I2C::TRISE   *******************/
#define TRISE_TRISE_POS       (0U)                                         
#define TRISE_TRISE_MSK       (0X3FUL << TRISE_TRISE_POS)               
#define TRISE_TRISE           TRISE_TRISE_MSK                          

/******************  BIT DEFINITION FOR I2C::FLTR   *******************/
#define FLTR_DNF_POS          (0U)                                         
#define FLTR_DNF_MSK          (0XFUL << FLTR_DNF_POS)                   
#define FLTR_DNF              FLTR_DNF_MSK                             
#define FLTR_ANOFF_POS        (4U)                                         
#define FLTR_ANOFF_MSK        (0X1UL << FLTR_ANOFF_POS)                 
#define FLTR_ANOFF            FLTR_ANOFF_MSK                           


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_I2C_REGISTER_MASKS */
