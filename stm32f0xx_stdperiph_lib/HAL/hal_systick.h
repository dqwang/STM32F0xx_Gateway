#ifndef __HAL_SYSTICK_H__
#define __HAL_SYSTICK_H__
#include "hal_type.h"


void hal_init_systick(void);
void hal_systick_delay(__IO u32 ms);



void hal_systick_thread(void);

#endif/*__HAL_SYSTICK_H__*/
