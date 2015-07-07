/************************************************************************************//**
* \file         Demo\HCS12_Evbplus_Dragon12p_CodeWarrior\Prog\timer.c
* \brief        Timer driver source file.
* \ingroup      Prog_HCS12_Evbplus_Dragon12p_CodeWarrior
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

/****************************************************************************************
* Include files
****************************************************************************************/
#include "header.h"                                    /* generic header               */


/****************************************************************************************
* Macro definitions
****************************************************************************************/
/** \brief Number of free running timer counts in 1 millisecond. */
#define TIMER_COUNTS_PER_MS      (BOOT_CPU_SYSTEM_SPEED_KHZ)


/****************************************************************************************
* Local data declarations
****************************************************************************************/
/** \brief Local variable for storing the number of milliseconds that have elapsed since
 *         startup.
 */
static unsigned long millisecond_counter;


/************************************************************************************//**
** \brief     Initializes the timer.
** \return    none.
**
****************************************************************************************/
void TimeInit(void)
{
  /* reset the timer configuration. note that this also sets the default prescaler
   * to 1, so the free running counter runs at the same speed as the system clock.
   */
  TimeDeinit();

  /* configure timer channel 0 as a 1 millisecond software timer */
  TIOS_IOS0 = 1;
  /* make sure timer 0 interrupt flag is cleared */
  TFLG1 = TFLG1_C0F_MASK;
  /* generate output compare event in 1 milliseconds from now */
  TC0 = TCNT + TIMER_COUNTS_PER_MS;
  /* enable the interrupt for timer channel 0 */
  TIE_C0I = 1;
  /* enable the timer subsystem */
  TSCR1_TEN = 1;
  /* reset the millisecond counter */
  TimeSet(0);
} /*** end of TimeInit ***/


/************************************************************************************//**
** \brief     Stops and disables the timer.
** \return    none.
**
****************************************************************************************/
void TimeDeinit(void)
{
  /* bring the timer subsystem back into its reset state */
  TIE = 0;
  TSCR1 = 0;
  TSCR2 = 0;
  TIOS = 0;
  TTOV = 0;
  TCTL1 = 0;
  TCTL2 = 0;
  TCTL3 = 0;
  TCTL4 = 0;
} /*** end of TimeDeinit ***/


/************************************************************************************//**
** \brief     Sets the initial counter value of the millisecond timer.
** \param     timer_value initialize value of the millisecond timer.
** \return    none.
**
****************************************************************************************/
void TimeSet(unsigned long timer_value)
{
  /* set the millisecond counter */
  millisecond_counter = timer_value;
} /*** end of TimeSet ***/


/************************************************************************************//**
** \brief     Obtains the counter value of the millisecond timer.
** \return    Current value of the millisecond timer.
**
****************************************************************************************/
unsigned long TimeGet(void)
{
  /* read and return the millisecond counter value */
  return millisecond_counter;
} /*** end of TimeGet ***/


/************************************************************************************//**
** \brief     Interrupt service routine of the timer.
** \return    none.
**
****************************************************************************************/
__interrupt void TimeISRHandler(void)
{
  /* make sure timer 0 interrupt flag is cleared */
  TFLG1 = TFLG1_C0F_MASK;
  /* generate output compare event in 1 milliseconds from now */
  TC0 += TIMER_COUNTS_PER_MS;
  /* increment the millisecond counter */
  millisecond_counter++;
} /*** end of TimeISRHandler ***/


/*********************************** end of time.c *************************************/
