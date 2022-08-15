#ifndef __LCD_2INCH_H
#define __LCD_2INCH_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>

#define LCD_W   240 //LCD width
#define LCD_H   320 //LCD height

#define PIN_CS   10   
#define PIN_RST  9   
#define PIN_DC   8   
#define PIN_BL   7

#define LCD_SIZE   (uint32_t)(LCD_W*LCD_H*2)                  



void Lcd_Gpio_Init(void);
void Lcd_Init(void); 
void Lcd_Clear(uint16_t Color);
void Display(uint16_t *image);
void Draw_Point(uint16_t x, uint16_t y, uint16_t color);

void Spi_write_data(unsigned char data);
void Spi_write_word(uint16_t da);
void Set_Cursor(uint16_t x, uint16_t y);
void Set_Window(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t  end_y);


#endif
