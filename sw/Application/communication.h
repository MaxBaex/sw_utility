#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#ifdef __cplusplus
extern "C" {
#endif


  //
  //  ******** Package IDs *****************************************************
  //
  enum CAN_PACKAGE_IDs
  {

    c_CAN_Id_Temperature          = 0x214,    //!< int32_t  // temp * 1000
    c_CAN_Id_Humidity             = 0x215,    //!< unit32_t // hum * 1000

    //
    //  FrontEnd to Audio
    //
    c_CAN_Id_F2A_HeartBeat        = 0x300,    //!< leer

    c_CAN_Id_Signal               = 0x301,    //!< uint8_t signal_id +
                                              //!< uint8_t signal_volume

    c_CAN_Id_Audio                = 0x302,    //!< int16_t  audio_frequency +
                                              //!< uint16_t interval +
                                              //!< uint8_t  audio-volume +
                                              //!< uint8_t  duty cycle
                                              //!< uint8_t  climb-mode

    c_CAN_Id_Flaps_Status         = 0x303,    //!< uint8_t  0/1 on/off-switch
                                              //!< uint8_t  CurrentFlapsSetting
                                              //!< uint8_t  OptimalFlapsSetting
                                              //!< uint8_t  FlapsFlashControl
                                              //!< uint8_t  LEDDutyCycle in %

    c_CAN_Id_Reboot               = 0x304,    //!< empty package, just a trigger

    //
    //  Audio to FrontEnd
    //
    c_CAN_Id_A2F_HeartBeat  = 0x400,    //!< leer
    c_CAN_Id_Send_Sec       = 0x401,    //!< ??   TODO
    c_CAN_Id_Flaps_Data     = 0x402,    //!< uint16_t position [percent * 100]
                                        //!> + uint8_t switch pattern [0b0000-0b1111]
  };




void StartComTask(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* __COMMUNICATION_H */


