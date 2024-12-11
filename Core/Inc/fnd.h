#ifndef FND_H
#define FND_H

#include "stm32f4xx_hal.h"

#define FND_A_Pin      GPIO_PIN_5
#define FND_A_GPIO_Port GPIOA

#define FND_B_Pin      GPIO_PIN_6
#define FND_B_GPIO_Port GPIOA

#define FND_C_Pin      GPIO_PIN_7
#define FND_C_GPIO_Port GPIOA

#define FND_D_Pin      GPIO_PIN_6
#define FND_D_GPIO_Port GPIOB

#define FND_E_Pin      GPIO_PIN_7
#define FND_E_GPIO_Port GPIOC

#define FND_F_Pin      GPIO_PIN_9
#define FND_F_GPIO_Port GPIOA

#define FND_G_Pin      GPIO_PIN_8
#define FND_G_GPIO_Port GPIOA

#define FND_DP_Pin     GPIO_PIN_10
#define FND_DP_GPIO_Port GPIOB

void FND_Init(void);
void FND_DisplayNumber(uint8_t number);

#endif // FND_H
