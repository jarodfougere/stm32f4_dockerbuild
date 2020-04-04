#ifndef RIMOT_RTC_REGISTER_MASKS
#define RIMOT_RTC_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/********************  BITS DEFINITION FOR RTC::TR   *******************/
#define TR_PM_POS                 (22U)                                    
#define TR_PM_MSK                 (0X1UL << TR_PM_POS)                  
#define TR_PM                     TR_PM_MSK                            
#define TR_HT_POS                 (20U)                                    
#define TR_HT_MSK                 (0X3UL << TR_HT_POS)                  
#define TR_HT                     TR_HT_MSK                            
#define TR_HT_0                   (0X1UL << TR_HT_POS)                  
#define TR_HT_1                   (0X2UL << TR_HT_POS)                  
#define TR_HU_POS                 (16U)                                    
#define TR_HU_MSK                 (0XFUL << TR_HU_POS)                  
#define TR_HU                     TR_HU_MSK                            
#define TR_HU_0                   (0X1UL << TR_HU_POS)                  
#define TR_HU_1                   (0X2UL << TR_HU_POS)                  
#define TR_HU_2                   (0X4UL << TR_HU_POS)                  
#define TR_HU_3                   (0X8UL << TR_HU_POS)                  
#define TR_MNT_POS                (12U)                                    
#define TR_MNT_MSK                (0X7UL << TR_MNT_POS)                 
#define TR_MNT                    TR_MNT_MSK                           
#define TR_MNT_0                  (0X1UL << TR_MNT_POS)                 
#define TR_MNT_1                  (0X2UL << TR_MNT_POS)                 
#define TR_MNT_2                  (0X4UL << TR_MNT_POS)                 
#define TR_MNU_POS                (8U)                                     
#define TR_MNU_MSK                (0XFUL << TR_MNU_POS)                 
#define TR_MNU                    TR_MNU_MSK                           
#define TR_MNU_0                  (0X1UL << TR_MNU_POS)                 
#define TR_MNU_1                  (0X2UL << TR_MNU_POS)                 
#define TR_MNU_2                  (0X4UL << TR_MNU_POS)                 
#define TR_MNU_3                  (0X8UL << TR_MNU_POS)                 
#define TR_ST_POS                 (4U)                                     
#define TR_ST_MSK                 (0X7UL << TR_ST_POS)                  
#define TR_ST                     TR_ST_MSK                            
#define TR_ST_0                   (0X1UL << TR_ST_POS)                  
#define TR_ST_1                   (0X2UL << TR_ST_POS)                  
#define TR_ST_2                   (0X4UL << TR_ST_POS)                  
#define TR_SU_POS                 (0U)                                     
#define TR_SU_MSK                 (0XFUL << TR_SU_POS)                  
#define TR_SU                     TR_SU_MSK                            
#define TR_SU_0                   (0X1UL << TR_SU_POS)                  
#define TR_SU_1                   (0X2UL << TR_SU_POS)                  
#define TR_SU_2                   (0X4UL << TR_SU_POS)                  
#define TR_SU_3                   (0X8UL << TR_SU_POS)                  

/********************  BITS DEFINITION FOR RTC::DR   *******************/
#define DR_YT_POS                 (20U)                                    
#define DR_YT_MSK                 (0XFUL << DR_YT_POS)                  
#define DR_YT                     DR_YT_MSK                            
#define DR_YT_0                   (0X1UL << DR_YT_POS)                  
#define DR_YT_1                   (0X2UL << DR_YT_POS)                  
#define DR_YT_2                   (0X4UL << DR_YT_POS)                  
#define DR_YT_3                   (0X8UL << DR_YT_POS)                  
#define DR_YU_POS                 (16U)                                    
#define DR_YU_MSK                 (0XFUL << DR_YU_POS)                  
#define DR_YU                     DR_YU_MSK                            
#define DR_YU_0                   (0X1UL << DR_YU_POS)                  
#define DR_YU_1                   (0X2UL << DR_YU_POS)                  
#define DR_YU_2                   (0X4UL << DR_YU_POS)                  
#define DR_YU_3                   (0X8UL << DR_YU_POS)                  
#define DR_WDU_POS                (13U)                                    
#define DR_WDU_MSK                (0X7UL << DR_WDU_POS)                 
#define DR_WDU                    DR_WDU_MSK                           
#define DR_WDU_0                  (0X1UL << DR_WDU_POS)                 
#define DR_WDU_1                  (0X2UL << DR_WDU_POS)                 
#define DR_WDU_2                  (0X4UL << DR_WDU_POS)                 
#define DR_MT_POS                 (12U)                                    
#define DR_MT_MSK                 (0X1UL << DR_MT_POS)                  
#define DR_MT                     DR_MT_MSK                            
#define DR_MU_POS                 (8U)                                     
#define DR_MU_MSK                 (0XFUL << DR_MU_POS)                  
#define DR_MU                     DR_MU_MSK                            
#define DR_MU_0                   (0X1UL << DR_MU_POS)                  
#define DR_MU_1                   (0X2UL << DR_MU_POS)                  
#define DR_MU_2                   (0X4UL << DR_MU_POS)                  
#define DR_MU_3                   (0X8UL << DR_MU_POS)                  
#define DR_DT_POS                 (4U)                                     
#define DR_DT_MSK                 (0X3UL << DR_DT_POS)                  
#define DR_DT                     DR_DT_MSK                            
#define DR_DT_0                   (0X1UL << DR_DT_POS)                  
#define DR_DT_1                   (0X2UL << DR_DT_POS)                  
#define DR_DU_POS                 (0U)                                     
#define DR_DU_MSK                 (0XFUL << DR_DU_POS)                  
#define DR_DU                     DR_DU_MSK                            
#define DR_DU_0                   (0X1UL << DR_DU_POS)                  
#define DR_DU_1                   (0X2UL << DR_DU_POS)                  
#define DR_DU_2                   (0X4UL << DR_DU_POS)                  
#define DR_DU_3                   (0X8UL << DR_DU_POS)                  

/********************  BITS DEFINITION FOR RTC::CR   *******************/
#define CR_COE_POS                (23U)                                    
#define CR_COE_MSK                (0X1UL << CR_COE_POS)                 
#define CR_COE                    CR_COE_MSK                           
#define CR_OSEL_POS               (21U)                                    
#define CR_OSEL_MSK               (0X3UL << CR_OSEL_POS)                
#define CR_OSEL                   CR_OSEL_MSK                          
#define CR_OSEL_0                 (0X1UL << CR_OSEL_POS)                
#define CR_OSEL_1                 (0X2UL << CR_OSEL_POS)                
#define CR_POL_POS                (20U)                                    
#define CR_POL_MSK                (0X1UL << CR_POL_POS)                 
#define CR_POL                    CR_POL_MSK                           
#define CR_COSEL_POS              (19U)                                    
#define CR_COSEL_MSK              (0X1UL << CR_COSEL_POS)               
#define CR_COSEL                  CR_COSEL_MSK                         
#define CR_BKP_POS                 (18U)                                   
#define CR_BKP_MSK                 (0X1UL << CR_BKP_POS)                
#define CR_BKP                     CR_BKP_MSK                          
#define CR_SUB1H_POS              (17U)                                    
#define CR_SUB1H_MSK              (0X1UL << CR_SUB1H_POS)               
#define CR_SUB1H                  CR_SUB1H_MSK                         
#define CR_ADD1H_POS              (16U)                                    
#define CR_ADD1H_MSK              (0X1UL << CR_ADD1H_POS)               
#define CR_ADD1H                  CR_ADD1H_MSK                         
#define CR_TSIE_POS               (15U)                                    
#define CR_TSIE_MSK               (0X1UL << CR_TSIE_POS)                
#define CR_TSIE                   CR_TSIE_MSK                          
#define CR_WUTIE_POS              (14U)                                    
#define CR_WUTIE_MSK              (0X1UL << CR_WUTIE_POS)               
#define CR_WUTIE                  CR_WUTIE_MSK                         
#define CR_ALRBIE_POS             (13U)                                    
#define CR_ALRBIE_MSK             (0X1UL << CR_ALRBIE_POS)              
#define CR_ALRBIE                 CR_ALRBIE_MSK                        
#define CR_ALRAIE_POS             (12U)                                    
#define CR_ALRAIE_MSK             (0X1UL << CR_ALRAIE_POS)              
#define CR_ALRAIE                 CR_ALRAIE_MSK                        
#define CR_TSE_POS                (11U)                                    
#define CR_TSE_MSK                (0X1UL << CR_TSE_POS)                 
#define CR_TSE                    CR_TSE_MSK                           
#define CR_WUTE_POS               (10U)                                    
#define CR_WUTE_MSK               (0X1UL << CR_WUTE_POS)                
#define CR_WUTE                   CR_WUTE_MSK                          
#define CR_ALRBE_POS              (9U)                                     
#define CR_ALRBE_MSK              (0X1UL << CR_ALRBE_POS)               
#define CR_ALRBE                  CR_ALRBE_MSK                         
#define CR_ALRAE_POS              (8U)                                     
#define CR_ALRAE_MSK              (0X1UL << CR_ALRAE_POS)               
#define CR_ALRAE                  CR_ALRAE_MSK                         
#define CR_DCE_POS                (7U)                                     
#define CR_DCE_MSK                (0X1UL << CR_DCE_POS)                 
#define CR_DCE                    CR_DCE_MSK                           
#define CR_FMT_POS                (6U)                                     
#define CR_FMT_MSK                (0X1UL << CR_FMT_POS)                 
#define CR_FMT                    CR_FMT_MSK                           
#define CR_BYPSHAD_POS            (5U)                                     
#define CR_BYPSHAD_MSK            (0X1UL << CR_BYPSHAD_POS)             
#define CR_BYPSHAD                CR_BYPSHAD_MSK                       
#define CR_REFCKON_POS            (4U)                                     
#define CR_REFCKON_MSK            (0X1UL << CR_REFCKON_POS)             
#define CR_REFCKON                CR_REFCKON_MSK                       
#define CR_TSEDGE_POS             (3U)                                     
#define CR_TSEDGE_MSK             (0X1UL << CR_TSEDGE_POS)              
#define CR_TSEDGE                 CR_TSEDGE_MSK                        
#define CR_WUCKSEL_POS            (0U)                                     
#define CR_WUCKSEL_MSK            (0X7UL << CR_WUCKSEL_POS)             
#define CR_WUCKSEL                CR_WUCKSEL_MSK                       
#define CR_WUCKSEL_0              (0X1UL << CR_WUCKSEL_POS)             
#define CR_WUCKSEL_1              (0X2UL << CR_WUCKSEL_POS)             
#define CR_WUCKSEL_2              (0X4UL << CR_WUCKSEL_POS)             



/********************  BITS DEFINITION FOR RTC::ISR   ******************/
#define ISR_RECALPF_POS           (16U)                                    
#define ISR_RECALPF_MSK           (0X1UL << ISR_RECALPF_POS)            
#define ISR_RECALPF               ISR_RECALPF_MSK                      
#define ISR_TAMP1F_POS            (13U)                                    
#define ISR_TAMP1F_MSK            (0X1UL << ISR_TAMP1F_POS)             
#define ISR_TAMP1F                ISR_TAMP1F_MSK                       
#define ISR_TAMP2F_POS            (14U)                                    
#define ISR_TAMP2F_MSK            (0X1UL << ISR_TAMP2F_POS)             
#define ISR_TAMP2F                ISR_TAMP2F_MSK                       
#define ISR_TSOVF_POS             (12U)                                    
#define ISR_TSOVF_MSK             (0X1UL << ISR_TSOVF_POS)              
#define ISR_TSOVF                 ISR_TSOVF_MSK                        
#define ISR_TSF_POS               (11U)                                    
#define ISR_TSF_MSK               (0X1UL << ISR_TSF_POS)                
#define ISR_TSF                   ISR_TSF_MSK                          
#define ISR_WUTF_POS              (10U)                                    
#define ISR_WUTF_MSK              (0X1UL << ISR_WUTF_POS)               
#define ISR_WUTF                  ISR_WUTF_MSK                         
#define ISR_ALRBF_POS             (9U)                                     
#define ISR_ALRBF_MSK             (0X1UL << ISR_ALRBF_POS)              
#define ISR_ALRBF                 ISR_ALRBF_MSK                        
#define ISR_ALRAF_POS             (8U)                                     
#define ISR_ALRAF_MSK             (0X1UL << ISR_ALRAF_POS)              
#define ISR_ALRAF                 ISR_ALRAF_MSK                        
#define ISR_INIT_POS              (7U)                                     
#define ISR_INIT_MSK              (0X1UL << ISR_INIT_POS)               
#define ISR_INIT                  ISR_INIT_MSK                         
#define ISR_INITF_POS             (6U)                                     
#define ISR_INITF_MSK             (0X1UL << ISR_INITF_POS)              
#define ISR_INITF                 ISR_INITF_MSK                        
#define ISR_RSF_POS               (5U)                                     
#define ISR_RSF_MSK               (0X1UL << ISR_RSF_POS)                
#define ISR_RSF                   ISR_RSF_MSK                          
#define ISR_INITS_POS             (4U)                                     
#define ISR_INITS_MSK             (0X1UL << ISR_INITS_POS)              
#define ISR_INITS                 ISR_INITS_MSK                        
#define ISR_SHPF_POS              (3U)                                     
#define ISR_SHPF_MSK              (0X1UL << ISR_SHPF_POS)               
#define ISR_SHPF                  ISR_SHPF_MSK                         
#define ISR_WUTWF_POS             (2U)                                     
#define ISR_WUTWF_MSK             (0X1UL << ISR_WUTWF_POS)              
#define ISR_WUTWF                 ISR_WUTWF_MSK                        
#define ISR_ALRBWF_POS            (1U)                                     
#define ISR_ALRBWF_MSK            (0X1UL << ISR_ALRBWF_POS)             
#define ISR_ALRBWF                ISR_ALRBWF_MSK                       
#define ISR_ALRAWF_POS            (0U)                                     
#define ISR_ALRAWF_MSK            (0X1UL << ISR_ALRAWF_POS)             
#define ISR_ALRAWF                ISR_ALRAWF_MSK                       

/********************  BITS DEFINITION FOR RTC::PRER   *****************/
#define PRER_PREDIV_A_POS         (16U)                                    
#define PRER_PREDIV_A_MSK         (0X7FUL << PRER_PREDIV_A_POS)         
#define PRER_PREDIV_A             PRER_PREDIV_A_MSK                    
#define PRER_PREDIV_S_POS         (0U)                                     
#define PRER_PREDIV_S_MSK         (0X7FFFUL << PRER_PREDIV_S_POS)       
#define PRER_PREDIV_S             PRER_PREDIV_S_MSK                    

/********************  BITS DEFINITION FOR RTC::WUTR   *****************/
#define WUTR_WUT_POS              (0U)                                     
#define WUTR_WUT_MSK              (0XFFFFUL << WUTR_WUT_POS)            
#define WUTR_WUT                  WUTR_WUT_MSK                         

/********************  BITS DEFINITION FOR RTC::CALIBR   ***************/
#define CALIBR_DCS_POS            (7U)                                     
#define CALIBR_DCS_MSK            (0X1UL << CALIBR_DCS_POS)             
#define CALIBR_DCS                CALIBR_DCS_MSK                       
#define CALIBR_DC_POS             (0U)                                     
#define CALIBR_DC_MSK             (0X1FUL << CALIBR_DC_POS)             
#define CALIBR_DC                 CALIBR_DC_MSK                        

/********************  BITS DEFINITION FOR RTC::ALRMAR   ***************/
#define ALRMAR_MSK4_POS           (31U)                                    
#define ALRMAR_MSK4_MSK           (0X1UL << ALRMAR_MSK4_POS)            
#define ALRMAR_MSK4               ALRMAR_MSK4_MSK                      
#define ALRMAR_WDSEL_POS          (30U)                                    
#define ALRMAR_WDSEL_MSK          (0X1UL << ALRMAR_WDSEL_POS)           
#define ALRMAR_WDSEL              ALRMAR_WDSEL_MSK                     
#define ALRMAR_DT_POS             (28U)                                    
#define ALRMAR_DT_MSK             (0X3UL << ALRMAR_DT_POS)              
#define ALRMAR_DT                 ALRMAR_DT_MSK                        
#define ALRMAR_DT_0               (0X1UL << ALRMAR_DT_POS)              
#define ALRMAR_DT_1               (0X2UL << ALRMAR_DT_POS)              
#define ALRMAR_DU_POS             (24U)                                    
#define ALRMAR_DU_MSK             (0XFUL << ALRMAR_DU_POS)              
#define ALRMAR_DU                 ALRMAR_DU_MSK                        
#define ALRMAR_DU_0               (0X1UL << ALRMAR_DU_POS)              
#define ALRMAR_DU_1               (0X2UL << ALRMAR_DU_POS)              
#define ALRMAR_DU_2               (0X4UL << ALRMAR_DU_POS)              
#define ALRMAR_DU_3               (0X8UL << ALRMAR_DU_POS)              
#define ALRMAR_MSK3_POS           (23U)                                    
#define ALRMAR_MSK3_MSK           (0X1UL << ALRMAR_MSK3_POS)            
#define ALRMAR_MSK3               ALRMAR_MSK3_MSK                      
#define ALRMAR_PM_POS             (22U)                                    
#define ALRMAR_PM_MSK             (0X1UL << ALRMAR_PM_POS)              
#define ALRMAR_PM                 ALRMAR_PM_MSK                        
#define ALRMAR_HT_POS             (20U)                                    
#define ALRMAR_HT_MSK             (0X3UL << ALRMAR_HT_POS)              
#define ALRMAR_HT                 ALRMAR_HT_MSK                        
#define ALRMAR_HT_0               (0X1UL << ALRMAR_HT_POS)              
#define ALRMAR_HT_1               (0X2UL << ALRMAR_HT_POS)              
#define ALRMAR_HU_POS             (16U)                                    
#define ALRMAR_HU_MSK             (0XFUL << ALRMAR_HU_POS)              
#define ALRMAR_HU                 ALRMAR_HU_MSK                        
#define ALRMAR_HU_0               (0X1UL << ALRMAR_HU_POS)              
#define ALRMAR_HU_1               (0X2UL << ALRMAR_HU_POS)              
#define ALRMAR_HU_2               (0X4UL << ALRMAR_HU_POS)              
#define ALRMAR_HU_3               (0X8UL << ALRMAR_HU_POS)              
#define ALRMAR_MSK2_POS           (15U)                                    
#define ALRMAR_MSK2_MSK           (0X1UL << ALRMAR_MSK2_POS)            
#define ALRMAR_MSK2               ALRMAR_MSK2_MSK                      
#define ALRMAR_MNT_POS            (12U)                                    
#define ALRMAR_MNT_MSK            (0X7UL << ALRMAR_MNT_POS)             
#define ALRMAR_MNT                ALRMAR_MNT_MSK                       
#define ALRMAR_MNT_0              (0X1UL << ALRMAR_MNT_POS)             
#define ALRMAR_MNT_1              (0X2UL << ALRMAR_MNT_POS)             
#define ALRMAR_MNT_2              (0X4UL << ALRMAR_MNT_POS)             
#define ALRMAR_MNU_POS            (8U)                                     
#define ALRMAR_MNU_MSK            (0XFUL << ALRMAR_MNU_POS)             
#define ALRMAR_MNU                ALRMAR_MNU_MSK                       
#define ALRMAR_MNU_0              (0X1UL << ALRMAR_MNU_POS)             
#define ALRMAR_MNU_1              (0X2UL << ALRMAR_MNU_POS)             
#define ALRMAR_MNU_2              (0X4UL << ALRMAR_MNU_POS)             
#define ALRMAR_MNU_3              (0X8UL << ALRMAR_MNU_POS)             
#define ALRMAR_MSK1_POS           (7U)                                     
#define ALRMAR_MSK1_MSK           (0X1UL << ALRMAR_MSK1_POS)            
#define ALRMAR_MSK1               ALRMAR_MSK1_MSK                      
#define ALRMAR_ST_POS             (4U)                                     
#define ALRMAR_ST_MSK             (0X7UL << ALRMAR_ST_POS)              
#define ALRMAR_ST                 ALRMAR_ST_MSK                        
#define ALRMAR_ST_0               (0X1UL << ALRMAR_ST_POS)              
#define ALRMAR_ST_1               (0X2UL << ALRMAR_ST_POS)              
#define ALRMAR_ST_2               (0X4UL << ALRMAR_ST_POS)              
#define ALRMAR_SU_POS             (0U)                                     
#define ALRMAR_SU_MSK             (0XFUL << ALRMAR_SU_POS)              
#define ALRMAR_SU                 ALRMAR_SU_MSK                        
#define ALRMAR_SU_0               (0X1UL << ALRMAR_SU_POS)              
#define ALRMAR_SU_1               (0X2UL << ALRMAR_SU_POS)              
#define ALRMAR_SU_2               (0X4UL << ALRMAR_SU_POS)              
#define ALRMAR_SU_3               (0X8UL << ALRMAR_SU_POS)              

/********************  BITS DEFINITION FOR RTC::ALRMBR   ***************/
#define ALRMBR_MSK4_POS           (31U)                                    
#define ALRMBR_MSK4_MSK           (0X1UL << ALRMBR_MSK4_POS)            
#define ALRMBR_MSK4               ALRMBR_MSK4_MSK                      
#define ALRMBR_WDSEL_POS          (30U)                                    
#define ALRMBR_WDSEL_MSK          (0X1UL << ALRMBR_WDSEL_POS)           
#define ALRMBR_WDSEL              ALRMBR_WDSEL_MSK                     
#define ALRMBR_DT_POS             (28U)                                    
#define ALRMBR_DT_MSK             (0X3UL << ALRMBR_DT_POS)              
#define ALRMBR_DT                 ALRMBR_DT_MSK                        
#define ALRMBR_DT_0               (0X1UL << ALRMBR_DT_POS)              
#define ALRMBR_DT_1               (0X2UL << ALRMBR_DT_POS)              
#define ALRMBR_DU_POS             (24U)                                    
#define ALRMBR_DU_MSK             (0XFUL << ALRMBR_DU_POS)              
#define ALRMBR_DU                 ALRMBR_DU_MSK                        
#define ALRMBR_DU_0               (0X1UL << ALRMBR_DU_POS)              
#define ALRMBR_DU_1               (0X2UL << ALRMBR_DU_POS)              
#define ALRMBR_DU_2               (0X4UL << ALRMBR_DU_POS)              
#define ALRMBR_DU_3               (0X8UL << ALRMBR_DU_POS)              
#define ALRMBR_MSK3_POS           (23U)                                    
#define ALRMBR_MSK3_MSK           (0X1UL << ALRMBR_MSK3_POS)            
#define ALRMBR_MSK3               ALRMBR_MSK3_MSK                      
#define ALRMBR_PM_POS             (22U)                                    
#define ALRMBR_PM_MSK             (0X1UL << ALRMBR_PM_POS)              
#define ALRMBR_PM                 ALRMBR_PM_MSK                        
#define ALRMBR_HT_POS             (20U)                                    
#define ALRMBR_HT_MSK             (0X3UL << ALRMBR_HT_POS)              
#define ALRMBR_HT                 ALRMBR_HT_MSK                        
#define ALRMBR_HT_0               (0X1UL << ALRMBR_HT_POS)              
#define ALRMBR_HT_1               (0X2UL << ALRMBR_HT_POS)              
#define ALRMBR_HU_POS             (16U)                                    
#define ALRMBR_HU_MSK             (0XFUL << ALRMBR_HU_POS)              
#define ALRMBR_HU                 ALRMBR_HU_MSK                        
#define ALRMBR_HU_0               (0X1UL << ALRMBR_HU_POS)              
#define ALRMBR_HU_1               (0X2UL << ALRMBR_HU_POS)              
#define ALRMBR_HU_2               (0X4UL << ALRMBR_HU_POS)              
#define ALRMBR_HU_3               (0X8UL << ALRMBR_HU_POS)              
#define ALRMBR_MSK2_POS           (15U)                                    
#define ALRMBR_MSK2_MSK           (0X1UL << ALRMBR_MSK2_POS)            
#define ALRMBR_MSK2               ALRMBR_MSK2_MSK                      
#define ALRMBR_MNT_POS            (12U)                                    
#define ALRMBR_MNT_MSK            (0X7UL << ALRMBR_MNT_POS)             
#define ALRMBR_MNT                ALRMBR_MNT_MSK                       
#define ALRMBR_MNT_0              (0X1UL << ALRMBR_MNT_POS)             
#define ALRMBR_MNT_1              (0X2UL << ALRMBR_MNT_POS)             
#define ALRMBR_MNT_2              (0X4UL << ALRMBR_MNT_POS)             
#define ALRMBR_MNU_POS            (8U)                                     
#define ALRMBR_MNU_MSK            (0XFUL << ALRMBR_MNU_POS)             
#define ALRMBR_MNU                ALRMBR_MNU_MSK                       
#define ALRMBR_MNU_0              (0X1UL << ALRMBR_MNU_POS)             
#define ALRMBR_MNU_1              (0X2UL << ALRMBR_MNU_POS)             
#define ALRMBR_MNU_2              (0X4UL << ALRMBR_MNU_POS)             
#define ALRMBR_MNU_3              (0X8UL << ALRMBR_MNU_POS)             
#define ALRMBR_MSK1_POS           (7U)                                     
#define ALRMBR_MSK1_MSK           (0X1UL << ALRMBR_MSK1_POS)            
#define ALRMBR_MSK1               ALRMBR_MSK1_MSK                      
#define ALRMBR_ST_POS             (4U)                                     
#define ALRMBR_ST_MSK             (0X7UL << ALRMBR_ST_POS)              
#define ALRMBR_ST                 ALRMBR_ST_MSK                        
#define ALRMBR_ST_0               (0X1UL << ALRMBR_ST_POS)              
#define ALRMBR_ST_1               (0X2UL << ALRMBR_ST_POS)              
#define ALRMBR_ST_2               (0X4UL << ALRMBR_ST_POS)              
#define ALRMBR_SU_POS             (0U)                                     
#define ALRMBR_SU_MSK             (0XFUL << ALRMBR_SU_POS)              
#define ALRMBR_SU                 ALRMBR_SU_MSK                        
#define ALRMBR_SU_0               (0X1UL << ALRMBR_SU_POS)              
#define ALRMBR_SU_1               (0X2UL << ALRMBR_SU_POS)              
#define ALRMBR_SU_2               (0X4UL << ALRMBR_SU_POS)              
#define ALRMBR_SU_3               (0X8UL << ALRMBR_SU_POS)              

/********************  BITS DEFINITION FOR RTC::WPR   ******************/
#define WPR_KEY_POS               (0U)                                     
#define WPR_KEY_MSK               (0XFFUL << WPR_KEY_POS)               
#define WPR_KEY                   WPR_KEY_MSK                          

/********************  BITS DEFINITION FOR RTC::SSR   ******************/
#define SSR_SS_POS                (0U)                                     
#define SSR_SS_MSK                (0XFFFFUL << SSR_SS_POS)              
#define SSR_SS                    SSR_SS_MSK                           

/********************  BITS DEFINITION FOR RTC::SHIFTR   ***************/
#define SHIFTR_SUBFS_POS          (0U)                                     
#define SHIFTR_SUBFS_MSK          (0X7FFFUL << SHIFTR_SUBFS_POS)        
#define SHIFTR_SUBFS              SHIFTR_SUBFS_MSK                     
#define SHIFTR_ADD1S_POS          (31U)                                    
#define SHIFTR_ADD1S_MSK          (0X1UL << SHIFTR_ADD1S_POS)           
#define SHIFTR_ADD1S              SHIFTR_ADD1S_MSK                     

/********************  BITS DEFINITION FOR RTC::TSTR   *****************/
#define TSTR_PM_POS               (22U)                                    
#define TSTR_PM_MSK               (0X1UL << TSTR_PM_POS)                
#define TSTR_PM                   TSTR_PM_MSK                          
#define TSTR_HT_POS               (20U)                                    
#define TSTR_HT_MSK               (0X3UL << TSTR_HT_POS)                
#define TSTR_HT                   TSTR_HT_MSK                          
#define TSTR_HT_0                 (0X1UL << TSTR_HT_POS)                
#define TSTR_HT_1                 (0X2UL << TSTR_HT_POS)                
#define TSTR_HU_POS               (16U)                                    
#define TSTR_HU_MSK               (0XFUL << TSTR_HU_POS)                
#define TSTR_HU                   TSTR_HU_MSK                          
#define TSTR_HU_0                 (0X1UL << TSTR_HU_POS)                
#define TSTR_HU_1                 (0X2UL << TSTR_HU_POS)                
#define TSTR_HU_2                 (0X4UL << TSTR_HU_POS)                
#define TSTR_HU_3                 (0X8UL << TSTR_HU_POS)                
#define TSTR_MNT_POS              (12U)                                    
#define TSTR_MNT_MSK              (0X7UL << TSTR_MNT_POS)               
#define TSTR_MNT                  TSTR_MNT_MSK                         
#define TSTR_MNT_0                (0X1UL << TSTR_MNT_POS)               
#define TSTR_MNT_1                (0X2UL << TSTR_MNT_POS)               
#define TSTR_MNT_2                (0X4UL << TSTR_MNT_POS)               
#define TSTR_MNU_POS              (8U)                                     
#define TSTR_MNU_MSK              (0XFUL << TSTR_MNU_POS)               
#define TSTR_MNU                  TSTR_MNU_MSK                         
#define TSTR_MNU_0                (0X1UL << TSTR_MNU_POS)               
#define TSTR_MNU_1                (0X2UL << TSTR_MNU_POS)               
#define TSTR_MNU_2                (0X4UL << TSTR_MNU_POS)               
#define TSTR_MNU_3                (0X8UL << TSTR_MNU_POS)               
#define TSTR_ST_POS               (4U)                                     
#define TSTR_ST_MSK               (0X7UL << TSTR_ST_POS)                
#define TSTR_ST                   TSTR_ST_MSK                          
#define TSTR_ST_0                 (0X1UL << TSTR_ST_POS)                
#define TSTR_ST_1                 (0X2UL << TSTR_ST_POS)                
#define TSTR_ST_2                 (0X4UL << TSTR_ST_POS)                
#define TSTR_SU_POS               (0U)                                     
#define TSTR_SU_MSK               (0XFUL << TSTR_SU_POS)                
#define TSTR_SU                   TSTR_SU_MSK                          
#define TSTR_SU_0                 (0X1UL << TSTR_SU_POS)                
#define TSTR_SU_1                 (0X2UL << TSTR_SU_POS)                
#define TSTR_SU_2                 (0X4UL << TSTR_SU_POS)                
#define TSTR_SU_3                 (0X8UL << TSTR_SU_POS)                

/********************  BITS DEFINITION FOR RTC::TSDR   *****************/
#define TSDR_WDU_POS              (13U)                                    
#define TSDR_WDU_MSK              (0X7UL << TSDR_WDU_POS)               
#define TSDR_WDU                  TSDR_WDU_MSK                         
#define TSDR_WDU_0                (0X1UL << TSDR_WDU_POS)               
#define TSDR_WDU_1                (0X2UL << TSDR_WDU_POS)               
#define TSDR_WDU_2                (0X4UL << TSDR_WDU_POS)               
#define TSDR_MT_POS               (12U)                                    
#define TSDR_MT_MSK               (0X1UL << TSDR_MT_POS)                
#define TSDR_MT                   TSDR_MT_MSK                          
#define TSDR_MU_POS               (8U)                                     
#define TSDR_MU_MSK               (0XFUL << TSDR_MU_POS)                
#define TSDR_MU                   TSDR_MU_MSK                          
#define TSDR_MU_0                 (0X1UL << TSDR_MU_POS)                
#define TSDR_MU_1                 (0X2UL << TSDR_MU_POS)                
#define TSDR_MU_2                 (0X4UL << TSDR_MU_POS)                
#define TSDR_MU_3                 (0X8UL << TSDR_MU_POS)                
#define TSDR_DT_POS               (4U)                                     
#define TSDR_DT_MSK               (0X3UL << TSDR_DT_POS)                
#define TSDR_DT                   TSDR_DT_MSK                          
#define TSDR_DT_0                 (0X1UL << TSDR_DT_POS)                
#define TSDR_DT_1                 (0X2UL << TSDR_DT_POS)                
#define TSDR_DU_POS               (0U)                                     
#define TSDR_DU_MSK               (0XFUL << TSDR_DU_POS)                
#define TSDR_DU                   TSDR_DU_MSK                          
#define TSDR_DU_0                 (0X1UL << TSDR_DU_POS)                
#define TSDR_DU_1                 (0X2UL << TSDR_DU_POS)                
#define TSDR_DU_2                 (0X4UL << TSDR_DU_POS)                
#define TSDR_DU_3                 (0X8UL << TSDR_DU_POS)                

/********************  BITS DEFINITION FOR RTC::TSSSR   ****************/
#define TSSSR_SS_POS              (0U)                                     
#define TSSSR_SS_MSK              (0XFFFFUL << TSSSR_SS_POS)            
#define TSSSR_SS                  TSSSR_SS_MSK                         

/********************  BITS DEFINITION FOR RTC::CAL   *****************/
#define CALR_CALP_POS             (15U)                                    
#define CALR_CALP_MSK             (0X1UL << CALR_CALP_POS)              
#define CALR_CALP                 CALR_CALP_MSK                        
#define CALR_CALW8_POS            (14U)                                    
#define CALR_CALW8_MSK            (0X1UL << CALR_CALW8_POS)             
#define CALR_CALW8                CALR_CALW8_MSK                       
#define CALR_CALW16_POS           (13U)                                    
#define CALR_CALW16_MSK           (0X1UL << CALR_CALW16_POS)            
#define CALR_CALW16               CALR_CALW16_MSK                      
#define CALR_CALM_POS             (0U)                                     
#define CALR_CALM_MSK             (0X1FFUL << CALR_CALM_POS)            
#define CALR_CALM                 CALR_CALM_MSK                        
#define CALR_CALM_0               (0X001UL << CALR_CALM_POS)            
#define CALR_CALM_1               (0X002UL << CALR_CALM_POS)            
#define CALR_CALM_2               (0X004UL << CALR_CALM_POS)            
#define CALR_CALM_3               (0X008UL << CALR_CALM_POS)            
#define CALR_CALM_4               (0X010UL << CALR_CALM_POS)            
#define CALR_CALM_5               (0X020UL << CALR_CALM_POS)            
#define CALR_CALM_6               (0X040UL << CALR_CALM_POS)            
#define CALR_CALM_7               (0X080UL << CALR_CALM_POS)            
#define CALR_CALM_8               (0X100UL << CALR_CALM_POS)            

/********************  BITS DEFINITION FOR RTC::TAFCR   ****************/
#define TAFCR_ALARMOUTTYPE_POS    (18U)                                    
#define TAFCR_ALARMOUTTYPE_MSK    (0X1UL << TAFCR_ALARMOUTTYPE_POS)     
#define TAFCR_ALARMOUTTYPE        TAFCR_ALARMOUTTYPE_MSK               
#define TAFCR_TSINSEL_POS         (17U)                                    
#define TAFCR_TSINSEL_MSK         (0X1UL << TAFCR_TSINSEL_POS)          
#define TAFCR_TSINSEL             TAFCR_TSINSEL_MSK                    
#define TAFCR_TAMP1INSEL_POS      (16U)                                    
#define TAFCR_TAMP1INSEL_MSK      (0X1UL << TAFCR_TAMP1INSEL_POS)        
#define TAFCR_TAMP1INSEL          TAFCR_TAMP1INSEL_MSK                  
#define TAFCR_TAMPPUDIS_POS       (15U)                                    
#define TAFCR_TAMPPUDIS_MSK       (0X1UL << TAFCR_TAMPPUDIS_POS)        
#define TAFCR_TAMPPUDIS           TAFCR_TAMPPUDIS_MSK                  
#define TAFCR_TAMPPRCH_POS        (13U)                                    
#define TAFCR_TAMPPRCH_MSK        (0X3UL << TAFCR_TAMPPRCH_POS)         
#define TAFCR_TAMPPRCH            TAFCR_TAMPPRCH_MSK                   
#define TAFCR_TAMPPRCH_0          (0X1UL << TAFCR_TAMPPRCH_POS)         
#define TAFCR_TAMPPRCH_1          (0X2UL << TAFCR_TAMPPRCH_POS)         
#define TAFCR_TAMPFLT_POS         (11U)                                    
#define TAFCR_TAMPFLT_MSK         (0X3UL << TAFCR_TAMPFLT_POS)          
#define TAFCR_TAMPFLT             TAFCR_TAMPFLT_MSK                    
#define TAFCR_TAMPFLT_0           (0X1UL << TAFCR_TAMPFLT_POS)          
#define TAFCR_TAMPFLT_1           (0X2UL << TAFCR_TAMPFLT_POS)          
#define TAFCR_TAMPFREQ_POS        (8U)                                     
#define TAFCR_TAMPFREQ_MSK        (0X7UL << TAFCR_TAMPFREQ_POS)         
#define TAFCR_TAMPFREQ            TAFCR_TAMPFREQ_MSK                   
#define TAFCR_TAMPFREQ_0          (0X1UL << TAFCR_TAMPFREQ_POS)         
#define TAFCR_TAMPFREQ_1          (0X2UL << TAFCR_TAMPFREQ_POS)         
#define TAFCR_TAMPFREQ_2          (0X4UL << TAFCR_TAMPFREQ_POS)         
#define TAFCR_TAMPTS_POS          (7U)                                     
#define TAFCR_TAMPTS_MSK          (0X1UL << TAFCR_TAMPTS_POS)           
#define TAFCR_TAMPTS              TAFCR_TAMPTS_MSK                     
#define TAFCR_TAMP2TRG_POS        (4U)                                     
#define TAFCR_TAMP2TRG_MSK        (0X1UL << TAFCR_TAMP2TRG_POS)         
#define TAFCR_TAMP2TRG            TAFCR_TAMP2TRG_MSK                   
#define TAFCR_TAMP2E_POS          (3U)                                     
#define TAFCR_TAMP2E_MSK          (0X1UL << TAFCR_TAMP2E_POS)           
#define TAFCR_TAMP2E              TAFCR_TAMP2E_MSK                     
#define TAFCR_TAMPIE_POS          (2U)                                     
#define TAFCR_TAMPIE_MSK          (0X1UL << TAFCR_TAMPIE_POS)           
#define TAFCR_TAMPIE              TAFCR_TAMPIE_MSK                     
#define TAFCR_TAMP1TRG_POS        (1U)                                     
#define TAFCR_TAMP1TRG_MSK        (0X1UL << TAFCR_TAMP1TRG_POS)         
#define TAFCR_TAMP1TRG            TAFCR_TAMP1TRG_MSK                   
#define TAFCR_TAMP1E_POS          (0U)                                     
#define TAFCR_TAMP1E_MSK          (0X1UL << TAFCR_TAMP1E_POS)           
#define TAFCR_TAMP1E              TAFCR_TAMP1E_MSK                     


/********************  BITS DEFINITION FOR RTC::ALRMASSR   *************/
#define ALRMASSR_MASKSS_POS       (24U)                                    
#define ALRMASSR_MASKSS_MSK       (0XFUL << ALRMASSR_MASKSS_POS)        
#define ALRMASSR_MASKSS           ALRMASSR_MASKSS_MSK                  
#define ALRMASSR_MASKSS_0         (0X1UL << ALRMASSR_MASKSS_POS)        
#define ALRMASSR_MASKSS_1         (0X2UL << ALRMASSR_MASKSS_POS)        
#define ALRMASSR_MASKSS_2         (0X4UL << ALRMASSR_MASKSS_POS)        
#define ALRMASSR_MASKSS_3         (0X8UL << ALRMASSR_MASKSS_POS)        
#define ALRMASSR_SS_POS           (0U)                                     
#define ALRMASSR_SS_MSK           (0X7FFFUL << ALRMASSR_SS_POS)         
#define ALRMASSR_SS               ALRMASSR_SS_MSK                      

/********************  BITS DEFINITION FOR RTC::ALRMBSSR   *************/
#define ALRMBSSR_MASKSS_POS       (24U)                                    
#define ALRMBSSR_MASKSS_MSK       (0XFUL << ALRMBSSR_MASKSS_POS)        
#define ALRMBSSR_MASKSS           ALRMBSSR_MASKSS_MSK                  
#define ALRMBSSR_MASKSS_0         (0X1UL << ALRMBSSR_MASKSS_POS)        
#define ALRMBSSR_MASKSS_1         (0X2UL << ALRMBSSR_MASKSS_POS)        
#define ALRMBSSR_MASKSS_2         (0X4UL << ALRMBSSR_MASKSS_POS)        
#define ALRMBSSR_MASKSS_3         (0X8UL << ALRMBSSR_MASKSS_POS)        
#define ALRMBSSR_SS_POS           (0U)                                     
#define ALRMBSSR_SS_MSK           (0X7FFFUL << ALRMBSSR_SS_POS)         
#define ALRMBSSR_SS               ALRMBSSR_SS_MSK                      

/********************  BITS DEFINITION FOR RTC::BKP0R   ****************/
#define BKP0R_POS                 (0U)                                     
#define BKP0R_MSK                 (0XFFFFFFFFUL << BKP0R_POS)           
#define BKP0R                     BKP0R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP1R   ****************/
#define BKP1R_POS                 (0U)                                     
#define BKP1R_MSK                 (0XFFFFFFFFUL << BKP1R_POS)           
#define BKP1R                     BKP1R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP2R   ****************/
#define BKP2R_POS                 (0U)                                     
#define BKP2R_MSK                 (0XFFFFFFFFUL << BKP2R_POS)           
#define BKP2R                     BKP2R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP3R   ****************/
#define BKP3R_POS                 (0U)                                     
#define BKP3R_MSK                 (0XFFFFFFFFUL << BKP3R_POS)           
#define BKP3R                     BKP3R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP4R   ****************/
#define BKP4R_POS                 (0U)                                     
#define BKP4R_MSK                 (0XFFFFFFFFUL << BKP4R_POS)           
#define BKP4R                     BKP4R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP5R   ****************/
#define BKP5R_POS                 (0U)                                     
#define BKP5R_MSK                 (0XFFFFFFFFUL << BKP5R_POS)           
#define BKP5R                     BKP5R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP6R   ****************/
#define BKP6R_POS                 (0U)                                     
#define BKP6R_MSK                 (0XFFFFFFFFUL << BKP6R_POS)           
#define BKP6R                     BKP6R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP7R   ****************/
#define BKP7R_POS                 (0U)                                     
#define BKP7R_MSK                 (0XFFFFFFFFUL << BKP7R_POS)           
#define BKP7R                     BKP7R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP8R   ****************/
#define BKP8R_POS                 (0U)                                     
#define BKP8R_MSK                 (0XFFFFFFFFUL << BKP8R_POS)           
#define BKP8R                     BKP8R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP9R   ****************/
#define BKP9R_POS                 (0U)                                     
#define BKP9R_MSK                 (0XFFFFFFFFUL << BKP9R_POS)           
#define BKP9R                     BKP9R_MSK                            

/********************  BITS DEFINITION FOR RTC::BKP10R   ***************/
#define BKP10R_POS                (0U)                                     
#define BKP10R_MSK                (0XFFFFFFFFUL << BKP10R_POS)          
#define BKP10R                    BKP10R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP11R   ***************/
#define BKP11R_POS                (0U)                                     
#define BKP11R_MSK                (0XFFFFFFFFUL << BKP11R_POS)          
#define BKP11R                    BKP11R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP12R   ***************/
#define BKP12R_POS                (0U)                                     
#define BKP12R_MSK                (0XFFFFFFFFUL << BKP12R_POS)          
#define BKP12R                    BKP12R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP13R   ***************/
#define BKP13R_POS                (0U)                                     
#define BKP13R_MSK                (0XFFFFFFFFUL << BKP13R_POS)          
#define BKP13R                    BKP13R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP14R   ***************/
#define BKP14R_POS                (0U)                                     
#define BKP14R_MSK                (0XFFFFFFFFUL << BKP14R_POS)          
#define BKP14R                    BKP14R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP15R   ***************/
#define BKP15R_POS                (0U)                                     
#define BKP15R_MSK                (0XFFFFFFFFUL << BKP15R_POS)          
#define BKP15R                    BKP15R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP16R   ***************/
#define BKP16R_POS                (0U)                                     
#define BKP16R_MSK                (0XFFFFFFFFUL << BKP16R_POS)          
#define BKP16R                    BKP16R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP17R   ***************/
#define BKP17R_POS                (0U)                                     
#define BKP17R_MSK                (0XFFFFFFFFUL << BKP17R_POS)          
#define BKP17R                    BKP17R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP18R   ***************/
#define BKP18R_POS                (0U)                                     
#define BKP18R_MSK                (0XFFFFFFFFUL << BKP18R_POS)          
#define BKP18R                    BKP18R_MSK                           

/********************  BITS DEFINITION FOR RTC::BKP19R   ***************/
#define BKP19R_POS                (0U)                                     
#define BKP19R_MSK                (0XFFFFFFFFUL << BKP19R_POS)          
#define BKP19R                    BKP19R_MSK                           

/******************** NUMBER OF BACKUP S ******************************/
#define BKP_NUMBER                       0X000000014U

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_RTC_REGISTER_MASKS */