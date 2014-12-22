/**********************************************
Fonts for Sparkfun LCD 160x128
Andrew Gray

12-19-2014
**********************************************/

#ifndef fontsLCD_h
#define fontsLCD_h

#include "Arduino.h"


class fontsLCD
{
	public:
	fontsLCD();
	void no_pulse(int randx, int randy);
	void acquiring_pulse(int counter);
	void display_number(int num1, int num2, int num3);
    void toggleReverseMode();
    void setBacklight(byte duty);
    void clearScreen();

	private:

};

#endif

