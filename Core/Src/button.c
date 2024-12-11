#include "button.h"

void Button_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = BUTTON_FLOOR1_Pin | BUTTON_FLOOR2_Pin | BUTTON_FLOOR3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t Button_Read(uint8_t button) {
    GPIO_TypeDef* port;
    uint16_t pin;

    switch (button) {
    case 1:
        port = BUTTON_FLOOR1_GPIO_Port;
        pin = BUTTON_FLOOR1_Pin;
        break;
    case 2:
        port = BUTTON_FLOOR2_GPIO_Port;
        pin = BUTTON_FLOOR2_Pin;
        break;
    case 3:
        port = BUTTON_FLOOR3_GPIO_Port;
        pin = BUTTON_FLOOR3_Pin;
        break;
    }

    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET;
}
