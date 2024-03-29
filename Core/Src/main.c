/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "xpt2046.h"
#include "stdio.h"

#include "display_ssd1963.h"
#include "math.h"



#include "008_Open_Sans_Bold.h"
#include "009_Open_Sans_Bold.h"
#include "010_Open_Sans_Bold.h"
#include "012_Open_Sans_Bold.h"
#include "014_Open_Sans_Bold.h"
#include "016_Open_Sans_Bold.h"
#include "018_Open_Sans_Bold.h"
#include "020_Open_Sans_Bold.h"
#include "022_Open_Sans_Bold.h"
#include "024_Open_Sans_Bold.h"
#include "026_Open_Sans_Bold.h"
#include "028_Open_Sans_Bold.h"
#include "036_Open_Sans_Bold.h"
#include "048_Open_Sans_Bold.h"
#include "072_Open_Sans_Bold.h"
#include "096_Open_Sans_Bold.h"
#include "112_Open_Sans_Bold.h"
#include "128_Open_Sans_Bold.h"


#define _Open_Sans_Bold_8      &Open_Sans_Bold_8
#define _Open_Sans_Bold_9      &Open_Sans_Bold_9
#define _Open_Sans_Bold_10     &Open_Sans_Bold_10
#define _Open_Sans_Bold_11     &Open_Sans_Bold_11
#define _Open_Sans_Bold_12      &Open_Sans_Bold_12
#define _Open_Sans_Bold_14      &Open_Sans_Bold_14
#define _Open_Sans_Bold_16      &Open_Sans_Bold_16
#define _Open_Sans_Bold_18      &Open_Sans_Bold_18
#define _Open_Sans_Bold_20      &Open_Sans_Bold_20
#define _Open_Sans_Bold_22      &Open_Sans_Bold_22
#define _Open_Sans_Bold_24      &Open_Sans_Bold_24
#define _Open_Sans_Bold_26      &Open_Sans_Bold_26
#define _Open_Sans_Bold_28      &Open_Sans_Bold_28
#define _Open_Sans_Bold_36      &Open_Sans_Bold_36
#define _Open_Sans_Bold_48      &Open_Sans_Bold_48
#define _Open_Sans_Bold_72      &Open_Sans_Bold_72
#define _Open_Sans_Bold_96      &Open_Sans_Bold_96
#define _Open_Sans_Bold_112      &Open_Sans_Bold_112
#define _Open_Sans_Bold_128      &Open_Sans_Bold_128

uint16_t touchX = 0, touchY = 0;


uint16_t x00=0, x11=0, y00=0, y11=0;

float sx = 0, sy = 1;

#define COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */
  Init_SSD1963();


  //  XPT2046_Init();
    TFT_Clear_Screen(RED);
    LCD_Font(120, 450, "SSD1963", _Open_Sans_Bold_128, 1, RED);
  	for(int i = 0; i<360; i+= 30) {

  	    sx = cos((i-90)*0.0174532925);
  	    sy = sin((i-90)*0.0174532925);
  	    x00 = sx*114+240;
  	    y00 = sy*114+160;
  	    x11 = sx*100+240;
  	    y11 = sy*100+160;

  	    TFT_Draw_Line(x00-1, y00-1, x11, y11,1,WHITE);
  	    if (i == 150) {
  	    	TFT_Draw_Line(x00, y00, x11, y11,1,BLACK);
  	    }
  	  }

  	LCD_Font(235, 254, "0", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(193, 240, "10", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(158, 210, "20", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(142, 165, "30", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(155, 120, "40", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(185, 91, "50", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(230, 76, "60", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(275, 91, "70", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(300, 120, "80", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(315, 165, "90", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(290, 215, "100", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(228, 210, "C", _Open_Sans_Bold_48, 1, WHITE);




  	for(int i = 0; i<360; i+= 30) {

  	    sx = cos((i-90)*0.0174532925);
  	    sy = sin((i-90)*0.0174532925);
  	    x00 = sx*114+540;  //240
  	    y00 = sy*114+160;
  	    x11 = sx*100+540;   //240
  	    y11 = sy*100+160;

  	    TFT_Draw_Line(x00-1, y00-1, x11, y11,1,WHITE);
  	    if (i == 150) {
  	    	TFT_Draw_Line(x00, y00, x11, y11,1,BLACK);
  	    }
  	  }

  	LCD_Font(535, 254, "0", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(493, 240, "10", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(458, 210, "20", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(442, 165, "30", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(455, 120, "40", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(485, 91, "50", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(530, 76, "60", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(575, 91, "70", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(600, 120, "80", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(615, 165, "90", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(590, 215, "100", _Open_Sans_Bold_18, 1, WHITE);
  	LCD_Font(528, 210, "C", _Open_Sans_Bold_48, 1, WHITE);
  //	touchx = getX();
  //	  	touchy = getY();
  //	  	sprintf(string,"x=%3d y=%3d",touchx,touchy);
  //
  //	  	ILI9341_WriteString(300, 0, string, Font_11x18, ILI9341_RED, ILI9341_WHITE);
    char string[30],string1[30];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    //void TFT_Draw_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint16_t color)
    //void TFT_Draw_Fill_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color)
    TFT_Draw_Fill_Rectangle (50, 300, 80, 80, BLUE);
    TFT_Draw_Round_Rect (700, 300, 80, 80, 10, 10, BLUE);
  while (1)
  {
	  //	  TFT_Clear_Screen(YELLOW);
	  	  //	  TFT_Clear_Screen(RED);
	  	  //	  TFT_Clear_Screen(GREEN);
	  	  //	  TFT_Clear_Screen(BLUE);
	  	  //	  TFT_Clear_Screen(RED);




	  	  					 	for(int j = 0; j<850; j+= 30) {
	  	  					 		ringMeter(j, 0, 1020, 100, 20, 140, RED2GREEN);
	  	  					 		sprintf(string, "%.1f", j/8.5);
	  	  					 		TFT_Draw_Fill_Rectangle(190,115, 100, 50,BLACK);
	  	  					 		  LCD_Font(190, 165, string, _Open_Sans_Bold_48, 1, WHITE);


	  	  						 		ringMeter(j, 0, 1020, 400, 20, 140, GREEN2RED);
	  	  						 		sprintf(string, "%.1f", j/8.5);
	  	  						 		TFT_Draw_Fill_Rectangle(490,115, 100, 50,BLACK);
	  	  						 		  LCD_Font(490, 165, string, _Open_Sans_Bold_48, 1, WHITE);
	  	  					 	  }


	  	  //	  LCD_Font(0, 200, string, _Open_Sans_Bold_26, 1, YELLOW);
	  	  //	  	touchX = getX();
	  	  //	  	  	touchY = getY();
	  	  //	  	  	sprintf(string,"x=%3d y=%3d",touchX,touchY);
	  	  //	  	  sprintf(string1,"x=%3d y=%3d",touchX,touchY);
	  	  ////	  TFT_Draw_String(0, 0, BLUE,GREEN, 1, string, 1);
	  	  //	  LCD_Font(0, 200, string, _Open_Sans_Bold_26, 1, BLUE);
	  	  	  //	  	ILI9341_WriteString(300, 0, string, Font_11x18, ILI9341_RED, ILI9341_WHITE);


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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
