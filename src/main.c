#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

static UART_HandleTypeDef huart1;

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


int __io_putchar(int ch);
static void SystemClock_Config(void);
static void MX_USART1_UART_Init(void);
static void Error_Handler(void);

osThreadId AlgorithmHandle;
void Algorithm_Thread(void const * argument);

int main(void)
{
    /* Enable the CPU caches */
    // SCB_EnableICache();
    // SCB_EnableDCache();

    /* HAL initialization */
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    if (HAL_Init() != HAL_OK)
    {
        Error_Handler();
    }

    /* Configure the system clock to 216 MHz */
    SystemClock_Config();

    /* Configure UART for printf */
    MX_USART1_UART_Init();
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

int __io_putchar(int ch)
{
    /* Support printf over UART */
    (void) HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 0xFFFFU);
    return ch;
}

// void SysTick_Handler(void)
// {
//     HAL_IncTick();
// }


static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}


/**
  * @brief This function provides accurate delay (in milliseconds) based 
  *        on SysTick counter flag.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay: specifies the delay time length, in milliseconds.
  * @retval None
  */

// void HAL_Delay(__IO uint32_t Delay)
// {
//   while(Delay) 
//   {
//     if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) 
//     {
//       Delay--;
//     }
//   }
// }

static void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
