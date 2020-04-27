
#if 0

#include "stm32f4xx_hal_pcd.h"
#include "rimot_rcc.h"

#include "usbd_conf.h"

#include "rimot_usb.h"
#include "rimot_LL_debug.h"
#include "stm32f4xx_ll_usb.h"

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define PCD_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define PCD_MAX(a, b) (((a) > (b)) ? (a) : (b))

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
static HAL_StatusTypeDef PCD_WriteEmptyTxFifo(PCD_HandleTypeDef *hpcd, uint32_t epnum);
static HAL_StatusTypeDef PCD_EP_OutXfrComplete_int(PCD_HandleTypeDef *hpcd, uint32_t epnum);
static HAL_StatusTypeDef PCD_EP_OutSetupPacket_int(PCD_HandleTypeDef *hpcd, uint32_t epnum);
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */


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
    #if 0
    LL_ASSERT(IS_PCD_ALL_INSTANCE(hpcd->Instance));
    #endif 

    USBx = hpcd->Instance;

    if (hpcd->State == HAL_PCD_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hpcd->Lock = HAL_UNLOCKED;

        /* 
         *  Init the low level hardware like GPIO, 
         *  CLOCK, NVIC... using injected function.
         */
        USBD_PhyInit();
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

    /* DeInit the low level hardware: CLOCK, NVIC.*/
    HAL_PCD_MspDeInit(hpcd);

    hpcd->State = HAL_PCD_STATE_RESET;

    return HAL_OK;
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


/**
  * @brief  Start the USB device
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd)
{
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
    USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

    __HAL_LOCK(hpcd);
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
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
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
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
        if(0 == USB_ReadInterrupts(hpcd->Instance))
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

                        usbDeviceDriver_DataInStageCallback(hpcd, 
                                                            (uint8_t)epnum);

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

                HAL_PCDEx_LPM_Callback(hpcd, PCD_LPM_L0_ACTIVE);
            }
            else
            {
                HAL_PCD_ResumeCallback(hpcd);
            }

            __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_WKUINT);
        }

        /* Handle Suspend Interrupt */
        if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_USBSUSP))
        {
            if ((USBx_DEVICE->DSTS & USB_OTG_DSTS_SUSPSTS) == USB_OTG_DSTS_SUSPSTS)
            {
                HAL_PCD_SuspendCallback(hpcd);
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

                HAL_PCDEx_LPM_Callback(hpcd, PCD_LPM_L1_ACTIVE);
            }
            else
            {
                HAL_PCD_SuspendCallback(hpcd);
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

            usbDeviceDriver_ResetCallback(hpcd);

            __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_ENUMDNE);
        }

        /* Handle RxQLevel Interrupt */
        if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_RXFLVL))
        {
            USB_MASK_INTERRUPT(hpcd->Instance, USB_OTG_GINTSTS_RXFLVL);

            temp = USBx->GRXSTSP;

            ep = &hpcd->OUT_ep[temp & USB_OTG_GRXSTSP_EPNUM];

            if (((temp & USB_OTG_GRXSTSP_PKTSTS) >> 17) == STS_DATA_UPDT)
            {
                if ((temp & USB_OTG_GRXSTSP_BCNT) != 0U)
                {
                    (void)USB_ReadPacket(USBx, ep->xfer_buff,
                                         (uint16_t)((temp & USB_OTG_GRXSTSP_BCNT) >> 4));

                    ep->xfer_buff += (temp & USB_OTG_GRXSTSP_BCNT) >> 4;
                    ep->xfer_count += (temp & USB_OTG_GRXSTSP_BCNT) >> 4;
                }
            }
            else if (((temp & USB_OTG_GRXSTSP_PKTSTS) >> 17) == STS_SETUP_UPDT)
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
            HAL_PCD_SOFCallback(hpcd);

            __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_SOF);
        }

        /* Handle Incomplete ISO IN Interrupt */
        if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_IISOIXFR))
        {
            /* Keep application checking the corresponding Iso IN endpoint
      causing the incomplete Interrupt */
            epnum = 0U;

            usbDeviceDriver_ISOINIncompleteCallback(hpcd, (uint8_t)epnum);

            __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_IISOIXFR);
        }

        /* Handle Incomplete ISO OUT Interrupt */
        if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT))
        {
            /* Keep application checking the corresponding Iso OUT endpoint
      causing the incomplete Interrupt */
            epnum = 0U;

            HAL_PCD_ISOOUTIncompleteCallback(hpcd, (uint8_t)epnum);

            __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_PXFR_INCOMPISOOUT);
        }

        /* Handle Connection event Interrupt */
        if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_SRQINT))
        {
            HAL_PCD_ConnectCallback(hpcd);

            __HAL_PCD_CLEAR_FLAG(hpcd, USB_OTG_GINTSTS_SRQINT);
        }

        /* Handle Disconnection event Interrupt */
        if (__HAL_PCD_GET_FLAG(hpcd, USB_OTG_GINTSTS_OTGINT))
        {
            temp = hpcd->Instance->GOTGINT;

            if ((temp & USB_OTG_GOTGINT_SEDET) == USB_OTG_GOTGINT_SEDET)
            {
                HAL_PCD_DisconnectCallback(hpcd);
            }
            hpcd->Instance->GOTGINT |= temp;
        }
    }
}
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */










/**
  * @brief  Connect the USB device
  * @param  hpcd PCD handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PCD_DevConnect(PCD_HandleTypeDef *hpcd)
{
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
    USB_OTG_GlobalTypeDef *USBx = hpcd->Instance;
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

    __HAL_LOCK(hpcd);
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
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
    HAL_StatusTypeDef ret = HAL_OK;
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
    ep->num = ep_addr & EP_ADDR_MSK;

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
  * @brief  Return the PCD handle state.
  * @param  hpcd PCD handle
  * @retval HAL state
  */
PCD_StateTypeDef HAL_PCD_GetState(PCD_HandleTypeDef *hpcd)
{
    return hpcd->State;
}



#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
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

        ep->xfer_buff += len;
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
            HAL_PCD_SetupStageCallback(hpcd);

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

                usbDeviceDriver_DataOutStageCallback(hpcd, (uint8_t)epnum);

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

                usbDeviceDriver_DataOutStageCallback(hpcd, (uint8_t)epnum);
            }
        }
        else
        {
            usbDeviceDriver_DataOutStageCallback(hpcd, (uint8_t)epnum);
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
    HAL_PCD_SetupStageCallback(hpcd);


    if ((gSNPSiD > USB_OTG_CORE_ID_300A) && (hpcd->Init.dma_enable == 1U))
    {
        (void)USB_EP0_OutStart(hpcd->Instance, 1U, (uint8_t *)hpcd->Setup);
    }

    return HAL_OK;
}
#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */


#endif /* defined (USB_OTG_FS) || defined (USB_OTG_HS) */

#endif 


