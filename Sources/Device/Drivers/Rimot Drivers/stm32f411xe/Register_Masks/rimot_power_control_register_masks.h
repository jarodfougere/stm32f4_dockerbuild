#ifndef RIMOT_PWR_CTL_REGISTER_MASKS
#define RIMOT_PWR_CTL_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/********************  BIT DEFINITION FOR PWR::CR   ********************/
#define CR_LPDS_POS        (0U)                                            
#define CR_LPDS_MSK        (0X1UL << CR_LPDS_POS)                       
#define CR_LPDS            CR_LPDS_MSK                                 
#define CR_PDDS_POS        (1U)                                            
#define CR_PDDS_MSK        (0X1UL << CR_PDDS_POS)                       
#define CR_PDDS            CR_PDDS_MSK                                 
#define CR_CWUF_POS        (2U)                                            
#define CR_CWUF_MSK        (0X1UL << CR_CWUF_POS)                       
#define CR_CWUF            CR_CWUF_MSK                                 
#define CR_CSBF_POS        (3U)                                            
#define CR_CSBF_MSK        (0X1UL << CR_CSBF_POS)                       
#define CR_CSBF            CR_CSBF_MSK                                 
#define CR_PVDE_POS        (4U)                                            
#define CR_PVDE_MSK        (0X1UL << CR_PVDE_POS)                       
#define CR_PVDE            CR_PVDE_MSK                                 

#define CR_PLS_POS         (5U)                                            
#define CR_PLS_MSK         (0X7UL << CR_PLS_POS)                        
#define CR_PLS             CR_PLS_MSK                                  
#define CR_PLS_0           (0X1UL << CR_PLS_POS)                        
#define CR_PLS_1           (0X2UL << CR_PLS_POS)                        
#define CR_PLS_2           (0X4UL << CR_PLS_POS)                        

#define CR_PLS_LEV0        0X00000000U                                     
#define CR_PLS_LEV1        0X00000020U                                     
#define CR_PLS_LEV2        0X00000040U                                     
#define CR_PLS_LEV3        0X00000060U                                     
#define CR_PLS_LEV4        0X00000080U                                     
#define CR_PLS_LEV5        0X000000A0U                                     
#define CR_PLS_LEV6        0X000000C0U                                     
#define CR_PLS_LEV7        0X000000E0U                                     
#define CR_DBP_POS         (8U)                                            
#define CR_DBP_MSK         (0X1UL << CR_DBP_POS)                        
#define CR_DBP             CR_DBP_MSK                                  
#define CR_FPDS_POS        (9U)                                            
#define CR_FPDS_MSK        (0X1UL << CR_FPDS_POS)                       
#define CR_FPDS            CR_FPDS_MSK                                 
#define CR_LPLVDS_POS      (10U)                                           
#define CR_LPLVDS_MSK      (0X1UL << CR_LPLVDS_POS)                     
#define CR_LPLVDS          CR_LPLVDS_MSK                               
#define CR_MRLVDS_POS      (11U)                                           
#define CR_MRLVDS_MSK      (0X1UL << CR_MRLVDS_POS)                     
#define CR_MRLVDS          CR_MRLVDS_MSK                               
#define CR_ADCDC1_POS      (13U)                                           
#define CR_ADCDC1_MSK      (0X1UL << CR_ADCDC1_POS)                     
#define CR_ADCDC1          CR_ADCDC1_MSK                                
#define CR_VOS_POS         (14U)                                           
#define CR_VOS_MSK         (0X3UL << CR_VOS_POS)                        
#define CR_VOS             CR_VOS_MSK                                  
#define CR_VOS_0           0X00004000U                                     
#define CR_VOS_1           0X00008000U                                     
#define CR_FMSSR_POS       (20U)                                           
#define CR_FMSSR_MSK       (0X1UL << CR_FMSSR_POS)                      
#define CR_FMSSR           CR_FMSSR_MSK                                
#define CR_FISSR_POS       (21U)                                           
#define CR_FISSR_MSK       (0X1UL << CR_FISSR_POS)                      
#define CR_FISSR           CR_FISSR_MSK                                

/*******************  BIT DEFINITION FOR PWR::CSR   ********************/
#define CSR_WUF_POS        (0U)                                            
#define CSR_WUF_MSK        (0X1UL << CSR_WUF_POS)                       
#define CSR_WUF            CSR_WUF_MSK                                 
#define CSR_SBF_POS        (1U)                                            
#define CSR_SBF_MSK        (0X1UL << CSR_SBF_POS)                       
#define CSR_SBF            CSR_SBF_MSK                                 
#define CSR_PVDO_POS       (2U)                                            
#define CSR_PVDO_MSK       (0X1UL << CSR_PVDO_POS)                      
#define CSR_PVDO           CSR_PVDO_MSK                                
#define CSR_BRR_POS        (3U)                                            
#define CSR_BRR_MSK        (0X1UL << CSR_BRR_POS)                       
#define CSR_BRR            CSR_BRR_MSK                                 
#define CSR_EWUP_POS       (8U)                                            
#define CSR_EWUP_MSK       (0X1UL << CSR_EWUP_POS)                      
#define CSR_EWUP           CSR_EWUP_MSK                                
#define CSR_BRE_POS        (9U)                                            
#define CSR_BRE_MSK        (0X1UL << CSR_BRE_POS)                       
#define CSR_BRE            CSR_BRE_MSK                                 
#define CSR_VOSRDY_POS     (14U)                                           
#define CSR_VOSRDY_MSK     (0X1UL << CSR_VOSRDY_POS)                    
#define CSR_VOSRDY         CSR_VOSRDY_MSK                              

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_PWR_CTL_REGISTER_MASKS */
