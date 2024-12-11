#include "delay.h"


void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim10, 0);	// 타이머 10번 0으로 리셋

	HAL_TIM_Base_Start(&htim10);		// 타이머 10번 시작
	while(__HAL_TIM_GET_COUNTER(&htim10) < us);	// 카운트가 us보다 작으면 ...

	HAL_TIM_Base_Stop(&htim10);	// 타이머 10번 정지
}

