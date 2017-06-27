#include "hal_common.h"

//USART1
//USART2

hal_uart_t hal_uart1;
hal_uart_t hal_uart2;

static void hal_init_uart1(void)
{
	GPIO_InitTypeDef  GPIOA_InitStruct;
	USART_InitTypeDef USART1_InitStruct;
	NVIC_InitTypeDef 	NVIC_InitStruct;

	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );						
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);     											 

	GPIOA_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;                 
	GPIOA_InitStruct.GPIO_Mode = GPIO_Mode_AF; 
	GPIOA_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIOA_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOA_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_InitStruct);   

	USART1_InitStruct.USART_BaudRate = 57600;//9600;
	USART1_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART1_InitStruct.USART_StopBits = USART_StopBits_1;
	USART1_InitStruct.USART_Parity = USART_Parity_No;
	USART1_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART1_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);


	HAL_CLEAR_TYPE(&hal_uart1, hal_uart_t);
}

static void hal_init_uart2(void)
{
	GPIO_InitTypeDef 	GPIOA_InitStruct;
	USART_InitTypeDef 	USART2_InitStruct;
	NVIC_InitTypeDef 	NVIC_InitStruct;

	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1);

	GPIOA_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;                 
	GPIOA_InitStruct.GPIO_Mode = GPIO_Mode_AF; 
	GPIOA_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIOA_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOA_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_InitStruct); 

	USART2_InitStruct.USART_BaudRate=115200;
	USART2_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART2_InitStruct.USART_StopBits=USART_StopBits_1;
	USART2_InitStruct.USART_Parity=USART_Parity_No;
	USART2_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART2_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART2,&USART2_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	USART_Cmd(USART2,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	HAL_CLEAR_TYPE(&hal_uart2, hal_uart_t);
}

void hal_init_uart(void)
{
	//hal_init_uart1();
	hal_init_uart2();
}

void hal_sleepmode_uart(void)
{
	USART_Cmd(USART1,DISABLE);
	USART_Cmd(USART2,DISABLE);
}

void hal_uart1_sendbuf(u8* buf, u16 size)
{
	if (buf == NULL || size <=0){
		return;
	}
	memcpy(hal_uart1.sbuf, buf, size);
	hal_uart1.slen = size;
	hal_uart1.sindex = 0;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}


void hal_uart2_sendbuf(u8* buf, u16 size)
{
	if (buf == NULL || size <=0){
		return;
	}
	memcpy(hal_uart2.sbuf, buf, size);
	hal_uart2.slen = size;
	hal_uart2.sindex = 0;
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

void hal_clear_uart_rbuf(hal_uart_t *p)
{
	p->rflag=0;
	p->rindex=0;
}

