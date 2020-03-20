/**
 * @file usb_otg.c
 * @author Carl Mattatall
 * @brief  The purpose of this module was to implement a custom (lower power,
 *  faster, more efficient) Driver for the USB OTG Peripheral since it will
 *  consume the majority of the system power.
 * 
 *  I have copied sources references from 
 *  stm32_ll_usb and stm32_HAL_PCD.c below to use as a reference.
 *  For now, I am using the HAL Layer because this entire firmware project is
 *  actually a 2 year long endeavor and I don't have time to write efficient
 *  low-level drivers by hand. Explaining to management that baremetal firmware 
 *  dev takes eons before actually having any result is a waste of time.
 * @version 0.1
 * @date 2020-03-20
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include <stdint.h>

#include "usb_otg.h"


#if 0
/**
  ******************************************************************************
  * @file    stm32f4xx_hal_pcd.c
  * @author  MCD Application Team
  * @brief   PCD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      The PCD HAL driver can be used as follows:

     (#) Declare a PCD_HandleTypeDef handle structure, for example:
         PCD_HandleTypeDef  hpcd;

     (#) Fill parameters of Init structure in HCD handle

     (#) Call HAL_PCD_Init() API to initialize the PCD peripheral (Core, Device core, ...)

     (#) Initialize the PCD low level resources through the HAL_PCD_MspInit() API:
         (##) Enable the PCD/USB Low Level interface clock using
              (+++) __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
              (+++) __HAL_RCC_USB_OTG_HS_CLK_ENABLE(); (For High Speed Mode)

         (##) Initialize the related GPIO clocks
         (##) Configure PCD pin-out
         (##) Configure PCD NVIC interrupt

     (#)Associate the Upper USB device stack to the HAL PCD Driver:
         (##) hpcd.pData = pdev;

     (#)Enable PCD transmission and reception:
         (##) HAL_PCD_Start();

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup PCD PCD
  * @brief PCD HAL module driver
  * @{
  */

#ifdef HAL_PCD_MODULE_ENABLED

#if defined (USB_OTG_FS) || defined (USB_OTG_HS)

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup PCD_Private_Macros PCD Private Macros
  * @{
  */
#define PCD_MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define PCD_MAX(a, b)  (((a) > (b)) ? (a) : (b))
/**
  * @}
  */

/* Private functions prototypes ----------------------------------------------*/
/** @defgroup PCD_Private_Functions PCD Private Functions
  * @{
  */
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
static HAL_StatusTypeDef PCD_WriteEmptyTxFifo(PCD_HandleTypeDef *hpcd, uint32_t epnum);
static HAL_StatusTypeDef PCD_EP_OutXfrComplete_int(PCD_HandleTypeDef *hpcd, uint32_t epnum);
static HAL_StatusTypeDef PCD_EP_OutSetupPacket_int(PCD_HandleTypeDef *hpcd, uint32_t epnum);
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PCD_Exported_Functions PCD Exported Functions
  * @{
  */

/** @defgroup PCD_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the PCD according to the specified
  *         parameters in the PCD_InitTypeDef and initialize the associated handle.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Init(PCD_HandleTypeDef *hpcd)
{
  USB_OTG_GlobalTypeDef *USBx;
  uint8_t i;

  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PCD_ALL_INSTANCE(hpcd->Instance));

  USBx = hpcd->Instance;

  if (hpcd->State == HAL_PCD_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hpcd->Lock = HAL_UNLOCKED;

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
    hpcd->SOFCallback = HAL_PCD_SOFCallback;
    hpcd->SetupStageCallback = HAL_PCD_SetupStageCallback;
    hpcd->ResetCallback = HAL_PCD_ResetCallback;
    hpcd->SuspendCallback = HAL_PCD_SuspendCallback;
    hpcd->ResumeCallback = HAL_PCD_ResumeCallback;
    hpcd->ConnectCallback = HAL_PCD_ConnectCallback;
    hpcd->DisconnectCallback = HAL_PCD_DisconnectCallback;
    hpcd->DataOutStageCallback = HAL_PCD_DataOutStageCallback;
    hpcd->DataInStageCallback = HAL_PCD_DataInStageCallback;
    hpcd->ISOOUTIncompleteCallback = HAL_PCD_ISOOUTIncompleteCallback;
    hpcd->ISOINIncompleteCallback = HAL_PCD_ISOINIncompleteCallback;
    hpcd->LPMCallback = HAL_PCDEx_LPM_Callback;
    hpcd->BCDCallback = HAL_PCDEx_BCD_Callback;

    if (hpcd->MspInitCallback == NULL)
    {
      hpcd->MspInitCallback = HAL_PCD_MspInit;
    }

    /* Init the low level hardware */
    hpcd->MspInitCallback(hpcd);
#else
    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_PCD_MspInit(hpcd);
#endif /* (USE_HAL_PCD_REGISTER_CALLBACKS) */
  }

  hpcd->State = HAL_PCD_STATE_BUSY;

  /* Disable DMA mode for FS instance */
  if ((USBx->CID & (0x1U << 8)) == 0U)
  {
    hpcd->Init.dma_enable = 0U;
  }

  /* Disable the Interrupts */
  __HAL_PCD_DISABLE(hpcd);

  /*Init the Core (common init.) */
  if (USB_CoreInit(hpcd->Instance, hpcd->Init) != HAL_OK)
  {
    hpcd->State = HAL_PCD_STATE_ERROR;
    return HAL_ERROR;
  }

  /* Force Device Mode*/
  (void)USB_SetCurrentMode(hpcd->Instance, USB_DEVICE_MODE);

  /* Init endpoints structures */
  for (i = 0U; i < hpcd->Init.dev_endpoints; i++)
  {
    /* Init ep structure */
    hpcd->IN_ep[i].is_in = 1U;
    hpcd->IN_ep[i].num = i;
    hpcd->IN_ep[i].tx_fifo_num = i;
    /* Control until ep is activated */
    hpcd->IN_ep[i].type = EP_TYPE_CTRL;
    hpcd->IN_ep[i].maxpacket = 0U;
    hpcd->IN_ep[i].xfer_buff = 0U;
    hpcd->IN_ep[i].xfer_len = 0U;
  }

  for (i = 0U; i < hpcd->Init.dev_endpoints; i++)
  {
    hpcd->OUT_ep[i].is_in = 0U;
    hpcd->OUT_ep[i].num = i;
    /* Control until ep is activated */
    hpcd->OUT_ep[i].type = EP_TYPE_CTRL;
    hpcd->OUT_ep[i].maxpacket = 0U;
    hpcd->OUT_ep[i].xfer_buff = 0U;
    hpcd->OUT_ep[i].xfer_len = 0U;
  }

  /* Init Device */
  if (USB_DevInit(hpcd->Instance, hpcd->Init) != HAL_OK)
  {
    hpcd->State = HAL_PCD_STATE_ERROR;
    return HAL_ERROR;
  }

  hpcd->USB_Address = 0U;
  hpcd->State = HAL_PCD_STATE_READY;
  #if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
  /* Activate LPM */
  if (hpcd->Init.lpm_enable == 1U)
  {
    (void)HAL_PCDEx_ActivateLPM(hpcd);
  }
  #endif /* defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx) */
  (void)USB_DevDisconnect(hpcd->Instance);

  return HAL_OK;
}

/**
  * @brief  DeInitializes the PCD peripheral.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DeInit(PCD_HandleTypeDef *hpcd)
{
  /* Check the PCD handle allocation */
  if (hpcd == NULL)
  {
    return HAL_ERROR;
  }

  hpcd->State = HAL_PCD_STATE_BUSY;

  /* Stop Device */
  (void)HAL_PCD_Stop(hpcd);

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
  if (hpcd->MspDeInitCallback == NULL)
  {
    hpcd->MspDeInitCallback = HAL_PCD_MspDeInit; /* Legacy weak MspDeInit  */
  }

  /* DeInit the low level hardware */
  hpcd->MspDeInitCallback(hpcd);
#else
  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HAL_PCD_MspDeInit(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

  hpcd->State = HAL_PCD_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitializes PCD MSP.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_MspDeInit could be implemented in the user file
   */
}

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User USB PCD Callback
  *         To be used instead of the weak predefined callback
  * @param  hpcd USB PCD handle
  * @param  CallbackID ID of the callback to be registered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_PCD_SOF_CB_ID USB PCD SOF callback ID
  *          @arg @ref HAL_PCD_SETUPSTAGE_CB_ID USB PCD Setup callback ID
  *          @arg @ref HAL_PCD_RESET_CB_ID USB PCD Reset callback ID
  *          @arg @ref HAL_PCD_SUSPEND_CB_ID USB PCD Suspend callback ID
  *          @arg @ref HAL_PCD_RESUME_CB_ID USB PCD Resume callback ID
  *          @arg @ref HAL_PCD_CONNECT_CB_ID USB PCD Connect callback ID
  *          @arg @ref HAL_PCD_DISCONNECT_CB_ID OTG PCD Disconnect callback ID
  *          @arg @ref HAL_PCD_MSPINIT_CB_ID MspDeInit callback ID
  *          @arg @ref HAL_PCD_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param  pCallback pointer to the Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterCallback(PCD_HandleTypeDef *hpcd, HAL_PCD_CallbackIDTypeDef CallbackID, pPCD_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;
    return HAL_ERROR;
  }
  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_PCD_SOF_CB_ID :
        hpcd->SOFCallback = pCallback;
        break;

      case HAL_PCD_SETUPSTAGE_CB_ID :
        hpcd->SetupStageCallback = pCallback;
        break;

      case HAL_PCD_RESET_CB_ID :
        hpcd->ResetCallback = pCallback;
        break;

      case HAL_PCD_SUSPEND_CB_ID :
        hpcd->SuspendCallback = pCallback;
        break;

      case HAL_PCD_RESUME_CB_ID :
        hpcd->ResumeCallback = pCallback;
        break;

      case HAL_PCD_CONNECT_CB_ID :
        hpcd->ConnectCallback = pCallback;
        break;

      case HAL_PCD_DISCONNECT_CB_ID :
        hpcd->DisconnectCallback = pCallback;
        break;

      case HAL_PCD_MSPINIT_CB_ID :
        hpcd->MspInitCallback = pCallback;
        break;

      case HAL_PCD_MSPDEINIT_CB_ID :
        hpcd->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hpcd->State == HAL_PCD_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_PCD_MSPINIT_CB_ID :
        hpcd->MspInitCallback = pCallback;
        break;

      case HAL_PCD_MSPDEINIT_CB_ID :
        hpcd->MspDeInitCallback = pCallback;
        break;

      default :
        /* Update the error code */
        hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;
        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);
  return status;
}

/**
  * @brief  Unregister an USB PCD Callback
  *         USB PCD callabck is redirected to the weak predefined callback
  * @param  hpcd USB PCD handle
  * @param  CallbackID ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_PCD_SOF_CB_ID USB PCD SOF callback ID
  *          @arg @ref HAL_PCD_SETUPSTAGE_CB_ID USB PCD Setup callback ID
  *          @arg @ref HAL_PCD_RESET_CB_ID USB PCD Reset callback ID
  *          @arg @ref HAL_PCD_SUSPEND_CB_ID USB PCD Suspend callback ID
  *          @arg @ref HAL_PCD_RESUME_CB_ID USB PCD Resume callback ID
  *          @arg @ref HAL_PCD_CONNECT_CB_ID USB PCD Connect callback ID
  *          @arg @ref HAL_PCD_DISCONNECT_CB_ID OTG PCD Disconnect callback ID
  *          @arg @ref HAL_PCD_MSPINIT_CB_ID MspDeInit callback ID
  *          @arg @ref HAL_PCD_MSPDEINIT_CB_ID MspDeInit callback ID
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterCallback(PCD_HandleTypeDef *hpcd, HAL_PCD_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  /* Setup Legacy weak Callbacks  */
  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_PCD_SOF_CB_ID :
        hpcd->SOFCallback = HAL_PCD_SOFCallback;
        break;

      case HAL_PCD_SETUPSTAGE_CB_ID :
        hpcd->SetupStageCallback = HAL_PCD_SetupStageCallback;
        break;

      case HAL_PCD_RESET_CB_ID :
        hpcd->ResetCallback = HAL_PCD_ResetCallback;
        break;

      case HAL_PCD_SUSPEND_CB_ID :
        hpcd->SuspendCallback = HAL_PCD_SuspendCallback;
        break;

      case HAL_PCD_RESUME_CB_ID :
        hpcd->ResumeCallback = HAL_PCD_ResumeCallback;
        break;

      case HAL_PCD_CONNECT_CB_ID :
        hpcd->ConnectCallback = HAL_PCD_ConnectCallback;
        break;

      case HAL_PCD_DISCONNECT_CB_ID :
        hpcd->DisconnectCallback = HAL_PCD_DisconnectCallback;
        break;

      case HAL_PCD_MSPINIT_CB_ID :
        hpcd->MspInitCallback = HAL_PCD_MspInit;
        break;

      case HAL_PCD_MSPDEINIT_CB_ID :
        hpcd->MspDeInitCallback = HAL_PCD_MspDeInit;
        break;

      default :
        /* Update the error code */
        hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hpcd->State == HAL_PCD_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_PCD_MSPINIT_CB_ID :
        hpcd->MspInitCallback = HAL_PCD_MspInit;
        break;

      case HAL_PCD_MSPDEINIT_CB_ID :
        hpcd->MspDeInitCallback = HAL_PCD_MspDeInit;
        break;

      default :
        /* Update the error code */
        hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

        /* Return error status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);
  return status;
}

/**
  * @brief  Register USB PCD Data OUT Stage Callback
  *         To be used instead of the weak HAL_PCD_DataOutStageCallback() predefined callback
  * @param  hpcd PCD handle
  * @param  pCallback pointer to the USB PCD Data OUT Stage Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterDataOutStageCallback(PCD_HandleTypeDef *hpcd, pPCD_DataOutStageCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->DataOutStageCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  UnRegister the USB PCD Data OUT Stage Callback
  *         USB PCD Data OUT Stage Callback is redirected to the weak HAL_PCD_DataOutStageCallback() predefined callback
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterDataOutStageCallback(PCD_HandleTypeDef *hpcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->DataOutStageCallback = HAL_PCD_DataOutStageCallback; /* Legacy weak DataOutStageCallback  */
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  Register USB PCD Data IN Stage Callback
  *         To be used instead of the weak HAL_PCD_DataInStageCallback() predefined callback
  * @param  hpcd PCD handle
  * @param  pCallback pointer to the USB PCD Data IN Stage Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterDataInStageCallback(PCD_HandleTypeDef *hpcd, pPCD_DataInStageCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->DataInStageCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  UnRegister the USB PCD Data IN Stage Callback
  *         USB PCD Data OUT Stage Callback is redirected to the weak HAL_PCD_DataInStageCallback() predefined callback
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterDataInStageCallback(PCD_HandleTypeDef *hpcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->DataInStageCallback = HAL_PCD_DataInStageCallback; /* Legacy weak DataInStageCallback  */
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  Register USB PCD Iso OUT incomplete Callback
  *         To be used instead of the weak HAL_PCD_ISOOUTIncompleteCallback() predefined callback
  * @param  hpcd PCD handle
  * @param  pCallback pointer to the USB PCD Iso OUT incomplete Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterIsoOutIncpltCallback(PCD_HandleTypeDef *hpcd, pPCD_IsoOutIncpltCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->ISOOUTIncompleteCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  UnRegister the USB PCD Iso OUT incomplete Callback
  *         USB PCD Iso OUT incomplete Callback is redirected to the weak HAL_PCD_ISOOUTIncompleteCallback() predefined callback
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterIsoOutIncpltCallback(PCD_HandleTypeDef *hpcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->ISOOUTIncompleteCallback = HAL_PCD_ISOOUTIncompleteCallback; /* Legacy weak ISOOUTIncompleteCallback  */
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  Register USB PCD Iso IN incomplete Callback
  *         To be used instead of the weak HAL_PCD_ISOINIncompleteCallback() predefined callback
  * @param  hpcd PCD handle
  * @param  pCallback pointer to the USB PCD Iso IN incomplete Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterIsoInIncpltCallback(PCD_HandleTypeDef *hpcd, pPCD_IsoInIncpltCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->ISOINIncompleteCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  UnRegister the USB PCD Iso IN incomplete Callback
  *         USB PCD Iso IN incomplete Callback is redirected to the weak HAL_PCD_ISOINIncompleteCallback() predefined callback
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterIsoInIncpltCallback(PCD_HandleTypeDef *hpcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->ISOINIncompleteCallback = HAL_PCD_ISOINIncompleteCallback; /* Legacy weak ISOINIncompleteCallback  */
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  Register USB PCD BCD Callback
  *         To be used instead of the weak HAL_PCDEx_BCD_Callback() predefined callback
  * @param  hpcd PCD handle
  * @param  pCallback pointer to the USB PCD BCD Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterBcdCallback(PCD_HandleTypeDef *hpcd, pPCD_BcdCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->BCDCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  UnRegister the USB PCD BCD Callback
  *         USB BCD Callback is redirected to the weak HAL_PCDEx_BCD_Callback() predefined callback
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterBcdCallback(PCD_HandleTypeDef *hpcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->BCDCallback = HAL_PCDEx_BCD_Callback; /* Legacy weak HAL_PCDEx_BCD_Callback  */
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  Register USB PCD LPM Callback
  *         To be used instead of the weak HAL_PCDEx_LPM_Callback() predefined callback
  * @param  hpcd PCD handle
  * @param  pCallback pointer to the USB PCD LPM Callback function
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_RegisterLpmCallback(PCD_HandleTypeDef *hpcd, pPCD_LpmCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->LPMCallback = pCallback;
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}

/**
  * @brief  UnRegister the USB PCD LPM Callback
  *         USB LPM Callback is redirected to the weak HAL_PCDEx_LPM_Callback() predefined callback
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_UnRegisterLpmCallback(PCD_HandleTypeDef *hpcd)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hpcd);

  if (hpcd->State == HAL_PCD_STATE_READY)
  {
    hpcd->LPMCallback = HAL_PCDEx_LPM_Callback; /* Legacy weak HAL_PCDEx_LPM_Callback  */
  }
  else
  {
    /* Update the error code */
    hpcd->ErrorCode |= HAL_PCD_ERROR_INVALID_CALLBACK;

    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hpcd);

  return status;
}
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group2 Input and Output operation functions
 *  @brief   Data transfers functions
 *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the PCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the USB device
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd)
{
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
  USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

  __HAL_LOCK(hpcd);
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
  if ((hpcd->Init.battery_charging_enable == 1U) &&
      (hpcd->Init.phy_itface != USB_OTG_ULPI_PHY))
  {
    /* Enable USB Transceiver */
    USBx->GCCFG |= USB_OTG_GCCFG_PWRDWN;
  }
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
  (void)USB_DevConnect(hpcd->Instance);
  __HAL_PCD_ENABLE(hpcd);
  __HAL_UNLOCK(hpcd);
  return HAL_OK;
}

/**
  * @brief  Stop the USB device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Stop(PCD_HandleTypeDef *hpcd)
{
  __HAL_LOCK(hpcd);
  __HAL_PCD_DISABLE(hpcd);

  if (USB_StopDevice(hpcd->Instance) != HAL_OK)
  {
    __HAL_UNLOCK(hpcd);
    return HAL_ERROR;
  }

  (void)USB_DevDisconnect(hpcd->Instance);
  __HAL_UNLOCK(hpcd);

  return HAL_OK;
}
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
/**
  * @brief  Handles PCD interrupt request.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
void HAL_PCD_IRQHandler(PCD_HandleTypeDef *hpcd)
{
  USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t i, ep_intr, epint, epnum;
  uint32_t fifoemptymsk, temp;
  USB_OTG_EPTypeDef *ep;

  /* ensure that we are in device mode */
  if (USB_GetMode(hpcd->Instance) == USB_OTG_MODE_DEVICE)
  {
    /* avoid spurious interrupt */
    if (__HAL_PCD_IS_INVALID_INTERRUPT(hpcd))
    {
      return;
    }

    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_MMIS))
    {
      /* incorrect mode, acknowledge the interrupt */
      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_MMIS);
    }

    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_OEPINT))
    {
      epnum = 0U;

      /* Read in the device interrupt bits */
      ep_intr = USB_ReadDevAllOutEpInterrupt(hpcd->Instance);

      while (ep_intr != 0U)
      {
        if ((ep_intr & 0x1U) != 0U)
        {
          epint = USB_ReadDevOutEPInterrupt(hpcd->Instance, (uint8_t)epnum);

          if ((epint & USB_OTG_DOEPINT_XFRC) == USB_OTG_DOEPINT_XFRC)
          {
            CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_XFRC);
            (void)PCD_EP_OutXfrComplete_int(hpcd, epnum);
          }

          if ((epint & USB_OTG_DOEPINT_STUP) == USB_OTG_DOEPINT_STUP)
          {
            /* Class B setup phase done for previous decoded setup */
            (void)PCD_EP_OutSetupPacket_int(hpcd, epnum);
            CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STUP);
          }

          if ((epint & USB_OTG_DOEPINT_OTEPDIS) == USB_OTG_DOEPINT_OTEPDIS)
          {
            CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_OTEPDIS);
          }

          /* Clear Status Phase Received interrupt */
          if ((epint & USB_OTG_DOEPINT_OTEPSPR) == USB_OTG_DOEPINT_OTEPSPR)
          {
            if (hpcd->Init.dma_enable == 1U)
            {
              (void)USB_EP0_OutStart(hpcd->Instance, 1U, (uint8_t *)hpcd->Setup);
            }
            CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_OTEPSPR);
          }

          /* Clear OUT NAK interrupt */
          if ((epint & USB_OTG_DOEPINT_NAK) == USB_OTG_DOEPINT_NAK)
          {
            CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_NAK);
          }
        }
        epnum++;
        ep_intr >>= 1U;
      }
    }

    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_IEPINT))
    {
      /* Read in the device interrupt bits */
      ep_intr = USB_ReadDevAllInEpInterrupt(hpcd->Instance);

      epnum = 0U;

      while (ep_intr != 0U)
      {
        if ((ep_intr & 0x1U) != 0U) /* In ITR */
        {
          epint = USB_ReadDevInEPInterrupt(hpcd->Instance, (uint8_t)epnum);

          if ((epint & USB_OTG_DIEPINT_XFRC) == USB_OTG_DIEPINT_XFRC)
          {
            fifoemptymsk = (uint32_t)(0x1UL << (epnum & EP_ADDR_MSK));
            USBx_DEVICE->DIEPEMPMSK &= ~fifoemptymsk;

            CLEAR_IN_EP_INTR(epnum, USB_OTG_DIEPINT_XFRC);

            if (hpcd->Init.dma_enable == 1U)
            {
              hpcd->IN_ep[epnum].xfer_buff += hpcd->IN_ep[epnum].maxpacket;
            }

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
            hpcd->DataInStageCallback(hpcd, (uint8_t)epnum);
#else
            HAL_PCD_DataInStageCallback(hpcd, (uint8_t)epnum);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

            if (hpcd->Init.dma_enable == 1U)
            {
              /* this is ZLP, so prepare EP0 for next setup */
              if ((epnum == 0U) && (hpcd->IN_ep[epnum].xfer_len == 0U))
              {
                /* prepare to rx more setup packets */
                (void)USB_EP0_OutStart(hpcd->Instance, 1U, (uint8_t *)hpcd->Setup);
              }
            }
          }
          if ((epint & USB_OTG_DIEPINT_TOC) == USB_OTG_DIEPINT_TOC)
          {
            CLEAR_IN_EP_INTR(epnum, USB_OTG_DIEPINT_TOC);
          }
          if ((epint & USB_OTG_DIEPINT_ITTXFE) == USB_OTG_DIEPINT_ITTXFE)
          {
            CLEAR_IN_EP_INTR(epnum, USB_OTG_DIEPINT_ITTXFE);
          }
          if ((epint & USB_OTG_DIEPINT_INEPNE) == USB_OTG_DIEPINT_INEPNE)
          {
            CLEAR_IN_EP_INTR(epnum, USB_OTG_DIEPINT_INEPNE);
          }
          if ((epint & USB_OTG_DIEPINT_EPDISD) == USB_OTG_DIEPINT_EPDISD)
          {
            CLEAR_IN_EP_INTR(epnum, USB_OTG_DIEPINT_EPDISD);
          }
          if ((epint & USB_OTG_DIEPINT_TXFE) == USB_OTG_DIEPINT_TXFE)
          {
            (void)PCD_WriteEmptyTxFifo(hpcd, epnum);
          }
        }
        epnum++;
        ep_intr >>= 1U;
      }
    }

    /* Handle Resume Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_WKUINT))
    {
      /* Clear the Remote Wake-up Signaling */
      USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_RWUSIG;

      if (hpcd->LPM_State == LPM_L1)
      {
        hpcd->LPM_State = LPM_L0;

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->LPMCallback(hpcd, PCD_LPM_L0_ACTIVE);
#else
        HAL_PCDEx_LPM_Callback(hpcd, PCD_LPM_L0_ACTIVE);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      else
      {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->ResumeCallback(hpcd);
#else
        HAL_PCD_ResumeCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_WKUINT);
    }

    /* Handle Suspend Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_USBSUSP))
    {
      if ((USBx_DEVICE->DSTS & USB_OTG_DSTS_SUSPSTS) == USB_OTG_DSTS_SUSPSTS)
      {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->SuspendCallback(hpcd);
#else
        HAL_PCD_SuspendCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_USBSUSP);
    }
    #if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    /* Handle LPM Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_LPMINT))
    {
      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_LPMINT);

      if (hpcd->LPM_State == LPM_L0)
      {
        hpcd->LPM_State = LPM_L1;
        hpcd->BESL = (hpcd->Instance->GLPMCFG & USB_OTG_GLPMCFG_BESL) >> 2U;

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->LPMCallback(hpcd, PCD_LPM_L1_ACTIVE);
#else
        HAL_PCDEx_LPM_Callback(hpcd, PCD_LPM_L1_ACTIVE);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      else
      {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->SuspendCallback(hpcd);
#else
        HAL_PCD_SuspendCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
    }
    #endif /* defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx) */
    /* Handle Reset Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_USBRST))
    {
      USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_RWUSIG;
      (void)USB_FlushTxFifo(hpcd->Instance, 0x10U);

      for (i = 0U; i < hpcd->Init.dev_endpoints; i++)
      {
        USBx_INEP(i)->DIEPINT = 0xFB7FU;
        USBx_INEP(i)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
        USBx_OUTEP(i)->DOEPINT = 0xFB7FU;
        USBx_OUTEP(i)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
      }
      USBx_DEVICE->DAINTMSK |= 0x10001U;

      if (hpcd->Init.use_dedicated_ep1 != 0U)
      {
        USBx_DEVICE->DOUTEP1MSK |= USB_OTG_DOEPMSK_STUPM |
                                   USB_OTG_DOEPMSK_XFRCM |
                                   USB_OTG_DOEPMSK_EPDM;

        USBx_DEVICE->DINEP1MSK |= USB_OTG_DIEPMSK_TOM |
                                  USB_OTG_DIEPMSK_XFRCM |
                                  USB_OTG_DIEPMSK_EPDM;
      }
      else
      {
        USBx_DEVICE->DOEPMSK |= USB_OTG_DOEPMSK_STUPM |
                                USB_OTG_DOEPMSK_XFRCM |
                                USB_OTG_DOEPMSK_EPDM |
                                USB_OTG_DOEPMSK_OTEPSPRM |
                                USB_OTG_DOEPMSK_NAKM;

        USBx_DEVICE->DIEPMSK |= USB_OTG_DIEPMSK_TOM |
                                USB_OTG_DIEPMSK_XFRCM |
                                USB_OTG_DIEPMSK_EPDM;
      }

      /* Set Default Address to 0 */
      USBx_DEVICE->DCFG &= ~USB_OTG_DCFG_DAD;

      /* setup EP0 to receive SETUP packets */
      (void)USB_EP0_OutStart(hpcd->Instance, (uint8_t)hpcd->Init.dma_enable,
                             (uint8_t *)hpcd->Setup);

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_USBRST);
    }

    /* Handle Enumeration done Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_ENUMDNE))
    {
      (void)USB_ActivateSetup(hpcd->Instance);
      hpcd->Init.speed = USB_GetDevSpeed(hpcd->Instance);

      /* Set USB Turnaround time */
      (void)USB_SetTurnaroundTime(hpcd->Instance,
                                  HAL_RCC_GetHCLKFreq(),
                                  (uint8_t)hpcd->Init.speed);

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->ResetCallback(hpcd);
#else
      HAL_PCD_ResetCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_ENUMDNE);
    }

    /* Handle RxQLevel Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_RXFLVL))
    {
      USB_MASK_INTERRUPT(hpcd->Instance, USB_OTG_GINTSTS_RXFLVL);

      temp = USBx->GRXSTSP;

      ep = &hpcd->OUT_ep[temp & USB_OTG_GRXSTSP_EPNUM];

      if (((temp & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_DATA_UPDT)
      {
        if ((temp & USB_OTG_GRXSTSP_BCNT) != 0U)
        {
          (void)USB_ReadPacket(USBx, ep->xfer_buff,
                               (uint16_t)((temp & USB_OTG_GRXSTSP_BCNT) >> 4));

          ep->xfer_buff += (temp & USB_OTG_GRXSTSP_BCNT) >> 4;
          ep->xfer_count += (temp & USB_OTG_GRXSTSP_BCNT) >> 4;
        }
      }
      else if (((temp & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_SETUP_UPDT)
      {
        (void)USB_ReadPacket(USBx, (uint8_t *)hpcd->Setup, 8U);
        ep->xfer_count += (temp & USB_OTG_GRXSTSP_BCNT) >> 4;
      }
      else
      {
        /* ... */
      }
      USB_UNMASK_INTERRUPT(hpcd->Instance, USB_OTG_GINTSTS_RXFLVL);
    }

    /* Handle SOF Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_SOF))
    {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->SOFCallback(hpcd);
#else
      HAL_PCD_SOFCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_SOF);
    }

    /* Handle Incomplete ISO IN Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_IISOIXFR))
    {
      /* Keep application checking the corresponding Iso IN endpoint
      causing the incomplete Interrupt */
      epnum = 0U;

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->ISOINIncompleteCallback(hpcd, (uint8_t)epnum);
#else
      HAL_PCD_ISOINIncompleteCallback(hpcd, (uint8_t)epnum);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_IISOIXFR);
    }

    /* Handle Incomplete ISO OUT Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT))
    {
      /* Keep application checking the corresponding Iso OUT endpoint
      causing the incomplete Interrupt */
      epnum = 0U;

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->ISOOUTIncompleteCallback(hpcd, (uint8_t)epnum);
#else
      HAL_PCD_ISOOUTIncompleteCallback(hpcd, (uint8_t)epnum);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT);
    }

    /* Handle Connection event Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_SRQINT))
    {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->ConnectCallback(hpcd);
#else
      HAL_PCD_ConnectCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_SRQINT);
    }

    /* Handle Disconnection event Interrupt */
    if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_OTGINT))
    {
      temp = hpcd->Instance->GOTGINT;

      if ((temp & USB_OTG_GOTGINT_SEDET) == USB_OTG_GOTGINT_SEDET)
      {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->DisconnectCallback(hpcd);
#else
        HAL_PCD_DisconnectCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
      hpcd->Instance->GOTGINT |= temp;
    }
  }
}
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */


/**
  * @brief  Data OUT stage callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_DataOutStageCallback could be implemented in the user file
   */
}

/**
  * @brief  Data IN stage callback
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_DataInStageCallback could be implemented in the user file
   */
}
/**
  * @brief  Setup stage callback
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_SetupStageCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Start Of Frame callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_SOFCallback could be implemented in the user file
   */
}

/**
  * @brief  USB Reset callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_ResetCallback could be implemented in the user file
   */
}

/**
  * @brief  Suspend event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_SuspendCallback could be implemented in the user file
   */
}

/**
  * @brief  Resume event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_ResumeCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO OUT callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_ISOOUTIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Incomplete ISO IN callback.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval None
  */
__weak void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);
  UNUSED(epnum);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_ISOINIncompleteCallback could be implemented in the user file
   */
}

/**
  * @brief  Connection event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_ConnectCallback could be implemented in the user file
   */
}

/**
  * @brief  Disconnection event callback.
  * @param  hpcd PCD handle
  * @retval None
  */
__weak void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hpcd);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PCD_DisconnectCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group3 Peripheral Control functions
 *  @brief   management functions
 *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the PCD data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Connect the USB device
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DevConnect(PCD_HandleTypeDef *hpcd)
{
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
  USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

  __HAL_LOCK(hpcd);
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
  if ((hpcd->Init.battery_charging_enable == 1U) &&
      (hpcd->Init.phy_itface != USB_OTG_ULPI_PHY))
  {
    /* Enable USB Transceiver */
    USBx->GCCFG |= USB_OTG_GCCFG_PWRDWN;
  }
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
  (void)USB_DevConnect(hpcd->Instance);
  __HAL_UNLOCK(hpcd);
  return HAL_OK;
}

/**
  * @brief  Disconnect the USB device.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DevDisconnect(PCD_HandleTypeDef *hpcd)
{
  __HAL_LOCK(hpcd);
  (void)USB_DevDisconnect(hpcd->Instance);
  __HAL_UNLOCK(hpcd);
  return HAL_OK;
}

/**
  * @brief  Set the USB Device address.
  * @param  hpcd PCD handle
  * @param  address new device address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_SetAddress(PCD_HandleTypeDef *hpcd, uint8_t address)
{
  __HAL_LOCK(hpcd);
  hpcd->USB_Address = address;
  (void)USB_SetDevAddress(hpcd->Instance, address);
  __HAL_UNLOCK(hpcd);
  return HAL_OK;
}
/**
  * @brief  Open and configure an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  ep_mps endpoint max packet size
  * @param  ep_type endpoint type
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Open(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
  HAL_StatusTypeDef  ret = HAL_OK;
  PCD_EPTypeDef *ep;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 0U;
  }

  ep->num = ep_addr & EP_ADDR_MSK;
  ep->maxpacket = ep_mps;
  ep->type = ep_type;

  if (ep->is_in != 0U)
  {
    /* Assign a Tx FIFO */
    ep->tx_fifo_num = ep->num;
  }
  /* Set initial data PID. */
  if (ep_type == EP_TYPE_BULK)
  {
    ep->data_pid_start = 0U;
  }

  __HAL_LOCK(hpcd);
  (void)USB_ActivateEndpoint(hpcd->Instance, ep);
  __HAL_UNLOCK(hpcd);

  return ret;
}

/**
  * @brief  Deactivate an endpoint.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Close(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_EPTypeDef *ep;

  if ((ep_addr & 0x80U) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 0U;
  }
  ep->num   = ep_addr & EP_ADDR_MSK;

  __HAL_LOCK(hpcd);
  (void)USB_DeactivateEndpoint(hpcd->Instance, ep);
  __HAL_UNLOCK(hpcd);
  return HAL_OK;
}


/**
  * @brief  Receive an amount of data.
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the reception buffer
  * @param  len amount of data to be received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Receive(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_EPTypeDef *ep;

  ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0U;
  ep->is_in = 0U;
  ep->num = ep_addr & EP_ADDR_MSK;

  if (hpcd->Init.dma_enable == 1U)
  {
    ep->dma_addr = (uint32_t)pBuf;
  }

  if ((ep_addr & EP_ADDR_MSK) == 0U)
  {
    (void)USB_EP0StartXfer(hpcd->Instance, ep, (uint8_t)hpcd->Init.dma_enable);
  }
  else
  {
    (void)USB_EPStartXfer(hpcd->Instance, ep, (uint8_t)hpcd->Init.dma_enable);
  }

  return HAL_OK;
}

/**
  * @brief  Get Received Data Size
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval Data Size
  */
uint32_t HAL_PCD_EP_GetRxCount(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  return hpcd->OUT_ep[ep_addr & EP_ADDR_MSK].xfer_count;
}
/**
  * @brief  Send an amount of data
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @param  pBuf pointer to the transmission buffer
  * @param  len amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Transmit(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
  PCD_EPTypeDef *ep;

  ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];

  /*setup and start the Xfer */
  ep->xfer_buff = pBuf;
  ep->xfer_len = len;
  ep->xfer_count = 0U;
  ep->is_in = 1U;
  ep->num = ep_addr & EP_ADDR_MSK;

  if (hpcd->Init.dma_enable == 1U)
  {
    ep->dma_addr = (uint32_t)pBuf;
  }

  if ((ep_addr & EP_ADDR_MSK) == 0U)
  {
    (void)USB_EP0StartXfer(hpcd->Instance, ep, (uint8_t)hpcd->Init.dma_enable);
  }
  else
  {
    (void)USB_EPStartXfer(hpcd->Instance, ep, (uint8_t)hpcd->Init.dma_enable);
  }

  return HAL_OK;
}

/**
  * @brief  Set a STALL condition over an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_SetStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_EPTypeDef *ep;

  if (((uint32_t)ep_addr & EP_ADDR_MSK) > hpcd->Init.dev_endpoints)
  {
    return HAL_ERROR;
  }

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr];
    ep->is_in = 0U;
  }

  ep->is_stall = 1U;
  ep->num = ep_addr & EP_ADDR_MSK;

  __HAL_LOCK(hpcd);

  (void)USB_EPSetStall(hpcd->Instance, ep);
  if ((ep_addr & EP_ADDR_MSK) == 0U)
  {
    (void)USB_EP0_OutStart(hpcd->Instance, (uint8_t)hpcd->Init.dma_enable, (uint8_t *)hpcd->Setup);
  }
  __HAL_UNLOCK(hpcd);

  return HAL_OK;
}

/**
  * @brief  Clear a STALL condition over in an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_ClrStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  PCD_EPTypeDef *ep;

  if (((uint32_t)ep_addr & 0x0FU) > hpcd->Init.dev_endpoints)
  {
    return HAL_ERROR;
  }

  if ((0x80U & ep_addr) == 0x80U)
  {
    ep = &hpcd->IN_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 1U;
  }
  else
  {
    ep = &hpcd->OUT_ep[ep_addr & EP_ADDR_MSK];
    ep->is_in = 0U;
  }

  ep->is_stall = 0U;
  ep->num = ep_addr & EP_ADDR_MSK;

  __HAL_LOCK(hpcd);
  (void)USB_EPClearStall(hpcd->Instance, ep);
  __HAL_UNLOCK(hpcd);

  return HAL_OK;
}

/**
  * @brief  Flush an endpoint
  * @param  hpcd PCD handle
  * @param  ep_addr endpoint address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_EP_Flush(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
  __HAL_LOCK(hpcd);

  if ((ep_addr & 0x80U) == 0x80U)
  {
    (void)USB_FlushTxFifo(hpcd->Instance, (uint32_t)ep_addr & EP_ADDR_MSK);
  }
  else
  {
    (void)USB_FlushRxFifo(hpcd->Instance);
  }

  __HAL_UNLOCK(hpcd);

  return HAL_OK;
}

/**
  * @brief  Activate remote wakeup signalling
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_ActivateRemoteWakeup(PCD_HandleTypeDef *hpcd)
{
  return (USB_ActivateRemoteWakeup(hpcd->Instance));
}

/**
  * @brief  De-activate remote wakeup signalling.
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DeActivateRemoteWakeup(PCD_HandleTypeDef *hpcd)
{
  return (USB_DeActivateRemoteWakeup(hpcd->Instance));
}

/**
  * @}
  */

/** @defgroup PCD_Exported_Functions_Group4 Peripheral State functions
 *  @brief   Peripheral State functions
 *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the PCD handle state.
  * @param  hpcd PCD handle
  * @retval HAL state
  */
PCD_StateTypeDef HAL_PCD_GetState(PCD_HandleTypeDef *hpcd)
{
  return hpcd->State;
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup PCD_Private_Functions
  * @{
  */
#if defined (USB_OTG_FS) || defined (USB_OTG_HS)
/**
  * @brief  Check FIFO for the next packet to be loaded.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval HAL status
  */
static HAL_StatusTypeDef PCD_WriteEmptyTxFifo(PCD_HandleTypeDef *hpcd, uint32_t epnum)
{
  USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  USB_OTG_EPTypeDef *ep;
  uint32_t len;
  uint32_t len32b;
  uint32_t fifoemptymsk;

  ep = &hpcd->IN_ep[epnum];

  if (ep->xfer_count > ep->xfer_len)
  {
    return HAL_ERROR;
  }

  len = ep->xfer_len - ep->xfer_count;

  if (len > ep->maxpacket)
  {
    len = ep->maxpacket;
  }

  len32b = (len + 3U) / 4U;

  while (((USBx_INEP(epnum)->DTXFSTS & USB_OTG_DTXFSTS_INEPTFSAV) >= len32b) &&
         (ep->xfer_count < ep->xfer_len) && (ep->xfer_len != 0U))
  {
    /* Write the FIFO */
    len = ep->xfer_len - ep->xfer_count;

    if (len > ep->maxpacket)
    {
      len = ep->maxpacket;
    }
    len32b = (len + 3U) / 4U;

    (void)USB_WritePacket(USBx, ep->xfer_buff, (uint8_t)epnum, (uint16_t)len,
                          (uint8_t)hpcd->Init.dma_enable);

    ep->xfer_buff  += len;
    ep->xfer_count += len;
  }

  if (ep->xfer_len <= ep->xfer_count)
  {
    fifoemptymsk = (uint32_t)(0x1UL << (epnum & EP_ADDR_MSK));
    USBx_DEVICE->DIEPEMPMSK &= ~fifoemptymsk;
  }

  return HAL_OK;
}


/**
  * @brief  process EP OUT transfer complete interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval HAL status
  */
static HAL_StatusTypeDef PCD_EP_OutXfrComplete_int(PCD_HandleTypeDef *hpcd, uint32_t epnum)
{
  USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t gSNPSiD = *(volatile uint32_t *)(&USBx->CID + 0x1U);
  uint32_t DoepintReg = USBx_OUTEP(epnum)->DOEPINT;

  if (hpcd->Init.dma_enable == 1U)
  {
    if ((DoepintReg & USB_OTG_DOEPINT_STUP) == USB_OTG_DOEPINT_STUP) /* Class C */
    {
      /* StupPktRcvd = 1 this is a setup packet */
      if ((gSNPSiD > USB_OTG_CORE_ID_300A) &&
          ((DoepintReg & USB_OTG_DOEPINT_STPKTRX) == USB_OTG_DOEPINT_STPKTRX))
      {
        CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STPKTRX);
      }

      /* Inform the upper layer that a setup packet is available */
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->SetupStageCallback(hpcd);
#else
      HAL_PCD_SetupStageCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

      (void)USB_EP0_OutStart(hpcd->Instance, 1U, (uint8_t *)hpcd->Setup);
      CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STUP);
    }
    else if ((DoepintReg & USB_OTG_DOEPINT_OTEPSPR) == USB_OTG_DOEPINT_OTEPSPR) /* Class E */
    {
      CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_OTEPSPR);
    }
    else if ((DoepintReg & (USB_OTG_DOEPINT_STUP | USB_OTG_DOEPINT_OTEPSPR)) == 0U)
    {
      /* StupPktRcvd = 1 this is a setup packet */
      if ((gSNPSiD > USB_OTG_CORE_ID_300A) &&
          ((DoepintReg & USB_OTG_DOEPINT_STPKTRX) == USB_OTG_DOEPINT_STPKTRX))
      {
        CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STPKTRX);
      }
      else
      {
        /* out data packet received over EP0 */
        hpcd->OUT_ep[epnum].xfer_count =
          hpcd->OUT_ep[epnum].maxpacket -
          (USBx_OUTEP(epnum)->DOEPTSIZ & USB_OTG_DOEPTSIZ_XFRSIZ);

        hpcd->OUT_ep[epnum].xfer_buff += hpcd->OUT_ep[epnum].maxpacket;

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->DataOutStageCallback(hpcd, (uint8_t)epnum);
#else
        HAL_PCD_DataOutStageCallback(hpcd, (uint8_t)epnum);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

        if ((epnum == 0U) && (hpcd->OUT_ep[epnum].xfer_len == 0U))
        {
          /* this is ZLP, so prepare EP0 for next setup */
          (void)USB_EP0_OutStart(hpcd->Instance, 1U, (uint8_t *)hpcd->Setup);
        }
      }
    }
    else
    {
      /* ... */
    }
  }
  else
  {
    if (gSNPSiD == USB_OTG_CORE_ID_310A)
    {
      /* StupPktRcvd = 1 this is a setup packet */
      if ((DoepintReg & USB_OTG_DOEPINT_STPKTRX) == USB_OTG_DOEPINT_STPKTRX)
      {
        CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STPKTRX);
      }
      else
      {
        if ((DoepintReg & USB_OTG_DOEPINT_OTEPSPR) == USB_OTG_DOEPINT_OTEPSPR)
        {
          CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_OTEPSPR);
        }

#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
        hpcd->DataOutStageCallback(hpcd, (uint8_t)epnum);
#else
        HAL_PCD_DataOutStageCallback(hpcd, (uint8_t)epnum);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
      }
    }
    else
    {
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
      hpcd->DataOutStageCallback(hpcd, (uint8_t)epnum);
#else
      HAL_PCD_DataOutStageCallback(hpcd, (uint8_t)epnum);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */
    }
  }

  return HAL_OK;
}


/**
  * @brief  process EP OUT setup packet received interrupt.
  * @param  hpcd PCD handle
  * @param  epnum endpoint number
  * @retval HAL status
  */
static HAL_StatusTypeDef PCD_EP_OutSetupPacket_int(PCD_HandleTypeDef *hpcd, uint32_t epnum)
{
  USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
  uint32_t USBx_BASE = (uint32_t)USBx;
  uint32_t gSNPSiD = *(volatile uint32_t *)(&USBx->CID + 0x1U);
  uint32_t DoepintReg = USBx_OUTEP(epnum)->DOEPINT;

  if (hpcd->Init.dma_enable == 1U)
  {
    /* StupPktRcvd = 1 pending setup packet int */
    if ((gSNPSiD > USB_OTG_CORE_ID_300A) &&
        ((DoepintReg & USB_OTG_DOEPINT_STPKTRX) == USB_OTG_DOEPINT_STPKTRX))
    {
      CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STPKTRX);
    }
  }
  else
  {
    if ((gSNPSiD == USB_OTG_CORE_ID_310A) &&
        ((DoepintReg & USB_OTG_DOEPINT_STPKTRX) == USB_OTG_DOEPINT_STPKTRX))
    {
      CLEAR_OUT_EP_INTR(epnum, USB_OTG_DOEPINT_STPKTRX);
    }
  }

  /* Inform the upper layer that a setup packet is available */
#if (USE_HAL_PCD_REGISTER_CALLBACKS == 1U)
  hpcd->SetupStageCallback(hpcd);
#else
  HAL_PCD_SetupStageCallback(hpcd);
#endif /* USE_HAL_PCD_REGISTER_CALLBACKS */

  if ((gSNPSiD > USB_OTG_CORE_ID_300A) && (hpcd->Init.dma_enable == 1U))
  {
    (void)USB_EP0_OutStart(hpcd->Instance, 1U, (uint8_t *)hpcd->Setup);
  }

  return HAL_OK;
}
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */


/**
  * @}
  */
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
#endif /* HAL_PCD_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/F
#endif 



#if 0
/**
  ******************************************************************************
  * @file    stm32f4xx_ll_usb.c
  * @author  MCD Application Team
  * @brief   USB Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of Init structure in USB_OTG_CfgTypeDef structure.

      (#) Call USB_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_LL_USB_DRIVER
  * @{
  */

#if defined(HAL_PCD_MODULE_ENABLED) || defined(HAL_HCD_MODULE_ENABLED)
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
static HAL_StatusTypeDef USB_CoreReset(USB_OTG_GlobalTypeDef *USBx);

/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Functions USB Low Layer Exported Functions
  * @{
  */

/** @defgroup USB_LL_Exported_Functions_Group1 Initialization/de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
                      ##### Initialization/de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the USB Core
  * @param  USBx USB Instance
  * @param  cfg pointer to a USB_OTG_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_CoreInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
    HAL_StatusTypeDef ret;

    if (cfg.phy_itface == USB_OTG_ULPI_PHY)
    {
        USBx->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);

        /* Init The ULPI Interface */
        USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_TSDPS | USB_OTG_GUSBCFG_ULPIFSLS | USB_OTG_GUSBCFG_PHYSEL);

        /* Select vbus source */
        USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_ULPIEVBUSD | USB_OTG_GUSBCFG_ULPIEVBUSI);
        if (cfg.use_external_vbus == 1U)
        {
            USBx->GUSBCFG |= USB_OTG_GUSBCFG_ULPIEVBUSD;
        }
        /* Reset after a PHY select  */
        ret = USB_CoreReset(USBx);
    }
    else /* FS interface (embedded Phy) */
    {
        /* Select FS Embedded PHY */
        USBx->GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;

        /* Reset after a PHY select and set Host mode */
        ret = USB_CoreReset(USBx);

        if (cfg.battery_charging_enable == 0U)
        {
            /* Activate the USB Transceiver */
            USBx->GCCFG |= USB_OTG_GCCFG_PWRDWN;
        }
        else
        {
            /* Deactivate the USB Transceiver */
            USBx->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
        }
    }


    if (cfg.dma_enable == 1U)
    {
        USBx->GAHBCFG |= USB_OTG_GAHBCFG_HBSTLEN_2;
        USBx->GAHBCFG |= USB_OTG_GAHBCFG_DMAEN;
    }

    return ret;
}

/**
  * @brief  Set the USB turnaround time
  * @param  USBx USB Instance
  * @param  hclk: AHB clock frequency
  * @retval USB turnaround time In PHY Clocks number
  */
HAL_StatusTypeDef USB_SetTurnaroundTime(USB_OTG_GlobalTypeDef *USBx,
                                        uint32_t hclk, uint8_t speed)
{
    uint32_t UsbTrd;

    /* The USBTRD is configured according to the tables below, depending on AHB frequency
  used by application. In the low AHB frequency range it is used to stretch enough the USB response
  time to IN tokens, the USB turnaround time, so to compensate for the longer AHB read access
  latency to the Data FIFO */
    if (speed == USBD_FS_SPEED)
    {
        if ((hclk >= 14200000U) && (hclk < 15000000U))
        {
            /* hclk Clock Range between 14.2-15 MHz */
            UsbTrd = 0xFU;
        }
        else if ((hclk >= 15000000U) && (hclk < 16000000U))
        {
            /* hclk Clock Range between 15-16 MHz */
            UsbTrd = 0xEU;
        }
        else if ((hclk >= 16000000U) && (hclk < 17200000U))
        {
            /* hclk Clock Range between 16-17.2 MHz */
            UsbTrd = 0xDU;
        }
        else if ((hclk >= 17200000U) && (hclk < 18500000U))
        {
            /* hclk Clock Range between 17.2-18.5 MHz */
            UsbTrd = 0xCU;
        }
        else if ((hclk >= 18500000U) && (hclk < 20000000U))
        {
            /* hclk Clock Range between 18.5-20 MHz */
            UsbTrd = 0xBU;
        }
        else if ((hclk >= 20000000U) && (hclk < 21800000U))
        {
            /* hclk Clock Range between 20-21.8 MHz */
            UsbTrd = 0xAU;
        }
        else if ((hclk >= 21800000U) && (hclk < 24000000U))
        {
            /* hclk Clock Range between 21.8-24 MHz */
            UsbTrd = 0x9U;
        }
        else if ((hclk >= 24000000U) && (hclk < 27700000U))
        {
            /* hclk Clock Range between 24-27.7 MHz */
            UsbTrd = 0x8U;
        }
        else if ((hclk >= 27700000U) && (hclk < 32000000U))
        {
            /* hclk Clock Range between 27.7-32 MHz */
            UsbTrd = 0x7U;
        }
        else /* if(hclk >= 32000000) */
        {
            /* hclk Clock Range between 32-200 MHz */
            UsbTrd = 0x6U;
        }
    }
    else if (speed == USBD_HS_SPEED)
    {
        UsbTrd = USBD_HS_TRDT_VALUE;
    }
    else
    {
        UsbTrd = USBD_DEFAULT_TRDT_VALUE;
    }

    USBx->GUSBCFG &= ~USB_OTG_GUSBCFG_TRDT;
    USBx->GUSBCFG |= (uint32_t)((UsbTrd << 10) & USB_OTG_GUSBCFG_TRDT);

    return HAL_OK;
}

/**
  * @brief  USB_EnableGlobalInt
  *         Enables the controller's Global Int in the AHB Config reg
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EnableGlobalInt(USB_OTG_GlobalTypeDef *USBx)
{
    USBx->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
    return HAL_OK;
}

/**
  * @brief  USB_DisableGlobalInt
  *         Disable the controller's Global Int in the AHB Config reg
  * @param  USBx  Selected device
  * @retval HAL status
*/
HAL_StatusTypeDef USB_DisableGlobalInt(USB_OTG_GlobalTypeDef *USBx)
{
    USBx->GAHBCFG &= ~USB_OTG_GAHBCFG_GINT;
    return HAL_OK;
}

/**
  * @brief  USB_SetCurrentMode : Set functional mode
  * @param  USBx  Selected device
  * @param  mode   current core mode
  *          This parameter can be one of these values:
  *            @arg USB_DEVICE_MODE: Peripheral mode
  *            @arg USB_HOST_MODE: Host mode
  *            @arg USB_DRD_MODE: Dual Role Device mode
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetCurrentMode(USB_OTG_GlobalTypeDef *USBx, USB_OTG_ModeTypeDef mode)
{
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD);

    if (mode == USB_HOST_MODE)
    {
        USBx->GUSBCFG |= USB_OTG_GUSBCFG_FHMOD;
    }
    else if (mode == USB_DEVICE_MODE)
    {
        USBx->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;
    }
    else
    {
        return HAL_ERROR;
    }
    HAL_Delay(50U);

    return HAL_OK;
}

/**
  * @brief  USB_DevInit : Initializes the USB_OTG controller registers
  *         for device mode
  * @param  USBx  Selected device
  * @param  cfg   pointer to a USB_OTG_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
    HAL_StatusTypeDef ret = HAL_OK;
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t i;

    for (i = 0U; i < 15U; i++)
    {
        USBx->DIEPTXF[i] = 0U;
    }

#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    /* VBUS Sensing setup */
    if (cfg.vbus_sensing_enable == 0U)
    {
        /* Deactivate VBUS Sensing B */
        USBx->GCCFG &= ~USB_OTG_GCCFG_VBDEN;

        /* B-peripheral session valid override enable */
        USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
        USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
    }
    else
    {
        /* Enable HW VBUS sensing */
        USBx->GCCFG |= USB_OTG_GCCFG_VBDEN;
    }
#else
    /* VBUS Sensing setup */
    if (cfg.vbus_sensing_enable == 0U)
    {
        /*
     * Disable HW VBUS sensing. VBUS is internally considered to be always
     * at VBUS-Valid level (5V).
     */
        USBx->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
        USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
        USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSASEN;
    }
    else
    {
        /* Enable HW VBUS sensing */
        USBx->GOTGCTL &= ~USB_OTG_GCCFG_NOVBUSSENS;
        USBx->GCCFG |= USB_OTG_GCCFG_VBUSBSEN;
    }
#endif /* defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx) */

    /* Restart the Phy Clock */
    USBx_PCGCCTL = 0U;

    /* Device mode configuration */
    USBx_DEVICE->DCFG |= DCFG_FRAME_INTERVAL_80;

    if (cfg.phy_itface == USB_OTG_ULPI_PHY)
    {
        if (cfg.speed == USBD_HS_SPEED)
        {
            /* Set Core speed to High speed mode */
            (void)USB_SetDevSpeed(USBx, USB_OTG_SPEED_HIGH);
        }
        else
        {
            /* Set Core speed to Full speed mode */
            (void)USB_SetDevSpeed(USBx, USB_OTG_SPEED_HIGH_IN_FULL);
        }
    }
    else
    {
        /* Set Core speed to Full speed mode */
        (void)USB_SetDevSpeed(USBx, USB_OTG_SPEED_FULL);
    }

    /* Flush the FIFOs */
    if (USB_FlushTxFifo(USBx, 0x10U) != HAL_OK) /* all Tx FIFOs */
    {
        ret = HAL_ERROR;
    }

    if (USB_FlushRxFifo(USBx) != HAL_OK)
    {
        ret = HAL_ERROR;
    }

    /* Clear all pending Device Interrupts */
    USBx_DEVICE->DIEPMSK = 0U;
    USBx_DEVICE->DOEPMSK = 0U;
    USBx_DEVICE->DAINTMSK = 0U;

    for (i = 0U; i < cfg.dev_endpoints; i++)
    {
        if ((USBx_INEP(i)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA)
        {
            if (i == 0U)
            {
                USBx_INEP(i)->DIEPCTL = USB_OTG_DIEPCTL_SNAK;
            }
            else
            {
                USBx_INEP(i)->DIEPCTL = USB_OTG_DIEPCTL_EPDIS | USB_OTG_DIEPCTL_SNAK;
            }
        }
        else
        {
            USBx_INEP(i)->DIEPCTL = 0U;
        }

        USBx_INEP(i)->DIEPTSIZ = 0U;
        USBx_INEP(i)->DIEPINT = 0xFB7FU;
    }

    for (i = 0U; i < cfg.dev_endpoints; i++)
    {
        if ((USBx_OUTEP(i)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
        {
            if (i == 0U)
            {
                USBx_OUTEP(i)->DOEPCTL = USB_OTG_DOEPCTL_SNAK;
            }
            else
            {
                USBx_OUTEP(i)->DOEPCTL = USB_OTG_DOEPCTL_EPDIS | USB_OTG_DOEPCTL_SNAK;
            }
        }
        else
        {
            USBx_OUTEP(i)->DOEPCTL = 0U;
        }

        USBx_OUTEP(i)->DOEPTSIZ = 0U;
        USBx_OUTEP(i)->DOEPINT = 0xFB7FU;
    }

    USBx_DEVICE->DIEPMSK &= ~(USB_OTG_DIEPMSK_TXFURM);

    if (cfg.dma_enable == 1U)
    {
        /*Set threshold parameters */
        USBx_DEVICE->DTHRCTL = USB_OTG_DTHRCTL_TXTHRLEN_6 |
                               USB_OTG_DTHRCTL_RXTHRLEN_6;

        USBx_DEVICE->DTHRCTL |= USB_OTG_DTHRCTL_RXTHREN |
                                USB_OTG_DTHRCTL_ISOTHREN |
                                USB_OTG_DTHRCTL_NONISOTHREN;
    }

    /* Disable all interrupts. */
    USBx->GINTMSK = 0U;

    /* Clear any pending interrupts */
    USBx->GINTSTS = 0xBFFFFFFFU;

    /* Enable the common interrupts */
    if (cfg.dma_enable == 0U)
    {
        USBx->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
    }

    /* Enable interrupts matching to the Device mode ONLY */
    USBx->GINTMSK |= USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
                     USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_IEPINT |
                     USB_OTG_GINTMSK_OEPINT | USB_OTG_GINTMSK_IISOIXFRM |
                     USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM;

    if (cfg.Sof_enable != 0U)
    {
        USBx->GINTMSK |= USB_OTG_GINTMSK_SOFM;
    }

    if (cfg.vbus_sensing_enable == 1U)
    {
        USBx->GINTMSK |= (USB_OTG_GINTMSK_SRQIM | USB_OTG_GINTMSK_OTGINT);
    }

    return ret;
}

/**
  * @brief  USB_OTG_FlushTxFifo : Flush a Tx FIFO
  * @param  USBx  Selected device
  * @param  num  FIFO number
  *         This parameter can be a value from 1 to 15
            15 means Flush all Tx FIFOs
  * @retval HAL status
  */
HAL_StatusTypeDef USB_FlushTxFifo(USB_OTG_GlobalTypeDef *USBx, uint32_t num)
{
    uint32_t count = 0U;

    USBx->GRSTCTL = (USB_OTG_GRSTCTL_TXFFLSH | (num << 6));

    do
    {
        if (++count > 200000U)
        {
            return HAL_TIMEOUT;
        }
    } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);

    return HAL_OK;
}

/**
  * @brief  USB_FlushRxFifo : Flush Rx FIFO
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_FlushRxFifo(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t count = 0;

    USBx->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;

    do
    {
        if (++count > 200000U)
        {
            return HAL_TIMEOUT;
        }
    } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);

    return HAL_OK;
}

/**
  * @brief  USB_SetDevSpeed  Initializes the DevSpd field of DCFG register
  *         depending the PHY type and the enumeration speed of the device.
  * @param  USBx  Selected device
  * @param  speed  device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_HIGH: High speed mode
  *            @arg USB_OTG_SPEED_HIGH_IN_FULL: High speed core in Full Speed mode
  *            @arg USB_OTG_SPEED_FULL: Full speed mode
  * @retval  Hal status
  */
HAL_StatusTypeDef USB_SetDevSpeed(USB_OTG_GlobalTypeDef *USBx, uint8_t speed)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    USBx_DEVICE->DCFG |= speed;
    return HAL_OK;
}

/**
  * @brief  USB_GetDevSpeed  Return the Dev Speed
  * @param  USBx  Selected device
  * @retval speed  device speed
  *          This parameter can be one of these values:
  *            @arg PCD_SPEED_HIGH: High speed mode
  *            @arg PCD_SPEED_FULL: Full speed mode
  */
uint8_t USB_GetDevSpeed(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint8_t speed;
    uint32_t DevEnumSpeed = USBx_DEVICE->DSTS & USB_OTG_DSTS_ENUMSPD;

    if (DevEnumSpeed == DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ)
    {
        speed = USBD_HS_SPEED;
    }
    else if ((DevEnumSpeed == DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ) ||
             (DevEnumSpeed == DSTS_ENUMSPD_FS_PHY_48MHZ))
    {
        speed = USBD_FS_SPEED;
    }
    else
    {
        speed = 0xFU;
    }

    return speed;
}

/**
  * @brief  Activate and configure an endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateEndpoint(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    if (ep->is_in == 1U)
    {
        USBx_DEVICE->DAINTMSK |= USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK));

        if ((USBx_INEP(epnum)->DIEPCTL & USB_OTG_DIEPCTL_USBAEP) == 0U)
        {
            USBx_INEP(epnum)->DIEPCTL |= (ep->maxpacket & USB_OTG_DIEPCTL_MPSIZ) |
                                         ((uint32_t)ep->type << 18) | (epnum << 22) |
                                         USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                         USB_OTG_DIEPCTL_USBAEP;
        }
    }
    else
    {
        USBx_DEVICE->DAINTMSK |= USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16);

        if (((USBx_OUTEP(epnum)->DOEPCTL) & USB_OTG_DOEPCTL_USBAEP) == 0U)
        {
            USBx_OUTEP(epnum)->DOEPCTL |= (ep->maxpacket & USB_OTG_DOEPCTL_MPSIZ) |
                                          ((uint32_t)ep->type << 18) |
                                          USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                          USB_OTG_DOEPCTL_USBAEP;
        }
    }
    return HAL_OK;
}

/**
  * @brief  Activate and configure a dedicated endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateDedicatedEndpoint(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    /* Read DEPCTLn register */
    if (ep->is_in == 1U)
    {
        if (((USBx_INEP(epnum)->DIEPCTL) & USB_OTG_DIEPCTL_USBAEP) == 0U)
        {
            USBx_INEP(epnum)->DIEPCTL |= (ep->maxpacket & USB_OTG_DIEPCTL_MPSIZ) |
                                         ((uint32_t)ep->type << 18) | (epnum << 22) |
                                         USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                         USB_OTG_DIEPCTL_USBAEP;
        }

        USBx_DEVICE->DEACHMSK |= USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK));
    }
    else
    {
        if (((USBx_OUTEP(epnum)->DOEPCTL) & USB_OTG_DOEPCTL_USBAEP) == 0U)
        {
            USBx_OUTEP(epnum)->DOEPCTL |= (ep->maxpacket & USB_OTG_DOEPCTL_MPSIZ) |
                                          ((uint32_t)ep->type << 18) | (epnum << 22) |
                                          USB_OTG_DOEPCTL_USBAEP;
        }

        USBx_DEVICE->DEACHMSK |= USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16);
    }

    return HAL_OK;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateEndpoint(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    /* Read DEPCTLn register */
    if (ep->is_in == 1U)
    {
        USBx_DEVICE->DEACHMSK &= ~(USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
        USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
        USBx_INEP(epnum)->DIEPCTL &= ~(USB_OTG_DIEPCTL_USBAEP |
                                       USB_OTG_DIEPCTL_MPSIZ |
                                       USB_OTG_DIEPCTL_TXFNUM |
                                       USB_OTG_DIEPCTL_SD0PID_SEVNFRM |
                                       USB_OTG_DIEPCTL_EPTYP);
    }
    else
    {
        USBx_DEVICE->DEACHMSK &= ~(USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
        USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
        USBx_OUTEP(epnum)->DOEPCTL &= ~(USB_OTG_DOEPCTL_USBAEP |
                                        USB_OTG_DOEPCTL_MPSIZ |
                                        USB_OTG_DOEPCTL_SD0PID_SEVNFRM |
                                        USB_OTG_DOEPCTL_EPTYP);
    }

    return HAL_OK;
}

/**
  * @brief  De-activate and de-initialize a dedicated endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateDedicatedEndpoint(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    /* Read DEPCTLn register */
    if (ep->is_in == 1U)
    {
        USBx_INEP(epnum)->DIEPCTL &= ~USB_OTG_DIEPCTL_USBAEP;
        USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_IEPM & (uint32_t)(1UL << (ep->num & EP_ADDR_MSK)));
    }
    else
    {
        USBx_OUTEP(epnum)->DOEPCTL &= ~USB_OTG_DOEPCTL_USBAEP;
        USBx_DEVICE->DAINTMSK &= ~(USB_OTG_DAINTMSK_OEPM & ((uint32_t)(1UL << (ep->num & EP_ADDR_MSK)) << 16));
    }

    return HAL_OK;
}

/**
  * @brief  USB_EPStartXfer : setup and starts a transfer over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPStartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep, uint8_t dma)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;
    uint16_t pktcnt;

    /* IN endpoint */
    if (ep->is_in == 1U)
    {
        /* Zero Length Packet? */
        if (ep->xfer_len == 0U)
        {
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);
            USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
        }
        else
        {
            /* Program the transfer size and packet count
      * as follows: xfersize = N * maxpacket +
      * short_packet pktcnt = N + (short_packet
      * exist ? 1 : 0)
      */
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);
            USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket) << 19));
            USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_XFRSIZ & ep->xfer_len);

            if (ep->type == EP_TYPE_ISOC)
            {
                USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_MULCNT);
                USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_MULCNT & (1U << 29));
            }
        }

        if (dma == 1U)
        {
            if ((uint32_t)ep->dma_addr != 0U)
            {
                USBx_INEP(epnum)->DIEPDMA = (uint32_t)(ep->dma_addr);
            }

            if (ep->type == EP_TYPE_ISOC)
            {
                if ((USBx_DEVICE->DSTS & (1U << 8)) == 0U)
                {
                    USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
                }
                else
                {
                    USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
                }
            }

            /* EP enable, IN data in FIFO */
            USBx_INEP(epnum)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);
        }
        else
        {
            /* EP enable, IN data in FIFO */
            USBx_INEP(epnum)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);

            if (ep->type != EP_TYPE_ISOC)
            {
                /* Enable the Tx FIFO Empty Interrupt for this EP */
                if (ep->xfer_len > 0U)
                {
                    USBx_DEVICE->DIEPEMPMSK |= 1UL << (ep->num & EP_ADDR_MSK);
                }
            }
            else
            {
                if ((USBx_DEVICE->DSTS & (1U << 8)) == 0U)
                {
                    USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
                }
                else
                {
                    USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
                }

                (void)USB_WritePacket(USBx, ep->xfer_buff, ep->num, (uint16_t)ep->xfer_len, dma);
            }
        }
    }
    else /* OUT endpoint */
    {
        /* Program the transfer size and packet count as follows:
    * pktcnt = N
    * xfersize = N * maxpacket
    */
        USBx_OUTEP(epnum)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_XFRSIZ);
        USBx_OUTEP(epnum)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_PKTCNT);

        if (ep->xfer_len == 0U)
        {
            USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & ep->maxpacket);
            USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
        }
        else
        {
            pktcnt = (uint16_t)((ep->xfer_len + ep->maxpacket - 1U) / ep->maxpacket);
            USBx_OUTEP(epnum)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_PKTCNT & ((uint32_t)pktcnt << 19);
            USBx_OUTEP(epnum)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_XFRSIZ & (ep->maxpacket * pktcnt);
        }

        if (dma == 1U)
        {
            if ((uint32_t)ep->xfer_buff != 0U)
            {
                USBx_OUTEP(epnum)->DOEPDMA = (uint32_t)(ep->xfer_buff);
            }
        }

        if (ep->type == EP_TYPE_ISOC)
        {
            if ((USBx_DEVICE->DSTS & (1U << 8)) == 0U)
            {
                USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SODDFRM;
            }
            else
            {
                USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM;
            }
        }
        /* EP enable */
        USBx_OUTEP(epnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
    }

    return HAL_OK;
}

/**
  * @brief  USB_EP0StartXfer : setup and starts a transfer over the EP  0
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EP0StartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep, uint8_t dma)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    /* IN endpoint */
    if (ep->is_in == 1U)
    {
        /* Zero Length Packet? */
        if (ep->xfer_len == 0U)
        {
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);
            USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
        }
        else
        {
            /* Program the transfer size and packet count
      * as follows: xfersize = N * maxpacket +
      * short_packet pktcnt = N + (short_packet
      * exist ? 1 : 0)
      */
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_XFRSIZ);
            USBx_INEP(epnum)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT);

            if (ep->xfer_len > ep->maxpacket)
            {
                ep->xfer_len = ep->maxpacket;
            }
            USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (1U << 19));
            USBx_INEP(epnum)->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_XFRSIZ & ep->xfer_len);
        }

        if (dma == 1U)
        {
            if ((uint32_t)ep->dma_addr != 0U)
            {
                USBx_INEP(epnum)->DIEPDMA = (uint32_t)(ep->dma_addr);
            }

            /* EP enable, IN data in FIFO */
            USBx_INEP(epnum)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);
        }
        else
        {
            /* EP enable, IN data in FIFO */
            USBx_INEP(epnum)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);

            /* Enable the Tx FIFO Empty Interrupt for this EP */
            if (ep->xfer_len > 0U)
            {
                USBx_DEVICE->DIEPEMPMSK |= 1UL << (ep->num & EP_ADDR_MSK);
            }
        }
    }
    else /* OUT endpoint */
    {
        /* Program the transfer size and packet count as follows:
    * pktcnt = N
    * xfersize = N * maxpacket
    */
        USBx_OUTEP(epnum)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_XFRSIZ);
        USBx_OUTEP(epnum)->DOEPTSIZ &= ~(USB_OTG_DOEPTSIZ_PKTCNT);

        if (ep->xfer_len > 0U)
        {
            ep->xfer_len = ep->maxpacket;
        }

        USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
        USBx_OUTEP(epnum)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & (ep->maxpacket));

        if (dma == 1U)
        {
            if ((uint32_t)ep->xfer_buff != 0U)
            {
                USBx_OUTEP(epnum)->DOEPDMA = (uint32_t)(ep->xfer_buff);
            }
        }

        /* EP enable */
        USBx_OUTEP(epnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
    }

    return HAL_OK;
}

/**
  * @brief  USB_WritePacket : Writes a packet into the Tx FIFO associated
  *         with the EP/channel
  * @param  USBx  Selected device
  * @param  src   pointer to source buffer
  * @param  ch_ep_num  endpoint or host channel number
  * @param  len  Number of bytes to write
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL status
  */
HAL_StatusTypeDef USB_WritePacket(USB_OTG_GlobalTypeDef *USBx, uint8_t *src, uint8_t ch_ep_num, uint16_t len, uint8_t dma)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t *pSrc = (uint32_t *)src;
    uint32_t count32b, i;

    if (dma == 0U)
    {
        count32b = ((uint32_t)len + 3U) / 4U;
        for (i = 0U; i < count32b; i++)
        {
            USBx_DFIFO((uint32_t)ch_ep_num) = __UNALIGNED_UINT32_READ(pSrc);
            pSrc++;
        }
    }

    return HAL_OK;
}

/**
  * @brief  USB_ReadPacket : read a packet from the RX FIFO
  * @param  USBx  Selected device
  * @param  dest  source pointer
  * @param  len  Number of bytes to read
  * @retval pointer to destination buffer
  */
void *USB_ReadPacket(USB_OTG_GlobalTypeDef *USBx, uint8_t *dest, uint16_t len)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t *pDest = (uint32_t *)dest;
    uint32_t i;
    uint32_t count32b = ((uint32_t)len + 3U) / 4U;

    for (i = 0U; i < count32b; i++)
    {
        __UNALIGNED_UINT32_WRITE(pDest, USBx_DFIFO(0U));
        pDest++;
    }

    return ((void *)pDest);
}

/**
  * @brief  USB_EPSetStall : set a stall condition over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPSetStall(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    if (ep->is_in == 1U)
    {
        if (((USBx_INEP(epnum)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == 0U) && (epnum != 0U))
        {
            USBx_INEP(epnum)->DIEPCTL &= ~(USB_OTG_DIEPCTL_EPDIS);
        }
        USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_STALL;
    }
    else
    {
        if (((USBx_OUTEP(epnum)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == 0U) && (epnum != 0U))
        {
            USBx_OUTEP(epnum)->DOEPCTL &= ~(USB_OTG_DOEPCTL_EPDIS);
        }
        USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_STALL;
    }

    return HAL_OK;
}

/**
  * @brief  USB_EPClearStall : Clear a stall condition over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPClearStall(USB_OTG_GlobalTypeDef *USBx, USB_OTG_EPTypeDef *ep)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t epnum = (uint32_t)ep->num;

    if (ep->is_in == 1U)
    {
        USBx_INEP(epnum)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
        if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
        {
            USBx_INEP(epnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM; /* DATA0 */
        }
    }
    else
    {
        USBx_OUTEP(epnum)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
        if ((ep->type == EP_TYPE_INTR) || (ep->type == EP_TYPE_BULK))
        {
            USBx_OUTEP(epnum)->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM; /* DATA0 */
        }
    }
    return HAL_OK;
}

/**
  * @brief  USB_StopDevice : Stop the usb device mode
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_StopDevice(USB_OTG_GlobalTypeDef *USBx)
{
    HAL_StatusTypeDef ret;
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t i;

    /* Clear Pending interrupt */
    for (i = 0U; i < 15U; i++)
    {
        USBx_INEP(i)->DIEPINT = 0xFB7FU;
        USBx_OUTEP(i)->DOEPINT = 0xFB7FU;
    }

    /* Clear interrupt masks */
    USBx_DEVICE->DIEPMSK = 0U;
    USBx_DEVICE->DOEPMSK = 0U;
    USBx_DEVICE->DAINTMSK = 0U;

    /* Flush the FIFO */
    ret = USB_FlushRxFifo(USBx);
    if (ret != HAL_OK)
    {
        return ret;
    }

    ret = USB_FlushTxFifo(USBx, 0x10U);
    if (ret != HAL_OK)
    {
        return ret;
    }

    return ret;
}

/**
  * @brief  USB_SetDevAddress : Stop the usb device mode
  * @param  USBx  Selected device
  * @param  address  new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetDevAddress(USB_OTG_GlobalTypeDef *USBx, uint8_t address)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    USBx_DEVICE->DCFG &= ~(USB_OTG_DCFG_DAD);
    USBx_DEVICE->DCFG |= ((uint32_t)address << 4) & USB_OTG_DCFG_DAD;

    return HAL_OK;
}

/**
  * @brief  USB_DevConnect : Connect the USB device by enabling the pull-up/pull-down
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevConnect(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_SDIS;
    HAL_Delay(3U);

    return HAL_OK;
}

/**
  * @brief  USB_DevDisconnect : Disconnect the USB device by disabling the pull-up/pull-down
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevDisconnect(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    USBx_DEVICE->DCTL |= USB_OTG_DCTL_SDIS;
    HAL_Delay(3U);

    return HAL_OK;
}

/**
  * @brief  USB_ReadInterrupts: return the global USB interrupt status
  * @param  USBx  Selected device
  * @retval HAL status
  */
uint32_t USB_ReadInterrupts(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t tmpreg;

    tmpreg = USBx->GINTSTS;
    tmpreg &= USBx->GINTMSK;

    return tmpreg;
}

/**
  * @brief  USB_ReadDevAllOutEpInterrupt: return the USB device OUT endpoints interrupt status
  * @param  USBx  Selected device
  * @retval HAL status
  */
uint32_t USB_ReadDevAllOutEpInterrupt(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t tmpreg;

    tmpreg = USBx_DEVICE->DAINT;
    tmpreg &= USBx_DEVICE->DAINTMSK;

    return ((tmpreg & 0xffff0000U) >> 16);
}

/**
  * @brief  USB_ReadDevAllInEpInterrupt: return the USB device IN endpoints interrupt status
  * @param  USBx  Selected device
  * @retval HAL status
  */
uint32_t USB_ReadDevAllInEpInterrupt(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t tmpreg;

    tmpreg = USBx_DEVICE->DAINT;
    tmpreg &= USBx_DEVICE->DAINTMSK;

    return ((tmpreg & 0xFFFFU));
}

/**
  * @brief  Returns Device OUT EP Interrupt register
  * @param  USBx  Selected device
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device OUT EP Interrupt register
  */
uint32_t USB_ReadDevOutEPInterrupt(USB_OTG_GlobalTypeDef *USBx, uint8_t epnum)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t tmpreg;

    tmpreg = USBx_OUTEP((uint32_t)epnum)->DOEPINT;
    tmpreg &= USBx_DEVICE->DOEPMSK;

    return tmpreg;
}

/**
  * @brief  Returns Device IN EP Interrupt register
  * @param  USBx  Selected device
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device IN EP Interrupt register
  */
uint32_t USB_ReadDevInEPInterrupt(USB_OTG_GlobalTypeDef *USBx, uint8_t epnum)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t tmpreg, msk, emp;

    msk = USBx_DEVICE->DIEPMSK;
    emp = USBx_DEVICE->DIEPEMPMSK;
    msk |= ((emp >> (epnum & EP_ADDR_MSK)) & 0x1U) << 7;
    tmpreg = USBx_INEP((uint32_t)epnum)->DIEPINT & msk;

    return tmpreg;
}

/**
  * @brief  USB_ClearInterrupts: clear a USB interrupt
  * @param  USBx  Selected device
  * @param  interrupt  interrupt flag
  * @retval None
  */
void USB_ClearInterrupts(USB_OTG_GlobalTypeDef *USBx, uint32_t interrupt)
{
    USBx->GINTSTS |= interrupt;
}

/**
  * @brief  Returns USB core mode
  * @param  USBx  Selected device
  * @retval return core mode : Host or Device
  *          This parameter can be one of these values:
  *           0 : Host
  *           1 : Device
  */
uint32_t USB_GetMode(USB_OTG_GlobalTypeDef *USBx)
{
    return ((USBx->GINTSTS) & 0x1U);
}

/**
  * @brief  Activate EP0 for Setup transactions
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateSetup(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    /* Set the MPS of the IN EP based on the enumeration speed */
    USBx_INEP(0U)->DIEPCTL &= ~USB_OTG_DIEPCTL_MPSIZ;

    if ((USBx_DEVICE->DSTS & USB_OTG_DSTS_ENUMSPD) == DSTS_ENUMSPD_LS_PHY_6MHZ)
    {
        USBx_INEP(0U)->DIEPCTL |= 3U;
    }
    USBx_DEVICE->DCTL |= USB_OTG_DCTL_CGINAK;

    return HAL_OK;
}

/**
  * @brief  Prepare the EP0 to start the first control setup
  * @param  USBx  Selected device
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @param  psetup  pointer to setup packet
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EP0_OutStart(USB_OTG_GlobalTypeDef *USBx, uint8_t dma, uint8_t *psetup)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t gSNPSiD = *(volatile uint32_t *)(&USBx->CID + 0x1U);

    if (gSNPSiD > USB_OTG_CORE_ID_300A)
    {
        if ((USBx_OUTEP(0U)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA)
        {
            return HAL_OK;
        }
    }

    USBx_OUTEP(0U)->DOEPTSIZ = 0U;
    USBx_OUTEP(0U)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19));
    USBx_OUTEP(0U)->DOEPTSIZ |= (3U * 8U);
    USBx_OUTEP(0U)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_STUPCNT;

    if (dma == 1U)
    {
        USBx_OUTEP(0U)->DOEPDMA = (uint32_t)psetup;
        /* EP enable */
        USBx_OUTEP(0U)->DOEPCTL |= USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_USBAEP;
    }

    return HAL_OK;
}

/**
  * @brief  Reset the USB Core (needed after USB clock settings change)
  * @param  USBx  Selected device
  * @retval HAL status
  */
static HAL_StatusTypeDef USB_CoreReset(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t count = 0U;

    /* Wait for AHB master IDLE state. */
    do
    {
        if (++count > 200000U)
        {
            return HAL_TIMEOUT;
        }
    } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0U);

    /* Core Soft Reset */
    count = 0U;
    USBx->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;

    do
    {
        if (++count > 200000U)
        {
            return HAL_TIMEOUT;
        }
    } while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_CSRST) == USB_OTG_GRSTCTL_CSRST);

    return HAL_OK;
}

/**
  * @brief  USB_HostInit : Initializes the USB OTG controller registers
  *         for Host mode
  * @param  USBx  Selected device
  * @param  cfg   pointer to a USB_OTG_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_HostInit(USB_OTG_GlobalTypeDef *USBx, USB_OTG_CfgTypeDef cfg)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t i;

    /* Restart the Phy Clock */
    USBx_PCGCCTL = 0U;

#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    /* Disable HW VBUS sensing */
    USBx->GCCFG &= ~(USB_OTG_GCCFG_VBDEN);
#else
    /*
  * Disable HW VBUS sensing. VBUS is internally considered to be always
  * at VBUS-Valid level (5V).
  */
    USBx->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
    USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
    USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSASEN;
#endif /* defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx) */
#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    /* Disable Battery chargin detector */
    USBx->GCCFG &= ~(USB_OTG_GCCFG_BCDEN);
#endif /* defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx) */

    if ((USBx->CID & (0x1U << 8)) != 0U)
    {
        if (cfg.speed == USB_OTG_SPEED_FULL)
        {
            /* Force Device Enumeration to FS/LS mode only */
            USBx_HOST->HCFG |= USB_OTG_HCFG_FSLSS;
        }
        else
        {
            /* Set default Max speed support */
            USBx_HOST->HCFG &= ~(USB_OTG_HCFG_FSLSS);
        }
    }
    else
    {
        /* Set default Max speed support */
        USBx_HOST->HCFG &= ~(USB_OTG_HCFG_FSLSS);
    }

    /* Make sure the FIFOs are flushed. */
    (void)USB_FlushTxFifo(USBx, 0x10U); /* all Tx FIFOs */
    (void)USB_FlushRxFifo(USBx);

    /* Clear all pending HC Interrupts */
    for (i = 0U; i < cfg.Host_channels; i++)
    {
        USBx_HC(i)->HCINT = 0xFFFFFFFFU;
        USBx_HC(i)->HCINTMSK = 0U;
    }

    /* Enable VBUS driving */
    (void)USB_DriveVbus(USBx, 1U);

    HAL_Delay(200U);

    /* Disable all interrupts. */
    USBx->GINTMSK = 0U;

    /* Clear any pending interrupts */
    USBx->GINTSTS = 0xFFFFFFFFU;

    if ((USBx->CID & (0x1U << 8)) != 0U)
    {
        /* set Rx FIFO size */
        USBx->GRXFSIZ = 0x200U;
        USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x100U << 16) & USB_OTG_NPTXFD) | 0x200U);
        USBx->HPTXFSIZ = (uint32_t)(((0xE0U << 16) & USB_OTG_HPTXFSIZ_PTXFD) | 0x300U);
    }
    else
    {
        /* set Rx FIFO size */
        USBx->GRXFSIZ = 0x80U;
        USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((0x60U << 16) & USB_OTG_NPTXFD) | 0x80U);
        USBx->HPTXFSIZ = (uint32_t)(((0x40U << 16) & USB_OTG_HPTXFSIZ_PTXFD) | 0xE0U);
    }

    /* Enable the common interrupts */
    if (cfg.dma_enable == 0U)
    {
        USBx->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
    }

    /* Enable interrupts matching to the Host mode ONLY */
    USBx->GINTMSK |= (USB_OTG_GINTMSK_PRTIM | USB_OTG_GINTMSK_HCIM |
                      USB_OTG_GINTMSK_SOFM | USB_OTG_GINTSTS_DISCINT |
                      USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM);

    return HAL_OK;
}

/**
  * @brief  USB_InitFSLSPClkSel : Initializes the FSLSPClkSel field of the
  *         HCFG register on the PHY type and set the right frame interval
  * @param  USBx  Selected device
  * @param  freq  clock frequency
  *          This parameter can be one of these values:
  *           HCFG_48_MHZ : Full Speed 48 MHz Clock
  *           HCFG_6_MHZ : Low Speed 6 MHz Clock
  * @retval HAL status
  */
HAL_StatusTypeDef USB_InitFSLSPClkSel(USB_OTG_GlobalTypeDef *USBx, uint8_t freq)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    USBx_HOST->HCFG &= ~(USB_OTG_HCFG_FSLSPCS);
    USBx_HOST->HCFG |= (uint32_t)freq & USB_OTG_HCFG_FSLSPCS;

    if (freq == HCFG_48_MHZ)
    {
        USBx_HOST->HFIR = 48000U;
    }
    else if (freq == HCFG_6_MHZ)
    {
        USBx_HOST->HFIR = 6000U;
    }
    else
    {
        /* ... */
    }

    return HAL_OK;
}

/**
* @brief  USB_OTG_ResetPort : Reset Host Port
  * @param  USBx  Selected device
  * @retval HAL status
  * @note (1)The application must wait at least 10 ms
  *   before clearing the reset bit.
  */
HAL_StatusTypeDef USB_ResetPort(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    volatile uint32_t hprt0 = 0U;

    hprt0 = USBx_HPRT0;

    hprt0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
               USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

    USBx_HPRT0 = (USB_OTG_HPRT_PRST | hprt0);
    HAL_Delay(100U); /* See Note #1 */
    USBx_HPRT0 = ((~USB_OTG_HPRT_PRST) & hprt0);
    HAL_Delay(10U);

    return HAL_OK;
}

/**
  * @brief  USB_DriveVbus : activate or de-activate vbus
  * @param  state  VBUS state
  *          This parameter can be one of these values:
  *           0 : VBUS Active
  *           1 : VBUS Inactive
  * @retval HAL status
*/
HAL_StatusTypeDef USB_DriveVbus(USB_OTG_GlobalTypeDef *USBx, uint8_t state)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    volatile uint32_t hprt0 = 0U;

    hprt0 = USBx_HPRT0;

    hprt0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
               USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);

    if (((hprt0 & USB_OTG_HPRT_PPWR) == 0U) && (state == 1U))
    {
        USBx_HPRT0 = (USB_OTG_HPRT_PPWR | hprt0);
    }
    if (((hprt0 & USB_OTG_HPRT_PPWR) == USB_OTG_HPRT_PPWR) && (state == 0U))
    {
        USBx_HPRT0 = ((~USB_OTG_HPRT_PPWR) & hprt0);
    }
    return HAL_OK;
}

/**
  * @brief  Return Host Core speed
  * @param  USBx  Selected device
  * @retval speed : Host speed
  *          This parameter can be one of these values:
  *            @arg HCD_SPEED_HIGH: High speed mode
  *            @arg HCD_SPEED_FULL: Full speed mode
  *            @arg HCD_SPEED_LOW: Low speed mode
  */
uint32_t USB_GetHostSpeed(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    volatile uint32_t hprt0 = 0U;

    hprt0 = USBx_HPRT0;
    return ((hprt0 & USB_OTG_HPRT_PSPD) >> 17);
}

/**
  * @brief  Return Host Current Frame number
  * @param  USBx  Selected device
  * @retval current frame number
*/
uint32_t USB_GetCurrentFrame(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    return (USBx_HOST->HFNUM & USB_OTG_HFNUM_FRNUM);
}

/**
  * @brief  Initialize a host channel
  * @param  USBx  Selected device
  * @param  ch_num  Channel number
  *         This parameter can be a value from 1 to 15
  * @param  epnum  Endpoint number
  *          This parameter can be a value from 1 to 15
  * @param  dev_address  Current device address
  *          This parameter can be a value from 0 to 255
  * @param  speed  Current device speed
  *          This parameter can be one of these values:
  *            @arg USB_OTG_SPEED_HIGH: High speed mode
  *            @arg USB_OTG_SPEED_FULL: Full speed mode
  *            @arg USB_OTG_SPEED_LOW: Low speed mode
  * @param  ep_type  Endpoint Type
  *          This parameter can be one of these values:
  *            @arg EP_TYPE_CTRL: Control type
  *            @arg EP_TYPE_ISOC: Isochronous type
  *            @arg EP_TYPE_BULK: Bulk type
  *            @arg EP_TYPE_INTR: Interrupt type
  * @param  mps  Max Packet Size
  *          This parameter can be a value from 0 to32K
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_Init(USB_OTG_GlobalTypeDef *USBx,
                              uint8_t ch_num,
                              uint8_t epnum,
                              uint8_t dev_address,
                              uint8_t speed,
                              uint8_t ep_type,
                              uint16_t mps)
{
    HAL_StatusTypeDef ret = HAL_OK;
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t HCcharEpDir, HCcharLowSpeed;

    /* Clear old interrupt conditions for this host channel. */
    USBx_HC((uint32_t)ch_num)->HCINT = 0xFFFFFFFFU;

    /* Enable channel interrupts required for this transfer. */
    switch (ep_type)
    {
    case EP_TYPE_CTRL:
    case EP_TYPE_BULK:
        USBx_HC((uint32_t)ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM |
                                              USB_OTG_HCINTMSK_STALLM |
                                              USB_OTG_HCINTMSK_TXERRM |
                                              USB_OTG_HCINTMSK_DTERRM |
                                              USB_OTG_HCINTMSK_AHBERR |
                                              USB_OTG_HCINTMSK_NAKM;

        if ((epnum & 0x80U) == 0x80U)
        {
            USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_BBERRM;
        }
        else
        {
            if ((USBx->CID & (0x1U << 8)) != 0U)
            {
                USBx_HC((uint32_t)ch_num)->HCINTMSK |= (USB_OTG_HCINTMSK_NYET | USB_OTG_HCINTMSK_ACKM);
            }
        }
        break;

    case EP_TYPE_INTR:
        USBx_HC((uint32_t)ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM |
                                              USB_OTG_HCINTMSK_STALLM |
                                              USB_OTG_HCINTMSK_TXERRM |
                                              USB_OTG_HCINTMSK_DTERRM |
                                              USB_OTG_HCINTMSK_NAKM |
                                              USB_OTG_HCINTMSK_AHBERR |
                                              USB_OTG_HCINTMSK_FRMORM;

        if ((epnum & 0x80U) == 0x80U)
        {
            USBx_HC((uint32_t)ch_num)->HCINTMSK |= USB_OTG_HCINTMSK_BBERRM;
        }

        break;

    case EP_TYPE_ISOC:
        USBx_HC((uint32_t)ch_num)->HCINTMSK = USB_OTG_HCINTMSK_XFRCM |
                                              USB_OTG_HCINTMSK_ACKM |
                                              USB_OTG_HCINTMSK_AHBERR |
                                              USB_OTG_HCINTMSK_FRMORM;

        if ((epnum & 0x80U) == 0x80U)
        {
            USBx_HC((uint32_t)ch_num)->HCINTMSK |= (USB_OTG_HCINTMSK_TXERRM | USB_OTG_HCINTMSK_BBERRM);
        }
        break;

    default:
        ret = HAL_ERROR;
        break;
    }

    /* Enable the top level host channel interrupt. */
    USBx_HOST->HAINTMSK |= 1UL << (ch_num & 0xFU);

    /* Make sure host channel interrupts are enabled. */
    USBx->GINTMSK |= USB_OTG_GINTMSK_HCIM;

    /* Program the HCCHAR register */
    if ((epnum & 0x80U) == 0x80U)
    {
        HCcharEpDir = (0x1U << 15) & USB_OTG_HCCHAR_EPDIR;
    }
    else
    {
        HCcharEpDir = 0U;
    }

    if (speed == HPRT0_PRTSPD_LOW_SPEED)
    {
        HCcharLowSpeed = (0x1U << 17) & USB_OTG_HCCHAR_LSDEV;
    }
    else
    {
        HCcharLowSpeed = 0U;
    }

    USBx_HC((uint32_t)ch_num)->HCCHAR = (((uint32_t)dev_address << 22) & USB_OTG_HCCHAR_DAD) |
                                        ((((uint32_t)epnum & 0x7FU) << 11) & USB_OTG_HCCHAR_EPNUM) |
                                        (((uint32_t)ep_type << 18) & USB_OTG_HCCHAR_EPTYP) |
                                        ((uint32_t)mps & USB_OTG_HCCHAR_MPSIZ) | HCcharEpDir | HCcharLowSpeed;

    if (ep_type == EP_TYPE_INTR)
    {
        USBx_HC((uint32_t)ch_num)->HCCHAR |= USB_OTG_HCCHAR_ODDFRM;
    }

    return ret;
}

/**
  * @brief  Start a transfer over a host channel
  * @param  USBx  Selected device
  * @param  hc  pointer to host channel structure
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_StartXfer(USB_OTG_GlobalTypeDef *USBx, USB_OTG_HCTypeDef *hc, uint8_t dma)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t ch_num = (uint32_t)hc->ch_num;
    static volatile uint32_t tmpreg = 0U;
    uint8_t is_oddframe;
    uint16_t len_words;
    uint16_t num_packets;
    uint16_t max_hc_pkt_count = 256U;

    if (((USBx->CID & (0x1U << 8)) != 0U) && (hc->speed == USBH_HS_SPEED))
    {
        if ((dma == 0U) && (hc->do_ping == 1U))
        {
            (void)USB_DoPing(USBx, hc->ch_num);
            return HAL_OK;
        }
        else if (dma == 1U)
        {
            USBx_HC(ch_num)->HCINTMSK &= ~(USB_OTG_HCINTMSK_NYET | USB_OTG_HCINTMSK_ACKM);
            hc->do_ping = 0U;
        }
        else
        {
            /* ... */
        }
    }

    /* Compute the expected number of packets associated to the transfer */
    if (hc->xfer_len > 0U)
    {
        num_packets = (uint16_t)((hc->xfer_len + hc->max_packet - 1U) / hc->max_packet);

        if (num_packets > max_hc_pkt_count)
        {
            num_packets = max_hc_pkt_count;
            hc->xfer_len = (uint32_t)num_packets * hc->max_packet;
        }
    }
    else
    {
        num_packets = 1U;
    }
    if (hc->ep_is_in != 0U)
    {
        hc->xfer_len = (uint32_t)num_packets * hc->max_packet;
    }

    /* Initialize the HCTSIZn register */
    USBx_HC(ch_num)->HCTSIZ = (hc->xfer_len & USB_OTG_HCTSIZ_XFRSIZ) |
                              (((uint32_t)num_packets << 19) & USB_OTG_HCTSIZ_PKTCNT) |
                              (((uint32_t)hc->data_pid << 29) & USB_OTG_HCTSIZ_DPID);

    if (dma != 0U)
    {
        /* xfer_buff MUST be 32-bits aligned */
        USBx_HC(ch_num)->HCDMA = (uint32_t)hc->xfer_buff;
    }

    is_oddframe = (((uint32_t)USBx_HOST->HFNUM & 0x01U) != 0U) ? 0U : 1U;
    USBx_HC(ch_num)->HCCHAR &= ~USB_OTG_HCCHAR_ODDFRM;
    USBx_HC(ch_num)->HCCHAR |= (uint32_t)is_oddframe << 29;

    /* Set host channel enable */
    tmpreg = USBx_HC(ch_num)->HCCHAR;
    tmpreg &= ~USB_OTG_HCCHAR_CHDIS;

    /* make sure to set the correct ep direction */
    if (hc->ep_is_in != 0U)
    {
        tmpreg |= USB_OTG_HCCHAR_EPDIR;
    }
    else
    {
        tmpreg &= ~USB_OTG_HCCHAR_EPDIR;
    }
    tmpreg |= USB_OTG_HCCHAR_CHENA;
    USBx_HC(ch_num)->HCCHAR = tmpreg;

    if (dma == 0U) /* Slave mode */
    {
        if ((hc->ep_is_in == 0U) && (hc->xfer_len > 0U))
        {
            switch (hc->ep_type)
            {
            /* Non periodic transfer */
            case EP_TYPE_CTRL:
            case EP_TYPE_BULK:

                len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);

                /* check if there is enough space in FIFO space */
                if (len_words > (USBx->HNPTXSTS & 0xFFFFU))
                {
                    /* need to process data in nptxfempty interrupt */
                    USBx->GINTMSK |= USB_OTG_GINTMSK_NPTXFEM;
                }
                break;

            /* Periodic transfer */
            case EP_TYPE_INTR:
            case EP_TYPE_ISOC:
                len_words = (uint16_t)((hc->xfer_len + 3U) / 4U);
                /* check if there is enough space in FIFO space */
                if (len_words > (USBx_HOST->HPTXSTS & 0xFFFFU)) /* split the transfer */
                {
                    /* need to process data in ptxfempty interrupt */
                    USBx->GINTMSK |= USB_OTG_GINTMSK_PTXFEM;
                }
                break;

            default:
                break;
            }

            /* Write packet into the Tx FIFO. */
            (void)USB_WritePacket(USBx, hc->xfer_buff, hc->ch_num, (uint16_t)hc->xfer_len, 0);
        }
    }

    return HAL_OK;
}

/**
  * @brief Read all host channel interrupts status
  * @param  USBx  Selected device
  * @retval HAL state
  */
uint32_t USB_HC_ReadInterrupt(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    return ((USBx_HOST->HAINT) & 0xFFFFU);
}

/**
  * @brief  Halt a host channel
  * @param  USBx  Selected device
  * @param  hc_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_HC_Halt(USB_OTG_GlobalTypeDef *USBx, uint8_t hc_num)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t hcnum = (uint32_t)hc_num;
    uint32_t count = 0U;
    uint32_t HcEpType = (USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_EPTYP) >> 18;

    /* Check for space in the request queue to issue the halt. */
    if ((HcEpType == HCCHAR_CTRL) || (HcEpType == HCCHAR_BULK))
    {
        USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHDIS;

        if ((USBx->HNPTXSTS & (0xFFU << 16)) == 0U)
        {
            USBx_HC(hcnum)->HCCHAR &= ~USB_OTG_HCCHAR_CHENA;
            USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
            USBx_HC(hcnum)->HCCHAR &= ~USB_OTG_HCCHAR_EPDIR;
            do
            {
                if (++count > 1000U)
                {
                    break;
                }
            } while ((USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
        }
        else
        {
            USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
        }
    }
    else
    {
        USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHDIS;

        if ((USBx_HOST->HPTXSTS & (0xFFU << 16)) == 0U)
        {
            USBx_HC(hcnum)->HCCHAR &= ~USB_OTG_HCCHAR_CHENA;
            USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
            USBx_HC(hcnum)->HCCHAR &= ~USB_OTG_HCCHAR_EPDIR;
            do
            {
                if (++count > 1000U)
                {
                    break;
                }
            } while ((USBx_HC(hcnum)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
        }
        else
        {
            USBx_HC(hcnum)->HCCHAR |= USB_OTG_HCCHAR_CHENA;
        }
    }

    return HAL_OK;
}

/**
  * @brief  Initiate Do Ping protocol
  * @param  USBx  Selected device
  * @param  hc_num  Host Channel number
  *         This parameter can be a value from 1 to 15
  * @retval HAL state
  */
HAL_StatusTypeDef USB_DoPing(USB_OTG_GlobalTypeDef *USBx, uint8_t ch_num)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t chnum = (uint32_t)ch_num;
    uint32_t num_packets = 1U;
    uint32_t tmpreg;

    USBx_HC(chnum)->HCTSIZ = ((num_packets << 19) & USB_OTG_HCTSIZ_PKTCNT) |
                             USB_OTG_HCTSIZ_DOPING;

    /* Set host channel enable */
    tmpreg = USBx_HC(chnum)->HCCHAR;
    tmpreg &= ~USB_OTG_HCCHAR_CHDIS;
    tmpreg |= USB_OTG_HCCHAR_CHENA;
    USBx_HC(chnum)->HCCHAR = tmpreg;

    return HAL_OK;
}

/**
  * @brief  Stop Host Core
  * @param  USBx  Selected device
  * @retval HAL state
  */
HAL_StatusTypeDef USB_StopHost(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;
    uint32_t count = 0U;
    uint32_t value;
    uint32_t i;

    (void)USB_DisableGlobalInt(USBx);

    /* Flush FIFO */
    (void)USB_FlushTxFifo(USBx, 0x10U);
    (void)USB_FlushRxFifo(USBx);

    /* Flush out any leftover queued requests. */
    for (i = 0U; i <= 15U; i++)
    {
        value = USBx_HC(i)->HCCHAR;
        value |= USB_OTG_HCCHAR_CHDIS;
        value &= ~USB_OTG_HCCHAR_CHENA;
        value &= ~USB_OTG_HCCHAR_EPDIR;
        USBx_HC(i)->HCCHAR = value;
    }

    /* Halt all channels to put them into a known state. */
    for (i = 0U; i <= 15U; i++)
    {
        value = USBx_HC(i)->HCCHAR;
        value |= USB_OTG_HCCHAR_CHDIS;
        value |= USB_OTG_HCCHAR_CHENA;
        value &= ~USB_OTG_HCCHAR_EPDIR;
        USBx_HC(i)->HCCHAR = value;

        do
        {
            if (++count > 1000U)
            {
                break;
            }
        } while ((USBx_HC(i)->HCCHAR & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
    }

    /* Clear any pending Host interrupts */
    USBx_HOST->HAINT = 0xFFFFFFFFU;
    USBx->GINTSTS = 0xFFFFFFFFU;
    (void)USB_EnableGlobalInt(USBx);

    return HAL_OK;
}

/**
  * @brief  USB_ActivateRemoteWakeup active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateRemoteWakeup(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    if ((USBx_DEVICE->DSTS & USB_OTG_DSTS_SUSPSTS) == USB_OTG_DSTS_SUSPSTS)
    {
        /* active Remote wakeup signalling */
        USBx_DEVICE->DCTL |= USB_OTG_DCTL_RWUSIG;
    }

    return HAL_OK;
}

/**
  * @brief  USB_DeActivateRemoteWakeup de-active remote wakeup signalling
  * @param  USBx Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeActivateRemoteWakeup(USB_OTG_GlobalTypeDef *USBx)
{
    uint32_t USBx_BASE = (uint32_t)USBx;

    /* active Remote wakeup signalling */
    USBx_DEVICE->DCTL &= ~(USB_OTG_DCTL_RWUSIG);

    return HAL_OK;
}
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */
#endif /* defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED) */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


#endif 

