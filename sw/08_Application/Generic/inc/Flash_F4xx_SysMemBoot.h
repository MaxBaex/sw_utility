/**
 * @file  Flash_F4xx_SysMemBoot.h
 * @brief  New Vario
 * @author  Horst Rupp
 */

#ifndef __Flash_F4xx_SysMemBoot_H
  #define __Flash_F4xx_SysMemBoot_H

  //
  // ***************************************************************************
  //

  #include "Generic_Includes.h"
  #include "stm32f4xx_hal.h"


  /** Address of System Memory (ST Bootloader) */
  #define SYSMEM_ADDRESS (uint32_t)0x1FFF0000

  typedef int ( *FPTR)( void); // declare void* -> int function pointer

  void    Bootloader_JumpToSysMem(void);

#endif  // Flash_F4xx_SysMemBoot
//
// **************************************************************************************
// ************************ EOF *********************************************************
// **************************************************************************************
//
