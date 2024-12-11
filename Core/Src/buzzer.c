#include "buzzer.h"

#define BUZZER_END_TIME 2000	// 2000번 타이머10 카운트 후 멈춤 (현재 설정: 2000ms)

static TIM_HandleTypeDef *buzzer_htim;
static uint32_t buzzer_channel;
static uint32_t buzzer_time_counter = 0;


void Buzzer_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
	buzzer_htim = htim;
	buzzer_channel = channel;
}

void Buzzer_SetFrequency(uint32_t frequency)
{
	// 주파수에 따라 타이머의 주기를 설정, 이부분은 gpt도움받았습니다.
	uint32_t period = (HAL_RCC_GetPCLK2Freq() / (buzzer_htim->Init.Prescaler + 1)) / frequency;
	__HAL_TIM_SET_AUTORELOAD(buzzer_htim, period - 1);
	__HAL_TIM_SET_COMPARE(buzzer_htim, buzzer_channel, period / 2);
}

void Buzzer_Start(void)
{
	HAL_TIM_PWM_Start(buzzer_htim, buzzer_channel);
}
void Buzzer_Stop(void)
{
	HAL_TIM_PWM_Stop(buzzer_htim, buzzer_channel);
}

void Play_Buzzer_Sound(uint8_t currentfloor)	// 각층마다 주파수다르게 해서 소리다르게
{
	switch(currentfloor)
	{
		case 1:
			Buzzer_SetFrequency(500);
			break;
		case 2:
			Buzzer_SetFrequency(1000);
			break;
		case 3:
			Buzzer_SetFrequency(1500);
			break;
		default:
			return;
	}
	buzzer_time_counter = 0;	// Buzzer_update() 에도 있지만 중복 확인용으로 넣음
	Buzzer_Start();
}

void Buzzer_Update(void)
{
	if (buzzer_time_counter >= BUZZER_END_TIME)
	{
		Buzzer_Stop();
		buzzer_time_counter = 0;
	}
	else{
		buzzer_time_counter++;
	}
}
