/********************************
 *  Seengreat 2 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/

#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

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


int main(void)
{
	u_int16_t *image;
	image = (u_int16_t *)malloc(LCD_SIZE);
	Image_Init(image, LCD_W, LCD_H, ROTATE_270, MIRROR_NONE);
	Lcd_Init();
	while(1)
	{
		Gui_Clear(WHITE);
		Gui_draw_point(20, 200, YELLOW, 18);
		Gui_draw_line(310, 175, 180, 190, BLUE, 1, SOLID);
		Gui_draw_line(310, 110, 230, 10, BLUE, 2, DOTTED);
		Gui_draw_line(180, 195, 310, 215, RED, 2, DOTTED);
		Gui_draw_rectangle(200, 210, 230, 235, BLUE, 1, EMPTY);
		Gui_draw_rectangle(50, 200, 70, 230, YELLOW, 1, FULL);
		Gui_draw_circle(110, 210, 20, RED,1, EMPTY);
		Gui_draw_circle(170, 220, 15, RED,1, FULL);
		Gui_draw_str(10, 30, "876543210!", &Font24, BLACK, WHITE);
		Gui_draw_str(10, 80, "seengreat!", &Font24, BLUE, WHITE);
		Gui_draw_str(10, 120, "SEENGREAT!", &Font24, GREEN, WHITE);
		Gui_draw_str_cn(10, 160,"Éî¹ð¿Æ¼¼", &CN_Font24, GREEN, WHITE);
		Display(image);
		delay(3000);
		
		Gui_show_bmp("./fruits8.bmp");
		Display(image);
		delay(3000);		
	}
}
