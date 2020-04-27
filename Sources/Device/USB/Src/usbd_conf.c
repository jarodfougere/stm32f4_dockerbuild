#if defined(MCU_APP)

#include <stdint.h>

#include "usbd_conf.h"
#include "usbd_def.h"
#include "usbd_core.h"

#include "rimot_LL_debug.h"
#include "rimot_usb.h"
#include "rimot_interrupts.h"
#include "rimot_cortex_config.h"

typedef enum
{
    USBD_FUNC_STATE_disabled = 0U,
    USBD_FUNC_STATE_enabled = 1U,
}   USBD_FUNC_STATE_t;

static USBD_StatusTypeDef USBD_Get_USB_Status(uint8_t status);

USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev)
{
    usbDriver_LinkDeviceDriverHandle(pdev);
    int LLstatus = usbLLDriverInit();
    USBD_StatusTypeDef status = USBD_Get_USB_Status(LLstatus);
    return status;
}

/**
  * @brief  Setup stage callback
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_SetupStageCallback(usbDriverHandle_t *hpcd)
{
    USBD_LL_SetupStage((USBD_HandleTypeDef *)hpcd->pData, (uint8_t *)hpcd->Setup);
}

/**
  * @brief  Data Out stage callback.
  * @param  hpcd: driver handle
  * @param  epnum: Endpoint number
  * @retval None
  */
void usbDeviceDriver_DataOutStageCallback(usbDriverHandle_t *hpcd, uint8_t epnum)
{
    USBD_LL_DataOutStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

/**
  * @brief  Data In stage callback.
  * @param  hpcd: driver handle
  * @param  epnum: Endpoint number
  * @retval None
  */
void usbDeviceDriver_DataInStageCallback(usbDriverHandle_t *hpcd, uint8_t epnum)
{
    USBD_LL_DataInStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

/**
  * @brief  SOF callback.
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_SOFCallback(usbDriverHandle_t *hpcd)
{
    USBD_LL_SOF((USBD_HandleTypeDef *)hpcd->pData);
}

/**
  * @brief  Reset callback.
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_ResetCallback(usbDriverHandle_t *hpcd)
{
#if defined(STM32F411RE) || defined(STM32F411VE)
    /* These mcu ONLY support FS mode */
    LL_ASSERT(hpcd->Init.speed == USBD_DEVSPEED_TYPE_fs);
#endif

    /* Set Speed. */
    USBD_LL_SetSpeed((USBD_HandleTypeDef *)hpcd->pData,
                     (USBD_SpeedTypeDef)hpcd->Init.speed);

    /* Reset Device. */
    USBD_LL_Reset((USBD_HandleTypeDef *)hpcd->pData);
}

/**
  * @brief  Suspend callback.
  * When Low power mode is enabled the debug cannot be used (IAR, Keil doesn't support it)
  * @note 
  * THIS SHOULD BE THE VERY FIRST INTERRUPT CALLBACK THAT OCCURS AS PART OF 
  * THE USB DRIVER INIT + ENUMERATION PROCESS
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_SuspendCallback(usbDriverHandle_t *hpcd)
{
    /* Inform USB library that core enters in suspend Mode. */
    USBD_LL_Suspend((USBD_HandleTypeDef *)hpcd->pData);
    usbGatePhyClock();

    /* Enter in STOP mode. */
    if (hpcd->Init.low_power_enable)
    {
        /* Set SLEEPDEEP bit and SleepOnExit of Cortex System Control Register. */
        SCB->SCR |= (uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
    }
}

/**
  * @brief  Resume callback.
  * When Low power mode is enabled the debug cannot be used (IAR, Keil doesn't support it)
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_ResumeCallback(usbDriverHandle_t *hpcd)
{
    USBD_LL_Resume((USBD_HandleTypeDef *)hpcd->pData);
}

/**
  * @brief  ISOOUTIncomplete callback.
  * @param  hpcd: driver handle
  * @param  epnum: Endpoint number
  * @retval None
  */
void usbDeviceDriver_ISOOUTIncompleteCallback(usbDriverHandle_t *hpcd, uint8_t epnum)
{
    USBD_LL_IsoOUTIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

/**
  * @brief  ISOINIncomplete callback.
  * @param  hpcd: driver handle
  * @param  epnum: Endpoint number
  * @retval None
  */
void usbDeviceDriver_ISOINIncompleteCallback(usbDriverHandle_t *hpcd, uint8_t epnum)
{
    USBD_LL_IsoINIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

/**
  * @brief  Connect callback.
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_ConnectCallback(usbDriverHandle_t *hpcd)
{
    USBD_LL_DevConnected((USBD_HandleTypeDef *)hpcd->pData);
}

/**
  * @brief  Disconnect callback.
  * @param  hpcd: driver handle
  * @retval None
  */
void usbDeviceDriver_DisconnectCallback(usbDriverHandle_t *hpcd)
{
    USBD_LL_DevDisconnected((USBD_HandleTypeDef *)hpcd->pData);
}

/**
  * @brief  De-Initializes the low level portion of the device driver.
  * @param  pdev: Device handle
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev)
{
    usbDriverStop();
    return USBD_OK;
}

/**
  * @brief  Starts the low level portion of the device driver. 
  * @param  pdev: Device handle
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev)
{
    usbDriverStart();
    return USBD_OK;
}

/**
  * @brief  Stops the low level portion of the device driver.
  * @param  pdev: Device handle
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev)
{
    USBD_StatusTypeDef usb_status;
    usb_status = USBD_Get_USB_Status(usbDriverStop());
    return usb_status;
}

/**
  * @brief  Opens an endpoint of the low level driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @param  ep_type: Endpoint type
  * @param  ep_mps: Endpoint max packet size
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t ep_type, uint16_t ep_mps)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;
    uint8_t status;
    status = usbDeviceDriver_OpenEndpoint(driver, ep_addr, ep_mps, ep_type);
    USBD_StatusTypeDef usb_status = USBD_Get_USB_Status(status);
    return usb_status;
}

/**
  * @brief  Closes an endpoint of the low level driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;
    usbDeviceDriver_CloseEndpoint(driver, ep_addr);
    return USBD_OK;
}

/**
  * @brief  Flushes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)&pdev->pData;
    uint8_t status = (uint8_t)usbDeviceDriver_FlushEndpoint(driver, ep_addr);
    USBD_StatusTypeDef usb_status = USBD_Get_USB_Status(status);
    return usb_status;
}

/**
  * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)&pdev->pData;
    uint8_t status = usbDeviceDriver_StallEndpoint(driver, ep_addr);
    USBD_StatusTypeDef usb_status = USBD_Get_USB_Status(status);
    return usb_status;
}

/**
  * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)&pdev->pData;
    int status = usbDeviceDriver_ClrStalledEndpoint(driver, ep_addr);
    USBD_StatusTypeDef usb_status = USBD_Get_USB_Status(status);
    return usb_status;
}

/**
  * @brief  Returns Stall condition.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @retval Stall (1: Yes, 0: No)
  */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;

    if ((ep_addr & 0x80) == 0x80)
    {
        return driver->IN_ep[ep_addr & 0x7F].is_stall;
    }
    else
    {
        return driver->OUT_ep[ep_addr & 0x7F].is_stall;
    }
}

/**
  * @brief  Assigns a USB address to the device.
  * @param  pdev: Device handle
  * @param  dev_addr: Device address
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;
    uint8_t status = usbDeviceDriver_setDeviceAddress(driver, dev_addr);
    USBD_StatusTypeDef usb_status = USBD_Get_USB_Status(status);
    return usb_status;
}

/**
  * @brief  Transmits data over an endpoint.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @param  pbuf: Pointer to data to be sent
  * @param  size: Data size    
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev,
                                    uint8_t ep_addr,
                                    uint8_t *pbuf,
                                    uint16_t size)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;
    usbDeviceDriver_EP_Transmit(driver, ep_addr, pbuf, size);
    return USBD_OK;
}

/**
  * @brief  Prepares an endpoint for reception.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @param  pbuf: Pointer to data to be received
  * @param  size: Data size
  * @retval USBD status
  */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t size)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;
    usbDeviceDriver_EP_Receive(driver, ep_addr, pbuf, size);
    return USBD_OK;
}

/**
  * @brief  Returns the last transfered packet size.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint number
  * @retval Recived Data Size
  */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
    usbDriverHandle_t *driver = (usbDriverHandle_t *)pdev->pData;
    return usbDeviceDriver_GetEPRxCnt(driver, ep_addr);
}

/**
  * @brief  Retuns the USB status depending on the incoming status
  * @param  status the incoming status.
  * @retval One of USBD_STATUS_TypeDef
  */
static USBD_StatusTypeDef USBD_Get_USB_Status(uint8_t status)
{
    USBD_StatusTypeDef usb_status = USBD_OK;
    switch (status)
    {
    case 0:
        usb_status = USBD_OK;
        break;
    case 1:
        usb_status = USBD_FAIL;
        break;
    case 2:
        usb_status = USBD_BUSY;
        break;
    case 3:
        usb_status = USBD_FAIL;
        break;
    default:
        usb_status = USBD_FAIL;
        break;
    }
    return usb_status;
}
#endif /* MCU_APP */
