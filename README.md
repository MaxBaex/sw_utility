# Firmware for the SOAR All-In-One-Board
Firmware for a module based on STM32F407VTG Discovery Board providing the following functions :
- sophisticated audio output
- sensor for 3 micro switches (used for "air brakes extended", "gear extended" and "flaps above neutral") and a potentiometer (used to find the current flap setting)
- driver for an array of LEDs to signal current and proposed flap settings     
- I2C connection and driver for the BME temperature and humidity sensor

The board is connected to the vario CAN bus. 
In- and outgoing CAN bus communications adher to the project wide definitions in Generic_CAN_Ids.h .
