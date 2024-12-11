#include "uart.h"
#include "stdlib.h"


// 버퍼 크기와 각도 값의 범위 설정
uint8_t buffer[10]; // 수신된 각도 값을 저장하는 버퍼
uint8_t rxData; // 수신된 단일 문자를 저장하는 변수
uint8_t rxIndex = 0; // 버퍼 인덱스를 추적하는 변수
uint8_t dir; // 회전 방향을 저장하는 변수 ('a' 또는 'b')
uint16_t degree; // 회전 각도를 저장하는 변수



//// UART 인터럽트 콜백 함수
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  if(huart->Instance == USART2) // 인터럽트가 발생한 UART 인스턴스가 USART2인지 확인
//  {
//    if(rxIndex == 0) // 첫 번째 수신 데이터인 경우 (즉, 방향 데이터)
//    {
//      dir = rxData; // 방향 데이터를 저장 ('a' 또는 'b')
//      rxIndex++; // 인덱스를 증가시켜 다음 데이터를 각도 값으로 설정
//    }
//    else // 두 번째 이후의 수신 데이터인 경우 (즉, 각도 데이터)
//    {
//      if(rxData != '\n') // 줄바꿈 문자가 아닌 경우
//      {
//        if(rxIndex < sizeof(buffer)) // 버퍼가 오버플로우되지 않도록 확인
//        {
//          buffer[rxIndex - 1] = rxData; // 버퍼에 데이터를 저장
//          rxIndex++; // 인덱스를 증가시킴
//        }
//      }
//      else // 줄바꿈 문자가 수신된 경우 (즉, 데이터의 끝)
//      {
//        buffer[rxIndex - 1] = '\0'; // 버퍼의 마지막에 NULL 문자를 추가하여 문자열 종료
//        degree = (uint16_t)atoi((char*)buffer); // 버퍼의 문자열을 정수로 변환하여 각도로 설정
//
//
//
//        rxIndex = 0; // 인덱스를 0으로 리셋하여 다음 데이터 수신을 준비
//      }
//    }
//    HAL_UART_Receive_IT(&huart2, &rxData, 1); // 다음 데이터를 수신하도록 인터럽트를 재설정
//  }
//}
