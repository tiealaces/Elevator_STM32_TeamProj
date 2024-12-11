
#include "hw.h"



void hwInit()
{
	stepperInit();
}


// 할딜레이 함수 대체
void delay(uint32_t time_ms)
{
  HAL_Delay(time_ms);
}

// 전원 입력후에 카운트 값을 반환 함수
// 시스템 틱을 이용함
uint32_t millis(void)
{
  return HAL_GetTick();
}




