/**
 * @file bootjump.c
 * @author Carl Mattatall (cmattatall2@gmail.com)
 * @brief Bootloader API file
 * @version 0.1
 * @date 2020-10-26
 *
 * @copyright Copyright (c) 2020
 *
 * @note
 * @todo
 */

#include <stdint.h>

#include "bootjump.h"

void SysMemBootJump(void)
{
    /* Jump to start of bootloader in system memory */
    void (*bootloader)(void);
    volatile uint32_t addr = USBD_DFU_APP_DEFAULT_ADDRESS;
    bootloader             = (void (*)(void))(*((uint32_t *)(addr)));
    bootloader();
}
