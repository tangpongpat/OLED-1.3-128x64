/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*********************************************************************
I change the adafruit SSD1306 to SH1106

SH1106 driver don't provide several functions such as scroll commands.

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 64
#define LOGO16_GLCD_WIDTH  64
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0x01, 0xFF, 0xF0, 0x0F, 0xFF, 0x80, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x00, 0xFF, 0xE0, 0x00,
0x00, 0x0F, 0xFC, 0x00, 0x00, 0x3F, 0xF0, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x07, 0xF8, 0x00,
0x00, 0x3F, 0xC0, 0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x7F, 0x00, 0x3F, 0xFC, 0x00, 0xFE, 0x00,
0x00, 0xFE, 0x00, 0x3F, 0xFC, 0x00, 0x7F, 0x00, 0x01, 0xFC, 0x00, 0x3F, 0xFC, 0x00, 0x3F, 0x80,
0x03, 0xF8, 0x00, 0x3F, 0xFC, 0x00, 0x1F, 0xC0, 0x07, 0xF0, 0x00, 0x3C, 0x03, 0xC0, 0x0F, 0xE0,
0x07, 0xE0, 0x00, 0x3C, 0x03, 0xC0, 0x07, 0xE0, 0x0F, 0xC0, 0x00, 0x3C, 0x03, 0xC0, 0x03, 0xF0,
0x1F, 0x80, 0x00, 0x3C, 0x03, 0xC0, 0x01, 0xF8, 0x1F, 0x80, 0x00, 0x3F, 0xFC, 0x00, 0x01, 0xF8,
0x1F, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0xF8, 0x3E, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x7C,
0x3E, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x7C, 0x7E, 0x00, 0x00, 0x3C, 0x03, 0xC0, 0x00, 0x7E,
0x7C, 0x00, 0x00, 0x3C, 0x03, 0xC0, 0x00, 0x3E, 0x7C, 0x00, 0x00, 0x3C, 0x03, 0xC0, 0x00, 0x3E,
0x78, 0x00, 0x00, 0x3C, 0x03, 0xC0, 0x00, 0x1E, 0xF8, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x1F,
0xF8, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x1F,
0xF0, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0xF8, 0x78, 0x38, 0x78, 0xC4, 0x6C, 0x6C, 0x1F, 0xF8, 0xC4, 0x64, 0xC5, 0xBA, 0xDA, 0xDA, 0x1F,
0xF8, 0xDA, 0xDA, 0x69, 0x92, 0xDA, 0xCA, 0x1F, 0x78, 0xC4, 0xC2, 0x68, 0xC4, 0xDA, 0xD2, 0x1E,
0x7C, 0xDA, 0xDA, 0x68, 0x68, 0xDA, 0xDA, 0x3E, 0x7C, 0xC4, 0xDA, 0xC4, 0x68, 0x64, 0xDA, 0x3E,
0x7E, 0x78, 0x6C, 0x78, 0x30, 0x38, 0x6C, 0x7E, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C,
0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x1F, 0x81, 0x9E, 0xF3, 0x39, 0x90, 0x01, 0xF8,
0x0F, 0xC2, 0x50, 0x84, 0x92, 0x50, 0x03, 0xF0, 0x07, 0xE2, 0x5C, 0xE4, 0x13, 0xD0, 0x07, 0xE0,
0x07, 0xF2, 0x50, 0x84, 0x92, 0x50, 0x0F, 0xE0, 0x03, 0xF9, 0x90, 0x83, 0x3A, 0x5E, 0x1F, 0xC0,
0x01, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00,
0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x03, 0xFC, 0x00,
0x00, 0x1F, 0xE0, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00, 0x3F, 0xF0, 0x00,
0x00, 0x07, 0xFF, 0x00, 0x00, 0xFF, 0xE0, 0x00, 0x00, 0x01, 0xFF, 0xF0, 0x0F, 0xFF, 0x80, 0x00,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x00 };

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif



void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);


  display.clearDisplay();
  display.drawBitmap(30,1,logo16_glcd_bmp,64,64,1);
  display.display();
  //display.begin(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
  // testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop() {
  
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
	icons[f][XPOS] = random(display.width());
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}



void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    display.display();
  }
  delay(250);
}

