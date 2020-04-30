#ifndef RIMOT_CRC_REGISTER_MASKS
#define RIMOT_CRC_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/*******************  Bit definition for CRC::DR register  ******************/
#define DR_DR_POS       (0U)                                               
#define DR_DR_MSK       (0xFFFFFFFFUL << DR_DR_POS)                     
#define DR_DR           DR_DR_MSK                                      

/*****************  Bit definition for CRC::IDR register  ********************/
#define IDR_IDR_POS     (0U)                                               
#define IDR_IDR_MSK     (0xFFUL << IDR_IDR_POS)                         
#define IDR_IDR         IDR_IDR_MSK                                    

/********************  Bit definition for CRC::CR register  ******************/
#define CR_RESET_POS    (0U)                                               
#define CR_RESET_MSK    (0x1UL << CR_RESET_POS)                         
#define CR_RESET        CR_RESET_MSK        

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_CRC_REGISTER_MASKS */

