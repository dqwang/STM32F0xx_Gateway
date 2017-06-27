#include "hal_common.h"

HAL_BEEP_T hal_beep;

static void hal_init_beep_gpio(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	/* Configure PF7 output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}

/*-------------------------------------------------------------------
名称：hal_init_beep_struct
说明：hal_beep  结构体初始化
参数：void
返回：void
-------------------------------------------------------------------*/

static void hal_init_beep_struct(void)
{
	memset(&hal_beep, 0x0, sizeof(HAL_BEEP_T));
}


/*-------------------------------------------------------------------
名称：hal_beep_ctrl
说明：蜂鸣器控制
参数：HAL_BEEP_CMD_E
返回：void
-------------------------------------------------------------------*/

void hal_beep_ctrl(HAL_BEEP_CMD_E cmd)
{
	if (cmd == HAL_BEEP_ON)
		hal_gpio_set(GPIOF, GPIO_Pin_7);
	else
		hal_gpio_reset(GPIOF, GPIO_Pin_7);
}


/*-------------------------------------------------------------------
名称：hal_beep_num
说明：蜂鸣器多次控制
参数：
	    	  OnTime		发音时间, 1ms为单位
	    	  OffTime   	静音时间, 1ms为单位
	    	  FlashNum	蜂鸣次数
返回：void
-------------------------------------------------------------------*/

void hal_beep_num(u16 OnTime, u16 OffTime, u8 BeepNum)
{
	hal_beep.beepOnTime=OnTime;
	hal_beep.beepOffTime=OffTime;
	hal_beep.beepNum=BeepNum;
	hal_beep.beepCnt=0;
	hal_beep.beepFlag=0;
	hal_beep.beepEn=0;
}

/*-------------------------------------------------------------------
名称：hal_init_beep
说明：BEEP结构体和GPIO状态初始化函数，系统启动时调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_init_beep(void)
{
	hal_init_beep_gpio();
	hal_init_beep_struct();
	hal_beep_ctrl(HAL_BEEP_OFF);
}

/*-------------------------------------------------------------------
名称：hal_beep_thread
说明：蜂鸣器线程，此线程需在TMR1_IRQHandler
		   中断服务程序中调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_beep_thread(void)
{
	hal_beep.beepCnt++;
	if (hal_beep.beepNum){
		if (hal_beep.beepCnt < hal_beep.beepOnTime){
			hal_beep.beepEn = 1;
		}else{
			if (hal_beep.beepCnt<(hal_beep.beepOnTime + hal_beep.beepOffTime)){
				hal_beep.beepEn = 0;
			}else{
				hal_beep.beepCnt = 0;
				hal_beep.beepEn = 0;
				hal_beep.beepNum--;
			}			
		}
	}

	if (hal_beep.beepEn && hal_beep.beepFlag == 0){
		hal_beep.beepFlag = 1;
		hal_beep_ctrl(HAL_BEEP_ON);
	}

	if ( hal_beep.beepEn == 0  && hal_beep.beepFlag == 1){
		hal_beep.beepFlag = 0;
		hal_beep_ctrl(HAL_BEEP_OFF);
	}
}

