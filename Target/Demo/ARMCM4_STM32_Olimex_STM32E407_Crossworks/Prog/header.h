/************************************************************************************//**
* \file         Demo\ARMCM4_STM32_Olimex_STM32E407_Crossworks\Prog\header.h
* \brief        Generic header file.
* \ingroup      Prog_ARMCM4_STM32_Olimex_STM32E407_Crossworks
* \internal
*----------------------------------------------------------------------------------------
*                          C O P Y R I G H T
*----------------------------------------------------------------------------------------
*   Copyright (c) 2013  by Feaser    http://www.feaser.com    All rights reserved
*
*----------------------------------------------------------------------------------------
*                            L I C E N S E
*----------------------------------------------------------------------------------------
* This file is part of OpenBLT. OpenBLT is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option) any later
* version.
*
* OpenBLT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
* PURPOSE. See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with OpenBLT.
* If not, see <http://www.gnu.org/licenses/>.
*
* A special exception to the GPL is included to allow you to distribute a combined work 
* that includes OpenBLT without being obliged to provide the source code for any 
* proprietary components. The exception text is included at the bottom of the license
* file <license.html>.
* 
* \endinternal
****************************************************************************************/
#ifndef HEADER_H
#define HEADER_H

/****************************************************************************************
* Include files
****************************************************************************************/
#include "../Boot/blt_conf.h"                          /* bootloader configuration     */
#include "stm32f4xx.h"                                 /* STM32 registers              */
#include "stm32f4xx_conf.h"                            /* STM32 peripheral drivers     */
#include "boot.h"                                      /* bootloader interface driver  */
#include "irq.h"                                       /* IRQ driver                   */
#include "led.h"                                       /* LED driver                   */
#include "timer.h"                                     /* Timer driver                 */
#include "net.h"                                       /* TCP/IP server application    */


#endif /* HEADER_H */
/*********************************** end of header.h ***********************************/
