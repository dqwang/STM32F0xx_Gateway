#include "hal_common.h"


/*外部晶振48MHz
   内部晶振8MHz  √*/
void hal_init_sysclock(void)
{
	SystemInit();
	SystemCoreClockUpdate();/*update system core clock source*/
}
