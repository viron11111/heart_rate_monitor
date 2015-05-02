/**********************************************
Fonts for Sparkfun LCD 160x128
Andrew Gray

12-19-2014
**********************************************/
#include "Arduino.h"
#include "fontsLCD.h"
#include <SoftwareSerial.h>

//initialize an instance of the SoftwareSerial library
SoftwareSerial serial(6,11);//change these two pin values to whichever pins you wish to use (RX, TX)

fontsLCD::fontsLCD()
{
	serial.begin(115200);
}
//-------------------------------------------------------------------------------------------
void eraseBlock(byte x1, byte y1, byte x2, byte y2)
{
  //This is just like the draw box command, except the contents of the box are erased to the background color
  delay(15);
  serial.write(0x7C);
  serial.write(0x05);//CTRL e
  serial.write(x1);
  serial.write(y1);
  serial.write(x2);
  serial.write(y2);
  delay(10);

}

void drawBox(byte x1, byte y1, byte x2, byte y2, byte set)
{
  //draws a box from two given points. You can set and reset just as the pixel function.
  delay(15);
  serial.write(0x7C);
  serial.write(0x0F);//CTRL o
  serial.write(x1);
  serial.write(y1);
  serial.write(x2);
  serial.write(y2);
  serial.write(0x01);
  delay(10);

}

void ball(int x, int y)
{
  serial.write(0x7C);
  serial.write(0x03);//CTRL c
  serial.write(x);
  serial.write(y);
  serial.write(8);
  serial.write(0x01);

  //delay(10);
}

void setHome()
{
  serial.write(0x7C);
  serial.write(0x18);
  serial.write((byte)0);//set x back to 0

  serial.write(0x7C);
  serial.write(0x19);
  serial.write((byte)0);//set y back to 0
}

void fontsLCD::clearScreen()
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
    serial.write(125);

    serial.write(0x7C);
    serial.write(0x19);//CTRL y
    serial.write(64);

    serial.print("BPM");
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
//***************Solid Numbers**********************************

void zero(int x)
{

    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=2; i<= 12; i++){
        drawLine(i+x, 34, i+x, 94, 1);
        drawLine(i+x+22, 34, i+x+22, 94, 1);
    }
    for (i=13; i<= 23; i++){
        drawLine(i+x, 34, i+x, 44, 1);
        drawLine(i+x, 84, i+x, 94, 1);
    }
}

void one(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=15; i<= 25; i++){
        drawLine(i+x, 34, i+x, 94, 1);
    }
}

void two(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 34+x, i, 1);
        drawLine(2+x, i+25, 34+x, i+25, 1);
        drawLine(2+x, i+50, 34+x, i+50, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x, 69, i+x, 84, 1);
        drawLine(i+x+22, 44, i+x+22, 59, 1);
    }
}

void three(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 34+x, i, 1);
        drawLine(2+x, i+25, 34+x, i+25, 1);
        drawLine(2+x, i+50, 34+x, i+50, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x+22, 44, i+x+22, 84, 1);
    }

}

void four(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=2; i<= 12; i++){
        drawLine(i+x, 34, i+x, 59, 1);
        drawLine(i+x+22, 34, i+x+22, 94, 1);
    }
    for (i=59; i<= 69; i++){
        drawLine(2+x, i, 24+x, i, 1);
    }

}

void five(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 34+x, i, 1);
        drawLine(2+x, i+25, 34+x, i+25, 1);
        drawLine(2+x, i+50, 34+x, i+50, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x, 44, i+x, 59, 1);
        drawLine(i+x+22, 69, i+x+22, 84, 1);
    }
}

void six(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 34+x, i, 1);
        drawLine(2+x, i+25, 34+x, i+25, 1);
        drawLine(2+x, i+50, 34+x, i+50, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x+22, 69, i+x+22, 94, 1);
        drawLine(i+x, 34, i+x, 94, 1);
    }
}

void seven(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 32+x, i, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x+22, 34, i+x+12, 94, 1);
    }

}

void eight(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 34+x, i, 1);
        drawLine(2+x, i+25, 34+x, i+25, 1);
        drawLine(2+x, i+50, 34+x, i+50, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x+22, 34, i+x+22, 94, 1);
        drawLine(i+x, 34, i+x, 94, 1);
    }
}

void nine(int x)
{
    eraseBlock(x+2, 34, x+34, 94);
    delay(100);
    //drawBox   (x+2, 34, x+34, 94, 1);
    //delay(10);
    int i = 0;
    for (i=34; i<= 44; i++){
        drawLine(2+x, i, 34+x, i, 1);
        drawLine(2+x, i+25, 34+x, i+25, 1);
        drawLine(2+x, i+50, 34+x, i+50, 1);
    }
    for (i=2; i<= 12; i++){
        drawLine(i+x+22, 34, i+x+22, 94, 1);
        drawLine(i+x, 34, i+x, 69, 1);
    }
}

//****************************************************************************
//Hollow numbers
/*
void zero(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(2+x, 94, 34+x, 94, 1);
    drawLine(12+x, 44, 24+x, 44, 1);
    drawLine(12+x, 84, 24+x, 84, 1);

    drawLine(2+x, 34, 2+x, 94, 1);
    drawLine(34+x, 34, 34+x, 94, 1);
    drawLine(12+x, 44, 12+x, 84, 1);
    drawLine(24+x, 44, 24+x, 84, 1);
}

void one(int x)
{
    delay(15);

    drawLine(15+x, 34, 15+x, 94, 1);
    drawLine(25+x, 34, 25+x, 94, 1);
    drawLine(15+x, 34, 25+x, 34, 1);
    drawLine(15+x, 94, 25+x, 94, 1);
}

void two(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(2+x, 44, 24+x, 44, 1);
    drawLine(2+x, 59, 24+x, 59, 1);
    drawLine(12+x, 69, 34+x, 69, 1);
    drawLine(12+x, 84, 34+x, 84, 1);
    drawLine(2+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 44, 1);
    drawLine(2+x, 59, 2+x, 94, 1);
    drawLine(12+x, 69, 12+x, 84, 1);
    drawLine(24+x, 44, 24+x, 59, 1);
    drawLine(34+x, 34, 34+x, 69, 1);
    drawLine(34+x, 84, 34+x, 94, 1);
}

void three(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(2+x, 44, 24+x, 44, 1);
    drawLine(2+x, 59, 24+x, 59, 1);
    drawLine(2+x, 69, 24+x, 69, 1);
    drawLine(2+x, 84, 24+x, 84, 1);
    drawLine(2+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 44, 1);
    drawLine(2+x, 59, 2+x, 69, 1);
    drawLine(2+x, 84, 2+x, 94, 1);
    drawLine(24+x, 44, 24+x, 59, 1);
    drawLine(24+x, 69, 24+x, 84, 1);
    drawLine(34+x, 34, 34+x, 94, 1);
}

void four(int x)
{
    delay(15);

    drawLine(2+x, 34, 12+x, 34, 1);
    drawLine(24+x, 34, 34+x, 34, 1);
    drawLine(12+x, 59, 24+x, 59, 1);
    drawLine(2+x, 69, 24+x, 69, 1);
    drawLine(24+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 69, 1);
    drawLine(12+x, 34, 12+x, 59, 1);
    drawLine(24+x, 34, 24+x, 59, 1);
    drawLine(24+x, 69, 24+x, 94, 1);
    drawLine(34+x, 34, 34+x, 94, 1);
}

void five(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(12+x, 44, 34+x, 44, 1);
    drawLine(12+x, 59, 34+x, 59, 1);
    drawLine(2+x, 69, 24+x, 69, 1);
    drawLine(2+x, 84, 24+x, 84, 1);
    drawLine(2+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 69, 1);
    drawLine(2+x, 84, 2+x, 94, 1);
    drawLine(12+x, 44, 12+x, 59, 1);
    drawLine(24+x, 69, 24+x, 84, 1);
    drawLine(34+x, 34, 34+x, 44, 1);
    drawLine(34+x, 59, 34+x, 94, 1);
}

void six(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(12+x, 44, 34+x, 44, 1);
    drawLine(12+x, 59, 34+x, 59, 1);
    drawLine(12+x, 69, 24+x, 69, 1);
    drawLine(12+x, 84, 24+x, 84, 1);
    drawLine(2+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 94, 1);
    drawLine(12+x, 69, 12+x, 84, 1);
    drawLine(12+x, 44, 12+x, 59, 1);
    drawLine(24+x, 69, 24+x, 84, 1);
    drawLine(34+x, 34, 34+x, 44, 1);
    drawLine(34+x, 59, 34+x, 94, 1);
}

void seven(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(2+x, 44, 22+x, 44, 1);
    drawLine(12+x, 94, 22+x, 94, 1);

    drawLine(22+x, 44, 12+x, 94, 1);
    drawLine(34+x, 34, 22+x, 94, 1);
    drawLine(2+x, 34, 2+x, 44, 1);
}

void eight(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(12+x, 44, 24+x, 44, 1);
    drawLine(12+x, 59, 24+x, 59, 1);
    drawLine(12+x, 69, 24+x, 69, 1);
    drawLine(12+x, 84, 24+x, 84, 1);
    drawLine(2+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 94, 1);
    drawLine(12+x, 69, 12+x, 84, 1);
    drawLine(12+x, 44, 12+x, 59, 1);
    drawLine(24+x, 69, 24+x, 84, 1);
    drawLine(24+x, 44, 24+x, 59, 1);
    drawLine(34+x, 34, 34+x, 94, 1);
}

void nine(int x)
{
    delay(15);

    drawLine(2+x, 34, 34+x, 34, 1);
    drawLine(12+x, 44, 24+x, 44, 1);
    drawLine(12+x, 59, 24+x, 59, 1);
    drawLine(2+x, 69, 24+x, 69, 1);
    drawLine(2+x, 84, 24+x, 84, 1);
    drawLine(2+x, 94, 34+x, 94, 1);

    drawLine(2+x, 34, 2+x, 69, 1);
    drawLine(2+x, 84, 2+x, 94, 1);
    drawLine(12+x, 44, 12+x, 59, 1);
    drawLine(24+x, 69, 24+x, 84, 1);
    drawLine(24+x, 44, 24+x, 59, 1);
    drawLine(34+x, 34, 34+x, 94, 1);
}
//**************************************************************************
*/

void no_pulse_words()
{
    serial.print("No pulse detected");
}

void acquire_pulse_words()
{
    serial.write(0x7C);
    serial.write(0x18);//CTRL x
    serial.write((byte)35);

    serial.write(0x7C);
    serial.write(0x19);//CTRL y
    serial.write((byte)34);

    //display "Acquiring pulse"
    delay(10);
    serial.print("Acquiring pulse");
}

void fontsLCD::no_pulse(int x, int y)//no pulse detected
{
    serial.write(0x7C);
    serial.write(0x18);//CTRL x
    serial.write(x);

    serial.write(0x7C);
    serial.write(0x19);//CTRL y
    serial.write(y);
    delay(10);
    no_pulse_words();
}

void fontsLCD::acquiring_pulse(int counter)//no pulse detected
{
    int x1 = 68, y1 = 58, x2 = 64, y2 = 55;
    switch (counter)
    {
        case 0:
            delay(10);
            eraseBlock(1+x2, 1+y2, 21+x2, 18+y2);
            delay(40);
            drawLine(7+x1, 3+y1, 5+x1, 1+y1, 1);
            drawLine(5+x1, 1+y1, 3+x1, 1+y1, 1);
            drawLine(3+x1, 1+y1, 1+x1, 3+y1, 1);
            drawLine(1+x1, 3+y1, 1+x1, 5+y1, 1);
            drawLine(1+x1, 5+y1, 7+x1, 11+y1, 1);
            drawLine(7+x1, 11+y1, 13+x1, 5+y1, 1);
            drawLine(13+x1, 5+y1, 13+x1, 3+y1, 1);
            drawLine(13+x1, 3+y1, 11+x1, 1+y1, 1);
            drawLine(11+x1, 1+y1, 9+x1, 1+y1, 1);
            drawLine(9+x1, 1+y1, 7+x1, 3+y1, 1);


            /*delay(20);
            eraseBlock(20, 70, 40, 90);
            delay(20);
            //drawBox   (20, 70, 40, 90, 1);
            delay(10);
            ball(60, 80);*/
            break;
        case 1:
            delay(10);
            eraseBlock(1+x1, 1+y1, 13+x1, 11+y1);
            delay(40);
            drawLine(11+x2, 3+y2, 10+x2, 2+y2, 1);
            drawLine(9+x2, 2+y2, 8+x2, 1+y2, 1);
            drawLine(8+x2, 1+y2, 4+x2, 1+y2, 1);
            drawLine(4+x2, 1+y2, 1+x2, 4+y2, 1);
            drawLine(1+x2, 4+y2, 1+x2, 8+y2, 1);
            drawLine(1+x2, 8+y2, 11+x2, 18+y2, 1);
            drawLine(11+x2, 18+y2, 21+x2, 8+y2, 1);
            drawLine(21+x2, 8+y2, 21+x2, 4+y2, 1);
            drawLine(21+x2, 4+y2, 18+x2, 1+y2, 1);
            drawLine(18+x2, 1+y2, 14+x2, 1+y2, 1);
            drawLine(14+x2, 1+y2, 13+x2, 2+y2, 1);
            drawLine(12+x2, 2+y2, 11+x2, 3+y2, 1);

            /*delay(20);
            eraseBlock(50, 70, 70, 90);
            delay(20);
            //drawBox   (50, 70, 70, 90, 1);
            delay(10);
            ball(30, 80);*/
            break;
        default:
            break;
    }

    delay(15);
    acquire_pulse_words();
}

void fontsLCD::display_number(int num1, int num2, int num3)
{
    switch (num1)
    {
        case 0:
            //zero(0);//display zero with x offset
            eraseBlock(2, 34, 34, 94);
            delay(100);
            break;
        case 1:
            one(0);//display zero with x offset
            break;
        case 2:
            two(0);//display zero with x offset
            break;
        default:
            break;
    }

    switch (num2)
    {
        case 0:
            zero(40);//display zero with x offset
            break;
        case 1:
            one(40);//display zero with x offset
            break;
        case 2:
            two(40);//display zero with x offset
            break;
        case 3:
            three(40);//display zero with x offset
            break;
        case 4:
            four(40);//display zero with x offset
            break;
        case 5:
            five(40);//display zero with x offset
            break;
        case 6:
            six(40);//display zero with x offset
            break;
        case 7:
            seven(40);//display zero with x offset
            break;
        case 8:
            eight(40);//display zero with x offset
            break;
        case 9:
            nine(40);//display zero with x offset
            break;
        default:
            break;
    }

    switch (num3)
    {
        case 0:
            zero(80);//display zero with x offset
            break;
        case 1:
            one(80);//display zero with x offset
            break;
        case 2:
            two(80);//display zero with x offset
            break;
        case 3:
            three(80);//display zero with x offset
            break;
        case 4:
            four(80);//display zero with x offset
            break;
        case 5:
            five(80);//display zero with x offset
            break;
        case 6:
            six(80);//display zero with x offset
            break;
        case 7:
            seven(80);//display zero with x offset
            break;
        case 8:
            eight(80);//display zero with x offset
            break;
        case 9:
            nine(80);//display zero with x offset
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


