/**
  * ############################################################################
  * @file     task_Emulator.c
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
#include  "task_Emulator.h"
#ifdef RUN_EMULATOR

  // =============================================================================
  //
  void Emulator ( void * nix)
  {
    while ( true )
    {
      vTaskDelay ( 1000 );
      if ( g_SystemTime_sec - g_last_time > 15 )
      {
        g_last_time = g_SystemTime_sec;

        SensorOutQItem.value2 = 0;
        SensorOutQItem.value3 = 0;
        SensorOutQItem.value4 = 0;

        SensorOutQItem.CAN_Id = c_CID_AUD_TCs;
        SensorOutQItem.value1 = g_TC_FWC * 10;
        SensorOutQItem.value2 = g_TC_SWC * 10;
        SensorOutQItem.value3 = g_TC_FWG * 10;
        SensorOutQItem.value4 = g_TC_SWG * 10;
        if ( ! xQueueSend ( SensorOutQId, &SensorOutQItem, portMAX_DELAY ) )
        {
          /* Some error happened. Break loop and reinitialize everything from scratch */
          break;
        }

        SensorOutQItem.CAN_Id = c_CID_AUD_Sw_Hysteresis;
        SensorOutQItem.value1 = g_TC_Hysteresis * 10;
        if ( ! xQueueSend ( SensorOutQId, &SensorOutQItem, portMAX_DELAY ) )
        {
          /* Some error happened. Break loop and reinitialize everything from scratch */
          break;
        }

        SensorOutQItem.CAN_Id = c_CID_AUD_Euler_SetUp;
        SensorOutQItem.value1 = g_Roll * 10;
        SensorOutQItem.value2 = g_Nick * 10;
        SensorOutQItem.value3 = g_Yaw  * 10;
        if ( ! xQueueSend ( SensorOutQId, &SensorOutQItem, portMAX_DELAY ) )
        {
          /* Some error happened. Break loop and reinitialize everything from scratch */
          break;
        }

        SensorOutQItem.CAN_Id = c_CID_AUD_DecInclination;
        SensorOutQItem.value1 = g_Declination * 10;
        SensorOutQItem.value2 = g_Inclination * 10;
        if ( ! xQueueSend ( SensorOutQId, &SensorOutQItem, portMAX_DELAY ) )
        {
          /* Some error happened. Break loop and reinitialize everything from scratch */
          break;
        }
      }
    }
  }
#endif
//
// *******************************************************************************
// The End
// *******************************************************************************
