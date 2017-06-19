#include "hal_common.h"

HAL_LED_T hal_led_run;
HAL_LED_T hal_led_err;


/*-------------------------------------------------------------------
���ƣ�hal_init_led_struct
˵����hal_led_run hal_led_err �ṹ���ʼ��
������void
���أ�void
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
���ƣ�hal_led_power_ctrl
˵������Դָʾ�ƿ���green
������HAL_LED_CMD_E
���أ�void
-------------------------------------------------------------------*/

void hal_led_power_ctrl(HAL_LED_CMD_E cmd)
{
	if (cmd == HAL_LED_ON)
		hal_gpio_reset(GPIOB,GPIO_Pin_7);
	else
		hal_gpio_set(GPIOB,GPIO_Pin_7);
}


/*-------------------------------------------------------------------
���ƣ�hal_led_run_ctrl
˵������������ָʾ�ƿ���blue
������HAL_LED_CMD_E
���أ�void
-------------------------------------------------------------------*/

void hal_led_run_ctrl(HAL_LED_CMD_E cmd)
{
	if (cmd == HAL_LED_ON)
		hal_gpio_reset(GPIOB,GPIO_Pin_6);
	else
		hal_gpio_set(GPIOB,GPIO_Pin_6);
}

/*-------------------------------------------------------------------
���ƣ�hal_led_err_ctrl
˵����������ʾָʾ�ƿ���red
������HAL_LED_CMD_E
���أ�void
-------------------------------------------------------------------*/

void hal_led_err_ctrl(HAL_LED_CMD_E cmd)
{
	if (cmd == HAL_LED_ON)
		hal_gpio_reset(GPIOB,GPIO_Pin_5);
	else
		hal_gpio_set(GPIOB,GPIO_Pin_5);
}


/*-------------------------------------------------------------------
���ƣ�hal_led_run_thread
˵��������ָʾ���߳�, ���߳�����TMR1_IRQHandler
		   �жϷ�������е���
������void
���أ�void
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
���ƣ�hal_led_err_flash
˵����������ʾָʾ����˸����
������
		  OnTime		��ʱ��, 1msΪ��λ
		  OffTime   	��ʱ��, 1msΪ��λ
		  FlashNum	��˸����
���أ�void
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
���ƣ�hal_led_err_thread
˵����������ʾָʾ����˸�̣߳����߳�����TMR1_IRQHandler
		   �жϷ�������е���
������void
���أ�void
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
���ƣ�hal_init_led
˵����LED�ṹ���GPIO״̬��ʼ��������ϵͳ����ʱ����
������void
���أ�void
-------------------------------------------------------------------*/

void hal_init_led(void)
{
	hal_init_led_struct();
	hal_init_led_gpio();

	
	hal_led_err_ctrl(HAL_LED_OFF);
	hal_led_run_ctrl(HAL_LED_OFF);
	hal_led_power_ctrl(HAL_LED_ON);
}

