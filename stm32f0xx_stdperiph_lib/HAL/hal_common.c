#include "hal_common.h"


/*-------------------------------------------------------------------
���ƣ�hal_init
˵����HAL��ģ��ṹ���GPIO״̬��ʼ������
		  ϵͳ����ʱ����
������void
���أ�void
-------------------------------------------------------------------*/

void hal_init(void)
{
	hal_init_sysclock();	
	hal_init_systick();
	hal_init_led();


	hal_enable_irq();
}
