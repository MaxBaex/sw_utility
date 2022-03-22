/**
  ******************************************************************************
  * @file     Generic_Common.h
  * @author   Horst Rupp
  * @brief    H-File for this application
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Generic_Common_H
  #define __Generic_Common_H

  #include  "General_Includes.h"
  #include  "General_Types.h"
  #include  "General_Const.h"

  #include  "Generic_Includes.h"
  #include  "Generic_Types.h"
  #include  "Generic_Const.h"

  //  **************************************************************************
  //
  extern  SemaphoreHandle_t     I2C_Usage_Mutex;
  extern  uint32_t              g_SystemTime_ms;
  extern  uint32_t              g_SystemTime_sec;
  extern  uint8_t               g_CanBusDataXfer_established;       // fixme :
  extern  uint8_t               g_RunUp_Complete;
  extern  volatile  TickType_t  g_Time_in_Ticks;

  extern  xQueueHandle          EventQId;
  extern  EventQItem_t          EventQItem;

  extern  xQueueHandle          SignalQId;
  extern  SignalQItem_t         SignalQItem;

#ifdef  RUN_EMULATOR
  extern  xQueueHandle      SensorOutQId;
  extern  SensorOutQItem_t  SensorOutQItem;

  extern  float         g_TC_FWC;
  extern  float         g_TC_SWC;
  extern  float         g_TC_FWG;
  extern  float         g_TC_SWG;

  extern  float         g_TC_Hysteresis;

  extern  float         g_Roll;
  extern  float         g_Nick;
  extern  float         g_Yaw;

  extern  float         g_Declination;
  extern  float         g_Inclination;

  extern  uint32_t      g_last_time;


#endif

  extern  uint16_t              g_Signal_ID;
  extern  uint16_t              g_Signal_Volume;
  extern  uint16_t              g_Signal_Count;
  extern  uint8_t               g_climbmode;
  extern  uint16_t              g_Audio_Volume;
  extern  float                 g_NormedFrequency;
  extern  uint16_t              g_Interval;
  extern  uint16_t              g_Duty_Cycle;
  extern  uint8_t               g_Vario_Mute_Window_Low_Limit;
  extern  uint8_t               g_Vario_Mute_Window_High_Limit;
  extern  uint8_t               g_SC_Mute_Window_Low_Limit;
  extern  uint8_t               g_SC_Mute_Window_High_Limit;

  extern  uint8_t               g_SideWall_Sensor_status;
  extern  uint8_t               g_CurrentFlapsSetting;
  extern  uint8_t               g_OptimalFlapsSetting;
  extern  uint8_t               g_FlashPatternInvert;
  extern  uint8_t               g_FlashRowInvert;
  extern  uint8_t               g_FlapsFlashControl;
  extern  uint8_t				g_LEDDutyCycle;
  extern  uint8_t				g_NoFlapsPositions;


  extern  uint32_t              g_Capture_Start,
                                g_Capture_Stop,
                                g_Capture_Diff,
                                g_Capt_Polarity;



  extern  uint16_t              g_Next_Volume;
  extern  uint16_t              g_Next_Frequency;

  extern  uint16_t              g_HeartBeat_Count;


#endif /* __Generic_Common_H */
// *****************************************************************************
// The End
// *****************************************************************************
