/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.1
  * @date    17-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "hal_common.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	hal_systick_thread();
	
	hal_led_err_thread();
	hal_led_run_thread();
	hal_beep_thread();
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
		/* Read one byte from the receive data register */
		hal_uart1.rbuf[hal_uart1.rindex++] = USART_ReceiveData(USART1);

		if(hal_uart1.rindex == UART_RBUF_SIZE){		
			hal_uart1.rindex =0;			
		}

		hal_uart1.rflag = 1;
	}

	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET){   
		if (hal_uart1.slen == 0){
			return;
		}
		/* Write one byte to the transmit data register */
		USART_SendData(USART1, hal_uart1.sbuf[hal_uart1.sindex++]);

		if (hal_uart1.sindex >= hal_uart1.slen) {
			/* Disable the USART Transmit interrupt */
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
			hal_uart1.slen=0;
		}
	}	
}



//Firstly, clear the inputrupt flag!!!
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
		/* Read one byte from the receive data register */
		hal_uart2.rbuf[hal_uart2.rindex++] = USART_ReceiveData(USART2);

		if(hal_uart2.rindex == UART_RBUF_SIZE){		
			hal_uart2.rindex =0;			
		}

		hal_uart2.rflag = 1;
	}

	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET){   
		if (hal_uart2.slen == 0){
			return;
		}
		/* Write one byte to the transmit data register */
		USART_SendData(USART2, hal_uart2.sbuf[hal_uart2.sindex++]);

		if (hal_uart2.sindex >= hal_uart2.slen) {
			/* Disable the USART Transmit interrupt */
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
			hal_uart2.slen=0;
		}
	}	
}


/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
