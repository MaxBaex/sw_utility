/**
  * ############################################################################
  * @file     PWM_Lib.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This routine TODO
  * ############################################################################
  */
//
// Includes
//
#include  "PWM_Lib.h"
#include  "General_Includes.h"
#include  "Generic_Common.h"

extern  TIM_HandleTypeDef    htim3;

//  ============================================================================
//
//  Set relative brightness as percentage
//
void PWM_SetValue ( uint8_t percentage )
{
  float               l_pulse_width = (float) 65535.0 * percentage / 100.0;            // TODO
  uint16_t            i_pulse_width = floor ( l_pulse_width );
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, i_pulse_width );
}
//
// =============================================================================
//  The End
// =============================================================================
