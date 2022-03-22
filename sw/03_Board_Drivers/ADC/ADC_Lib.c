/**
  * ############################################################################
  * @file     ADC_Lib.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This routine TODO
  * ############################################################################
  */
//
// Includes
//
#include  "ADC_Lib.h"

extern  ADC_HandleTypeDef       hadc1;
extern  ADC_ChannelConfTypeDef  sConfig;


//  ============================================================================
//
uint32_t MyADCInit ( void )
{
  HAL_StatusTypeDef l_HAL_ADC_retcode;
  l_HAL_ADC_retcode = HAL_ADC_Init ( &hadc1 );
  return 1;
}

//  ============================================================================
//
uint32_t Get_ADC_Converted_Value (uint8_t channel )
{
  HAL_StatusTypeDef l_HAL_ADC_retcode;
  uint32_t          l_ADC_value;

  sConfig.Channel = (uint32_t) channel;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  //acquire_privileges();
  l_HAL_ADC_retcode = HAL_ADC_Start ( &hadc1 );
  //drop_privileges();
  ASSERT ( l_HAL_ADC_retcode == HAL_OK );

  //acquire_privileges();
  l_HAL_ADC_retcode = HAL_ADC_PollForConversion ( &hadc1, 20 );
  //drop_privileges();
  ASSERT ( l_HAL_ADC_retcode == HAL_OK );

  vTaskDelay( 10 );   //  time for conversion to complete

  //acquire_privileges();
  l_ADC_value = HAL_ADC_GetValue ( &hadc1 );
  //drop_privileges();
  //ASSERT ( l_ADC_value > 450 );

  //acquire_privileges();
  l_HAL_ADC_retcode = HAL_ADC_Stop ( &hadc1 );
  ASSERT ( l_HAL_ADC_retcode == HAL_OK );
  //drop_privileges();

  return l_ADC_value;
}
//
// =============================================================================
//  The End
// =============================================================================
