/**
  * ############################################################################
  * @file     task_CAN_Bus_Receiver.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This task
  *           accepts dynamic data from the sensor unit via CAN Bus
  *           and stores that data into the dedicated common area.
  * ############################################################################
  */
//
// Includes
//
#include  "task_CAN_Bus_Receiver.h"

  extern CAN_HandleTypeDef hcan1;
  extern CAN_HandleTypeDef hcan2;

#define   c_blink_alive_limit   20
//
// *****************************************************************************
//
//! basic CAN packet type
//typedef struct
//{
//  uint16_t id; 	//!< identifier
//  uint16_t dlc; //!< data length code
//  union
//  {
//		uint8_t  data_b[8]; 	//!< data seen as 8 times uint8_t
//		int8_t   data_sb[8]; 	//!< data seen as 8 times int8_t
//		uint16_t data_h[4]; 	//!< data seen as 4 times uint16_t
//		int16_t  data_sh[4]; 	//!< data seen as 4 times int16_t
//		uint32_t data_w[2]; 	//!< data seen as 2 times uint32_t
//		int32_t  data_sw[2];	//!< data seen as 2 times int32_t
//		float    data_f[2]; 	//!< data seen as 2 times 32-bit floats
//		uint64_t data_l;    	//!< data seen as 64-bit integer
//  };
//} CAN_Packet_t;

#ifdef  USE_CAN1
  extern  QueueHandle_t CAN1_rxQueue_Id;
#endif
#ifdef  USE_CAN2
  extern  QueueHandle_t CAN2_rxQueue_Id;
#endif

//
// *****************************************************************************
//
//  This routine emulates the sensor data input
//  or reads the sensor data from CAN Bus
//
void CAN_Bus_Receiver ( void * nix )
{
  uint16_t  l_blink_alive_counter_CAN_Rec     = 0;
  uint16_t  l_retcode = 0;
  CAN_Packet_t p;
  HAL_GPIO_WritePin ( LED_Port, LEDblue_Pin, GPIO_PIN_RESET );

  while ( 1  )
  {
    //vTaskDelay ( 10 );

#ifdef  USE_CAN1
      l_retcode = xQueueReceive( CAN1_rxQueue_Id, &p, 10 );
#endif
#ifdef  USE_CAN2
      l_retcode = xQueueReceive( CAN2_rxQueue_Id, &p, 10 );
#endif
    if ( l_retcode > 0 )
    {

      g_CanBusDataXfer_established = 1;

      //
      //  Blue LED flashing indicates CAN data reception
      //
      l_blink_alive_counter_CAN_Rec++;
      if ( l_blink_alive_counter_CAN_Rec < c_blink_alive_limit / 2 )
      {
        HAL_GPIO_WritePin ( LED_Port, LEDblue_Pin, GPIO_PIN_SET );
      }
      else
      {
        HAL_GPIO_WritePin ( LED_Port, LEDblue_Pin, GPIO_PIN_RESET );
      }

      if ( l_blink_alive_counter_CAN_Rec > c_blink_alive_limit )
      {
        l_blink_alive_counter_CAN_Rec = 0;
      }

      switch( p.id)
      {
        case c_CID_A57_HeartBeat :
          g_HeartBeat_Count = p.data_b[0];
          break;

        case c_CID_A57_Reboot :
          Bootloader_JumpToSysMem( );
          break;

        case  c_CID_A57_Signal : //!< uint16_t signal_id + uint16_t signal_volume
          SignalQItem.Signal_Id     = p.data_h[0];
          SignalQItem.Signal_Volume = p.data_h[1];
          xQueueSend ( SignalQId, &SignalQItem, c_MaxQWaitTime_in_ms );
          break;

        case  c_CID_A57_Flaps_Status :
          g_SideWall_Sensor_status = p.data_b[0];
          g_CurrentFlapsSetting = p.data_b[1];
          g_OptimalFlapsSetting = p.data_b[2];
          g_FlapsFlashControl   = p.data_b[3];
          g_LEDDutyCycle	   	  = p.data_b[4];
          g_NoFlapsPositions	  = p.data_b[5];
          break;

        case  c_CID_A57_Audio :
          g_NormedFrequency = (float) p.data_sh[0] / 10e3;
          g_Interval        = p.data_h[1];
          g_Audio_Volume    = p.data_b[4];
          g_Duty_Cycle      = p.data_b[5];
          g_climbmode       = p.data_b[6];
          break;

#if 0
          g_NormedFrequency = -0.5;
          g_Interval        = 200;
          g_Audio_Volume    = 75;
          g_Duty_Cycle      = 50;
          g_climbmode       = c_Climbing;
#endif

          break;

#ifdef  RUN_EMULATOR

        case  c_CID_A57_TCs :
          g_TC_FWC        = (float) p.data_h[0] * 0.1;
          g_TC_SWC        = (float) p.data_h[1] * 0.1;
          g_TC_FWG        = (float) p.data_h[2] * 0.1;
          g_TC_SWG        = (float) p.data_h[3] * 0.1;
          g_last_time     = 0;  // Feedbck immediately
          break;

        case  c_CID_A57_Sw_Hysteresis :
          g_TC_Hysteresis = (float) p.data_h[0] * 0.1;
          g_last_time     = 0;  // Feedbck immediately
          break;

        case  c_CID_A57_Euler_SetUp :
          g_Roll          = (float) p.data_sh[0] * 0.1;
          g_Nick          = (float) p.data_sh[1] * 0.1;
          g_Yaw           = (float) p.data_sh[2] * 0.1;
          g_last_time     = g_SystemTime_sec; // Feedback delayed
          break;

        case  c_CID_A57_DecInclination :
          g_Declination   = (float) p.data_sh[0] * 0.1;
          g_Inclination   = (float) p.data_sh[1] * 0.1;
          g_last_time     = g_SystemTime_sec; // Feedback delayed
          break;

#endif

        default:
          break;
      }
    }

#if 0
    else
    {
        g_CurrentFlapsSetting 	= 1;
        g_OptimalFlapsSetting 	= 5;
        g_LEDDutyCycle	   		= 50;

        g_FlapsFlashControl   	= 0;
        g_FlapsFlashControl   	|= ( 1 << c_FlashRowInvert );
        //g_FlapsFlashControl   	|= ( 1 << c_FlashPatternInvert );
    }
#endif
    }
}
//    - g_NormedFrequency   int32_t / 10e6      -2 --- 0 ---- +2
//    - g_Interval          uint16_t            ?? -- 500 [msec]
//    - g_Audio_Volume      uint8_t             0 -- 100 [% max Volume]
//    - g_Duty_Cycle        uint8_t             10 - 90
//    - g_Mode              uint8_t             0 for cruise  / 1 for climb
//
//      g_Vario_LW_Limit    uint8_t             0 - 50 [%]
//      g_Vario_HW_Limit    uint8_t             0 - 50 [%]
//      g_SF_LW_Limit       uint8_t             0 - 50 [%]
//      g_SF_HW_Limit       uint8_t             0 - 50 [%]
//
//    - g_Signal_Id         uint8_t             nn
//    - g_Signal_Volume     uint8_t             0 -- 100 [% max Volume]
//
//
// *****************************************************************************
// The End
// *****************************************************************************

