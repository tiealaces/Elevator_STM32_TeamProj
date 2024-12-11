#ifndef BUTTON_H
#define BUTTON_H

#include "stm32f4xx_hal.h"

#define BUTTON_FLOOR1_Pin GPIO_PIN_15
#define BUTTON_FLOOR1_GPIO_Port GPIOB

#define BUTTON_FLOOR2_Pin GPIO_PIN_1
#define BUTTON_FLOOR2_GPIO_Port GPIOB

#define BUTTON_FLOOR3_Pin GPIO_PIN_2
#define BUTTON_FLOOR3_GPIO_Port GPIOB

void Button_Init(void);
uint8_t Button_Read(uint8_t button);

#endif // BUTTON_H