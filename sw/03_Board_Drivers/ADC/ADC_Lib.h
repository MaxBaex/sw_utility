/**
  * ############################################################################
  * @file     ADC_Lib.h
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This routine TODO
  * ############################################################################
  */
//
// Includes
//
#ifndef __ADC_Lib_H
  #define __ADC_Lib_H

  #include  "General_Includes.h"
  #include  "Generic_Common.h"

  #ifdef __cplusplus
    extern "C" {
  #endif /* __cplusplus */

    uint32_t  MyADCInit ( void );
    uint32_t  Get_ADC_Converted_Value (uint8_t channel );

  #ifdef __cplusplus
    }
  #endif /* __cplusplus */

#endif // __ADC_Lib_H
//
// =============================================================================
//  The End
// =============================================================================

