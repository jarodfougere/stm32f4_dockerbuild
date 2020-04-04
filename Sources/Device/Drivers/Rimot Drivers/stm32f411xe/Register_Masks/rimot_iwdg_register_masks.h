#ifndef RIMOT_IWDG_REGISTER_MASKS
#define RIMOT_IWDG_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  BIT DEFINITION FOR IWDG::KR   ********************/
#define KR_KEY_POS     (0U)                                               
#define KR_KEY_MSK     (0XFFFFUL << KR_KEY_POS)                       
#define KR_KEY         KR_KEY_MSK                                    

/*******************  BIT DEFINITION FOR IWDG::PR   ********************/
#define PR_PR_POS      (0U)                                               
#define PR_PR_MSK      (0X7UL << PR_PR_POS)                           
#define PR_PR          PR_PR_MSK                                     
#define PR_PR_0        (0X1UL << PR_PR_POS)                           
#define PR_PR_1        (0X2UL << PR_PR_POS)                           
#define PR_PR_2        (0X4UL << PR_PR_POS)                           

/*******************  BIT DEFINITION FOR IWDG::RLR   *******************/
#define RLR_RL_POS     (0U)                                               
#define RLR_RL_MSK     (0XFFFUL << RLR_RL_POS)                        
#define RLR_RL         RLR_RL_MSK                                    

/*******************  BIT DEFINITION FOR IWDG::SR   ********************/
#define SR_PVU_POS     (0U)                                               
#define SR_PVU_MSK     (0X1UL << SR_PVU_POS)                          
#define SR_PVU         SR_PVU_MSK                                    
#define SR_RVU_POS     (1U)                                               
#define SR_RVU_MSK     (0X1UL << SR_RVU_POS)                          
#define SR_RVU         SR_RVU_MSK                                    

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_IWDG_REGISTER_MASKS */