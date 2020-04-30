#ifndef RIMOT_DMA_REGISTER_MASKS
#define RIMOT_DMA_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/********************  BITS DEFINITION FOR DMA_SXCR   *****************/
#define SXCR_CHSEL_POS       (25U)                                         
#define SXCR_CHSEL_MSK       (0X7UL << SXCR_CHSEL_POS)                  
#define SXCR_CHSEL           SXCR_CHSEL_MSK                            
#define SXCR_CHSEL_0         0X02000000U                                   
#define SXCR_CHSEL_1         0X04000000U                                   
#define SXCR_CHSEL_2         0X08000000U                                   
#define SXCR_MBURST_POS      (23U)                                         
#define SXCR_MBURST_MSK      (0X3UL << SXCR_MBURST_POS)                 
#define SXCR_MBURST          SXCR_MBURST_MSK                           
#define SXCR_MBURST_0        (0X1UL << SXCR_MBURST_POS)                 
#define SXCR_MBURST_1        (0X2UL << SXCR_MBURST_POS)                 
#define SXCR_PBURST_POS      (21U)                                         
#define SXCR_PBURST_MSK      (0X3UL << SXCR_PBURST_POS)                 
#define SXCR_PBURST          SXCR_PBURST_MSK                           
#define SXCR_PBURST_0        (0X1UL << SXCR_PBURST_POS)                 
#define SXCR_PBURST_1        (0X2UL << SXCR_PBURST_POS)                 
#define SXCR_CT_POS          (19U)                                         
#define SXCR_CT_MSK          (0X1UL << SXCR_CT_POS)                     
#define SXCR_CT              SXCR_CT_MSK                               
#define SXCR_DBM_POS         (18U)                                         
#define SXCR_DBM_MSK         (0X1UL << SXCR_DBM_POS)                    
#define SXCR_DBM             SXCR_DBM_MSK                              
#define SXCR_PL_POS          (16U)                                         
#define SXCR_PL_MSK          (0X3UL << SXCR_PL_POS)                     
#define SXCR_PL              SXCR_PL_MSK                               
#define SXCR_PL_0            (0X1UL << SXCR_PL_POS)                     
#define SXCR_PL_1            (0X2UL << SXCR_PL_POS)                     
#define SXCR_PINCOS_POS      (15U)                                         
#define SXCR_PINCOS_MSK      (0X1UL << SXCR_PINCOS_POS)                 
#define SXCR_PINCOS          SXCR_PINCOS_MSK                           
#define SXCR_MSIZE_POS       (13U)                                         
#define SXCR_MSIZE_MSK       (0X3UL << SXCR_MSIZE_POS)                  
#define SXCR_MSIZE           SXCR_MSIZE_MSK                            
#define SXCR_MSIZE_0         (0X1UL << SXCR_MSIZE_POS)                  
#define SXCR_MSIZE_1         (0X2UL << SXCR_MSIZE_POS)                  
#define SXCR_PSIZE_POS       (11U)                                         
#define SXCR_PSIZE_MSK       (0X3UL << SXCR_PSIZE_POS)                  
#define SXCR_PSIZE           SXCR_PSIZE_MSK                            
#define SXCR_PSIZE_0         (0X1UL << SXCR_PSIZE_POS)                  
#define SXCR_PSIZE_1         (0X2UL << SXCR_PSIZE_POS)                  
#define SXCR_MINC_POS        (10U)                                         
#define SXCR_MINC_MSK        (0X1UL << SXCR_MINC_POS)                   
#define SXCR_MINC            SXCR_MINC_MSK                             
#define SXCR_PINC_POS        (9U)                                          
#define SXCR_PINC_MSK        (0X1UL << SXCR_PINC_POS)                   
#define SXCR_PINC            SXCR_PINC_MSK                             
#define SXCR_CIRC_POS        (8U)                                          
#define SXCR_CIRC_MSK        (0X1UL << SXCR_CIRC_POS)                   
#define SXCR_CIRC            SXCR_CIRC_MSK                             
#define SXCR_DIR_POS         (6U)                                          
#define SXCR_DIR_MSK         (0X3UL << SXCR_DIR_POS)                    
#define SXCR_DIR             SXCR_DIR_MSK                              
#define SXCR_DIR_0           (0X1UL << SXCR_DIR_POS)                    
#define SXCR_DIR_1           (0X2UL << SXCR_DIR_POS)                    
#define SXCR_PFCTRL_POS      (5U)                                          
#define SXCR_PFCTRL_MSK      (0X1UL << SXCR_PFCTRL_POS)                 
#define SXCR_PFCTRL          SXCR_PFCTRL_MSK                           
#define SXCR_TCIE_POS        (4U)                                          
#define SXCR_TCIE_MSK        (0X1UL << SXCR_TCIE_POS)                   
#define SXCR_TCIE            SXCR_TCIE_MSK                             
#define SXCR_HTIE_POS        (3U)                                          
#define SXCR_HTIE_MSK        (0X1UL << SXCR_HTIE_POS)                   
#define SXCR_HTIE            SXCR_HTIE_MSK                             
#define SXCR_TEIE_POS        (2U)                                          
#define SXCR_TEIE_MSK        (0X1UL << SXCR_TEIE_POS)                   
#define SXCR_TEIE            SXCR_TEIE_MSK                             
#define SXCR_DMEIE_POS       (1U)                                          
#define SXCR_DMEIE_MSK       (0X1UL << SXCR_DMEIE_POS)                  
#define SXCR_DMEIE           SXCR_DMEIE_MSK                            
#define SXCR_EN_POS          (0U)                                          
#define SXCR_EN_MSK          (0X1UL << SXCR_EN_POS)                     
#define SXCR_EN              SXCR_EN_MSK                               

/********************  BITS DEFINITION FOR DMA_SXCNDTR   **************/
#define SXNDT_POS            (0U)                                          
#define SXNDT_MSK            (0XFFFFUL << SXNDT_POS)                    
#define SXNDT                SXNDT_MSK                                 
#define SXNDT_0              (0X0001UL << SXNDT_POS)                    
#define SXNDT_1              (0X0002UL << SXNDT_POS)                    
#define SXNDT_2              (0X0004UL << SXNDT_POS)                    
#define SXNDT_3              (0X0008UL << SXNDT_POS)                    
#define SXNDT_4              (0X0010UL << SXNDT_POS)                    
#define SXNDT_5              (0X0020UL << SXNDT_POS)                    
#define SXNDT_6              (0X0040UL << SXNDT_POS)                    
#define SXNDT_7              (0X0080UL << SXNDT_POS)                    
#define SXNDT_8              (0X0100UL << SXNDT_POS)                    
#define SXNDT_9              (0X0200UL << SXNDT_POS)                    
#define SXNDT_10             (0X0400UL << SXNDT_POS)                    
#define SXNDT_11             (0X0800UL << SXNDT_POS)                    
#define SXNDT_12             (0X1000UL << SXNDT_POS)                    
#define SXNDT_13             (0X2000UL << SXNDT_POS)                    
#define SXNDT_14             (0X4000UL << SXNDT_POS)                    
#define SXNDT_15             (0X8000UL << SXNDT_POS)                    

/********************  BITS DEFINITION FOR DMA_SXFCR   ****************/ 
#define SXFCR_FEIE_POS       (7U)                                          
#define SXFCR_FEIE_MSK       (0X1UL << SXFCR_FEIE_POS)                  
#define SXFCR_FEIE           SXFCR_FEIE_MSK                            
#define SXFCR_FS_POS         (3U)                                          
#define SXFCR_FS_MSK         (0X7UL << SXFCR_FS_POS)                    
#define SXFCR_FS             SXFCR_FS_MSK                              
#define SXFCR_FS_0           (0X1UL << SXFCR_FS_POS)                    
#define SXFCR_FS_1           (0X2UL << SXFCR_FS_POS)                    
#define SXFCR_FS_2           (0X4UL << SXFCR_FS_POS)                    
#define SXFCR_DMDIS_POS      (2U)                                          
#define SXFCR_DMDIS_MSK      (0X1UL << SXFCR_DMDIS_POS)                 
#define SXFCR_DMDIS          SXFCR_DMDIS_MSK                           
#define SXFCR_FTH_POS        (0U)                                          
#define SXFCR_FTH_MSK        (0X3UL << SXFCR_FTH_POS)                   
#define SXFCR_FTH            SXFCR_FTH_MSK                             
#define SXFCR_FTH_0          (0X1UL << SXFCR_FTH_POS)                   
#define SXFCR_FTH_1          (0X2UL << SXFCR_FTH_POS)                   

/********************  BITS DEFINITION FOR DMA_LISR   *****************/ 
#define LISR_TCIF3_POS       (27U)                                         
#define LISR_TCIF3_MSK       (0X1UL << LISR_TCIF3_POS)                  
#define LISR_TCIF3           LISR_TCIF3_MSK                            
#define LISR_HTIF3_POS       (26U)                                         
#define LISR_HTIF3_MSK       (0X1UL << LISR_HTIF3_POS)                  
#define LISR_HTIF3           LISR_HTIF3_MSK                            
#define LISR_TEIF3_POS       (25U)                                         
#define LISR_TEIF3_MSK       (0X1UL << LISR_TEIF3_POS)                  
#define LISR_TEIF3           LISR_TEIF3_MSK                            
#define LISR_DMEIF3_POS      (24U)                                         
#define LISR_DMEIF3_MSK      (0X1UL << LISR_DMEIF3_POS)                 
#define LISR_DMEIF3          LISR_DMEIF3_MSK                           
#define LISR_FEIF3_POS       (22U)                                         
#define LISR_FEIF3_MSK       (0X1UL << LISR_FEIF3_POS)                  
#define LISR_FEIF3           LISR_FEIF3_MSK                            
#define LISR_TCIF2_POS       (21U)                                         
#define LISR_TCIF2_MSK       (0X1UL << LISR_TCIF2_POS)                  
#define LISR_TCIF2           LISR_TCIF2_MSK                            
#define LISR_HTIF2_POS       (20U)                                         
#define LISR_HTIF2_MSK       (0X1UL << LISR_HTIF2_POS)                  
#define LISR_HTIF2           LISR_HTIF2_MSK                            
#define LISR_TEIF2_POS       (19U)                                         
#define LISR_TEIF2_MSK       (0X1UL << LISR_TEIF2_POS)                  
#define LISR_TEIF2           LISR_TEIF2_MSK                            
#define LISR_DMEIF2_POS      (18U)                                         
#define LISR_DMEIF2_MSK      (0X1UL << LISR_DMEIF2_POS)                 
#define LISR_DMEIF2          LISR_DMEIF2_MSK                           
#define LISR_FEIF2_POS       (16U)                                         
#define LISR_FEIF2_MSK       (0X1UL << LISR_FEIF2_POS)                  
#define LISR_FEIF2           LISR_FEIF2_MSK                            
#define LISR_TCIF1_POS       (11U)                                         
#define LISR_TCIF1_MSK       (0X1UL << LISR_TCIF1_POS)                  
#define LISR_TCIF1           LISR_TCIF1_MSK                            
#define LISR_HTIF1_POS       (10U)                                         
#define LISR_HTIF1_MSK       (0X1UL << LISR_HTIF1_POS)                  
#define LISR_HTIF1           LISR_HTIF1_MSK                            
#define LISR_TEIF1_POS       (9U)                                          
#define LISR_TEIF1_MSK       (0X1UL << LISR_TEIF1_POS)                  
#define LISR_TEIF1           LISR_TEIF1_MSK                            
#define LISR_DMEIF1_POS      (8U)                                          
#define LISR_DMEIF1_MSK      (0X1UL << LISR_DMEIF1_POS)                 
#define LISR_DMEIF1          LISR_DMEIF1_MSK                           
#define LISR_FEIF1_POS       (6U)                                          
#define LISR_FEIF1_MSK       (0X1UL << LISR_FEIF1_POS)                  
#define LISR_FEIF1           LISR_FEIF1_MSK                            
#define LISR_TCIF0_POS       (5U)                                          
#define LISR_TCIF0_MSK       (0X1UL << LISR_TCIF0_POS)                  
#define LISR_TCIF0           LISR_TCIF0_MSK                            
#define LISR_HTIF0_POS       (4U)                                          
#define LISR_HTIF0_MSK       (0X1UL << LISR_HTIF0_POS)                  
#define LISR_HTIF0           LISR_HTIF0_MSK                            
#define LISR_TEIF0_POS       (3U)                                          
#define LISR_TEIF0_MSK       (0X1UL << LISR_TEIF0_POS)                  
#define LISR_TEIF0           LISR_TEIF0_MSK                            
#define LISR_DMEIF0_POS      (2U)                                          
#define LISR_DMEIF0_MSK      (0X1UL << LISR_DMEIF0_POS)                 
#define LISR_DMEIF0          LISR_DMEIF0_MSK                           
#define LISR_FEIF0_POS       (0U)                                          
#define LISR_FEIF0_MSK       (0X1UL << LISR_FEIF0_POS)                  
#define LISR_FEIF0           LISR_FEIF0_MSK                            

/********************  BITS DEFINITION FOR DMA_HISR   *****************/ 
#define HISR_TCIF7_POS       (27U)                                         
#define HISR_TCIF7_MSK       (0X1UL << HISR_TCIF7_POS)                  
#define HISR_TCIF7           HISR_TCIF7_MSK                            
#define HISR_HTIF7_POS       (26U)                                         
#define HISR_HTIF7_MSK       (0X1UL << HISR_HTIF7_POS)                  
#define HISR_HTIF7           HISR_HTIF7_MSK                            
#define HISR_TEIF7_POS       (25U)                                         
#define HISR_TEIF7_MSK       (0X1UL << HISR_TEIF7_POS)                  
#define HISR_TEIF7           HISR_TEIF7_MSK                            
#define HISR_DMEIF7_POS      (24U)                                         
#define HISR_DMEIF7_MSK      (0X1UL << HISR_DMEIF7_POS)                 
#define HISR_DMEIF7          HISR_DMEIF7_MSK                           
#define HISR_FEIF7_POS       (22U)                                         
#define HISR_FEIF7_MSK       (0X1UL << HISR_FEIF7_POS)                  
#define HISR_FEIF7           HISR_FEIF7_MSK                            
#define HISR_TCIF6_POS       (21U)                                         
#define HISR_TCIF6_MSK       (0X1UL << HISR_TCIF6_POS)                  
#define HISR_TCIF6           HISR_TCIF6_MSK                            
#define HISR_HTIF6_POS       (20U)                                         
#define HISR_HTIF6_MSK       (0X1UL << HISR_HTIF6_POS)                  
#define HISR_HTIF6           HISR_HTIF6_MSK                            
#define HISR_TEIF6_POS       (19U)                                         
#define HISR_TEIF6_MSK       (0X1UL << HISR_TEIF6_POS)                  
#define HISR_TEIF6           HISR_TEIF6_MSK                            
#define HISR_DMEIF6_POS      (18U)                                         
#define HISR_DMEIF6_MSK      (0X1UL << HISR_DMEIF6_POS)                 
#define HISR_DMEIF6          HISR_DMEIF6_MSK                           
#define HISR_FEIF6_POS       (16U)                                         
#define HISR_FEIF6_MSK       (0X1UL << HISR_FEIF6_POS)                  
#define HISR_FEIF6           HISR_FEIF6_MSK                            
#define HISR_TCIF5_POS       (11U)                                         
#define HISR_TCIF5_MSK       (0X1UL << HISR_TCIF5_POS)                  
#define HISR_TCIF5           HISR_TCIF5_MSK                            
#define HISR_HTIF5_POS       (10U)                                         
#define HISR_HTIF5_MSK       (0X1UL << HISR_HTIF5_POS)                  
#define HISR_HTIF5           HISR_HTIF5_MSK                            
#define HISR_TEIF5_POS       (9U)                                          
#define HISR_TEIF5_MSK       (0X1UL << HISR_TEIF5_POS)                  
#define HISR_TEIF5           HISR_TEIF5_MSK                            
#define HISR_DMEIF5_POS      (8U)                                          
#define HISR_DMEIF5_MSK      (0X1UL << HISR_DMEIF5_POS)                 
#define HISR_DMEIF5          HISR_DMEIF5_MSK                           
#define HISR_FEIF5_POS       (6U)                                          
#define HISR_FEIF5_MSK       (0X1UL << HISR_FEIF5_POS)                  
#define HISR_FEIF5           HISR_FEIF5_MSK                            
#define HISR_TCIF4_POS       (5U)                                          
#define HISR_TCIF4_MSK       (0X1UL << HISR_TCIF4_POS)                  
#define HISR_TCIF4           HISR_TCIF4_MSK                            
#define HISR_HTIF4_POS       (4U)                                          
#define HISR_HTIF4_MSK       (0X1UL << HISR_HTIF4_POS)                  
#define HISR_HTIF4           HISR_HTIF4_MSK                            
#define HISR_TEIF4_POS       (3U)                                          
#define HISR_TEIF4_MSK       (0X1UL << HISR_TEIF4_POS)                  
#define HISR_TEIF4           HISR_TEIF4_MSK                            
#define HISR_DMEIF4_POS      (2U)                                          
#define HISR_DMEIF4_MSK      (0X1UL << HISR_DMEIF4_POS)                 
#define HISR_DMEIF4          HISR_DMEIF4_MSK                           
#define HISR_FEIF4_POS       (0U)                                          
#define HISR_FEIF4_MSK       (0X1UL << HISR_FEIF4_POS)                  
#define HISR_FEIF4           HISR_FEIF4_MSK                            

/********************  BITS DEFINITION FOR DMA_LIFCR   ****************/ 
#define LIFCR_CTCIF3_POS     (27U)                                         
#define LIFCR_CTCIF3_MSK     (0X1UL << LIFCR_CTCIF3_POS)                
#define LIFCR_CTCIF3         LIFCR_CTCIF3_MSK                          
#define LIFCR_CHTIF3_POS     (26U)                                         
#define LIFCR_CHTIF3_MSK     (0X1UL << LIFCR_CHTIF3_POS)                
#define LIFCR_CHTIF3         LIFCR_CHTIF3_MSK                          
#define LIFCR_CTEIF3_POS     (25U)                                         
#define LIFCR_CTEIF3_MSK     (0X1UL << LIFCR_CTEIF3_POS)                
#define LIFCR_CTEIF3         LIFCR_CTEIF3_MSK                          
#define LIFCR_CDMEIF3_POS    (24U)                                         
#define LIFCR_CDMEIF3_MSK    (0X1UL << LIFCR_CDMEIF3_POS)               
#define LIFCR_CDMEIF3        LIFCR_CDMEIF3_MSK                         
#define LIFCR_CFEIF3_POS     (22U)                                         
#define LIFCR_CFEIF3_MSK     (0X1UL << LIFCR_CFEIF3_POS)                
#define LIFCR_CFEIF3         LIFCR_CFEIF3_MSK                          
#define LIFCR_CTCIF2_POS     (21U)                                         
#define LIFCR_CTCIF2_MSK     (0X1UL << LIFCR_CTCIF2_POS)                
#define LIFCR_CTCIF2         LIFCR_CTCIF2_MSK                          
#define LIFCR_CHTIF2_POS     (20U)                                         
#define LIFCR_CHTIF2_MSK     (0X1UL << LIFCR_CHTIF2_POS)                
#define LIFCR_CHTIF2         LIFCR_CHTIF2_MSK                          
#define LIFCR_CTEIF2_POS     (19U)                                         
#define LIFCR_CTEIF2_MSK     (0X1UL << LIFCR_CTEIF2_POS)                
#define LIFCR_CTEIF2         LIFCR_CTEIF2_MSK                          
#define LIFCR_CDMEIF2_POS    (18U)                                         
#define LIFCR_CDMEIF2_MSK    (0X1UL << LIFCR_CDMEIF2_POS)               
#define LIFCR_CDMEIF2        LIFCR_CDMEIF2_MSK                         
#define LIFCR_CFEIF2_POS     (16U)                                         
#define LIFCR_CFEIF2_MSK     (0X1UL << LIFCR_CFEIF2_POS)                
#define LIFCR_CFEIF2         LIFCR_CFEIF2_MSK                          
#define LIFCR_CTCIF1_POS     (11U)                                         
#define LIFCR_CTCIF1_MSK     (0X1UL << LIFCR_CTCIF1_POS)                
#define LIFCR_CTCIF1         LIFCR_CTCIF1_MSK                          
#define LIFCR_CHTIF1_POS     (10U)                                         
#define LIFCR_CHTIF1_MSK     (0X1UL << LIFCR_CHTIF1_POS)                
#define LIFCR_CHTIF1         LIFCR_CHTIF1_MSK                          
#define LIFCR_CTEIF1_POS     (9U)                                          
#define LIFCR_CTEIF1_MSK     (0X1UL << LIFCR_CTEIF1_POS)                
#define LIFCR_CTEIF1         LIFCR_CTEIF1_MSK                          
#define LIFCR_CDMEIF1_POS    (8U)                                          
#define LIFCR_CDMEIF1_MSK    (0X1UL << LIFCR_CDMEIF1_POS)               
#define LIFCR_CDMEIF1        LIFCR_CDMEIF1_MSK                         
#define LIFCR_CFEIF1_POS     (6U)                                          
#define LIFCR_CFEIF1_MSK     (0X1UL << LIFCR_CFEIF1_POS)                
#define LIFCR_CFEIF1         LIFCR_CFEIF1_MSK                          
#define LIFCR_CTCIF0_POS     (5U)                                          
#define LIFCR_CTCIF0_MSK     (0X1UL << LIFCR_CTCIF0_POS)                
#define LIFCR_CTCIF0         LIFCR_CTCIF0_MSK                          
#define LIFCR_CHTIF0_POS     (4U)                                          
#define LIFCR_CHTIF0_MSK     (0X1UL << LIFCR_CHTIF0_POS)                
#define LIFCR_CHTIF0         LIFCR_CHTIF0_MSK                          
#define LIFCR_CTEIF0_POS     (3U)                                          
#define LIFCR_CTEIF0_MSK     (0X1UL << LIFCR_CTEIF0_POS)                
#define LIFCR_CTEIF0         LIFCR_CTEIF0_MSK                          
#define LIFCR_CDMEIF0_POS    (2U)                                          
#define LIFCR_CDMEIF0_MSK    (0X1UL << LIFCR_CDMEIF0_POS)               
#define LIFCR_CDMEIF0        LIFCR_CDMEIF0_MSK                         
#define LIFCR_CFEIF0_POS     (0U)                                          
#define LIFCR_CFEIF0_MSK     (0X1UL << LIFCR_CFEIF0_POS)                
#define LIFCR_CFEIF0         LIFCR_CFEIF0_MSK                          

/********************  BITS DEFINITION FOR DMA_HIFCR    ****************/ 
#define HIFCR_CTCIF7_POS     (27U)                                         
#define HIFCR_CTCIF7_MSK     (0X1UL << HIFCR_CTCIF7_POS)                
#define HIFCR_CTCIF7         HIFCR_CTCIF7_MSK                          
#define HIFCR_CHTIF7_POS     (26U)                                         
#define HIFCR_CHTIF7_MSK     (0X1UL << HIFCR_CHTIF7_POS)                
#define HIFCR_CHTIF7         HIFCR_CHTIF7_MSK                          
#define HIFCR_CTEIF7_POS     (25U)                                         
#define HIFCR_CTEIF7_MSK     (0X1UL << HIFCR_CTEIF7_POS)                
#define HIFCR_CTEIF7         HIFCR_CTEIF7_MSK                          
#define HIFCR_CDMEIF7_POS    (24U)                                         
#define HIFCR_CDMEIF7_MSK    (0X1UL << HIFCR_CDMEIF7_POS)               
#define HIFCR_CDMEIF7        HIFCR_CDMEIF7_MSK                         
#define HIFCR_CFEIF7_POS     (22U)                                         
#define HIFCR_CFEIF7_MSK     (0X1UL << HIFCR_CFEIF7_POS)                
#define HIFCR_CFEIF7         HIFCR_CFEIF7_MSK                          
#define HIFCR_CTCIF6_POS     (21U)                                         
#define HIFCR_CTCIF6_MSK     (0X1UL << HIFCR_CTCIF6_POS)                
#define HIFCR_CTCIF6         HIFCR_CTCIF6_MSK                          
#define HIFCR_CHTIF6_POS     (20U)                                         
#define HIFCR_CHTIF6_MSK     (0X1UL << HIFCR_CHTIF6_POS)                
#define HIFCR_CHTIF6         HIFCR_CHTIF6_MSK                          
#define HIFCR_CTEIF6_POS     (19U)                                         
#define HIFCR_CTEIF6_MSK     (0X1UL << HIFCR_CTEIF6_POS)                
#define HIFCR_CTEIF6         HIFCR_CTEIF6_MSK                          
#define HIFCR_CDMEIF6_POS    (18U)                                         
#define HIFCR_CDMEIF6_MSK    (0X1UL << HIFCR_CDMEIF6_POS)               
#define HIFCR_CDMEIF6        HIFCR_CDMEIF6_MSK                         
#define HIFCR_CFEIF6_POS     (16U)                                         
#define HIFCR_CFEIF6_MSK     (0X1UL << HIFCR_CFEIF6_POS)                
#define HIFCR_CFEIF6         HIFCR_CFEIF6_MSK                          
#define HIFCR_CTCIF5_POS     (11U)                                         
#define HIFCR_CTCIF5_MSK     (0X1UL << HIFCR_CTCIF5_POS)                
#define HIFCR_CTCIF5         HIFCR_CTCIF5_MSK                          
#define HIFCR_CHTIF5_POS     (10U)                                         
#define HIFCR_CHTIF5_MSK     (0X1UL << HIFCR_CHTIF5_POS)                
#define HIFCR_CHTIF5         HIFCR_CHTIF5_MSK                          
#define HIFCR_CTEIF5_POS     (9U)                                          
#define HIFCR_CTEIF5_MSK     (0X1UL << HIFCR_CTEIF5_POS)                
#define HIFCR_CTEIF5         HIFCR_CTEIF5_MSK                          
#define HIFCR_CDMEIF5_POS    (8U)                                          
#define HIFCR_CDMEIF5_MSK    (0X1UL << HIFCR_CDMEIF5_POS)               
#define HIFCR_CDMEIF5        HIFCR_CDMEIF5_MSK                         
#define HIFCR_CFEIF5_POS     (6U)                                          
#define HIFCR_CFEIF5_MSK     (0X1UL << HIFCR_CFEIF5_POS)                
#define HIFCR_CFEIF5         HIFCR_CFEIF5_MSK                          
#define HIFCR_CTCIF4_POS     (5U)                                          
#define HIFCR_CTCIF4_MSK     (0X1UL << HIFCR_CTCIF4_POS)                
#define HIFCR_CTCIF4         HIFCR_CTCIF4_MSK                          
#define HIFCR_CHTIF4_POS     (4U)                                          
#define HIFCR_CHTIF4_MSK     (0X1UL << HIFCR_CHTIF4_POS)                
#define HIFCR_CHTIF4         HIFCR_CHTIF4_MSK                          
#define HIFCR_CTEIF4_POS     (3U)                                          
#define HIFCR_CTEIF4_MSK     (0X1UL << HIFCR_CTEIF4_POS)                
#define HIFCR_CTEIF4         HIFCR_CTEIF4_MSK                          
#define HIFCR_CDMEIF4_POS    (2U)                                          
#define HIFCR_CDMEIF4_MSK    (0X1UL << HIFCR_CDMEIF4_POS)               
#define HIFCR_CDMEIF4        HIFCR_CDMEIF4_MSK                         
#define HIFCR_CFEIF4_POS     (0U)                                          
#define HIFCR_CFEIF4_MSK     (0X1UL << HIFCR_CFEIF4_POS)                
#define HIFCR_CFEIF4         HIFCR_CFEIF4_MSK                          

/******************  BIT DEFINITION FOR DMA_SXPAR   ********************/
#define SXPAR_PA_POS         (0U)                                          
#define SXPAR_PA_MSK         (0XFFFFFFFFUL << SXPAR_PA_POS)             
#define SXPAR_PA             SXPAR_PA_MSK                              

/******************  BIT DEFINITION FOR DMA_SXM0AR   ********************/
#define SXM0AR_M0A_POS       (0U)                                          
#define SXM0AR_M0A_MSK       (0XFFFFFFFFUL << SXM0AR_M0A_POS)           
#define SXM0AR_M0A           SXM0AR_M0A_MSK                            

/******************  BIT DEFINITION FOR DMA_SXM1AR   ********************/
#define SXM1AR_M1A_POS       (0U)                                          
#define SXM1AR_M1A_MSK       (0XFFFFFFFFUL << SXM1AR_M1A_POS)           
#define SXM1AR_M1A           SXM1AR_M1A_MSK                                 

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_DMA_REGISTER_MASKS */
