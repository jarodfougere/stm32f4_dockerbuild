#ifndef RIMOT_ADC_REGISTER_MASKS
#define RIMOT_ADC_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/* BIT DEFINITIONS FOR ADC SR */
#define SR_AWD_POS            (0U)                                         
#define SR_AWD_MSK            (0x1UL << SR_AWD_POS) 
#define SR_AWD                SR_AWD_MSK    
#define SR_EOC_POS            (1U)                                         
#define SR_EOC_MSK            (0x1UL << SR_EOC_POS)  
#define SR_EOC                SR_EOC_MSK                         
#define SR_JEOC_POS           (2U)                                         
#define SR_JEOC_MSK           (0x1UL << SR_JEOC_POS)                    
#define SR_JEOC               SR_JEOC_MSK                              
#define SR_JSTRT_POS          (3U)                                         
#define SR_JSTRT_MSK          (0x1UL << SR_JSTRT_POS)                   
#define SR_JSTRT              SR_JSTRT_MSK                             
#define SR_STRT_POS           (4U)                                         
#define SR_STRT_MSK           (0x1UL << SR_STRT_POS)                    
#define SR_STRT               SR_STRT_MSK                              
#define SR_OVR_POS            (5U)                                         
#define SR_OVR_MSK            (0x1UL << SR_OVR_POS)                     
#define SR_OVR                SR_OVR_MSK                               

/*******************  Bit definition for CR1 register  ********************/
#define CR1_AWDCH_POS         (0U)                                         
#define CR1_AWDCH_MSK         (0x1FUL << CR1_AWDCH_POS)                 
#define CR1_AWDCH             CR1_AWDCH_MSK                          
#define CR1_AWDCH_0           (0x01UL << CR1_AWDCH_POS)                 
#define CR1_AWDCH_1           (0x02UL << CR1_AWDCH_POS)                 
#define CR1_AWDCH_2           (0x04UL << CR1_AWDCH_POS)                 
#define CR1_AWDCH_3           (0x08UL << CR1_AWDCH_POS)                 
#define CR1_AWDCH_4           (0x10UL << CR1_AWDCH_POS)                 
#define CR1_EOCIE_POS         (5U)                                         
#define CR1_EOCIE_MSK         (0x1UL << CR1_EOCIE_POS)                  
#define CR1_EOCIE             CR1_EOCIE_MSK                            
#define CR1_AWDIE_POS         (6U)                                         
#define CR1_AWDIE_MSK         (0x1UL << CR1_AWDIE_POS)                  
#define CR1_AWDIE             CR1_AWDIE_MSK                            
#define CR1_JEOCIE_POS        (7U)                                         
#define CR1_JEOCIE_MSK        (0x1UL << CR1_JEOCIE_POS)                 
#define CR1_JEOCIE            CR1_JEOCIE_MSK                           
#define CR1_SCAN_POS          (8U)                                         
#define CR1_SCAN_MSK          (0x1UL << CR1_SCAN_POS)                   
#define CR1_SCAN              CR1_SCAN_MSK                             
#define CR1_AWDSGL_POS        (9U)                                         
#define CR1_AWDSGL_MSK        (0x1UL << CR1_AWDSGL_POS)                 
#define CR1_AWDSGL            CR1_AWDSGL_MSK                           
#define CR1_JAUTO_POS         (10U)                                        
#define CR1_JAUTO_MSK         (0x1UL << CR1_JAUTO_POS)                  
#define CR1_JAUTO             CR1_JAUTO_MSK                            
#define CR1_DISCEN_POS        (11U)                                        
#define CR1_DISCEN_MSK        (0x1UL << CR1_DISCEN_POS)                 
#define CR1_DISCEN            CR1_DISCEN_MSK                           
#define CR1_JDISCEN_POS       (12U)                                        
#define CR1_JDISCEN_MSK       (0x1UL << CR1_JDISCEN_POS)                
#define CR1_JDISCEN           CR1_JDISCEN_MSK                          
#define CR1_DISCNUM_POS       (13U)                                        
#define CR1_DISCNUM_MSK       (0x7UL << CR1_DISCNUM_POS)                
#define CR1_DISCNUM           CR1_DISCNUM_MSK                          
#define CR1_DISCNUM_0         (0x1UL << CR1_DISCNUM_POS)                
#define CR1_DISCNUM_1         (0x2UL << CR1_DISCNUM_POS)                
#define CR1_DISCNUM_2         (0x4UL << CR1_DISCNUM_POS)                
#define CR1_JAWDEN_POS        (22U)                                        
#define CR1_JAWDEN_MSK        (0x1UL << CR1_JAWDEN_POS)                 
#define CR1_JAWDEN            CR1_JAWDEN_MSK                           
#define CR1_AWDEN_POS         (23U)                                        
#define CR1_AWDEN_MSK         (0x1UL << CR1_AWDEN_POS)                  
#define CR1_AWDEN             CR1_AWDEN_MSK                            
#define CR1_RES_POS           (24U)                                        
#define CR1_RES_MSK           (0x3UL << CR1_RES_POS)                    
#define CR1_RES               CR1_RES_MSK                              
#define CR1_RES_0             (0x1UL << CR1_RES_POS)                    
#define CR1_RES_1             (0x2UL << CR1_RES_POS)                    
#define CR1_OVRIE_POS         (26U)                                        
#define CR1_OVRIE_MSK         (0x1UL << CR1_OVRIE_POS)                  
#define CR1_OVRIE             CR1_OVRIE_MSK                            

/*******************  Bit definition for CR2 register  ********************/
#define CR2_ADON_POS          (0U)                                         
#define CR2_ADON_MSK          (0x1UL << CR2_ADON_POS)                   
#define CR2_ADON              CR2_ADON_MSK                             
#define CR2_CONT_POS          (1U)                                         
#define CR2_CONT_MSK          (0x1UL << CR2_CONT_POS)                   
#define CR2_CONT              CR2_CONT_MSK                             
#define CR2_DMA_POS           (8U)                                         
#define CR2_DMA_MSK           (0x1UL << CR2_DMA_POS)                    
#define CR2_DMA               CR2_DMA_MSK                              
#define CR2_DDS_POS           (9U)                                         
#define CR2_DDS_MSK           (0x1UL << CR2_DDS_POS)                    
#define CR2_DDS               CR2_DDS_MSK                              
#define CR2_EOCS_POS          (10U)                                        
#define CR2_EOCS_MSK          (0x1UL << CR2_EOCS_POS)                   
#define CR2_EOCS              CR2_EOCS_MSK                             
#define CR2_ALIGN_POS         (11U)                                        
#define CR2_ALIGN_MSK         (0x1UL << CR2_ALIGN_POS)                  
#define CR2_ALIGN             CR2_ALIGN_MSK                            
#define CR2_JEXTSEL_POS       (16U)                                        
#define CR2_JEXTSEL_MSK       (0xFUL << CR2_JEXTSEL_POS)                
#define CR2_JEXTSEL           CR2_JEXTSEL_MSK                          
#define CR2_JEXTSEL_0         (0x1UL << CR2_JEXTSEL_POS)                
#define CR2_JEXTSEL_1         (0x2UL << CR2_JEXTSEL_POS)                
#define CR2_JEXTSEL_2         (0x4UL << CR2_JEXTSEL_POS)                
#define CR2_JEXTSEL_3         (0x8UL << CR2_JEXTSEL_POS)                
#define CR2_JEXTEN_POS        (20U)                                        
#define CR2_JEXTEN_MSK        (0x3UL << CR2_JEXTEN_POS)                 
#define CR2_JEXTEN            CR2_JEXTEN_MSK                           
#define CR2_JEXTEN_0          (0x1UL << CR2_JEXTEN_POS)                 
#define CR2_JEXTEN_1          (0x2UL << CR2_JEXTEN_POS)                 
#define CR2_JSWSTART_POS      (22U)                                        
#define CR2_JSWSTART_MSK      (0x1UL << CR2_JSWSTART_POS)               
#define CR2_JSWSTART          CR2_JSWSTART_MSK                         
#define CR2_EXTSEL_POS        (24U)                                        
#define CR2_EXTSEL_MSK        (0xFUL << CR2_EXTSEL_POS)                 
#define CR2_EXTSEL            CR2_EXTSEL_MSK                           
#define CR2_EXTSEL_0          (0x1UL << CR2_EXTSEL_POS)                 
#define CR2_EXTSEL_1          (0x2UL << CR2_EXTSEL_POS)                 
#define CR2_EXTSEL_2          (0x4UL << CR2_EXTSEL_POS)                 
#define CR2_EXTSEL_3          (0x8UL << CR2_EXTSEL_POS)                 
#define CR2_EXTEN_POS         (28U)                                        
#define CR2_EXTEN_MSK         (0x3UL << CR2_EXTEN_POS)                  
#define CR2_EXTEN             CR2_EXTEN_MSK                            
#define CR2_EXTEN_0           (0x1UL << CR2_EXTEN_POS)                  
#define CR2_EXTEN_1           (0x2UL << CR2_EXTEN_POS)                  
#define CR2_SWSTART_POS       (30U)                                        
#define CR2_SWSTART_MSK       (0x1UL << CR2_SWSTART_POS)                
#define CR2_SWSTART           CR2_SWSTART_MSK                          

/******************  Bit definition for SMPR1 register  *******************/
#define SMPR1_SMP10_POS       (0U)                                         
#define SMPR1_SMP10_MSK       (0x7UL << SMPR1_SMP10_POS)                
#define SMPR1_SMP10           SMPR1_SMP10_MSK                          
#define SMPR1_SMP10_0         (0x1UL << SMPR1_SMP10_POS)                
#define SMPR1_SMP10_1         (0x2UL << SMPR1_SMP10_POS)                
#define SMPR1_SMP10_2         (0x4UL << SMPR1_SMP10_POS)                
#define SMPR1_SMP11_POS       (3U)                                         
#define SMPR1_SMP11_MSK       (0x7UL << SMPR1_SMP11_POS)                
#define SMPR1_SMP11           SMPR1_SMP11_MSK                          
#define SMPR1_SMP11_0         (0x1UL << SMPR1_SMP11_POS)                
#define SMPR1_SMP11_1         (0x2UL << SMPR1_SMP11_POS)                
#define SMPR1_SMP11_2         (0x4UL << SMPR1_SMP11_POS)                
#define SMPR1_SMP12_POS       (6U)                                         
#define SMPR1_SMP12_MSK       (0x7UL << SMPR1_SMP12_POS)                
#define SMPR1_SMP12           SMPR1_SMP12_MSK                          
#define SMPR1_SMP12_0         (0x1UL << SMPR1_SMP12_POS)                
#define SMPR1_SMP12_1         (0x2UL << SMPR1_SMP12_POS)                
#define SMPR1_SMP12_2         (0x4UL << SMPR1_SMP12_POS)                
#define SMPR1_SMP13_POS       (9U)                                         
#define SMPR1_SMP13_MSK       (0x7UL << SMPR1_SMP13_POS)                
#define SMPR1_SMP13           SMPR1_SMP13_MSK                          
#define SMPR1_SMP13_0         (0x1UL << SMPR1_SMP13_POS)                
#define SMPR1_SMP13_1         (0x2UL << SMPR1_SMP13_POS)                
#define SMPR1_SMP13_2         (0x4UL << SMPR1_SMP13_POS)                
#define SMPR1_SMP14_POS       (12U)                                        
#define SMPR1_SMP14_MSK       (0x7UL << SMPR1_SMP14_POS)                
#define SMPR1_SMP14           SMPR1_SMP14_MSK                          
#define SMPR1_SMP14_0         (0x1UL << SMPR1_SMP14_POS)                
#define SMPR1_SMP14_1         (0x2UL << SMPR1_SMP14_POS)                
#define SMPR1_SMP14_2         (0x4UL << SMPR1_SMP14_POS)                
#define SMPR1_SMP15_POS       (15U)                                        
#define SMPR1_SMP15_MSK       (0x7UL << SMPR1_SMP15_POS)                
#define SMPR1_SMP15           SMPR1_SMP15_MSK                          
#define SMPR1_SMP15_0         (0x1UL << SMPR1_SMP15_POS)                
#define SMPR1_SMP15_1         (0x2UL << SMPR1_SMP15_POS)                
#define SMPR1_SMP15_2         (0x4UL << SMPR1_SMP15_POS)                
#define SMPR1_SMP16_POS       (18U)                                        
#define SMPR1_SMP16_MSK       (0x7UL << SMPR1_SMP16_POS)                
#define SMPR1_SMP16           SMPR1_SMP16_MSK                          
#define SMPR1_SMP16_0         (0x1UL << SMPR1_SMP16_POS)                
#define SMPR1_SMP16_1         (0x2UL << SMPR1_SMP16_POS)                
#define SMPR1_SMP16_2         (0x4UL << SMPR1_SMP16_POS)                
#define SMPR1_SMP17_POS       (21U)                                        
#define SMPR1_SMP17_MSK       (0x7UL << SMPR1_SMP17_POS)                
#define SMPR1_SMP17           SMPR1_SMP17_MSK                          
#define SMPR1_SMP17_0         (0x1UL << SMPR1_SMP17_POS)                
#define SMPR1_SMP17_1         (0x2UL << SMPR1_SMP17_POS)                
#define SMPR1_SMP17_2         (0x4UL << SMPR1_SMP17_POS)                
#define SMPR1_SMP18_POS       (24U)                                        
#define SMPR1_SMP18_MSK       (0x7UL << SMPR1_SMP18_POS)                
#define SMPR1_SMP18           SMPR1_SMP18_MSK                          
#define SMPR1_SMP18_0         (0x1UL << SMPR1_SMP18_POS)                
#define SMPR1_SMP18_1         (0x2UL << SMPR1_SMP18_POS)                
#define SMPR1_SMP18_2         (0x4UL << SMPR1_SMP18_POS)                

/******************  Bit definition for SMPR2 register  *******************/
#define SMPR2_SMP0_POS        (0U)                                         
#define SMPR2_SMP0_MSK        (0x7UL << SMPR2_SMP0_POS)                 
#define SMPR2_SMP0            SMPR2_SMP0_MSK                           
#define SMPR2_SMP0_0          (0x1UL << SMPR2_SMP0_POS)                 
#define SMPR2_SMP0_1          (0x2UL << SMPR2_SMP0_POS)                 
#define SMPR2_SMP0_2          (0x4UL << SMPR2_SMP0_POS)                 
#define SMPR2_SMP1_POS        (3U)                                         
#define SMPR2_SMP1_MSK        (0x7UL << SMPR2_SMP1_POS)                 
#define SMPR2_SMP1            SMPR2_SMP1_MSK                           
#define SMPR2_SMP1_0          (0x1UL << SMPR2_SMP1_POS)                 
#define SMPR2_SMP1_1          (0x2UL << SMPR2_SMP1_POS)                 
#define SMPR2_SMP1_2          (0x4UL << SMPR2_SMP1_POS)                 
#define SMPR2_SMP2_POS        (6U)                                         
#define SMPR2_SMP2_MSK        (0x7UL << SMPR2_SMP2_POS)                 
#define SMPR2_SMP2            SMPR2_SMP2_MSK                           
#define SMPR2_SMP2_0          (0x1UL << SMPR2_SMP2_POS)                 
#define SMPR2_SMP2_1          (0x2UL << SMPR2_SMP2_POS)                 
#define SMPR2_SMP2_2          (0x4UL << SMPR2_SMP2_POS)                 
#define SMPR2_SMP3_POS        (9U)                                         
#define SMPR2_SMP3_MSK        (0x7UL << SMPR2_SMP3_POS)                 
#define SMPR2_SMP3            SMPR2_SMP3_MSK                           
#define SMPR2_SMP3_0          (0x1UL << SMPR2_SMP3_POS)                 
#define SMPR2_SMP3_1          (0x2UL << SMPR2_SMP3_POS)                 
#define SMPR2_SMP3_2          (0x4UL << SMPR2_SMP3_POS)                 
#define SMPR2_SMP4_POS        (12U)                                        
#define SMPR2_SMP4_MSK        (0x7UL << SMPR2_SMP4_POS)                 
#define SMPR2_SMP4            SMPR2_SMP4_MSK                           
#define SMPR2_SMP4_0          (0x1UL << SMPR2_SMP4_POS)                 
#define SMPR2_SMP4_1          (0x2UL << SMPR2_SMP4_POS)                 
#define SMPR2_SMP4_2          (0x4UL << SMPR2_SMP4_POS)                 
#define SMPR2_SMP5_POS        (15U)                                        
#define SMPR2_SMP5_MSK        (0x7UL << SMPR2_SMP5_POS)                 
#define SMPR2_SMP5            SMPR2_SMP5_MSK                           
#define SMPR2_SMP5_0          (0x1UL << SMPR2_SMP5_POS)                 
#define SMPR2_SMP5_1          (0x2UL << SMPR2_SMP5_POS)                 
#define SMPR2_SMP5_2          (0x4UL << SMPR2_SMP5_POS)                 
#define SMPR2_SMP6_POS        (18U)                                        
#define SMPR2_SMP6_MSK        (0x7UL << SMPR2_SMP6_POS)                 
#define SMPR2_SMP6            SMPR2_SMP6_MSK                           
#define SMPR2_SMP6_0          (0x1UL << SMPR2_SMP6_POS)                 
#define SMPR2_SMP6_1          (0x2UL << SMPR2_SMP6_POS)                 
#define SMPR2_SMP6_2          (0x4UL << SMPR2_SMP6_POS)                 
#define SMPR2_SMP7_POS        (21U)                                        
#define SMPR2_SMP7_MSK        (0x7UL << SMPR2_SMP7_POS)                 
#define SMPR2_SMP7            SMPR2_SMP7_MSK                           
#define SMPR2_SMP7_0          (0x1UL << SMPR2_SMP7_POS)                 
#define SMPR2_SMP7_1          (0x2UL << SMPR2_SMP7_POS)                 
#define SMPR2_SMP7_2          (0x4UL << SMPR2_SMP7_POS)                 
#define SMPR2_SMP8_POS        (24U)                                        
#define SMPR2_SMP8_MSK        (0x7UL << SMPR2_SMP8_POS)                 
#define SMPR2_SMP8            SMPR2_SMP8_MSK                           
#define SMPR2_SMP8_0          (0x1UL << SMPR2_SMP8_POS)                 
#define SMPR2_SMP8_1          (0x2UL << SMPR2_SMP8_POS)                 
#define SMPR2_SMP8_2          (0x4UL << SMPR2_SMP8_POS)                 
#define SMPR2_SMP9_POS        (27U)                                        
#define SMPR2_SMP9_MSK        (0x7UL << SMPR2_SMP9_POS)                 
#define SMPR2_SMP9            SMPR2_SMP9_MSK                           
#define SMPR2_SMP9_0          (0x1UL << SMPR2_SMP9_POS)                 
#define SMPR2_SMP9_1          (0x2UL << SMPR2_SMP9_POS)                 
#define SMPR2_SMP9_2          (0x4UL << SMPR2_SMP9_POS)                 

/******************  Bit definition for JOFR1 register  *******************/
#define JOFR1_JOFFSET1_POS    (0U)                                         
#define JOFR1_JOFFSET1_MSK    (0xFFFUL << JOFR1_JOFFSET1_POS)           
#define JOFR1_JOFFSET1        JOFR1_JOFFSET1_MSK                       

/******************  Bit definition for JOFR2 register  *******************/
#define JOFR2_JOFFSET2_POS    (0U)                                         
#define JOFR2_JOFFSET2_MSK    (0xFFFUL << JOFR2_JOFFSET2_POS)           
#define JOFR2_JOFFSET2        JOFR2_JOFFSET2_MSK                       

/******************  Bit definition for JOFR3 register  *******************/
#define JOFR3_JOFFSET3_POS    (0U)                                         
#define JOFR3_JOFFSET3_MSK    (0xFFFUL << JOFR3_JOFFSET3_POS)           
#define JOFR3_JOFFSET3        JOFR3_JOFFSET3_MSK                       

/******************  Bit definition for JOFR4 register  *******************/
#define JOFR4_JOFFSET4_POS    (0U)                                         
#define JOFR4_JOFFSET4_MSK    (0xFFFUL << JOFR4_JOFFSET4_POS)           
#define JOFR4_JOFFSET4        JOFR4_JOFFSET4_MSK                       

/*******************  Bit definition for HTR register  ********************/
#define HTR_HT_POS            (0U)                                         
#define HTR_HT_MSK            (0xFFFUL << HTR_HT_POS)                   
#define HTR_HT                HTR_HT_MSK                               

/*******************  Bit definition for LTR register  ********************/
#define LTR_LT_POS            (0U)                                         
#define LTR_LT_MSK            (0xFFFUL << LTR_LT_POS)                   
#define LTR_LT                LTR_LT_MSK                               

/*******************  Bit definition for SQR1 register  *******************/
#define SQR1_SQ13_POS         (0U)                                         
#define SQR1_SQ13_MSK         (0x1FUL << SQR1_SQ13_POS)                 
#define SQR1_SQ13             SQR1_SQ13_MSK                            
#define SQR1_SQ13_0           (0x01UL << SQR1_SQ13_POS)                 
#define SQR1_SQ13_1           (0x02UL << SQR1_SQ13_POS)                 
#define SQR1_SQ13_2           (0x04UL << SQR1_SQ13_POS)                 
#define SQR1_SQ13_3           (0x08UL << SQR1_SQ13_POS)                 
#define SQR1_SQ13_4           (0x10UL << SQR1_SQ13_POS)                 
#define SQR1_SQ14_POS         (5U)                                         
#define SQR1_SQ14_MSK         (0x1FUL << SQR1_SQ14_POS)                 
#define SQR1_SQ14             SQR1_SQ14_MSK                            
#define SQR1_SQ14_0           (0x01UL << SQR1_SQ14_POS)                 
#define SQR1_SQ14_1           (0x02UL << SQR1_SQ14_POS)                 
#define SQR1_SQ14_2           (0x04UL << SQR1_SQ14_POS)                 
#define SQR1_SQ14_3           (0x08UL << SQR1_SQ14_POS)                 
#define SQR1_SQ14_4           (0x10UL << SQR1_SQ14_POS)                 
#define SQR1_SQ15_POS         (10U)                                        
#define SQR1_SQ15_MSK         (0x1FUL << SQR1_SQ15_POS)                 
#define SQR1_SQ15             SQR1_SQ15_MSK                            
#define SQR1_SQ15_0           (0x01UL << SQR1_SQ15_POS)                 
#define SQR1_SQ15_1           (0x02UL << SQR1_SQ15_POS)                 
#define SQR1_SQ15_2           (0x04UL << SQR1_SQ15_POS)                 
#define SQR1_SQ15_3           (0x08UL << SQR1_SQ15_POS)                 
#define SQR1_SQ15_4           (0x10UL << SQR1_SQ15_POS)                 
#define SQR1_SQ16_POS         (15U)                                        
#define SQR1_SQ16_MSK         (0x1FUL << SQR1_SQ16_POS)                 
#define SQR1_SQ16             SQR1_SQ16_MSK                            
#define SQR1_SQ16_0           (0x01UL << SQR1_SQ16_POS)                 
#define SQR1_SQ16_1           (0x02UL << SQR1_SQ16_POS)                 
#define SQR1_SQ16_2           (0x04UL << SQR1_SQ16_POS)                 
#define SQR1_SQ16_3           (0x08UL << SQR1_SQ16_POS)                 
#define SQR1_SQ16_4           (0x10UL << SQR1_SQ16_POS)                 
#define SQR1_L_POS            (20U)                                        
#define SQR1_L_MSK            (0xFUL << SQR1_L_POS)                     
#define SQR1_L                SQR1_L_MSK                               
#define SQR1_L_0              (0x1UL << SQR1_L_POS)                     
#define SQR1_L_1              (0x2UL << SQR1_L_POS)                     
#define SQR1_L_2              (0x4UL << SQR1_L_POS)                     
#define SQR1_L_3              (0x8UL << SQR1_L_POS)                     

/*******************  Bit definition for SQR2 register  *******************/
#define SQR2_SQ7_POS          (0U)                                         
#define SQR2_SQ7_MSK          (0x1FUL << SQR2_SQ7_POS)                  
#define SQR2_SQ7              SQR2_SQ7_MSK                             
#define SQR2_SQ7_0            (0x01UL << SQR2_SQ7_POS)                  
#define SQR2_SQ7_1            (0x02UL << SQR2_SQ7_POS)                  
#define SQR2_SQ7_2            (0x04UL << SQR2_SQ7_POS)                  
#define SQR2_SQ7_3            (0x08UL << SQR2_SQ7_POS)                  
#define SQR2_SQ7_4            (0x10UL << SQR2_SQ7_POS)                  
#define SQR2_SQ8_POS          (5U)                                         
#define SQR2_SQ8_MSK          (0x1FUL << SQR2_SQ8_POS)                  
#define SQR2_SQ8              SQR2_SQ8_MSK                             
#define SQR2_SQ8_0            (0x01UL << SQR2_SQ8_POS)                  
#define SQR2_SQ8_1            (0x02UL << SQR2_SQ8_POS)                  
#define SQR2_SQ8_2            (0x04UL << SQR2_SQ8_POS)                  
#define SQR2_SQ8_3            (0x08UL << SQR2_SQ8_POS)                  
#define SQR2_SQ8_4            (0x10UL << SQR2_SQ8_POS)                  
#define SQR2_SQ9_POS          (10U)                                        
#define SQR2_SQ9_MSK          (0x1FUL << SQR2_SQ9_POS)                  
#define SQR2_SQ9              SQR2_SQ9_MSK                             
#define SQR2_SQ9_0            (0x01UL << SQR2_SQ9_POS)                  
#define SQR2_SQ9_1            (0x02UL << SQR2_SQ9_POS)                  
#define SQR2_SQ9_2            (0x04UL << SQR2_SQ9_POS)                  
#define SQR2_SQ9_3            (0x08UL << SQR2_SQ9_POS)                  
#define SQR2_SQ9_4            (0x10UL << SQR2_SQ9_POS)                  
#define SQR2_SQ10_POS         (15U)                                        
#define SQR2_SQ10_MSK         (0x1FUL << SQR2_SQ10_POS)                 
#define SQR2_SQ10             SQR2_SQ10_MSK                            
#define SQR2_SQ10_0           (0x01UL << SQR2_SQ10_POS)                 
#define SQR2_SQ10_1           (0x02UL << SQR2_SQ10_POS)                 
#define SQR2_SQ10_2           (0x04UL << SQR2_SQ10_POS)                 
#define SQR2_SQ10_3           (0x08UL << SQR2_SQ10_POS)                 
#define SQR2_SQ10_4           (0x10UL << SQR2_SQ10_POS)                 
#define SQR2_SQ11_POS         (20U)                                        
#define SQR2_SQ11_MSK         (0x1FUL << SQR2_SQ11_POS)                 
#define SQR2_SQ11             SQR2_SQ11_MSK                            
#define SQR2_SQ11_0           (0x01UL << SQR2_SQ11_POS)                 
#define SQR2_SQ11_1           (0x02UL << SQR2_SQ11_POS)                 
#define SQR2_SQ11_2           (0x04UL << SQR2_SQ11_POS)                 
#define SQR2_SQ11_3           (0x08UL << SQR2_SQ11_POS)                 
#define SQR2_SQ11_4           (0x10UL << SQR2_SQ11_POS)                 
#define SQR2_SQ12_POS         (25U)                                        
#define SQR2_SQ12_MSK         (0x1FUL << SQR2_SQ12_POS)                 
#define SQR2_SQ12             SQR2_SQ12_MSK                            
#define SQR2_SQ12_0           (0x01UL << SQR2_SQ12_POS)                 
#define SQR2_SQ12_1           (0x02UL << SQR2_SQ12_POS)                 
#define SQR2_SQ12_2           (0x04UL << SQR2_SQ12_POS)                 
#define SQR2_SQ12_3           (0x08UL << SQR2_SQ12_POS)                 
#define SQR2_SQ12_4           (0x10UL << SQR2_SQ12_POS)                 

/*******************  Bit definition for SQR3 register  *******************/
#define SQR3_SQ1_POS          (0U)                                         
#define SQR3_SQ1_MSK          (0x1FUL << SQR3_SQ1_POS)                  
#define SQR3_SQ1              SQR3_SQ1_MSK                             
#define SQR3_SQ1_0            (0x01UL << SQR3_SQ1_POS)                  
#define SQR3_SQ1_1            (0x02UL << SQR3_SQ1_POS)                  
#define SQR3_SQ1_2            (0x04UL << SQR3_SQ1_POS)                  
#define SQR3_SQ1_3            (0x08UL << SQR3_SQ1_POS)                  
#define SQR3_SQ1_4            (0x10UL << SQR3_SQ1_POS)                  
#define SQR3_SQ2_POS          (5U)                                         
#define SQR3_SQ2_MSK          (0x1FUL << SQR3_SQ2_POS)                  
#define SQR3_SQ2              SQR3_SQ2_MSK                             
#define SQR3_SQ2_0            (0x01UL << SQR3_SQ2_POS)                  
#define SQR3_SQ2_1            (0x02UL << SQR3_SQ2_POS)                  
#define SQR3_SQ2_2            (0x04UL << SQR3_SQ2_POS)                  
#define SQR3_SQ2_3            (0x08UL << SQR3_SQ2_POS)                  
#define SQR3_SQ2_4            (0x10UL << SQR3_SQ2_POS)                  
#define SQR3_SQ3_POS          (10U)                                        
#define SQR3_SQ3_MSK          (0x1FUL << SQR3_SQ3_POS)                  
#define SQR3_SQ3              SQR3_SQ3_MSK                             
#define SQR3_SQ3_0            (0x01UL << SQR3_SQ3_POS)                  
#define SQR3_SQ3_1            (0x02UL << SQR3_SQ3_POS)                  
#define SQR3_SQ3_2            (0x04UL << SQR3_SQ3_POS)                  
#define SQR3_SQ3_3            (0x08UL << SQR3_SQ3_POS)                  
#define SQR3_SQ3_4            (0x10UL << SQR3_SQ3_POS)                  
#define SQR3_SQ4_POS          (15U)                                        
#define SQR3_SQ4_MSK          (0x1FUL << SQR3_SQ4_POS)                  
#define SQR3_SQ4              SQR3_SQ4_MSK                             
#define SQR3_SQ4_0            (0x01UL << SQR3_SQ4_POS)                  
#define SQR3_SQ4_1            (0x02UL << SQR3_SQ4_POS)                  
#define SQR3_SQ4_2            (0x04UL << SQR3_SQ4_POS)                  
#define SQR3_SQ4_3            (0x08UL << SQR3_SQ4_POS)                  
#define SQR3_SQ4_4            (0x10UL << SQR3_SQ4_POS)                  
#define SQR3_SQ5_POS          (20U)                                        
#define SQR3_SQ5_MSK          (0x1FUL << SQR3_SQ5_POS)                  
#define SQR3_SQ5              SQR3_SQ5_MSK                             
#define SQR3_SQ5_0            (0x01UL << SQR3_SQ5_POS)                  
#define SQR3_SQ5_1            (0x02UL << SQR3_SQ5_POS)                  
#define SQR3_SQ5_2            (0x04UL << SQR3_SQ5_POS)                  
#define SQR3_SQ5_3            (0x08UL << SQR3_SQ5_POS)                  
#define SQR3_SQ5_4            (0x10UL << SQR3_SQ5_POS)                  
#define SQR3_SQ6_POS          (25U)                                        
#define SQR3_SQ6_MSK          (0x1FUL << SQR3_SQ6_POS)                  
#define SQR3_SQ6              SQR3_SQ6_MSK                             
#define SQR3_SQ6_0            (0x01UL << SQR3_SQ6_POS)                  
#define SQR3_SQ6_1            (0x02UL << SQR3_SQ6_POS)                  
#define SQR3_SQ6_2            (0x04UL << SQR3_SQ6_POS)                  
#define SQR3_SQ6_3            (0x08UL << SQR3_SQ6_POS)                  
#define SQR3_SQ6_4            (0x10UL << SQR3_SQ6_POS)                  

/*******************  Bit definition for JSQR register  *******************/
#define JSQR_JSQ1_POS         (0U)                                         
#define JSQR_JSQ1_MSK         (0x1FUL << JSQR_JSQ1_POS)                 
#define JSQR_JSQ1             JSQR_JSQ1_MSK                              
#define JSQR_JSQ1_0           (0x01UL << JSQR_JSQ1_POS)                 
#define JSQR_JSQ1_1           (0x02UL << JSQR_JSQ1_POS)                 
#define JSQR_JSQ1_2           (0x04UL << JSQR_JSQ1_POS)                 
#define JSQR_JSQ1_3           (0x08UL << JSQR_JSQ1_POS)                 
#define JSQR_JSQ1_4           (0x10UL << JSQR_JSQ1_POS)                 
#define JSQR_JSQ2_POS         (5U)                                         
#define JSQR_JSQ2_MSK         (0x1FUL << JSQR_JSQ2_POS)                 
#define JSQR_JSQ2             JSQR_JSQ2_MSK                            
#define JSQR_JSQ2_0           (0x01UL << JSQR_JSQ2_POS)                 
#define JSQR_JSQ2_1           (0x02UL << JSQR_JSQ2_POS)                 
#define JSQR_JSQ2_2           (0x04UL << JSQR_JSQ2_POS)                 
#define JSQR_JSQ2_3           (0x08UL << JSQR_JSQ2_POS)                 
#define JSQR_JSQ2_4           (0x10UL << JSQR_JSQ2_POS)                 
#define JSQR_JSQ3_POS         (10U)                                        
#define JSQR_JSQ3_MSK         (0x1FUL << JSQR_JSQ3_POS)                 
#define JSQR_JSQ3             JSQR_JSQ3_MSK                            
#define JSQR_JSQ3_0           (0x01UL << JSQR_JSQ3_POS)                 
#define JSQR_JSQ3_1           (0x02UL << JSQR_JSQ3_POS)                 
#define JSQR_JSQ3_2           (0x04UL << JSQR_JSQ3_POS)                 
#define JSQR_JSQ3_3           (0x08UL << JSQR_JSQ3_POS)                 
#define JSQR_JSQ3_4           (0x10UL << JSQR_JSQ3_POS)                 
#define JSQR_JSQ4_POS         (15U)                                        
#define JSQR_JSQ4_MSK         (0x1FUL << JSQR_JSQ4_POS)                 
#define JSQR_JSQ4             JSQR_JSQ4_MSK                            
#define JSQR_JSQ4_0           (0x01UL << JSQR_JSQ4_POS)                 
#define JSQR_JSQ4_1           (0x02UL << JSQR_JSQ4_POS)                 
#define JSQR_JSQ4_2           (0x04UL << JSQR_JSQ4_POS)                 
#define JSQR_JSQ4_3           (0x08UL << JSQR_JSQ4_POS)                 
#define JSQR_JSQ4_4           (0x10UL << JSQR_JSQ4_POS)                 
#define JSQR_JL_POS           (20U)                                        
#define JSQR_JL_MSK           (0x3UL << JSQR_JL_POS)                    
#define JSQR_JL               JSQR_JL_MSK                              
#define JSQR_JL_0             (0x1UL << JSQR_JL_POS)                    
#define JSQR_JL_1             (0x2UL << JSQR_JL_POS)                    

/*******************  Bit definition for JDR1 register  *******************/
#define JDR1_JDATA_POS        (0U)                                         
#define JDR1_JDATA_MSK        (0xFFFFUL << JDR1_JDATA_POS)              
#define JDR1_JDATA            JDR1_JDATA_MSK                           

/*******************  Bit definition for JDR2 register  *******************/
#define JDR2_JDATA_POS        (0U)                                         
#define JDR2_JDATA_MSK        (0xFFFFUL << JDR2_JDATA_POS)              
#define JDR2_JDATA            JDR2_JDATA_MSK                           

/*******************  Bit definition for JDR3 register  *******************/
#define JDR3_JDATA_POS        (0U)                                         
#define JDR3_JDATA_MSK        (0xFFFFUL << JDR3_JDATA_POS)              
#define JDR3_JDATA            JDR3_JDATA_MSK                           

/*******************  Bit definition for JDR4 register  *******************/
#define JDR4_JDATA_POS        (0U)                                         
#define JDR4_JDATA_MSK        (0xFFFFUL << JDR4_JDATA_POS)              
#define JDR4_JDATA            JDR4_JDATA_MSK                           

/********************  Bit definition for DR register  ********************/
#define DR_DATA_POS           (0U)                                         
#define DR_DATA_MSK           (0xFFFFUL << DR_DATA_POS)                 
#define DR_DATA               DR_DATA_MSK                              
#define DR_ADC2DATA_POS       (16U)                                        
#define DR_ADC2DATA_MSK       (0xFFFFUL << DR_ADC2DATA_POS)             
#define DR_ADC2DATA           DR_ADC2DATA_MSK                          

/*******************  Bit definition for CSR register  ********************/
#define CSR_AWD1_POS          (0U)                                         
#define CSR_AWD1_MSK          (0x1UL << CSR_AWD1_POS)                   
#define CSR_AWD1              CSR_AWD1_MSK                             
#define CSR_EOC1_POS          (1U)                                         
#define CSR_EOC1_MSK          (0x1UL << CSR_EOC1_POS)                   
#define CSR_EOC1              CSR_EOC1_MSK                             
#define CSR_JEOC1_POS         (2U)                                         
#define CSR_JEOC1_MSK         (0x1UL << CSR_JEOC1_POS)                  
#define CSR_JEOC1             CSR_JEOC1_MSK                            
#define CSR_JSTRT1_POS        (3U)                                         
#define CSR_JSTRT1_MSK        (0x1UL << CSR_JSTRT1_POS)                 
#define CSR_JSTRT1            CSR_JSTRT1_MSK                           
#define CSR_STRT1_POS         (4U)                                         
#define CSR_STRT1_MSK         (0x1UL << CSR_STRT1_POS)                  
#define CSR_STRT1             CSR_STRT1_MSK                            
#define CSR_OVR1_POS          (5U)                                         
#define CSR_OVR1_MSK          (0x1UL << CSR_OVR1_POS)                   
#define CSR_OVR1              CSR_OVR1_MSK                             

/* Legacy defines */
#define  CSR_DOVR1                        CSR_OVR1

/*******************  Bit definition for ADC CCR register  ********************/
#define CCR_MULTI_POS         (0U)                                         
#define CCR_MULTI_MSK         (0x1FUL << CCR_MULTI_POS)                 
#define CCR_MULTI             CCR_MULTI_MSK                              
#define CCR_MULTI_0           (0x01UL << CCR_MULTI_POS)                 
#define CCR_MULTI_1           (0x02UL << CCR_MULTI_POS)                 
#define CCR_MULTI_2           (0x04UL << CCR_MULTI_POS)                 
#define CCR_MULTI_3           (0x08UL << CCR_MULTI_POS)                 
#define CCR_MULTI_4           (0x10UL << CCR_MULTI_POS)                 
#define CCR_DELAY_POS         (8U)                                         
#define CCR_DELAY_MSK         (0xFUL << CCR_DELAY_POS)                  
#define CCR_DELAY             CCR_DELAY_MSK                              
#define CCR_DELAY_0           (0x1UL << CCR_DELAY_POS)                  
#define CCR_DELAY_1           (0x2UL << CCR_DELAY_POS)                  
#define CCR_DELAY_2           (0x4UL << CCR_DELAY_POS)                  
#define CCR_DELAY_3           (0x8UL << CCR_DELAY_POS)                  
#define CCR_DDS_POS           (13U)                                        
#define CCR_DDS_MSK           (0x1UL << CCR_DDS_POS)                    
#define CCR_DDS               CCR_DDS_MSK                              
#define CCR_DMA_POS           (14U)                                        
#define CCR_DMA_MSK           (0x3UL << CCR_DMA_POS)                    
#define CCR_DMA               CCR_DMA_MSK                                
#define CCR_DMA_0             (0x1UL << CCR_DMA_POS)                    
#define CCR_DMA_1             (0x2UL << CCR_DMA_POS)                    
#define CCR_ADCPRE_POS        (16U)                                        
#define CCR_ADCPRE_MSK        (0x3UL << CCR_ADCPRE_POS)                 
#define CCR_ADCPRE            CCR_ADCPRE_MSK                             
#define CCR_ADCPRE_0          (0x1UL << CCR_ADCPRE_POS)                 
#define CCR_ADCPRE_1          (0x2UL << CCR_ADCPRE_POS)                 
#define CCR_VBATE_POS         (22U)                                        
#define CCR_VBATE_MSK         (0x1UL << CCR_VBATE_POS)                  
#define CCR_VBATE             CCR_VBATE_MSK                            
#define CCR_TSVREFE_POS       (23U)                                        
#define CCR_TSVREFE_MSK       (0x1UL << CCR_TSVREFE_POS)                
#define CCR_TSVREFE           CCR_TSVREFE_MSK                          

/*******************  Bit definition for CDR register  ********************/
#define CDR_DATA1_POS         (0U)                                         
#define CDR_DATA1_MSK         (0xFFFFUL << CDR_DATA1_POS)               
#define CDR_DATA1             CDR_DATA1_MSK                            
#define CDR_DATA2_POS         (16U)                                        
#define CDR_DATA2_MSK         (0xFFFFUL << CDR_DATA2_POS)               
#define CDR_DATA2             CDR_DATA2_MSK                            

/* Legacy defines */
#define CDR_RDATA_MST         CDR_DATA1
#define CDR_RDATA_SLV         CDR_DATA2

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_ADC_REGISTER_MASKS */

