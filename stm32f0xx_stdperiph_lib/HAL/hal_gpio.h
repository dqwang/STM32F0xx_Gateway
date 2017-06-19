#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__
#include "hal_type.h"

void hal_gpio_set(GPIO_TypeDef *port, u16 pin);
void hal_gpio_reset(GPIO_TypeDef *port, u16 pin);



#endif/*__HAL_GPIO_H__*/
