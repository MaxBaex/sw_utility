/*
 * i2c_mutex.h
 *
 *  Created on: 21.12.2020
 *      Author: HMR
 */



#ifndef CUSTOM_I2C_H_
  #define CUSTOM_I2C_H_

  // project headers
  #include  "System_Configuration.h"
  //#include  "FreeRTOS_wrapper.h"
  #include  "main.h"
  #include  "FreeRTOS.h"
  #include  "semphr.h"

  extern    SemaphoreHandle_t     I2C_Usage_Mutex;

  typedef enum {
    I2C_MUTEX_OK = 0,
    I2C_MUTEX_NOT_AVAILABLE,
    I2C_MUTEX_ERROR,
  } I2C_RESULT;


  #ifdef __cplusplus
   extern "C" {
  #endif

  uint16_t  I2C_Take_Mutex ( void );
  uint16_t  I2C_Give_Mutex ( void );

  #ifdef __cplusplus
  }
  #endif

#endif /* CUSTOM_I2C_H_ */
