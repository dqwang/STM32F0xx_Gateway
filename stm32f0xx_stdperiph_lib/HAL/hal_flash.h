#ifndef __HAL_FLASH_H__
#define __HAL_FLASH_H__
#include "hal_type.h"



/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#ifdef STM32F030
 #define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size 1k*/
 #define FLASH_USER_START_ADDR   ((uint32_t)0x0800F000)   /* Start @ of user Flash area , the last 4k*/
 #define FLASH_USER_END_ADDR     ((uint32_t)0x08010000)   /* End @ of user Flash area */
#endif /* STM32F072 */
#define DATA_32                 ((uint32_t)0x12345678)


#endif/*__HAL_FLASH_H__*/