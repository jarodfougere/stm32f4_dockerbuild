#ifndef RIMOT_FLASH_REGISTER_MASKS
#define RIMOT_FLASH_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BITS DEFINITION FOR FLASH::ACR   *****************/
#define ACR_LATENCY_POS          (0U)                                    
#define ACR_LATENCY_MSK          (0XFUL << ACR_LATENCY_POS)         
#define ACR_LATENCY              ACR_LATENCY_MSK                   

#define ACR_PRFTEN_POS           (8U)                                    
#define ACR_PRFTEN_MSK           (0X1UL << ACR_PRFTEN_POS)          
#define ACR_PRFTEN               ACR_PRFTEN_MSK                    
#define ACR_ICEN_POS             (9U)                                    
#define ACR_ICEN_MSK             (0X1UL << ACR_ICEN_POS)            
#define ACR_ICEN                 ACR_ICEN_MSK                      
#define ACR_DCEN_POS             (10U)                                   
#define ACR_DCEN_MSK             (0X1UL << ACR_DCEN_POS)            
#define ACR_DCEN                 ACR_DCEN_MSK                      
#define ACR_ICRST_POS            (11U)                                   
#define ACR_ICRST_MSK            (0X1UL << ACR_ICRST_POS)           
#define ACR_ICRST                ACR_ICRST_MSK                     
#define ACR_DCRST_POS            (12U)                                   
#define ACR_DCRST_MSK            (0X1UL << ACR_DCRST_POS)           
#define ACR_DCRST                ACR_DCRST_MSK                     
#define ACR_BYTE0_ADDRESS_POS    (10U)                                   
#define ACR_BYTE0_ADDRESS_MSK    (0X10008FUL << ACR_BYTE0_ADDRESS_POS) 
#define ACR_BYTE0_ADDRESS        ACR_BYTE0_ADDRESS_MSK             
#define ACR_BYTE2_ADDRESS_POS    (0U)                                    
#define ACR_BYTE2_ADDRESS_MSK    (0X40023C03UL << ACR_BYTE2_ADDRESS_POS) 
#define ACR_BYTE2_ADDRESS        ACR_BYTE2_ADDRESS_MSK             

/*******************  BITS DEFINITION FOR FLASH::SR   ******************/
#define SR_EOP_POS               (0U)                                    
#define SR_EOP_MSK               (0X1UL << SR_EOP_POS)              
#define SR_EOP                   SR_EOP_MSK                        
#define SR_OPERR_POS             (1U)                                    
#define SR_OPERR_MSK             (0X1UL << SR_OPERR_POS)              
#define SR_OPERR                 SR_OPERR_MSK                        
#define SR_WRPERR_POS            (4U)                                    
#define SR_WRPERR_MSK            (0X1UL << SR_WRPERR_POS)           
#define SR_WRPERR                SR_WRPERR_MSK                     
#define SR_PGAERR_POS            (5U)                                    
#define SR_PGAERR_MSK            (0X1UL << SR_PGAERR_POS)           
#define SR_PGAERR                SR_PGAERR_MSK                     
#define SR_PGPERR_POS            (6U)                                    
#define SR_PGPERR_MSK            (0X1UL << SR_PGPERR_POS)           
#define SR_PGPERR                SR_PGPERR_MSK                     
#define SR_PGSERR_POS            (7U)                                    
#define SR_PGSERR_MSK            (0X1UL << SR_PGSERR_POS)           
#define SR_PGSERR                SR_PGSERR_MSK                     
#define SR_RDERR_POS            (8U)                                    
#define SR_RDERR_MSK            (0X1UL << SR_RDERR_POS)             
#define SR_RDERR                SR_RDERR_MSK                     
#define SR_BSY_POS               (16U)                                   
#define SR_BSY_MSK               (0X1UL << SR_BSY_POS)              
#define SR_BSY                   SR_BSY_MSK                        

/*******************  BITS DEFINITION FOR FLASH::CR   ******************/
#define CR_PG_POS                (0U)                                    
#define CR_PG_MSK                (0X1UL << CR_PG_POS)               
#define CR_PG                    CR_PG_MSK                         
#define CR_SER_POS               (1U)                                    
#define CR_SER_MSK               (0X1UL << CR_SER_POS)              
#define CR_SER                   CR_SER_MSK                        
#define CR_MER_POS               (2U)                                    
#define CR_MER_MSK               (0X1UL << CR_MER_POS)              
#define CR_MER                   CR_MER_MSK                        
#define CR_SNB_POS               (3U)                                    
#define CR_SNB_MSK               (0X1FUL << CR_SNB_POS)             
#define CR_SNB                   CR_SNB_MSK                        
#define CR_SNB_0                 (0X01UL << CR_SNB_POS)             
#define CR_SNB_1                 (0X02UL << CR_SNB_POS)             
#define CR_SNB_2                 (0X04UL << CR_SNB_POS)             
#define CR_SNB_3                 (0X08UL << CR_SNB_POS)             
#define CR_SNB_4                 (0X10UL << CR_SNB_POS)             
#define CR_PSIZE_POS             (8U)                                    
#define CR_PSIZE_MSK             (0X3UL << CR_PSIZE_POS)            
#define CR_PSIZE                 CR_PSIZE_MSK                      
#define CR_PSIZE_0               (0X1UL << CR_PSIZE_POS)            
#define CR_PSIZE_1               (0X2UL << CR_PSIZE_POS)            
#define CR_STRT_POS              (16U)                                   
#define CR_STRT_MSK              (0X1UL << CR_STRT_POS)             
#define CR_STRT                  CR_STRT_MSK                       
#define CR_EOPIE_POS             (24U)                                   
#define CR_EOPIE_MSK             (0X1UL << CR_EOPIE_POS)            
#define CR_EOPIE                 CR_EOPIE_MSK                      
#define CR_LOCK_POS              (31U)                                   
#define CR_LOCK_MSK              (0X1UL << CR_LOCK_POS)             
#define CR_LOCK                  CR_LOCK_MSK                       

/*******************  BITS DEFINITION FOR FLASH::OPTCR   ***************/
#define OPTCR_OPTLOCK_POS        (0U)                                    
#define OPTCR_OPTLOCK_MSK        (0X1UL << OPTCR_OPTLOCK_POS)       
#define OPTCR_OPTLOCK            OPTCR_OPTLOCK_MSK                 
#define OPTCR_OPTSTRT_POS        (1U)                                    
#define OPTCR_OPTSTRT_MSK        (0X1UL << OPTCR_OPTSTRT_POS)       
#define OPTCR_OPTSTRT            OPTCR_OPTSTRT_MSK                 

#define OPTCR_BOR_LEV_0          0X00000004U                             
#define OPTCR_BOR_LEV_1          0X00000008U                             
#define OPTCR_BOR_LEV_POS        (2U)                                    
#define OPTCR_BOR_LEV_MSK        (0X3UL << OPTCR_BOR_LEV_POS)       
#define OPTCR_BOR_LEV            OPTCR_BOR_LEV_MSK                 
#define OPTCR_WDG_SW_POS         (5U)                                    
#define OPTCR_WDG_SW_MSK         (0X1UL << OPTCR_WDG_SW_POS)        
#define OPTCR_WDG_SW             OPTCR_WDG_SW_MSK                  
#define OPTCR_NRST_STOP_POS      (6U)                                    
#define OPTCR_NRST_STOP_MSK      (0X1UL << OPTCR_NRST_STOP_POS)     
#define OPTCR_NRST_STOP          OPTCR_NRST_STOP_MSK               
#define OPTCR_NRST_STDBY_POS     (7U)                                    
#define OPTCR_NRST_STDBY_MSK     (0X1UL << OPTCR_NRST_STDBY_POS)    
#define OPTCR_NRST_STDBY         OPTCR_NRST_STDBY_MSK              
#define OPTCR_RDP_POS            (8U)                                    
#define OPTCR_RDP_MSK            (0XFFUL << OPTCR_RDP_POS)          
#define OPTCR_RDP                OPTCR_RDP_MSK                     
#define OPTCR_RDP_0              (0X01UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_1              (0X02UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_2              (0X04UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_3              (0X08UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_4              (0X10UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_5              (0X20UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_6              (0X40UL << OPTCR_RDP_POS)          
#define OPTCR_RDP_7              (0X80UL << OPTCR_RDP_POS)          
#define OPTCR_NWRP_POS           (16U)                                   
#define OPTCR_NWRP_MSK           (0XFFFUL << OPTCR_NWRP_POS)        
#define OPTCR_NWRP               OPTCR_NWRP_MSK                    
#define OPTCR_NWRP_0             0X00010000U                             
#define OPTCR_NWRP_1             0X00020000U                             
#define OPTCR_NWRP_2             0X00040000U                             
#define OPTCR_NWRP_3             0X00080000U                             
#define OPTCR_NWRP_4             0X00100000U                             
#define OPTCR_NWRP_5             0X00200000U                             
#define OPTCR_NWRP_6             0X00400000U                             
#define OPTCR_NWRP_7             0X00800000U                             
#define OPTCR_NWRP_8             0X01000000U                             
#define OPTCR_NWRP_9             0X02000000U                             
#define OPTCR_NWRP_10            0X04000000U                             
#define OPTCR_NWRP_11            0X08000000U                             

/******************  BITS DEFINITION FOR FLASH::OPTCR1   ***************/
#define OPTCR1_NWRP_POS          (16U)                                   
#define OPTCR1_NWRP_MSK          (0XFFFUL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP              OPTCR1_NWRP_MSK                   
#define OPTCR1_NWRP_0            (0X001UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_1            (0X002UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_2            (0X004UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_3            (0X008UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_4            (0X010UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_5            (0X020UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_6            (0X040UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_7            (0X080UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_8            (0X100UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_9            (0X200UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_10           (0X400UL << OPTCR1_NWRP_POS)       
#define OPTCR1_NWRP_11           (0X800UL << OPTCR1_NWRP_POS)       


#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_FLASH_REGISTER_MASKS */
