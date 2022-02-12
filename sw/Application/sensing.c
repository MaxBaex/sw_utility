#include "stm32f1xx_hal.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sensing.h"
#include "i2c.h"
#include "bme68x.h"
#include "communication.h"


extern I2C_HandleTypeDef hi2c1;
static uint8_t dev_addr;


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


void StartSensingTask(void *argument)
{
  struct bme68x_dev bme;
  struct bme68x_conf conf;
  struct bme68x_heatr_conf heatr_conf;
  struct bme68x_data data;
  uint32_t del_period;
  uint8_t n_fields;
  CAN_RAW_DATA rawData;

  for(;;)
    {
      if (BME68X_OK == bme68x_interface_init(&bme, BME68X_I2C_INTF))
	{
	  if (BME68X_OK == bme68x_init(&bme))
	    {
	      conf.filter = BME68X_FILTER_OFF;
	      conf.odr = BME68X_ODR_NONE;
	      conf.os_hum = BME68X_OS_16X;
	      conf.os_pres = BME68X_OS_16X;
	      conf.os_temp = BME68X_OS_16X;

	      if (BME68X_OK == bme68x_set_conf(&conf, &bme))
		{
		  heatr_conf.enable = BME68X_DISABLE;   /* Enabling this causes to high temperature values for quick consecutive readings*/
		  heatr_conf.heatr_temp = 300;
		  heatr_conf.heatr_dur = 100;

		  if (BME68X_OK == bme68x_set_heatr_conf(BME68X_FORCED_MODE, &heatr_conf, &bme))
		    {

		      for(;;)  /* Enter cyclic measurement mode here */
			{
			  if(BME68X_OK == bme68x_set_op_mode(BME68X_FORCED_MODE, &bme))
			    {
			      /* Calculate delay period in microseconds */
			      del_period = bme68x_get_meas_dur(BME68X_FORCED_MODE, &conf, &bme) + (heatr_conf.heatr_dur * 1000);
			      bme.delay_us(del_period, bme.intf_ptr);

			      /* Check if rslt == BME68X_OK, report or handle if otherwise */
			      if(BME68X_OK == bme68x_get_data(BME68X_FORCED_MODE, &data, &n_fields, &bme))
				{
				  /*Signal that reading BME680 works*/
				  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

				  /* Only send data if measurement was successful */
				  rawData.id = c_CAN_Id_Temperature;
				  rawData.value = data.temperature;
				  if( pdTRUE != xQueueSend(COM_Message_Queue, &rawData, 0))
				    {
				      Error_Handler();
				    }

				  rawData.id = c_CAN_Id_Humidity;
				  rawData.value = data.humidity;
				  if( pdTRUE != xQueueSend(COM_Message_Queue, &rawData, 0))
				    {
				      Error_Handler();
				    }

				  rawData.id = c_CAN_Id_Pressure;
				  rawData.value = data.pressure;
				  if( pdTRUE != xQueueSend(COM_Message_Queue, &rawData, 0))
				    {
				      Error_Handler();
				    }

				}
			      else
				{
				  /* Some error happened. Break loop and reinitialize everything from scratch */
				  break;
				}

			    }
			  else
			    {
			      /* Some error happened. Break loop and reinitialize everything from scratch */
			      break;
			    }
			}
		    }
		}
	    }
	}
      /* Wait some time and try again if any error happens */
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
      vTaskDelay(500);
    }
}


