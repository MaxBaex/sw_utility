#include "audio.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "can.h"
#include "communication.h"


extern CAN_HandleTypeDef hcan;  //Defined in main.c from generator
CAN_Packet_t txPacket;

void StartComTask(void *argument)
{
  CAN_Init(&hcan);

  txPacket.id = c_CAN_Id_Temperature;
  txPacket.dlc = 8;
  txPacket.data_l = 0;


  for(;;)
   {
     CAN_Send(&hcan, &txPacket);

      txPacket.data_l++;

      vTaskDelay(250);
   }
}

