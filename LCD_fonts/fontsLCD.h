/**********************************************
Fonts for Sparkfun LCD 160x128
Andrew Gray
ThemeWorks
12-19-2014
**********************************************/

#ifndef fontsLCD_h
#define fontsLCD_h

#include "Arduino.h"


class fontsLCD
{
	public:
	fontsLCD();
	void no_pulse(int counter);
	void acquiring_pulse(int counter);
	void display_number(int num1, int num2, int num3);
    void toggleReverseMode();
    void setBacklight(byte duty);
/*
	void nextLine();
	void clearScreen();
    void toggleReverseMode();
	void toggleSplash();
	void setBacklight(byte duty);
	void setBaud(byte baud);
	void restoreDefaultBaud();
  	void setX(byte posX);
	void setY(byte posY);
	void setHome();
	void demo();
	void setPixel(byte x, byte y, byte set);
	void drawLine(byte x1, byte y1, byte x2, byte y2, byte set);
	void drawBox(byte x1, byte y1, byte x2, byte y2, byte set);
	void drawCircle(byte x, byte y, byte rad, byte set);
	void eraseBlock(byte x1, byte y1, byte x2, byte y2); */


	private:




};

#endif

