#include "audio.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "can.h"
#include "communication.h"


extern CAN_HandleTypeDef hcan;  //Defined in main.c from generator
static CAN_Packet_t txPacket, rxPacket;

QueueHandle_t COM_Message_Queue;
#define COM_Message_Queue_Len  10

void StartComTask(void *argument)
{
  CAN_Init(&hcan);

  CAN_RAW_DATA rawData;

  COM_Message_Queue = xQueueCreate(COM_Message_Queue_Len, sizeof(CAN_RAW_DATA));

  txPacket.id = c_CAN_Id_Temperature;
  txPacket.dlc = 8;
  txPacket.data_l = 0;


  for(;;)
    {
      if (HAL_OK == CAN_Receive(&hcan, &rxPacket))
	{
	  /*Do something with the received data. But do not wait!*/
	}


      /* Send data here*/
      if (pdTRUE == xQueueReceive(COM_Message_Queue, &rawData, 100))
	{

	  if (rawData.id == c_CAN_Id_Temperature)
	    {
	      txPacket.id = c_CAN_Id_Temperature;
	      txPacket.dlc = 4;
	      txPacket.data_sw[0] = (int32_t)(rawData.value * 1000.0);
	      if (HAL_OK != CAN_Send(&hcan, &txPacket))
		{
		   //Don't care if package can not be sent
		}
	    }
	  if (rawData.id == c_CAN_Id_Humidity)
	    {
	      txPacket.id = c_CAN_Id_Humidity;
	      txPacket.dlc = 4;
	      txPacket.data_w[0] = (uint32_t)(rawData.value * 1000.0);
	      if (HAL_OK != CAN_Send(&hcan, &txPacket))
		{
		  //Don't care if package can not be sent
		}
	    }
	  if (rawData.id == c_CAN_Id_Pressure)
	    {
	      txPacket.id = c_CAN_Id_Pressure;
	      txPacket.dlc = 4;
	      txPacket.data_w[0] = (uint32_t)(rawData.value * 1000.0);
	      if (HAL_OK != CAN_Send(&hcan, &txPacket))
		{
		  //Don't care if package can not be sent
		}
	    }

	}

    }
}

