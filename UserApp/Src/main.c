#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "usart.h"
#include "clock.h"


osThreadId AlgorithmHandle;
void Algorithm_Thread(void const * argument);

int main(void)
{
    /* HAL initialization */
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock to 216 MHz */
    SystemClock_Config();

    /* Configure UART for printf */
    uart_console_init(115200);
    // osKernelInitialize();

    osThreadDef(Algorithm, Algorithm_Thread, osPriorityNormal, 0, 1024);
    AlgorithmHandle = osThreadCreate(osThread(Algorithm), NULL);

    /* Start scheduler */
    osKernelStart();

    while (1)
    {

    }
}


void Algorithm_Thread(void const * argument)
{
  for(;;)
  {
    printf("Hello World!\r\n");
	  osDelay(5000);
  }
}



void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


