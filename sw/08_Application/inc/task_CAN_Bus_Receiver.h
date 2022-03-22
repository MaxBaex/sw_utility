/**
  * * @file  task_CAN_Bus_Receiver.h
  * @brief  New Vario
  * @author  Horst Rupp
  */
//
// *****************************************************************************
//

#include <Flash_F4xx_SysMemBoot.h>
#include  "Generic_Const.h"
#include  "Generic_Common.h"
#include  "Generic_Includes.h"
#include  "can.h"
#include  "Generic_CAN_Ids.h"
#include  "FreeRTOS_wrapper.h"


#ifndef __task_CAN_Bus_Receiver_H
  #define __task_CAN_Bus_Receiver_H
  //
  //  signatures
  //
  void CAN_Bus_Receiver             ( void * nix );
  void create_task_CAN_Bus_Receiver ( void );

#endif
//
// *****************************************************************************
// The End
// *****************************************************************************

