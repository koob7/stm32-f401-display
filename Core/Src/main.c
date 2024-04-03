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
    TFT_Clear_Screen(0xCFFF);
    TFT_Draw_Fill_Rectangle(100,0, 600, 144, 0xD61F);//niebieska ramka
    TFT_Draw_Fill_Rectangle(0,0, 20, 20, 0x8C51);//szare prostokąty z prawej i lewej
    TFT_Draw_Fill_Rectangle(0,460, 20, 20, 0x8C51);
    TFT_Draw_Fill_Rectangle(780,0, 20, 20, 0x8C51);
    TFT_Draw_Fill_Rectangle(780,460, 20, 20, 0x8C51);
    TFT_Draw_Fill_Round_Rect (0, 0, 120, 480, 20, 0x8C51);
    TFT_Draw_Fill_Round_Rect (680, 0, 120, 480, 20, 0x8C51);
    uint16_t pos_y = 9;
    for(uint8_t i = 0; i<7;i+=1)//przyciski po prawej
    {
    TFT_Draw_Fill_Round_Rect (696, pos_y, 88, 47, 10,  0xD6BA);
    TFT_Draw_Fill_Rectangle(740,pos_y, 2, 47, 0x0000);
    LCD_centered_Font(696, pos_y+24, 88, "+   -", _Open_Sans_Bold_48, 1, 0x4A69);
    pos_y+=56;
    }

    TFT_Draw_Fill_Round_Rect (696, 413, 88, 47, 10,  0xD6BA);
    TFT_Draw_Fill_Rectangle(740, 413, 2, 47, 0x0000);
    LCD_centered_Font(696, 413+24, 88, "+   -", _Open_Sans_Bold_48, 1, 0x4A69);

    LCD_centered_Font(696, 9+25, 88, "X", _Open_Sans_Bold_48, 1, 0x7D3D);//literki po prawej
    LCD_centered_Font(696, 65+25, 88, "Y", _Open_Sans_Bold_48, 1, 0x7D3D);
    LCD_centered_Font(696, 121+25, 88, "Z", _Open_Sans_Bold_48, 1, 0x7D3D);
    LCD_centered_Font(696, 177+25, 88, "A", _Open_Sans_Bold_48, 1, 0x7D3D);
    LCD_centered_Font(696, 233+25, 88, "B", _Open_Sans_Bold_48, 1, 0x7D3D);
    LCD_centered_Font(696, 289+25, 88, "C", _Open_Sans_Bold_48, 1, 0x7D3D);


  //	touchx = getX();
  //	  	touchy = getY();
  //	  	sprintf(string,"x=%3d y=%3d",touchx,touchy);
  //
  //	  	ILI9341_WriteString(300, 0, string, Font_11x18, ILI9341_RED, ILI9341_WHITE);
    char string[30],string1[30];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    /*TFT_Draw_Fill_Rectangle (300, 300, 80, 80, BLUE);
    TFT_Draw_Fill_Rectangle (50, 300, 80, 80, BLUE);
    LCD_Font(50, 300, "hej", _Open_Sans_Bold_10, 1, WHITE);
    TFT_Draw_Fill_Round_Rect (700, 300, 80, 80, 10,  BLUE);
    LCD_Font(700, 350, "nArA", _Open_Sans_Bold_10, 2, WHITE);
    TFT_Draw_Circle(300, 340, 40, 1, 10, WHITE);*/

    int allertX = 220;	//MAX size is 220x200 - with bigger tabs malloc has problem
    int allertY = 200;
    uint16_t *save = (uint16_t *)malloc(allertX* allertY * sizeof(uint16_t));

  while (1)
  {





	  	  					 	for(int j = 0; j<850; j+= 30) {
	  	  					 		ringMeter(j, 0, 1020, 100, 20, 140, RED2GREEN);
	  	  					 		sprintf(string, "%.1f", j/8.5);
	  	  					 		TFT_Draw_Fill_Rectangle(190,115, 100, 50,BLACK);
	  	  					 		  LCD_Font(190, 165, string, _Open_Sans_Bold_48, 1, WHITE);


/*	  	  						 		ringMeter(j, 0, 1020, 400, 20, 140, GREEN2RED);
	  	  						 		sprintf(string, "%.1f", j/8.5);
	  	  						 		TFT_Draw_Fill_Rectangle(490,115, 100, 50,BLACK);
	  	  						 		  LCD_Font(490, 165, string, _Open_Sans_Bold_48, 1, WHITE);*/
	  	  					 	  }

	  	  					TFT_Draw_Alert (allertX, allertY, "to jest przykladowy alert do celow demonstracyjnych i testowych",  save, _Open_Sans_Bold_20);
	  	  					HAL_Delay(3000);
	  	  					TFT_Restore_Area(allertX, allertY, save);



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
