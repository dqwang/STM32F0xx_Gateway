#ifndef __HAL_LED_H__
#define __HAL_LED_H__

#include "hal_type.h"

typedef struct hal_led_type{
	u8 ledEn;	
	u8 ledNum;
	u8 ledFlag;
	u16 ledCnt;
	u16 ledOnTime;
	u16 ledOffTime;
}HAL_LED_T;

typedef enum hal_led_cmd_enum{
	HAL_LED_ON = 0,
	HAL_LED_OFF
}HAL_LED_CMD_E;

#define HAL_LED_RUN_TIME 1000 // 1000ms


/*-------------------------------------------------------------------
名称：HAL 用户API
说明：上层应用调用此组函数进行LED功能控制
-------------------------------------------------------------------*/

void hal_init_led(void);
void hal_led_power_ctrl(HAL_LED_CMD_E cmd);//green LED
void hal_led_run_ctrl(HAL_LED_CMD_E cmd);//blue LED
void hal_led_err_ctrl(HAL_LED_CMD_E cmd);//red LED
void hal_led_err_flash(u16 OnTime, u16 OffTime, u8 FlashNum);


/*-------------------------------------------------------------------
名称：HAL 底层API
说明：在底层中断中调用
-------------------------------------------------------------------*/

void hal_led_run_thread(void);
void hal_led_err_thread(void);


#endif/*__HAL_LED_H__*/
