#include "hal_common.h"

HAL_LED_T hal_led_run;
HAL_LED_T hal_led_err;


/*-------------------------------------------------------------------
名称：hal_init_led_struct
说明：hal_led_run hal_led_err 结构体初始化
参数：void
返回：void
-------------------------------------------------------------------*/

static void hal_init_led_struct(void)
{
	memset(&hal_led_run, 0x0, sizeof(HAL_LED_T));
	memset(&hal_led_err, 0x0, sizeof(HAL_LED_T));
}

static void hal_init_led_gpio(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/* Configure PC10 and PC11 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/*-------------------------------------------------------------------
名称：hal_led_power_ctrl
说明：电源指示灯控制green
参数：HAL_LED_CMD_E
返回：void
-------------------------------------------------------------------*/

void hal_led_power_ctrl(HAL_LED_CMD_E cmd)
{
	if (cmd == HAL_LED_ON)
		hal_gpio_reset(GPIOB,GPIO_Pin_7);
	else
		hal_gpio_set(GPIOB,GPIO_Pin_7);
}


/*-------------------------------------------------------------------
名称：hal_led_run_ctrl
说明：正常运行指示灯控制blue
参数：HAL_LED_CMD_E
返回：void
-------------------------------------------------------------------*/

void hal_led_run_ctrl(HAL_LED_CMD_E cmd)
{
	if (cmd == HAL_LED_ON)
		hal_gpio_reset(GPIOB,GPIO_Pin_6);
	else
		hal_gpio_set(GPIOB,GPIO_Pin_6);
}

/*-------------------------------------------------------------------
名称：hal_led_err_ctrl
说明：错误提示指示灯控制red
参数：HAL_LED_CMD_E
返回：void
-------------------------------------------------------------------*/

void hal_led_err_ctrl(HAL_LED_CMD_E cmd)
{
	if (cmd == HAL_LED_ON)
		hal_gpio_reset(GPIOB,GPIO_Pin_5);
	else
		hal_gpio_set(GPIOB,GPIO_Pin_5);
}


/*-------------------------------------------------------------------
名称：hal_led_run_thread
说明：运行指示灯线程, 此线程需在TMR1_IRQHandler
		   中断服务程序中调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_led_run_thread(void)
{
	hal_led_run.ledCnt++;
	if (hal_led_run.ledCnt >= HAL_LED_RUN_TIME){
		hal_led_run.ledCnt = 0;
		
		hal_led_run.ledFlag = !hal_led_run.ledFlag;

		if(hal_led_run.ledFlag)
		{
			hal_led_run_ctrl(HAL_LED_ON);
		}
		else
		{
			hal_led_run_ctrl(HAL_LED_OFF);
		}
	}
}

/*-------------------------------------------------------------------
名称：hal_led_err_flash
说明：错误提示指示灯闪烁控制
参数：
		  OnTime		亮时间, 1ms为单位
		  OffTime   	灭时间, 1ms为单位
		  FlashNum	闪烁次数
返回：void
-------------------------------------------------------------------*/

void hal_led_err_flash(u16 OnTime, u16 OffTime, u8 FlashNum)
{
	hal_led_err.ledOnTime=OnTime;
	hal_led_err.ledOffTime=OffTime;
	hal_led_err.ledNum=FlashNum;
	hal_led_err.ledCnt=0;
	hal_led_err.ledFlag=0;
	hal_led_err.ledEn=0;
}

/*-------------------------------------------------------------------
名称：hal_led_err_thread
说明：错误提示指示灯闪烁线程，此线程需在TMR1_IRQHandler
		   中断服务程序中调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_led_err_thread(void)
{
	hal_led_err.ledCnt++;
	if (hal_led_err.ledNum){
		if (hal_led_err.ledCnt < hal_led_err.ledOnTime){
			hal_led_err.ledEn = 1;
		}else{
			if (hal_led_err.ledCnt<(hal_led_err.ledOnTime + hal_led_err.ledOffTime)){
				hal_led_err.ledEn = 0;
			}else{
				hal_led_err.ledCnt = 0;
				hal_led_err.ledEn = 0;
				hal_led_err.ledNum--;
			}			
		}
	}

	if (hal_led_err.ledEn && hal_led_err.ledFlag == 0){
		hal_led_err.ledFlag = 1;
		hal_led_err_ctrl(HAL_LED_ON);
	}

	if ( hal_led_err.ledEn == 0  && hal_led_err.ledFlag == 1){
		hal_led_err.ledFlag = 0;
		hal_led_err_ctrl(HAL_LED_OFF);
	}

}


/*-------------------------------------------------------------------
名称：hal_init_led
说明：LED结构体和GPIO状态初始化函数，系统启动时调用
参数：void
返回：void
-------------------------------------------------------------------*/

void hal_init_led(void)
{
	hal_init_led_struct();
	hal_init_led_gpio();

	
	hal_led_err_ctrl(HAL_LED_OFF);
	hal_led_run_ctrl(HAL_LED_OFF);
	hal_led_power_ctrl(HAL_LED_ON);
}

