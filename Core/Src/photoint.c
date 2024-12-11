#include "photoint.h"

void Photoint_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = PHOTOINT_1_Pin | PHOTOINT_2_Pin | PHOTOINT_3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t Photoint_Read(uint8_t floor) {
    GPIO_TypeDef* port;
    uint16_t pin;

    switch (floor) {
    case 1:
        port = PHOTOINT_1_GPIO_Port;
        pin = PHOTOINT_1_Pin;
        break;
    case 2:
        port = PHOTOINT_2_GPIO_Port;
        pin = PHOTOINT_2_Pin;
        break;
    case 3:
        port = PHOTOINT_3_GPIO_Port;
        pin = PHOTOINT_3_Pin;
        break;
    }

    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET;
}
