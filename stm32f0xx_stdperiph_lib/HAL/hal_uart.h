#ifndef __HAL_UART_H__
#define __HAL_UART_H__
#include "hal_type.h"

#define UART_RBUF_SIZE 128
#define UART_SBUF_SIZE 64


typedef struct uart{
	u8 rflag;
	u8 rbusy;
	u16 rindex;
	u8 rbuf[UART_RBUF_SIZE];
	u8 slen;
	u8 sindex;
	u8 sbuf[UART_SBUF_SIZE];
}hal_uart_t;


extern hal_uart_t hal_uart1;
extern hal_uart_t hal_uart2;

#define CLEAR_UART(p) memset(p,0x0,sizeof(hal_uart_t))


void hal_init_uart(void);
void hal_sleepmode_uart(void);

void hal_uart1_sendbuf(u8* buf, u16 size);

void hal_uart2_sendbuf(u8* buf, u16 size);

void hal_clear_uart_rbuf(hal_uart_t *p);


#endif/*__HAL_UART_H__*/

