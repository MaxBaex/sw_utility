/*
 * i2c.h
 *
 *  Created on: 25.01.2022
 *      Author: Maximilian Betz
 */

#ifndef I2C_H_
#define I2C_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include <stdbool.h>

extern I2C_HandleTypeDef hi2c1;

/**/
#define I2C1_SCL_GPIOPIN GPIO_PIN_6
#define I2C1_SCL_GPIOX  GPIOB
#define I2C1_SDA_GPIOPIN GPIO_PIN_7
#define I2C1_SDA_GPIOX  GPIOB


typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR    = 0x01U
} I2C_StatusTypeDef;

I2C_StatusTypeDef I2C_Init(I2C_HandleTypeDef *hi2c);
I2C_StatusTypeDef I2C_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
I2C_StatusTypeDef I2C_ReadRegister(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
I2C_StatusTypeDef I2C_WriteRegister(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
I2C_StatusTypeDef I2C_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

#ifdef __cplusplus
}
#endif


#endif /* I2C_H_ */
