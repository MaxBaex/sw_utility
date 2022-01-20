#include "audio.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"

#define NS       128
#define TIM4CLK  72000000
#define F_SIGNAL 1000

uint32_t Wave_LUT[NS] = {
    512, 537, 562, 587, 612, 637, 661, 685, 709, 732, 754, 776, 798, 818, 838,
    857, 875, 893, 909, 925, 939, 952, 965, 976, 986, 995, 1002, 1009, 1014, 1018,
    1021, 1023, 1023, 1022, 1020, 1016, 1012, 1006, 999, 990, 981, 970, 959, 946, 932,
    917, 901, 884, 866, 848, 828, 808, 787, 765, 743, 720, 697, 673, 649, 624,
    600, 575, 549, 524, 499, 474, 448, 423, 399, 374, 350, 326, 303, 280, 258,
    236, 215, 195, 175, 157, 139, 122, 106, 91, 77, 64, 53, 42, 33, 24,
    17, 11, 7, 3, 1, 0, 0, 2, 5, 9, 14, 21, 28, 37, 47,
    58, 71, 84, 98, 114, 130, 148, 166, 185, 205, 225, 247, 269, 291, 314,
    338, 362, 386, 411, 436, 461, 486, 511
};


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_tim4_ch1;

uint32_t DestAddress = (uint32_t) &(TIM2->CCR1);
uint32_t TIM4_Ticks = TIM4CLK / (NS * F_SIGNAL);

void StartAudioTask(void *argument)
{

  htim4.Init.Period = TIM4_Ticks - 1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
   {
     Error_Handler();
   }

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
  HAL_DMA_Start_IT(&hdma_tim4_ch1, (uint32_t)Wave_LUT, DestAddress, NS);

  __HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC1);


  for(;;)
  {
    osDelay(1);
  }

}

