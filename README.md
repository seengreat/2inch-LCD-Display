### Instructions
## 1.1、Overview
This LCD is a 2-inch TFT display, with resolution of 320 * 240, the built-in  ST7789V controller. It uses SPI interface, providing Raspberry Pi C, Python and Arduino demo codes. It can be not only drawn point, line, rectangle, circle, but also displayed pictures and characters in Chinese and English by demo codes.<br>
__Specifications__
|DIMENSIONS	|60mm(length)*37mm(Width)|
|----------------------|--------------------------------|
|RESOLUTION	|240*320RGB|
|DRIVER	|ST7789V|
|DISPLAY SIZE	|40.8mm*30.6mm|
|LCD TYPE	|IPS
|OPERATING TEMPERATURE	|-20℃--+70℃|
|OPERATIN VOLTAGE	|3.3V/5V|
|INTERFACE	|4-wire SPI |
### Usage
## 2.1、Instructions of Hard Interface Configuration
# 2.1.1、Raspberry Pi Hardware Connection
The demo codes of Raspberry Pi motherboard use the pin definition of wiringPi code. The definition of connecting to the Raspberry Pi motherboard  is according to the following table:<br>
|LCD Interface	|BCM 	|wiringPi	|BOARD|
|----------------------|-----------|-----------|--------|
|VCC	|3.3V	|3.3V	|3.3V|
|GND	|GND	|GND	|GND|
|DIN	|MOSI	|12	|19|
|CLK	|SCLK	|14	|23|
|CS	|CE0	|10	|24|
|RST	|22	|3	|15|
|DC	|25	|6	|22|
|BL	|24	|5             |18|
The wiring diagram of connections between the Raspberry Pi extension interface and display interface is shown in figure 2-1.<br>
![1.jpg](https://github.com/seengreat/2inch-LCD-Display/blob/main/pic/pic1.png)<br>
                       Figure 2-1 Connection between LCD and Raspberry Pi<br>
# 2.1.2、Arduino Hardware Connection
LCD and Arduino Connection Pin Correspondences are shown in the following table:<br>
|LCD Display	|Arduino UNO|
|----------------------|---------------|
|VCC	|5V|
|GND	|GN|
|DIN	|D11|
|SCK	|D13|
|CS	|D10|
|RST	|D9|
|DC	|D8|
|BL	|D7|
![2.jpg](https://github.com/seengreat/2inch-LCD-Display/blob/main/pic/pic2.png)<br>
                 Figure 2-2 Connections between LCD and Arduino<br>
## 2.2、Usage of Demo Codes 
# 2.2.1、wiringpi Libraries Installation
sudo apt-get install wiringpi<br>
   wget https://project-downloads.drogon.net/wiringpi-latest.deb  # Raspberry Pi 4B version upgrade<br>
   sudo dpkg -i wiringpi-latest.deb<br>
   gpio -v # If version 2.52 appears, it means that the installation has been successful<br>
# 2.2.2、Enable SPI Interface
sudo raspi-config<br>
Enable the SPI Interface:<br>
Interfacing Options -> SPI -> Yes<br>
Check the enabled SPI devices:<br>
ls /dev/spi*   # at this time it will print:“/dev/spidev0.0”and“/dev/spidev0.1”<br>
# 2.2.3、Python Libraries Installation
The demo codes are working under the python3 environment, and running the demo codes of python requires the installation of the pil, numpy, and spidev libraries. Please run the following commands to install: <br>
sudo apt-get install python3-pil<br>
sudo apt-get install python3-numpy<br>
sudo apt-get install python3-pip<br>
sudo pip3 install spidev<br>
# 2.2.4、C Demo Codes
Access 2inch_lcd/c directory<br>
sudo make clean<br>
sudo make<br>
sudo ./main<br>
# 2.2.5、Python Demo Codes
Access 2inch_lcd/python directory<br>
python3 2inch_lcd.py<br>
## 2.3、Instructions of Demo Codes
# 2.3.1、C
The structure of demo codes is divided into the underlying layer and the application layer. The underlying file is lcd_2inch.c and lcd_2inch.h, the underlying code implements the initialization of the Raspberry Pi motherboard control pin and the LCD screen. The application layer file is lcd_gui.c and lcd_gui.h, which mainly makes the painting of points, lines, rectangles, circles and the display functions of pictures and characters in Chinese and English come true. The files starting with "font" in the file name are related to the font library. The ".c" suffix corresponds to the font library's data source file, and the data structure of multiple font library data source files is defined in the "fonts.h" file. The file with the suffix ".bmp" in the demo codes of the Raspberry Pi Motherboard is a picture source file used for display, and the number in the file name indicates the number of pixel bits (bpp, bit-per-pixel) of color. For example, fruits24.bmp represents a picture file in 24bpp true color format. The demo codes of Arduino UNO motherboard do not have these ".bmp" files, because the available memory in the Arduino UNO motherboard is relatively less , and the source data of the pictures is stored in the image.cpp file in the form of an array.
# 2.3.2、Python 
The Python demo codes are only provided for the Raspberry Pi platform. Because the Python platform can reference the PIL image processing library, many application-layer API functions can be provided directly by the library, greatly reducing the amount of codes in the demo codes.

