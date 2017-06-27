#ifndef __HAL_UT_H__
#define __HAL_UT_H__

#include "hal_common.h"

/*-------------------------------------------------------------------
名称：HAL 单元测试API
说明：测试各单元API功能
-------------------------------------------------------------------*/

void hal_ut_led(void);
void hal_ut_beep(void);
void hal_ut_uart2_send(void);
void hal_ut_uart2_echo(void);
void hal_ut_gprs(void);




#endif/*__HAL_UT_H__*/
