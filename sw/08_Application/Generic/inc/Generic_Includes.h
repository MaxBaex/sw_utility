/**
  ******************************************************************************
  * @file     Generic_Includes.h
  * @author   Horst Rupp
  * @brief    General_Includes for the New Vario
  ******************************************************************************
  */
/* prevent recursive inclusion -------------------------------------*/
#ifndef __Generic_Includes_H
  #define __Generic_Includes_H

  #include  "General_Includes.h"
  #include  "General_Const.h"
  #include  "General_Types.h"

  #include  "Generic_Const.h"
  #include  "Generic_Types.h"

  #include  "my_assert.h"

  //  **************************************************************************
  //
  #if ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )


    #include  "ff.h"
    #include  "semphr.h"
    //#include  "Box_Lib.h"

//    #include  "BaDisplay.h"
//    #include  "BaDisplayTest.h"
//    #include  "BaBasicGraphicFunctions.h"
//    #include  "BaGraphicFunctions.h"
//    #include  "BaBasicFont.h"
//    #include  "BaFont.h"

  #endif

#endif /* __Generic_Includes_H */

/*****************************END OF FILE**************************************/
