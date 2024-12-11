
#ifndef HW_HW_H_
#define HW_HW_H_

#include "hw_def.h"


#include "elavator_ctrl.h"
#include "usart.h"
#include "uart.h"

#include "buzzer.h"

#include "fnd.h"
#include "button.h"
#include "photoint.h"


#include "stepper.h"


void hwInit();


void delay(uint32_t time_ms);
uint32_t millis(void);

#endif /* HW_HW_H_ */
