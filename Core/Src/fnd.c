#include "fnd.h"

// FND 숫자 배열 (0~9)
static const uint8_t FND_Number[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x27, // 7
    0x7F, // 8
    0x6F  // 9
};

void FND_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Pin = FND_A_Pin | FND_B_Pin | FND_C_Pin | FND_D_Pin | FND_E_Pin | FND_F_Pin | FND_G_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(FND_A_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_Init(FND_D_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_Init(FND_E_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_Init(FND_B_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_Init(FND_C_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_Init(FND_F_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_Init(FND_G_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(FND_A_GPIO_Port, FND_A_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_B_GPIO_Port, FND_B_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_C_GPIO_Port, FND_C_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_D_GPIO_Port, FND_D_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_E_GPIO_Port, FND_E_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_F_GPIO_Port, FND_F_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_G_GPIO_Port, FND_G_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_DP_GPIO_Port, FND_DP_Pin, GPIO_PIN_RESET);
}

void FND_DisplayNumber(uint8_t number) {
    if (number > 9) return;

    uint8_t segments = FND_Number[number];

    HAL_GPIO_WritePin(FND_A_GPIO_Port, FND_A_Pin, (segments & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_B_GPIO_Port, FND_B_Pin, (segments & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_C_GPIO_Port, FND_C_Pin, (segments & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_D_GPIO_Port, FND_D_Pin, (segments & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_E_GPIO_Port, FND_E_Pin, (segments & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_F_GPIO_Port, FND_F_Pin, (segments & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_G_GPIO_Port, FND_G_Pin, (segments & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(FND_DP_GPIO_Port, FND_DP_Pin, GPIO_PIN_RESET);
}
