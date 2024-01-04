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
#include "ESPDataLogger.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
#include<string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//*******************************************************************************************interruption automatique
uint8_t convCompleted=0;
 void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
     convCompleted=1;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/*#define SSID "laptopwiss"
#define PASSWORD "wissemA1"
#define API_KEY "KCQZI6FEOB3LUVD3"

void ESP8266_Init(void);
void ESP8266_SendData(const char *data);

void ESP8266_Init(void) {
  char buffer[100];

  // Send AT commands for ESP8266 initialization
  HAL_UART_Transmit(&huart2, (uint8_t *)"AT\r\n", 4, HAL_MAX_DELAY);
  HAL_Delay(1000);

   // Uart_flush();
  	//Uart_sendstring("AT+CWMODE=1\r\n");
  	//while (!(Wait_for("OK\r\n")));

  sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
  HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
  HAL_Delay(2000);
}
void ESP8266_SendData(const char *data) {
  char buffer[100];

  // Establish TCP connection with ThingSpeak
  sprintf(buffer, "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
  HAL_Delay(2000);
  // Send data
  sprintf(buffer, "AT+CIPSEND=%d\r\n", strlen(data) + 2);
  HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
  HAL_Delay(1000);
HAL_UART_Transmit(&huart2, (uint8_t *)data, strlen(data), HAL_MAX_DELAY);
  HAL_Delay(1000);

  // Close the TCP connection
  HAL_UART_Transmit(&huart2, (uint8_t *)"AT+CIPCLOSE\r\n", 12, HAL_MAX_DELAY);
  HAL_Delay(1000);
} */


/* USER CODE BEGIN PV */
// Configuration WiFi de l'ESP8266 (à adapter)

// Buffer pour stocker les données à envoyer à l'ESP8266
char buffer3[50];
uint16_t readValue=0;
uint16_t readValue2=0;
uint16_t rawValues[2];
char msg[20];

//UART_HandleTypeDef huart2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Timer interrupt callback function
//void HAL_SYSTICK_Callback(void) {
 //   millis++;
//}
/* USER CODE END 0 */
/**
  * @brief  The application entry point.
  * @retval int
  */
uint8_t count = 0;
uint16_t Value_Buf [4];


void sendATCommand(const char* command) {
    HAL_UART_Transmit(&huart2, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
}
void configureWiFi(const char* ssid, const char* password) {
    char command[50];
    sprintf(command, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    sendATCommand(command);
}

void sendDataToThingSpeak(const char* apiKey, const char* data) {
    char httpPost[100];
    sprintf(httpPost, "GET /update?api_key=%s&field1=%s\r\n", apiKey, data);
    sendATCommand("AT+CIPSEND=0,"); // Open a TCP connection
    HAL_Delay(1000);
    sendATCommand(httpPost); // Send data
}

// Function to send data to ThingSpeak
int main(void)
{
  /* USER CODE BEGIN 1 */


	// Start the system tick timer with 1 ms period
	   // if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK) {
	    //    Error_Handler();
	   // }

  /* USER CODE END 1 */
	   // Assuming val1 is declared somewhere in your code
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HD44780_Init(2);
  HD44780_Clear();

   HAL_ADC_Start_DMA(&hadc1,(uint32_t *) rawValues, 2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    //Configuration de la communication avec l'ESP8266
  //  sprintf(buffer3, "AT+CWJAP=\"%s\",\"%s\"\r\n", "laptopwiss", "wissemA12");
  //  HAL_UART_Transmit(&huart2, (uint8_t *)buffer3, strlen(buffer3), HAL_MAX_DELAY);

    //MX_USART2_UART_Init();
   // ESP8266_Init();
// ESP_Init("laptopwiss","wissemA1");

  // ESP8266_Init();

    char ssid[] = "laptopwiss";
    char password[] = "wissemA12";
    configureWiFi(ssid, password); // Connect to WiFi

    char apiKey[] = "R7WDHYB22J733QUZ";
    char sensorData[] = "123"; // Replace with your actual sensor data

  //  ESP_Init("laptopwiss", "wissemA1");
    while (1)
      {
    /*	Value_Buf[0] = readValue;
    	Value_Buf[1] = readValue2;
    	Value_Buf[2] = count;
    	Value_Buf[3] = count*2;

    	  count++;
    	 ESP_Send_Multi("R7WDHYB22J733QUZ", 4, Value_Buf);

    	   /* float temperature = 25.5;
    	    char dataBuffer[50];
    	    sprintf(dataBuffer, "GET /update?api_key=%s&field1=%d\r\n", API_KEY, temperature);
    	    ESP8266_SendData(dataBuffer);
    	    HAL_Delay(10000); */

    	sendDataToThingSpeak(apiKey, sensorData);



    	if (convCompleted) {

    	readValue =(uint16_t) rawValues[0];
    	readValue2 =(uint16_t) rawValues[1];
/**********************************************************************************************************************************************/
    	 // Debug print for ADC values
    	     /*   printf("ADC1 Value: %d\r\n", readValue);

    	        // Debug print for ESP8266 communication
    	        char buffer[50];
    	        sprintf(buffer, "AT+CIPSEND=%d\r\n", strlen("Test Data"));
    	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

    	        HAL_UART_Transmit(&huart2, (uint8_t *)"Test Data", strlen("Test Data"), HAL_MAX_DELAY);  */
/***************************************************************************************************************************************************/

    	        // Print data for debugging
    	       /* printf("Data to send: %d, %d\r\n", readValue, readValue2);

    	        // Send data to ThingSpeak
    	        char dataBuffer[100];
    	        sprintf(dataBuffer, "GET /update?api_key=YOUR_API_KEY&field1=%d&field2=%d\r\n", readValue, readValue2);

    	        printf("Sending data: %s\r\n", dataBuffer);

    	        HAL_UART_Transmit(&huart2, (uint8_t *)dataBuffer, strlen(dataBuffer), HAL_MAX_DELAY);

    	        // Wait for a response (you may need to adjust the buffer size)
    	        char responseBuffer[100];
    	        HAL_UART_Receive(&huart2, (uint8_t *)responseBuffer, sizeof(responseBuffer) - 1, HAL_MAX_DELAY);
    	        responseBuffer[sizeof(responseBuffer) - 1] = '\0'; // Null-terminate the string  */


/************************************************************************************************************************************/
    	// Send data to ThingSpeak
    	// Simplified dataBuffer for ThingSpeak
    	   /*     char dataBuffer[100];
    	        sprintf(dataBuffer, "GET /update?api_key=R7WDHYB22J733QUZ&field1=%d\r\n", readValue);

    	        // Send the HTTP request to ThingSpeak
    	        HAL_UART_Transmit(&huart2, (uint8_t *)dataBuffer, strlen(dataBuffer), HAL_MAX_DELAY);

    	        // Wait for a response (you may need to adjust the buffer size)
    	        char responseBuffer[100];
    	        HAL_UART_Receive(&huart2, (uint8_t *)responseBuffer, sizeof(responseBuffer) - 1, HAL_MAX_DELAY);
    	        responseBuffer[sizeof(responseBuffer) - 1] = '\0'; // Null-terminate the string


    	             // Print the response
    	             printf("ThingSpeak Response: %s\r\n", responseBuffer);*/
/*******************************************************************************************************************************/
    	  HD44780_Clear();
    	    		    HD44780_SetCursor(0, 0);
    	    		    HD44780_PrintStr("Temp:");
    	    		    HD44780_SetCursor(6, 0);
    	    		    // Convert ADC value to string and then print it
    	    		    sprintf(msg, "%d", rawValues[0]);
    	    		    HD44780_PrintStr(msg);

    	    		      HD44780_SetCursor(0, 1);
    	    		      HD44780_PrintStr("Cons:");
    	    		      HD44780_SetCursor(6, 1);
    	    		     // Convert ADC value to string and then print it
    	    		      sprintf(msg, "%d", rawValues[1]);
    	    		      HD44780_PrintStr(msg);

    	if (readValue > 2000) {
    		  /*  HD44780_Clear();
    		    HD44780_SetCursor(0, 0);
    		    HD44780_PrintStr("Temp:");
    		    HD44780_SetCursor(6, 0);
    		    // Convert ADC value to string and then print it
    		    sprintf(msg, "%d", rawValues[0]);
    		    HD44780_PrintStr(msg);   */
    		    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    		    // Send temperature value over UART
    		      //sprintf(buffer3, "Temperature: %d\r\n", rawValues[0]);
    		      //HAL_UART_Transmit(&huart2, (uint8_t *)buffer3, strlen(buffer3), HAL_MAX_DELAY);
    	    	    		  }

    	    	    	    if ( readValue2 > 3000 ){
    	    	    	    	/* HD44780_SetCursor(0, 1);
    	    	    	    	    HD44780_PrintStr("Cons:");
    	    	    	    	    HD44780_SetCursor(6, 1);
    	    	    	    	    // Convert ADC value to string and then print it
    	    	    	    	    sprintf(msg, "%d", rawValues[1]);
    	    	    	    	    HD44780_PrintStr(msg);  */
    	    	    	    	   // HAL_Delay(2000);
    	    	    	    	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    	    	    	    	    // Send consumption value over UART
    	    	    	    	    //sprintf(buffer3, "Consumption: %d\r\n", rawValues[1]);
    	    	    	    	  //  HAL_UART_Transmit(&huart2, (uint8_t *)buffer3, strlen(buffer3), HAL_MAX_DELAY);
    	    	              }

    	    	    	    convCompleted = 0;
    	 printf("ADC1 Value: %d, ADC2 Value: %d\r\n", readValue, readValue2);
    	//while(!convCompleted);
    	 }

    	//for(uint8_t i=0; i<hadc1.Init.NbrOfConversion; i++){

    	//	readValue =(uint16_t) rawValues[0];
    	//	readValue2 =(uint16_t) rawValues[1];
    	//}

    	  // Add appropriate delay to control the loop speed
          HAL_Delay(50); // Adjust the delay as needed
      }
  /* USER CODE END 3 */
}

//void Delay(count){

    //	while(count--);

 //   }

/**
  * @brief System Clock Configuration
  * @retval None
  */
//********************************************************************************************interruption manuelle avec les button
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_4) // Check if the interrupt is from Button 1 (Assuming GPIO_PIN_4 is Button 1)
    {
        // Handle Button 1 interrupt
    	 HD44780_Clear();
    	 HD44780_SetCursor(0, 0);
    	 HD44780_PrintStr("Ventillation actif");
         HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
         HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
    }
    else if (GPIO_Pin == GPIO_PIN_5) // Replace /* Pin for Button 2 */ with the actual pin for Button 2
    {
    	        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    }
    // Add more else if statements for additional buttons if needed
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();//*********************************************configuration de regulation du tention interne
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);//******************kfifkif


  //********************************************************************initialisation de oscilateur RCC
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
//***************************************************jusqu'au ici
  /** Initializes the CPU, AHB and APB buses clocks ==>initialisation de clock CPU, AHB"Advanced High-performance Bus", APB"Advanced Peripheral Bus"
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
   * configuration global de ADC : convertisseur analogique numerique
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
   * configuration pour l'ADC
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}


/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD11 PD12 PD13 PD14
                           PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
