#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "clock.h"
#include "ulog.h"


osThreadId AlgorithmHandle;
void Algorithm_Thread(void const * argument);

/* main entry*/
int main(void)
{
    /* HAL initialization */
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock to 216 MHz */
    SystemClock_Config();

    /* Configure UART for printf */
    uart_console_init(115200);
    print_console("Hello World!\r\n");
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
  // uint32_t PreviousWakeTime = 0;
  uint32_t count = 0;

  for(;;)
  {
      // PreviousWakeTime = osKernelSysTick();

      print_console("Algorithm thread lock, ==%d==!\r\n", ++count);
	    osDelay(5000);
  }
}



void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  print_console("Error Handler\r\n");
  // while (1)
  // {
  // }
  /* USER CODE END Error_Handler_Debug */
}


