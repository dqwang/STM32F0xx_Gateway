#include "hal_common.h"


/*�ⲿ����48MHz
   �ڲ�����8MHz  ��*/
void hal_init_sysclock(void)
{
	SystemInit();
	SystemCoreClockUpdate();/*update system core clock source*/
}
