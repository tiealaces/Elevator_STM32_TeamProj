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
#define fnd_segA_Pin GPIO_PIN_5
#define fnd_segA_GPIO_Port GPIOA
#define fnd_segB_Pin GPIO_PIN_6
#define fnd_segB_GPIO_Port GPIOA
#define fnd_segC_Pin GPIO_PIN_7
#define fnd_segC_GPIO_Port GPIOA
#define photoint_1f_Pin GPIO_PIN_4
#define photoint_1f_GPIO_Port GPIOC
#define photoint_1f_EXTI_IRQn EXTI4_IRQn
#define stepmotor_in1_Pin GPIO_PIN_5
#define stepmotor_in1_GPIO_Port GPIOC
#define button_2f_Pin GPIO_PIN_1
#define button_2f_GPIO_Port GPIOB
#define button_2f_EXTI_IRQn EXTI1_IRQn
#define button_3f_Pin GPIO_PIN_2
#define button_3f_GPIO_Port GPIOB
#define button_3f_EXTI_IRQn EXTI2_IRQn
#define fnd_segDP_Pin GPIO_PIN_10
#define fnd_segDP_GPIO_Port GPIOB
#define photoint_2f_Pin GPIO_PIN_13
#define photoint_2f_GPIO_Port GPIOB
#define photoint_2f_EXTI_IRQn EXTI15_10_IRQn
#define photoint_3f_Pin GPIO_PIN_14
#define photoint_3f_GPIO_Port GPIOB
#define photoint_3f_EXTI_IRQn EXTI15_10_IRQn
#define button_1f_Pin GPIO_PIN_15
#define button_1f_GPIO_Port GPIOB
#define button_1f_EXTI_IRQn EXTI15_10_IRQn
#define stepmotor_in2_Pin GPIO_PIN_6
#define stepmotor_in2_GPIO_Port GPIOC
#define fnd_segE_Pin GPIO_PIN_7
#define fnd_segE_GPIO_Port GPIOC
#define stepmotor_in3_Pin GPIO_PIN_8
#define stepmotor_in3_GPIO_Port GPIOC
#define stepmotor_in4_Pin GPIO_PIN_9
#define stepmotor_in4_GPIO_Port GPIOC
#define fnd_segG_Pin GPIO_PIN_8
#define fnd_segG_GPIO_Port GPIOA
#define fnd_segF_Pin GPIO_PIN_9
#define fnd_segF_GPIO_Port GPIOA
#define fnd_segD_Pin GPIO_PIN_6
#define fnd_segD_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
