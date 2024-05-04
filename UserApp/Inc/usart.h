
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

extern void uart_console_init(uint32_t bound);
extern void print_console(char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */