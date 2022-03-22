/*
 *****************************************************************************
 *  @file   Audio_Lib.h
 *  @author Horst Rupp
 *  @brief  Created on: 21.11.2020
 *  @brief  Last Change : 28.11.2020
 *  @brief  These are the valid IDs for any data transfer on the CAN Bus.
 *****************************************************************************
 */

#ifndef  __Audio_Lib_h
  #define  __Audio_Lib_h

  //
  // *****************************************************************************
  //


  void Set_Volume     ( uint8_t vol );
  void Set_Frequency  ( uint16_t freq );
  void Start_Audio    ( uint16_t vol, uint16_t freq );

  void HAL_DAC_ConvCpltCallbackCh1 ( DAC_HandleTypeDef *hdac );



#endif
// ****************************************************************************
//  EOF
// ****************************************************************************

