#include "hal_common.h"


/*-------------------------------------------------------------------
名称：hal_init
说明：HAL各模块结构体和GPIO状态初始化函数
		  系统启动时调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_init(void)
{
	hal_init_sysclock();	
	hal_init_systick();
	hal_init_led();
	hal_init_beep();
	hal_init_uart();
	

	hal_enable_irq();

	//hal_init_gprs();//init gprs after enable the irq, because gprs use the UART2 interrupt..
}

/*-------------------------------------------------------------------
名称：hal_sleepmode
说明：禁用各种外设，降低功耗，进入低功耗模式前调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_init_sleepmode(void)
{
	hal_sleepmode_uart();
}

