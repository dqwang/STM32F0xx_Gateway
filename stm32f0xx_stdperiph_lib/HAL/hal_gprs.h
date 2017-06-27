#ifndef __HAL_GPRS_H__
#define __HAL_GPRS_H__
#include "hal_type.h"

//GPRS_RST PA5
//GPRS_INT PA6

typedef enum {
	   GPRS_FLAG0_NONE =0,

	   GPRS_FLAG1_REG,
	   GPRS_FLAG2_CLOSE_ECHO,
	   GPRS_FLAG3_GATT,
	   GPRS_FLAG4_GACT,

	   GPRS_FLAG5_CONNECT_TCP,
	   GPRS_FLAG6_TRS_CONFIG,
	   GPRS_FLAG7_TRS_OPEN,
	   GPRS_FLAG8_USER_DATA
}gprs_flag_e;

typedef struct gprs_{
	gprs_flag_e gprs_flag;
}gprs_t;

#define sizeofstr(str) (sizeof(str)-1)
#define GPRS_SEND_CMD(cmd_buf) hal_uart2_sendbuf(cmd_buf, sizeofstr(cmd_buf))
#define CLEAR_GPRS(p) memset(p,0x0,sizeof(gprs_t))

extern gprs_t gprs;

void hal_init_gprs(void);
void hal_gprs_reconnect_server(void);



#endif/*__HAL_GPRS_H__*/
