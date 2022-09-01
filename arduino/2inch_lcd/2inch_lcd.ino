#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <SPI.h>
#include "lcd_2inch.h"
#include "lcd_gui.h"
#include "fonts.h"

/******************************
 * when set image in ROTATE_270:
 * 0------------> x (1~320) 
 * |
 * |
 * |
 * |
 * y (1~240)
 * 
 * */

void setup()
{
    Lcd_Init();
    Gui_Clear(WHITE);
    Image_Init(LCD_W, LCD_H, ROTATE_0, MIRROR_NONE);
}

void loop()
{
    Gui_Clear(RED);
    delay(600);
    Gui_Clear(GREEN);
    delay(600);
    Gui_Clear(BLUE);
    delay(600);
    Gui_Clear(WHITE);
    Gui_draw_point(30, 20, YELLOW, 18);
    Gui_draw_line(10, 120, 320, 120, RED, 2, SOLID);
    Gui_draw_line(160, 1, 160, 240, RED, 2, SOLID);
    Gui_draw_rectangle(170, 160, 200, 200, BLUE, 1, EMPTY);
    Gui_draw_rectangle(240, 180, 270, 220, YELLOW, 1, FULL);
    Gui_draw_circle(80, 80, 20, RED,1, EMPTY);
    Gui_draw_circle(40, 160, 15, RED,1, FULL);
    delay(1000);
    Gui_Clear(WHITE);
    Gui_draw_str(10, 10, "9876543210", &Font24, BLACK, WHITE);
    Gui_draw_str(10, 40, "seengreat!", &Font24, BLUE, WHITE);
    Gui_draw_str(10, 70, "SEENGREAT!", &Font24, RED, WHITE);
    Gui_draw_str_cn(10, 100,"深桂科技", &CN_Font24, GREEN, WHITE);
    Gui_show_bmp(gImage_180X40, 10, 140, 180, 40);
    delay(1000);    
}
