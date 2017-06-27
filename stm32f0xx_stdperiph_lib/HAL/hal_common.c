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
	hal_init_beep();
	hal_init_uart();
	

	hal_enable_irq();

	//hal_init_gprs();//init gprs after enable the irq, because gprs use the UART2 interrupt..
}

/*-------------------------------------------------------------------
���ƣ�hal_sleepmode
˵�������ø������裬���͹��ģ�����͹���ģʽǰ����
������void
���أ�void
-------------------------------------------------------------------*/

void hal_init_sleepmode(void)
{
	hal_sleepmode_uart();
}

