#include "hal_ut.h"


/*-------------------------------------------------------------------
名称：hal_ut_audio
说明：HAL 语音功能单元测试
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_ut_led(void)
{
	hal_led_run_ctrl(HAL_LED_ON);
	hal_led_err_ctrl(HAL_LED_ON);
	hal_led_power_ctrl(HAL_LED_ON);

	hal_systick_delay(1000);
	hal_led_err_flash(50,500,30);
	
	#if 0
	while (1){
		hal_led_run_ctrl(HAL_LED_ON);
		hal_systick_delay(10);
		hal_led_run_ctrl(HAL_LED_OFF);
		hal_systick_delay(10);
	}
	#endif
}


void hal_ut_beep(void)
{
	hal_beep_ctrl(HAL_BEEP_ON);

	//hal_beep_num(500,1000,3);

	while(1){
		hal_beep_ctrl(HAL_BEEP_ON);
		hal_systick_delay(100);
		hal_beep_ctrl(HAL_BEEP_OFF);
		hal_systick_delay(100);
	}
	
}

void hal_ut_uart2_send(void)
{
	//send
	u8 buf[]="hello world";
	
	while (1){
		hal_uart2_sendbuf(buf,sizeof(buf));

		hal_systick_delay(1000);
	}
	//recv
}


void hal_ut_uart2_echo(void)
{
	if (hal_uart2.rflag == 1){
		hal_systick_delay(10);//waiting until the packet done
		hal_uart2_sendbuf(hal_uart2.rbuf, hal_uart2.rindex);
		hal_clear_uart_rbuf(&hal_uart2);
	}
}

void hal_ut_gprs(void)
{
	if (hal_uart2.rflag == 1 && gprs.gprs_flag == GPRS_FLAG8_USER_DATA){
		hal_systick_delay(10);//waiting until the packet done

		hal_uart2_sendbuf(hal_uart2.rbuf, hal_uart2.rindex);

		hal_clear_uart_rbuf(&hal_uart2);
	}
}


