/**
 * @file  task_CAN_Bus_Sender.h
 * @brief  New Vario
 * @author  Horst Rupp
 */
//
//
#include  "Generic_Common.h"
#include  "Generic_Includes.h"

//extern  SD_HandleTypeDef hsd;
extern  DMA_HandleTypeDef hdma_sdio_rx;
extern  DMA_HandleTypeDef hdma_sdio_tx;

//
// *****************************************************************************
//
#ifndef __task_CAN_Bus_Sender_H
  #define __task_CAN_Bus_Sender_H
  //
  //  signatures
  //
  void CAN_Bus_Sender ( void * nix );
  void create_task_CAN_Bus_Sender ( void );

#endif    // __task_CAN_Bus_Sender_H
//
// *****************************************************************************
// The End
// *****************************************************************************

