/**
  * ############################################################################
  * @file     task_TempHum_Sensor.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This task
  *           Reads bit patterns from GPIO and rotary encoder
  *           loops at 10 msecs
  * ############################################################################
  */
//
// Includes
//
#include  "task_TempHum_Sensor.h"

#define   c_blink_alive_limit 4
// neuer Kommentar

// =============================================================================
//
//  Code groesstenteils von Max. Danke !!
//
void TempHum_Sensor ( void * nix)
{

  struct bme68x_dev         bme;
  struct bme68x_conf        conf;
  struct bme68x_heatr_conf  heatr_conf;
  struct bme68x_data        data;

  uint16_t  l_blink_alive_counter_BME680  = 0;
  uint32_t  del_period;
  uint8_t   n_fields;

  for(;;)
  {
    if (BME68X_OK == bme68x_interface_init(&bme, BME68X_I2C_INTF))
    {
      int8_t rslt = bme68x_init(&bme);
      if (BME68X_OK == rslt )
      {
        conf.filter   = BME68X_FILTER_OFF;
        conf.odr      = BME68X_ODR_NONE;
        conf.os_hum   = BME68X_OS_16X;
        conf.os_pres  = BME68X_OS_16X;
        conf.os_temp  = BME68X_OS_16X;

        if (BME68X_OK == bme68x_set_conf(&conf, &bme))
        {
          heatr_conf.enable = BME68X_DISABLE;   /* Enabling this causes to high temperature values for quick consecutive readings*/
          heatr_conf.heatr_temp = 300;
          heatr_conf.heatr_dur  = 100;

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

                  //
                  //  TempHum Sensor heart beat blinker
                  //
                  l_blink_alive_counter_BME680++;
                 if ( l_blink_alive_counter_BME680 < c_blink_alive_limit / 2 )
                  {
                    HAL_GPIO_WritePin ( LED_Port, LEDgreen_Pin, GPIO_PIN_SET );
                  }
                  else
                  {
                    HAL_GPIO_WritePin ( LED_Port, LEDgreen_Pin, GPIO_PIN_RESET );
                  }

                  if ( l_blink_alive_counter_BME680 > c_blink_alive_limit )
                  {
                    l_blink_alive_counter_BME680 = 0;
                  }

                  /* Only send data if measurement was successful */
                  EventQItem.Command = cCmdTemperature;
                  EventQItem.SensedValue = data.temperature * 1000;
                  if ( ! xQueueSend ( EventQId, &EventQItem, portMAX_DELAY ) )
                  {
                    /* Some error happened. Break loop and reinitialize everything from scratch */
                    break;
                  }

                  EventQItem.Command = cCmdHumidity;
                  EventQItem.SensedValue = data.humidity* 1000;
                  if ( ! xQueueSend ( EventQId, &EventQItem, portMAX_DELAY ) )
                  {
                    /* Some error happened. Break loop and reinitialize everything from scratch */
                    break;
                  }

                  EventQItem.Command = cCmdPressure;
                  EventQItem.SensedValue = data.pressure;
                  if ( ! xQueueSend ( EventQId, &EventQItem, portMAX_DELAY ) )
                  {
                    /* Some error happened. Break loop and reinitialize everything from scratch */
                    break;
                  }

                  vTaskDelay ( c_WakeTempHumSensor );
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
    vTaskDelay(500);
  }
}

//
// *******************************************************************************
// The End
// *******************************************************************************
