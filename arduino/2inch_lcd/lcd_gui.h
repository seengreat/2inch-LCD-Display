#ifndef __LCD_GUI_H
#define __LCD_GUI_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fonts.h"

#define RED       0XF800
#define WHITE     0XFFFF
#define BLACK     0X0000
#define BLUE      0X001F
#define GREEN     0X07E0
#define YELLOW    0XFFE0 //0XFFE0

#define FONT_BACKGROUND  WHITE

#define MIRROR_NONE        0
#define MIRROR_HORIZONTAL  1
#define MIRROR_VERTICAL    2
#define MIRROR_ORGIN       3

#define ROTATE_0     0
#define ROTATE_90    1
#define ROTATE_180   2
#define ROTATE_270   3

typedef struct{
	uint16_t w;
	uint16_t h;
	uint16_t rotate;
	uint16_t mirror;
}IMAGE;

typedef enum{
    EMPTY = 0,
    FULL,	
} FILL;

typedef enum{
    SOLID = 0,  //_______________
    DOTTED,	    //---------------
} LINE_STYLE;

typedef enum{
    ROUND = 0,             
    SQUAER,	    
} DOT_STYLE;

extern IMAGE Image;
extern const unsigned char gImage_180X40[];

void Image_Init( uint16_t img_w, uint16_t img_h, uint16_t rotate, uint16_t mirror);
void Gui_set_pix(uint16_t x, uint16_t y, uint16_t color);
void Gui_Clear(uint16_t color);
void Gui_draw_point(uint16_t x, uint16_t y, uint16_t color, uint16_t width);
void Gui_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t width, LINE_STYLE  type);
void Gui_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t width, FILL fill);
void Gui_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color, uint16_t width, FILL fill);
void Gui_draw_char(uint16_t x, uint16_t y, const char str_char,FONT* Font, uint16_t color, uint16_t background);
void Gui_draw_str(uint16_t x, uint16_t y, const char *str_char, FONT* Font, uint16_t color, uint16_t background);
void Gui_draw_str_cn(uint16_t x, uint16_t y, const char *str_cn, CN_FONT* Font, uint16_t color, uint16_t background);
int Gui_show_bmp(const unsigned char *img, uint16_t x, uint16_t y, uint16_t img_w, uint16_t img_h);
#endif
