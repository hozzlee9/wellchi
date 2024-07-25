
/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F1xx HAL API.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef  GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

extern uint32_t gTimeDelay;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This sample code shows how to use GPIO HAL API to toggle LED2 IO
    in an infinite loop. */

  /* STM32F103xB HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();
  
  /* -1- Enable GPIO Clock (to be able to program the configuration registers) */
  LED2_GPIO_CLK_ENABLE();

  /* -2- Configure IO in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);

/*  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);*/

  /* -3- Toggle IO in an infinite loop */


  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pin   = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

#if 0
#define FREQ_HIGH	100
#define FREQ_LOW	500
#define LIMIT_LOW	3
#define LIMIT_HIGH	10
#define BUTTON_PIN	GPIO_PIN_13
#define LED_PIN		GPIO_PIN_5


  uint32_t TargetTime		= FREQ_HIGH;
  uint32_t ButtonCnt		= LIMIT_HIGH;
  uint32_t ButtonCntUp		= 0;
  uint32_t LastButtonState	= 1; // 초기 버튼 상태


  while (1)
  {
	  uint32_t CurrentButtonState = HAL_GPIO_ReadPin(GPIOC, BUTTON_PIN);

    if (LastButtonState == 1 && CurrentButtonState == 0) // 버튼 눌림 감지
    {
    	ButtonCntUp++;
    	if (ButtonCntUp >= ButtonCnt) // 버튼 10회 이상 눌림
    	{
    		HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_RESET);
    		break;
    	}

    	if (TargetTime == FREQ_HIGH) // LED 깜빡임 주기 변경
    	{
    		TargetTime = FREQ_LOW;
    	}
    	else
    	{
    		TargetTime = FREQ_HIGH;
    	}
    }

    LastButtonState = CurrentButtonState;


    if (gTimeDelay >= TargetTime)
    {
    	gTimeDelay = 0;
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
  }



#define FREQ_HIGH	100
#define FREQ_LOW	500
#define LIMIT_LOW	3
#define LIMIT_HIGH	10
#define BUTTON_PIN	GPIO_PIN_13
#define LED_PIN		GPIO_PIN_5


  uint32_t	TargetTime		= FREQ_HIGH;
  uint32_t	ButtonCnt		= LIMIT_HIGH;
  uint32_t	ButtonCntUp		= 0;
  uint8_t	LastButtonState	= 1; // 초기 버튼 상태 (Released)


  while (1)
  {
	  uint32_t PinState;
	  if (GPIOC->IDR & GPIO_PIN_13)
	  {PinState = GPIO_PIN_SET;}
	  else
	  {PinState = GPIO_PIN_RESET;}

    if (LastButtonState == 1 && PinState == 0) // 버튼 눌림 감지
    {
    	ButtonCntUp++;
    	if (ButtonCntUp >= ButtonCnt) // 버튼 10회 이상 눌림
    	{
    		HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_RESET);
    		break; // 프로그램 종료
    	}
    	// LED 깜빡임 주기 변경
    	if (TargetTime == FREQ_HIGH)
    		TargetTime = FREQ_LOW;
    	else
    		TargetTime = FREQ_HIGH;
    }

    LastButtonState = PinState;


    if (gTimeDelay >= TargetTime)
    {
    	gTimeDelay = 0;
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
  }



//예제 2
//버튼을 누를 때 마다 led on / off 하는 코드
#define FREQ_HIGH	100
#define FREQ_LOW	500
#define LIMIT_LOW	3
#define LIMIT_HIGH	10
#define BUTTON_PIN	GPIO_PIN_13
#define LED_PIN		GPIO_PIN_5


  uint32_t TargetTime		= FREQ_HIGH;
  uint32_t ButtonCnt		= LIMIT_HIGH;
  uint32_t ButtonCntUp		= 0;
  uint8_t LastButtonState	= 1; // 초기 버튼 상태

  while(1)
  {
	  uint8_t CurrentButtonState = HAL_GPIO_ReadPin(GPIOC, BUTTON_PIN);
	  if(LastButtonState == 1 && CurrentButtonState == 0)
	  {
		  HAL_GPIO_TogglePin(GPIOA, LED_PIN);
	  }
	  LastButtonState = CurrentButtonState;
  }

#else
// 예제 3
// LED ON 상태에서 B1 버튼을 누르면 (3초 뒤에 타이머를 사용하여) 100ms 주기로 LED 깜빡이게 하는 예제

#define	LED_PIN		GPIO_PIN_5
#define	ButtonPIN	GPIO_PIN_13
#define	Delay_Time	3000
#define	Blink_FREQ	100

  uint32_t	TargetTime	= Delay_Time;
  uint8_t	LastState	= 1;
  uint8_t	LEDMode		= 0; // 0 : LED ON, 1 : LED Blink
  uint32_t	PressTime	= 0; // B1 버튼이 눌린 시각

  HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_SET); // 초기 LED ON 상태

  while(1)
  {
	  uint8_t CurrentState = HAL_GPIO_ReadPin(GPIOC, ButtonPIN);

	  if (LastState == 1 && CurrentState == 0)
	  {
		  PressTime = HAL_GetTick(); // B1 버튼이 눌린 시각 기록
	  }

	  // 3초 후 LED 모드 변경
	  if (PressTime != 0 && (HAL_GetTick()-PressTime >= Delay_Time))
	  {
		  LEDMode = !LEDMode; // LED 모드 변경
		  PressTime = 0; // 버튼 눌림 시각 초기화
	  }
	  LastState = CurrentState;

	  if (LEDMode == 0)
	  {
		  HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_SET); // LED ON
	  }
	  else
	  {
		  if(gTimeDelay >= Blink_FREQ)
		  {
			  gTimeDelay = 0;
			  HAL_GPIO_TogglePin(GPIOA, LED_PIN); // LED 토글 (깜빡임)
		  }
	  }
  }




#endif
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = 16
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Configure PLL ------------------------------------------------------*/
  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
  /* Enable HSI and activate PLL with HSi_DIV2 as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  oscinitstruct.HSEState        = RCC_HSE_OFF;
  oscinitstruct.LSEState        = RCC_LSE_OFF;
  oscinitstruct.HSIState        = RCC_HSI_ON;
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
