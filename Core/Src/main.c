/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

#include "lcdDisplay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
lcd_t Lcd1, Lcd2;

uint8_t arrow1[8] = { 0x00, 0x04, 0x06, 0x1F, 0x1F, 0x06, 0x04, 0x00 };
// 0 0 0 0 0 0 0 0
// 0 0 0 0 0 1 0 0
// 0 0 0 0 0 1 1 0
// 0 0 0 1 1 1 1 1
// 0 0 0 1 1 1 1 1
// 0 0 0 0 0 1 1 0
// 0 0 0 0 0 1 0 0
// 0 0 0 0 0 0 0 0

uint8_t arrow2[8] = { 0x00, 0x04, 0x0C, 0x1F, 0x1F, 0x0C, 0x04, 0x00 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void __lcd1_init(){
	Lcd1.columns = 16;
	Lcd1.rows = 2;
	Lcd1.font = LCD_FONT_5X8;
	Lcd1.interface = LCD_INTERFACE_4BIT;
	Lcd1.backlightGpio.GPIO = (uint32_t)LCD1_BL_GPIO_Port;
	Lcd1.backlightGpio.pin = LCD1_BL_Pin;

	Lcd1.gpios[LCD_RS].GPIO = (uint32_t)LCD1_RS_GPIO_Port;
	Lcd1.gpios[LCD_RS].pin = LCD1_RS_Pin;
	Lcd1.gpios[LCD_E].GPIO = (uint32_t)LCD1_E_GPIO_Port;
	Lcd1.gpios[LCD_E].pin = LCD1_E_Pin;
	Lcd1.gpios[LCD_D4].GPIO = (uint32_t)LCD1_D4_GPIO_Port;
	Lcd1.gpios[LCD_D4].pin = LCD1_D4_Pin;
	Lcd1.gpios[LCD_D5].GPIO = (uint32_t)LCD1_D5_GPIO_Port;
	Lcd1.gpios[LCD_D5].pin = LCD1_D5_Pin;
	Lcd1.gpios[LCD_D6].GPIO = (uint32_t)LCD1_D6_GPIO_Port;
	Lcd1.gpios[LCD_D6].pin = LCD1_D6_Pin;
	Lcd1.gpios[LCD_D7].GPIO = (uint32_t)LCD1_D7_GPIO_Port;
	Lcd1.gpios[LCD_D7].pin = LCD1_D7_Pin;

	lcd_init(&Lcd1);
	lcd_backlight_set(&Lcd1, LCD_BACKLIGHT_ON);
}

void __lcd2_init(){
	int i;

	Lcd2.columns = 16;
	Lcd2.rows = 2;
	Lcd2.font = LCD_FONT_5X8;
	Lcd2.interface = LCD_INTERFACE_4BIT;
	Lcd2.backlightGpio.GPIO = (uint32_t)LCD1_BL_GPIO_Port;
	Lcd2.backlightGpio.pin = LCD1_BL_Pin;
	Lcd2.backlightPwm.Channel = TIM_CHANNEL_1;
	Lcd2.backlightPwm.Peripheral = (uint32_t)&htim4;

	Lcd2.gpios[LCD_RS].GPIO = (uint32_t)LCD2_RS_GPIO_Port;
	Lcd2.gpios[LCD_RS].pin = LCD2_RS_Pin;
	Lcd2.gpios[LCD_E].GPIO = (uint32_t)LCD2_E_GPIO_Port;
	Lcd2.gpios[LCD_E].pin = LCD2_E_Pin;
	Lcd2.gpios[LCD_D4].GPIO = (uint32_t)LCD2_D4_GPIO_Port;
	Lcd2.gpios[LCD_D4].pin = LCD2_D4_Pin;
	Lcd2.gpios[LCD_D5].GPIO = (uint32_t)LCD2_D5_GPIO_Port;
	Lcd2.gpios[LCD_D5].pin = LCD2_D5_Pin;
	Lcd2.gpios[LCD_D6].GPIO = (uint32_t)LCD2_D6_GPIO_Port;
	Lcd2.gpios[LCD_D6].pin = LCD2_D6_Pin;
	Lcd2.gpios[LCD_D7].GPIO = (uint32_t)LCD2_D7_GPIO_Port;
	Lcd2.gpios[LCD_D7].pin = LCD2_D7_Pin;

	lcd_init(&Lcd2);
	for (i=0 ; i<100 ; i++){
		lcd_backlight_set_bright(&Lcd2, i);
		HAL_Delay(10);
	}
}

void __lcd1_creat_custom_char(){
	lcd_create_custom_char(&Lcd1, LCD_CUSTOM_1, arrow1);
	lcd_create_custom_char(&Lcd1, LCD_CUSTOM_2, arrow1);
}

void __lcd2_creat_custom_char(){
	lcd_create_custom_char(&Lcd2, LCD_CUSTOM_1, arrow2);
	lcd_create_custom_char(&Lcd2, LCD_CUSTOM_2, arrow2);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char Text[17];
	int Cnt;
	float CntFl;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  HAL_Delay(250);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

  __lcd1_init();
  __lcd2_init();

  __lcd1_creat_custom_char();
  __lcd2_creat_custom_char();

  lcd_send_char_pos(&Lcd1, LCD_CUSTOM_1, 0, 0);
  lcd_send_string_pos(&Lcd1, "Hello Lcd1", 0, 1);
  lcd_send_char(&Lcd1, LCD_CUSTOM_2);

  lcd_send_char_pos(&Lcd2, LCD_CUSTOM_1, 0, 0);
  lcd_send_string_pos(&Lcd2, "Hello Lcd2", 0, 1);
  lcd_send_char(&Lcd2, LCD_CUSTOM_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Cnt = 0;
  CntFl = 0.0f;
  while (1)
  {
	  sprintf(Text, "Contador: %d", Cnt);
	  lcd_send_string_pos(&Lcd1, Text, 1, 0);

	  sprintf(Text, "Contador: %.2f", CntFl);
	  lcd_send_string_pos(&Lcd2, Text, 1, 0);

	  Cnt++;
	  CntFl += 0.5f;
	  HAL_Delay(500);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1499;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 100;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD1_D7_Pin|LCD1_D6_Pin|LCD1_D5_Pin|LCD1_D4_Pin
                          |LCD1_E_Pin|LCD1_RS_Pin|LCD2_D4_Pin|LCD2_D5_Pin
                          |LCD2_D6_Pin|LCD2_D7_Pin|LCD2_RS_Pin|LCD2_E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD1_BL_GPIO_Port, LCD1_BL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LCD1_D7_Pin LCD1_D6_Pin LCD1_D5_Pin LCD1_D4_Pin
                           LCD1_E_Pin LCD1_RS_Pin LCD2_D4_Pin LCD2_D5_Pin
                           LCD2_D6_Pin LCD2_D7_Pin LCD2_RS_Pin LCD2_E_Pin */
  GPIO_InitStruct.Pin = LCD1_D7_Pin|LCD1_D6_Pin|LCD1_D5_Pin|LCD1_D4_Pin
                          |LCD1_E_Pin|LCD1_RS_Pin|LCD2_D4_Pin|LCD2_D5_Pin
                          |LCD2_D6_Pin|LCD2_D7_Pin|LCD2_RS_Pin|LCD2_E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD1_BL_Pin */
  GPIO_InitStruct.Pin = LCD1_BL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD1_BL_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
