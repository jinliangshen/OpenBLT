/************************************************************************************//**
* \file         Source\ARMCM3_EFM32\GCC\vectors.c
* \brief        Bootloader interrupt vector table source file.
* \ingroup      Target_ARMCM3_EFM32
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

/****************************************************************************************
* Include files
****************************************************************************************/
#include "boot.h"                                    /* bootloader generic header      */


/****************************************************************************************
* External data declarations
****************************************************************************************/
extern blt_int32u _estack;                            /* stack end address (memory.x)  */


/************************************************************************************//**
** \brief     Catch-all for unused interrrupt service routines.
** \return    none.
**
****************************************************************************************/
void UnusedISR(void)
{
  /* unexpected interrupt occured, so trigger an assertion to halt the system */
  ASSERT_RT(BLT_FALSE);
} /*** end of UnusedISR ***/


/****************************************************************************************
*                I N T E R R U P T     V E C T O R     T A B L E
****************************************************************************************/
extern void reset_handler(void);                      /* implemented in cstart.c       */
/** \brief Structure type for vector table entries. */
typedef union
{
  void (*func)(void);                                 /**< for ISR function pointers   */
  blt_int32u ptr;                                     /**< for stack pointer entry     */
}tIsrFunc;

/** \brief Interrupt vector table. */
__attribute__ ((section(".isr_vector")))
const tIsrFunc _vectab[] =
{
  { .ptr = (blt_int32u)&_estack },                    /* the initial stack pointer     */
  { reset_handler               },                    /* the reset handler             */
  { UnusedISR                   },                    /* NMI Handler                   */
  { UnusedISR                   },                    /* Hard Fault Handler            */
  { UnusedISR                   },                    /* MPU Fault Handler             */
  { UnusedISR                   },                    /* Bus Fault Handler             */
  { UnusedISR                   },                    /* Usage Fault Handler           */
  { UnusedISR                   },                    /* Reserved                      */
  { UnusedISR                   },                    /* Reserved                      */
  { UnusedISR                   },                    /* Reserved                      */
  { UnusedISR                   },                    /* Reserved                      */
  { UnusedISR                   },                    /* SVCall Handler                */
  { UnusedISR                   },                    /* Debug Monitor Handler         */
  { UnusedISR                   },                    /* Reserved                      */
  { UnusedISR                   },                    /* PendSV Handler                */
  { UnusedISR                   },                    /* SysTick Handler               */
  { UnusedISR                   },                    /* 0 - DMA Handler               */
  { UnusedISR                   },                    /* 1 - GPIO_EVEN Handler         */
  { UnusedISR                   },                    /* 2 - TIMER0 Handler            */
  { UnusedISR                   },                    /* 3 - USART0_RX Handler         */
  { UnusedISR                   },                    /* 4 - USART0_TX Handler         */
  { UnusedISR                   },                    /* 5 - ACMP0 Handler             */
  { UnusedISR                   },                    /* 6 - ADC0 Handler              */
  { UnusedISR                   },                    /* 7 - DAC0 Handler              */
  { UnusedISR                   },                    /* 8 - I2C0 Handler              */
  { UnusedISR                   },                    /* 9 - GPIO_ODD Handler          */
  { UnusedISR                   },                    /* 10 - TIMER1 Handler           */
  { UnusedISR                   },                    /* 11 - TIMER2 Handler           */
  { UnusedISR                   },                    /* 12 - USART1_RX Handler        */
  { UnusedISR                   },                    /* 13 - USART1_TX Handler        */
  { UnusedISR                   },                    /* 14 - USART2_RX Handler        */
  { UnusedISR                   },                    /* 15 - USART2_TX Handler        */
  { UnusedISR                   },                    /* 16 - UART0_RX Handler         */
  { UnusedISR                   },                    /* 17 - UART0_TX Handler         */
  { UnusedISR                   },                    /* 18 - LEUART0 Handler          */
  { UnusedISR                   },                    /* 19 - LEUART1 Handler          */
  { UnusedISR                   },                    /* 20 - LETIMER0 Handler         */
  { UnusedISR                   },                    /* 21 - PCNT0 Handler            */
  { UnusedISR                   },                    /* 22 - PCNT1 Handler            */
  { UnusedISR                   },                    /* 23 - PCNT2 Handler            */
  { UnusedISR                   },                    /* 24 - RTC Handler              */
  { UnusedISR                   },                    /* 25 - CMU Handler              */
  { UnusedISR                   },                    /* 26 - VCMP Handler             */
  { UnusedISR                   },                    /* 27 - LCD Handler              */
  { UnusedISR                   },                    /* 28 - MSC Handler              */
  { UnusedISR                   }                     /* 29 - AES Handler              */
};


/************************************ end of vectors.c *********************************/


