#include "can.h"
#include "main.h"
#include "queue.h"

QueueHandle_t CAN1_rxQueue_Id;


  HAL_StatusTypeDef CAN_Init(CAN_HandleTypeDef *hcan)
{
  if(hcan->Instance == CAN1)
  {
    CAN1_rxQueue_Id = xQueueCreate(CAN_RX_QUEUE_LEN, sizeof(CAN_Packet_t));
    if (CAN1_rxQueue_Id == 0)
    {
      Error_Handler();
    }
  }

  /*Receive all messages on fifo 0, do not filter yet*/
  CAN_FilterTypeDef sFilterConfig;
  sFilterConfig.FilterIdHigh = 0xFFFF;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0xFFFF;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
  sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
  sFilterConfig.SlaveStartFilterBank = 0;

  if (HAL_CAN_ConfigFilter(hcan, &sFilterConfig)!= HAL_OK)
    {
      Error_Handler();
    }

  if (HAL_CAN_ActivateNotification(hcan, CAN_IT_TX_MAILBOX_EMPTY|CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK)
    {
      Error_Handler();
    }

  if (HAL_CAN_Start(hcan) != HAL_OK)
    {
      Error_Handler();
    }

  return HAL_OK;
}

HAL_StatusTypeDef CAN_Send(CAN_HandleTypeDef *hcan, CAN_Packet_t *p)
{
  CAN_TxHeaderTypeDef canHeader;
  canHeader.StdId = (uint32_t)p->id;
  canHeader.ExtId = 0;
  canHeader.IDE = CAN_ID_STD;
  canHeader.RTR = CAN_RTR_DATA;
  canHeader.DLC = p->dlc;

  uint32_t usedMailbox;  // NOTE: only required for STM32F1

  return HAL_CAN_AddTxMessage(hcan, &canHeader, p->data_b, &usedMailbox);
}

HAL_StatusTypeDef CAN_Receive(CAN_HandleTypeDef *hcan, CAN_Packet_t *p)
{
  if(hcan->Instance == CAN1)
    {
      if (xQueueReceive(CAN1_rxQueue_Id, p, CAN_RX_TIMEOUT_MS) == pdTRUE)
      	{
      	  return HAL_OK;
      	}
      else
      	{
      	  return HAL_TIMEOUT;
      	}
    }

  return HAL_ERROR;
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_TxMailbox0AbortCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_TxMailbox1AbortCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_TxMailbox2AbortCallback(CAN_HandleTypeDef *hcan)
{

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  BaseType_t xHigherPriorityTaskWokenByPost = pdFALSE;
  CAN_RxHeaderTypeDef rxfifo0_header;
  uint8_t rxfifo0_rxData[8];

  HAL_CAN_GetRxMessage(hcan, 0, &rxfifo0_header, rxfifo0_rxData);

  CAN_Packet_t p;
  p.id = (uint16_t)rxfifo0_header.StdId;
  p.dlc = rxfifo0_header.DLC;

  for (int i = 0; i < p.dlc; i++)
  {
    p.data_b[i] = rxfifo0_rxData[i];
  }

  if(hcan->Instance == CAN1)
  {
    if( xQueueSendFromISR(CAN1_rxQueue_Id, &p, &xHigherPriorityTaskWokenByPost) != pdTRUE)
  	{
  	  Error_Handler();
  	}
  }

  portYIELD_FROM_ISR(xHigherPriorityTaskWokenByPost);
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
  Error_Handler();
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  Error_Handler();
}

void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
{
  Error_Handler();
}

void HAL_CAN_SleepCallback(CAN_HandleTypeDef *hcan)
{
  Error_Handler();
}

void HAL_CAN_WakeUpFromRxMsgCallback(CAN_HandleTypeDef *hcan)
{
  Error_Handler();
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
  Error_Handler();
}
