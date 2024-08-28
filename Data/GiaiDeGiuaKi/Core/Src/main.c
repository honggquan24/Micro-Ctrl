/* USER CODE BEGIN Header */
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

void LED_Decode(uint8_t num)
{
	uint8_t LED[] = {0xF5, 0x5, 0x76, 0x57, 0x87, 0xD3, 0xF3, 0x45, 0xF7, 0xD7, 0xA7, 0xE7, 0xE6, 0x97, 0x00}; 
	for (uint8_t i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin,(GPIO_PinState) LED[num] & (1<<i));
		SCK();
	}
}

void LED_Display(uint8_t pos,uint8_t num)
{
	uint8_t Pos = 0x01 << pos;  
	for (uint8_t i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin,(GPIO_PinState) Pos & (1 << i));
		SCK();
	}
	LED_Decode(num); 
	LAT(); 
}
	


uint8_t ReadButton() {
    uint8_t val = 0;
    
    // B?t d?u giao th?c SPI
    HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_SET);
    
    // Ð?c bit cao nh?t
    val |= HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin) << 7;
    
    // Ð?c các bit còn l?i
    for (int i = 6; i >= 0; i--) {
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
        val |= HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin) << i;
    }
    
    return val;
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
	#define NOT_PRESSED			225
	#define SW1_PRESSED			224
	#define SW2_PRESSED			193
	#define SW3_PRESSED			161
	#define SW4_PRESSED			97
	
	uint8_t B1state = 0; 
	uint32_t non = 12145; 
	int n = 10235;
	int delayCnt = 0;
	uint8_t val = 0;
	int PrevState = 255;
	
	_Bool AUTO = 0;
	_Bool UP = 0;
	_Bool DOWN = 0;

  while (1)
  {
		/* uint8_t B_val = ReadButton(); 

		
		if ((B1state == 0) && (B_val == SW1_PRESSED))
			{
				B1state = 1; 
			}
		else if ((B1state == 1) && (B_val == NOT_PRESSED))
			{
				B1state = 0;
				non = non + 1; 
			}
			
			
			
		LED_Display(0, 14); 
		LED_Display(0, non%10); 
		HAL_Delay(1);
		
		LED_Display(0, 14); 
		LED_Display(1, (non/10)%10); 
		HAL_Delay(1);		
		
		LED_Display(0, 14); 
		LED_Display(2, (non/100)%10); 
		HAL_Delay(1);
		
		LED_Display(0, 14); 
		LED_Display(3, (non/1000)%10); 
		HAL_Delay(1);
		
		LED_Display(0, 14); 
		LED_Display(4, (non/10000)%10); 
		HAL_Delay(1);
  } */ 
	val = ReadButton();	
		// State machine for SW1
		if (val == SW1_PRESSED && PrevState == 255){
			if (AUTO){
				DOWN = !DOWN;
				UP = 0;
			}
			else n --;
			PrevState = SW1_PRESSED;
		}
		
		if (val == NOT_PRESSED && PrevState == SW1_PRESSED){
			PrevState = 255;
		}
		
		// State machine for SW2
		if (val == SW2_PRESSED && PrevState == 255){
			if (AUTO){
				UP = !UP;
				DOWN = 0;
			}
			else n ++;
			PrevState = SW1_PRESSED;
		}
		
		if (val == NOT_PRESSED && PrevState == SW2_PRESSED){
			PrevState = 255;
		}
		
		// State machine for SW3
		if (val == SW3_PRESSED && PrevState == 255){
			n = 0;
			PrevState = SW1_PRESSED;
		}
		
		if (val == NOT_PRESSED && PrevState == SW3_PRESSED){
			PrevState = 255;
		}
		
		// State machine for SW4
		if (val == SW4_PRESSED && PrevState == 255){
			AUTO = !AUTO;
			PrevState = SW1_PRESSED;
			if (AUTO == 0){
				UP = 0;
				DOWN = 0;
			}
		}
		
		if (val == NOT_PRESSED && PrevState == SW4_PRESSED){
			PrevState = 255;
		}

		
		int multiple = 1;
		for (int i = 5; i >= 1; i--){
			LED_Display(i, 10);
			LED_Display(i, n / multiple % 10);
			HAL_Delay(1);
			multiple *= 10;
		}
		
		
		
		if (UP == 1){
			if (delayCnt < 2) n++;
			if (delayCnt > 50) delayCnt = 0;
			delayCnt ++;
		}
		
		if (DOWN == 1){
			if (delayCnt < 2) n--;
			if (delayCnt > 50) delayCnt = 0;
			delayCnt ++;
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, RCL_Pin|LAT_Pin|LOAD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
                          |LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin
                          |LCD_LED_Pin|LCD_E_Pin|LCD_RW_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, UART1_TX_Pin|UART1_RX_Pin|UART1_TXA14_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SCK_Pin|MISO_Pin|MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RCL_Pin LAT_Pin LOAD_Pin */
  GPIO_InitStruct.Pin = RCL_Pin|LAT_Pin|LOAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D0_Pin LCD_D1_Pin LCD_D2_Pin LCD_D3_Pin
                           LCD_D4_Pin LCD_D5_Pin LCD_D6_Pin LCD_D7_Pin
                           LCD_LED_Pin LCD_E_Pin LCD_RW_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
                          |LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin
                          |LCD_LED_Pin|LCD_E_Pin|LCD_RW_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : UART1_TX_Pin UART1_RX_Pin UART1_TXA14_Pin */
  GPIO_InitStruct.Pin = UART1_TX_Pin|UART1_RX_Pin|UART1_TXA14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SCK_Pin MISO_Pin MOSI_Pin */
  GPIO_InitStruct.Pin = SCK_Pin|MISO_Pin|MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
