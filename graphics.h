/*
 * graphics.h
 */
 
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <stdint.h>

// font sizes
#define FONT_SM		0
#define FONT_MD		1
#define FONT_LG		2
#define FONT_SM_BKG	3
#define FONT_MD_BKG	4
#define FONT_LG_BKG	5

// channel locations:
#define ch1Low 30
#define ch1High 18
#define ch2Low 46
#define ch2High 34
#define ch3Low 62
#define ch3High 50
#define ch4Low 78
#define ch4High 66




void setColor(uint16_t color);
void setBackgroundColor(uint16_t color);

void clearScreen(uint8_t blackWhite);
void clearChannel(uint8_t channel, uint8_t blackWhite);
void clearMsgBox(uint8_t msgLine, uint8_t blackWhite);

void drawPixel(uint8_t x, uint8_t y);
void drawString(uint8_t x, uint8_t y, char type, char *string);
void drawCharLg(uint8_t x, uint8_t y, char c);
void drawCharMd(uint8_t x, uint8_t y, char c);
void drawCharSm(uint8_t x, uint8_t y, char c);
void drawCharLgBkg(uint8_t x, uint8_t y, char c);
void drawCharMdBkg(uint8_t x, uint8_t y, char c);
void drawCharSmBkg(uint8_t x, uint8_t y, char c);
void drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void drawRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void drawHeart(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void drawCircle(uint8_t x, uint8_t y, uint8_t radius);

void fillRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void fillCircle(uint8_t x, uint8_t y, uint8_t radius);

void drawLogicLine(uint8_t x, uint8_t y, uint8_t length, uint8_t height, uint8_t * data);

void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t * data);
void drawImageLut(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data, uint16_t * lut);
void drawImageMono(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data);

///////////////////////////////
////////APPENDED BR
///////////////////////////////
void printChannel(uint8_t page, uint8_t channel);
void printKey(void);

#endif /* GRAPHICS_H_ */
