/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define BATTERY_LEVEL_Pin GPIO_PIN_0
#define BATTERY_LEVEL_GPIO_Port GPIOC
#define GUITAR_IN_Pin GPIO_PIN_0
#define GUITAR_IN_GPIO_Port GPIOA
#define test_Pin GPIO_PIN_1
#define test_GPIO_Port GPIOA
#define PEDAL_OUT_Pin GPIO_PIN_4
#define PEDAL_OUT_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_12
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_13
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_14
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_15
#define LCD_D4_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_6
#define LCD_E_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOC
#define ROTARY_SW_Pin GPIO_PIN_5
#define ROTARY_SW_GPIO_Port GPIOB
#define ROTARY_SW_EXTI_IRQn EXTI9_5_IRQn
#define ROTARY_B_Pin GPIO_PIN_6
#define ROTARY_B_GPIO_Port GPIOB
#define ROTARY_A_Pin GPIO_PIN_7
#define ROTARY_A_GPIO_Port GPIOB
#define ROTARY_A_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
