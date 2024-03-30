#include "display_ssd1963.h"
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include "math.h"




uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define swap(a, b)			do {\
								int16_t t = a;\
								a = b;\
								b = t;\
							} while(0)

GPIO_TypeDef* PORT_NAME_ARR[]={D0_PORT,D1_PORT,D2_PORT,D3_PORT,D4_PORT,D5_PORT,D6_PORT,D7_PORT,D8_PORT,D9_PORT,D10_PORT,D11_PORT,D12_PORT,D13_PORT,D14_PORT,D15_PORT};
uint16_t      PIN_NAME_ARR[]={D0_PIN,D1_PIN,D2_PIN,D3_PIN,D4_PIN,D5_PIN,D6_PIN,D7_PIN,D8_PIN,D9_PIN,D10_PIN,D11_PIN,D12_PIN,D13_PIN,D14_PIN,D15_PIN};


void tft_write_bus(uint8_t high_byte,uint8_t low_byte)
{
  /*uint8_t i;
  for(i=0;i<8;i++)
  {
    if(high_byte&(0x01<<i))
    {
      pin_high(PORT_NAME_ARR[i+8],PIN_NAME_ARR[i+8]);
    }
    else
    {
      pin_low(PORT_NAME_ARR[i+8],PIN_NAME_ARR[i+8]);
    }

		if(low_byte&(0x01<<i))
    {
      pin_high(PORT_NAME_ARR[i],PIN_NAME_ARR[i]);
    }
    else
    {
      pin_low(PORT_NAME_ARR[i],PIN_NAME_ARR[i]);
    }
  }*/
	PORTA->ODR = (PORTA->ODR & 0xffffff00) | low_byte;
	PORTB->ODR = (PORTB->ODR & 0xffffff00) | high_byte;
	asm("nop");
	pin_low(WR_PORT,WR_PIN);
	pin_high(WR_PORT,WR_PIN);
}



void Lcd_Write_Data(uint16_t data)
{
  pin_high(RS_PORT,RS_PIN);
  tft_write_bus(data>>8,data&0x00ff);
}

void Lcd_Write_Cmd(uint16_t data)
{
  pin_low(RS_PORT,RS_PIN);
  tft_write_bus(data>>8,data&0x00ff);
}


void Lcd_SetArea(uint16_t sx, uint16_t ex, uint16_t sy, uint16_t ey)
{
Lcd_Write_Cmd(SSD1963_SET_COLUMN_ADDRESS);	
Lcd_Write_Data((sx >> 8) & 0xFF);
Lcd_Write_Data((sx >> 0) & 0xFF);
Lcd_Write_Data((ex >> 8) & 0xFF);
Lcd_Write_Data((ex >> 0) & 0xFF);

Lcd_Write_Cmd(SSD1963_SET_PAGE_ADDRESS);	
Lcd_Write_Data((sy >> 8) & 0xFF);
Lcd_Write_Data((sy >> 0) & 0xFF);
Lcd_Write_Data((ey >> 8) & 0xFF);
Lcd_Write_Data((ey >> 0) & 0xFF);
}
//=============================================================================
// Fill area of specified color
//=============================================================================
void Lcd_FillArea(uint16_t sx, uint16_t ex, uint16_t sy, uint16_t ey, int16_t color)
{
uint16_t i;
Lcd_SetArea(sx, ex, sy, ey);
Lcd_Write_Cmd(SSD1963_WRITE_MEMORY_START);
for(i = 0; i < ((ex-sx+1)*(ey-sy+1)); i++)
	{
	Lcd_Write_Data(color);
	}
}

//=============================================================================
// Fills whole screen specified color
//=============================================================================
void Lcd_ClearScreen(int16_t color)
{
unsigned int x,y;
Lcd_SetArea(0, TFT_WIDTH-1 , 0, TFT_HEIGHT-1);
Lcd_Write_Cmd(0x2c);
for(x=0;x<TFT_WIDTH;x++)
	{
        for(y= 0;y<TFT_HEIGHT;y++)
                {
                Lcd_Write_Data(color);
                }
	}
}

void Lcd_SetPixel(int16_t x, int16_t y, int16_t color)
{
Lcd_SetArea(x, x, y, y);
Lcd_Write_Cmd(0x2c);
Lcd_Write_Data(color);
Lcd_Write_Cmd(0x0);
}



void Init_SSD1963(void)
{

	pin_high(CS_PORT,CS_PIN);
	pin_high(RD_PORT,RD_PIN);
	pin_high(WR_PORT,WR_PIN);
	pin_low(REST_PORT,REST_PIN);

	HAL_Delay(20);
	pin_high(REST_PORT,REST_PIN);
	HAL_Delay(20);
	pin_low(CS_PORT,CS_PIN);


Lcd_Write_Cmd(0xE2);		//PLL multiplier, set PLL clock to 120M
Lcd_Write_Data(0x23);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
Lcd_Write_Data(0x02);
Lcd_Write_Data(0x04);
Lcd_Write_Cmd(0xE0);		// PLL enable
Lcd_Write_Data(0x01);
HAL_Delay(10);
Lcd_Write_Cmd(0xE0);
Lcd_Write_Data(0x03);
HAL_Delay(10);
Lcd_Write_Cmd(0x01);		// software reset
HAL_Delay(100);
Lcd_Write_Cmd(0xE6);		//PLL setting for PCLK, depends on resolution
Lcd_Write_Data(0x04);
Lcd_Write_Data(0x93);
Lcd_Write_Data(0xE0);

Lcd_Write_Cmd(0xB0);		//LCD SPECIFICATION
Lcd_Write_Data(0x00);		// 0x24
Lcd_Write_Data(0x00);
Lcd_Write_Data(0x03);		//Set HDP	799
Lcd_Write_Data(0x1F);
Lcd_Write_Data(0x01);		//Set VDP	479
Lcd_Write_Data(0xDF);
Lcd_Write_Data(0x00);

Lcd_Write_Cmd(0xB4);		//HSYNC
Lcd_Write_Data(0x03);		//Set HT	928
Lcd_Write_Data(0xA0);
Lcd_Write_Data(0x00);		//Set HPS	46
Lcd_Write_Data(0x2E);
Lcd_Write_Data(0x30);		//Set HPW	48
Lcd_Write_Data(0x00);		//Set LPS	15
Lcd_Write_Data(0x0F);
Lcd_Write_Data(0x00);

Lcd_Write_Cmd(0xB6);		//VSYNC
Lcd_Write_Data(0x02);		//Set VT	525
Lcd_Write_Data(0x0D);
Lcd_Write_Data(0x00);		//Set VPS	16
Lcd_Write_Data(0x10);
Lcd_Write_Data(0x10);		//Set VPW	16
Lcd_Write_Data(0x00);		//Set FPS	8
Lcd_Write_Data(0x08);

Lcd_Write_Cmd(0xBA);
Lcd_Write_Data(0x05);		//GPIO[3:0] out 1

Lcd_Write_Cmd(0xB8);
Lcd_Write_Data(0x07);	    //GPIO3=input, GPIO[2:0]=output
Lcd_Write_Data(0x01);		//GPIO0 normal

Lcd_Write_Cmd(0xba);		//rotation
Lcd_Write_Data(0x01);		// -- Set to 0x22 to rotate 180 degrees 0x21


Lcd_Write_Cmd(0xF0);		//pixel data interface
Lcd_Write_Data(0x03);


HAL_Delay(10);

Lcd_SetArea(0, 0, 799, 479);
Lcd_Write_Cmd(0x29);		//display on

Lcd_Write_Cmd(0xBE);		//set PWM for B/L
Lcd_Write_Data(0x06);
Lcd_Write_Data(0xF0);
Lcd_Write_Data(0x01);
Lcd_Write_Data(0xF0);
Lcd_Write_Data(0x00);
Lcd_Write_Data(0x00);

Lcd_Write_Cmd(0xD0);
Lcd_Write_Data(0x0D);

Lcd_Write_Cmd(0x2C);

}



void TFT_Set_X(uint16_t start_x,uint16_t end_x)
{
	Lcd_Write_Cmd(0x002A);
	Lcd_Write_Data(start_x>>8);
	Lcd_Write_Data(start_x&0x00ff);
	
	Lcd_Write_Data(end_x>>8);
	Lcd_Write_Data(end_x&0x00ff);
}


void TFT_Set_Y(uint16_t start_y,uint16_t end_y)
{
	Lcd_Write_Cmd(0x002B);
	Lcd_Write_Data(start_y>>8);
	Lcd_Write_Data(start_y&0x00ff);
	
	Lcd_Write_Data(end_y>>8);
	Lcd_Write_Data(end_y&0x00ff);
}


void TFT_Set_XY(uint16_t x, uint16_t y)
{
	TFT_Set_X(x, x);
	TFT_Set_Y(y, y);
}



void TFT_Set_Work_Area(uint16_t x, uint16_t y, uint16_t length, uint16_t width)
{
	TFT_Set_X(x, x+length-1);
	TFT_Set_Y(y, y+width-1);
	Lcd_Write_Cmd(0x2C);
}




void TFT_Clear_Screen(uint16_t color)
{
	uint32_t i=0;
	TFT_Set_Work_Area(0,0,800,480);
	pin_high(RS_PORT,RS_PIN);
	for(i=0; i < 384000; i++)
	{
		  tft_write_bus(color>>8,color&0x00ff);
	}
}

void TFT_Draw_Char(uint16_t x, uint16_t y, uint16_t color, uint16_t phone,const uint8_t *table, uint8_t ascii, uint8_t size)
{
	uint8_t i,f = 0;
	
	
	for (i = 0; i < 8; i++)
	{
		for(f = 0; f < 8; f++)
		{
			if((*(table + 8*(ascii-0x20)+i)>>(7-f))&0x01)
			{
				 TFT_Draw_Fill_Rectangle(x+f*size, y+i*size, size, size, color);
			}
			else
			{	
				 TFT_Draw_Fill_Rectangle(x+f*size, y+i*size, size, size, phone);
			}
		}
	}
}


void TFT_Draw_String(uint16_t x, uint16_t y, uint16_t color,uint16_t phone, const uint8_t *table, char *string, uint8_t size)
{

	while(*string)
	{      
		if((x + 8) > (TFT_WIDTH-1))
		{
			x = 1;
			y = y + 8*size;
		}
		TFT_Draw_Char(x, y, color, phone, table, *string, size);
		x += 8*size;
		*string++;
	}
}


void TFT_Draw_Line (uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2, uint8_t size,uint16_t color)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int error2 = 0;
	
	for (;;)
	{
		TFT_Draw_Fill_Rectangle(x1,y1,size,size,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		
		error2 = error * 2;
		
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		
		if(error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}


void TFT_Draw_HLine(uint16_t x, uint16_t y, uint16_t length, uint16_t size, uint16_t color)
{
	uint16_t i=0;
	
	TFT_Set_Work_Area(x,y,length,size);
	for(i=0; i<(length*size); i++)
	Lcd_Write_Data(color);
}

void TFT_Set_Read_Area(uint16_t x, uint16_t y, uint16_t length, uint16_t width)
{
	TFT_Set_X(x, x+length-1);
	TFT_Set_Y(y, y+width-1);
	Lcd_Write_Cmd(0x2E);
}

void TFT_Draw_Alert (uint16_t length, uint16_t width, char *text,  uint16_t *save, const GFXfont *p_font)
{

	uint32_t i=0;
	lcd_Read_Area(TFT_WIDTH/2-(length/2), TFT_HEIGHT/2-(width/2), length, width, save);
    TFT_Draw_Fill_Round_Rect (TFT_WIDTH/2-(length/2), TFT_HEIGHT/2-(width/2), length, width, 20,  0xd699);
    TFT_Draw_Fill_Round_Rect (TFT_WIDTH/2-(length/2), TFT_HEIGHT/2-(width/2), length, 60, 20,  0xe266);
    LCD_Font(TFT_WIDTH/2-30, TFT_HEIGHT/2-(width/2)+40, "ALERT", p_font, 1, BLACK);

}

void TFT_Restore_Alert (uint16_t length, uint16_t width, uint16_t *save)
{
	uint32_t i=0;
	TFT_Set_Work_Area(TFT_WIDTH/2-(length/2), TFT_HEIGHT/2-(width/2), length, width);
	for(i=0; i < length*width; i++)
	{
		Lcd_Write_Data(save[i]);
	}
}

void lcd_Read_Area(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t *save)
{
	uint32_t i=0;
	TFT_Set_Read_Area(x, y, length, width);
	PORTA->MODER = (PORTA->MODER & 0xffff0000);
	PORTB->MODER = (PORTB->MODER & 0xffff0000);
	pin_high(RS_PORT,RS_PIN);

	for(i=0; i < length*width; i++)
	{
		save[i] = lcd_Read_bus();
	}

	PORTA->MODER = (PORTA->MODER | 0x00005555);
	PORTB->MODER = (PORTB->MODER | 0x00005555);
}

uint16_t lcd_Read_bus()
{

	pin_low(RD_PORT,RD_PIN);
	pin_high(RD_PORT,RD_PIN);
	uint8_t high_byte =PORTB->IDR ;
	uint8_t low_byte =PORTA->IDR ;



/*	uint8_t low_byte =0 ;
	uint8_t high_byte =0 ;*/

	return ((high_byte<<8)|low_byte);
}



void TFT_Draw_VLine(uint16_t x, uint16_t y, uint16_t length, uint16_t size, uint16_t color)
{
	uint16_t i=0;
	
	TFT_Set_Work_Area(x,y,size,length);
	for(i=0; i<(length*size); i++)
	Lcd_Write_Data(color);
}


void TFT_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint8_t size, uint16_t color)
{
	TFT_Draw_HLine(x, y, length, size, color);
	TFT_Draw_HLine(x, y + width, length, size, color);
	TFT_Draw_VLine(x, y, width, size, color);
	TFT_Draw_VLine(x + length - size, y, width, size, color);
}


void TFT_Draw_Fill_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color)
{
	uint32_t i=0;
	
	TFT_Set_Work_Area(x,y,length, width);
	for(i=0; i < length*width; i++)
	{
		Lcd_Write_Data(color);
	}
}


void TFT_Draw_Triangle( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint16_t color)
{
	
	TFT_Draw_Line( x1, y1, x2, y2, color, size);
	TFT_Draw_Line( x2, y2, x3, y3, color, size);
	TFT_Draw_Line( x3, y3, x1, y1, color, size);
}


void TFT_Draw_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint16_t color)
{
	int a_,b_,P;
	a_ = 0;
	b_ = radius;
	P = 1 - radius;
	while (a_ <= b_)
	{
		if(fill == 1)
		{
			TFT_Draw_Fill_Rectangle(x-a_,y-b_,2*a_+1,2*b_+1,color);
			TFT_Draw_Fill_Rectangle(x-b_,y-a_,2*b_+1,2*a_+1,color);
		}
		else
		{
			TFT_Draw_Fill_Rectangle(a_+x, b_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(b_+x, a_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(x-a_, b_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(x-b_, a_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(b_+x, y-a_, size, size, color);
			TFT_Draw_Fill_Rectangle(a_+x, y-b_, size, size, color);
			TFT_Draw_Fill_Rectangle(x-a_, y-b_, size, size, color);
			TFT_Draw_Fill_Rectangle(x-b_, y-a_, size, size, color);
		}
		if (P < 0 )
		{
			P = (P + 3) + (2* a_);
			a_ ++;
		}
		else
		{
			P = (P + 5) + (2* (a_ - b_));
			a_ ++;
			b_ --;
		}
	}
}


void TFT_Draw_Circle_Helper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t size, uint16_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      TFT_Draw_Fill_Rectangle(x0 + x, y0 + y, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 + y, y0 + x, size, size, color);
    }
    if (cornername & 0x2) {
      TFT_Draw_Fill_Rectangle(x0 + x, y0 - y, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 + y, y0 - x, size, size, color);
    }
    if (cornername & 0x8) {
      TFT_Draw_Fill_Rectangle(x0 - y, y0 + x, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 - x, y0 + y, size, size, color);
    }
    if (cornername & 0x1) {
      TFT_Draw_Fill_Rectangle(x0 - y, y0 - x, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 - x, y0 - y, size, size, color);
    }
  }
}


void TFT_Draw_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint16_t color)
{

  TFT_Draw_HLine(x+r  , y    , length-2*r, size, color); // Top
  TFT_Draw_HLine(x+r  , y+width-1, length-2*r, size, color); // Bottom
  TFT_Draw_VLine(x    , y+r  , width-2*r, size, color); // Left
  TFT_Draw_VLine(x+length-1, y+r  , width-2*r, size, color); // Right

  TFT_Draw_Circle_Helper(x+r    , y+r    , r, 		 			1, size, color);
  TFT_Draw_Circle_Helper(x+length-r-1, y+r    , r, 			2, size, color);
  TFT_Draw_Circle_Helper(x+length-r-1, y+width-r-1, r,  4, size, color);
  TFT_Draw_Circle_Helper(x+r    , y+width-r-1, r, 			8, size, color);
}


void TFT_Draw_Fill_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) 
{

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      TFT_Draw_VLine(x0+x, y0-y, 2*y+1+delta, 1, color);
      TFT_Draw_VLine(x0+y, y0-x, 2*x+1+delta, 1, color);
    }
    if (cornername & 0x2) {
     TFT_Draw_VLine(x0-x, y0-y, 2*y+1+delta, 1, color);
     TFT_Draw_VLine(x0-y, y0-x, 2*x+1+delta, 1, color);
    }
  }
}


void TFT_Draw_Fill_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint16_t color)
{
  TFT_Draw_Fill_Rectangle(x+r, y, length-2*r, width, color);

  TFT_Draw_Fill_Circle_Helper(x+length-r-1, y+r, r, 1, width-2*r-1, color);
  TFT_Draw_Fill_Circle_Helper(x+r    , y+r, r, 2, width-2*r-1, color);
}



static void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, uint32_t color24)
{
	uint8_t  *bitmap = font -> bitmap;
	uint16_t bo = glyph -> bitmapOffset;
	uint8_t bits = 0, bit = 0;
	uint16_t set_pixels = 0;
	uint8_t  cur_x, cur_y;
	for(cur_y = 0; cur_y < glyph -> height; cur_y++)
	{
		for(cur_x = 0; cur_x < glyph -> width; cur_x++)
		{
			if(bit == 0)
			{
				bits = (*(const unsigned char *)(&bitmap[bo++]));
				bit  = 0x80;
			}
			if(bits & bit)
			{
				set_pixels++;
			}
			else if (set_pixels > 0)
			{
				TFT_Draw_Fill_Rectangle(x + (glyph -> xOffset + cur_x - set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
				set_pixels = 0;
			}
			bit >>= 1;
		}
		if (set_pixels > 0)
		{
			TFT_Draw_Fill_Rectangle(x + (glyph -> xOffset + cur_x-set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
			set_pixels = 0;
		}
	}
}
void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, uint32_t color24)
{
	int16_t cursor_x = x;
	int16_t cursor_y = y;
	GFXfont font;
	memcpy((&font), (p_font), (sizeof(GFXfont)));
	for(uint16_t text_pos = 0; text_pos < strlen(text); text_pos++)
	{
		char c = text[text_pos];
		if(c == '\n')
		{
			cursor_x = x;
			cursor_y += font.yAdvance * size;
		}
		else if(c >= font.first && c <= font.last && c != '\r')
		{
			GFXglyph glyph;
			memcpy((&glyph), (&font.glyph[c - font.first]), (sizeof(GFXglyph)));
			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color24);
			cursor_x += glyph.xAdvance * size;
		}
	}
}

void LCD_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	int16_t a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1);
		swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}

	if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		TFT_Draw_HLine(a, y0, b - a + 1,1, color);
		return;
	}

	int16_t	dx01 = x1 - x0,
			dy01 = y1 - y0,
			dx02 = x2 - x0,
			dy02 = y2 - y0,
			dx12 = x2 - x1,
			dy12 = y2 - y1;
	int32_t	sa   = 0,
			sb   = 0;

	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if (y1 == y2) last = y1;   // Include y1 scanline
	else last = y1 - 1; // Skip it

	for(y = y0; y <= last; y++) {
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
		a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b) swap(a,b);
		TFT_Draw_HLine(a, y, b-a+1,1, color);
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y <= y2; y++) {
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
		a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b) swap(a,b);
		TFT_Draw_HLine(a, y, b - a + 1,1, color);
	}
}


uint16_t rainbow(uint16_t value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

	uint16_t red = 0; // Red is the top 5 bits of a 16 bit colour value
	uint16_t green = 0;// Green is the middle 6 bits
	uint16_t blue = 0; // Blue is the bottom 5 bits

	uint16_t quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int ringMeter(int value, int vmin, int vmax, int x, int y, int r, uint16_t scheme){
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option
  x += r; y += r;   // Calculate coords of centre of ring
  int w = r / 6;    // Width of outer ring is 1/4 of radius
  int angle = 180;  // Half the sweep angle of meter (300 degrees)
//  int text_colour = 0; // To hold the text colour
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
  uint16_t seg = 5; // Segments are 5 degrees wide = 60 segments for 300 degrees
  uint16_t inc = 5; // Draw segments every 5 degrees, increase to 10 for segmented ring

  // Draw colour blocks every inc degrees
  for (int i = -angle; i < angle; i += inc) {
    // Choose colour from scheme
    int colour = 0;
    switch (scheme) {
      case 0: colour = RED; break; // Fixed colour
      case 1: colour = GREEN; break; // Fixed colour
      case 2: colour = BLUE; break; // Fixed colour
      case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
      case 4: colour = rainbow(map(i, -angle, angle, 63, 127)); break; // Green to red (high temperature etc)
      case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
      default: colour = BLUE; break; // Fixed colour
    }

    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles

    	LCD_FillTriangle(x0, y0, x1, y1, x2, y2, colour);
    	LCD_FillTriangle(x1, y1, x2, y2, x3, y3, colour);

    }
    else // Fill in blank segments
    {

    	LCD_FillTriangle(x0, y0, x1, y1, x2, y2, BLUE);
    	LCD_FillTriangle(x1, y1, x2, y2, x3, y3, BLUE);

    }


  }

  return x + r;
}
