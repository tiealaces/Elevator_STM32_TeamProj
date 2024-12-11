#ifndef PHOTOINTER_H
#define PHOTOINTER_H

#include "stm32f4xx_hal.h"

#define PHOTOINT_1_Pin GPIO_PIN_4
#define PHOTOINT_1_GPIO_Port GPIOC

#define PHOTOINT_2_Pin GPIO_PIN_13
#define PHOTOINT_2_GPIO_Port GPIOB

#define PHOTOINT_3_Pin GPIO_PIN_14
#define PHOTOINT_3_GPIO_Port GPIOB

void Photoint_Init(void);
uint8_t Photoint_Read(uint8_t floor);

#endif // PHOTOINTER_H
