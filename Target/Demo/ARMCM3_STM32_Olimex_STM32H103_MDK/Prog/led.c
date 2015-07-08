#include "header.h"                                    /* generic header               */


/****************************************************************************************
* Macro definitions
****************************************************************************************/
/** \brief Toggle interval time in milliseconds. */
#define LED_TOGGLE_MS  (500)


/************************************************************************************//**
** \brief     Initializes the LED. The board doesn't have a dedicted LED so an
**            indicator on the LCD is used instead.
** \return    none.
**
****************************************************************************************/
void LedInit(void)
{
	GPIO_InitTypeDef  gpio_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpio_init.GPIO_Pin   = GPIO_Pin_5;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &gpio_init);
}


/************************************************************************************//**
** \brief     Toggles the LED at a fixed time interval.
** \return    none.
**
****************************************************************************************/
void LedToggle(void)
{
	static unsigned char led_toggle_state = 0;
	static unsigned long timer_counter_last = 0;
	unsigned long timer_counter_now;

	/* check if toggle interval time passed */
	timer_counter_now = TimerGet();
	if ( (timer_counter_now - timer_counter_last) < LED_TOGGLE_MS)
	{
		/* not yet time to toggle */
		return;
	}
  
	/* determine toggle action */
	if (led_toggle_state == 0)
	{
		led_toggle_state = 1;
		/* turn the LED on */
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	else
	{
		led_toggle_state = 0;
		/* turn the LED off */
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}

	/* store toggle time to determine next toggle interval */
	timer_counter_last = timer_counter_now;
}


/*********************************** end of led.c **************************************/
/************************************************************************************//**
* \file         Demo\ARMCM3_STM32_Olimex_STM32H103_IAR\Prog\led.c
* \brief        LED driver source file.
* \ingroup      Prog_ARMCM3_STM32_Olimex_STM32H103_IAR
* \internal
*----------------------------------------------------------------------------------------
*                          C O P Y R I G H T
*----------------------------------------------------------------------------------------
*   Copyright (c) 2012  by Feaser    http://www.feaser.com    All rights reserved
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
