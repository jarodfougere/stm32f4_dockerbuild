/**
 * @file drivers.h
 * @author your name (you@domain.com)
 * @brief Bundled drivers header to be included by middleware module
 * @version 0.1
 * @date 2020-02-27
 * 
 * @copyright Copyright Rimot.io Incorporated (c) 2020
 * @author Carl Mattatall
 */

//CARL TODO: ADD BSD-3 LICENSE

#ifndef RIMOT_DRIVERS
#define RIMOT_DRIVERS

#if defined(MCU_APP)
#include "stm32f4xx.h"
#else
//TODO: PORTABLE INCLUSION FOR SYSTEM-BASED APP
#endif /* MCU_APP */

#endif /* RIMOT_DRIVERS */