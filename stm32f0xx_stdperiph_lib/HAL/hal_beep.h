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
���ƣ�HAL �û�API
˵�����ϲ�Ӧ�õ��ô��麯������BEEP���ܿ���
-------------------------------------------------------------------*/

void hal_init_beep(void);
void hal_beep_ctrl(HAL_BEEP_CMD_E cmd);
void hal_beep_num(u16 OnTime, u16 OffTime, u8 BeepNum);

/*-------------------------------------------------------------------
���ƣ�HAL �ײ�API
˵�����ڵײ��ж��е���
-------------------------------------------------------------------*/

void hal_beep_thread(void);
#endif/*__HAL_BEEP_H__*/
