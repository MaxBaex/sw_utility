/**
  * ############################################################################
  * @file     task_SideWall_Sensor.c
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
#include <task_SideWall_Sensor.h>

#define   c_max_brightness    0
#define   c_min_brightness    15
#define   c_no_of_ADC_readings  8
#define   c_no_of_Conversions 16
#define   c_stack_depth_power 2
#define   c_stack_depth       4   // must be 2**c_stack_depth_power
#define   c_blink_alive_limit 10


//
// *****************************************************************************
//
void SideWall_Sensor ( void * nix)
{

  uint16_t  l_q_result,
            l_blink_alive_counter_Flaps     = 0;
  uint16_t  l_ADC_reading,
            l_old_ADC_reading,
            l_flaps_position;
  uint8_t   l_switch_pattern,
            l_old_switch_pattern;

// =============================================================================
//
  l_ADC_reading      = 0;
  l_old_ADC_reading  = 0;

  // the works
  //
  while ( 1 )
  {
    vTaskDelay( c_WakeFlapSensor );

    //
    //  time base
    //
    g_Time_in_Ticks   = xTaskGetTickCount( );        // time in msec
    g_SystemTime_ms   = g_Time_in_Ticks;
    g_SystemTime_sec  = g_SystemTime_ms / 1000;

    //
    //  Flaps Sensor heart beat blinker
    //
    l_blink_alive_counter_Flaps++;
    if ( l_blink_alive_counter_Flaps < c_blink_alive_limit / 2 )
    {
      HAL_GPIO_WritePin ( LED_Port, LEDred_Pin, GPIO_PIN_SET );
    }
    else
    {
      HAL_GPIO_WritePin ( LED_Port, LEDred_Pin, GPIO_PIN_RESET );
    }

    if ( l_blink_alive_counter_Flaps > c_blink_alive_limit )
    {
      l_blink_alive_counter_Flaps = 0;
    }

    l_switch_pattern   = 0;
    l_switch_pattern   |= ( ! HAL_GPIO_ReadPin ( External_Switches_Port, Check_Connection ) ) << 0;
    l_switch_pattern   |= ( ! HAL_GPIO_ReadPin ( External_Switches_Port, GearExtended ) ) << 1;
    l_switch_pattern   |= ( ! HAL_GPIO_ReadPin ( External_Switches_Port, AirBrakesExtended ) ) << 2;
    l_switch_pattern   |= ( ! HAL_GPIO_ReadPin ( External_Switches_Port, FlapsAboveNeutral ) ) << 3;

    l_ADC_reading = Get_ADC_Converted_Value ( 1 );

    //
    //  Send data to AD57 whenever there is a change
    l_old_switch_pattern  = l_switch_pattern;
    l_old_ADC_reading 	= l_ADC_reading;

    l_flaps_position = ( l_ADC_reading * 1000 ) >> 12; // div 4096

    EventQItem.Command  = cCmdFlapsData;
    EventQItem.FlapsPosition = l_flaps_position;
    EventQItem.SwitchPattern  = l_switch_pattern;
    l_q_result = xQueueSend ( EventQId, &EventQItem, portMAX_DELAY );
    if ( l_q_result != pdTRUE )
    {
      l_q_result = 1;
    }
  }  // while ( 1 )
}

//
// *******************************************************************************
// The End
// *******************************************************************************
