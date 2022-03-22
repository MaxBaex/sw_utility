/*
 *****************************************************************************
 *  @file   BME680_Lib.c
 *  @author Horst Rupp
 *  @brief  Created on: 21.11.2020
 *  @brief  Last Change : 28.11.2020
 *  @brief  These are the valid IDs for any data transfer on the CAN Bus.
 *****************************************************************************
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BME680_Lib.h"
#include "I2C.h"
#include "bme68x.h"
//#include "communication.h"


extern I2C_HandleTypeDef hi2c1;
static uint8_t dev_addr;

//
//  ===========================================================================
//
/*! I2C read function map */
BME68X_INTF_RET_TYPE bme68x_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  uint8_t dev_addr = *(uint8_t*)intf_ptr;

  if (I2C_OK == I2C_ReadRegister(&hi2c1, dev_addr, reg_addr, 1, reg_data, len))
    {
      return BME68X_INTF_RET_SUCCESS;
    }
  else
    {
      return -1;
    }
}

//
//  ===========================================================================
//
/*! I2C write function map */
BME68X_INTF_RET_TYPE bme68x_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  uint8_t dev_addr = *(uint8_t*)intf_ptr;

  if (I2C_OK == I2C_WriteRegister(&hi2c1, dev_addr, reg_addr, 1, (uint8_t *)reg_data, len))
    {
      return BME68X_INTF_RET_SUCCESS;
    }
  else
    {
      return -1;
    }
}

//
//  ===========================================================================
//
/*! Delay function map to FreeRTOS. Delay below 1ms will be rounded up to 1ms. */
void bme68x_delay_us(uint32_t period, void *intf_ptr)
{
  if (period < 1000)
    {
      vTaskDelay(1);
    }
  else
    {
      vTaskDelay(period / 1000);
    }
}

//
//  ===========================================================================
//
int8_t bme68x_interface_init(struct bme68x_dev *bme, uint8_t intf)
{
  int8_t rslt = BME68X_OK;

  if (bme != NULL)
    {
      /* Bus configuration : I2C */
      if (intf == BME68X_I2C_INTF)
  {
    I2C_Init(&hi2c1);
    dev_addr = BME68X_I2C_ADDR_HIGH << 1;
    bme->read = bme68x_i2c_read;
    bme->write = bme68x_i2c_write;
    bme->intf = BME68X_I2C_INTF;
  }
      /* Bus configuration : SPI */
      else if (intf == BME68X_SPI_INTF)
  {
    Error_Handler();
  }

      bme->delay_us = bme68x_delay_us;
      bme->intf_ptr = &dev_addr;
      bme->amb_temp = 25; /* The ambient temperature in deg C is used for defining the heater temperature */
    }
  else
    {
      rslt = BME68X_E_NULL_PTR;
    }

  return rslt;
}

// ****************************************************************************
//  EOF
// ****************************************************************************

