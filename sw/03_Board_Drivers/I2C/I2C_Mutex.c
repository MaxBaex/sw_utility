#include <I2C_Mutex.h>
#include  "main.h"
//#include  "HMR_Const.h"
#include  "my_assert.h"
#include  "FreeRTOS.h"
#include  "queue.h"
#define   I2C_MUTEX_DEFAULT_TIMEOUT_MS  100

//
//  =====================================================================
//
uint16_t  I2C_Take_Mutex ( void )
{
  //xPortRaisePrivilege();
  if ( xSemaphoreTake ( I2C_Usage_Mutex, I2C_MUTEX_DEFAULT_TIMEOUT_MS ) )
    return I2C_MUTEX_OK;
  else
    return I2C_MUTEX_NOT_AVAILABLE;
}
//
//  =====================================================================
//
uint16_t  I2C_Give_Mutex ( void )
{
  //portSWITCH_TO_USER_MODE();
  if ( xSemaphoreGive ( I2C_Usage_Mutex ) )
    return I2C_MUTEX_OK;
  else
    return I2C_MUTEX_ERROR;
}

