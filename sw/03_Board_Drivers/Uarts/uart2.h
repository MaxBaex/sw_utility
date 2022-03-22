/*
 * uart2.h
 *
 *  Created on: 03.01.2020
 *      Author: mbetz
 */

#ifndef CUSTOM_uart2_H_
#define CUSTOM_uart2_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

void uart2_Init(void);
void uart2_DeInit(void);
void uart2_ChangeBaudRate(uint32_t rate);
void uart2_Transmit(uint8_t *pData, uint16_t Size);
bool uart2_Receive(uint8_t *pRxByte, uint32_t timeout);
extern UART_HandleTypeDef huart2;

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_uart2_H_ */
