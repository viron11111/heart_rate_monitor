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
int no_pulse_counter = 0;
int beat_acquiring_counter = 0; //counter for adjusting screen saver
int change_number_counter = 0;
int heart_counter = 0;

Timer t;  //initialize timer library

int beat = 2;  //Pin reading red LED (interrupt 0)
int acqr = 4;  //Pin reading green LED
int stby = 3;  //Pin reading yellow LED (interrupt 1)

//Variables used to measure heart rate
unsigned long oldtime = 0;
unsigned long newtime = 0;
int beat_time = 0;
float BPM = 0.0;
int num1_old = 10;
int num2_old = 10;
int num3_old = 10;
int num1_new = 0;
int num2_new = 0;
int num3_new = 0;
int send1 = 10;
int send2 = 10;
int send3 = 10;


//Latches used for different states
//program starts with no heart rate detected
boolean no_pulse_latch = 1;
boolean acq_pulse_latch = 0;
boolean beat_pulse_latch = 0;
byte state = B0;
byte state_new;
byte state_old = B1111;

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
  
  t.every(100, display);
  
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
  
  state_new = state;
  
  if (state_new != state_old){
    f.clearScreen();
  }
  
  if ((int) BPM >= 35 && (int) BPM <= 225 && beat_pulse_latch == 1 && state == B11 && change_number_counter >= 21){
    //Serial.println((int) BPM);  
    num1_new = (int)BPM / 100;
    num2_new = ((int)BPM - (num1_new*100)) / 10;
    num3_new = ((int)BPM - (num1_new*100)) % 10 ; 
    
    if (num1_new != num1_old){
      send1 = num1_new;
    }
    else
      send1 = 10;
      
    if (num2_new != num2_old){
      send2 = num2_new;
    }
    else
      send2 = 10;

    if (num3_new != num3_old){
      send3 = num3_new;
    }
    else
      send3 = 10;      
      
    //f.clearScreen();
    f.display_number(send1, send2, send3);
    change_number_counter = 0; 

    num1_old = num1_new;
    num2_old = num2_new;
    num3_old = num3_new;
    
    //Serial.println(num1);
    //Serial.println(num2);
    //Serial.println(num3);
  }
  else if (state == B10 && beat_acquiring_counter >= 6){
    //Serial.println(beat_acquiring_counter);
    
    //f.clearScreen();
    f.acquiring_pulse(heart_counter);
    beat_acquiring_counter = 0;    
    heart_counter++;
    if (heart_counter >= 2){
      heart_counter = 0;
    }
    //state = B100;
  }
  else if (state == B00 && no_pulse_counter >= 21){
    //Serial.println("No pulse detected...");
    int randx = random(6, 55);
    int randy = random(34, 85);
    
    f.clearScreen();
    f.no_pulse(randx, randy);
    no_pulse_counter = 0;    
    //state = B100;
  }
  
  change_number_counter++;
  no_pulse_counter++;
  beat_acquiring_counter++;  
  state_old = state_new;
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
    num1_old = 0;
    num2_old = 0;
    num3_old = 0;
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
