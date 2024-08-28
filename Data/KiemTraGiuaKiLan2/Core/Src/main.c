/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void SCK()
{	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
}

void LAT()
{	HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_RESET);}

void tensv_74hc595_put(uint8_t ch)
{
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, ch & (1 << i));
		SCK(); 
	}
}

void tensv_LEDDecode(uint8_t num)
{
	uint8_t NUM[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1};
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, NUM[num] & (1 << i));
		SCK(); 
	} 
	LAT();
}


void tensv_LED7seg_PutMatrix(uint8_t num[])
{
	for (int i = 8; i > -1 ; i--)
	{
		tensv_LEDDecode(num[i]); 
	}  
}


void tensv_LED7seg_PutNum(uint32_t num) {
    uint8_t array[8]; // Initialize array to hold 8 digits
    for (int i = 7; i >= 0; i--) {
        array[i] = num % 10; 
        num /= 10;  
    }
    tensv_LED7seg_PutMatrix(array);
}	


uint8_t ReadButton() {
    uint8_t val = 0x00;
    uint8_t B1 = 0;
    uint8_t B2 = 0;
    uint8_t B3 = 0;
    uint8_t B4 = 0;
    
    // Read the state of each button
    B1 = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
    B2 = HAL_GPIO_ReadPin(B2_GPIO_Port, B2_Pin);
    B3 = HAL_GPIO_ReadPin(B3_GPIO_Port, B3_Pin);
    B4 = HAL_GPIO_ReadPin(B4_GPIO_Port, B4_Pin);
    
    // Combine the states into a single byte
    val |= (B1 << 0);
    val |= (B2 << 1);
    val |= (B3 << 2);
    val |= (B4 << 3);
    
    return val;
}


#define PRESS_ON GPIO_PIN_RESET
#define PRESS_OFF GPIO_PIN_RESET
#define B1 GPIO_PIN_RESET
#define B2 GPIO_PIN_RESET
#define B3 GPIO_PIN_RESET
#define B4 GPIO_PIN_RESET
#define COUNT_UP 1
#define COUNT_DOWN 2
uint8_t B1_state = 1, B2_state = 1, B3_state = 1, B4_state = 1 ;  
uint8_t nMode = 0; 
void StateM(void)
{
	uint8_t B1_vals = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
	uint8_t B2_vals = HAL_GPIO_ReadPin(B1_GPIO_Port, B2_Pin);
	uint8_t B3_vals = HAL_GPIO_ReadPin(B1_GPIO_Port, B3_Pin);
	uint8_t B4_vals = HAL_GPIO_ReadPin(B1_GPIO_Port, B4_Pin);
	
	uint8_t n = 0;

	if ((B1_state==1)&&(B1_vals==B1))
	{
		nMode = COUNT_UP; 
		B1_state = 0;
	}
	else if ((B1_state==1)&&(B1_vals==!B1))
	{
		B1_state = 1;
	}
	
	
	if ((B2_state==1)&&(B2_vals==B2))
	{
		nMode = COUNT_UP; 
		B1_state = 0;
	}
	else if ((B2_state==1)&&(B2_vals==!B2))
	{
		B1_state = 1;
	}
	
	if ((B3_state==1)&&(B3_vals==B3))
	{
		nMode = COUNT_DOWN; 
		B3_state = 0;
	}
	else if ((B3_state==1)&&(B3_vals==!B3))
	{
		B3_state = 1;
	}

	if ((B4_state==1)&&(B4_vals==B4))
	{
		nMode = COUNT_UP; 
		B4_state = 0;
	}
	else if ((B4_state==1)&&(B4_vals==!B4))
	{
		B4_state = 1;
	}

	
}

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	//

			
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SCK_Pin|LAT_Pin|MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SCK_Pin LAT_Pin MOSI_Pin */
  GPIO_InitStruct.Pin = SCK_Pin|LAT_Pin|MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : B1_Pin B2_Pin B3_Pin B4_Pin */
  GPIO_InitStruct.Pin = B1_Pin|B2_Pin|B3_Pin|B4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
