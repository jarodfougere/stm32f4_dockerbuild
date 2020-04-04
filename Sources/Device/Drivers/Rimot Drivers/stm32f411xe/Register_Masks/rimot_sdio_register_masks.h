#ifndef RIMOT_SDIO_REGISTER_MASKS
#define RIMOT_SDIO_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/******************  BIT DEFINITION FOR SDIO::POWER   ******************/
#define POWER_PWRCTRL_POS         (0U)                                    
#define POWER_PWRCTRL_MSK         (0X3UL << POWER_PWRCTRL_POS)        
#define POWER_PWRCTRL             POWER_PWRCTRL_MSK                  
#define POWER_PWRCTRL_0           (0X1UL << POWER_PWRCTRL_POS)        
#define POWER_PWRCTRL_1           (0X2UL << POWER_PWRCTRL_POS)        

/******************  BIT DEFINITION FOR SDIO::CLKCR   ******************/
#define CLKCR_CLKDIV_POS          (0U)                                    
#define CLKCR_CLKDIV_MSK          (0XFFUL << CLKCR_CLKDIV_POS)        
#define CLKCR_CLKDIV              CLKCR_CLKDIV_MSK                   
#define CLKCR_CLKEN_POS           (8U)                                    
#define CLKCR_CLKEN_MSK           (0X1UL << CLKCR_CLKEN_POS)          
#define CLKCR_CLKEN               CLKCR_CLKEN_MSK                    
#define CLKCR_PWRSAV_POS          (9U)                                    
#define CLKCR_PWRSAV_MSK          (0X1UL << CLKCR_PWRSAV_POS)         
#define CLKCR_PWRSAV              CLKCR_PWRSAV_MSK                   
#define CLKCR_BYPASS_POS          (10U)                                   
#define CLKCR_BYPASS_MSK          (0X1UL << CLKCR_BYPASS_POS)         
#define CLKCR_BYPASS              CLKCR_BYPASS_MSK                   

#define CLKCR_WIDBUS_POS          (11U)                                   
#define CLKCR_WIDBUS_MSK          (0X3UL << CLKCR_WIDBUS_POS)         
#define CLKCR_WIDBUS              CLKCR_WIDBUS_MSK                   
#define CLKCR_WIDBUS_0            (0X1UL << CLKCR_WIDBUS_POS)         
#define CLKCR_WIDBUS_1            (0X2UL << CLKCR_WIDBUS_POS)         

#define CLKCR_NEGEDGE_POS         (13U)                                   
#define CLKCR_NEGEDGE_MSK         (0X1UL << CLKCR_NEGEDGE_POS)        
#define CLKCR_NEGEDGE             CLKCR_NEGEDGE_MSK                  
#define CLKCR_HWFC_EN_POS         (14U)                                   
#define CLKCR_HWFC_EN_MSK         (0X1UL << CLKCR_HWFC_EN_POS)        
#define CLKCR_HWFC_EN             CLKCR_HWFC_EN_MSK                  

/*******************  BIT DEFINITION FOR SDIO::ARG   *******************/
#define ARG_CMDARG_POS            (0U)                                    
#define ARG_CMDARG_MSK            (0XFFFFFFFFUL << ARG_CMDARG_POS)    
#define ARG_CMDARG                ARG_CMDARG_MSK                     

/*******************  BIT DEFINITION FOR SDIO::CMD   *******************/
#define CMD_CMDINDEX_POS          (0U)                                    
#define CMD_CMDINDEX_MSK          (0X3FUL << CMD_CMDINDEX_POS)        
#define CMD_CMDINDEX              CMD_CMDINDEX_MSK                   

#define CMD_WAITRESP_POS          (6U)                                    
#define CMD_WAITRESP_MSK          (0X3UL << CMD_WAITRESP_POS)         
#define CMD_WAITRESP              CMD_WAITRESP_MSK                   
#define CMD_WAITRESP_0            (0X1UL << CMD_WAITRESP_POS)         
#define CMD_WAITRESP_1            (0X2UL << CMD_WAITRESP_POS)         

#define CMD_WAITINT_POS           (8U)                                    
#define CMD_WAITINT_MSK           (0X1UL << CMD_WAITINT_POS)          
#define CMD_WAITINT               CMD_WAITINT_MSK                    
#define CMD_WAITPEND_POS          (9U)                                    
#define CMD_WAITPEND_MSK          (0X1UL << CMD_WAITPEND_POS)         
#define CMD_WAITPEND              CMD_WAITPEND_MSK                   
#define CMD_CPSMEN_POS            (10U)                                   
#define CMD_CPSMEN_MSK            (0X1UL << CMD_CPSMEN_POS)           
#define CMD_CPSMEN                CMD_CPSMEN_MSK                     
#define CMD_SDIOSUSPEND_POS       (11U)                                   
#define CMD_SDIOSUSPEND_MSK       (0X1UL << CMD_SDIOSUSPEND_POS)      
#define CMD_SDIOSUSPEND           CMD_SDIOSUSPEND_MSK                
#define CMD_ENCMDCOMPL_POS        (12U)                                   
#define CMD_ENCMDCOMPL_MSK        (0X1UL << CMD_ENCMDCOMPL_POS)       
#define CMD_ENCMDCOMPL            CMD_ENCMDCOMPL_MSK                 
#define CMD_NIEN_POS              (13U)                                   
#define CMD_NIEN_MSK              (0X1UL << CMD_NIEN_POS)             
#define CMD_NIEN                  CMD_NIEN_MSK                       
#define CMD_CEATACMD_POS          (14U)                                   
#define CMD_CEATACMD_MSK          (0X1UL << CMD_CEATACMD_POS)         
#define CMD_CEATACMD              CMD_CEATACMD_MSK                   

/*****************  BIT DEFINITION FOR SDIO::RESPCMD   *****************/
#define RESPCMD_RESPCMD_POS       (0U)                                    
#define RESPCMD_RESPCMD_MSK       (0X3FUL << RESPCMD_RESPCMD_POS)     
#define RESPCMD_RESPCMD           RESPCMD_RESPCMD_MSK                

/******************  BIT DEFINITION FOR SDIO::RESP0   ******************/
#define RESP0_CARDSTATUS0_POS     (0U)                                    
#define RESP0_CARDSTATUS0_MSK     (0XFFFFFFFFUL << RESP0_CARDSTATUS0_POS) 
#define RESP0_CARDSTATUS0         RESP0_CARDSTATUS0_MSK              

/******************  BIT DEFINITION FOR SDIO::RESP1   ******************/
#define RESP1_CARDSTATUS1_POS     (0U)                                    
#define RESP1_CARDSTATUS1_MSK     (0XFFFFFFFFUL << RESP1_CARDSTATUS1_POS) 
#define RESP1_CARDSTATUS1         RESP1_CARDSTATUS1_MSK              

/******************  BIT DEFINITION FOR SDIO::RESP2   ******************/
#define RESP2_CARDSTATUS2_POS     (0U)                                    
#define RESP2_CARDSTATUS2_MSK     (0XFFFFFFFFUL << RESP2_CARDSTATUS2_POS) 
#define RESP2_CARDSTATUS2         RESP2_CARDSTATUS2_MSK              

/******************  BIT DEFINITION FOR SDIO::RESP3   ******************/
#define RESP3_CARDSTATUS3_POS     (0U)                                    
#define RESP3_CARDSTATUS3_MSK     (0XFFFFFFFFUL << RESP3_CARDSTATUS3_POS) 
#define RESP3_CARDSTATUS3         RESP3_CARDSTATUS3_MSK              

/******************  BIT DEFINITION FOR SDIO::RESP4   ******************/
#define RESP4_CARDSTATUS4_POS     (0U)                                    
#define RESP4_CARDSTATUS4_MSK     (0XFFFFFFFFUL << RESP4_CARDSTATUS4_POS) 
#define RESP4_CARDSTATUS4         RESP4_CARDSTATUS4_MSK              

/******************  BIT DEFINITION FOR SDIO::DTIMER   *****************/
#define DTIMER_DATATIME_POS       (0U)                                    
#define DTIMER_DATATIME_MSK       (0XFFFFFFFFUL << DTIMER_DATATIME_POS) 
#define DTIMER_DATATIME           DTIMER_DATATIME_MSK                

/******************  BIT DEFINITION FOR SDIO::DLEN   *******************/
#define DLEN_DATALENGTH_POS       (0U)                                    
#define DLEN_DATALENGTH_MSK       (0X1FFFFFFUL << DLEN_DATALENGTH_POS) 
#define DLEN_DATALENGTH           DLEN_DATALENGTH_MSK                

/******************  BIT DEFINITION FOR SDIO::DCTRL   ******************/
#define DCTRL_DTEN_POS            (0U)                                    
#define DCTRL_DTEN_MSK            (0X1UL << DCTRL_DTEN_POS)           
#define DCTRL_DTEN                DCTRL_DTEN_MSK                     
#define DCTRL_DTDIR_POS           (1U)                                    
#define DCTRL_DTDIR_MSK           (0X1UL << DCTRL_DTDIR_POS)          
#define DCTRL_DTDIR               DCTRL_DTDIR_MSK                    
#define DCTRL_DTMODE_POS          (2U)                                    
#define DCTRL_DTMODE_MSK          (0X1UL << DCTRL_DTMODE_POS)         
#define DCTRL_DTMODE              DCTRL_DTMODE_MSK                   
#define DCTRL_DMAEN_POS           (3U)                                    
#define DCTRL_DMAEN_MSK           (0X1UL << DCTRL_DMAEN_POS)          
#define DCTRL_DMAEN               DCTRL_DMAEN_MSK                    

#define DCTRL_DBLOCKSIZE_POS      (4U)                                    
#define DCTRL_DBLOCKSIZE_MSK      (0XFUL << DCTRL_DBLOCKSIZE_POS)     
#define DCTRL_DBLOCKSIZE          DCTRL_DBLOCKSIZE_MSK               
#define DCTRL_DBLOCKSIZE_0        (0X1UL << DCTRL_DBLOCKSIZE_POS)     
#define DCTRL_DBLOCKSIZE_1        (0X2UL << DCTRL_DBLOCKSIZE_POS)     
#define DCTRL_DBLOCKSIZE_2        (0X4UL << DCTRL_DBLOCKSIZE_POS)     
#define DCTRL_DBLOCKSIZE_3        (0X8UL << DCTRL_DBLOCKSIZE_POS)     

#define DCTRL_RWSTART_POS         (8U)                                    
#define DCTRL_RWSTART_MSK         (0X1UL << DCTRL_RWSTART_POS)        
#define DCTRL_RWSTART             DCTRL_RWSTART_MSK                  
#define DCTRL_RWSTOP_POS          (9U)                                    
#define DCTRL_RWSTOP_MSK          (0X1UL << DCTRL_RWSTOP_POS)         
#define DCTRL_RWSTOP              DCTRL_RWSTOP_MSK                   
#define DCTRL_RWMOD_POS           (10U)                                   
#define DCTRL_RWMOD_MSK           (0X1UL << DCTRL_RWMOD_POS)          
#define DCTRL_RWMOD               DCTRL_RWMOD_MSK                    
#define DCTRL_SDIOEN_POS          (11U)                                   
#define DCTRL_SDIOEN_MSK          (0X1UL << DCTRL_SDIOEN_POS)         
#define DCTRL_SDIOEN              DCTRL_SDIOEN_MSK                   

/******************  BIT DEFINITION FOR SDIO::DCOUNT   *****************/
#define DCOUNT_DATACOUNT_POS      (0U)                                    
#define DCOUNT_DATACOUNT_MSK      (0X1FFFFFFUL << DCOUNT_DATACOUNT_POS) 
#define DCOUNT_DATACOUNT          DCOUNT_DATACOUNT_MSK               

/******************  BIT DEFINITION FOR SDIO::STA   ********************/
#define STA_CCRCFAIL_POS          (0U)                                    
#define STA_CCRCFAIL_MSK          (0X1UL << STA_CCRCFAIL_POS)         
#define STA_CCRCFAIL              STA_CCRCFAIL_MSK                   
#define STA_DCRCFAIL_POS          (1U)                                    
#define STA_DCRCFAIL_MSK          (0X1UL << STA_DCRCFAIL_POS)         
#define STA_DCRCFAIL              STA_DCRCFAIL_MSK                   
#define STA_CTIMEOUT_POS          (2U)                                    
#define STA_CTIMEOUT_MSK          (0X1UL << STA_CTIMEOUT_POS)         
#define STA_CTIMEOUT              STA_CTIMEOUT_MSK                   
#define STA_DTIMEOUT_POS          (3U)                                    
#define STA_DTIMEOUT_MSK          (0X1UL << STA_DTIMEOUT_POS)         
#define STA_DTIMEOUT              STA_DTIMEOUT_MSK                   
#define STA_TXUNDERR_POS          (4U)                                    
#define STA_TXUNDERR_MSK          (0X1UL << STA_TXUNDERR_POS)         
#define STA_TXUNDERR              STA_TXUNDERR_MSK                   
#define STA_RXOVERR_POS           (5U)                                    
#define STA_RXOVERR_MSK           (0X1UL << STA_RXOVERR_POS)          
#define STA_RXOVERR               STA_RXOVERR_MSK                    
#define STA_CMDREND_POS           (6U)                                    
#define STA_CMDREND_MSK           (0X1UL << STA_CMDREND_POS)          
#define STA_CMDREND               STA_CMDREND_MSK                    
#define STA_CMDSENT_POS           (7U)                                    
#define STA_CMDSENT_MSK           (0X1UL << STA_CMDSENT_POS)          
#define STA_CMDSENT               STA_CMDSENT_MSK                    
#define STA_DATAEND_POS           (8U)                                    
#define STA_DATAEND_MSK           (0X1UL << STA_DATAEND_POS)          
#define STA_DATAEND               STA_DATAEND_MSK                    
#define STA_STBITERR_POS          (9U)                                    
#define STA_STBITERR_MSK          (0X1UL << STA_STBITERR_POS)         
#define STA_STBITERR              STA_STBITERR_MSK                   
#define STA_DBCKEND_POS           (10U)                                   
#define STA_DBCKEND_MSK           (0X1UL << STA_DBCKEND_POS)          
#define STA_DBCKEND               STA_DBCKEND_MSK                    
#define STA_CMDACT_POS            (11U)                                   
#define STA_CMDACT_MSK            (0X1UL << STA_CMDACT_POS)           
#define STA_CMDACT                STA_CMDACT_MSK                     
#define STA_TXACT_POS             (12U)                                   
#define STA_TXACT_MSK             (0X1UL << STA_TXACT_POS)            
#define STA_TXACT                 STA_TXACT_MSK                      
#define STA_RXACT_POS             (13U)                                   
#define STA_RXACT_MSK             (0X1UL << STA_RXACT_POS)            
#define STA_RXACT                 STA_RXACT_MSK                      
#define STA_TXFIFOHE_POS          (14U)                                   
#define STA_TXFIFOHE_MSK          (0X1UL << STA_TXFIFOHE_POS)         
#define STA_TXFIFOHE              STA_TXFIFOHE_MSK                   
#define STA_RXFIFOHF_POS          (15U)                                   
#define STA_RXFIFOHF_MSK          (0X1UL << STA_RXFIFOHF_POS)         
#define STA_RXFIFOHF              STA_RXFIFOHF_MSK                   
#define STA_TXFIFOF_POS           (16U)                                   
#define STA_TXFIFOF_MSK           (0X1UL << STA_TXFIFOF_POS)          
#define STA_TXFIFOF               STA_TXFIFOF_MSK                    
#define STA_RXFIFOF_POS           (17U)                                   
#define STA_RXFIFOF_MSK           (0X1UL << STA_RXFIFOF_POS)          
#define STA_RXFIFOF               STA_RXFIFOF_MSK                    
#define STA_TXFIFOE_POS           (18U)                                   
#define STA_TXFIFOE_MSK           (0X1UL << STA_TXFIFOE_POS)          
#define STA_TXFIFOE               STA_TXFIFOE_MSK                    
#define STA_RXFIFOE_POS           (19U)                                   
#define STA_RXFIFOE_MSK           (0X1UL << STA_RXFIFOE_POS)          
#define STA_RXFIFOE               STA_RXFIFOE_MSK                    
#define STA_TXDAVL_POS            (20U)                                   
#define STA_TXDAVL_MSK            (0X1UL << STA_TXDAVL_POS)           
#define STA_TXDAVL                STA_TXDAVL_MSK                     
#define STA_RXDAVL_POS            (21U)                                   
#define STA_RXDAVL_MSK            (0X1UL << STA_RXDAVL_POS)           
#define STA_RXDAVL                STA_RXDAVL_MSK                     
#define STA_SDIOIT_POS            (22U)                                   
#define STA_SDIOIT_MSK            (0X1UL << STA_SDIOIT_POS)           
#define STA_SDIOIT                STA_SDIOIT_MSK                     
#define STA_CEATAEND_POS          (23U)                                   
#define STA_CEATAEND_MSK          (0X1UL << STA_CEATAEND_POS)         
#define STA_CEATAEND              STA_CEATAEND_MSK                   

/*******************  BIT DEFINITION FOR SDIO::ICR   *******************/
#define ICR_CCRCFAILC_POS         (0U)                                    
#define ICR_CCRCFAILC_MSK         (0X1UL << ICR_CCRCFAILC_POS)        
#define ICR_CCRCFAILC             ICR_CCRCFAILC_MSK                  
#define ICR_DCRCFAILC_POS         (1U)                                    
#define ICR_DCRCFAILC_MSK         (0X1UL << ICR_DCRCFAILC_POS)        
#define ICR_DCRCFAILC             ICR_DCRCFAILC_MSK                  
#define ICR_CTIMEOUTC_POS         (2U)                                    
#define ICR_CTIMEOUTC_MSK         (0X1UL << ICR_CTIMEOUTC_POS)        
#define ICR_CTIMEOUTC             ICR_CTIMEOUTC_MSK                  
#define ICR_DTIMEOUTC_POS         (3U)                                    
#define ICR_DTIMEOUTC_MSK         (0X1UL << ICR_DTIMEOUTC_POS)        
#define ICR_DTIMEOUTC             ICR_DTIMEOUTC_MSK                  
#define ICR_TXUNDERRC_POS         (4U)                                    
#define ICR_TXUNDERRC_MSK         (0X1UL << ICR_TXUNDERRC_POS)        
#define ICR_TXUNDERRC             ICR_TXUNDERRC_MSK                  
#define ICR_RXOVERRC_POS          (5U)                                    
#define ICR_RXOVERRC_MSK          (0X1UL << ICR_RXOVERRC_POS)         
#define ICR_RXOVERRC              ICR_RXOVERRC_MSK                   
#define ICR_CMDRENDC_POS          (6U)                                    
#define ICR_CMDRENDC_MSK          (0X1UL << ICR_CMDRENDC_POS)         
#define ICR_CMDRENDC              ICR_CMDRENDC_MSK                   
#define ICR_CMDSENTC_POS          (7U)                                    
#define ICR_CMDSENTC_MSK          (0X1UL << ICR_CMDSENTC_POS)         
#define ICR_CMDSENTC              ICR_CMDSENTC_MSK                   
#define ICR_DATAENDC_POS          (8U)                                    
#define ICR_DATAENDC_MSK          (0X1UL << ICR_DATAENDC_POS)         
#define ICR_DATAENDC              ICR_DATAENDC_MSK                   
#define ICR_STBITERRC_POS         (9U)                                    
#define ICR_STBITERRC_MSK         (0X1UL << ICR_STBITERRC_POS)        
#define ICR_STBITERRC             ICR_STBITERRC_MSK                  
#define ICR_DBCKENDC_POS          (10U)                                   
#define ICR_DBCKENDC_MSK          (0X1UL << ICR_DBCKENDC_POS)         
#define ICR_DBCKENDC              ICR_DBCKENDC_MSK                   
#define ICR_SDIOITC_POS           (22U)                                   
#define ICR_SDIOITC_MSK           (0X1UL << ICR_SDIOITC_POS)          
#define ICR_SDIOITC               ICR_SDIOITC_MSK                    
#define ICR_CEATAENDC_POS         (23U)                                   
#define ICR_CEATAENDC_MSK         (0X1UL << ICR_CEATAENDC_POS)        
#define ICR_CEATAENDC             ICR_CEATAENDC_MSK                  

/******************  BIT DEFINITION FOR SDIO::MASK   *******************/
#define MASK_CCRCFAILIE_POS       (0U)                                    
#define MASK_CCRCFAILIE_MSK       (0X1UL << MASK_CCRCFAILIE_POS)      
#define MASK_CCRCFAILIE           MASK_CCRCFAILIE_MSK                
#define MASK_DCRCFAILIE_POS       (1U)                                    
#define MASK_DCRCFAILIE_MSK       (0X1UL << MASK_DCRCFAILIE_POS)      
#define MASK_DCRCFAILIE           MASK_DCRCFAILIE_MSK                
#define MASK_CTIMEOUTIE_POS       (2U)                                    
#define MASK_CTIMEOUTIE_MSK       (0X1UL << MASK_CTIMEOUTIE_POS)      
#define MASK_CTIMEOUTIE           MASK_CTIMEOUTIE_MSK                
#define MASK_DTIMEOUTIE_POS       (3U)                                    
#define MASK_DTIMEOUTIE_MSK       (0X1UL << MASK_DTIMEOUTIE_POS)      
#define MASK_DTIMEOUTIE           MASK_DTIMEOUTIE_MSK                
#define MASK_TXUNDERRIE_POS       (4U)                                    
#define MASK_TXUNDERRIE_MSK       (0X1UL << MASK_TXUNDERRIE_POS)      
#define MASK_TXUNDERRIE           MASK_TXUNDERRIE_MSK                
#define MASK_RXOVERRIE_POS        (5U)                                    
#define MASK_RXOVERRIE_MSK        (0X1UL << MASK_RXOVERRIE_POS)       
#define MASK_RXOVERRIE            MASK_RXOVERRIE_MSK                 
#define MASK_CMDRENDIE_POS        (6U)                                    
#define MASK_CMDRENDIE_MSK        (0X1UL << MASK_CMDRENDIE_POS)       
#define MASK_CMDRENDIE            MASK_CMDRENDIE_MSK                 
#define MASK_CMDSENTIE_POS        (7U)                                    
#define MASK_CMDSENTIE_MSK        (0X1UL << MASK_CMDSENTIE_POS)       
#define MASK_CMDSENTIE            MASK_CMDSENTIE_MSK                 
#define MASK_DATAENDIE_POS        (8U)                                    
#define MASK_DATAENDIE_MSK        (0X1UL << MASK_DATAENDIE_POS)       
#define MASK_DATAENDIE            MASK_DATAENDIE_MSK                 
#define MASK_STBITERRIE_POS       (9U)                                    
#define MASK_STBITERRIE_MSK       (0X1UL << MASK_STBITERRIE_POS)      
#define MASK_STBITERRIE           MASK_STBITERRIE_MSK                
#define MASK_DBCKENDIE_POS        (10U)                                   
#define MASK_DBCKENDIE_MSK        (0X1UL << MASK_DBCKENDIE_POS)       
#define MASK_DBCKENDIE            MASK_DBCKENDIE_MSK                 
#define MASK_CMDACTIE_POS         (11U)                                   
#define MASK_CMDACTIE_MSK         (0X1UL << MASK_CMDACTIE_POS)        
#define MASK_CMDACTIE             MASK_CMDACTIE_MSK                  
#define MASK_TXACTIE_POS          (12U)                                   
#define MASK_TXACTIE_MSK          (0X1UL << MASK_TXACTIE_POS)         
#define MASK_TXACTIE              MASK_TXACTIE_MSK                   
#define MASK_RXACTIE_POS          (13U)                                   
#define MASK_RXACTIE_MSK          (0X1UL << MASK_RXACTIE_POS)         
#define MASK_RXACTIE              MASK_RXACTIE_MSK                   
#define MASK_TXFIFOHEIE_POS       (14U)                                   
#define MASK_TXFIFOHEIE_MSK       (0X1UL << MASK_TXFIFOHEIE_POS)      
#define MASK_TXFIFOHEIE           MASK_TXFIFOHEIE_MSK                
#define MASK_RXFIFOHFIE_POS       (15U)                                   
#define MASK_RXFIFOHFIE_MSK       (0X1UL << MASK_RXFIFOHFIE_POS)      
#define MASK_RXFIFOHFIE           MASK_RXFIFOHFIE_MSK                
#define MASK_TXFIFOFIE_POS        (16U)                                   
#define MASK_TXFIFOFIE_MSK        (0X1UL << MASK_TXFIFOFIE_POS)       
#define MASK_TXFIFOFIE            MASK_TXFIFOFIE_MSK                 
#define MASK_RXFIFOFIE_POS        (17U)                                   
#define MASK_RXFIFOFIE_MSK        (0X1UL << MASK_RXFIFOFIE_POS)       
#define MASK_RXFIFOFIE            MASK_RXFIFOFIE_MSK                 
#define MASK_TXFIFOEIE_POS        (18U)                                   
#define MASK_TXFIFOEIE_MSK        (0X1UL << MASK_TXFIFOEIE_POS)       
#define MASK_TXFIFOEIE            MASK_TXFIFOEIE_MSK                 
#define MASK_RXFIFOEIE_POS        (19U)                                   
#define MASK_RXFIFOEIE_MSK        (0X1UL << MASK_RXFIFOEIE_POS)       
#define MASK_RXFIFOEIE            MASK_RXFIFOEIE_MSK                 
#define MASK_TXDAVLIE_POS         (20U)                                   
#define MASK_TXDAVLIE_MSK         (0X1UL << MASK_TXDAVLIE_POS)        
#define MASK_TXDAVLIE             MASK_TXDAVLIE_MSK                  
#define MASK_RXDAVLIE_POS         (21U)                                   
#define MASK_RXDAVLIE_MSK         (0X1UL << MASK_RXDAVLIE_POS)        
#define MASK_RXDAVLIE             MASK_RXDAVLIE_MSK                  
#define MASK_SDIOITIE_POS         (22U)                                   
#define MASK_SDIOITIE_MSK         (0X1UL << MASK_SDIOITIE_POS)        
#define MASK_SDIOITIE             MASK_SDIOITIE_MSK                  
#define MASK_CEATAENDIE_POS       (23U)                                   
#define MASK_CEATAENDIE_MSK       (0X1UL << MASK_CEATAENDIE_POS)      
#define MASK_CEATAENDIE           MASK_CEATAENDIE_MSK                

/*****************  BIT DEFINITION FOR SDIO::FIFOCNT   *****************/
#define FIFOCNT_FIFOCOUNT_POS     (0U)                                    
#define FIFOCNT_FIFOCOUNT_MSK     (0XFFFFFFUL << FIFOCNT_FIFOCOUNT_POS) 
#define FIFOCNT_FIFOCOUNT         FIFOCNT_FIFOCOUNT_MSK              

/******************  BIT DEFINITION FOR SDIO::FIFO   *******************/
#define FIFO_FIFODATA_POS         (0U)                                    
#define FIFO_FIFODATA_MSK         (0XFFFFFFFFUL << FIFO_FIFODATA_POS) 
#define FIFO_FIFODATA             FIFO_FIFODATA_MSK                  

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_SDIO_REGISTER_MASKS */