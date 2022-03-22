#include "uart2.h"
#include "my_assert.h"
//#include "FreeRTOS_wrapper.h"

#define uart2_DEFAULT_TIMEOUT 250
#define uart2_RX_QUEUE_SIZE 64

static COMMON QueueHandle_t uart2_CPL_Message_Id = NULL;
static COMMON QueueHandle_t uart2_Rx_Queue = NULL;

static uint8_t uart2_rx_byte = 0; //
void uart2_Init(void)
{
  if (uart2_CPL_Message_Id == NULL)
    {
      uart2_CPL_Message_Id =  xQueueCreate(1,0);
    }
  if (uart2_Rx_Queue == NULL)
    {
      uart2_Rx_Queue =  xQueueCreate(uart2_RX_QUEUE_SIZE, sizeof(uint8_t));
    }
  HAL_UART_Init(&huart2);
  HAL_UART_Receive_IT(&huart2, &uart2_rx_byte, 1); // Activate interrupt for rx data
}

void uart2_DeInit(void)
{
  HAL_UART_Abort(&huart2);
  HAL_UART_DeInit(&huart2);
}

void uart2_ChangeBaudRate(uint32_t rate)
{
  HAL_UART_Abort(&huart2);
  HAL_UART_DeInit(&huart2);
  huart2.Init.BaudRate = rate;
  HAL_UART_Init(&huart2);

  HAL_UART_Receive_IT(&huart2, &uart2_rx_byte, 1); // Activate interrupt for rx data
}

void uart2_Transmit(uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef status = HAL_OK;
  BaseType_t queue_status = pdFALSE;

  status = HAL_UART_Transmit_DMA(&huart2, pData, Size);
  ASSERT(HAL_OK == status);

  queue_status = xQueueReceive(uart2_CPL_Message_Id, 0, uart2_DEFAULT_TIMEOUT);
  ASSERT(pdTRUE == queue_status);
}

bool uart2_Receive(uint8_t *pRxByte, uint32_t timeout)
{
  BaseType_t queue_status = pdFALSE;

  queue_status = xQueueReceive(uart2_Rx_Queue, pRxByte, timeout);
  if(pdTRUE == queue_status)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  BaseType_t xHigherPriorityTaskWokenByPost = pdFALSE;
  BaseType_t queue_status;

  if (huart->Instance == USART2)
    {
      queue_status = xQueueSendFromISR(uart2_CPL_Message_Id, 0, &xHigherPriorityTaskWokenByPost);
    }
  else
    {
      ASSERT(0);
    }
  ASSERT(pdTRUE == queue_status);
  portYIELD_FROM_ISR(xHigherPriorityTaskWokenByPost);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  BaseType_t xHigherPriorityTaskWokenByPost = pdFALSE;
  BaseType_t queue_status;

  if (huart->Instance == USART2)
    {
      /*Get Byte and enable interrupt again*/
      queue_status = xQueueSendFromISR(uart2_Rx_Queue, &uart2_rx_byte, &xHigherPriorityTaskWokenByPost);
      HAL_UART_Receive_IT(&huart2, &uart2_rx_byte, 1);
      ASSERT(pdTRUE == queue_status);
    }
  else
    {
      //    ASSERT(0);
    }
  portYIELD_FROM_ISR(xHigherPriorityTaskWokenByPost);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart)
{

}


