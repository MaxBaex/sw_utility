/**
 * @file    task_TempHum_Sensor.h
 * @brief   New Vario
 * @author  Horst Rupp
 */
//#include  "System_Configuration.h"
//#include  "FreeRTOS_wrapper.h"
//#include  "Generic_Application_Includes.h"
//
// *****************************************************************************
//

#ifndef  __task_TempHum_Sensor_H
  #define  __task_TempHum_Sensor_H

  #include  "General_Includes.h"
  #include  "Generic_Common.h"

  #include "stm32f4xx_hal.h"
  #include "main.h"
  #include "FreeRTOS.h"
  #include "task.h"
  #include "queue.h"
  #include "I2C.h"
  #include "bme68x.h"
  #include "BME680_Lib.h"

  extern I2C_HandleTypeDef hi2c1;

  //
  //  #include  "Generic_Application_Includes.h"
  //
  void  TempHum_Sensor             ( void * nix);
  
#endif  
//
// *****************************************************************************
// The End
// *****************************************************************************
