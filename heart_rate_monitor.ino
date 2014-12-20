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

//Latches used for different states
//program starts with no heart rate detected
boolean no_pulse_latch = 1;
boolean acq_pulse_latch = 0;
boolean beat_pulse_latch = 0;
byte state = B0;

//Variables used to debounce hand sensors
long lastDebounceTime = 0;
long debounceDelay = 300;  //minimum time required to transition between states

void setup()
{
  randomSeed(analogRead(0));
  
  attachInterrupt(0, BPM_timer, RISING);  //Interrupt used to get accurate measurement for BPM

  //Place yellow and green LED pins as input
  pinMode(acqr, INPUT);
  pinMode(stby, INPUT);
  pinMode(beat, INPUT);
  
  //Default baudrate for Sparkfun LCD backpack (160x128 pixels)
  Serial.begin(115200);
  
  t.every(500, display);
  
  //intialize state to no heart beat detected
  no_pulse();
}

void loop()
{

  //No pulse detection, if statement is true when transistioning from green to yellow or red to yellow
  //only run once (during transition)
  if(no_pulse_latch == 0 && digitalRead(stby) == 1){
    if((millis() - lastDebounceTime) > debounceDelay){
      no_pulse();
    }    
  }
  
  //Acquiring pulse, green led, run once when transitioning from yellow to green
  else if (no_pulse_latch == 1 && acq_pulse_latch == 0 && beat_pulse_latch == 0 && digitalRead(acqr) == 1){  
    if((millis() - lastDebounceTime) > debounceDelay){
      acquiring();
    }    
  }
  
  //Heart rate detected, calculate BPM 
  else if (no_pulse_latch == 0 && acq_pulse_latch == 0 && beat_pulse_latch == 1){  
    attachInterrupt(1, no_pulse, RISING);
    beat_time = newtime - oldtime;
    BPM = 60 / (((float) beat_time) / 1000);
  }
  t.update();  //For updating timer used with diplaying graphic
}

void display(){  //Display current state onto LCD screen
  if ((int) BPM >= 35 && (int) BPM <= 225 && beat_pulse_latch == 1 && state == B11){
    Serial.println((int) BPM);  
    num1 = (int)BPM / 100;
    num2 = ((int)BPM - (num1*100)) / 10;
    num3 = ((int)BPM - (num1*100)) % 10 ; 
    f.display_number(num1, num2, num3);
    //Serial.println(num1);
    //Serial.println(num2);
    //Serial.println(num3);
  }
  else if (state == B10){
    //Serial.println("Acquiring pulse...");
    f.acquiring_pulse(counter);
    //state = B100;
  }
  else if (state == B00){
    //Serial.println("No pulse detected...");
    int randx = random(1, 50);
    int randy = random(1, 114);
    f.no_pulse(counter, randx, randy);
    //state = B100;
  }
  counter ++;
  if (counter >= 4){
    counter = 0;
  }
}

//Function for heart rate detection (red LED)
void BPM_timer(){
  no_pulse_latch = 0;
  acq_pulse_latch = 0;
  beat_pulse_latch = 1;
  state = B11;
  oldtime = newtime;
  newtime = millis();
}

//Function run when no pulse detected (yellow LED)
void no_pulse(){
  if(digitalRead(stby) == 1 and digitalRead(beat) != 1){  //Added to prevent "no pulse dectected during transition from acq to detected
    //Serial.println("No pulse detected...");
    no_pulse_latch = 1;
    acq_pulse_latch = 0;
    beat_pulse_latch = 0;
    state = B0;
    lastDebounceTime = millis();
    detachInterrupt(1);
  }
}

//Function for pulse detected but no beat yet (green LED)
void acquiring(){
  no_pulse_latch = 0;
  acq_pulse_latch = 1;
  beat_pulse_latch = 0;
  //Serial.println("Acquiring pulse...");
  state = B10;
  lastDebounceTime = millis();
}
