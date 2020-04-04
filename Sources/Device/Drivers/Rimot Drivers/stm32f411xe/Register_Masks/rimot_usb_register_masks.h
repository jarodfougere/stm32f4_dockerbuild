#ifndef RIMOT_USB_REGISTER_MASKS
#define RIMOT_USB_REGISTER_MASKS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

/********************  BIT DEFINITION FOR USB_OTG::GOTGCTL   ***********/
#define GOTGCTL_SRQSCS_POS               (0U)                          
#define GOTGCTL_SRQSCS_MSK               (0X1UL << GOTGCTL_SRQSCS_POS) 
#define GOTGCTL_SRQSCS                   GOTGCTL_SRQSCS_MSK    
#define GOTGCTL_SRQ_POS                  (1U)                          
#define GOTGCTL_SRQ_MSK                  (0X1UL << GOTGCTL_SRQ_POS) 
#define GOTGCTL_SRQ                      GOTGCTL_SRQ_MSK       
#define GOTGCTL_HNGSCS_POS               (8U)                          
#define GOTGCTL_HNGSCS_MSK               (0X1UL << GOTGCTL_HNGSCS_POS) 
#define GOTGCTL_HNGSCS                   GOTGCTL_HNGSCS_MSK    
#define GOTGCTL_HNPRQ_POS                (9U)                          
#define GOTGCTL_HNPRQ_MSK                (0X1UL << GOTGCTL_HNPRQ_POS) 
#define GOTGCTL_HNPRQ                    GOTGCTL_HNPRQ_MSK     
#define GOTGCTL_HSHNPEN_POS              (10U)                         
#define GOTGCTL_HSHNPEN_MSK              (0X1UL << GOTGCTL_HSHNPEN_POS) 
#define GOTGCTL_HSHNPEN                  GOTGCTL_HSHNPEN_MSK   
#define GOTGCTL_DHNPEN_POS               (11U)                         
#define GOTGCTL_DHNPEN_MSK               (0X1UL << GOTGCTL_DHNPEN_POS) 
#define GOTGCTL_DHNPEN                   GOTGCTL_DHNPEN_MSK    
#define GOTGCTL_CIDSTS_POS               (16U)                         
#define GOTGCTL_CIDSTS_MSK               (0X1UL << GOTGCTL_CIDSTS_POS) 
#define GOTGCTL_CIDSTS                   GOTGCTL_CIDSTS_MSK    
#define GOTGCTL_DBCT_POS                 (17U)                         
#define GOTGCTL_DBCT_MSK                 (0X1UL << GOTGCTL_DBCT_POS) 
#define GOTGCTL_DBCT                     GOTGCTL_DBCT_MSK      
#define GOTGCTL_ASVLD_POS                (18U)                         
#define GOTGCTL_ASVLD_MSK                (0X1UL << GOTGCTL_ASVLD_POS) 
#define GOTGCTL_ASVLD                    GOTGCTL_ASVLD_MSK     
#define GOTGCTL_BSVLD_POS                (19U)                         
#define GOTGCTL_BSVLD_MSK                (0X1UL << GOTGCTL_BSVLD_POS) 
#define GOTGCTL_BSVLD                    GOTGCTL_BSVLD_MSK     

/********************  BIT DEFINITION FORHCFG   ********************/

#define HCFG_FSLSPCS_POS                 (0U)                          
#define HCFG_FSLSPCS_MSK                 (0X3UL << HCFG_FSLSPCS_POS) 
#define HCFG_FSLSPCS                     HCFG_FSLSPCS_MSK      
#define HCFG_FSLSPCS_0                   (0X1UL << HCFG_FSLSPCS_POS) 
#define HCFG_FSLSPCS_1                   (0X2UL << HCFG_FSLSPCS_POS) 
#define HCFG_FSLSS_POS                   (2U)                          
#define HCFG_FSLSS_MSK                   (0X1UL << HCFG_FSLSS_POS) 
#define HCFG_FSLSS                       HCFG_FSLSS_MSK        

/********************  BIT DEFINITION FOR USB_OTG::DCFG   ********************/

#define DCFG_DSPD_POS                    (0U)                          
#define DCFG_DSPD_MSK                    (0X3UL << DCFG_DSPD_POS) 
#define DCFG_DSPD                        DCFG_DSPD_MSK         
#define DCFG_DSPD_0                      (0X1UL << DCFG_DSPD_POS) 
#define DCFG_DSPD_1                      (0X2UL << DCFG_DSPD_POS) 
#define DCFG_NZLSOHSK_POS                (2U)                          
#define DCFG_NZLSOHSK_MSK                (0X1UL << DCFG_NZLSOHSK_POS) 
#define DCFG_NZLSOHSK                    DCFG_NZLSOHSK_MSK     

#define DCFG_DAD_POS                     (4U)                          
#define DCFG_DAD_MSK                     (0X7FUL << DCFG_DAD_POS) 
#define DCFG_DAD                         DCFG_DAD_MSK          
#define DCFG_DAD_0                       (0X01UL << DCFG_DAD_POS) 
#define DCFG_DAD_1                       (0X02UL << DCFG_DAD_POS) 
#define DCFG_DAD_2                       (0X04UL << DCFG_DAD_POS) 
#define DCFG_DAD_3                       (0X08UL << DCFG_DAD_POS) 
#define DCFG_DAD_4                       (0X10UL << DCFG_DAD_POS) 
#define DCFG_DAD_5                       (0X20UL << DCFG_DAD_POS) 
#define DCFG_DAD_6                       (0X40UL << DCFG_DAD_POS) 

#define DCFG_PFIVL_POS                   (11U)                         
#define DCFG_PFIVL_MSK                   (0X3UL << DCFG_PFIVL_POS) 
#define DCFG_PFIVL                       DCFG_PFIVL_MSK        
#define DCFG_PFIVL_0                     (0X1UL << DCFG_PFIVL_POS) 
#define DCFG_PFIVL_1                     (0X2UL << DCFG_PFIVL_POS) 

#define DCFG_XCVRDLY_POS                 (14U)                         
#define DCFG_XCVRDLY_MSK                 (0X1UL << DCFG_XCVRDLY_POS) 
#define DCFG_XCVRDLY                     DCFG_XCVRDLY_MSK        

#define DCFG_ERRATIM_POS                 (15U)                         
#define DCFG_ERRATIM_MSK                 (0X1UL << DCFG_ERRATIM_POS) 
#define DCFG_ERRATIM                     DCFG_ERRATIM_MSK        

#define DCFG_PERSCHIVL_POS               (24U)                         
#define DCFG_PERSCHIVL_MSK               (0X3UL << DCFG_PERSCHIVL_POS) 
#define DCFG_PERSCHIVL                   DCFG_PERSCHIVL_MSK    
#define DCFG_PERSCHIVL_0                 (0X1UL << DCFG_PERSCHIVL_POS) 
#define DCFG_PERSCHIVL_1                 (0X2UL << DCFG_PERSCHIVL_POS) 

/********************  BIT DEFINITION FOR USB_OTG::PCGCR   ********************/
#define PCGCR_STPPCLK_POS                (0U)                          
#define PCGCR_STPPCLK_MSK                (0X1UL << PCGCR_STPPCLK_POS) 
#define PCGCR_STPPCLK                    PCGCR_STPPCLK_MSK     
#define PCGCR_GATEHCLK_POS               (1U)                          
#define PCGCR_GATEHCLK_MSK               (0X1UL << PCGCR_GATEHCLK_POS) 
#define PCGCR_GATEHCLK                   PCGCR_GATEHCLK_MSK    
#define PCGCR_PHYSUSP_POS                (4U)                          
#define PCGCR_PHYSUSP_MSK                (0X1UL << PCGCR_PHYSUSP_POS) 
#define PCGCR_PHYSUSP                    PCGCR_PHYSUSP_MSK     

/*********  BIT DEFINITION FOR USB_OTG::GOTGINT   ********************/
#define GOTGINT_SEDET_POS                (2U)                          
#define GOTGINT_SEDET_MSK                (0X1UL << GOTGINT_SEDET_POS) 
#define GOTGINT_SEDET                    GOTGINT_SEDET_MSK     
#define GOTGINT_SRSSCHG_POS              (8U)                          
#define GOTGINT_SRSSCHG_MSK              (0X1UL << GOTGINT_SRSSCHG_POS) 
#define GOTGINT_SRSSCHG                  GOTGINT_SRSSCHG_MSK   
#define GOTGINT_HNSSCHG_POS              (9U)                          
#define GOTGINT_HNSSCHG_MSK              (0X1UL << GOTGINT_HNSSCHG_POS) 
#define GOTGINT_HNSSCHG                  GOTGINT_HNSSCHG_MSK   
#define GOTGINT_HNGDET_POS               (17U)                         
#define GOTGINT_HNGDET_MSK               (0X1UL << GOTGINT_HNGDET_POS) 
#define GOTGINT_HNGDET                   GOTGINT_HNGDET_MSK    
#define GOTGINT_ADTOCHG_POS              (18U)                         
#define GOTGINT_ADTOCHG_MSK              (0X1UL << GOTGINT_ADTOCHG_POS) 
#define GOTGINT_ADTOCHG                  GOTGINT_ADTOCHG_MSK   
#define GOTGINT_DBCDNE_POS               (19U)                         
#define GOTGINT_DBCDNE_MSK               (0X1UL << GOTGINT_DBCDNE_POS) 
#define GOTGINT_DBCDNE                   GOTGINT_DBCDNE_MSK    

/********************  BIT DEFINITION FOR USB_OTG::DCTL   ********************/
#define DCTL_RWUSIG_POS                  (0U)                          
#define DCTL_RWUSIG_MSK                  (0X1UL << DCTL_RWUSIG_POS) 
#define DCTL_RWUSIG                      DCTL_RWUSIG_MSK       
#define DCTL_SDIS_POS                    (1U)                          
#define DCTL_SDIS_MSK                    (0X1UL << DCTL_SDIS_POS) 
#define DCTL_SDIS                        DCTL_SDIS_MSK         
#define DCTL_GINSTS_POS                  (2U)                          
#define DCTL_GINSTS_MSK                  (0X1UL << DCTL_GINSTS_POS) 
#define DCTL_GINSTS                      DCTL_GINSTS_MSK       
#define DCTL_GONSTS_POS                  (3U)                          
#define DCTL_GONSTS_MSK                  (0X1UL << DCTL_GONSTS_POS) 
#define DCTL_GONSTS                      DCTL_GONSTS_MSK       

#define DCTL_TCTL_POS                    (4U)                          
#define DCTL_TCTL_MSK                    (0X7UL << DCTL_TCTL_POS) 
#define DCTL_TCTL                        DCTL_TCTL_MSK         
#define DCTL_TCTL_0                      (0X1UL << DCTL_TCTL_POS) 
#define DCTL_TCTL_1                      (0X2UL << DCTL_TCTL_POS) 
#define DCTL_TCTL_2                      (0X4UL << DCTL_TCTL_POS) 
#define DCTL_SGINAK_POS                  (7U)                          
#define DCTL_SGINAK_MSK                  (0X1UL << DCTL_SGINAK_POS) 
#define DCTL_SGINAK                      DCTL_SGINAK_MSK       
#define DCTL_CGINAK_POS                  (8U)                          
#define DCTL_CGINAK_MSK                  (0X1UL << DCTL_CGINAK_POS) 
#define DCTL_CGINAK                      DCTL_CGINAK_MSK       
#define DCTL_SGONAK_POS                  (9U)                          
#define DCTL_SGONAK_MSK                  (0X1UL << DCTL_SGONAK_POS) 
#define DCTL_SGONAK                      DCTL_SGONAK_MSK       
#define DCTL_CGONAK_POS                  (10U)                         
#define DCTL_CGONAK_MSK                  (0X1UL << DCTL_CGONAK_POS) 
#define DCTL_CGONAK                      DCTL_CGONAK_MSK       
#define DCTL_POPRGDNE_POS                (11U)                         
#define DCTL_POPRGDNE_MSK                (0X1UL << DCTL_POPRGDNE_POS) 
#define DCTL_POPRGDNE                    DCTL_POPRGDNE_MSK     

/********************  BIT DEFINITION FOR USB_OTG::HFIR   ********************/
#define HFIR_FRIVL_POS                   (0U)                          
#define HFIR_FRIVL_MSK                   (0XFFFFUL << HFIR_FRIVL_POS) 
#define HFIR_FRIVL                       HFIR_FRIVL_MSK        

/********************  BIT DEFINITION FOR USB_OTG::HFNUM   ********************/
#define HFNUM_FRNUM_POS                  (0U)                          
#define HFNUM_FRNUM_MSK                  (0XFFFFUL << HFNUM_FRNUM_POS) 
#define HFNUM_FRNUM                      HFNUM_FRNUM_MSK       
#define HFNUM_FTREM_POS                  (16U)                         
#define HFNUM_FTREM_MSK                  (0XFFFFUL << HFNUM_FTREM_POS) 
#define HFNUM_FTREM                      HFNUM_FTREM_MSK       

/********************  BIT DEFINITION FOR USB_OTG::DSTS   ********************/
#define DSTS_SUSPSTS_POS                 (0U)                          
#define DSTS_SUSPSTS_MSK                 (0X1UL << DSTS_SUSPSTS_POS) 
#define DSTS_SUSPSTS                     DSTS_SUSPSTS_MSK      

#define DSTS_ENUMSPD_POS                 (1U)                          
#define DSTS_ENUMSPD_MSK                 (0X3UL << DSTS_ENUMSPD_POS) 
#define DSTS_ENUMSPD                     DSTS_ENUMSPD_MSK      
#define DSTS_ENUMSPD_0                   (0X1UL << DSTS_ENUMSPD_POS) 
#define DSTS_ENUMSPD_1                   (0X2UL << DSTS_ENUMSPD_POS) 
#define DSTS_EERR_POS                    (3U)                          
#define DSTS_EERR_MSK                    (0X1UL << DSTS_EERR_POS) 
#define DSTS_EERR                        DSTS_EERR_MSK         
#define DSTS_FNSOF_POS                   (8U)                          
#define DSTS_FNSOF_MSK                   (0X3FFFUL << DSTS_FNSOF_POS) 
#define DSTS_FNSOF                       DSTS_FNSOF_MSK        

/********** BIT DEFINITION FOR USB_OTG::GAHBCFG   ********************/
#define GAHBCFG_GINT_POS                 (0U)                          
#define GAHBCFG_GINT_MSK                 (0X1UL << GAHBCFG_GINT_POS) 
#define GAHBCFG_GINT                     GAHBCFG_GINT_MSK      
#define GAHBCFG_HBSTLEN_POS              (1U)                          
#define GAHBCFG_HBSTLEN_MSK              (0XFUL << GAHBCFG_HBSTLEN_POS) 
#define GAHBCFG_HBSTLEN                  GAHBCFG_HBSTLEN_MSK   
#define GAHBCFG_HBSTLEN_0                (0X0UL << GAHBCFG_HBSTLEN_POS) 
#define GAHBCFG_HBSTLEN_1                (0X1UL << GAHBCFG_HBSTLEN_POS) 
#define GAHBCFG_HBSTLEN_2                (0X3UL << GAHBCFG_HBSTLEN_POS) 
#define GAHBCFG_HBSTLEN_3                (0X5UL << GAHBCFG_HBSTLEN_POS) 
#define GAHBCFG_HBSTLEN_4                (0X7UL << GAHBCFG_HBSTLEN_POS) 
#define GAHBCFG_DMAEN_POS                (5U)                          
#define GAHBCFG_DMAEN_MSK                (0X1UL << GAHBCFG_DMAEN_POS) 
#define GAHBCFG_DMAEN                    GAHBCFG_DMAEN_MSK     
#define GAHBCFG_TXFELVL_POS              (7U)                          
#define GAHBCFG_TXFELVL_MSK              (0X1UL << GAHBCFG_TXFELVL_POS) 
#define GAHBCFG_TXFELVL                  GAHBCFG_TXFELVL_MSK   
#define GAHBCFG_PTXFELVL_POS             (8U)                          
#define GAHBCFG_PTXFELVL_MSK             (0X1UL << GAHBCFG_PTXFELVL_POS) 
#define GAHBCFG_PTXFELVL                 GAHBCFG_PTXFELVL_MSK  

/*********  BIT DEFINITION FOR USB_OTG::GUSBCFG   ********************/
#define GUSBCFG_TOCAL_POS                (0U)                          
#define GUSBCFG_TOCAL_MSK                (0X7UL << GUSBCFG_TOCAL_POS) 
#define GUSBCFG_TOCAL                    GUSBCFG_TOCAL_MSK     
#define GUSBCFG_TOCAL_0                  (0X1UL << GUSBCFG_TOCAL_POS) 
#define GUSBCFG_TOCAL_1                  (0X2UL << GUSBCFG_TOCAL_POS) 
#define GUSBCFG_TOCAL_2                  (0X4UL << GUSBCFG_TOCAL_POS) 
#define GUSBCFG_PHYSEL_POS               (6U)                          
#define GUSBCFG_PHYSEL_MSK               (0X1UL << GUSBCFG_PHYSEL_POS) 
#define GUSBCFG_PHYSEL                   GUSBCFG_PHYSEL_MSK    
#define GUSBCFG_SRPCAP_POS               (8U)                          
#define GUSBCFG_SRPCAP_MSK               (0X1UL << GUSBCFG_SRPCAP_POS) 
#define GUSBCFG_SRPCAP                   GUSBCFG_SRPCAP_MSK    
#define GUSBCFG_HNPCAP_POS               (9U)                          
#define GUSBCFG_HNPCAP_MSK               (0X1UL << GUSBCFG_HNPCAP_POS) 
#define GUSBCFG_HNPCAP                   GUSBCFG_HNPCAP_MSK    
#define GUSBCFG_TRDT_POS                 (10U)                         
#define GUSBCFG_TRDT_MSK                 (0XFUL << GUSBCFG_TRDT_POS) 
#define GUSBCFG_TRDT                     GUSBCFG_TRDT_MSK      
#define GUSBCFG_TRDT_0                   (0X1UL << GUSBCFG_TRDT_POS) 
#define GUSBCFG_TRDT_1                   (0X2UL << GUSBCFG_TRDT_POS) 
#define GUSBCFG_TRDT_2                   (0X4UL << GUSBCFG_TRDT_POS) 
#define GUSBCFG_TRDT_3                   (0X8UL << GUSBCFG_TRDT_POS) 
#define GUSBCFG_PHYLPCS_POS              (15U)                         
#define GUSBCFG_PHYLPCS_MSK              (0X1UL << GUSBCFG_PHYLPCS_POS) 
#define GUSBCFG_PHYLPCS                  GUSBCFG_PHYLPCS_MSK   
#define GUSBCFG_ULPIFSLS_POS             (17U)                         
#define GUSBCFG_ULPIFSLS_MSK             (0X1UL << GUSBCFG_ULPIFSLS_POS) 
#define GUSBCFG_ULPIFSLS                 GUSBCFG_ULPIFSLS_MSK  
#define GUSBCFG_ULPIAR_POS               (18U)                         
#define GUSBCFG_ULPIAR_MSK               (0X1UL << GUSBCFG_ULPIAR_POS) 
#define GUSBCFG_ULPIAR                   GUSBCFG_ULPIAR_MSK    
#define GUSBCFG_ULPICSM_POS              (19U)                         
#define GUSBCFG_ULPICSM_MSK              (0X1UL << GUSBCFG_ULPICSM_POS) 
#define GUSBCFG_ULPICSM                  GUSBCFG_ULPICSM_MSK   
#define GUSBCFG_ULPIEVBUSD_POS           (20U)                         
#define GUSBCFG_ULPIEVBUSD_MSK           (0X1UL << GUSBCFG_ULPIEVBUSD_POS) 
#define GUSBCFG_ULPIEVBUSD               GUSBCFG_ULPIEVBUSD_MSK 
#define GUSBCFG_ULPIEVBUSI_POS           (21U)                         
#define GUSBCFG_ULPIEVBUSI_MSK           (0X1UL << GUSBCFG_ULPIEVBUSI_POS) 
#define GUSBCFG_ULPIEVBUSI               GUSBCFG_ULPIEVBUSI_MSK 
#define GUSBCFG_TSDPS_POS                (22U)                         
#define GUSBCFG_TSDPS_MSK                (0X1UL << GUSBCFG_TSDPS_POS) 
#define GUSBCFG_TSDPS                    GUSBCFG_TSDPS_MSK     
#define GUSBCFG_PCCI_POS                 (23U)                         
#define GUSBCFG_PCCI_MSK                 (0X1UL << GUSBCFG_PCCI_POS) 
#define GUSBCFG_PCCI                     GUSBCFG_PCCI_MSK      
#define GUSBCFG_PTCI_POS                 (24U)                         
#define GUSBCFG_PTCI_MSK                 (0X1UL << GUSBCFG_PTCI_POS) 
#define GUSBCFG_PTCI                     GUSBCFG_PTCI_MSK      
#define GUSBCFG_ULPIIPD_POS              (25U)                         
#define GUSBCFG_ULPIIPD_MSK              (0X1UL << GUSBCFG_ULPIIPD_POS) 
#define GUSBCFG_ULPIIPD                  GUSBCFG_ULPIIPD_MSK   
#define GUSBCFG_FHMOD_POS                (29U)                         
#define GUSBCFG_FHMOD_MSK                (0X1UL << GUSBCFG_FHMOD_POS) 
#define GUSBCFG_FHMOD                    GUSBCFG_FHMOD_MSK     
#define GUSBCFG_FDMOD_POS                (30U)                         
#define GUSBCFG_FDMOD_MSK                (0X1UL << GUSBCFG_FDMOD_POS) 
#define GUSBCFG_FDMOD                    GUSBCFG_FDMOD_MSK     
#define GUSBCFG_CTXPKT_POS               (31U)                         
#define GUSBCFG_CTXPKT_MSK               (0X1UL << GUSBCFG_CTXPKT_POS) 
#define GUSBCFG_CTXPKT                   GUSBCFG_CTXPKT_MSK    

/***************  BIT DEFINITION FOR USB_OTG::GRSTCTL   ********************/
#define GRSTCTL_CSRST_POS                (0U)                          
#define GRSTCTL_CSRST_MSK                (0X1UL << GRSTCTL_CSRST_POS) 
#define GRSTCTL_CSRST                    GRSTCTL_CSRST_MSK     
#define GRSTCTL_HSRST_POS                (1U)                          
#define GRSTCTL_HSRST_MSK                (0X1UL << GRSTCTL_HSRST_POS) 
#define GRSTCTL_HSRST                    GRSTCTL_HSRST_MSK     
#define GRSTCTL_FCRST_POS                (2U)                          
#define GRSTCTL_FCRST_MSK                (0X1UL << GRSTCTL_FCRST_POS) 
#define GRSTCTL_FCRST                    GRSTCTL_FCRST_MSK     
#define GRSTCTL_RXFFLSH_POS              (4U)                          
#define GRSTCTL_RXFFLSH_MSK              (0X1UL << GRSTCTL_RXFFLSH_POS) 
#define GRSTCTL_RXFFLSH                  GRSTCTL_RXFFLSH_MSK   
#define GRSTCTL_TXFFLSH_POS              (5U)                          
#define GRSTCTL_TXFFLSH_MSK              (0X1UL << GRSTCTL_TXFFLSH_POS) 
#define GRSTCTL_TXFFLSH                  GRSTCTL_TXFFLSH_MSK   

#define GRSTCTL_TXFNUM_POS               (6U)                          
#define GRSTCTL_TXFNUM_MSK               (0X1FUL << GRSTCTL_TXFNUM_POS) 
#define GRSTCTL_TXFNUM                   GRSTCTL_TXFNUM_MSK    
#define GRSTCTL_TXFNUM_0                 (0X01UL << GRSTCTL_TXFNUM_POS) 
#define GRSTCTL_TXFNUM_1                 (0X02UL << GRSTCTL_TXFNUM_POS) 
#define GRSTCTL_TXFNUM_2                 (0X04UL << GRSTCTL_TXFNUM_POS) 
#define GRSTCTL_TXFNUM_3                 (0X08UL << GRSTCTL_TXFNUM_POS) 
#define GRSTCTL_TXFNUM_4                 (0X10UL << GRSTCTL_TXFNUM_POS) 
#define GRSTCTL_DMAREQ_POS               (30U)                         
#define GRSTCTL_DMAREQ_MSK               (0X1UL << GRSTCTL_DMAREQ_POS) 
#define GRSTCTL_DMAREQ                   GRSTCTL_DMAREQ_MSK    
#define GRSTCTL_AHBIDL_POS               (31U)                         
#define GRSTCTL_AHBIDL_MSK               (0X1UL << GRSTCTL_AHBIDL_POS) 
#define GRSTCTL_AHBIDL                   GRSTCTL_AHBIDL_MSK    

/************ BIT DEFINITION FOR USB_OTG::DIEPMSK   ********************/
#define DIEPMSK_XFRCM_POS                (0U)                          
#define DIEPMSK_XFRCM_MSK                (0X1UL << DIEPMSK_XFRCM_POS) 
#define DIEPMSK_XFRCM                    DIEPMSK_XFRCM_MSK     
#define DIEPMSK_EPDM_POS                 (1U)                          
#define DIEPMSK_EPDM_MSK                 (0X1UL << DIEPMSK_EPDM_POS) 
#define DIEPMSK_EPDM                     DIEPMSK_EPDM_MSK      
#define DIEPMSK_TOM_POS                  (3U)                          
#define DIEPMSK_TOM_MSK                  (0X1UL << DIEPMSK_TOM_POS) 
#define DIEPMSK_TOM                      DIEPMSK_TOM_MSK       
#define DIEPMSK_ITTXFEMSK_POS            (4U)                          
#define DIEPMSK_ITTXFEMSK_MSK            (0X1UL << DIEPMSK_ITTXFEMSK_POS) 
#define DIEPMSK_ITTXFEMSK                DIEPMSK_ITTXFEMSK_MSK 
#define DIEPMSK_INEPNMM_POS              (5U)                          
#define DIEPMSK_INEPNMM_MSK              (0X1UL << DIEPMSK_INEPNMM_POS) 
#define DIEPMSK_INEPNMM                  DIEPMSK_INEPNMM_MSK   
#define DIEPMSK_INEPNEM_POS              (6U)                          
#define DIEPMSK_INEPNEM_MSK              (0X1UL << DIEPMSK_INEPNEM_POS) 
#define DIEPMSK_INEPNEM                  DIEPMSK_INEPNEM_MSK   
#define DIEPMSK_TXFURM_POS               (8U)                          
#define DIEPMSK_TXFURM_MSK               (0X1UL << DIEPMSK_TXFURM_POS) 
#define DIEPMSK_TXFURM                   DIEPMSK_TXFURM_MSK    
#define DIEPMSK_BIM_POS                  (9U)                          
#define DIEPMSK_BIM_MSK                  (0X1UL << DIEPMSK_BIM_POS) 
#define DIEPMSK_BIM                      DIEPMSK_BIM_MSK       

/************ BIT DEFINITION FOR USB_OTG::HPTXSTS   ********************/
#define HPTXSTS_PTXFSAVL_POS             (0U)                          
#define HPTXSTS_PTXFSAVL_MSK             (0XFFFFUL << HPTXSTS_PTXFSAVL_POS) 
#define HPTXSTS_PTXFSAVL                 HPTXSTS_PTXFSAVL_MSK  
#define HPTXSTS_PTXQSAV_POS              (16U)                         
#define HPTXSTS_PTXQSAV_MSK              (0XFFUL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV                  HPTXSTS_PTXQSAV_MSK   
#define HPTXSTS_PTXQSAV_0                (0X01UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_1                (0X02UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_2                (0X04UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_3                (0X08UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_4                (0X10UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_5                (0X20UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_6                (0X40UL << HPTXSTS_PTXQSAV_POS) 
#define HPTXSTS_PTXQSAV_7                (0X80UL << HPTXSTS_PTXQSAV_POS) 

#define HPTXSTS_PTXQTOP_POS              (24U)                         
#define HPTXSTS_PTXQTOP_MSK              (0XFFUL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP                  HPTXSTS_PTXQTOP_MSK   
#define HPTXSTS_PTXQTOP_0                (0X01UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_1                (0X02UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_2                (0X04UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_3                (0X08UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_4                (0X10UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_5                (0X20UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_6                (0X40UL << HPTXSTS_PTXQTOP_POS) 
#define HPTXSTS_PTXQTOP_7                (0X80UL << HPTXSTS_PTXQTOP_POS) 

/********************  BIT DEFINITION FOR USB_OTG::HAINT   ********************/
#define HAINT_HAINT_POS                  (0U)                          
#define HAINT_HAINT_MSK                  (0XFFFFUL << HAINT_HAINT_POS) 
#define HAINT_HAINT                      HAINT_HAINT_MSK       

/********* BIT DEFINITION FOR USB_OTG::DOEPMSK   ********************/
#define DOEPMSK_XFRCM_POS                (0U)                          
#define DOEPMSK_XFRCM_MSK                (0X1UL << DOEPMSK_XFRCM_POS) 
#define DOEPMSK_XFRCM                    DOEPMSK_XFRCM_MSK     
#define DOEPMSK_EPDM_POS                 (1U)                          
#define DOEPMSK_EPDM_MSK                 (0X1UL << DOEPMSK_EPDM_POS) 
#define DOEPMSK_EPDM                     DOEPMSK_EPDM_MSK      
#define DOEPMSK_AHBERRM_POS              (2U)
#define DOEPMSK_AHBERRM_MSK              (0X1UL << DOEPMSK_AHBERRM_POS) 
#define DOEPMSK_AHBERRM                  DOEPMSK_AHBERRM_MSK   
#define DOEPMSK_STUPM_POS                (3U)                          
#define DOEPMSK_STUPM_MSK                (0X1UL << DOEPMSK_STUPM_POS) 
#define DOEPMSK_STUPM                    DOEPMSK_STUPM_MSK     
#define DOEPMSK_OTEPDM_POS               (4U)                          
#define DOEPMSK_OTEPDM_MSK               (0X1UL << DOEPMSK_OTEPDM_POS) 
#define DOEPMSK_OTEPDM                   DOEPMSK_OTEPDM_MSK    
#define DOEPMSK_OTEPSPRM_POS             (5U)                          
#define DOEPMSK_OTEPSPRM_MSK             (0X1UL << DOEPMSK_OTEPSPRM_POS) 
#define DOEPMSK_OTEPSPRM                 DOEPMSK_OTEPSPRM_MSK  
#define DOEPMSK_B2BSTUP_POS              (6U)                          
#define DOEPMSK_B2BSTUP_MSK              (0X1UL << DOEPMSK_B2BSTUP_POS) 
#define DOEPMSK_B2BSTUP                  DOEPMSK_B2BSTUP_MSK   
#define DOEPMSK_OPEM_POS                 (8U)                          
#define DOEPMSK_OPEM_MSK                 (0X1UL << DOEPMSK_OPEM_POS) 
#define DOEPMSK_OPEM                     DOEPMSK_OPEM_MSK      
#define DOEPMSK_BOIM_POS                 (9U)                          
#define DOEPMSK_BOIM_MSK                 (0X1UL << DOEPMSK_BOIM_POS) 
#define DOEPMSK_BOIM                     DOEPMSK_BOIM_MSK      
#define DOEPMSK_BERRM_POS                (12U)
#define DOEPMSK_BERRM_MSK                (0X1UL << DOEPMSK_BERRM_POS) 
#define DOEPMSK_BERRM                    DOEPMSK_BERRM_MSK      
#define DOEPMSK_NAKM_POS                 (13U)
#define DOEPMSK_NAKM_MSK                 (0X1UL << DOEPMSK_NAKM_POS) 
#define DOEPMSK_NAKM                     DOEPMSK_NAKM_MSK      
#define DOEPMSK_NYETM_POS                (14U)
#define DOEPMSK_NYETM_MSK                (0X1UL << DOEPMSK_NYETM_POS) 
#define DOEPMSK_NYETM                    DOEPMSK_NYETM_MSK 

/**********  BIT DEFINITION FOR USB_OTG::GINTSTS   ********************/
#define GINTSTS_CMOD_POS                 (0U)                          
#define GINTSTS_CMOD_MSK                 (0X1UL << GINTSTS_CMOD_POS) 
#define GINTSTS_CMOD                     GINTSTS_CMOD_MSK      
#define GINTSTS_MMIS_POS                 (1U)                          
#define GINTSTS_MMIS_MSK                 (0X1UL << GINTSTS_MMIS_POS) 
#define GINTSTS_MMIS                     GINTSTS_MMIS_MSK      
#define GINTSTS_OTGINT_POS               (2U)                          
#define GINTSTS_OTGINT_MSK               (0X1UL << GINTSTS_OTGINT_POS) 
#define GINTSTS_OTGINT                   GINTSTS_OTGINT_MSK    
#define GINTSTS_SOF_POS                  (3U)                          
#define GINTSTS_SOF_MSK                  (0X1UL << GINTSTS_SOF_POS) 
#define GINTSTS_SOF                      GINTSTS_SOF_MSK       
#define GINTSTS_RXFLVL_POS               (4U)                          
#define GINTSTS_RXFLVL_MSK               (0X1UL << GINTSTS_RXFLVL_POS) 
#define GINTSTS_RXFLVL                   GINTSTS_RXFLVL_MSK    
#define GINTSTS_NPTXFE_POS               (5U)                          
#define GINTSTS_NPTXFE_MSK               (0X1UL << GINTSTS_NPTXFE_POS) 
#define GINTSTS_NPTXFE                   GINTSTS_NPTXFE_MSK    
#define GINTSTS_GINAKEFF_POS             (6U)                          
#define GINTSTS_GINAKEFF_MSK             (0X1UL << GINTSTS_GINAKEFF_POS) 
#define GINTSTS_GINAKEFF                 GINTSTS_GINAKEFF_MSK  
#define GINTSTS_BOUTNAKEFF_POS           (7U)                          
#define GINTSTS_BOUTNAKEFF_MSK           (0X1UL << GINTSTS_BOUTNAKEFF_POS) 
#define GINTSTS_BOUTNAKEFF               GINTSTS_BOUTNAKEFF_MSK 
#define GINTSTS_ESUSP_POS                (10U)                         
#define GINTSTS_ESUSP_MSK                (0X1UL << GINTSTS_ESUSP_POS) 
#define GINTSTS_ESUSP                    GINTSTS_ESUSP_MSK     
#define GINTSTS_USBSUSP_POS              (11U)                         
#define GINTSTS_USBSUSP_MSK              (0X1UL << GINTSTS_USBSUSP_POS) 
#define GINTSTS_USBSUSP                  GINTSTS_USBSUSP_MSK   
#define GINTSTS_USBRST_POS               (12U)                         
#define GINTSTS_USBRST_MSK               (0X1UL << GINTSTS_USBRST_POS) 
#define GINTSTS_USBRST                   GINTSTS_USBRST_MSK    
#define GINTSTS_ENUMDNE_POS              (13U)                         
#define GINTSTS_ENUMDNE_MSK              (0X1UL << GINTSTS_ENUMDNE_POS) 
#define GINTSTS_ENUMDNE                  GINTSTS_ENUMDNE_MSK   
#define GINTSTS_ISOODRP_POS              (14U)                         
#define GINTSTS_ISOODRP_MSK              (0X1UL << GINTSTS_ISOODRP_POS) 
#define GINTSTS_ISOODRP                  GINTSTS_ISOODRP_MSK   
#define GINTSTS_EOPF_POS                 (15U)                         
#define GINTSTS_EOPF_MSK                 (0X1UL << GINTSTS_EOPF_POS) 
#define GINTSTS_EOPF                     GINTSTS_EOPF_MSK      
#define GINTSTS_IEPINT_POS               (18U)                         
#define GINTSTS_IEPINT_MSK               (0X1UL << GINTSTS_IEPINT_POS) 
#define GINTSTS_IEPINT                   GINTSTS_IEPINT_MSK    
#define GINTSTS_OEPINT_POS               (19U)                         
#define GINTSTS_OEPINT_MSK               (0X1UL << GINTSTS_OEPINT_POS) 
#define GINTSTS_OEPINT                   GINTSTS_OEPINT_MSK    
#define GINTSTS_IISOIXFR_POS             (20U)                         
#define GINTSTS_IISOIXFR_MSK             (0X1UL << GINTSTS_IISOIXFR_POS) 
#define GINTSTS_IISOIXFR                 GINTSTS_IISOIXFR_MSK  
#define GINTSTS_PXFR_INCOMPISOOUT_POS    (21U)                         
#define GINTSTS_PXFR_INCOMPISOOUT_MSK    (0X1UL << \
                                         GINTSTS_PXFR_INCOMPISOOUT_POS) 

#define GINTSTS_PXFR_INCOMPISOOUT        GINTSTS_PXFR_INCOMPISOOUT_MSK 
#define GINTSTS_DATAFSUSP_POS            (22U)                         
#define GINTSTS_DATAFSUSP_MSK            (0X1UL << GINTSTS_DATAFSUSP_POS) 
#define GINTSTS_DATAFSUSP                GINTSTS_DATAFSUSP_MSK 
#define GINTSTS_HPRTINT_POS              (24U)                         
#define GINTSTS_HPRTINT_MSK              (0X1UL << GINTSTS_HPRTINT_POS) 
#define GINTSTS_HPRTINT                  GINTSTS_HPRTINT_MSK   
#define GINTSTS_HCINT_POS                (25U)                         
#define GINTSTS_HCINT_MSK                (0X1UL << GINTSTS_HCINT_POS) 
#define GINTSTS_HCINT                    GINTSTS_HCINT_MSK     
#define GINTSTS_PTXFE_POS                (26U)                         
#define GINTSTS_PTXFE_MSK                (0X1UL << GINTSTS_PTXFE_POS) 
#define GINTSTS_PTXFE                    GINTSTS_PTXFE_MSK     
#define GINTSTS_CIDSCHG_POS              (28U)                         
#define GINTSTS_CIDSCHG_MSK              (0X1UL << GINTSTS_CIDSCHG_POS) 
#define GINTSTS_CIDSCHG                  GINTSTS_CIDSCHG_MSK   
#define GINTSTS_DISCINT_POS              (29U)                         
#define GINTSTS_DISCINT_MSK              (0X1UL << GINTSTS_DISCINT_POS) 
#define GINTSTS_DISCINT                  GINTSTS_DISCINT_MSK   
#define GINTSTS_SRQINT_POS               (30U)                         
#define GINTSTS_SRQINT_MSK               (0X1UL << GINTSTS_SRQINT_POS) 
#define GINTSTS_SRQINT                   GINTSTS_SRQINT_MSK    
#define GINTSTS_WKUINT_POS               (31U)                         
#define GINTSTS_WKUINT_MSK               (0X1UL << GINTSTS_WKUINT_POS) 
#define GINTSTS_WKUINT                   GINTSTS_WKUINT_MSK    

/******** BIT DEFINITION FOR USB_OTG::GINTMSK   ********************/
#define GINTMSK_MMISM_POS                (1U)                          
#define GINTMSK_MMISM_MSK                (0X1UL << GINTMSK_MMISM_POS) 
#define GINTMSK_MMISM                    GINTMSK_MMISM_MSK     
#define GINTMSK_OTGINT_POS               (2U)                          
#define GINTMSK_OTGINT_MSK               (0X1UL << GINTMSK_OTGINT_POS) 
#define GINTMSK_OTGINT                   GINTMSK_OTGINT_MSK    
#define GINTMSK_SOFM_POS                 (3U)                          
#define GINTMSK_SOFM_MSK                 (0X1UL << GINTMSK_SOFM_POS) 
#define GINTMSK_SOFM                     GINTMSK_SOFM_MSK      
#define GINTMSK_RXFLVLM_POS              (4U)                          
#define GINTMSK_RXFLVLM_MSK              (0X1UL << GINTMSK_RXFLVLM_POS) 
#define GINTMSK_RXFLVLM                  GINTMSK_RXFLVLM_MSK   
#define GINTMSK_NPTXFEM_POS              (5U)                          
#define GINTMSK_NPTXFEM_MSK              (0X1UL << GINTMSK_NPTXFEM_POS) 
#define GINTMSK_NPTXFEM                  GINTMSK_NPTXFEM_MSK   
#define GINTMSK_GINAKEFFM_POS            (6U)                          
#define GINTMSK_GINAKEFFM_MSK            (0X1UL << GINTMSK_GINAKEFFM_POS) 
#define GINTMSK_GINAKEFFM                GINTMSK_GINAKEFFM_MSK 
#define GINTMSK_GONAKEFFM_POS            (7U)                          
#define GINTMSK_GONAKEFFM_MSK            (0X1UL << GINTMSK_GONAKEFFM_POS) 
#define GINTMSK_GONAKEFFM                GINTMSK_GONAKEFFM_MSK 
#define GINTMSK_ESUSPM_POS               (10U)                         
#define GINTMSK_ESUSPM_MSK               (0X1UL << GINTMSK_ESUSPM_POS) 
#define GINTMSK_ESUSPM                   GINTMSK_ESUSPM_MSK    
#define GINTMSK_USBSUSPM_POS             (11U)                         
#define GINTMSK_USBSUSPM_MSK             (0X1UL << GINTMSK_USBSUSPM_POS) 
#define GINTMSK_USBSUSPM                 GINTMSK_USBSUSPM_MSK  
#define GINTMSK_USBRST_POS               (12U)                         
#define GINTMSK_USBRST_MSK               (0X1UL << GINTMSK_USBRST_POS) 
#define GINTMSK_USBRST                   GINTMSK_USBRST_MSK    
#define GINTMSK_ENUMDNEM_POS             (13U)                         
#define GINTMSK_ENUMDNEM_MSK             (0X1UL << GINTMSK_ENUMDNEM_POS) 
#define GINTMSK_ENUMDNEM                 GINTMSK_ENUMDNEM_MSK  
#define GINTMSK_ISOODRPM_POS             (14U)                         
#define GINTMSK_ISOODRPM_MSK             (0X1UL << GINTMSK_ISOODRPM_POS) 
#define GINTMSK_ISOODRPM                 GINTMSK_ISOODRPM_MSK  
#define GINTMSK_EOPFM_POS                (15U)                         
#define GINTMSK_EOPFM_MSK                (0X1UL << GINTMSK_EOPFM_POS) 
#define GINTMSK_EOPFM                    GINTMSK_EOPFM_MSK     
#define GINTMSK_EPMISM_POS               (17U)                         
#define GINTMSK_EPMISM_MSK               (0X1UL << GINTMSK_EPMISM_POS) 
#define GINTMSK_EPMISM                   GINTMSK_EPMISM_MSK    
#define GINTMSK_IEPINT_POS               (18U)                         
#define GINTMSK_IEPINT_MSK               (0X1UL << GINTMSK_IEPINT_POS) 
#define GINTMSK_IEPINT                   GINTMSK_IEPINT_MSK    
#define GINTMSK_OEPINT_POS               (19U)                         
#define GINTMSK_OEPINT_MSK               (0X1UL << GINTMSK_OEPINT_POS) 
#define GINTMSK_OEPINT                   GINTMSK_OEPINT_MSK    
#define GINTMSK_IISOIXFRM_POS            (20U)                         
#define GINTMSK_IISOIXFRM_MSK            (0X1UL << GINTMSK_IISOIXFRM_POS) 
#define GINTMSK_IISOIXFRM                GINTMSK_IISOIXFRM_MSK 
#define GINTMSK_PXFRM_IISOOXFRM_POS      (21U)                         
#define GINTMSK_PXFRM_IISOOXFRM_MSK      (0X1UL << GINTMSK_PXFRM_IISOOXFRM_POS) 
#define GINTMSK_PXFRM_IISOOXFRM          GINTMSK_PXFRM_IISOOXFRM_MSK 
#define GINTMSK_FSUSPM_POS               (22U)                         
#define GINTMSK_FSUSPM_MSK               (0X1UL << GINTMSK_FSUSPM_POS) 
#define GINTMSK_FSUSPM                   GINTMSK_FSUSPM_MSK    
#define GINTMSK_PRTIM_POS                (24U)                         
#define GINTMSK_PRTIM_MSK                (0X1UL << GINTMSK_PRTIM_POS) 
#define GINTMSK_PRTIM                    GINTMSK_PRTIM_MSK     
#define GINTMSK_HCIM_POS                 (25U)                         
#define GINTMSK_HCIM_MSK                 (0X1UL << GINTMSK_HCIM_POS) 
#define GINTMSK_HCIM                     GINTMSK_HCIM_MSK      
#define GINTMSK_PTXFEM_POS               (26U)                         
#define GINTMSK_PTXFEM_MSK               (0X1UL << GINTMSK_PTXFEM_POS) 
#define GINTMSK_PTXFEM                   GINTMSK_PTXFEM_MSK    
#define GINTMSK_CIDSCHGM_POS             (28U)                         
#define GINTMSK_CIDSCHGM_MSK             (0X1UL << GINTMSK_CIDSCHGM_POS) 
#define GINTMSK_CIDSCHGM                 GINTMSK_CIDSCHGM_MSK  
#define GINTMSK_DISCINT_POS              (29U)                         
#define GINTMSK_DISCINT_MSK              (0X1UL << GINTMSK_DISCINT_POS) 
#define GINTMSK_DISCINT                  GINTMSK_DISCINT_MSK   
#define GINTMSK_SRQIM_POS                (30U)                         
#define GINTMSK_SRQIM_MSK                (0X1UL << GINTMSK_SRQIM_POS) 
#define GINTMSK_SRQIM                    GINTMSK_SRQIM_MSK     
#define GINTMSK_WUIM_POS                 (31U)                         
#define GINTMSK_WUIM_MSK                 (0X1UL << GINTMSK_WUIM_POS) 
#define GINTMSK_WUIM                     GINTMSK_WUIM_MSK      

/********************  BIT DEFINITION FOR USB_OTG::DAINT   ********************/
#define DAINT_IEPINT_POS                 (0U)                          
#define DAINT_IEPINT_MSK                 (0XFFFFUL << DAINT_IEPINT_POS) 
#define DAINT_IEPINT                     DAINT_IEPINT_MSK      
#define DAINT_OEPINT_POS                 (16U)                         
#define DAINT_OEPINT_MSK                 (0XFFFFUL << DAINT_OEPINT_POS) 
#define DAINT_OEPINT                     DAINT_OEPINT_MSK      

/***********  BIT DEFINITION FOR USB_OTG::HAINTMSK   ********************/
#define HAINTMSK_HAINTM_POS              (0U)                          
#define HAINTMSK_HAINTM_MSK              (0XFFFFUL << HAINTMSK_HAINTM_POS) 
#define HAINTMSK_HAINTM                  HAINTMSK_HAINTM_MSK   

/********** BIT DEFINITION FOR USB_OTG::GRXSTSP   ********************/
#define GRXSTSP_EPNUM_POS                (0U)                          
#define GRXSTSP_EPNUM_MSK                (0XFUL << GRXSTSP_EPNUM_POS) 
#define GRXSTSP_EPNUM                    GRXSTSP_EPNUM_MSK     
#define GRXSTSP_BCNT_POS                 (4U)                          
#define GRXSTSP_BCNT_MSK                 (0X7FFUL << GRXSTSP_BCNT_POS) 
#define GRXSTSP_BCNT                     GRXSTSP_BCNT_MSK      
#define GRXSTSP_DPID_POS                 (15U)                         
#define GRXSTSP_DPID_MSK                 (0X3UL << GRXSTSP_DPID_POS) 
#define GRXSTSP_DPID                     GRXSTSP_DPID_MSK      
#define GRXSTSP_PKTSTS_POS               (17U)                         
#define GRXSTSP_PKTSTS_MSK               (0XFUL << GRXSTSP_PKTSTS_POS) 
#define GRXSTSP_PKTSTS                   GRXSTSP_PKTSTS_MSK    

/********** BIT DEFINITION FOR USB_OTG::DAINTMSK   ********************/
#define DAINTMSK_IEPM_POS                (0U)                          
#define DAINTMSK_IEPM_MSK                (0XFFFFUL << DAINTMSK_IEPM_POS) 
#define DAINTMSK_IEPM                    DAINTMSK_IEPM_MSK     
#define DAINTMSK_OEPM_POS                (16U)                         
#define DAINTMSK_OEPM_MSK                (0XFFFFUL << DAINTMSK_OEPM_POS) 
#define DAINTMSK_OEPM                    DAINTMSK_OEPM_MSK     

/********** BIT DEFINITION FOR USB_OTG::GRXFSIZ   ********************/
#define GRXFSIZ_RXFD_POS                 (0U)                          
#define GRXFSIZ_RXFD_MSK                 (0XFFFFUL << GRXFSIZ_RXFD_POS) 
#define GRXFSIZ_RXFD                     GRXFSIZ_RXFD_MSK      

/*********** BIT DEFINITION FOR USB_OTG::DVBUSDIS   ********************/
#define DVBUSDIS_VBUSDT_POS              (0U)                          
#define DVBUSDIS_VBUSDT_MSK              (0XFFFFUL << DVBUSDIS_VBUSDT_POS) 
#define DVBUSDIS_VBUSDT                  DVBUSDIS_VBUSDT_MSK   

/********* BIT DEFINITION FOR OTG   ********************/
#define NPTXFSA_POS                      (0U)                          
#define NPTXFSA_MSK                      (0XFFFFUL << NPTXFSA_POS) 
#define NPTXFSA                          NPTXFSA_MSK           
#define NPTXFD_POS                       (16U)                         
#define NPTXFD_MSK                       (0XFFFFUL << NPTXFD_POS) 
#define NPTXFD                           NPTXFD_MSK            
#define TX0FSA_POS                       (0U)                          
#define TX0FSA_MSK                       (0XFFFFUL << TX0FSA_POS) 
#define TX0FSA                           TX0FSA_MSK            
#define TX0FD_POS                        (16U)                         
#define TX0FD_MSK                        (0XFFFFUL << TX0FD_POS) 
#define TX0FD                            TX0FD_MSK             

/************  BIT DEFINITION FORDVBUSPULSE   ********************/
#define DVBUSPULSE_DVBUSP_POS            (0U)                          
#define DVBUSPULSE_DVBUSP_MSK            (0XFFFUL << DVBUSPULSE_DVBUSP_POS) 
#define DVBUSPULSE_DVBUSP                DVBUSPULSE_DVBUSP_MSK 

/*********** BIT DEFINITION FOR USB_OTG::GNPTXSTS   ********************/
#define GNPTXSTS_NPTXFSAV_POS            (0U)                          
#define GNPTXSTS_NPTXFSAV_MSK            (0XFFFFUL << GNPTXSTS_NPTXFSAV_POS) 
#define GNPTXSTS_NPTXFSAV                GNPTXSTS_NPTXFSAV_MSK 

#define GNPTXSTS_NPTQXSAV_POS            (16U)                         
#define GNPTXSTS_NPTQXSAV_MSK            (0XFFUL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV                GNPTXSTS_NPTQXSAV_MSK 
#define GNPTXSTS_NPTQXSAV_0              (0X01UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_1              (0X02UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_2              (0X04UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_3              (0X08UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_4              (0X10UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_5              (0X20UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_6              (0X40UL << GNPTXSTS_NPTQXSAV_POS) 
#define GNPTXSTS_NPTQXSAV_7              (0X80UL << GNPTXSTS_NPTQXSAV_POS) 

#define GNPTXSTS_NPTXQTOP_POS            (24U)                         
#define GNPTXSTS_NPTXQTOP_MSK            (0X7FUL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP                GNPTXSTS_NPTXQTOP_MSK 
#define GNPTXSTS_NPTXQTOP_0              (0X01UL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP_1              (0X02UL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP_2              (0X04UL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP_3              (0X08UL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP_4              (0X10UL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP_5              (0X20UL << GNPTXSTS_NPTXQTOP_POS) 
#define GNPTXSTS_NPTXQTOP_6              (0X40UL << GNPTXSTS_NPTXQTOP_POS) 

/*********** BIT DEFINITION FOR USB_OTG::DTHRCTL   ********************/
#define DTHRCTL_NONISOTHREN_POS          (0U)                          
#define DTHRCTL_NONISOTHREN_MSK          (0X1UL << DTHRCTL_NONISOTHREN_POS) 
#define DTHRCTL_NONISOTHREN              DTHRCTL_NONISOTHREN_MSK 
#define DTHRCTL_ISOTHREN_POS             (1U)                          
#define DTHRCTL_ISOTHREN_MSK             (0X1UL << DTHRCTL_ISOTHREN_POS) 
#define DTHRCTL_ISOTHREN                 DTHRCTL_ISOTHREN_MSK  

#define DTHRCTL_TXTHRLEN_POS             (2U)                          
#define DTHRCTL_TXTHRLEN_MSK             (0X1FFUL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN                 DTHRCTL_TXTHRLEN_MSK  
#define DTHRCTL_TXTHRLEN_0               (0X001UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_1               (0X002UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_2               (0X004UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_3               (0X008UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_4               (0X010UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_5               (0X020UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_6               (0X040UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_7               (0X080UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_TXTHRLEN_8               (0X100UL << DTHRCTL_TXTHRLEN_POS) 
#define DTHRCTL_RXTHREN_POS              (16U)                         
#define DTHRCTL_RXTHREN_MSK              (0X1UL << DTHRCTL_RXTHREN_POS) 
#define DTHRCTL_RXTHREN                  DTHRCTL_RXTHREN_MSK   

#define DTHRCTL_RXTHRLEN_POS             (17U)                         
#define DTHRCTL_RXTHRLEN_MSK             (0X1FFUL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN                 DTHRCTL_RXTHRLEN_MSK  
#define DTHRCTL_RXTHRLEN_0               (0X001UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_1               (0X002UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_2               (0X004UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_3               (0X008UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_4               (0X010UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_5               (0X020UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_6               (0X040UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_7               (0X080UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_RXTHRLEN_8               (0X100UL << DTHRCTL_RXTHRLEN_POS) 
#define DTHRCTL_ARPEN_POS                (27U)                         
#define DTHRCTL_ARPEN_MSK                (0X1UL << DTHRCTL_ARPEN_POS) 
#define DTHRCTL_ARPEN                    DTHRCTL_ARPEN_MSK     

/*********** BIT DEFINITION FOR USB_OTG::DIEPEMPMSK   ********************/
#define DIEPEMPMSK_INEPTXFEM_POS         (0U)                          
#define DIEPEMPMSK_INEPTXFEM_MSK         (0XFFFFUL << DIEPEMPMSK_INEPTXFEM_POS) 
#define DIEPEMPMSK_INEPTXFEM             DIEPEMPMSK_INEPTXFEM_MSK 

/************** BIT DEFINITION FOR USB_OTG::DEACHINT   ********************/
#define DEACHINT_IEP1INT_POS             (1U)                          
#define DEACHINT_IEP1INT_MSK             (0X1UL << DEACHINT_IEP1INT_POS) 
#define DEACHINT_IEP1INT                 DEACHINT_IEP1INT_MSK  
#define DEACHINT_OEP1INT_POS             (17U)                         
#define DEACHINT_OEP1INT_MSK             (0X1UL << DEACHINT_OEP1INT_POS) 
#define DEACHINT_OEP1INT                 DEACHINT_OEP1INT_MSK  

/********************  BIT DEFINITION FOR USB_OTG::GCCFG   ********************/
#define GCCFG_PWRDWN_POS                 (16U)                         
#define GCCFG_PWRDWN_MSK                 (0X1UL << GCCFG_PWRDWN_POS) 
#define GCCFG_PWRDWN                     GCCFG_PWRDWN_MSK      
#define GCCFG_I2CPADEN_POS               (17U)                         
#define GCCFG_I2CPADEN_MSK               (0X1UL << GCCFG_I2CPADEN_POS) 
#define GCCFG_I2CPADEN                   GCCFG_I2CPADEN_MSK     
#define GCCFG_VBUSASEN_POS               (18U)                         
#define GCCFG_VBUSASEN_MSK               (0X1UL << GCCFG_VBUSASEN_POS) 
#define GCCFG_VBUSASEN                   GCCFG_VBUSASEN_MSK    
#define GCCFG_VBUSBSEN_POS               (19U)                         
#define GCCFG_VBUSBSEN_MSK               (0X1UL << GCCFG_VBUSBSEN_POS) 
#define GCCFG_VBUSBSEN                   GCCFG_VBUSBSEN_MSK    
#define GCCFG_SOFOUTEN_POS               (20U)                         
#define GCCFG_SOFOUTEN_MSK               (0X1UL << GCCFG_SOFOUTEN_POS) 
#define GCCFG_SOFOUTEN                   GCCFG_SOFOUTEN_MSK    
#define GCCFG_NOVBUSSENS_POS             (21U)                         
#define GCCFG_NOVBUSSENS_MSK             (0X1UL << GCCFG_NOVBUSSENS_POS) 
#define GCCFG_NOVBUSSENS                 GCCFG_NOVBUSSENS_MSK   

/********************  BIT DEFINITION FORDEACHINTMSK   ********************/
#define DEACHINTMSK_IEP1INTM_POS         (1U)                          
#define DEACHINTMSK_IEP1INTM_MSK         (0X1UL << DEACHINTMSK_IEP1INTM_POS) 
#define DEACHINTMSK_IEP1INTM             DEACHINTMSK_IEP1INTM_MSK 
#define DEACHINTMSK_OEP1INTM_POS         (17U)                         
#define DEACHINTMSK_OEP1INTM_MSK         (0X1UL << DEACHINTMSK_OEP1INTM_POS) 
#define DEACHINTMSK_OEP1INTM             DEACHINTMSK_OEP1INTM_MSK 

/********************  BIT DEFINITION FOR USB_OTG::CID   ********************/
#define CID_PRODUCT_ID_POS               (0U)                          
#define CID_PRODUCT_ID_MSK               (0XFFFFFFFFUL << CID_PRODUCT_ID_POS) 
#define CID_PRODUCT_ID                   CID_PRODUCT_ID_MSK    

/************* BIT DEFINITION FOR USB_OTG::DIEPEACHMSK1   ********************/
#define DIEPEACHMSK1_XFRCM_POS           (0U)                          
#define DIEPEACHMSK1_XFRCM_MSK           (0X1UL << DIEPEACHMSK1_XFRCM_POS) 
#define DIEPEACHMSK1_XFRCM               DIEPEACHMSK1_XFRCM_MSK 
#define DIEPEACHMSK1_EPDM_POS            (1U)                          
#define DIEPEACHMSK1_EPDM_MSK            (0X1UL << DIEPEACHMSK1_EPDM_POS) 
#define DIEPEACHMSK1_EPDM                DIEPEACHMSK1_EPDM_MSK 
#define DIEPEACHMSK1_TOM_POS             (3U)                          
#define DIEPEACHMSK1_TOM_MSK             (0X1UL << DIEPEACHMSK1_TOM_POS) 
#define DIEPEACHMSK1_TOM                 DIEPEACHMSK1_TOM_MSK  
#define DIEPEACHMSK1_ITTXFEMSK_POS       (4U)                          
#define DIEPEACHMSK1_ITTXFEMSK_MSK       (0X1UL << DIEPEACHMSK1_ITTXFEMSK_POS) 
#define DIEPEACHMSK1_ITTXFEMSK           DIEPEACHMSK1_ITTXFEMSK_MSK 
#define DIEPEACHMSK1_INEPNMM_POS         (5U)                          
#define DIEPEACHMSK1_INEPNMM_MSK         (0X1UL << DIEPEACHMSK1_INEPNMM_POS) 
#define DIEPEACHMSK1_INEPNMM             DIEPEACHMSK1_INEPNMM_MSK 
#define DIEPEACHMSK1_INEPNEM_POS         (6U)                          
#define DIEPEACHMSK1_INEPNEM_MSK         (0X1UL << DIEPEACHMSK1_INEPNEM_POS) 
#define DIEPEACHMSK1_INEPNEM             DIEPEACHMSK1_INEPNEM_MSK 
#define DIEPEACHMSK1_TXFURM_POS          (8U)                          
#define DIEPEACHMSK1_TXFURM_MSK          (0X1UL << DIEPEACHMSK1_TXFURM_POS) 
#define DIEPEACHMSK1_TXFURM              DIEPEACHMSK1_TXFURM_MSK 
#define DIEPEACHMSK1_BIM_POS             (9U)                          
#define DIEPEACHMSK1_BIM_MSK             (0X1UL << DIEPEACHMSK1_BIM_POS) 
#define DIEPEACHMSK1_BIM                 DIEPEACHMSK1_BIM_MSK  
#define DIEPEACHMSK1_NAKM_POS            (13U)                         
#define DIEPEACHMSK1_NAKM_MSK            (0X1UL << DIEPEACHMSK1_NAKM_POS) 
#define DIEPEACHMSK1_NAKM                DIEPEACHMSK1_NAKM_MSK 

/********************  BIT DEFINITION FOR USB_OTG::HPRT   ********************/
#define HPRT_PCSTS_POS                   (0U)                          
#define HPRT_PCSTS_MSK                   (0X1UL << HPRT_PCSTS_POS) 
#define HPRT_PCSTS                       HPRT_PCSTS_MSK        
#define HPRT_PCDET_POS                   (1U)                          
#define HPRT_PCDET_MSK                   (0X1UL << HPRT_PCDET_POS) 
#define HPRT_PCDET                       HPRT_PCDET_MSK        
#define HPRT_PENA_POS                    (2U)                          
#define HPRT_PENA_MSK                    (0X1UL << HPRT_PENA_POS) 
#define HPRT_PENA                        HPRT_PENA_MSK         
#define HPRT_PENCHNG_POS                 (3U)                          
#define HPRT_PENCHNG_MSK                 (0X1UL << HPRT_PENCHNG_POS) 
#define HPRT_PENCHNG                     HPRT_PENCHNG_MSK      
#define HPRT_POCA_POS                    (4U)                          
#define HPRT_POCA_MSK                    (0X1UL << HPRT_POCA_POS) 
#define HPRT_POCA                        HPRT_POCA_MSK         
#define HPRT_POCCHNG_POS                 (5U)                          
#define HPRT_POCCHNG_MSK                 (0X1UL << HPRT_POCCHNG_POS) 
#define HPRT_POCCHNG                     HPRT_POCCHNG_MSK      
#define HPRT_PRES_POS                    (6U)                          
#define HPRT_PRES_MSK                    (0X1UL << HPRT_PRES_POS) 
#define HPRT_PRES                        HPRT_PRES_MSK         
#define HPRT_PSUSP_POS                   (7U)                          
#define HPRT_PSUSP_MSK                   (0X1UL << HPRT_PSUSP_POS) 
#define HPRT_PSUSP                       HPRT_PSUSP_MSK        
#define HPRT_PRST_POS                    (8U)                          
#define HPRT_PRST_MSK                    (0X1UL << HPRT_PRST_POS) 
#define HPRT_PRST                        HPRT_PRST_MSK         

#define HPRT_PLSTS_POS                   (10U)                         
#define HPRT_PLSTS_MSK                   (0X3UL << HPRT_PLSTS_POS) 
#define HPRT_PLSTS                       HPRT_PLSTS_MSK        
#define HPRT_PLSTS_0                     (0X1UL << HPRT_PLSTS_POS) 
#define HPRT_PLSTS_1                     (0X2UL << HPRT_PLSTS_POS) 
#define HPRT_PPWR_POS                    (12U)                         
#define HPRT_PPWR_MSK                    (0X1UL << HPRT_PPWR_POS) 
#define HPRT_PPWR                        HPRT_PPWR_MSK         

#define HPRT_PTCTL_POS                   (13U)                         
#define HPRT_PTCTL_MSK                   (0XFUL << HPRT_PTCTL_POS) 
#define HPRT_PTCTL                       HPRT_PTCTL_MSK        
#define HPRT_PTCTL_0                     (0X1UL << HPRT_PTCTL_POS) 
#define HPRT_PTCTL_1                     (0X2UL << HPRT_PTCTL_POS) 
#define HPRT_PTCTL_2                     (0X4UL << HPRT_PTCTL_POS) 
#define HPRT_PTCTL_3                     (0X8UL << HPRT_PTCTL_POS) 

#define HPRT_PSPD_POS                    (17U)                         
#define HPRT_PSPD_MSK                    (0X3UL << HPRT_PSPD_POS) 
#define HPRT_PSPD                        HPRT_PSPD_MSK         
#define HPRT_PSPD_0                      (0X1UL << HPRT_PSPD_POS) 
#define HPRT_PSPD_1                      (0X2UL << HPRT_PSPD_POS) 

/*********** BIT DEFINITION FOR USB_OTG::DOEPEACHMSK1   ********************/
#define DOEPEACHMSK1_XFRCM_POS           (0U)                          
#define DOEPEACHMSK1_XFRCM_MSK           (0X1UL << DOEPEACHMSK1_XFRCM_POS) 
#define DOEPEACHMSK1_XFRCM               DOEPEACHMSK1_XFRCM_MSK 
#define DOEPEACHMSK1_EPDM_POS            (1U)                          
#define DOEPEACHMSK1_EPDM_MSK            (0X1UL << DOEPEACHMSK1_EPDM_POS) 
#define DOEPEACHMSK1_EPDM                DOEPEACHMSK1_EPDM_MSK 
#define DOEPEACHMSK1_TOM_POS             (3U)                          
#define DOEPEACHMSK1_TOM_MSK             (0X1UL << DOEPEACHMSK1_TOM_POS) 
#define DOEPEACHMSK1_TOM                 DOEPEACHMSK1_TOM_MSK  
#define DOEPEACHMSK1_ITTXFEMSK_POS       (4U)                          
#define DOEPEACHMSK1_ITTXFEMSK_MSK       (0X1UL << DOEPEACHMSK1_ITTXFEMSK_POS) 
#define DOEPEACHMSK1_ITTXFEMSK           DOEPEACHMSK1_ITTXFEMSK_MSK 
#define DOEPEACHMSK1_INEPNMM_POS         (5U)                          
#define DOEPEACHMSK1_INEPNMM_MSK         (0X1UL << DOEPEACHMSK1_INEPNMM_POS) 
#define DOEPEACHMSK1_INEPNMM             DOEPEACHMSK1_INEPNMM_MSK 
#define DOEPEACHMSK1_INEPNEM_POS         (6U)                          
#define DOEPEACHMSK1_INEPNEM_MSK         (0X1UL << DOEPEACHMSK1_INEPNEM_POS) 
#define DOEPEACHMSK1_INEPNEM             DOEPEACHMSK1_INEPNEM_MSK 
#define DOEPEACHMSK1_TXFURM_POS          (8U)                          
#define DOEPEACHMSK1_TXFURM_MSK          (0X1UL << DOEPEACHMSK1_TXFURM_POS) 
#define DOEPEACHMSK1_TXFURM              DOEPEACHMSK1_TXFURM_MSK 
#define DOEPEACHMSK1_BIM_POS             (9U)                          
#define DOEPEACHMSK1_BIM_MSK             (0X1UL << DOEPEACHMSK1_BIM_POS) 
#define DOEPEACHMSK1_BIM                 DOEPEACHMSK1_BIM_MSK  
#define DOEPEACHMSK1_BERRM_POS           (12U)                         
#define DOEPEACHMSK1_BERRM_MSK           (0X1UL << DOEPEACHMSK1_BERRM_POS) 
#define DOEPEACHMSK1_BERRM               DOEPEACHMSK1_BERRM_MSK 
#define DOEPEACHMSK1_NAKM_POS            (13U)                         
#define DOEPEACHMSK1_NAKM_MSK            (0X1UL << DOEPEACHMSK1_NAKM_POS) 
#define DOEPEACHMSK1_NAKM                DOEPEACHMSK1_NAKM_MSK 
#define DOEPEACHMSK1_NYETM_POS           (14U)                         
#define DOEPEACHMSK1_NYETM_MSK           (0X1UL << DOEPEACHMSK1_NYETM_POS) 
#define DOEPEACHMSK1_NYETM               DOEPEACHMSK1_NYETM_MSK 

/********  BIT DEFINITION FOR USB_OTG::HPTXFSIZ   ********************/
#define HPTXFSIZ_PTXSA_POS               (0U)                          
#define HPTXFSIZ_PTXSA_MSK               (0XFFFFUL << HPTXFSIZ_PTXSA_POS) 
#define HPTXFSIZ_PTXSA                   HPTXFSIZ_PTXSA_MSK    
#define HPTXFSIZ_PTXFD_POS               (16U)                         
#define HPTXFSIZ_PTXFD_MSK               (0XFFFFUL << HPTXFSIZ_PTXFD_POS) 
#define HPTXFSIZ_PTXFD                   HPTXFSIZ_PTXFD_MSK    

/**********  BIT DEFINITION FOR USB_OTG::DIEPCTL   ********************/
#define DIEPCTL_MPSIZ_POS                (0U)                          
#define DIEPCTL_MPSIZ_MSK                (0X7FFUL << DIEPCTL_MPSIZ_POS) 
#define DIEPCTL_MPSIZ                    DIEPCTL_MPSIZ_MSK     
#define DIEPCTL_USBAEP_POS               (15U)                         
#define DIEPCTL_USBAEP_MSK               (0X1UL << DIEPCTL_USBAEP_POS) 
#define DIEPCTL_USBAEP                   DIEPCTL_USBAEP_MSK    
#define DIEPCTL_EONUM_DPID_POS           (16U)                         
#define DIEPCTL_EONUM_DPID_MSK           (0X1UL << DIEPCTL_EONUM_DPID_POS) 
#define DIEPCTL_EONUM_DPID               DIEPCTL_EONUM_DPID_MSK 
#define DIEPCTL_NAKSTS_POS               (17U)                         
#define DIEPCTL_NAKSTS_MSK               (0X1UL << DIEPCTL_NAKSTS_POS) 
#define DIEPCTL_NAKSTS                   DIEPCTL_NAKSTS_MSK    

#define DIEPCTL_EPTYP_POS                (18U)                         
#define DIEPCTL_EPTYP_MSK                (0X3UL << DIEPCTL_EPTYP_POS) 
#define DIEPCTL_EPTYP                    DIEPCTL_EPTYP_MSK     
#define DIEPCTL_EPTYP_0                  (0X1UL << DIEPCTL_EPTYP_POS) 
#define DIEPCTL_EPTYP_1                  (0X2UL << DIEPCTL_EPTYP_POS) 
#define DIEPCTL_STALL_POS                (21U)                         
#define DIEPCTL_STALL_MSK                (0X1UL << DIEPCTL_STALL_POS) 
#define DIEPCTL_STALL                    DIEPCTL_STALL_MSK     

#define DIEPCTL_TXFNUM_POS               (22U)                         
#define DIEPCTL_TXFNUM_MSK               (0XFUL << DIEPCTL_TXFNUM_POS) 
#define DIEPCTL_TXFNUM                   DIEPCTL_TXFNUM_MSK    
#define DIEPCTL_TXFNUM_0                 (0X1UL << DIEPCTL_TXFNUM_POS) 
#define DIEPCTL_TXFNUM_1                 (0X2UL << DIEPCTL_TXFNUM_POS) 
#define DIEPCTL_TXFNUM_2                 (0X4UL << DIEPCTL_TXFNUM_POS) 
#define DIEPCTL_TXFNUM_3                 (0X8UL << DIEPCTL_TXFNUM_POS) 
#define DIEPCTL_CNAK_POS                 (26U)                         
#define DIEPCTL_CNAK_MSK                 (0X1UL << DIEPCTL_CNAK_POS) 
#define DIEPCTL_CNAK                     DIEPCTL_CNAK_MSK      
#define DIEPCTL_SNAK_POS                 (27U)                         
#define DIEPCTL_SNAK_MSK                 (0X1UL << DIEPCTL_SNAK_POS) 
#define DIEPCTL_SNAK                     DIEPCTL_SNAK_MSK      
#define DIEPCTL_SD0PID_SEVNFRM_POS       (28U)                         
#define DIEPCTL_SD0PID_SEVNFRM_MSK       (0X1UL << DIEPCTL_SD0PID_SEVNFRM_POS) 
#define DIEPCTL_SD0PID_SEVNFRM           DIEPCTL_SD0PID_SEVNFRM_MSK 
#define DIEPCTL_SODDFRM_POS              (29U)                         
#define DIEPCTL_SODDFRM_MSK              (0X1UL << DIEPCTL_SODDFRM_POS) 
#define DIEPCTL_SODDFRM                  DIEPCTL_SODDFRM_MSK   
#define DIEPCTL_EPDIS_POS                (30U)                         
#define DIEPCTL_EPDIS_MSK                (0X1UL << DIEPCTL_EPDIS_POS) 
#define DIEPCTL_EPDIS                    DIEPCTL_EPDIS_MSK     
#define DIEPCTL_EPENA_POS                (31U)                         
#define DIEPCTL_EPENA_MSK                (0X1UL << DIEPCTL_EPENA_POS) 
#define DIEPCTL_EPENA                    DIEPCTL_EPENA_MSK     

/********* BIT DEFINITION FOR USB_OTG::HCCHAR   ********************/
#define HCCHAR_MPSIZ_POS                 (0U)                          
#define HCCHAR_MPSIZ_MSK                 (0X7FFUL << HCCHAR_MPSIZ_POS) 
#define HCCHAR_MPSIZ                     HCCHAR_MPSIZ_MSK      

#define HCCHAR_EPNUM_POS                 (11U)                         
#define HCCHAR_EPNUM_MSK                 (0XFUL << HCCHAR_EPNUM_POS) 
#define HCCHAR_EPNUM                     HCCHAR_EPNUM_MSK      
#define HCCHAR_EPNUM_0                   (0X1UL << HCCHAR_EPNUM_POS) 
#define HCCHAR_EPNUM_1                   (0X2UL << HCCHAR_EPNUM_POS) 
#define HCCHAR_EPNUM_2                   (0X4UL << HCCHAR_EPNUM_POS) 
#define HCCHAR_EPNUM_3                   (0X8UL << HCCHAR_EPNUM_POS) 
#define HCCHAR_EPDIR_POS                 (15U)                         
#define HCCHAR_EPDIR_MSK                 (0X1UL << HCCHAR_EPDIR_POS) 
#define HCCHAR_EPDIR                     HCCHAR_EPDIR_MSK      
#define HCCHAR_LSDEV_POS                 (17U)                         
#define HCCHAR_LSDEV_MSK                 (0X1UL << HCCHAR_LSDEV_POS) 
#define HCCHAR_LSDEV                     HCCHAR_LSDEV_MSK      

#define HCCHAR_EPTYP_POS                 (18U)                         
#define HCCHAR_EPTYP_MSK                 (0X3UL << HCCHAR_EPTYP_POS) 
#define HCCHAR_EPTYP                     HCCHAR_EPTYP_MSK      
#define HCCHAR_EPTYP_0                   (0X1UL << HCCHAR_EPTYP_POS) 
#define HCCHAR_EPTYP_1                   (0X2UL << HCCHAR_EPTYP_POS) 

#define HCCHAR_MC_POS                    (20U)                         
#define HCCHAR_MC_MSK                    (0X3UL << HCCHAR_MC_POS) 
#define HCCHAR_MC                        HCCHAR_MC_MSK         
#define HCCHAR_MC_0                      (0X1UL << HCCHAR_MC_POS) 
#define HCCHAR_MC_1                      (0X2UL << HCCHAR_MC_POS) 

#define HCCHAR_DAD_POS                   (22U)                         
#define HCCHAR_DAD_MSK                   (0X7FUL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD                       HCCHAR_DAD_MSK        
#define HCCHAR_DAD_0                     (0X01UL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD_1                     (0X02UL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD_2                     (0X04UL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD_3                     (0X08UL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD_4                     (0X10UL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD_5                     (0X20UL << HCCHAR_DAD_POS) 
#define HCCHAR_DAD_6                     (0X40UL << HCCHAR_DAD_POS) 
#define HCCHAR_ODDFRM_POS                (29U)                         
#define HCCHAR_ODDFRM_MSK                (0X1UL << HCCHAR_ODDFRM_POS) 
#define HCCHAR_ODDFRM                    HCCHAR_ODDFRM_MSK     
#define HCCHAR_CHDIS_POS                 (30U)                         
#define HCCHAR_CHDIS_MSK                 (0X1UL << HCCHAR_CHDIS_POS) 
#define HCCHAR_CHDIS                     HCCHAR_CHDIS_MSK      
#define HCCHAR_CHENA_POS                 (31U)                         
#define HCCHAR_CHENA_MSK                 (0X1UL << HCCHAR_CHENA_POS) 
#define HCCHAR_CHENA                     HCCHAR_CHENA_MSK      

/***********  BIT DEFINITION FOR USB_OTG::HCSPLT   ********************/
#define HCSPLT_PRTADDR_POS               (0U)                          
#define HCSPLT_PRTADDR_MSK               (0X7FUL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR                   HCSPLT_PRTADDR_MSK    
#define HCSPLT_PRTADDR_0                 (0X01UL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR_1                 (0X02UL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR_2                 (0X04UL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR_3                 (0X08UL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR_4                 (0X10UL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR_5                 (0X20UL << HCSPLT_PRTADDR_POS) 
#define HCSPLT_PRTADDR_6                 (0X40UL << HCSPLT_PRTADDR_POS) 

#define HCSPLT_HUBADDR_POS               (7U)                          
#define HCSPLT_HUBADDR_MSK               (0X7FUL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR                   HCSPLT_HUBADDR_MSK    
#define HCSPLT_HUBADDR_0                 (0X01UL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR_1                 (0X02UL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR_2                 (0X04UL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR_3                 (0X08UL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR_4                 (0X10UL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR_5                 (0X20UL << HCSPLT_HUBADDR_POS) 
#define HCSPLT_HUBADDR_6                 (0X40UL << HCSPLT_HUBADDR_POS) 

#define HCSPLT_XACTPOS_POS               (14U)                         
#define HCSPLT_XACTPOS_MSK               (0X3UL << HCSPLT_XACTPOS_POS) 
#define HCSPLT_XACTPOS                   HCSPLT_XACTPOS_MSK    
#define HCSPLT_XACTPOS_0                 (0X1UL << HCSPLT_XACTPOS_POS) 
#define HCSPLT_XACTPOS_1                 (0X2UL << HCSPLT_XACTPOS_POS) 
#define HCSPLT_COMPLSPLT_POS             (16U)                         
#define HCSPLT_COMPLSPLT_MSK             (0X1UL << HCSPLT_COMPLSPLT_POS) 
#define HCSPLT_COMPLSPLT                 HCSPLT_COMPLSPLT_MSK  
#define HCSPLT_SPLITEN_POS               (31U)                         
#define HCSPLT_SPLITEN_MSK               (0X1UL << HCSPLT_SPLITEN_POS) 
#define HCSPLT_SPLITEN                   HCSPLT_SPLITEN_MSK    

/********************  BIT DEFINITION FOR USB_OTG::HCINT   ********************/
#define HCINT_XFRC_POS                   (0U)                          
#define HCINT_XFRC_MSK                   (0X1UL << HCINT_XFRC_POS) 
#define HCINT_XFRC                       HCINT_XFRC_MSK        
#define HCINT_CHH_POS                    (1U)                          
#define HCINT_CHH_MSK                    (0X1UL << HCINT_CHH_POS) 
#define HCINT_CHH                        HCINT_CHH_MSK         
#define HCINT_AHBERR_POS                 (2U)                          
#define HCINT_AHBERR_MSK                 (0X1UL << HCINT_AHBERR_POS) 
#define HCINT_AHBERR                     HCINT_AHBERR_MSK      
#define HCINT_STALL_POS                  (3U)                          
#define HCINT_STALL_MSK                  (0X1UL << HCINT_STALL_POS) 
#define HCINT_STALL                      HCINT_STALL_MSK       
#define HCINT_NAK_POS                    (4U)                          
#define HCINT_NAK_MSK                    (0X1UL << HCINT_NAK_POS) 
#define HCINT_NAK                        HCINT_NAK_MSK         
#define HCINT_ACK_POS                    (5U)                          
#define HCINT_ACK_MSK                    (0X1UL << HCINT_ACK_POS) 
#define HCINT_ACK                        HCINT_ACK_MSK         
#define HCINT_NYET_POS                   (6U)                          
#define HCINT_NYET_MSK                   (0X1UL << HCINT_NYET_POS) 
#define HCINT_NYET                       HCINT_NYET_MSK        
#define HCINT_TXERR_POS                  (7U)                          
#define HCINT_TXERR_MSK                  (0X1UL << HCINT_TXERR_POS) 
#define HCINT_TXERR                      HCINT_TXERR_MSK       
#define HCINT_BBERR_POS                  (8U)                          
#define HCINT_BBERR_MSK                  (0X1UL << HCINT_BBERR_POS) 
#define HCINT_BBERR                      HCINT_BBERR_MSK       
#define HCINT_FRMOR_POS                  (9U)                          
#define HCINT_FRMOR_MSK                  (0X1UL << HCINT_FRMOR_POS) 
#define HCINT_FRMOR                      HCINT_FRMOR_MSK       
#define HCINT_DTERR_POS                  (10U)                         
#define HCINT_DTERR_MSK                  (0X1UL << HCINT_DTERR_POS) 
#define HCINT_DTERR                      HCINT_DTERR_MSK       

/*********  BIT DEFINITION FOR USB_OTG::DIEPINT   ********************/
#define DIEPINT_XFRC_POS                 (0U)                          
#define DIEPINT_XFRC_MSK                 (0X1UL << DIEPINT_XFRC_POS) 
#define DIEPINT_XFRC                     DIEPINT_XFRC_MSK      
#define DIEPINT_EPDISD_POS               (1U)                          
#define DIEPINT_EPDISD_MSK               (0X1UL << DIEPINT_EPDISD_POS) 
#define DIEPINT_EPDISD                   DIEPINT_EPDISD_MSK    
#define DIEPINT_AHBERR_POS               (2U)
#define DIEPINT_AHBERR_MSK               (0X1UL << DIEPINT_AHBERR_POS) 
#define DIEPINT_AHBERR                   DIEPINT_AHBERR_MSK   
#define DIEPINT_TOC_POS                  (3U)                          
#define DIEPINT_TOC_MSK                  (0X1UL << DIEPINT_TOC_POS) 
#define DIEPINT_TOC                      DIEPINT_TOC_MSK       
#define DIEPINT_ITTXFE_POS               (4U)                          
#define DIEPINT_ITTXFE_MSK               (0X1UL << DIEPINT_ITTXFE_POS) 
#define DIEPINT_ITTXFE                   DIEPINT_ITTXFE_MSK    
#define DIEPINT_INEPNM_POS               (5U)
#define DIEPINT_INEPNM_MSK               (0X1UL << DIEPINT_INEPNM_POS) 
#define DIEPINT_INEPNM                   DIEPINT_INEPNM_MSK   
#define DIEPINT_INEPNE_POS               (6U)                          
#define DIEPINT_INEPNE_MSK               (0X1UL << DIEPINT_INEPNE_POS) 
#define DIEPINT_INEPNE                   DIEPINT_INEPNE_MSK    
#define DIEPINT_TXFE_POS                 (7U)                          
#define DIEPINT_TXFE_MSK                 (0X1UL << DIEPINT_TXFE_POS) 
#define DIEPINT_TXFE                     DIEPINT_TXFE_MSK      
#define DIEPINT_TXFIFOUDRN_POS           (8U)                          
#define DIEPINT_TXFIFOUDRN_MSK           (0X1UL << DIEPINT_TXFIFOUDRN_POS) 
#define DIEPINT_TXFIFOUDRN               DIEPINT_TXFIFOUDRN_MSK 
#define DIEPINT_BNA_POS                  (9U)                          
#define DIEPINT_BNA_MSK                  (0X1UL << DIEPINT_BNA_POS) 
#define DIEPINT_BNA                      DIEPINT_BNA_MSK       
#define DIEPINT_PKTDRPSTS_POS            (11U)                         
#define DIEPINT_PKTDRPSTS_MSK            (0X1UL << DIEPINT_PKTDRPSTS_POS) 
#define DIEPINT_PKTDRPSTS                DIEPINT_PKTDRPSTS_MSK 
#define DIEPINT_BERR_POS                 (12U)                         
#define DIEPINT_BERR_MSK                 (0X1UL << DIEPINT_BERR_POS) 
#define DIEPINT_BERR                     DIEPINT_BERR_MSK      
#define DIEPINT_NAK_POS                  (13U)                         
#define DIEPINT_NAK_MSK                  (0X1UL << DIEPINT_NAK_POS) 
#define DIEPINT_NAK                      DIEPINT_NAK_MSK       

/********************  BIT DEFINITION FORHCINTMSK   ********************/
#define HCINTMSK_XFRCM_POS               (0U)                          
#define HCINTMSK_XFRCM_MSK               (0X1UL << HCINTMSK_XFRCM_POS) 
#define HCINTMSK_XFRCM                   HCINTMSK_XFRCM_MSK    
#define HCINTMSK_CHHM_POS                (1U)                          
#define HCINTMSK_CHHM_MSK                (0X1UL << HCINTMSK_CHHM_POS) 
#define HCINTMSK_CHHM                    HCINTMSK_CHHM_MSK     
#define HCINTMSK_AHBERR_POS              (2U)                          
#define HCINTMSK_AHBERR_MSK              (0X1UL << HCINTMSK_AHBERR_POS) 
#define HCINTMSK_AHBERR                  HCINTMSK_AHBERR_MSK   
#define HCINTMSK_STALLM_POS              (3U)                          
#define HCINTMSK_STALLM_MSK              (0X1UL << HCINTMSK_STALLM_POS) 
#define HCINTMSK_STALLM                  HCINTMSK_STALLM_MSK   
#define HCINTMSK_NAKM_POS                (4U)                          
#define HCINTMSK_NAKM_MSK                (0X1UL << HCINTMSK_NAKM_POS) 
#define HCINTMSK_NAKM                    HCINTMSK_NAKM_MSK     
#define HCINTMSK_ACKM_POS                (5U)                          
#define HCINTMSK_ACKM_MSK                (0X1UL << HCINTMSK_ACKM_POS) 
#define HCINTMSK_ACKM                    HCINTMSK_ACKM_MSK     
#define HCINTMSK_NYET_POS                (6U)                          
#define HCINTMSK_NYET_MSK                (0X1UL << HCINTMSK_NYET_POS) 
#define HCINTMSK_NYET                    HCINTMSK_NYET_MSK     
#define HCINTMSK_TXERRM_POS              (7U)                          
#define HCINTMSK_TXERRM_MSK              (0X1UL << HCINTMSK_TXERRM_POS) 
#define HCINTMSK_TXERRM                  HCINTMSK_TXERRM_MSK   
#define HCINTMSK_BBERRM_POS              (8U)                          
#define HCINTMSK_BBERRM_MSK              (0X1UL << HCINTMSK_BBERRM_POS) 
#define HCINTMSK_BBERRM                  HCINTMSK_BBERRM_MSK   
#define HCINTMSK_FRMORM_POS              (9U)                          
#define HCINTMSK_FRMORM_MSK              (0X1UL << HCINTMSK_FRMORM_POS) 
#define HCINTMSK_FRMORM                  HCINTMSK_FRMORM_MSK   
#define HCINTMSK_DTERRM_POS              (10U)                         
#define HCINTMSK_DTERRM_MSK              (0X1UL << HCINTMSK_DTERRM_POS) 
#define HCINTMSK_DTERRM                  HCINTMSK_DTERRM_MSK   

/*******  BIT DEFINITION FOR USB_OTG::DIEPTSIZ   ********************/
#define DIEPTSIZ_XFRSIZ_POS              (0U)                          
#define DIEPTSIZ_XFRSIZ_MSK              (0X7FFFFUL << DIEPTSIZ_XFRSIZ_POS) 
#define DIEPTSIZ_XFRSIZ                  DIEPTSIZ_XFRSIZ_MSK   
#define DIEPTSIZ_PKTCNT_POS              (19U)                         
#define DIEPTSIZ_PKTCNT_MSK              (0X3FFUL << DIEPTSIZ_PKTCNT_POS) 
#define DIEPTSIZ_PKTCNT                  DIEPTSIZ_PKTCNT_MSK   
#define DIEPTSIZ_MULCNT_POS              (29U)                         
#define DIEPTSIZ_MULCNT_MSK              (0X3UL << DIEPTSIZ_MULCNT_POS) 
#define DIEPTSIZ_MULCNT                  DIEPTSIZ_MULCNT_MSK   

/***********   BIT DEFINITION FOR USB_OTG::HCTSIZ   ********************/
#define HCTSIZ_XFRSIZ_POS                (0U)                          
#define HCTSIZ_XFRSIZ_MSK                (0X7FFFFUL << HCTSIZ_XFRSIZ_POS) 
#define HCTSIZ_XFRSIZ                    HCTSIZ_XFRSIZ_MSK     
#define HCTSIZ_PKTCNT_POS                (19U)                         
#define HCTSIZ_PKTCNT_MSK                (0X3FFUL << HCTSIZ_PKTCNT_POS) 
#define HCTSIZ_PKTCNT                    HCTSIZ_PKTCNT_MSK     
#define HCTSIZ_DOPING_POS                (31U)                         
#define HCTSIZ_DOPING_MSK                (0X1UL << HCTSIZ_DOPING_POS) 
#define HCTSIZ_DOPING                    HCTSIZ_DOPING_MSK     
#define HCTSIZ_DPID_POS                  (29U)                         
#define HCTSIZ_DPID_MSK                  (0X3UL << HCTSIZ_DPID_POS) 
#define HCTSIZ_DPID                      HCTSIZ_DPID_MSK       
#define HCTSIZ_DPID_0                    (0X1UL << HCTSIZ_DPID_POS) 
#define HCTSIZ_DPID_1                    (0X2UL << HCTSIZ_DPID_POS) 

/**********   BIT DEFINITION FOR USB_OTG::DIEPDMA   ********************/
#define DIEPDMA_DMAADDR_POS              (0U)                          
#define DIEPDMA_DMAADDR_MSK              (0XFFFFFFFFUL << DIEPDMA_DMAADDR_POS) 
#define DIEPDMA_DMAADDR                  DIEPDMA_DMAADDR_MSK   

/************   BIT DEFINITION FOR USB_OTG::HCDMA   ********************/
#define HCDMA_DMAADDR_POS                (0U)                          
#define HCDMA_DMAADDR_MSK                (0XFFFFFFFFUL << HCDMA_DMAADDR_POS) 
#define HCDMA_DMAADDR                    HCDMA_DMAADDR_MSK     

/**********   BIT DEFINITION FOR USB_OTG::DTXFSTS   ********************/
#define DTXFSTS_INEPTFSAV_POS            (0U)                          
#define DTXFSTS_INEPTFSAV_MSK            (0XFFFFUL << DTXFSTS_INEPTFSAV_POS) 
#define DTXFSTS_INEPTFSAV                DTXFSTS_INEPTFSAV_MSK 

/***********   BIT DEFINITION FOR USB_OTG::DIEPTXF   ********************/
#define DIEPTXF_INEPTXSA_POS             (0U)                          
#define DIEPTXF_INEPTXSA_MSK             (0XFFFFUL << DIEPTXF_INEPTXSA_POS) 
#define DIEPTXF_INEPTXSA                 DIEPTXF_INEPTXSA_MSK  
#define DIEPTXF_INEPTXFD_POS             (16U)                         
#define DIEPTXF_INEPTXFD_MSK             (0XFFFFUL << DIEPTXF_INEPTXFD_POS) 
#define DIEPTXF_INEPTXFD                 DIEPTXF_INEPTXFD_MSK  

/************  BIT DEFINITION FOR USB_OTG::DOEPCTL   ********************/
#define DOEPCTL_MPSIZ_POS                (0U)                          
#define DOEPCTL_MPSIZ_MSK                (0X7FFUL << DOEPCTL_MPSIZ_POS) 
#define DOEPCTL_MPSIZ                    DOEPCTL_MPSIZ_MSK     
#define DOEPCTL_USBAEP_POS               (15U)                         
#define DOEPCTL_USBAEP_MSK               (0X1UL << DOEPCTL_USBAEP_POS) 
#define DOEPCTL_USBAEP                   DOEPCTL_USBAEP_MSK    
#define DOEPCTL_NAKSTS_POS               (17U)                         
#define DOEPCTL_NAKSTS_MSK               (0X1UL << DOEPCTL_NAKSTS_POS) 
#define DOEPCTL_NAKSTS                   DOEPCTL_NAKSTS_MSK    
#define DOEPCTL_SD0PID_SEVNFRM_POS       (28U)                         
#define DOEPCTL_SD0PID_SEVNFRM_MSK       (0X1UL << DOEPCTL_SD0PID_SEVNFRM_POS) 
#define DOEPCTL_SD0PID_SEVNFRM           DOEPCTL_SD0PID_SEVNFRM_MSK 
#define DOEPCTL_SODDFRM_POS              (29U)                         
#define DOEPCTL_SODDFRM_MSK              (0X1UL << DOEPCTL_SODDFRM_POS) 
#define DOEPCTL_SODDFRM                  DOEPCTL_SODDFRM_MSK   
#define DOEPCTL_EPTYP_POS                (18U)                         
#define DOEPCTL_EPTYP_MSK                (0X3UL << DOEPCTL_EPTYP_POS) 
#define DOEPCTL_EPTYP                    DOEPCTL_EPTYP_MSK     
#define DOEPCTL_EPTYP_0                  (0X1UL << DOEPCTL_EPTYP_POS) 
#define DOEPCTL_EPTYP_1                  (0X2UL << DOEPCTL_EPTYP_POS) 
#define DOEPCTL_SNPM_POS                 (20U)                         
#define DOEPCTL_SNPM_MSK                 (0X1UL << DOEPCTL_SNPM_POS) 
#define DOEPCTL_SNPM                     DOEPCTL_SNPM_MSK      
#define DOEPCTL_STALL_POS                (21U)                         
#define DOEPCTL_STALL_MSK                (0X1UL << DOEPCTL_STALL_POS) 
#define DOEPCTL_STALL                    DOEPCTL_STALL_MSK     
#define DOEPCTL_CNAK_POS                 (26U)                         
#define DOEPCTL_CNAK_MSK                 (0X1UL << DOEPCTL_CNAK_POS) 
#define DOEPCTL_CNAK                     DOEPCTL_CNAK_MSK      
#define DOEPCTL_SNAK_POS                 (27U)                         
#define DOEPCTL_SNAK_MSK                 (0X1UL << DOEPCTL_SNAK_POS) 
#define DOEPCTL_SNAK                     DOEPCTL_SNAK_MSK      
#define DOEPCTL_EPDIS_POS                (30U)                         
#define DOEPCTL_EPDIS_MSK                (0X1UL << DOEPCTL_EPDIS_POS) 
#define DOEPCTL_EPDIS                    DOEPCTL_EPDIS_MSK     
#define DOEPCTL_EPENA_POS                (31U)                         
#define DOEPCTL_EPENA_MSK                (0X1UL << DOEPCTL_EPENA_POS) 
#define DOEPCTL_EPENA                    DOEPCTL_EPENA_MSK     

/************   BIT DEFINITION FOR USB_OTG::DOEPINT   ********************/
#define DOEPINT_XFRC_POS                 (0U)                          
#define DOEPINT_XFRC_MSK                 (0X1UL << DOEPINT_XFRC_POS) 
#define DOEPINT_XFRC                     DOEPINT_XFRC_MSK      
#define DOEPINT_EPDISD_POS               (1U)                          
#define DOEPINT_EPDISD_MSK               (0X1UL << DOEPINT_EPDISD_POS) 
#define DOEPINT_EPDISD                   DOEPINT_EPDISD_MSK    
#define DOEPINT_AHBERR_POS               (2U)
#define DOEPINT_AHBERR_MSK               (0X1UL << DOEPINT_AHBERR_POS) 
#define DOEPINT_AHBERR                   DOEPINT_AHBERR_MSK   
#define DOEPINT_STUP_POS                 (3U)                          
#define DOEPINT_STUP_MSK                 (0X1UL << DOEPINT_STUP_POS) 
#define DOEPINT_STUP                     DOEPINT_STUP_MSK      
#define DOEPINT_OTEPDIS_POS              (4U)                          
#define DOEPINT_OTEPDIS_MSK              (0X1UL << DOEPINT_OTEPDIS_POS) 
#define DOEPINT_OTEPDIS                  DOEPINT_OTEPDIS_MSK   
#define DOEPINT_OTEPSPR_POS              (5U)                          
#define DOEPINT_OTEPSPR_MSK              (0X1UL << DOEPINT_OTEPSPR_POS) 
#define DOEPINT_OTEPSPR                  DOEPINT_OTEPSPR_MSK   
#define DOEPINT_B2BSTUP_POS              (6U)                          
#define DOEPINT_B2BSTUP_MSK              (0X1UL << DOEPINT_B2BSTUP_POS) 
#define DOEPINT_B2BSTUP                  DOEPINT_B2BSTUP_MSK   
#define DOEPINT_OUTPKTERR_POS            (8U)
#define DOEPINT_OUTPKTERR_MSK            (0X1UL << DOEPINT_OUTPKTERR_POS) 
#define DOEPINT_OUTPKTERR                DOEPINT_OUTPKTERR_MSK   
#define DOEPINT_NAK_POS                  (13U)
#define DOEPINT_NAK_MSK                  (0X1UL << DOEPINT_NAK_POS) 
#define DOEPINT_NAK                      DOEPINT_NAK_MSK   
#define DOEPINT_NYET_POS                 (14U)                         
#define DOEPINT_NYET_MSK                 (0X1UL << DOEPINT_NYET_POS) 
#define DOEPINT_NYET                     DOEPINT_NYET_MSK      
#define DOEPINT_STPKTRX_POS              (15U)
#define DOEPINT_STPKTRX_MSK              (0X1UL << DOEPINT_STPKTRX_POS) 
#define DOEPINT_STPKTRX                  DOEPINT_STPKTRX_MSK   

/*********   BIT DEFINITION FOR USB_OTG::DOEPTSIZ    **************/
#define DOEPTSIZ_XFRSIZ_POS              (0U)                          
#define DOEPTSIZ_XFRSIZ_MSK              (0X7FFFFUL << DOEPTSIZ_XFRSIZ_POS) 
#define DOEPTSIZ_XFRSIZ                  DOEPTSIZ_XFRSIZ_MSK   
#define DOEPTSIZ_PKTCNT_POS              (19U)                         
#define DOEPTSIZ_PKTCNT_MSK              (0X3FFUL << DOEPTSIZ_PKTCNT_POS) 
#define DOEPTSIZ_PKTCNT                  DOEPTSIZ_PKTCNT_MSK   

#define DOEPTSIZ_STUPCNT_POS             (29U)                         
#define DOEPTSIZ_STUPCNT_MSK             (0X3UL << DOEPTSIZ_STUPCNT_POS) 
#define DOEPTSIZ_STUPCNT                 DOEPTSIZ_STUPCNT_MSK  
#define DOEPTSIZ_STUPCNT_0               (0X1UL << DOEPTSIZ_STUPCNT_POS) 
#define DOEPTSIZ_STUPCNT_1               (0X2UL << DOEPTSIZ_STUPCNT_POS) 

/********************  BIT DEFINITION FOR PCGCCTL   ********************/
#define PCGCCTL_STOPCLK_POS              (0U)                          
#define PCGCCTL_STOPCLK_MSK              (0X1UL << PCGCCTL_STOPCLK_POS) 
#define PCGCCTL_STOPCLK                  PCGCCTL_STOPCLK_MSK   
#define PCGCCTL_GATECLK_POS              (1U)                          
#define PCGCCTL_GATECLK_MSK              (0X1UL << PCGCCTL_GATECLK_POS) 
#define PCGCCTL_GATECLK                  PCGCCTL_GATECLK_MSK   
#define PCGCCTL_PHYSUSP_POS              (4U)                          
#define PCGCCTL_PHYSUSP_MSK              (0X1UL << PCGCCTL_PHYSUSP_POS) 
#define PCGCCTL_PHYSUSP                  PCGCCTL_PHYSUSP_MSK   

#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_USB_REGISTER_MASKS */