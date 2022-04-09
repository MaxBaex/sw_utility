# Firmware for the LARUS Audio-All-In-One-Board
Firmware for a module based on the STM32F407VTG Discovery Board providing the following functions :
- sophisticated audio output
- (optional) sensor for 3 micro switches (used for "air brakes extended", "gear extended" and "flaps above neutral") 
  and a potentiometer (used to find the current flap setting)
- (optional) driver for an array of LEDs to signal current and proposed flap settings     
- (optional) I2C connection and driver for the BME temperature and humidity sensor

The board is connected to the soar vario CAN bus. 
In- and outgoing CAN bus communications adher to the project wide definitions in Generic_CAN_Ids.h .

This module was built by Horst Rupp on a strictly prototype basis. The STM32F4 Disco Board is piggy-packed on a "manually webbed" PCB. So far there are only two specimen of this board.
In the long run this board should be completely obsolete as Max Baetz has designed a smaller and cheaper replacement based on either an F103 Blue Pill (also piggy-packed), or on an F4 processor (directly on-board).

The module fits into the standard blue Hammond box, which was used for the soar sensor in the first place.
