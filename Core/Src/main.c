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
#include "spi.h"
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
#include "bitmap_arrays.h"


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
uint8_t was_touched=0;

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
	//NVIC_DisableIRQ(EXTI15_10_IRQn);
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
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
  Init_SSD1963();
  NVIC_DisableIRQ(EXTI15_10_IRQn);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);

  uint16_t pos_y;
    TFT_Clear_Screen(0xCFFF);
    TFT_Draw_Fill_Rectangle(100,0, 600, 144, 0xD61F);//niebieska ramka




	TFT_Draw_Fill_Rectangle(780,0, 20, 20, 0x8C51);//szary prostokąt z prawej
	TFT_Draw_Fill_Rectangle(780,460, 20, 20, 0x8C51);
	TFT_Draw_Fill_Round_Rect (680, 0, 120, 480, 20, 0x8C51);
	pos_y = 9;
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
	LCD_FillTriangle(732, 417,732, 417+38, 732+24, 417+19, 0x7D3D);
	TFT_Draw_Bitmap_Without_Background(721, 353, hand_icon_x, hand_icon_y, hand_icon);




    TFT_Draw_Fill_Rectangle(0,0, 20, 20, 0x8C51);//szary prostokąt z lewej
    TFT_Draw_Fill_Rectangle(0,460, 20, 20, 0x8C51);
    TFT_Draw_Fill_Round_Rect (0, 0, 120, 480, 20, 0x8C51);
    pos_y = 33;
    for(uint8_t i = 0; i<8;i+=1)//przyciski po lewej
    {
        TFT_Draw_Fill_Round_Rect (16, pos_y, 88, 47, 10,  0xD6BA);
        pos_y+=56;
    }
    LCD_centered_Font(0, 0+16, 120, "JOB NAME", _Open_Sans_Bold_14, 1, BLACK);
	LCD_centered_Font(16, 33+24, 88, "OPEN", _Open_Sans_Bold_14, 1, 0x7D3D);//literki po lewej
	LCD_centered_Font(16, 89+24, 88, "CONT. JOB", _Open_Sans_Bold_14, 1, 0x7D3D);
	LCD_centered_Font(16, 145+24, 88, "MANUAL", _Open_Sans_Bold_14, 1, 0x7D3D);
	LCD_centered_Font(16, 201+14, 88, "ENABLE\nTOOL", _Open_Sans_Bold_14, 1, 0x7D3D);
	LCD_centered_Font(16, 257+24, 88, "RUN JOB", _Open_Sans_Bold_14, 1, 0x7D3D);
	LCD_centered_Font(16, 313+14, 88, "AXIS\nCONTROL", _Open_Sans_Bold_14, 1, 0x7D3D);
	LCD_centered_Font(16, 369+14, 88, "CONT.\nMOVEMENT", _Open_Sans_Bold_14, 1, 0x7D3D);
	LCD_centered_Font(16, 425+24, 88, "SETTINGS", _Open_Sans_Bold_14, 1, 0x7D3D);




	TFT_Draw_Fill_Round_Rect (132, 9, 70, 41, 20,  0xD6BA);//przyciski na gorze
	TFT_Draw_Fill_Round_Rect (212, 9, 70, 41, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (291, 9, 70, 41, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (371, 9, 81, 41, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (462, 9, 72, 41, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (544, 9, 72, 41, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (628, 15, 40, 40, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (628, 88, 40, 40, 20,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (211, 68, 61, 21, 10,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (211, 109, 61, 21, 10,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (362, 68, 61, 21, 10,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (362, 109, 61, 21, 10,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (532, 68, 61, 21, 10,  0xD6BA);
	TFT_Draw_Fill_Round_Rect (532, 109, 61, 21, 10,  0xD6BA);
    LCD_centered_Font(132, 9+22, 70, "SELECT", _Open_Sans_Bold_14, 1, BLACK);//opisy przyciskow
    LCD_centered_Font(212, 9+22, 70, "NEW P.", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(291, 9+22, 70, "EDIT P.", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(371, 9+22,  "DELETE P.", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(462, 9+22, 70, "SET T.P.", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(544, 9+22, 70, "SET H.P", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(155, 67+11, "Name:", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(155, 109+11, "Tool:", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(295, 67+11, "Move:", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(295, 109+11, "Speed:", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(446, 67+11, "Type:", _Open_Sans_Bold_14, 1, BLACK);
    LCD_Font(446, 109+11, "at Target:", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(211, 68+11, 61, "P11", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(211, 109+11, 41, "OFF", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(362, 68+11, 41, "Circ", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(362, 109+11, 41, "100%", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(532, 68+11, 41, "Cont", _Open_Sans_Bold_14, 1, BLACK);
    LCD_centered_Font(532, 109+11, 61, "YES", _Open_Sans_Bold_14, 1, BLACK);
	LCD_FillTriangle(636, 42,636+23, 42, 647, 22, 0x00FD);
	LCD_FillTriangle(636, 42+59,636+23, 42+59, 647, 22+40+59, 0x00FD);
	LCD_FillTriangle(574, 74,573+13, 74, 580, 74+11, 0x00FD);
	//LCD_FillTriangle(574, 74+41,573+13, 74+41, 580, 74+11+41, 0x00FD);
	LCD_FillTriangle(574-170, 74,573+13-170, 74, 580-170, 74+11, 0x00FD);
	LCD_FillTriangle(574-170, 74+41,573+13-170, 74+41, 580-170, 74+11+41, 0x00FD);
	LCD_FillTriangle(574-322, 74+41,573+13-322, 74+41, 580-322, 74+11+41, 0x00FD);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


    int allertX = 220;	//MAX size is 220x200 - with bigger tabs malloc has problem
    int allertY = 200;
    uint16_t *save = (uint16_t *)malloc(allertX* allertY * sizeof(uint16_t));
    XPT2046_Init();
	__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin);//czyszczenie zgłoszonego przerwania
	NVIC_EnableIRQ(EXTI15_10_IRQn);


  while (1)
  {
	  if(was_touched==1){
		  was_touched=0;
		NVIC_DisableIRQ(EXTI15_10_IRQn);
		uint16_t touchx, touchy;
		char buffer1[10]=""; // Bufor na konwertowaną wartość
		char buffer2[10]=""; // Bufor na konwertowaną wartość
		TFT_Draw_Fill_Round_Rect (280, 180, 200, 60, 10,  0xCFFF);
		touchx = getX();
		sprintf(buffer1, "X%d", touchx); // Konwersja wartości do ciągu znaków
		touchy = getY();
		sprintf(buffer2, "Y%d", touchy); // Konwersja wartości do ciągu znaków

		LCD_Font(300, 200,  buffer1, _Open_Sans_Bold_28, 1, BLACK);
		LCD_Font(300, 220,  buffer2, _Open_Sans_Bold_28, 1, BLACK);
		HAL_Delay(100);

//		for (int i =0; i<10;i+=1)
//		{
//			asm("nop");
//		}
		XPT2046_Init();


		if(touchx >=696 && touchx<=696+88 && touchy>=9 && touchy<=9+47)// 696, pos_y, 88, 47,
			 		  		{
			  	  	  	  	  	  	uint16_t counter = TFT_Draw_List(400, 200, 100, "TYPE:", "powitanie",  save, _Open_Sans_Bold_14);
			  	  	  	  	  	  	HAL_Delay(3000);
			  	  	  	  	  	  	TFT_Restore_Area(400, 200, 100, 47+1+34+35*counter, save);
			 		  		}
	  }
		__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin);//czyszczenie zgłoszonego przerwania
		NVIC_EnableIRQ(EXTI15_10_IRQn);

//		HAL_Delay(1000);
//		uint16_t counter3 = TFT_Draw_List(400, 200, 100, "TYPE:", "placek ciastko lody lizak",  save, _Open_Sans_Bold_14);
//		HAL_Delay(1000);
//		TFT_Restore_Area(400, 200, 100, 47+1+34+35*counter3, save);
//		HAL_Delay(1000);
//		uint16_t counter4 = TFT_Draw_List(400, 200, 100, "TYPE:", "",  save, _Open_Sans_Bold_14);
//		HAL_Delay(1000);
//		TFT_Restore_Area(400, 200, 100, 47+1+34+35*counter4, save);
//
//		HAL_Delay(3000);
//		TFT_Draw_Alert (allertX, allertY, "to jest przykladowy alert do celow demonstracyjnych i testowych",  save, _Open_Sans_Bold_20);
//		HAL_Delay(3000);
//		TFT_Restore_Area(TFT_WIDTH/2-(allertX/2), TFT_HEIGHT/2-(allertY/2), allertX, allertY, save);



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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == T_IRQ_Pin)
	{
		was_touched=1;
//					__HAL_GPIO_EXTI_CLEAR_IT(EXTI15_10_IRQn);//czyszczenie zgłoszonego przerwania
//					NVIC_DisableIRQ(EXTI15_10_IRQn);
//					uint16_t touchx, touchy;
//					char buffer1[10]=""; // Bufor na konwertowaną wartość
//					char buffer2[10]=""; // Bufor na konwertowaną wartość
//					TFT_Draw_Fill_Round_Rect (280, 180, 200, 60, 10,  0xCFFF);
//					touchx = getX();//pobrannie wartości X
//					sprintf(buffer1, "X%d", touchx); // Konwersja wartości do ciągu znaków
//					touchy = getY();//pobrannie wartości Y
//					sprintf(buffer2, "Y%d", touchy); // Konwersja wartości do ciągu znaków
//
//					LCD_Font(300, 200,  buffer1, _Open_Sans_Bold_28, 1, BLACK);
//					LCD_Font(300, 220,  buffer2, _Open_Sans_Bold_28, 1, BLACK);
//					HAL_Delay(1000);
//					XPT2046_Init();//włączenie przerwań
//					__HAL_GPIO_EXTI_CLEAR_IT(T_IRQ_Pin);//czyszczenie zgłoszonego przerwania
//					NVIC_EnableIRQ(EXTI15_10_IRQn);

	}
}
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
