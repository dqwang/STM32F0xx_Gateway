#ifndef __HAL_BEEP_H__
#define __HAL_BEEP_H__

#include "hal_type.h"

typedef struct hal_beep_type{
	u8 beepEn;
	u8 beepOnTime;
	u8 beepOffTime;
	u16 beepCnt;
	u16 beepNum;
	u16 beepFlag;
}HAL_BEEP_T;

typedef enum hal_beep_cmd_enum{
	HAL_BEEP_OFF = 0,
	HAL_BEEP_ON
}HAL_BEEP_CMD_E;


/*-------------------------------------------------------------------
名称：HAL 用户API
说明：上层应用调用此组函数进行BEEP功能控制
-------------------------------------------------------------------*/

void hal_init_beep(void);
void hal_beep_ctrl(HAL_BEEP_CMD_E cmd);
void hal_beep_num(u16 OnTime, u16 OffTime, u8 BeepNum);

/*-------------------------------------------------------------------
名称：HAL 底层API
说明：在底层中断中调用
-------------------------------------------------------------------*/

void hal_beep_thread(void);
#endif/*__HAL_BEEP_H__*/
