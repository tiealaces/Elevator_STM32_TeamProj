#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "stm32f4xx_hal.h"

void Buzzer_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void Buzzer_SetFrequency(uint32_t frequency);
void Buzzer_Start(void);
void Buzzer_Stop(void);
void Play_Buzzer_Sound(uint8_t currentfloor);
void Buzzer_Update(void);


#endif /* INC_BUZZER_H_ */
