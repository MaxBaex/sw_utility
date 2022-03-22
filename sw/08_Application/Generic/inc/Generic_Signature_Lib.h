/**
  * ############################################################################
  * @file     Generic_Signature_Lib.h
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This file contains
  * @brief    This
  * ############################################################################
  */
//******************************************************************************
//
// Includes
//
#include  "Generic_Types.h"

#ifndef __Generic_Signature_Lib_H
  #define __Generic_Signature_Lib_H



//******************************************************************************
//
  #ifdef  __cplusplus
    extern "C" {
  #endif

    void  Read_Appl_Data_from_EEProm ( void );
    void  Clear_Appl_Data_in_EEProm ( void );
    void  Save_Appl_Data_to_EEProm  ( void );

  #ifdef  __cplusplus
    }


  #endif

#endif  // #ifndef __Generic_Signature_Lib_H
//
// ******************************************************************************************
//  The End
// ******************************************************************************************

