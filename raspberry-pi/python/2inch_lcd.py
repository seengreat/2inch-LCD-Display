# Seengreat 2 Inch LCD Display demo
# Author(s):Andy Li from Seengreat

import os
import sys
import spidev
import time
import wiringpi as wpi
import numpy as np
from PIL import ImageDraw, Image, ImageFont
"""the following pin definiting use wiringpi"""
RST_PIN  = 3
DC_PIN   = 6
BL_PIN   = 5
class LCD_2Inch():
    def __init__(self):
        # gpio init
        wpi.wiringPiSetup()
        wpi.pinMode(DC_PIN, wpi.OUTPUT)  # D/C pin
        wpi.pinMode(RST_PIN, wpi.OUTPUT)  # reset pin
        wpi.pinMode(BL_PIN, wpi.OUTPUT)  # back light control pin
        wpi.softPwmCreate(BL_PIN, 0, 100)
        wpi.softPwmWrite(BL_PIN, 90)
        # spi init
        self.bus = 0
        self.dev = 0
        self.spi_speed = 4000000
        self.spi = spidev.SpiDev()
        self.spi.open(self.bus, self.dev)
        self.spi.max_speed_hz = self.spi_speed
        self.spi.mode = 0b00
        # self.spi.xfer([4000000, 10, 8])
        # define width and height of the 2 inch lcd
        self.w = 240
        self.h = 320 
        
    def write_cmd(self, cmd):
        """write command"""
        wpi.digitalWrite(DC_PIN,wpi.LOW)
        self.spi.writebytes([cmd])
        
    def write_data(self, value):
        """write data"""
        wpi.digitalWrite(DC_PIN,wpi.HIGH)
        self.spi.writebytes([value])
        
    def reset(self):
        """reset the lcd"""
        wpi.digitalWrite(RST_PIN,wpi.HIGH)
        time.sleep(0.02)
        wpi.digitalWrite(RST_PIN,wpi.LOW)
        time.sleep(0.02)
        wpi.digitalWrite(RST_PIN,wpi.HIGH)
        time.sleep(0.02)
    def lcd_init(self):
        """lcd init..."""
        self.reset()
        
        self.write_cmd(0x36)
        self.write_data(0x00)
        
        self.write_cmd(0x3A) # set interface pixel format
        self.write_data(0x05)

        self.write_cmd(0x21)
        
        self.write_cmd(0x2A) # set x address form 0 to 320
        self.write_data(0x00)
        self.write_data(0x00)
        self.write_data(0x01) 
        self.write_data(0x3F)
        
        self.write_cmd(0x2B)  # set y address form 0 to 240
        self.write_data(0x00)
        self.write_data(0x00)
        self.write_data(0x00)
        self.write_data(0xEF)
        
        self.write_cmd(0xB2) # porch control
        self.write_data(0x0C)
        self.write_data(0x0C)
        self.write_data(0x00)
        self.write_data(0x33)
        self.write_data(0x33)

        self.write_cmd(0xB7) # gate control 
        self.write_data(0x35)
        
        self.write_cmd(0xBB)  # VCOMS setting
        self.write_data(0x1F)

        self.write_cmd(0xC0) #LCM control
        self.write_data(0x2C)
        
        self.write_cmd(0xC2)
        self.write_data(0x01)
        
        self.write_cmd(0xC3)
        self.write_data(0x12) 

        self.write_cmd(0xC4) # VDV setting
        self.write_data(0x20)

        self.write_cmd(0xC6)  # FR control 2
        self.write_data(0x0F)
        
        self.write_cmd(0xD0) # power control 1
        self.write_data(0xA4)
        self.write_data(0xA1)
        
        self.write_cmd(0xE0) # positive voltage gamma control
        self.write_data(0xD0)
        self.write_data(0x08)
        self.write_data(0x11)
        self.write_data(0x08)
        self.write_data(0x0C)
        self.write_data(0x15)
        self.write_data(0x39)
        self.write_data(0x33)
        self.write_data(0x50)
        self.write_data(0x36)
        self.write_data(0x13)
        self.write_data(0x14)
        self.write_data(0x29)
        self.write_data(0x2D)
        
        self.write_cmd(0xE1) # negative voltage gamma control 
        self.write_data(0xD0)
        self.write_data(0x08)
        self.write_data(0x10)
        self.write_data(0x08)
        self.write_data(0x06)
        self.write_data(0x06)
        self.write_data(0x39)
        self.write_data(0x44)
        self.write_data(0x51)
        self.write_data(0x0B)
        self.write_data(0x16)
        self.write_data(0x14)
        self.write_data(0x2F)
        self.write_data(0x31)
        self.write_cmd(0x21)
        self.write_cmd(0x11)
        self.write_cmd(0x29)
        
    def set_windows(self, start_x, start_y, end_x, end_y):
        """display the windows of start point and end point"""
        self.write_cmd(0x2A) # set the start point and end point of x
        self.write_data(start_x >> 8)  # x address start
        self.write_data(start_x & 0xff)
        self.write_data(end_x >> 8)  # x address end
        temp = end_x - 1
        self.write_data(temp & 0xff)
        
        self.write_cmd(0x2B) # set the start point and end point of y
        self.write_data(start_y >> 8)  # y address start
        self.write_data(start_y & 0xff)
        self.write_data(end_y >> 8)  # y address end
        temp = end_y - 1
        self.write_data(temp & 0xff)
        
        self.write_cmd(0x2C)
        
    def img_show(self, img):
        img_w, img_h = img.size
        
        image = np.asarray(img)
        pixel = np.zeros((self.w, self.h, 2), dtype = np.uint8)
        pixel[..., [0]] = np.add(np.bitwise_and(image[..., [0]], 0xf8), np.right_shift(image[..., [1]], 5))
        
        pixel[..., [1]] = np.add(np.bitwise_and(np.left_shift(image[..., [1]], 3), 0xe0), np.right_shift(image[..., [2]], 3))       
        
        pixel = pixel.flatten().tolist()
        
        self.write_cmd(0x36)
        self.write_data(0x70)
        self.set_windows(0, 0, self.h, self.w)
        wpi.digitalWrite(DC_PIN,wpi.HIGH)
        for i in range(0, len(pixel), 4096):
            self.spi.writebytes(pixel[i:i+4096])
                
    def clear(self):
        self.set_windows(0, 0, self.w, self.h)
        wpi.digitalWrite(DC_PIN,wpi.HIGH)
        buf = [0xFF]*(self.w*self.h*2)
        for i in range(0, len(buf), 4096):
            self.spi.writebytes(buf[i:i+4096])

if __name__ == '__main__':
    lcd = LCD_2Inch()
    lcd.lcd_init()
    lcd.clear()
    img0 = Image.new("RGB", (lcd.h, lcd.w), "WHITE")
    lcd_draw = ImageDraw.Draw(img0)
    Font = ImageFont.truetype("MiSans-Light.ttf",32) # read chinese font file
    text= u"深桂科技"
    img1 = Image.open('fruits.jpg') # open jpg file
    
    while True:
        lcd_draw.line([(20, 80),(80, 80)], fill = "RED",width = 2)
    
        lcd_draw.rectangle([(20,10),(70,60)],fill = "WHITE",outline="BLUE")
        lcd_draw.rectangle([(85,10),(130,60)],fill = "BLUE")
    
        lcd_draw.arc((160,30,210,80), 0, 360, fill =(0,255,255))
        lcd_draw.ellipse((240,30,290,80), fill = (255,255,0))
    
        lcd_draw.text((5, 120), 'SEENGREAT', fill = "BLUE",font=Font)
        lcd_draw.text((5, 200), 'AB cd 3210', fill = "RED",font=Font)
    
        lcd_draw.text((5, 160),text, fill = "BLUE",font=Font)
    
        lcd.img_show(img0.rotate(180))
      
        time.sleep(3)
        lcd.img_show(img1.rotate(180)) # show image
        time.sleep(3)
    