#ifndef RIMOT_SPI_REGISTER_MASKS
#define RIMOT_SPI_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BIT DEFINITION FOR SPI::CR1   ********************/
#define CR1_CPHA_POS            (0U)                                       
#define CR1_CPHA_MSK            (0X1UL << CR1_CPHA_POS)                 
#define CR1_CPHA                CR1_CPHA_MSK                           
#define CR1_CPOL_POS            (1U)                                       
#define CR1_CPOL_MSK            (0X1UL << CR1_CPOL_POS)                 
#define CR1_CPOL                CR1_CPOL_MSK                           
#define CR1_MSTR_POS            (2U)                                       
#define CR1_MSTR_MSK            (0X1UL << CR1_MSTR_POS)                 
#define CR1_MSTR                CR1_MSTR_MSK                           

#define CR1_BR_POS              (3U)                                       
#define CR1_BR_MSK              (0X7UL << CR1_BR_POS)                   
#define CR1_BR                  CR1_BR_MSK                             
#define CR1_BR_0                (0X1UL << CR1_BR_POS)                   
#define CR1_BR_1                (0X2UL << CR1_BR_POS)                   
#define CR1_BR_2                (0X4UL << CR1_BR_POS)                   

#define CR1_SPE_POS             (6U)                                       
#define CR1_SPE_MSK             (0X1UL << CR1_SPE_POS)                  
#define CR1_SPE                 CR1_SPE_MSK                            
#define CR1_LSBFIRST_POS        (7U)                                       
#define CR1_LSBFIRST_MSK        (0X1UL << CR1_LSBFIRST_POS)             
#define CR1_LSBFIRST            CR1_LSBFIRST_MSK                       
#define CR1_SSI_POS             (8U)                                       
#define CR1_SSI_MSK             (0X1UL << CR1_SSI_POS)                  
#define CR1_SSI                 CR1_SSI_MSK                            
#define CR1_SSM_POS             (9U)                                       
#define CR1_SSM_MSK             (0X1UL << CR1_SSM_POS)                  
#define CR1_SSM                 CR1_SSM_MSK                            
#define CR1_RXONLY_POS          (10U)                                      
#define CR1_RXONLY_MSK          (0X1UL << CR1_RXONLY_POS)               
#define CR1_RXONLY              CR1_RXONLY_MSK                         
#define CR1_DFF_POS             (11U)                                      
#define CR1_DFF_MSK             (0X1UL << CR1_DFF_POS)                  
#define CR1_DFF                 CR1_DFF_MSK                            
#define CR1_CRCNEXT_POS         (12U)                                      
#define CR1_CRCNEXT_MSK         (0X1UL << CR1_CRCNEXT_POS)              
#define CR1_CRCNEXT             CR1_CRCNEXT_MSK                        
#define CR1_CRCEN_POS           (13U)                                      
#define CR1_CRCEN_MSK           (0X1UL << CR1_CRCEN_POS)                
#define CR1_CRCEN               CR1_CRCEN_MSK                          
#define CR1_BIDIOE_POS          (14U)                                      
#define CR1_BIDIOE_MSK          (0X1UL << CR1_BIDIOE_POS)               
#define CR1_BIDIOE              CR1_BIDIOE_MSK                         
#define CR1_BIDIMODE_POS        (15U)                                      
#define CR1_BIDIMODE_MSK        (0X1UL << CR1_BIDIMODE_POS)             
#define CR1_BIDIMODE            CR1_BIDIMODE_MSK                       

/*******************  BIT DEFINITION FOR SPI::CR2   ********************/
#define CR2_RXDMAEN_POS         (0U)                                       
#define CR2_RXDMAEN_MSK         (0X1UL << CR2_RXDMAEN_POS)              
#define CR2_RXDMAEN             CR2_RXDMAEN_MSK                        
#define CR2_TXDMAEN_POS         (1U)                                       
#define CR2_TXDMAEN_MSK         (0X1UL << CR2_TXDMAEN_POS)              
#define CR2_TXDMAEN             CR2_TXDMAEN_MSK                        
#define CR2_SSOE_POS            (2U)                                       
#define CR2_SSOE_MSK            (0X1UL << CR2_SSOE_POS)                 
#define CR2_SSOE                CR2_SSOE_MSK                           
#define CR2_FRF_POS             (4U)                                       
#define CR2_FRF_MSK             (0X1UL << CR2_FRF_POS)                  
#define CR2_FRF                 CR2_FRF_MSK                            
#define CR2_ERRIE_POS           (5U)                                       
#define CR2_ERRIE_MSK           (0X1UL << CR2_ERRIE_POS)                
#define CR2_ERRIE               CR2_ERRIE_MSK                          
#define CR2_RXNEIE_POS          (6U)                                       
#define CR2_RXNEIE_MSK          (0X1UL << CR2_RXNEIE_POS)               
#define CR2_RXNEIE              CR2_RXNEIE_MSK                         
#define CR2_TXEIE_POS           (7U)                                       
#define CR2_TXEIE_MSK           (0X1UL << CR2_TXEIE_POS)                
#define CR2_TXEIE               CR2_TXEIE_MSK                          

/********************  BIT DEFINITION FOR SPI::SR   ********************/
#define SR_RXNE_POS             (0U)                                       
#define SR_RXNE_MSK             (0X1UL << SR_RXNE_POS)                  
#define SR_RXNE                 SR_RXNE_MSK                            
#define SR_TXE_POS              (1U)                                       
#define SR_TXE_MSK              (0X1UL << SR_TXE_POS)                   
#define SR_TXE                  SR_TXE_MSK                             
#define SR_CHSIDE_POS           (2U)                                       
#define SR_CHSIDE_MSK           (0X1UL << SR_CHSIDE_POS)                
#define SR_CHSIDE               SR_CHSIDE_MSK                          
#define SR_UDR_POS              (3U)                                       
#define SR_UDR_MSK              (0X1UL << SR_UDR_POS)                   
#define SR_UDR                  SR_UDR_MSK                             
#define SR_CRCERR_POS           (4U)                                       
#define SR_CRCERR_MSK           (0X1UL << SR_CRCERR_POS)                
#define SR_CRCERR               SR_CRCERR_MSK                          
#define SR_MODF_POS             (5U)                                       
#define SR_MODF_MSK             (0X1UL << SR_MODF_POS)                  
#define SR_MODF                 SR_MODF_MSK                            
#define SR_OVR_POS              (6U)                                       
#define SR_OVR_MSK              (0X1UL << SR_OVR_POS)                   
#define SR_OVR                  SR_OVR_MSK                             
#define SR_BSY_POS              (7U)                                       
#define SR_BSY_MSK              (0X1UL << SR_BSY_POS)                   
#define SR_BSY                  SR_BSY_MSK                             
#define SR_FRE_POS              (8U)                                       
#define SR_FRE_MSK              (0X1UL << SR_FRE_POS)                   
#define SR_FRE                  SR_FRE_MSK                             

/********************  BIT DEFINITION FOR SPI::DR   ********************/
#define DR_DR_POS               (0U)                                       
#define DR_DR_MSK               (0XFFFFUL << DR_DR_POS)                 
#define DR_DR                   DR_DR_MSK                              

/*******************  BIT DEFINITION FOR SPI::CRCPR   ******************/
#define CRCPR_CRCPOLY_POS       (0U)                                       
#define CRCPR_CRCPOLY_MSK       (0XFFFFUL << CRCPR_CRCPOLY_POS)         
#define CRCPR_CRCPOLY           CRCPR_CRCPOLY_MSK                      

/******************  BIT DEFINITION FOR SPI::RXCRCR   ******************/
#define RXCRCR_RXCRC_POS        (0U)                                       
#define RXCRCR_RXCRC_MSK        (0XFFFFUL << RXCRCR_RXCRC_POS)          
#define RXCRCR_RXCRC            RXCRCR_RXCRC_MSK                       

/******************  BIT DEFINITION FOR SPI::TXCRCR   ******************/
#define TXCRCR_TXCRC_POS        (0U)                                       
#define TXCRCR_TXCRC_MSK        (0XFFFFUL << TXCRCR_TXCRC_POS)          
#define TXCRCR_TXCRC            TXCRCR_TXCRC_MSK                       

/******************  BIT DEFINITION FOR SPI::I2SCFGR   *****************/
#define I2SCFGR_CHLEN_POS       (0U)                                       
#define I2SCFGR_CHLEN_MSK       (0X1UL << I2SCFGR_CHLEN_POS)            
#define I2SCFGR_CHLEN           I2SCFGR_CHLEN_MSK                      

#define I2SCFGR_DATLEN_POS      (1U)                                       
#define I2SCFGR_DATLEN_MSK      (0X3UL << I2SCFGR_DATLEN_POS)           
#define I2SCFGR_DATLEN          I2SCFGR_DATLEN_MSK                     
#define I2SCFGR_DATLEN_0        (0X1UL << I2SCFGR_DATLEN_POS)           
#define I2SCFGR_DATLEN_1        (0X2UL << I2SCFGR_DATLEN_POS)           

#define I2SCFGR_CKPOL_POS       (3U)                                       
#define I2SCFGR_CKPOL_MSK       (0X1UL << I2SCFGR_CKPOL_POS)            
#define I2SCFGR_CKPOL           I2SCFGR_CKPOL_MSK                      

#define I2SCFGR_I2SSTD_POS      (4U)                                       
#define I2SCFGR_I2SSTD_MSK      (0X3UL << I2SCFGR_I2SSTD_POS)           
#define I2SCFGR_I2SSTD          I2SCFGR_I2SSTD_MSK                     
#define I2SCFGR_I2SSTD_0        (0X1UL << I2SCFGR_I2SSTD_POS)           
#define I2SCFGR_I2SSTD_1        (0X2UL << I2SCFGR_I2SSTD_POS)           

#define I2SCFGR_PCMSYNC_POS     (7U)                                       
#define I2SCFGR_PCMSYNC_MSK     (0X1UL << I2SCFGR_PCMSYNC_POS)          
#define I2SCFGR_PCMSYNC         I2SCFGR_PCMSYNC_MSK                    

#define I2SCFGR_I2SCFG_POS      (8U)                                       
#define I2SCFGR_I2SCFG_MSK      (0X3UL << I2SCFGR_I2SCFG_POS)           
#define I2SCFGR_I2SCFG          I2SCFGR_I2SCFG_MSK                     
#define I2SCFGR_I2SCFG_0        (0X1UL << I2SCFGR_I2SCFG_POS)           
#define I2SCFGR_I2SCFG_1        (0X2UL << I2SCFGR_I2SCFG_POS)           

#define I2SCFGR_I2SE_POS        (10U)                                      
#define I2SCFGR_I2SE_MSK        (0X1UL << I2SCFGR_I2SE_POS)             
#define I2SCFGR_I2SE            I2SCFGR_I2SE_MSK                       
#define I2SCFGR_I2SMOD_POS      (11U)                                      
#define I2SCFGR_I2SMOD_MSK      (0X1UL << I2SCFGR_I2SMOD_POS)           
#define I2SCFGR_I2SMOD          I2SCFGR_I2SMOD_MSK                     

/******************  BIT DEFINITION FOR SPI::I2SPR   *******************/
#define I2SPR_I2SDIV_POS        (0U)                                       
#define I2SPR_I2SDIV_MSK        (0XFFUL << I2SPR_I2SDIV_POS)            
#define I2SPR_I2SDIV            I2SPR_I2SDIV_MSK                       
#define I2SPR_ODD_POS           (8U)                                       
#define I2SPR_ODD_MSK           (0X1UL << I2SPR_ODD_POS)                
#define I2SPR_ODD               I2SPR_ODD_MSK                          
#define I2SPR_MCKOE_POS         (9U)                                       
#define I2SPR_MCKOE_MSK         (0X1UL << I2SPR_MCKOE_POS)              
#define I2SPR_MCKOE             I2SPR_MCKOE_MSK                        


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_SPI_REGISTER_MASKS */
