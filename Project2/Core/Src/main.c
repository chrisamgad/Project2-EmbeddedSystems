/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void resetSensor(void)
{
 
  hspi1.Init.CLKPolarity       = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase          = SPI_PHASE_1EDGE;
  hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;
  HAL_SPI_Init(&hspi1);

  // Reset MS5540C Sensor
  uint32_t resetBuffer[2] = {0x0015, 0x5540};
  HAL_SPI_Transmit(&hspi1, (uint8_t *) resetBuffer, 2, 5000);

  // Set TI mode 
  hspi1.Init.TIMode= SPI_TIMODE_ENABLE;
  HAL_SPI_Init(&hspi1);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,29);
	
	int counter=0;
	double PressureInitial;
	double PressureDiff;
	double CurrentDepth;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	

	uint16_t txBuffer;
  uint16_t rxBuffer;

	//Note: The MS5540C device does not have a CS signal. Instead there is  a START sequence (3-bit high) before each SETUP sequence and a STOP sequence (3-bit low) after each SETUP sequence.
   

  resetSensor();

  //2- Read calibration data (factory calibrated) from PROM of MS5540C 
  uint16_t word1, word2, word3, word4;
  /* Get Calibration word 1 */
  txBuffer = 0x1D50;
  rxBuffer = 0;
  HAL_SPI_Transmit(&hspi1, (uint8_t *) &txBuffer, 1, 5000);
  txBuffer = 0;
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t *) &txBuffer, (uint8_t *) &rxBuffer, 1, 5000);
  word1 = rxBuffer;

  resetSensor();

  /* Get Calibration word 2 */
  txBuffer = 0x1D60;
  rxBuffer = 0;
  HAL_SPI_Transmit(&hspi1, (uint8_t *) &txBuffer, 1, 5000);
  txBuffer = 0;
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t *) &txBuffer, (uint8_t *) &rxBuffer, 1, 5000);
  word2 = rxBuffer;

  resetSensor();


  //Get Calibration word 3 
  txBuffer = 0x1D90;
  rxBuffer = 0;
  HAL_SPI_Transmit(&hspi1, (uint8_t *) &txBuffer, 1, 5000);
  txBuffer = 0;
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t *) &txBuffer, (uint8_t *) &rxBuffer, 1, 5000);
  word3 = rxBuffer;

  resetSensor();

  //Get Calibration word 4 
  txBuffer = 0x1DA0;
  rxBuffer = 0;
  HAL_SPI_Transmit(&hspi1, (uint8_t *) &txBuffer, 1, 5000);
  txBuffer = 0;
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t *) &txBuffer, (uint8_t *) &rxBuffer, 1, 5000);
  word4 = rxBuffer;

	//Step 3
  //Convert calibration data into coefficients 
  uint16_t c1 = (word1 >> 1) & 0x7FFF; // Pressure sensitivity
  uint16_t c2 = ((word3 & 0x003F) << 6) | (word4 & 0x003F); // Pressure offset
  uint16_t c3 = (word4 >> 6) & 0x03FF;
  uint16_t c4 = (word3 >> 6) & 0x03FF;
  uint16_t c5 = ((word1 & 0x0001) << 10) | ((word2 >> 6) & 0x03FF);
  uint16_t c6 = word2 & 0x003F;

  resetSensor();
  hspi1.Init.CLKPhase          = SPI_PHASE_1EDGE;
  hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;
  HAL_SPI_Init(&hspi1);

  /*##-4- Read digital pressure value from MS5540C ###########################*/
  // TODO: Send reset (it is recommended to send a reset before each conversion)
  txBuffer = 0x0F40;
  rxBuffer = 0;
  HAL_SPI_Transmit(&hspi1, (uint8_t *) &txBuffer, 1, 5000);
  HAL_Delay(36); // wait for end of conversion (can be an interrupt on MISO)
  txBuffer = 0;
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t *) &txBuffer, (uint8_t *) &rxBuffer, 1, 5000);
  uint16_t d1 = (rxBuffer << 1) & 0xFFFF;

  resetSensor();
  hspi1.Init.CLKPhase          = SPI_PHASE_1EDGE;
  hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;
  HAL_SPI_Init(&hspi1);


  // Step 5
	//	Read digital temperature value from MS5540C 
  txBuffer = 0x0F20;
  rxBuffer = 0;
  HAL_SPI_Transmit(&hspi1, (uint8_t *) &txBuffer, 1, 5000);
  HAL_Delay(36); // wait for end of conversion (can be an interrupt on MISO)
  txBuffer = 0;
  HAL_SPI_TransmitReceive(&hspi1, (uint8_t *) &txBuffer, (uint8_t *) &rxBuffer, 1, 5000);
  // uint16_t d2 = rxBuffer;
  uint16_t d2 = (rxBuffer << 1) & 0xFFFF;

  /* Calculate calibration temperature */
  int32_t ut1 = 8 * c5 + 20224;

  /* Calculate actual temperature */
  int32_t dT = d2 - ut1;
  double temperature = (200 + ((dT * (c6 + 50)) >> 10)) / 10.0;

  /* Calculate pressure offset at actual temperature */
  int32_t offset = (c2 * 4) + (((c4 - 512) * dT) >> 12);
  /* Calculate pressure sensitivity at actual temperature */
  int32_t sensitivity = c1 + ((c3 * dT) >> 10) + 24576;
  int32_t x = (sensitivity * (d1 - 7168) >> 14) - offset;
  /* Calibration temperature compensated pressure */
  double pressure = (((x * 10) >> 5) + 2500) / 10.0;

	//For stability
	if(counter==0)
	{	
		PressureInitial=pressure;
		
	}
	if(counter==1)
	{	
		double ErrorPressureInitial=PressureInitial-pressure;
		if(abs(ErrorPressureInitial)>1) //if differance between first and second pressure readings were not very big 
			counter=0; //reset counter to 0 and don't start calculating the water depth until a valid inital pressure value is taken
		else
			{
				PressureInitial=pressure; //if valid initial pressure value(referance pressure) is taken 
				counter++;// increment counter
			}
	}
	else
		counter++;
	
	
	if(counter>=2)
	{
	PressureDiff=abs(pressure-PressureInitial)*100; //convertion into pascal
	CurrentDepth=PressureDiff/(1000*9.81); //Current Depth in Metres
	CurrentDepth=CurrentDepth*100; //To CM


	//For Debugging purposes
	/*uint8_t out[10];
	sprintf((char  *)out,"%f",pressure);
	HAL_UART_Transmit(&huart2, "pressure is now ",sizeof("pressure is now "),200);
	HAL_UART_Transmit(&huart2, out,sizeof(out),200);
	HAL_UART_Transmit(&huart2, "\n",sizeof("\n"),200);
	HAL_UART_Transmit(&huart2, "\r",sizeof("\r"),200);
	*/
		
	uint8_t out2[10];
	int depth=(int)CurrentDepth;//for removing decimal places from CurrentDepth
	sprintf((char  *)out2,"%d",depth);

	HAL_UART_Transmit(&huart2, out2,sizeof(out2),200); //transmit the depth to teraterm
	HAL_UART_Transmit(&huart2, "\r",sizeof("\r"),200);
	HAL_UART_Transmit(&huart2, "\n",sizeof("\n"),200);


	if(depth<=2) //if depth was below 2 cm
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); //Turn on alarm
	else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);//Turn off alarm
	}
  
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_7;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 3;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 60;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
