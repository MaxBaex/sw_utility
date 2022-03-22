/**
 * @file  task_I2C_Handler.h
 * @brief  New Vario
 * @author  Horst Rupp
 */
//
//
#include  "Generic_Common.h"
#include  "Generic_Signature.h"
#include  "Generic_Signature_Lib.h"
#include  "I2C.h"
#include  "Portable_Utils.h"

#ifdef BUILD_VARIO
	#include  "IO_Exp_Lib.h"
#endif


//
// *****************************************************************************
//
#ifndef __task_I2C_Handler_H
  #define __task_I2C_Handler_H
  //
  //  signatures
  //
  void  I2C_Handler             ( void * nix );
  void  create_task_I2C_Handler ( void );

#endif
//
// *****************************************************************************
// The End
// *****************************************************************************

