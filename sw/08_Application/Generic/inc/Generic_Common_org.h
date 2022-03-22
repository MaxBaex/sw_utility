/**
  ******************************************************************************
  * @file     Generic_Common_org.h
  ******************************************************************************
  */
#ifndef  __Generic_Common_Org_H
  #define __Generic_Common_Org_H

  #include  "General_Includes.h"
  #include  "General_Types.h"
  #include  "General_Const.h"

  #include  "Generic_Includes.h"
  #include  "Generic_Types.h"
  #include  "Generic_Const.h"

  #include  "vsqrtf.h"
  //
  // ******************************************************************************
  //
  // Global variables   // without MPU --> no COMMON required

  //
  SemaphoreHandle_t     I2C_Usage_Mutex;
  uint32_t              g_SystemTime_ms;
  uint32_t              g_SystemTime_sec;
  uint8_t               g_CanBusDataXfer_established;       // fixme :
  uint8_t               g_RunUp_Complete;
  volatile  TickType_t  g_Time_in_Ticks;

  xQueueHandle          EventQId;
  EventQItem_t          EventQItem;

  xQueueHandle          SignalQId;
  SignalQItem_t         SignalQItem;

#ifdef  RUN_EMULATOR

  xQueueHandle          SensorOutQId;
  SensorOutQItem_t      SensorOutQItem;

  float                 g_TC_FWC      = 15.0;
  float                 g_TC_SWC      = 30.0;
  float                 g_TC_FWG      = 15.0;
  float                 g_TC_SWG      = 60.0;

  float                 g_TC_Hysteresis  = 10.0;

  float                 g_Roll        = 0.0;
  float                 g_Nick        = 0.0;
  float                 g_Yaw         = 90.0;

  float                 g_Declination = -5.6;
  float                 g_Inclination = -17.8;

  uint32_t              g_last_time = 0;

#endif

  uint16_t              g_Signal_ID;
  uint16_t              g_Signal_Volume   = 20;   // %
  uint16_t              g_Signal_Count;
  uint8_t               g_climbmode;
  uint16_t              g_Audio_Volume    = 20;   // %
  float                 g_NormedFrequency = 0.0;  // span : -2.0 --- 0.0 --- +2.0
                                                  // corresponding to
                                                  // c_min_frequency -- c_mid_frequency -- c_max_frequency
                                                  // in logarithmic steps
  uint16_t              g_Interval        = 400;  // msec (if = 0 --> not beeping )
  uint16_t              g_Duty_Cycle      = 50;   // %
  uint8_t               g_Vario_Mute_Window_Low_Limit;
  uint8_t               g_Vario_Mute_Window_High_Limit;
  uint8_t               g_SC_Mute_Window_Low_Limit;
  uint8_t               g_SC_Mute_Window_High_Limit;

  uint8_t               g_SideWall_Sensor_status;
  uint8_t               g_CurrentFlapsSetting;
  uint8_t               g_OptimalFlapsSetting;
  uint8_t               g_FlashPatternInvert;
  uint8_t               g_FlashRowInvert;
  uint8_t               g_FlapsFlashControl;
  uint8_t				        g_LEDDutyCycle;
  uint8_t				        g_NoFlapsPositions;

  uint32_t              g_Capture_Start = 0,
                        g_Capture_Stop  = 0,
                        g_Capture_Diff  = 0,
                        g_Capt_Polarity = 1;      // Sincerely proposed start value

  uint16_t              g_Next_Volume;
  uint16_t              g_Next_Frequency;

  uint16_t              g_HeartBeat_Count = 0;


#endif    /* __Generic_Common_Org_H */
// *****************************************************************************
// The End
// *****************************************************************************
