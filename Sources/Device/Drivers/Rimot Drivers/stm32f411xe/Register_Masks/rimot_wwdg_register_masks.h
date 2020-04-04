
#ifndef RIMOT_WWDG_REGISTER_MASKS
#define RIMOT_WWDG_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BIT DEFINITION FOR WWDG::CR   ********************/
#define CR_T_POS           (0U)                                           
#define CR_T_MSK           (0X7FUL << CR_T_POS)                       
#define CR_T               CR_T_MSK                                  
#define CR_T_0             (0X01UL << CR_T_POS)                       
#define CR_T_1             (0X02UL << CR_T_POS)                       
#define CR_T_2             (0X04UL << CR_T_POS)                       
#define CR_T_3             (0X08UL << CR_T_POS)                       
#define CR_T_4             (0X10UL << CR_T_POS)                       
#define CR_T_5             (0X20UL << CR_T_POS)                       
#define CR_T_6             (0X40UL << CR_T_POS)                       

#define CR_WDGA_POS        (7U)                                           
#define CR_WDGA_MSK        (0X1UL << CR_WDGA_POS)                     
#define CR_WDGA            CR_WDGA_MSK 

/*******************  BIT DEFINITION FOR WWDG::CFR   *******************/
#define CFR_W_POS          (0U)                                           
#define CFR_W_MSK          (0X7FUL << CFR_W_POS)                      
#define CFR_W              CFR_W_MSK                                 
#define CFR_W_0            (0X01UL << CFR_W_POS)                      
#define CFR_W_1            (0X02UL << CFR_W_POS)                      
#define CFR_W_2            (0X04UL << CFR_W_POS)                      
#define CFR_W_3            (0X08UL << CFR_W_POS)                      
#define CFR_W_4            (0X10UL << CFR_W_POS)                      
#define CFR_W_5            (0X20UL << CFR_W_POS)                      
#define CFR_W_6            (0X40UL << CFR_W_POS)                      

#define CFR_WDGTB_POS      (7U)                                           
#define CFR_WDGTB_MSK      (0X3UL << CFR_WDGTB_POS)                   
#define CFR_WDGTB          CFR_WDGTB_MSK                             
#define CFR_WDGTB_0        (0X1UL << CFR_WDGTB_POS)                   
#define CFR_WDGTB_1        (0X2UL << CFR_WDGTB_POS)                   

#define CFR_EWI_POS        (9U)                                           
#define CFR_EWI_MSK        (0X1UL << CFR_EWI_POS)                     
#define CFR_EWI            CFR_EWI_MSK                               

/*******************  BIT DEFINITION FOR WWDG::SR   ********************/
#define SR_EWIF_POS        (0U)                                           
#define SR_EWIF_MSK        (0X1UL << SR_EWIF_POS)                     
#define SR_EWIF            SR_EWIF_MSK  

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_WWDG_REGISTER_MASKS */