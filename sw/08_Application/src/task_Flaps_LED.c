/**
  * ############################################################################
  * @file     task_Flaps_LED.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This task outputs bit pattern on the LED panel.
  * ############################################################################
  */
//
// Includes
//
#include  "task_Flaps_LED.h"
#include  "PWM_Lib.h"


#define		c_reduced_duty_cycle	30

#ifdef BRIGHTNESS_REGULATION_ACTIVE
  extern TIM_HandleTypeDef htim3;  // PWM by Horst
#endif


// =============================================================================
//
  void  Check_Leads_LED_Register ( void )
  {
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR,  GPIO_PIN_LOW ); 	// yellow   Pin 10
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER,        GPIO_PIN_LOW ); 	// orange   Pin 14
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK,      GPIO_PIN_LOW ); 	// green    Pin 11
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK,       GPIO_PIN_LOW ); 	// white    Pin 12

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR,  GPIO_PIN_HIGH );	// yellow   Pin 10
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER,        GPIO_PIN_HIGH );  // orange   Pin 14
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK,      GPIO_PIN_HIGH );  // green    Pin 11
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK,       GPIO_PIN_HIGH );  // white    Pin 12

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR,  GPIO_PIN_LOW ); 	// yellow   Pin 10
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER,        GPIO_PIN_LOW ); 	// orange   Pin 14
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK,      GPIO_PIN_LOW ); 	// green    Pin 11
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK,       GPIO_PIN_LOW ); 	// white    Pin 12

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR,  GPIO_PIN_HIGH );  // yellow   Pin 10
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR,  GPIO_PIN_LOW ); 	// yellow   Pin 10

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER,        GPIO_PIN_HIGH );  // orange   Pin 14
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER,        GPIO_PIN_LOW ); 	// orange   Pin 14

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK,      GPIO_PIN_HIGH );  // green    Pin 11
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK,      GPIO_PIN_LOW ); 	// green    Pin 11

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK,       GPIO_PIN_HIGH );  // white    Pin 12
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK,       GPIO_PIN_LOW ); 	// white    Pin 12
  }

  // =============================================================================
//
void  Clear_LED_Register ( void )
{
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR, GPIO_PIN_HIGH );	// yellow   Pin 10
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR, GPIO_PIN_LOW ); // yellow   Pin 10
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR, GPIO_PIN_LOW ); // yellow   Pin 10
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR, GPIO_PIN_HIGH );   // yellow   Pin 10
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_LOW );
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_HIGH );      // white    Pin 12
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_LOW );
}
// =============================================================================
//
void Write_LED_Register ( uint8_t pattern_1, uint8_t pattern_2 )
{
  uint8_t i, j, l_data;
  //
  //    Caution : Colours are interleaved
  //
  //   output bit 0               green
  //   output bit 1               red
  //   output bit 2               green
  //   output bit 3               red
  //   output bit 4               green
  //
  //
  //   output bit 12              green
  //   output bit 13              res
  //   output bit 14              green
  //   output bit 15              red

  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_NEG_SRCLR, GPIO_PIN_HIGH ); // yellow   Pin 10

  for ( i = 0; i < 16; i++ )
  {
    l_data = 0;
    j = i / 2;
    if ( j * 2 == i )
    { // even
      if ( ( pattern_1 & ( 1 << j ) ) != 0 )
        l_data = 1;
    }
    else
    { // odd
      if ( ( pattern_2 & ( 1 << j ) ) != 0 )
        l_data = 1;
    }
    if ( l_data != 0 )
      HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER, GPIO_PIN_HIGH );
    else
      HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER, GPIO_PIN_LOW );

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK, GPIO_PIN_HIGH );
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SRCLK, GPIO_PIN_LOW );
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_SER, GPIO_PIN_LOW );

    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_HIGH );
    HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_LOW );
  }
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_HIGH );
  HAL_GPIO_WritePin ( Shift_Reg_Port, Shift_Reg_RCLK, GPIO_PIN_LOW );
}

//
// *****************************************************************************
//
void Flaps_LED ( void * nix)
{
  #define   c_local_wait      200
  #define   c_flipfloplimit   10

  uint32_t  l_flipflopcounter = 0;
  uint8_t   pattern1, pattern2;
  uint8_t   old_pattern1 = 0;
  uint8_t   old_pattern2 = 0;
  uint8_t   l_CurrentFlapsSetting;
  uint8_t   l_OptimalFlapsSetting;
  uint8_t	l_duty_cycle;

  //
  //  Switch off Flaps LEDs
  //
  Clear_LED_Register ( );

  //
  //  Switch on dimming (brightness control)
  //

#if 0
  //
  //  Test Flaps LEDs
  //
  Check_Leads_LED_Register ( );
#endif

#if 1
  Write_LED_Register ( 0b00000000, 0b11111111 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b11111111, 0b00000000 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b00000000, 0b11111111 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b11111111, 0b00000000 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b00000000, 0b11111111 );
  vTaskDelay( c_local_wait );
#endif
#if 1
  Write_LED_Register ( 0b11111111, 0b00000000 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b10101010, 0b01010101 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b01010101, 0b10101010 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b10101010, 0b01010101 );
  vTaskDelay( c_local_wait );
  Write_LED_Register ( 0b01010101, 0b10101010 );
  vTaskDelay( c_local_wait );
#endif

  // the works
  //
#if 1
  while ( 1 )
  {
    vTaskDelay( c_WakeFlapsLED );

    if  ( g_FlapsFlashControl & ( 1 << c_FlashPatternInvert ) )
      g_FlashPatternInvert = true;
    else
      g_FlashPatternInvert = false;

    if  ( g_FlapsFlashControl & ( 1 << c_FlashRowInvert ) )
      g_FlashRowInvert = true;
    else
      g_FlashRowInvert = false;

    //
    //  OutPut Flaps LEDs
    //
    l_CurrentFlapsSetting = g_CurrentFlapsSetting;
    l_OptimalFlapsSetting = g_OptimalFlapsSetting;

    if ( g_FlashRowInvert )
    {
      l_CurrentFlapsSetting = g_OptimalFlapsSetting;
      l_OptimalFlapsSetting = g_CurrentFlapsSetting;
    }

    if ( g_FlashPatternInvert )
    {
      l_CurrentFlapsSetting = g_NoFlapsPositions-1 - l_CurrentFlapsSetting;
      l_OptimalFlapsSetting = g_NoFlapsPositions-1 - l_OptimalFlapsSetting;
    }

    pattern1 = ( 1 << l_CurrentFlapsSetting );
    pattern2 = ( 1 << l_OptimalFlapsSetting );
    l_duty_cycle = 100 - g_LEDDutyCycle;


    if  ( g_FlapsFlashControl & ( 1 << c_FlashOneBit1 ) )
    {
      if ( l_flipflopcounter < c_flipfloplimit/2 )
      {
        pattern1 = 0;       // red
      }
    }

    if  ( g_FlapsFlashControl & ( 1 << c_FlashOneBit2 ) )
    {
      if ( l_flipflopcounter < c_flipfloplimit/2 )
      {
        pattern2 = 0;       // green
      }
    }

    if  ( g_FlapsFlashControl & ( 1 << c_FlashPattern1 ) )
    {
      if ( l_flipflopcounter < c_flipfloplimit/2 )
      {
        pattern1 = 0;
      }
      else
      {
        pattern1 = 0xff;
        l_duty_cycle = c_reduced_duty_cycle;
      }
    }

    if  ( g_FlapsFlashControl & ( 1 << c_FlashPattern2 ) )
    {
      if ( l_flipflopcounter < c_flipfloplimit/2 )
      {
        pattern2 = 0;
      }
      else
      {
        pattern2 = 0xff;
        l_duty_cycle = c_reduced_duty_cycle;
      }
    }

    if  ( g_FlapsFlashControl & ( 1 << c_FlashPatternBoth ) )
    {
      if ( l_flipflopcounter < c_flipfloplimit/2 )
      {
        pattern1 = 0;
        pattern2 = 0xff;
      }
      else
      {
        pattern1 = 0xff;
        pattern2 = 0;
      }
      l_duty_cycle = c_reduced_duty_cycle;
    }

#if 0
    if  ( g_FlapsFlashControl != 0 )
      pattern1 = ( 1 << g_CurrentFlapsSetting );
#endif
    if  (
          ( old_pattern1 != pattern1 )
        ||
          ( old_pattern2 != pattern2 )
        )
    {
      Write_LED_Register ( pattern1, pattern2 );
      old_pattern1 = pattern1;
      old_pattern2 = pattern2;
    }

#ifdef BRIGHTNESS_REGULATION_ACTIVE
    PWM_SetValue ( l_duty_cycle );
#endif

    l_flipflopcounter++;
    if ( l_flipflopcounter >= c_flipfloplimit )
      l_flipflopcounter = 0;

  }  // while ( 1 )
#endif
}

// *******************************************************************************
// The End
// *******************************************************************************
