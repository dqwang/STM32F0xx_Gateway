#include "hal_ut.h"


/*-------------------------------------------------------------------
���ƣ�hal_ut_audio
˵����HAL �������ܵ�Ԫ����
������void
���أ�void
-------------------------------------------------------------------*/

void hal_ut_led(void)
{
	hal_led_run_ctrl(HAL_LED_ON);
	hal_led_err_ctrl(HAL_LED_ON);
	hal_led_power_ctrl(HAL_LED_ON);

	hal_systick_delay(1000);
	hal_led_err_flash(500,500,30);
	
	#if 0
	while (1){
		hal_led_run_ctrl(HAL_LED_ON);
		hal_systick_delay(10);
		hal_led_run_ctrl(HAL_LED_OFF);
		hal_systick_delay(10);
	}
	#endif
}

