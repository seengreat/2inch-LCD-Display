#include <SPI.h>
#include <string.h>
#include <stdlib.h>		

#include "lcd_2inch.h"

//Configure the serial port to use the standard printf function
//start
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}
//end

/***************************************************************
function:Hardware initialization
***************************************************************/
void Lcd_Gpio_Init(void)
{
    //gpio init
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_RST, OUTPUT);
    pinMode(PIN_DC, OUTPUT);
    pinMode(PIN_BL, OUTPUT);
    analogWrite(PIN_BL, 140);
    //Serial init
    Serial.begin(115200);
    printf_begin();
    printf("Init gpio for arduino\r\n"); 
    //spi init
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.begin();
}

/***************************************************************
function:Hardware reset
***************************************************************/
static void Lcd_Reset(void)
{
	digitalWrite(PIN_CS, HIGH);
	delay(100);
	digitalWrite(PIN_RST, LOW);
	delay(100);
	digitalWrite(PIN_RST, HIGH);
	delay(100);
}

/****************************************************************
function:Write data and commands
*****************************************************************/
static void Spi_write_cmd(unsigned char data)	 
{	
	digitalWrite(PIN_CS, LOW);
	digitalWrite(PIN_DC, LOW);
	SPI.transfer(data); 
}

void Spi_write_data(unsigned char data) 
{	
	digitalWrite(PIN_CS, LOW);
	digitalWrite(PIN_DC, HIGH);
	SPI.transfer(data);  
	digitalWrite(PIN_CS,HIGH);
}  

void Spi_write_word(uint16_t data)
{
	unsigned char temp = 0;
	digitalWrite(PIN_CS, LOW);
	digitalWrite(PIN_DC, HIGH);
	temp = (data>>8) & 0xff;
  SPI.transfer(temp);
	temp = data & 0xff;
  SPI.transfer(temp);
	digitalWrite(PIN_CS, HIGH);
}	  


/******************************************************************************
function:	Common register initialization
******************************************************************************/
void Lcd_Init(void)
{
	Lcd_Gpio_Init();
	Lcd_Reset();

	Spi_write_cmd(0x36);
	Spi_write_data(0xA0); 

	Spi_write_cmd(0x3A); 
	Spi_write_data(0x05);

	Spi_write_cmd(0x21); 

	Spi_write_cmd(0x2A);
	Spi_write_data(0x00);
	Spi_write_data(0x01);
	Spi_write_data(0x00);
	Spi_write_data(0x3F);

	Spi_write_cmd(0x2B);
	Spi_write_data(0x00);
	Spi_write_data(0x00);
	Spi_write_data(0x00);
	Spi_write_data(0xEF);

	Spi_write_cmd(0xB2);
	Spi_write_data(0x0C);
	Spi_write_data(0x0C);
	Spi_write_data(0x00);
	Spi_write_data(0x33);
	Spi_write_data(0x33);

	Spi_write_cmd(0xB7);
	Spi_write_data(0x35); 

	Spi_write_cmd(0xBB);
	Spi_write_data(0x1F);

	Spi_write_cmd(0xC0);
	Spi_write_data(0x2C);

	Spi_write_cmd(0xC2);
	Spi_write_data(0x01);

	Spi_write_cmd(0xC3);
	Spi_write_data(0x12);   

	Spi_write_cmd(0xC4);
	Spi_write_data(0x20);

	Spi_write_cmd(0xC6);
	Spi_write_data(0x0F); 

	Spi_write_cmd(0xD0);
	Spi_write_data(0xA4);
	Spi_write_data(0xA1);

	Spi_write_cmd(0xE0);
	Spi_write_data(0xD0);
	Spi_write_data(0x08);
	Spi_write_data(0x11);
	Spi_write_data(0x08);
	Spi_write_data(0x0C);
	Spi_write_data(0x15);
	Spi_write_data(0x39);
	Spi_write_data(0x33);
	Spi_write_data(0x50);
	Spi_write_data(0x36);
	Spi_write_data(0x13);
	Spi_write_data(0x14);
	Spi_write_data(0x29);
	Spi_write_data(0x2D);

	Spi_write_cmd(0xE1);
	Spi_write_data(0xD0);
	Spi_write_data(0x08);
	Spi_write_data(0x10);
	Spi_write_data(0x08);
	Spi_write_data(0x06);
	Spi_write_data(0x06);
	Spi_write_data(0x39);
	Spi_write_data(0x44);
	Spi_write_data(0x51);
	Spi_write_data(0x0B);
	Spi_write_data(0x16);
	Spi_write_data(0x14);
	Spi_write_data(0x2F);
	Spi_write_data(0x31);
	Spi_write_cmd(0x21);

	Spi_write_cmd(0x11);

	Spi_write_cmd(0x29);
}


//select the srceen area(from point(start_x,start_y) to point(end_x,end_y))
void Set_Window(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t  end_y)
{ 
	Spi_write_cmd(0x2a);
	Spi_write_data(start_x >>8);
	Spi_write_data(start_x & 0xff);
	Spi_write_data((end_x - 1) >> 8);
	Spi_write_data((end_x - 1) & 0xff);

	Spi_write_cmd(0x2b);
	Spi_write_data(start_y >>8);
	Spi_write_data(start_y & 0xff);
	Spi_write_data((end_y - 1) >> 8);
	Spi_write_data((end_y - 1) & 0xff);

	Spi_write_cmd(0x2C);
}


//set cursor to the point(x, y)
void Set_Cursor(uint16_t x, uint16_t y)
{ 
	Spi_write_cmd(0x2a);
	Spi_write_data(x >> 8);
	Spi_write_data(x);
	Spi_write_data(x >> 8);
	Spi_write_data(x);

	Spi_write_cmd(0x2b);
	Spi_write_data(y >> 8);
	Spi_write_data(y);
	Spi_write_data(y >> 8);
	Spi_write_data(y);

	Spi_write_cmd(0x2C);
}

//refresh the entire screen to color
void Lcd_Clear(uint16_t color)
{
	uint16_t i,j;
	Set_Window(0, 0, LCD_W, LCD_H);
	digitalWrite(PIN_DC, HIGH);
	for(i = 0; i < LCD_W; i++)
	{
      for(j=0;j< LCD_H; j++)
      {
          Spi_write_data((color>>8)&0xff);
          Spi_write_data(color);
      } 
	}
}

//set the point(x,y) to color
void Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{
	 Set_Cursor(x, y);
   Spi_write_word(color);  
}
