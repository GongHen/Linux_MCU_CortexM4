/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "cmsis_os.h"
#include "usart.h"


/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
UART_HandleTypeDef huart1;

void uart_console_init(uint32_t bound)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = bound;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
  }

}


PUTCHAR_PROTOTYPE 
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

// void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
// {
// }

static int inHandlerMode (void)
{
  return __get_IPSR() != 0;
}

void print_console(char *format, ...)
{
  char buf[128];
  if (inHandlerMode() != 0)
  {
    taskDISABLE_INTERRUPTS();
  }
  else
  {
    while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX)
      taskYIELD();
  }
  va_list ap;
  va_start(ap, format);
  vsprintf(buf, format, ap);
  HAL_UART_Transmit(&huart1, (uint8_t *)buf, strlen(buf), 128);
  va_end(ap);
  if (inHandlerMode() != 0)
    taskENABLE_INTERRUPTS();
}