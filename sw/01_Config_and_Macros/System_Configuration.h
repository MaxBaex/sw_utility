
#ifndef __System_Configuration_H_
  #define __System_Configuration_H_

  #define BUILD_AUDIO
  //#define   BUILD_VARIO
  //#define BUILD_BOOTLOADER

  #ifdef BUILD_AUDIO
    #define RUN_AUDIO
    #define RUN_CAN_TASKS
    //#define RUN_SIDEWALL_SENSOR
    #define RUN_TEMPHUM_SENSOR
    #define RUN_EMULATOR
    //#define BRIGHTNESS_REGULATION_ACTIVE

    //#define   USE_CAN1
    #ifndef   USE_CAN1
      #define   USE_CAN2
    #endif

    #define configUSE_TRACE_FACILITY  0
    #define TEST_ANAUTHORIZED_ACCESS  0
    #define RUN_GPIO_TESTER           0
    #define RUN_CAN_TEST              0
  #endif

  #ifdef BUILD_BOOTLOADER
    #define BL_STUB_ONLY
    #define RUN_BUTTON_TASK     1
  #endif

  #ifdef  BUILD_VARIO

    #define configUSE_TRACE_FACILITY  1
    #define TEST_ANAUTHORIZED_ACCESS  0
    #define RUN_BLINK_TASK            0
    #define RUN_CAN_TEST              0


    //#define MINIMUM_NO_OF_POINTERS
    //#define SD_Failure_Demo
    //#define TEST_AUDIO
    //#define FLAPS_AVAILABLE
    //#define DEBUGGING_ON

    #ifdef DEBUGGING_ON
      //#define CHECK_COLORS
      #define DEBUG_HORIZON
      //#define SHOW_HORIZON_FOOT_POINT
      //#define DEBUG_HORIZON_OUTPUT
    #endif

  #endif

#endif /* __System_Configuration_H_ */
