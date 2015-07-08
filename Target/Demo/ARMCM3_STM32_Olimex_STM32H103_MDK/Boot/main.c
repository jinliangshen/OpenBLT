/************************************************************************************//**
* \file         Demo\ARMCM3_STM32_Olimex_STM32H103_IAR\Boot\main.c
* \brief        Bootloader application source file.
* \ingroup      Boot_ARMCM3_STM32_Olimex_STM32H103_IAR
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
#include "boot.h"                                /* bootloader generic header          */
#include "stm32f10x.h"                           /* microcontroller registers          */


/****************************************************************************************
* Function prototypes
****************************************************************************************/
static void Init(void);

const char BLPrompt[] = "\r\nBL 1.0\r\n";

/************************************************************************************//**
** \brief     This is the entry point for the bootloader application and is called 
**            by the reset interrupt vector after the C-startup routines executed.
** \return    none.
**
****************************************************************************************/
int main(void)
{
	Init();		/* initialize the microcontroller */
	BootInit();	/* initialize the bootloader */
	ComTransmitPacket((blt_int8u *)&BLPrompt[0], sizeof(BLPrompt) - 1);

	while (1)	/* start the infinite program loop */
	{
		BootTask();	/* run the bootloader task */
	}
} /*** end of main ***/


/************************************************************************************//**
** \brief     Initializes the microcontroller. 
** \return    none.
**
****************************************************************************************/
static void Init(void)
{
	volatile uint32_t StartUpCounter = 0, HSEStatus = 0;
	uint32_t pll_multiplier;
	RCC_TypeDef * rcc = RCC;

	/* reset the RCC clock configuration to the default reset state (for debug purpose) */
	rcc->CR |= RCC_CR_HSION;
	/* reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
	rcc->CFGR &= ~(RCC_CFGR_SW | RCC_CFGR_SWS | RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2| RCC_CFGR_ADCPRE | RCC_CFGR_MCO);
	rcc->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSON | RCC_CR_HSEON);
	rcc->CR &= ~RCC_CR_HSEBYP;
	/* reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	rcc->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL | RCC_CFGR_USBPRE);
	/* disable all interrupts and clear pending bits  */
	rcc->CIR = (RCC_CIR_PLLRDYC | RCC_CIR_CSSC | RCC_CIR_LSIRDYC | RCC_CIR_LSERDYC | RCC_CIR_HSIRDYC | RCC_CIR_HSERDYC);

	rcc->CR |= RCC_CR_HSEON;
	/* wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = rcc->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != 1500));

	/* check if time out was reached */
	if ((rcc->CR & RCC_CR_HSERDY) == RESET)
	{	/* cannot continue when HSE is not ready */
		ASSERT_RT(BLT_FALSE);
	}
	/* enable flash prefetch buffer */
	FLASH->ACR |= FLASH_ACR_PRFTBE;
	/* reset flash wait state configuration to default 0 wait states */
	FLASH->ACR &= ~FLASH_ACR_LATENCY;

#if (BOOT_CPU_SYSTEM_SPEED_KHZ > 48000)
	/* configure 2 flash wait states */
	FLASH->ACR |= FLASH_ACR_LATENCY_2;
#elif (BOOT_CPU_SYSTEM_SPEED_KHZ > 24000)  
	/* configure 1 flash wait states */
	FLASH->ACR |= FLASH_ACR_LATENCY_1;    
#endif

	rcc->CFGR |= RCC_CFGR_HPRE_DIV1;	/* HCLK = SYSCLK */
	rcc->CFGR |= RCC_CFGR_PPRE2_DIV2;	/* PCLK2 = HCLK/2 */
	rcc->CFGR |= RCC_CFGR_PPRE1_DIV2;	/* PCLK1 = HCLK/2 */

	/* reset PLL configuration */
	rcc->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);

	/* assert that the pll_multiplier is between 2 and 16 */
	ASSERT_CT((BOOT_CPU_SYSTEM_SPEED_KHZ / BOOT_CPU_XTAL_SPEED_KHZ) >= 2);
	ASSERT_CT((BOOT_CPU_SYSTEM_SPEED_KHZ / BOOT_CPU_XTAL_SPEED_KHZ) <= 16);

	/* calculate multiplier value */
	pll_multiplier = BOOT_CPU_SYSTEM_SPEED_KHZ / BOOT_CPU_XTAL_SPEED_KHZ;
	/* convert to register value */
	pll_multiplier = ((pll_multiplier - 2) << 18);

	/* set the PLL multiplier and clock source */
	rcc->CFGR |= (RCC_CFGR_PLLSRC_HSE | pll_multiplier);
	rcc->CR |= RCC_CR_PLLON;	/* enable PLL */

	/* wait till PLL is ready */
	while((rcc->CR & RCC_CR_PLLRDY) == 0)
	{ }

	/* select PLL as system clock source */
	;
	rcc->CFGR = (rcc->CFGR & ~(RCC_CFGR_SW)) | RCC_CFGR_SW_PLL;
	/* wait till PLL is used as system clock source */
	while ((rcc->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
	{ }

#if (BOOT_COM_UART_ENABLE > 0)
	/* enable clock for USART2 peripheral */
	rcc->APB1ENR |= RCC_APB1ENR_USART2EN;
	/* enable clocks for USART2 transmitter and receiver pins (GPIOA and AFIO) */
	rcc->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN);

	/* configure USART2 Tx (GPIOA2) as alternate function push-pull */
	/* CNF2[1:0] = %10 and MODE2[1:0] = %11 */
	GPIOA->CRL = (GPIOA->CRL & ~((uint32_t)0x0F << (4 * 2))) | ((uint32_t)0x0B << (4 * 2));

	/* configure USART2 Rx (GPIOA3) as alternate function input floating */
	/* first reset the configuration */
	/* CNF2[1:0] = %01 and MODE2[1:0] = %00 */
	GPIOA->CRL = (GPIOA->CRL & ~((uint32_t)0x0f << (4 * 3))) | ((uint32_t)0x04 << (4 * 3));
#endif

#if (BOOT_COM_CAN_ENABLE > 0)
	/* enable clocks for CAN transmitter and receiver pins (GPIOB and AFIO) */
	rcc->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN);

	/* configure CAN Rx (GPIOB8) as alternate function input pull-up */
	/* CNF8[1:0] = %10 and MODE8[1:0] = %00 */
	GPIOB->CRH = (GPIOB->CRH & ~((uint32_t)0x0F << (4 * 0))) | ((uint32_t)0x08 << (4 * 0));

	/* configure CAN Tx (GPIOB9) as alternate function push-pull */
	/* CNF9[1:0] = %10 and MODE9[1:0] = %11 */
	GPIOB->CRH = (GPIOB->CRH & ~((uint32_t)0x0F << (4 * 1))) | ((uint32_t)0x0B << (4 * 1));

	/* remap CAN1 pins to PortB */
	AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_CAN_REMAP) | AFIO_MAPR_CAN_REMAP_REMAP2;

	/* enable clocks for CAN controller peripheral */
	rcc->APB1ENR |= RCC_APB1ENR_CAN1EN;
#endif

#if (BOOT_COM_USB_ENABLE > 0)
	/* divide USB clock by 1.5 to create 48MHz clock */
	rcc->CFGR &= ~RCC_CFGR_USBPRE;
	/* enable the USB clock */
	rcc->APB1ENR |= RCC_APB1ENR_USBEN;
#endif
} /*** end of Init ***/


/*********************************** end of main.c *************************************/
