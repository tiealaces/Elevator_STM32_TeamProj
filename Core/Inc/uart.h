
#ifndef HW_DEVICE_UART_H_
#define HW_DEVICE_UART_H_

#include "hw_def.h"
#include "stepper.h"

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;


bool uartInit(void);


#endif /* HW_DEVICE_UART_H_ */
