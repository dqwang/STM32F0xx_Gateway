#include "hal_common.h"

gprs_t gprs;


static void hal_gprs_reg(void)
{
	u8 reg_cmd[]="AT+CREG?\r\n";
	u8 i=0;
	gprs.gprs_flag = GPRS_FLAG0_NONE;

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(reg_cmd);
		hal_systick_delay(5000);
		for(i=0;i<hal_uart2.rindex;i++){
			if (hal_uart2.rbuf[i] == ':'){
				if (hal_uart2.rbuf[i+2] == '1' && hal_uart2.rbuf[i+4] == '1'){
					gprs.gprs_flag = GPRS_FLAG1_REG;
					// 语音提示 GPRS注册成功
					break;
				}
			}
		}
		hal_led_err_flash(100,100,1);
	}while(gprs.gprs_flag == GPRS_FLAG0_NONE);
}

static errno_t check_gprs_cmd_ack(u8 *ok, u8 *ack_from_gprs)
{
	u8 i=0;

	for (i=0;i<sizeofstr(ok);i++){
		if (ok[i] != ack_from_gprs[i]){
			return E_INVALID_PACKET;
		}
	}
	return EOK;
}

static void hal_gprs_close_echo(void)
{
	u8 close_echo_cmd[]="ATE0\r\n";
	u8 close_echo_ok[]="ATE0\r\n\r\nOK\r\n";

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(close_echo_cmd);
		hal_systick_delay(1000);

		if (EOK == check_gprs_cmd_ack(close_echo_ok, hal_uart2.rbuf)){
			gprs.gprs_flag = GPRS_FLAG2_CLOSE_ECHO;
			// 语音提示 GPRS关闭回显功能成功
			break;
		}

		hal_led_err_flash(100,100,2);
	}while(gprs.gprs_flag == GPRS_FLAG1_REG);
}

static void hal_gprs_att(void)
{
	u8 att_cmd[]="AT+CGATT=1\r\n";
	u8 att_ok[]="\r\nOK\r\n";

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(att_cmd);
		hal_systick_delay(1000);

		if (EOK == check_gprs_cmd_ack(att_ok, hal_uart2.rbuf)){
			gprs.gprs_flag = GPRS_FLAG3_GATT;
			// 语音提示 GPRS附着成功
			break;
		}
		hal_led_err_flash(100,100,3);
	}while(gprs.gprs_flag == GPRS_FLAG2_CLOSE_ECHO);
}

static void hal_gprs_act(void)
{
	u8 act_cmd[]="AT+CGACT=1,1\r\n";
	u8 act_ok[]="\r\nOK\r\n";

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(act_cmd);
		hal_systick_delay(3000);
		if (EOK == check_gprs_cmd_ack(act_ok, hal_uart2.rbuf)){
			gprs.gprs_flag = GPRS_FLAG4_GACT;
			// 语音提示 GPRS PDP激活成功
			break;
		}
		hal_led_err_flash(100,100,4);
	}while(gprs.gprs_flag == GPRS_FLAG3_GATT);
}

static void hal_gprs_connect_tcp(void)
{
	u8 connect_tcp_cmd[]="AT+CIPSTART=TCP,120.55.117.108,10000\r\n";
	u8 connect_tcp_ok[]="\r\nCONNECT OK\r\n\r\nOK\r\n";

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(connect_tcp_cmd);
		hal_systick_delay(3000);

		if (EOK == check_gprs_cmd_ack(connect_tcp_ok, hal_uart2.rbuf)){
			gprs.gprs_flag = GPRS_FLAG5_CONNECT_TCP;
			// 语音提示 GPRS 连接TCP服务器
			break;
		}
		hal_led_err_flash(100,100,5);
	}while(gprs.gprs_flag == GPRS_FLAG4_GACT);
}


static void hal_gprs_trs_config(void)
{
	u8 trs_config_cmd[]="AT+CIPTCFG=2,10\r\n";// 10 bytes at least per packet
	u8 trs_config_ok[]="\r\nOK\r\n";

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(trs_config_cmd);
		hal_systick_delay(1000);

		if (EOK == check_gprs_cmd_ack(trs_config_ok, hal_uart2.rbuf)){
			gprs.gprs_flag = GPRS_FLAG6_TRS_CONFIG;
			// 语音提示 GPRS 透传设置参数

			break;
		}
		hal_led_err_flash(100,100,6);
	}while(gprs.gprs_flag == GPRS_FLAG5_CONNECT_TCP);
}

static void hal_gprs_trs_open(void)
{
	u8 trs_open_cmd[]="AT+CIPTMODE=1\r\n";
	u8 trs_open_ok[]="\r\nOK\r\n";

	do{
		CLEAR_UART(&hal_uart2);
		GPRS_SEND_CMD(trs_open_cmd);
		hal_systick_delay(1000);
		if (EOK == check_gprs_cmd_ack(trs_open_ok, hal_uart2.rbuf)){
			gprs.gprs_flag = GPRS_FLAG7_TRS_OPEN;
			// 语音提示 GPRS 透传模式开启
			break;
		}
		hal_led_err_flash(100,100,7);
	}while(gprs.gprs_flag == GPRS_FLAG6_TRS_CONFIG);
}

static void hal_gprs_user_data(void)
{
	if (gprs.gprs_flag == GPRS_FLAG7_TRS_OPEN){
		gprs.gprs_flag = GPRS_FLAG8_USER_DATA;
		//next to hal_uart2_thread()

		//
	}
}

static void hal_gprs_close_tcp(void)
{
	//u8 close_tcp_cmd[]="AT+CIPCLOSE\r\n";
}


static void hal_init_gprs_gpio(void)
{
	GPIO_InitTypeDef        GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* Configure PA5 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	hal_gpio_set(GPIOA,GPIO_Pin_5);
}

void hal_init_gprs(void)
{
	CLEAR_GPRS(&gprs);
	
	hal_init_gprs_gpio();

	hal_gprs_reg();
	hal_gprs_close_echo();
	hal_gprs_att();
	hal_gprs_act();

	hal_gprs_connect_tcp();
	hal_gprs_trs_config();
	hal_gprs_trs_open();

	hal_gprs_user_data();
}

void hal_gprs_reconnect_server(void)
{
	gprs.gprs_flag = GPRS_FLAG4_GACT;

	hal_gprs_connect_tcp();
	hal_gprs_trs_config();
	hal_gprs_trs_open();

	hal_gprs_user_data();
}



