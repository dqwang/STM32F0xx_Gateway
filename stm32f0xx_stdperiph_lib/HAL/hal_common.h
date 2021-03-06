#ifndef __HAL_COMMON_H__
#define __HAL_COMMON_H__

#include <intrinsics.h>
#include <string.h>

#include "stm32f0xx.h"
#include "core_cm0.h"
#include "stm32f0xx_it.h"

#include "hal_type.h"
#include "hal_led.h"
#include "hal_gpio.h"
#include "hal_systick.h"
#include "hal_sysclock.h"
#include "hal_beep.h"
#include "hal_uart.h"
#include "hal_gprs.h"
#include "hal_error.h"

#include "hal_ut.h"

#define hal_enable_irq()	__enable_irq()
#define hal_disable_irq()	__disable_irq()

#define HAL_CLEAR_TYPE(p, type) memset(p, 0x00, sizeof(type))

/*-------------------------------------------------------------------
名称：HAL 用户API
说明：上层应用调用此组函数进行HAL初始化
-------------------------------------------------------------------*/
void hal_init(void);

void hal_init_sleepmode(void);

#endif/*__HAL_COMMON_H__*/
