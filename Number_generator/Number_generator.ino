/*
***************************************************
*************PASCO HAND GRIP HEART RATE************
***************************************************

By: Andrew Gray
Date started: December 19, 2014
*/
#include "Timer.h"
#include "fontsLCD.h"
#include <SoftwareSerial.h>

fontsLCD f;  //initialize font library
int counter = 0; //counter for adjusting screen saver

Timer t;  //initialize timer library

int beat = 2;  //Pin reading red LED (interrupt 0)
int acqr = 4;  //Pin reading green LED
int stby = 3;  //Pin reading yellow LED (interrupt 1)

//Variables used to measure heart rate
unsigned long oldtime = 0;
unsigned long newtime = 0;
int beat_time = 0;
float BPM = 0.0;
int num1 = 0;
int num2 = 0;
int num3 = 0;


int counter1 = 0;
int counter2 = 1;
int counter3 = 2;


void setup()
{
  //Default baudrate for Sparkfun LCD backpack (160x128 pixels)
  Serial.begin(115200);
  
  t.every(2000, display);

}

void loop()
{
  t.update();  //For updating timer used with diplaying graphic
}

void display(){  //Display current state onto LCD screen

  num1 = counter1;
  num2 = counter2;
  num3 = counter3;
  f.display_number(num1, num2, num3);
  
  counter1++;
  counter2++;
  counter3++;

  if (counter1 > 2){
    counter1 = 0;
  }
  if (counter2 > 9){
    counter2 = 0;
  }
  if (counter3 > 9){
    counter3 = 0;
  }



}
