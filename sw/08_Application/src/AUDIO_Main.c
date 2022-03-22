/**
  ******************************************************************************
  * @file       AUDIO_Main.c
  * @brief      AUDIO Board for the New Vario
  * @author     Horst Rupp
  * @mainpage   Starting Point
  *
  *             This application uses FreeRTOS as tool to govern the execution.
  *             It is constructed in adherence to the MVC paradigm. xxx
  *
  * @verbatim

  * @endverbatim
  *
  *
  ******************************************************************************
  */
//
//  Includes
//
#include  "Generic_Common_org.h"
#include  "Generic_Includes.h"
#ifdef RUN_CAN_TASKS
  #include  "task_CAN_Bus_Receiver.h"
  #include  "task_CAN_Bus_Sender.h"
#endif
#ifdef  RUN_SIDEWALL_SENSOR
  #include  <task_SideWall_Sensor.h>
  #include  "task_Flaps_LED.h"
#endif
#ifdef RUN_AUDIO
  #include  "task_Audio_Controller.h"
#endif
#ifdef RUN_TEMPHUM_SENSOR
  #include  "task_TempHum_Sensor.h"
#endif
#ifdef RUN_EMULATOR
  #include  "task_Emulator.h"
#endif
#include  "can.h"

//
// ******************************************************************************
//
// Global variables
//

  SemaphoreHandle_t     I2C_Usage_Mutex;

  QueueHandle_t CAN1_rxQueue_Id;
  QueueHandle_t CAN2_rxQueue_Id;

//
// ******************************************************************************
//
// The entry point of the BootLoader application
//
void AUDIO_Main(void)
{
  //
  //  ##########################################################################
  //
  //  Global variables to share time information throughout the system
  //
  g_Time_in_Ticks               = 0;
  g_SystemTime_ms               = 0;
  g_SystemTime_sec              = 0;
  //
  //  Initializing various global status variables
  //
  g_RunUp_Complete              = 0;

  //
  //  ##########################################################################

  //
  //  Intertask communication setup
  //

  EventQId      = xQueueCreate ( c_MaxElementsEventQ,    c_Size_EventQItem );
  ASSERT( EventQId != 0);

  SignalQId      = xQueueCreate ( c_MaxElementsSignalQ,    c_Size_SignalQItem );
  ASSERT( SignalQId != 0);

#ifdef RUN_EMULATOR
  SensorOutQId      = xQueueCreate ( c_MaxElementsSensorOutQ,    c_Size_SensorOutQItem );
  ASSERT( SensorOutQId != 0);
#endif
  //
  //  ##########################################################################
  //
  //  Set-up of various system parameters
  //
  //  Init the timer system
  //
  g_Time_in_Ticks  =  xTaskGetTickCount( );
  g_SystemTime_ms  = 0;

  //
  //  ##########################################################################
  //
  //  setup locking mechanisms for SD_Card_lib
  //
  I2C_Usage_Mutex       = xSemaphoreCreateMutex( );

  //
  // ---------------------------------------------------------------------------
  //
  g_RunUp_Complete  = 1;

  //
  //  ##########################################################################
  //
  //  Start the tasks
  //

#ifdef  RUN_SIDEWALL_SENSOR
  TaskHandle_t taskHandle_FlapsSensor = NULL;
  xTaskCreate( SideWall_Sensor, "SWS", 256, NULL, Prio_FLP, &taskHandle_FlapsSensor );
  ASSERT  ( taskHandle_FlapsSensor != NULL );

  TaskHandle_t taskHandle_Flaps_LED = NULL;
  xTaskCreate( Flaps_LED, "FLP", 256, NULL, Prio_FLP, &taskHandle_Flaps_LED );
  ASSERT  ( taskHandle_Flaps_LED != NULL );
#endif

#ifdef  RUN_AUDIO
  TaskHandle_t taskHandle_Audio_Controller = NULL;
  xTaskCreate( Audio_Controller, "AUD", 1024, NULL, Prio_AUD, &taskHandle_Audio_Controller );
  ASSERT  ( taskHandle_Audio_Controller != NULL );
#endif

#ifdef  RUN_TEMPHUM_SENSOR
  TaskHandle_t taskHandle_TempHum_Sensor = NULL;
  xTaskCreate( TempHum_Sensor, "THM", 1024, NULL, Prio_AUD, &taskHandle_TempHum_Sensor );
  ASSERT  ( taskHandle_TempHum_Sensor != NULL );
#endif

#ifdef RUN_CAN_TASKS
  TaskHandle_t taskHandle_CAN_Sender = NULL;
  xTaskCreate( CAN_Bus_Sender, "SEN", 256, NULL, Prio_SEN, &taskHandle_CAN_Sender );
  ASSERT  ( taskHandle_CAN_Sender != NULL );

  TaskHandle_t taskHandle_CAN_Receiver = NULL;
  xTaskCreate( CAN_Bus_Receiver, "REC", 256, NULL, Prio_REC, &taskHandle_CAN_Receiver );
  ASSERT  ( taskHandle_CAN_Receiver != NULL );
#endif

#ifdef  RUN_EMULATOR
  TaskHandle_t taskHandle_Emulator = NULL;
  xTaskCreate( Emulator, "EMU", 1024, NULL, Prio_EMU, &taskHandle_Emulator );
  ASSERT  ( taskHandle_Emulator != NULL );
#endif

  //
  //  As from here, FreeRTOS takes control
  //
}
// *****************************************************************************
// The End
// *****************************************************************************
