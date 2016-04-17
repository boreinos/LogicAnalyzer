/*
 * graphics.c
 */

#include "graphics.h"
#include "fonts.h"
#include "Lab7.h"
#include "color.h"

uint8_t xLine=2;
uint8_t Line=90;

extern void setArea(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
extern void writeData(uint8_t data);
extern uint8_t getScreenWidth();
extern uint8_t getScreenHeight();


uint8_t colorLowByte = 0;
uint8_t colorHighByte = 0;
uint8_t bgColorLowByte = 0;
uint8_t bgColorHighByte = 0;

//////////////////////
// color
//////////////////////

void setColor(uint16_t color) {
	colorLowByte = color;
	colorHighByte = color >> 8;
}

void setBackgroundColor(uint16_t color) {
	bgColorLowByte = color;
	bgColorHighByte = color >> 8;
}

/////////////////
// drawing
/////////////////

void clearScreen(uint8_t blackWhite) {
	uint8_t w = getScreenWidth();
	uint8_t h = getScreenHeight();
	setArea(0, 0, w - 1, h - 1);
	setBackgroundColor(blackWhite ? 0x0000 : 0xFFFF);

	while (h != 0) {
		while (w != 0) {
			writeData(bgColorHighByte);
			writeData(bgColorLowByte);
			w--;
		}
		w = getScreenWidth();
		h--;
	}
}
void clearChannel(uint8_t channel, uint8_t blackWhite){
	uint8_t x, y;
	x=21;
	switch(channel){
	case 1:
		y=17;
		break;
	case 2:
		y=33;
		break;
	case 3:
		y=49;
		break;
	case 4:
		y=65;
		break;
	default:
		y=17;
	}
	uint8_t w = 159;
	uint8_t h = 14;
	setArea(x, y, w - 1, h - 1);
	setBackgroundColor(blackWhite ? 0x0000 : 0xFFFF);
	while(h!=0){
		while(w!=0){
			writeData(bgColorHighByte);
			writeData(bgColorLowByte);
			w--;
		}
		w = 159;
		h--;
	}

}
void clearMsgBox(uint8_t msgLine, uint8_t blackWhite){
	uint8_t x, y;
	x=2;
	switch(msgLine){
	case 1:
		y=90;
		break;
	case 2:
		y=99;
		break;
	case 3:
		y=108;
		break;
	case 4:
		y=117;
		break;
	}
	uint8_t w = 159;
	uint8_t h = 8;
	setArea(x, y, w - 1, h - 1);
	setBackgroundColor(blackWhite ? 0x0000 : 0xFFFF);
	while(h!=0){
		while(w!=0){
			writeData(bgColorHighByte);
			writeData(bgColorLowByte);
			w--;
		}
		w = 159;
		h--;
	}

}

void drawPixel(uint8_t x, uint8_t y) {
	setArea(x, y, x, y);
	writeData(colorHighByte);
	writeData(colorLowByte);
}

/////////////////////////////
// Draw String - type: 0=Sm, 1=Md, 2=Lg, 3=Sm/Bkg, 4=Md/Bkg, 5=Lg/Bkg
/////////////////////////////
void drawString(uint8_t x, uint8_t y, char type, char *string) {
	uint8_t xs = x;
	switch (type) {
	case FONT_SM:
		while (*string) {
			drawCharSm(xs, y, *string++);
			xs += 6;
		}
		break;
	case FONT_MD:
		while (*string) {
			drawCharMd(xs, y, *string++);
			xs += 8;
		}
		break;
	case FONT_LG:
		while (*string) {
			drawCharLg(xs, y, *string++);
			xs += 12;
		}
		break;
	case FONT_SM_BKG:
		while (*string) {
			drawCharSmBkg(xs, y, *string++);
			xs += 6;
		}
		break;
	case FONT_MD_BKG:
		while (*string) {
			drawCharMdBkg(xs, y, *string++);
			xs += 8;
		}
		break;
	case FONT_LG_BKG:
		while (*string) {
			drawCharLgBkg(xs, y, *string++);
			xs += 12;
		}
		break;
	}
}

//////////////////////////
// 5x7 font - this function does not draw background pixels
//////////////////////////
void drawCharSm(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x01;
	uint8_t oc = c - 0x20;
	while (row < 8) {
		while (col < 5) {
			if (font_5x7[oc][col] & bit)
				drawPixel(x + col, y + row);
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 5x7 font - this function draws background pixels
////////////////
void drawCharSmBkg(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x01;
	uint8_t oc = c - 0x20;
	setArea(x, y, x + 4, y + 7); // if you want to fill column between chars, change x + 4 to x + 5

	while (row < 8) {
		while (col < 5) {
			if (font_5x7[oc][col] & bit) {
				//foreground
				writeData(colorHighByte);
				writeData(colorLowByte);
			} else {
				//background
				writeData(bgColorHighByte);
				writeData(bgColorLowByte);
			}
			col++;
		}
		// if you want to fill column between chars, writeData(bgColor) here
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 11x16 font - this function does not draw background pixels
////////////////
void drawCharLg(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint16_t bit = 0x0001;
	uint8_t oc = c - 0x20;
	while (row < 16) {
		while (col < 11) {
			if (font_11x16[oc][col] & bit)
				drawPixel(x + col, y + row);
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 11x16 font - this function draws background pixels
////////////////
void drawCharLgBkg(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint16_t bit = 0x0001;
	uint8_t oc = c - 0x20;
	setArea(x, y, x + 10, y + 15);
	while (row < 16) {
		while (col < 11) {
			if (font_11x16[oc][col] & bit) {
				//foreground
				writeData(colorHighByte);
				writeData(colorLowByte);
			} else {
				//background
				writeData(bgColorHighByte);
				writeData(bgColorLowByte);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 8x12 font - this function does not draw background pixels
////////////////
void drawCharMd(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x80;
	uint8_t oc = c - 0x20;
	while (row < 12) {
		while (col < 8) {
			if (font_8x12[oc][row] & bit)
				drawPixel(x + col, y + row);
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}
}

////////////////
// 8x12 font - this function draws background pixels
////////////////
void drawCharMdBkg(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x80;
	uint8_t oc = c - 0x20;
	setArea(x, y, x + 7, y + 11);
	while (row < 12) {
		while (col < 8) {
			if (font_8x12[oc][row] & bit) {
				//foreground
				writeData(colorHighByte);
				writeData(colorLowByte);
			} else {
				//background
				writeData(bgColorHighByte);
				writeData(bgColorLowByte);
			}
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}

}

////////////////////////
// images
////////////////////////
//data is 16 bit color
void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t * data) {

}

// lut is used, ?0 means skip, sort of a mask?
void drawImageLut(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data,
		uint16_t * lut) {

}

// each bit represents color, fg and bg colors are used, ?how about 0 as a mask?
void drawImageMono(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data) {

}

////////////////////////
// shapes
////////////////////////

void drawLogicLine(uint8_t x, uint8_t y, uint8_t length, uint8_t height,
		uint8_t * data) {
	uint8_t last = (*data & 0x80);
	uint8_t counter = 0;
	while (counter < length) {
		uint8_t bitCounter = 0;
		uint8_t byte = *data;
		while (bitCounter < 8 && counter < length) {
			if (last == (byte & 0x80)) {
				//draw pixel
				uint8_t h = (byte & 0x80) ? (height + y) : y;
				drawPixel(x + counter, h);
			} else {
				// draw line
				if (byte & 0x80) {
					drawLine(x + counter - 1, y, x + counter, y + height);
				} else {
					drawLine(x + counter - 1, y + height, x + counter, y);
				}
			}
			last = byte & 0x80;
			byte <<= 1;
			bitCounter++;
			counter++;
		}
		*data++;
	}
}

void drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

	uint8_t x0, x1, y0, y1;
	uint8_t d = 0;

// handle direction
	if (yStart > yEnd) {
		y0 = yEnd;
		y1 = yStart;
	} else {
		y1 = yEnd;
		y0 = yStart;
	}

	if (xStart > xEnd) {
		x0 = xEnd;
		x1 = xStart;
	} else {
		x1 = xEnd;
		x0 = xStart;
	}

// check if horizontal
	if (y0 == y1) {
		d = x1 - x0 + 1;
		setArea(x0, y0, x1, y1);
		while (d-- > 0) {
			writeData(colorHighByte);
			writeData(colorLowByte);
		}

	} else if (x0 == x1) { // check if vertical
		d = y1 - y0 + 1;
		setArea(x0, y0, x1, y1);
		while (d-- > 0) {
			writeData(colorHighByte);
			writeData(colorLowByte);
		}

	} else { // angled
		char dx, dy;
		int sx, sy;

		if (xStart < xEnd) {
			sx = 1;
			dx = xEnd - xStart;
		} else {
			sx = -1;
			dx = xStart - xEnd;
		}

		if (yStart < yEnd) {
			sy = 1;
			dy = yEnd - yStart;
		} else {
			sy = -1;
			dy = yStart - yEnd;
		}

		int e1 = dx - dy;
		int e2;

		while (1) {
			drawPixel(xStart, yStart);
			if (xStart == xEnd && yStart == yEnd)
				break;
			e2 = 2 * e1;
			if (e2 > -dy) {
				e1 = e1 - dy;
				xStart = xStart + sx;
			}
			if (e2 < dx) {
				e1 = e1 + dx;
				yStart = yStart + sy;
			}
		}
	}
}

void drawRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

	drawLine(xStart, yStart, xEnd, yStart);
	drawLine(xStart, yEnd, xEnd, yEnd);
	drawLine(xStart, yStart, xStart, yEnd);
	drawLine(xEnd, yStart, xEnd, yEnd);
}

void drawHeart(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {
	uint8_t width, height, xFrac, yFrac;
	width = xEnd - xStart;
	height = yEnd - yStart;
	xFrac = width / 4;
	yFrac = height / 5;

	drawLine(xStart,         yStart+yFrac,  xStart+xFrac,   yStart);
	drawLine(xStart+xFrac,   yStart,        xStart+2*xFrac, yStart+yFrac);
	drawLine(xStart+2*xFrac, yStart+yFrac,  xStart+3*xFrac, yStart);
	drawLine(xStart+3*xFrac, yStart,        xStart+width,   yStart+yFrac);
	drawLine(xStart,         yStart+yFrac,  xStart+2*xFrac, yStart+height);
	drawLine(xStart+2*xFrac, yStart+height, xStart+width,   yStart+yFrac);
}

void drawCircle(uint8_t x, uint8_t y, uint8_t radius) {
	int dx = radius;
	int dy = 0;
	int xChange = 1 - 2 * radius;
	int yChange = 1;
	int radiusError = 0;
	while (dx >= dy) {
		drawPixel(x + dx, y + dy);
		drawPixel(x - dx, y + dy);
		drawPixel(x - dx, y - dy);
		drawPixel(x + dx, y - dy);
		drawPixel(x + dy, y + dx);
		drawPixel(x - dy, y + dx);
		drawPixel(x - dy, y - dx);
		drawPixel(x + dy, y - dx);
		dy++;
		radiusError += yChange;
		yChange += 2;
		if (2 * radiusError + xChange > 0) {
			dx--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

/////////////////////////
// fill
/////////////////////////

void fillRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {
	setArea(xStart, yStart, xEnd, yEnd);
	uint16_t total = (xEnd - xStart + 1) * (yEnd - yStart + 1);
	uint16_t c = 0;
	while (c < total) {
		writeData(colorHighByte);
		writeData(colorLowByte);
		c++;
	}
}

void fillCircle(uint8_t x, uint8_t y, uint8_t radius) {
	int dx = radius;
	int dy = 0;
	int xChange = 1 - 2 * radius;
	int yChange = 1;
	int radiusError = 0;
	while (dx >= dy) {
		drawLine(x + dy, y + dx, x - dy, y + dx);
		drawLine(x - dy, y - dx, x + dy, y - dx);
		drawLine(x - dx, y + dy, x + dx, y + dy);
		drawLine(x - dx, y - dy, x + dx, y - dy);
		dy++;
		radiusError += yChange;
		yChange += 2;
		if (2 * radiusError + xChange > 0) {
			dx--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// APPENDED FUNCTIONS BORIS REINOSA
/////////////////////////////////////////////////////////////////////////////////////////////////////

void printKey(void){
	setColor(COLOR_16_WHITE);
	switch(key){
	case 0:
		drawString(xLine, Line, FONT_SM, "0");
		break;
	case 1:
		drawString(xLine, Line, FONT_SM, "1");
		break;
	case 2:
		drawString(xLine, Line, FONT_SM, "2");
		break;
	case 3:
		drawString(xLine, Line, FONT_SM, "3");
		break;
	case 4:
		drawString(xLine, Line, FONT_SM, "4");
		break;
	case 5:
		drawString(xLine, Line, FONT_SM, "5");
		break;
	case 6:
		drawString(xLine, Line, FONT_SM, "6");
		break;
	case 7:
		drawString(xLine, Line, FONT_SM, "7");
		break;
	case 8:
		drawString(xLine, Line, FONT_SM, "8");
		break;
	case 9:
		drawString(xLine, Line, FONT_SM, "9");
		break;
	case 10:
		drawString(xLine, Line, FONT_SM, "A");
		break;
	case 11:
		drawString(xLine, Line, FONT_SM, "B");
		break;
	case 12:
		drawString(xLine, Line, FONT_SM, "C");
		break;
	case 13:
		drawString(xLine, Line, FONT_SM, "D");
		break;
	default:
		drawString(xLine, Line, FONT_SM, "test!");
		break;
		// clear the message area of channel
	}
	xLine+=6;
	if(xLine>148){
		xLine =2;
		Line +=9;
	}
}
void printChannel(uint8_t page, uint8_t channel){
	uint16_t i;
	uint16_t x=25;
	uint8_t y;
	uint8_t yend;
	uint8_t state;
	uint8_t chLow;
	uint8_t chHigh;
	uint8_t  *channelptr;

	switch(channel){
	case 1: //high is at y =18
		setColor(COLOR_16_BLUE);
		clearChannel(1,1);
		chLow=ch1Low;
		chHigh=ch1High;
		channelptr= &channel1[0];
		break;
	case 2:

		setColor(COLOR_16_ORANGE_RED);
		clearChannel(2,1);
		chLow=ch2Low;
		chHigh=ch2High;
		channelptr= &channel2[0];
		break;
	case 3:
		setColor(COLOR_16_GREEN);
		clearChannel(3,1);
		chLow=ch3Low;
		chHigh=ch3High;
		channelptr= &channel3[0];
		break;
	case 4:
		setColor(COLOR_16_YELLOW);
		clearChannel(4,1);
		chLow=ch4Low;
		chHigh=ch4High;
		channelptr=&channel4[0];
		break;
	}
	switch(page){
	case 1:
		break;
	case 2:
		channelptr +=135;
		break;
	case 3:
		channelptr +=269;
		break;
	}
	//check for original state:
	if (channel1[0]==0){
		y=chLow;
		state=0;
	}else{
		y=chHigh;
		state=1;
	}
	for (i=0; i<134; i++){
		if(state != *channelptr){
			//draw existing line then draw change:
			if(state==0){
				yend=chLow;
				drawLine(x,y,i+25,yend);
				//jump:
				x=i+25;
				yend=chHigh;
				drawLine(x,y,x,yend);
				//now prepare to change the other way:
				y=yend;
			}else{
				yend=chHigh;
				drawLine(x,y,i+25,yend);
				//drop:
				x=i+25;
				yend=chLow;
				drawLine(x,y,x,yend);
				y=yend;
			}
			//toggle the state:
			state=1-state;
		}
		channelptr++;
		if(i==133){
			if(state==0)
				yend=chLow;
			else
				yend=chHigh;
			drawLine(x,yend,i+25,yend);
		}
	}
}
