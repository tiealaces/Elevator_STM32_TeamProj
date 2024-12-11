#include "elavator_ctrl.h"
#include "stepper.h"


extern uint8_t is_motor_working;
extern uint8_t direction;	// DIR_CW(high), DIR_CCW (low)
uint8_t is_door_open = 0;	// 0: door closed, 1: door opened

#define FLOOR_1F 0b1
#define FLOOR_2F 0b10
#define FLOOR_3F 0b100
#define FLOOR_4F 0b1000
#define FLOOR_5F 0b10000
#define FLOOR_6F 0b100000
#define FLOOR_7F 0b1000000
#define FLOOR_8F 0b10000000

// 버전 2: 외부 인터럽트 핀별 작동 분리 및 층 레지스터 일반화 코드 
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// 각 비트가 층을 상징하는 변수 (예: 1층 = 0번 비트)
	static uint8_t queued_floor = 0;		// 목적지 층 대기열
	static uint8_t current_floor = 0;		// 현재 엘레베이터 위치

	// 버튼 처리
	if (GPIO_Pin == button_1f_Pin) queued_floor |= FLOOR_1F;
	else if (GPIO_Pin == button_2f_Pin) queued_floor |= FLOOR_2F;
	else if (GPIO_Pin == button_3f_Pin) queued_floor |= FLOOR_3F;

	// 포토인터럽트 처리
	else if (HAL_GPIO_ReadPin(photoint_1f_GPIO_Port, photoint_1f_Pin)) current_floor = FLOOR_1F;
	else if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin)) current_floor = FLOOR_2F;
	else if (HAL_GPIO_ReadPin(photoint_3f_GPIO_Port, photoint_3f_Pin)) current_floor = FLOOR_3F;

	// 현재층 FND 출력 갱신
	uint8_t current_floor_num = 0;
	uint8_t temp_current_floor = current_floor;
	while (temp_current_floor)	// 대기열의 현재층 위치 비트를 숫자로 변환
	{
		temp_current_floor = temp_current_floor >> 1;
		current_floor_num++;
	}
	FND_DisplayNumber(current_floor_num);

	// 만약 현재층이 대기열에 있다면...
	if (queued_floor & current_floor)
	{
		queued_floor &= ~current_floor;
		is_door_open = 1;
		Play_Buzzer_Sound(current_floor_num);
	}

	// 스텝 모터 동작 설정
	if (queued_floor && !is_door_open)
		is_motor_working = 1;
	else // (!queued_floor || is_door_open)
		is_motor_working = 0;

	// 스텝 모터 방향 설정
	int8_t temp_floor_queue;
	if (direction == DIR_CW) temp_floor_queue = (queued_floor / current_floor);	// possibility that result may be 1 if queued_floor equals current floor,  but the possibility is removed above when queued_floor &= ~current_floor
	else temp_floor_queue = (queued_floor % current_floor);
	// if there is nothing above/below current floor, switch direction
	if (temp_floor_queue == 0) direction = !direction;
}

/*
uint8_t currentfloor = 0;
void updateCurrentFloor() {
    if (HAL_GPIO_ReadPin(photoint_1f_GPIO_Port, photoint_1f_Pin)) {
        currentfloor = 1; // 현재 1층
    } else if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin)) {
        currentfloor = 2; // 현재 2층
    } else if (HAL_GPIO_ReadPin(photoint_3f_GPIO_Port, photoint_3f_Pin)) {
        currentfloor = 3; // 현재 3층
    }
    FND_DisplayNumber(currentfloor);
}
*/

/*
// 버전1: 작동 확인된 코드
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint8_t check_1f;
	static uint8_t check_2f;
	static uint8_t check_3f;

	updateCurrentFloor();

	if (GPIO_Pin == button_1f_Pin) check_1f = 1;
	if (GPIO_Pin == button_2f_Pin) check_2f = 1;
	if (GPIO_Pin == button_3f_Pin) check_3f = 1;

	if (currentfloor == 1) check_1f = 0;
	if (currentfloor == 2) check_2f = 0;
	if (currentfloor == 3) check_3f = 0;


	// motor working?
	if (check_1f || check_2f || check_3f)
		is_motor_working = 1;
	else
		is_motor_working = 0;

	// motor direction
	switch (currentfloor)
	{
	case 1:
		if (check_2f || check_3f) direction = DIR_CW;
		break;
	case 2:
		{
			if (check_1f && !check_3f) direction = DIR_CCW;
			if (check_3f && !check_1f) direction = DIR_CW;
		}
		break;
	case 3:
		if (check_1f || check_2f) direction = DIR_CCW;
		break;
	}
}
*/



/*
// great effor of works of Mr. Q
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (currentfloor)
	{
	case 1:

		// 1번 버튼 (이미 1층이니 동작x)
		if(check_1f)
		    {
				is_motor_working = 0;		// 모터 정지 및 알림
				updateCurrentFloor();			// 현재 층수 파악
		    }

		// 2번 버튼
		if(check_2f)
		    {
				direction = DIR_CW;	// 1 -> 2 상승
				is_motor_working = 1;

			// 상승 중 포토인터럽트 2번 검출 시
			if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin))
					{
						is_motor_working = 0;		// 모터 정지
						updateCurrentFloor();			// 현재 층수 파악
					}
		    }

		// 3번 버튼
		if(check_3f)
		    {
				direction = DIR_CW;	// 1 -> 3 상승
				is_motor_working = 1;

			// 상승 중 포토인터럽트 3번 검출 시
			if (HAL_GPIO_ReadPin(photoint_3f_GPIO_Port, photoint_3f_Pin))
					{
						is_motor_working = 0;		// 모터 정지
						updateCurrentFloor();			// 현재 층수 파악
					}
			// 1 -> 3 층 올라갈때 2층 포토인터럽트 검출시 2층 fnd 출력
			else if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin))
				{
					updateCurrentFloor();
				}

		    }

		break;

	case 2:

		// 2번 버튼 (이미 2층이니 동작x)
		if(check_2f)
		    {
				is_motor_working = 0;		// 모터 정지 및 알림
				updateCurrentFloor();			// 현재 층수 파악
		    }

		// 1번 버튼
		if(check_1f)
		    {
				direction = DIR_CCW;	// 2 -> 1 하강
				is_motor_working = 1;

			// 하강 중 포토인터럽트 1번 검출 시
			if (HAL_GPIO_ReadPin(photoint_1f_GPIO_Port, photoint_1f_Pin))
					{
						is_motor_working = 0;		// 모터 정지
						updateCurrentFloor();			// 현재 층수 파악
					}
		    }

		// 3번 버튼
		if(check_3f)
		    {
				direction = DIR_CW;	// 2 -> 3 상승
				is_motor_working = 1;

			// 상승 중 포토인터럽트 3번 검출 시
			if (HAL_GPIO_ReadPin(photoint_3f_GPIO_Port, photoint_3f_Pin))
					{
						is_motor_working = 0;		// 모터 정지
						updateCurrentFloor();			// 현재 층수 파악
					}
		    }

		break;


	case 3:

		// 3번 버튼 (이미 3층이니 동작x)
		if(check_3f)
		    {
				is_motor_working = 0;		// 모터 정지 및 알림
				updateCurrentFloor();			// 현재 층수 파악
		    }


		// 2번 버튼
		if(check_2f)
		    {
				direction = DIR_CCW;	// 3 -> 2 하강
				is_motor_working = 1;

			// 하강 중 포토인터럽트 2번 검출 시
			if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin))
					{
						is_motor_working = 0;		// 모터 정지
						updateCurrentFloor();			// 현재 층수 파악
					}
		    }

		// 1번 버튼
		if(check_1f)
		    {
				direction = DIR_CCW;	// 3 -> 1 하강
				is_motor_working = 1;

			// 하강 중 포토인터럽트 1번 검출 시
			if (HAL_GPIO_ReadPin(photoint_1f_GPIO_Port, photoint_1f_Pin))
					{
						is_motor_working = 0;			// 모터 정지
						updateCurrentFloor();			// 현재 층수 파악
					}
			else if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin))
				{
					updateCurrentFloor();
				}
		    }


		break;

		default :


				if (HAL_GPIO_ReadPin(photoint_1f_GPIO_Port, photoint_1f_Pin))
						{
								is_motor_working = 0;
								updateCurrentFloor();
						}

				else if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin))
						{
								is_motor_working = 0;
								updateCurrentFloor();
						}

				else if (HAL_GPIO_ReadPin(photoint_3f_GPIO_Port, photoint_3f_Pin))
						{
								is_motor_working = 0;
								updateCurrentFloor();
						}


		}

	if (HAL_GPIO_ReadPin(photoint_1f_GPIO_Port, photoint_1f_Pin))
	{
		if (currentfloor == 1)
		{
			check_1f = 0;
		}
	}
	else if(GPIO_Pin == button_1f_Pin)
	{
		check_1f = 1;
	}

	if (HAL_GPIO_ReadPin(photoint_2f_GPIO_Port, photoint_2f_Pin))
	{
		if (currentfloor == 2)
		{
			check_2f = 0;
		}
	}
	else if(GPIO_Pin == button_2f_Pin)
	{
		check_2f = 1;
	}

	if (HAL_GPIO_ReadPin(photoint_3f_GPIO_Port, photoint_3f_Pin))
	{
		if (currentfloor == 3)
		{
			check_3f = 0;
		}
	}
	else if(GPIO_Pin == button_3f_Pin)
	{
		check_3f = 1;
	}
}
*/
