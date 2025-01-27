/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RCL_Pin GPIO_PIN_2
#define RCL_GPIO_Port GPIOE
#define LCD_D0_Pin GPIO_PIN_8
#define LCD_D0_GPIO_Port GPIOD
#define LCD_D1_Pin GPIO_PIN_9
#define LCD_D1_GPIO_Port GPIOD
#define LCD_D2_Pin GPIO_PIN_10
#define LCD_D2_GPIO_Port GPIOD
#define LCD_D3_Pin GPIO_PIN_11
#define LCD_D3_GPIO_Port GPIOD
#define UART1_TX_Pin GPIO_PIN_9
#define UART1_TX_GPIO_Port GPIOA
#define UART1_RX_Pin GPIO_PIN_10
#define UART1_RX_GPIO_Port GPIOA
#define UART1_TXA14_Pin GPIO_PIN_14
#define UART1_TXA14_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_0
#define LCD_D4_GPIO_Port GPIOD
#define LCD_D5_Pin GPIO_PIN_1
#define LCD_D5_GPIO_Port GPIOD
#define LCD_D6_Pin GPIO_PIN_2
#define LCD_D6_GPIO_Port GPIOD
#define LCD_D7_Pin GPIO_PIN_3
#define LCD_D7_GPIO_Port GPIOD
#define LCD_LED_Pin GPIO_PIN_4
#define LCD_LED_GPIO_Port GPIOD
#define LCD_E_Pin GPIO_PIN_5
#define LCD_E_GPIO_Port GPIOD
#define LCD_RW_Pin GPIO_PIN_6
#define LCD_RW_GPIO_Port GPIOD
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOD
#define SCK_Pin GPIO_PIN_3
#define SCK_GPIO_Port GPIOB
#define MISO_Pin GPIO_PIN_4
#define MISO_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_5
#define MOSI_GPIO_Port GPIOB
#define LAT_Pin GPIO_PIN_0
#define LAT_GPIO_Port GPIOE
#define LOAD_Pin GPIO_PIN_1
#define LOAD_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
