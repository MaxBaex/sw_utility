/**
 * @file    task_Emulator.h
 * @brief   New Vario
 * @author  Horst Rupp
 */
//#include  "System_Configuration.h"
//#include  "FreeRTOS_wrapper.h"
//#include  "Generic_Application_Includes.h"
//
// *****************************************************************************
//

#ifndef  __task_Emulator_H
  #define  __task_Emulator_H

  #include  "General_Includes.h"
  #include  "Generic_Common.h"
  #include  "Generic_CAN_Ids.h"


  #include "stm32f4xx_hal.h"
  #include "main.h"
  #include "FreeRTOS.h"
  #include "task.h"
  #include "queue.h"


  //
  void  Emulator             ( void * nix );

#endif
//
// *****************************************************************************
// The End
// *****************************************************************************
