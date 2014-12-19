/**********************************************
Fonts for Sparkfun LCD 160x128
Andrew Gray
ThemeWorks
12-19-2014
**********************************************/
#include "Arduino.h"
#include "fontsLCD.h"
#include <SoftwareSerial.h>

//initialize an instance of the SoftwareSerial library
SoftwareSerial serial(6,5);//change these two pin values to whichever pins you wish to use (RX, TX)

fontsLCD::fontsLCD()
{
	serial.begin(115200);
}
//-------------------------------------------------------------------------------------------
void ball(int x, int y)
{
  serial.write(0x7C);
  serial.write(0x03);//CTRL c
  serial.write(x+20);
  serial.write(y+20);
  serial.write(10);
  serial.write(0x01);
  //delay(10);
}

void clearScreen()
{
  //clears the screen, you will use this a lot!
  serial.write(0x7C);
  serial.write((byte)0); //CTRL @
  //can't send LCD.write(0) or LCD.write(0x00) because it's interprestted as a NULL
}

void BPM()
{
    //display BPM words
    serial.write(0x7C);
    serial.write(0x18);//CTRL x
    serial.write(120);

    serial.write(0x7C);
    serial.write(0x19);//CTRL y
    serial.write(64);

    serial.print("BPM");
}

void zero(int x)
{


}

void one(int x)
{


}

void two(int x)
{


}

void three(int x)
{


}

void four(int x)
{


}

void five(int x)
{


}

void six(int x)
{


}

void seven(int x)
{


}

void eight(int x)
{


}

void nine(int x)
{


}

void no_pulse_words()
{
    serial.write(0x7C);
    serial.write(0x18);//CTRL x
    serial.write(40);

    serial.write(0x7C);
    serial.write(0x19);//CTRL y
    serial.write(1);

    //display "No pulse detected"
    serial.print("No pulse detected");
}

void acquire_pulse_words()
{
    serial.write(0x7C);
    serial.write(0x18);//CTRL x
    serial.write(40);

    serial.write(0x7C);
    serial.write(0x19);//CTRL y
    serial.write(1);

    //display "Acquiring pulse"
    serial.print("Acquiring pulse");
}

void fontsLCD::no_pulse(int counter)//no pulse detected
{
    int y1 = 88, y2 = 88, y3 = 88, y4 = 88;
    switch (counter)
    {
        case 0:
            y1 = 48;
            break;
        case 1:
            y2 = 48;
            break;
        case 2:
            y3 = 48;
            break;
        case 3:
            y4 = 48;
            break;
    }
    clearScreen();
    no_pulse_words();
    ball(0, y1);
    ball(40, y2);
    ball(80, y3);
    ball(120, y4);
}

void fontsLCD::acquiring_pulse(int counter)//no pulse detected
{
    int y1 = 88, y2 = 88, y3 = 88, y4 = 88;
    switch (counter)
    {
        case 0:
            y1 = 48;
            break;
        case 1:
            y2 = 48;
            break;
        case 2:
            y3 = 48;
            break;
        case 3:
            y4 = 48;
            break;
    }
    clearScreen();
    acquire_pulse_words();
    ball(0, y1);
    ball(40, y2);
    ball(80, y3);
    ball(120, y4);
}

void fontsLCD::display_number(int num1, int num2, int num3)
{
    clearScreen();
    switch (num1)
    {
        case 0:
            zero(0);//display zero with x offset
            break;
        case 1:
            one(0);//display zero with x offset
            break;
        case 2:
            two(0);//display zero with x offset
            break;
        case 3:
            three(0);//display zero with x offset
            break;
        case 4:
            four(0);//display zero with x offset
            break;
        case 5:
            five(0);//display zero with x offset
            break;
        case 6:
            six(0);//display zero with x offset
            break;
        case 7:
            seven(0);//display zero with x offset
            break;
        case 8:
            eight(0);//display zero with x offset
            break;
        case 9:
            nine(0);//display zero with x offset
            break;
        default:
            break;
    }

    switch (num2)
    {
        case 0:
            zero(0);//display zero with x offset
            break;
        case 1:
            one(0);//display zero with x offset
            break;
        case 2:
            two(0);//display zero with x offset
            break;
        case 3:
            three(0);//display zero with x offset
            break;
        case 4:
            four(0);//display zero with x offset
            break;
        case 5:
            five(0);//display zero with x offset
            break;
        case 6:
            six(0);//display zero with x offset
            break;
        case 7:
            seven(0);//display zero with x offset
            break;
        case 8:
            eight(0);//display zero with x offset
            break;
        case 9:
            nine(0);//display zero with x offset
            break;
        default:
            break;
    }

    switch (num3)
    {
        case 0:
            zero(0);//display zero with x offset
            break;
        case 1:
            one(0);//display zero with x offset
            break;
        case 2:
            two(0);//display zero with x offset
            break;
        case 3:
            three(0);//display zero with x offset
            break;
        case 4:
            four(0);//display zero with x offset
            break;
        case 5:
            five(0);//display zero with x offset
            break;
        case 6:
            six(0);//display zero with x offset
            break;
        case 7:
            seven(0);//display zero with x offset
            break;
        case 8:
            eight(0);//display zero with x offset
            break;
        case 9:
            nine(0);//display zero with x offset
            break;
        default:
            break;
    }
    BPM();

}
//-------------------------------------------------------------------------------------------

void fontsLCD::toggleReverseMode()
{
  //Everything that was black is now white and vise versa
  serial.write(0x7C);
  serial.write(0x12); //CTRL r
}

void fontsLCD::setBacklight(byte duty)
{
  //changes the back light intensity, range is 0-100.
  serial.write(0x7C);
  serial.write(0x02); //CTRL b
  serial.write(duty); //send a value of 0 - 100
}

void drawLine(byte x1, byte y1, byte x2, byte y2, byte set)
{
  //draws a line from two given points. You can set and reset just as the pixel function.
  serial.write(0x7C);
  serial.write(0x0C);//CTRL l
  serial.write(x1);
  serial.write(y1);
  serial.write(x2);
  serial.write(y2);
  serial.write(0x01);
  delay(10);

}


