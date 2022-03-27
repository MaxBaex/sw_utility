/**
 * ###########################################################################
 * @file     task_CAN_Bus_Sender.c
 * @brief    New Vario
 * @author   Horst Rupp
 * ############################################################################
 */
//
//  ****************************************************************************
//
// Includes
//
#include  "can.h"
#include  "Generic_Common.h"
#include  "Generic_Includes.h"
#include  "Generic_Types.h"

#include  "Generic_CAN_Ids.h"
#include  "task_CAN_Bus_Sender.h"

#ifdef  USE_CAN1
  extern CAN_HandleTypeDef hcan1;
#endif
#ifdef  USE_CAN2
  extern CAN_HandleTypeDef hcan2;
#endif

//extern  uint8_t  CAN_HangUp;
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

//
//  ****************************************************************************
//  ****************************************************************************
//
void CAN_Bus_Sender ( void * nix )
{
  uint32_t  l_ret32;
  CAN_Packet_t p;
  uint16_t  l_count = 0;
  //uint32_t  l_last_time_stamp;

  //
  // the works
  //
  while( 1)
  {
    vTaskDelay( 10 );                // loop 100 msec

    //
    //  HeartBeat
    //
    if ( ++l_count > 50 )
    {
      p.id        = c_CID_AUD_HeartBeat; // --------------------------------
      p.dlc       = 8;
      p.data_w[0] = VERSION_TXT6; //  Own version

#ifdef  USE_CAN1
      l_ret32 = CAN_Send ( &hcan1, &p );
#endif

#ifdef  USE_CAN2
      l_ret32 = CAN_Send ( &hcan2, &p );
#endif
      //ASSERT ( l_ret32 == HAL_OK );
      l_count = 0;
    }

#ifdef RUN_EMULATOR
    //
    //  if SensorOut Q not empty, send data
    //
    if ( uxQueueMessagesWaiting( SensorOutQId ) > 0 )
    {
      if ( xQueueReceive ( SensorOutQId, &SensorOutQItem, 200 ) == 1 )
      {
        p.id        = SensorOutQItem.CAN_Id; // -------------------------------
        p.dlc       = 8;
        p.data_h[0] = SensorOutQItem.value1;
        p.data_h[1] = SensorOutQItem.value2;
        p.data_h[2] = SensorOutQItem.value3;
        p.data_h[3] = SensorOutQItem.value4;

#ifdef  USE_CAN1
        l_ret32 = CAN_Send ( &hcan1, &p );
#endif

#ifdef  USE_CAN2
        l_ret32 = CAN_Send ( &hcan2, &p );
#endif
        //ASSERT ( l_ret32 == HAL_OK );
        //break;
      }
    }
#endif

    //
    //  if Event Q not empty, send data
    //
    if ( uxQueueMessagesWaiting( EventQId ) > 0 )
    {
      if ( xQueueReceive ( EventQId, &EventQItem, 200 ) == 1 )
      {
        switch ( EventQItem.Command )
        {
          case cCmdFlapsData :  // --------------------------------------------
            p.id        = c_CID_AUD_Flaps_Data;
            p.dlc       = 3;
            p.data_h[0] = EventQItem.FlapsPosition;
            p.data_b[2] = EventQItem.SwitchPattern;

#ifdef  USE_CAN1
            l_ret32 = CAN_Send ( &hcan1, &p );
#endif

#ifdef  USE_CAN2
            l_ret32 = CAN_Send ( &hcan2, &p );
#endif
            //ASSERT ( l_ret32 == HAL_OK );
            break;


          case cCmdTemperature :  // ------------------------------------------
            p.id          = c_CID_AUD_Temperature;
            p.dlc         = 4;
            p.data_sw[0]  = (int32_t)(EventQItem.SensedValue);

#ifdef  USE_CAN1
            l_ret32 = CAN_Send ( &hcan1, &p );
#endif

#ifdef  USE_CAN2
            l_ret32 = CAN_Send ( &hcan2, &p );
#endif
            //ASSERT ( l_ret32 == HAL_OK );
            break;


          case cCmdHumidity : //  ---------------------------------------------
            p.id          = c_CID_AUD_Humidity;
            p.dlc         = 4;
            p.data_w[0]   = (uint32_t)(EventQItem.SensedValue);

#ifdef  USE_CAN1
            l_ret32 = CAN_Send ( &hcan1, &p );
#endif

#ifdef  USE_CAN2
            l_ret32 = CAN_Send ( &hcan2, &p );
#endif
            //ASSERT ( l_ret32 == HAL_OK );
            break;


          case cCmdPressure : //  ---------------------------------------------
            p.id          = c_CID_AUD_Pressure;
            p.dlc         = 4;
            p.data_w[0]   = (uint32_t)(EventQItem.SensedValue);

#ifdef  USE_CAN1
            l_ret32 = CAN_Send ( &hcan1, &p );
#endif

#ifdef  USE_CAN2
            l_ret32 = CAN_Send ( &hcan2, &p );
#endif
            //ASSERT ( l_ret32 == HAL_OK );
            break;

        }
      }
    }

  }
}
//
// *****************************************************************************
// The End
// *****************************************************************************

