;===============================================================================
;
; Honestly not sure if DOXYGEN will process these tags 
; since they are in asm rather than C-style comments
;
;===============================================================================
;
; @file stm32f411_startup.s
; @author: Carl Mattatall
; @brief This file is thumb2 startup code for stm32f411 microcontroller.
; It does the following:
;    - Declares strong symbol existence for the vector table 
;
;    - DEFINES WEAK symbol existence for vector table so code LINKS
;      in the case that the programmer doesn't have a ISR defined in 
;      their C files
;
;    - Sets up the initial stack pointer and stack/heap in SRAM
;      (This is assuming the vector table gets placed by linker at
;      FLASH BASE)
;
;    - Configures the internal HSI RC oscillator (16MHz) as system clock
;
;    - Branches to SystemInit (which configures the VTAB and 
;            SCB registers in control unit of cortex processor)
;
;    - Branches to program entry (labelled as __iar_program_start)
;        -> If We are building with arm-none-eabi-gcc and arm-none-eabi-ld,
;           some changes for compatibility may be required to this file.
;
;    - __iar_program_start then starts the boostrap sequence which will
;      lead to the start of mainline call tree
;
; @note After Reset the Cortex-M4 processor is in Thread mode,
;       priority is Privileged, and the Stack is set to Main.
;
;===============================================================================

;       I dont know what this does 
;       but if I dont put it here IAR CSPY wont work
; 
        MODULE  ?cstartup

;;  Forward declaration of sections for linker
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start

;       This is defined in rimot_startup_code_sysInit.c
        EXTERN  SystemInit              

;       #####################################################################
;       ##                                                                 ##
;       ##                 THIS MUST BE __vector_table                     ##
;       ##           FOR IAR HARDWARE DEBUGGER (CSPY) TO WORK.             ##
;       ##                                                                 ##
;       ##         YOU CAN CALL IT WHATEVER YOU WANT IF YOU'RE             ##
;       ##                 USING GDB SYMBOL-BASED DEBUG                    ##
;       #####################################################################
        PUBLIC  __vector_table          

        DATA
__vector_table

;               Initial Stack Ptr Address
        DCD     sfe(CSTACK)               

;#############################
;##      CORTEX EXCEPTIONS  ##
;#############################

;      Location of PC at Bootstrap
        DCD     Reset_Handler             
  
;       Non Maskable Interrupt
        DCD     NMI_Handler               

;       Hard Fault Handler
        DCD     HardFault_Handler 

                             
        DCD     MemManage_Handler         ; MPU Fault Handler
        DCD     BusFault_Handler          ; Bus Fault Handler
        DCD     UsageFault_Handler        ; Usage Fault Handler

        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved

        DCD     SVC_Handler               ; SVCall Handler
        DCD     DebugMon_Handler          ; Debug Monitor Handler
        
        DCD     0 ; Reserved

        DCD     PendSV_Handler            ; PendSV Handler
        DCD     SysTick_Handler           ; SysTick Handler

;               #################################
;               ##  MCU PERIPHERAL INTERRUPTS  ##
;               #################################

;       Window WatchDog Interrupt
        DCD     WWDG_IRQHandler                   

;       PVD through EXTI Line detection
        DCD     PVD_IRQHandler                    

;       Tamper and TimeStamps through the EXTI line
        DCD     TAMP_STAMP_IRQHandler            

;       RTC Wakeup through the EXTI line
        DCD     RTC_WKUP_IRQHandler               

;       Flash Controller Interupt
        DCD     FLASH_IRQHandler                  ; FLASH

;       RCC Interrupt
        DCD     RCC_IRQHandler                    

;       External GPIO Interrupts Line[0:4]s
        DCD     EXTI0_IRQHandler                  
        DCD     EXTI1_IRQHandler                  
        DCD     EXTI2_IRQHandler                  
        DCD     EXTI3_IRQHandler                  
        DCD     EXTI4_IRQHandler                  

;       DMA1 stream interrupts
        DCD     DMA1_Stream0_IRQHandler           ; DMA1 Stream 0
        DCD     DMA1_Stream1_IRQHandler           ; DMA1 Stream 1
        DCD     DMA1_Stream2_IRQHandler           ; DMA1 Stream 2
        DCD     DMA1_Stream3_IRQHandler           ; DMA1 Stream 3
        DCD     DMA1_Stream4_IRQHandler           ; DMA1 Stream 4
        DCD     DMA1_Stream5_IRQHandler           ; DMA1 Stream 5
        DCD     DMA1_Stream6_IRQHandler           ; DMA1 Stream 6

;       ADC Interrupt
        DCD     ADC_IRQHandler 


        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved

;       External GPIO Interrupts Line[9:5]s
        DCD     EXTI9_5_IRQHandler                

;       TIM1 Break and TIM9
        DCD     TIM1_BRK_TIM9_IRQHandler          

;       TIM1 Update and TIM10
        DCD     TIM1_UP_TIM10_IRQHandler          

;       TIM1 Trigger and Commutation and TIM11
        DCD     TIM1_TRG_COM_TIM11_IRQHandler 

;       TIM1 Capture Compare
        DCD     TIM1_CC_IRQHandler                

;       Timer2 Generic Interrupt
        DCD     TIM2_IRQHandler                  

;       Timer3 Generic Interrupt
        DCD     TIM3_IRQHandler                  

;       Timer 4 Generic Interrupt
        DCD     TIM4_IRQHandler                

;       I2C1 Event Interrupt
        DCD     I2C1_EV_IRQHandler               

;       I2C1 Error Interrupt
        DCD     I2C1_ER_IRQHandler                

;       I2C2 Event Interrupt
        DCD     I2C2_EV_IRQHandler                

;       I2C2 Error Interrupt
        DCD     I2C2_ER_IRQHandler               

;       SPI1 Generic ISR
        DCD     SPI1_IRQHandler                  

;       SPI2 Generic ISR
        DCD     SPI2_IRQHandler                   

;       USART1 Generic ISR
        DCD     USART1_IRQHandler                

;       USART2 Generic ISR.
;
;       This is important because USART2
;       is one of the ways to access
;       or burn the embedded bootloader
;       into system memory block
        DCD     USART2_IRQHandler                

        DCD     0 ; Reserved

;       External GPIO Interrupt Line[15:10]s
        DCD     EXTI15_10_IRQHandler           

;       RTC Alarm (A and B) through EXTI Line
        DCD     RTC_Alarm_IRQHandler     

;       USB OTG FS Wakeup (VBUS Triggered) through EXTI line
        DCD     OTG_FS_WKUP_IRQHandler            


        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved

;               DMA1 Stream7 ISR
        DCD     DMA1_Stream7_IRQHandler   


        DCD     0 ; Reserved

;       SDIO Generic ISR
        DCD     SDIO_IRQHandler        

;       Timer 5 Generic ISR           
        DCD     TIM5_IRQHandler                   

;       SPI3 Generic ISR
        DCD     SPI3_IRQHandler                  

        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved

;       DMA2 Stream[0:4] ISR
        DCD     DMA2_Stream0_IRQHandler
        DCD     DMA2_Stream1_IRQHandler
        DCD     DMA2_Stream2_IRQHandler
        DCD     DMA2_Stream3_IRQHandler
        DCD     DMA2_Stream4_IRQHandler


        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved

;       USB OTG FS GLOBAL INTERRUPT
        DCD     OTG_FS_IRQHandler          

;       DMA2 Stream[5:7] ISR
        DCD     DMA2_Stream5_IRQHandler           
        DCD     DMA2_Stream6_IRQHandler           
        DCD     DMA2_Stream7_IRQHandler     

;       USART6 Generic ISR
        DCD     USART6_IRQHandler 

;       I2C3 Event Interrupt                
        DCD     I2C3_EV_IRQHandler                

;       I2C3 Error ISR
        DCD     I2C3_ER_IRQHandler

        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved
        DCD     0 ; Reserved

;       Floating Point Unit Exception
        DCD     FPU_IRQHandler

        DCD     0 ; Reserved
        DCD     0 ; Reserved

;       SPI4 Generic ISR
        DCD     SPI4_IRQHandler   

;       SPI5 Generic ISR                
        DCD     SPI5_IRQHandler

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

;; THESE ARE THE "WEAK" SYMBOLS SO THAT IF FOR 
;; SOME REASON THE PROGRAMMER DELETES AN ISR FUNCTION
;; DELCARED IN THE ABOVE TABLE, THE CODE STILL COMPILES.
;;
        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler

        LDR     R0, = SystemInit
        BLX     R0  ; Branch with link and execute 
        LDR     R0, =__iar_program_start
        BX      R0  ; Branch and execute (this will lead to mainline call tree)

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG_IRQHandler  
        B WWDG_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler  
        B PVD_IRQHandler

        PUBWEAK TAMP_STAMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TAMP_STAMP_IRQHandler  
        B TAMP_STAMP_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_WKUP_IRQHandler  
        B RTC_WKUP_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FLASH_IRQHandler  
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCC_IRQHandler  
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI0_IRQHandler  
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI1_IRQHandler  
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI2_IRQHandler  
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI4_IRQHandler  
        B EXTI4_IRQHandler

        PUBWEAK DMA1_Stream0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream0_IRQHandler  
        B DMA1_Stream0_IRQHandler

        PUBWEAK DMA1_Stream1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream1_IRQHandler  
        B DMA1_Stream1_IRQHandler

        PUBWEAK DMA1_Stream2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream2_IRQHandler  
        B DMA1_Stream2_IRQHandler

        PUBWEAK DMA1_Stream3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream3_IRQHandler  
        B DMA1_Stream3_IRQHandler

        PUBWEAK DMA1_Stream4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream4_IRQHandler  
        B DMA1_Stream4_IRQHandler

        PUBWEAK DMA1_Stream5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream5_IRQHandler  
        B DMA1_Stream5_IRQHandler

        PUBWEAK DMA1_Stream6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream6_IRQHandler  
        B DMA1_Stream6_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler  
        B ADC_IRQHandler

        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI9_5_IRQHandler  
        B EXTI9_5_IRQHandler

        PUBWEAK TIM1_BRK_TIM9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_BRK_TIM9_IRQHandler  
        B TIM1_BRK_TIM9_IRQHandler

        PUBWEAK TIM1_UP_TIM10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_UP_TIM10_IRQHandler  
        B TIM1_UP_TIM10_IRQHandler

        PUBWEAK TIM1_TRG_COM_TIM11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_TRG_COM_TIM11_IRQHandler  
        B TIM1_TRG_COM_TIM11_IRQHandler
        
        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM1_CC_IRQHandler  
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM2_IRQHandler  
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM3_IRQHandler  
        B TIM3_IRQHandler

        PUBWEAK TIM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM4_IRQHandler  
        B TIM4_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EV_IRQHandler  
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ER_IRQHandler  
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EV_IRQHandler  
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ER_IRQHandler  
        B I2C2_ER_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler  
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler  
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler  
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler  
        B USART2_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI15_10_IRQHandler  
        B EXTI15_10_IRQHandler

        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_Alarm_IRQHandler  
        B RTC_Alarm_IRQHandler

        PUBWEAK OTG_FS_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_FS_WKUP_IRQHandler  
        B OTG_FS_WKUP_IRQHandler

        PUBWEAK DMA1_Stream7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Stream7_IRQHandler  
        B DMA1_Stream7_IRQHandler

        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_IRQHandler  
        B SDIO_IRQHandler

        PUBWEAK TIM5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIM5_IRQHandler  
        B TIM5_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_IRQHandler  
        B SPI3_IRQHandler

        PUBWEAK DMA2_Stream0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream0_IRQHandler  
        B DMA2_Stream0_IRQHandler

        PUBWEAK DMA2_Stream1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream1_IRQHandler  
        B DMA2_Stream1_IRQHandler

        PUBWEAK DMA2_Stream2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream2_IRQHandler  
        B DMA2_Stream2_IRQHandler

        PUBWEAK DMA2_Stream3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream3_IRQHandler  
        B DMA2_Stream3_IRQHandler

        PUBWEAK DMA2_Stream4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream4_IRQHandler  
        B DMA2_Stream4_IRQHandler

        PUBWEAK OTG_FS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_FS_IRQHandler  
        B OTG_FS_IRQHandler

        PUBWEAK DMA2_Stream5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream5_IRQHandler  
        B DMA2_Stream5_IRQHandler

        PUBWEAK DMA2_Stream6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream6_IRQHandler  
        B DMA2_Stream6_IRQHandler

        PUBWEAK DMA2_Stream7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Stream7_IRQHandler  
        B DMA2_Stream7_IRQHandler

        PUBWEAK USART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART6_IRQHandler  
        B USART6_IRQHandler

        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EV_IRQHandler  
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ER_IRQHandler  
        B I2C3_ER_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler  
        B FPU_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI4_IRQHandler  
        B SPI4_IRQHandler
		
        PUBWEAK SPI5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI5_IRQHandler  
        B SPI5_IRQHandler
        
        END
