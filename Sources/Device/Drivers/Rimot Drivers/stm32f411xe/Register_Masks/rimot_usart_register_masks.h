#ifndef RIMOT_USART_REGISTER_MASKS
#define RIMOT_USART_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BIT DEFINITION FOR USART::SR   *******************/
#define SR_PE_POS               (0U)                                     
#define SR_PE_MSK               (0X1UL << SR_PE_POS)                
#define SR_PE                   SR_PE_MSK                          
#define SR_FE_POS               (1U)                                     
#define SR_FE_MSK               (0X1UL << SR_FE_POS)                
#define SR_FE                   SR_FE_MSK                          
#define SR_NE_POS               (2U)                                     
#define SR_NE_MSK               (0X1UL << SR_NE_POS)                
#define SR_NE                   SR_NE_MSK                          
#define SR_ORE_POS              (3U)                                     
#define SR_ORE_MSK              (0X1UL << SR_ORE_POS)               
#define SR_ORE                  SR_ORE_MSK                         
#define SR_IDLE_POS             (4U)                                     
#define SR_IDLE_MSK             (0X1UL << SR_IDLE_POS)              
#define SR_IDLE                 SR_IDLE_MSK                        
#define SR_RXNE_POS             (5U)                                     
#define SR_RXNE_MSK             (0X1UL << SR_RXNE_POS)              
#define SR_RXNE                 SR_RXNE_MSK                        
#define SR_TC_POS               (6U)                                     
#define SR_TC_MSK               (0X1UL << SR_TC_POS)                
#define SR_TC                   SR_TC_MSK                          
#define SR_TXE_POS              (7U)                                     
#define SR_TXE_MSK              (0X1UL << SR_TXE_POS)               
#define SR_TXE                  SR_TXE_MSK                         
#define SR_LBD_POS              (8U)                                     
#define SR_LBD_MSK              (0X1UL << SR_LBD_POS)               
#define SR_LBD                  SR_LBD_MSK                         
#define SR_CTS_POS              (9U)                                     
#define SR_CTS_MSK              (0X1UL << SR_CTS_POS)               
#define SR_CTS                  SR_CTS_MSK                         

/*******************  BIT DEFINITION FOR USART::DR   *******************/
#define DR_DR_POS               (0U)                                     
#define DR_DR_MSK               (0X1FFUL << DR_DR_POS)              
#define DR_DR                   DR_DR_MSK                          

/******************  BIT DEFINITION FOR USART::BRR   *******************/
#define BRR_DIV_FRACTION_POS    (0U)                                     
#define BRR_DIV_FRACTION_MSK    (0XFUL << BRR_DIV_FRACTION_POS)     
#define BRR_DIV_FRACTION        BRR_DIV_FRACTION_MSK               
#define BRR_DIV_MANTISSA_POS    (4U)                                     
#define BRR_DIV_MANTISSA_MSK    (0XFFFUL << BRR_DIV_MANTISSA_POS)   
#define BRR_DIV_MANTISSA        BRR_DIV_MANTISSA_MSK               

/******************  BIT DEFINITION FOR USART::CR1   *******************/
#define CR1_SBK_POS             (0U)                                     
#define CR1_SBK_MSK             (0X1UL << CR1_SBK_POS)              
#define CR1_SBK                 CR1_SBK_MSK                        
#define CR1_RWU_POS             (1U)                                     
#define CR1_RWU_MSK             (0X1UL << CR1_RWU_POS)              
#define CR1_RWU                 CR1_RWU_MSK                        
#define CR1_RE_POS              (2U)                                     
#define CR1_RE_MSK              (0X1UL << CR1_RE_POS)               
#define CR1_RE                  CR1_RE_MSK                         
#define CR1_TE_POS              (3U)                                     
#define CR1_TE_MSK              (0X1UL << CR1_TE_POS)               
#define CR1_TE                  CR1_TE_MSK                         
#define CR1_IDLEIE_POS          (4U)                                     
#define CR1_IDLEIE_MSK          (0X1UL << CR1_IDLEIE_POS)           
#define CR1_IDLEIE              CR1_IDLEIE_MSK                     
#define CR1_RXNEIE_POS          (5U)                                     
#define CR1_RXNEIE_MSK          (0X1UL << CR1_RXNEIE_POS)           
#define CR1_RXNEIE              CR1_RXNEIE_MSK                     
#define CR1_TCIE_POS            (6U)                                     
#define CR1_TCIE_MSK            (0X1UL << CR1_TCIE_POS)             
#define CR1_TCIE                CR1_TCIE_MSK                       
#define CR1_TXEIE_POS           (7U)                                     
#define CR1_TXEIE_MSK           (0X1UL << CR1_TXEIE_POS)            
#define CR1_TXEIE               CR1_TXEIE_MSK                      
#define CR1_PEIE_POS            (8U)                                     
#define CR1_PEIE_MSK            (0X1UL << CR1_PEIE_POS)             
#define CR1_PEIE                CR1_PEIE_MSK                       
#define CR1_PS_POS              (9U)                                     
#define CR1_PS_MSK              (0X1UL << CR1_PS_POS)               
#define CR1_PS                  CR1_PS_MSK                         
#define CR1_PCE_POS             (10U)                                    
#define CR1_PCE_MSK             (0X1UL << CR1_PCE_POS)              
#define CR1_PCE                 CR1_PCE_MSK                        
#define CR1_WAKE_POS            (11U)                                    
#define CR1_WAKE_MSK            (0X1UL << CR1_WAKE_POS)             
#define CR1_WAKE                CR1_WAKE_MSK                       
#define CR1_M_POS               (12U)                                    
#define CR1_M_MSK               (0X1UL << CR1_M_POS)                
#define CR1_M                   CR1_M_MSK                          
#define CR1_UE_POS              (13U)                                    
#define CR1_UE_MSK              (0X1UL << CR1_UE_POS)               
#define CR1_UE                  CR1_UE_MSK                         
#define CR1_OVER8_POS           (15U)                                    
#define CR1_OVER8_MSK           (0X1UL << CR1_OVER8_POS)            
#define CR1_OVER8               CR1_OVER8_MSK                      

/******************  BIT DEFINITION FOR USART::CR2   *******************/
#define CR2_ADD_POS             (0U)                                     
#define CR2_ADD_MSK             (0XFUL << CR2_ADD_POS)              
#define CR2_ADD                 CR2_ADD_MSK                        
#define CR2_LBDL_POS            (5U)                                     
#define CR2_LBDL_MSK            (0X1UL << CR2_LBDL_POS)             
#define CR2_LBDL                CR2_LBDL_MSK                       
#define CR2_LBDIE_POS           (6U)                                     
#define CR2_LBDIE_MSK           (0X1UL << CR2_LBDIE_POS)            
#define CR2_LBDIE               CR2_LBDIE_MSK                      
#define CR2_LBCL_POS            (8U)                                     
#define CR2_LBCL_MSK            (0X1UL << CR2_LBCL_POS)             
#define CR2_LBCL                CR2_LBCL_MSK                       
#define CR2_CPHA_POS            (9U)                                     
#define CR2_CPHA_MSK            (0X1UL << CR2_CPHA_POS)             
#define CR2_CPHA                CR2_CPHA_MSK                       
#define CR2_CPOL_POS            (10U)                                    
#define CR2_CPOL_MSK            (0X1UL << CR2_CPOL_POS)             
#define CR2_CPOL                CR2_CPOL_MSK                       
#define CR2_CLKEN_POS           (11U)                                    
#define CR2_CLKEN_MSK           (0X1UL << CR2_CLKEN_POS)            
#define CR2_CLKEN               CR2_CLKEN_MSK                      

#define CR2_STOP_POS            (12U)                                    
#define CR2_STOP_MSK            (0X3UL << CR2_STOP_POS)             
#define CR2_STOP                CR2_STOP_MSK                       
#define CR2_STOP_0              (0X1UL << CR2_STOP_POS)             
#define CR2_STOP_1              (0X2UL << CR2_STOP_POS)             

#define CR2_LINEN_POS           (14U)                                    
#define CR2_LINEN_MSK           (0X1UL << CR2_LINEN_POS)            
#define CR2_LINEN               CR2_LINEN_MSK                      

/******************  BIT DEFINITION FOR USART::CR3   *******************/
#define CR3_EIE_POS             (0U)                                     
#define CR3_EIE_MSK             (0X1UL << CR3_EIE_POS)              
#define CR3_EIE                 CR3_EIE_MSK                        
#define CR3_IREN_POS            (1U)                                     
#define CR3_IREN_MSK            (0X1UL << CR3_IREN_POS)             
#define CR3_IREN                CR3_IREN_MSK                       
#define CR3_IRLP_POS            (2U)                                     
#define CR3_IRLP_MSK            (0X1UL << CR3_IRLP_POS)             
#define CR3_IRLP                CR3_IRLP_MSK                       
#define CR3_HDSEL_POS           (3U)                                     
#define CR3_HDSEL_MSK           (0X1UL << CR3_HDSEL_POS)            
#define CR3_HDSEL               CR3_HDSEL_MSK                      
#define CR3_NACK_POS            (4U)                                     
#define CR3_NACK_MSK            (0X1UL << CR3_NACK_POS)             
#define CR3_NACK                CR3_NACK_MSK                       
#define CR3_SCEN_POS            (5U)                                     
#define CR3_SCEN_MSK            (0X1UL << CR3_SCEN_POS)             
#define CR3_SCEN                CR3_SCEN_MSK                       
#define CR3_DMAR_POS            (6U)                                     
#define CR3_DMAR_MSK            (0X1UL << CR3_DMAR_POS)             
#define CR3_DMAR                CR3_DMAR_MSK                       
#define CR3_DMAT_POS            (7U)                                     
#define CR3_DMAT_MSK            (0X1UL << CR3_DMAT_POS)             
#define CR3_DMAT                CR3_DMAT_MSK                       
#define CR3_RTSE_POS            (8U)                                     
#define CR3_RTSE_MSK            (0X1UL << CR3_RTSE_POS)             
#define CR3_RTSE                CR3_RTSE_MSK                       
#define CR3_CTSE_POS            (9U)                                     
#define CR3_CTSE_MSK            (0X1UL << CR3_CTSE_POS)             
#define CR3_CTSE                CR3_CTSE_MSK                       
#define CR3_CTSIE_POS           (10U)                                    
#define CR3_CTSIE_MSK           (0X1UL << CR3_CTSIE_POS)            
#define CR3_CTSIE               CR3_CTSIE_MSK                      
#define CR3_ONEBIT_POS          (11U)                                    
#define CR3_ONEBIT_MSK          (0X1UL << CR3_ONEBIT_POS)           
#define CR3_ONEBIT              CR3_ONEBIT_MSK                     

/******************  BIT DEFINITION FOR USART::GTPR   ******************/
#define GTPR_PSC_POS            (0U)                                     
#define GTPR_PSC_MSK            (0XFFUL << GTPR_PSC_POS)            
#define GTPR_PSC                GTPR_PSC_MSK                       
#define GTPR_PSC_0              (0X01UL << GTPR_PSC_POS)            
#define GTPR_PSC_1              (0X02UL << GTPR_PSC_POS)            
#define GTPR_PSC_2              (0X04UL << GTPR_PSC_POS)            
#define GTPR_PSC_3              (0X08UL << GTPR_PSC_POS)            
#define GTPR_PSC_4              (0X10UL << GTPR_PSC_POS)            
#define GTPR_PSC_5              (0X20UL << GTPR_PSC_POS)            
#define GTPR_PSC_6              (0X40UL << GTPR_PSC_POS)            
#define GTPR_PSC_7              (0X80UL << GTPR_PSC_POS)            

#define GTPR_GT_POS             (8U)                                     
#define GTPR_GT_MSK             (0XFFUL << GTPR_GT_POS)             
#define GTPR_GT                 GTPR_GT_MSK                        

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_USART_REGISTER_MASKS */
