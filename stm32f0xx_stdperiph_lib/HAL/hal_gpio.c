#include "hal_common.h"

void hal_gpio_set(GPIO_TypeDef *port, u16 pin)
{
	port->BSRR = pin;		
}


void hal_gpio_reset(GPIO_TypeDef *port, u16 pin)
{
	port->BRR = pin;
}

