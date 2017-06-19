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


	hal_enable_irq();
}
