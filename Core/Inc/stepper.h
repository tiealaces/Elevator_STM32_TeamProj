#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

#include "delay.h"
#include "hw.h"



#define STEPS_PER_REVOLATION	4096
#define DIR_CW					1		// 시계방향
#define DIR_CCW					0		// 반시계방향



#define	IN1_Pin					GPIO_PIN_5
#define	IN1_GPIO_Port			GPIOC

#define	IN2_Pin					GPIO_PIN_6
#define	IN2_GPIO_Port			GPIOC

#define	IN3_Pin					GPIO_PIN_8
#define	IN3_GPIO_Port			GPIOC

#define	IN4_Pin					GPIO_PIN_9
#define	IN4_GPIO_Port			GPIOC


bool stepperInit(void);

static const uint8_t HALF_STEP_SEQ[8][4]=
{
		{1,0,0,0},	// step 1
		{1,1,0,0},	// step 2
		{0,1,0,0},	// step 3
		{0,1,1,0},	// step 4
		{0,0,1,0},	// step 5
		{0,0,1,1},	// step 6
		{0,0,0,1},	// step 7
		{1,0,0,1}	// step 8
};

void stepMotor(uint8_t step);


#endif /* INC_STEPPER_H_ */
