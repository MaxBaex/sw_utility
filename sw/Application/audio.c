#include "audio.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "main.h"

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


//With some harmonics and a step in between:
uint32_t Wave_LUT_1[NS] = {
  518 , 522 , 698 , 933 , 990 , 866 , 787 , 853 , 886 , 712 , 445 , 325 , 359 , 328 ,
  144 , 0 , 77 , 268 , 341 , 297 , 355 , 600 , 829 , 856 , 781 , 825 , 972 , 991 , 796 ,
  585 , 541 , 562 , 434 , 184 , 52 , 133 , 238 , 195 , 117 , 224 , 487 , 664 , 659 , 656 ,
  814 , 1006 , 1006 , 832 , 719 , 755 , 751 , 550 , 286 , 193 , 255 , 250 , 103 , 15 , 149 ,
  376 , 467 , 438 , 513 , 753 , 950 , 930 , 815 , 824 , 926 , 892 , 658 , 435 , 396 , 421 ,
  303 , 85 , 7 , 142 , 285 , 274 , 235 , 377 , 650 , 810 , 779 , 752 , 880 , 1022 , 961 ,
  742 , 605 , 622 , 598 , 389 , 147 , 96 , 199 , 227 , 122 , 87 , 270 , 520 , 612 , 583 , 655 ,
  874 , 1023 , 947 , 790 , 766 , 829 , 754 , 497 , 281 , 263 , 309 , 215 , 41 , 22 , 209 , 383 ,
  394 , 380 , 539 , 803 , 928 , 856 , 797
};



extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_tim4_ch1;
extern DMA_HandleTypeDef hdma_tim4_ch2;

uint32_t DestAddress_ch1 = (uint32_t) &(TIM2->CCR1);
uint32_t DestAddress_ch2 = (uint32_t) &(TIM2->CCR2);
uint32_t TIM4_Ticks = TIM4CLK / (NS * F_SIGNAL);

void StartAudioTask(void *argument)
{

  htim4.Init.Period = TIM4_Ticks - 1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
   {
     Error_Handler();
   }

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);
  HAL_DMA_Start_IT(&hdma_tim4_ch1, (uint32_t)Wave_LUT, DestAddress_ch1, NS);
  HAL_DMA_Start_IT(&hdma_tim4_ch2, (uint32_t)Wave_LUT, DestAddress_ch2, NS);

  __HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC1);
  __HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC2);

  /*
   * PA7,  PA6,  PA5,   PA4,   PA3,    PA2
   * 0x80  0x40  0x20   0x10   0x08    0x04
   *
   * Pin = 0 => low volume,  Pin = 1 => high volume
   *
   * lowest volume =  0x111111XX
   * highest volume = 0x000000XX
   *
   */
  HAL_GPIO_WritePin(GPIOA, ATTN_1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ATTN_2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ATTN_3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ATTN_4_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ATTN_5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, ATTN_6_Pin, GPIO_PIN_RESET);

  for(;;)
   {





      HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_1);
      HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_2);
      osDelay(250);

      htim4.Init.Period =  TIM4CLK / (NS * 1000) - 1;
      HAL_TIM_Base_Init(&htim4);
      HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
      HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);
      osDelay(250);

      HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_1);
      HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_2);
      osDelay(250);

      htim4.Init.Period =  TIM4CLK / (NS * 2000) - 1;
      HAL_TIM_Base_Init(&htim4);
      HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
      HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);
      osDelay(250);

   }



  for(;;)
  {





    HAL_GPIO_WritePin(GPIOA, ATTN_1_Pin, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(GPIOA, ATTN_2_Pin, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(GPIOA, ATTN_3_Pin, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(GPIOA, ATTN_4_Pin, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(GPIOA, ATTN_5_Pin, GPIO_PIN_RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(GPIOA, ATTN_6_Pin, GPIO_PIN_RESET);
    osDelay(1000);


    GPIOA->ODR = 0xFC;   // Set maximum volume
    osDelay(5000);
  }

}

