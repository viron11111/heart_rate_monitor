t#include "Timer.h"
#include "fontsLCD.h"
#include <SoftwareSerial.h>

fontsLCD f;  //initialize font library
int no_pulse_counter = 0;
int beat_acquiring_counter = 0; //counter for adjusting screen saver
int change_number_counter = 0;
int heart_counter = 0;

Timer t;  //initialize timer library

int amount = 1000;
unsigned int a_read = 0;
float sum = 0.0;
float average = 0.0;
int i = 0;

long lastDebounceTime = 0;
long debounceDelay = 400;

boolean no_pulse_latch = 1;
boolean acq_pulse_latch = 0;
boolean beat_pulse_latch = 0;
boolean beat_latch = 0;
byte state = B0;
byte state_new;
byte state_old = B1111;

//Variables used to measure heart rate
unsigned long oldtime = 0;
unsigned long newtime = 0;
int beat_time = 0;
float BPM_new = 0.0;
float BPM_old = 0.0;
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

void setup() {
  //for acquiring hb screen
  randomSeed(analogRead(1));
  
  // initialize the serial communication:
  Serial.begin(115200);
  
  pinMode(2, INPUT); // Setup for leads off detection LO +
  pinMode(3, INPUT); // Setup for leads off detection LO -

  attachInterrupt(0, right_Hand_Detect, FALLING);
  
  lastDebounceTime = millis();
  //t.every(100, display);
}

void loop() {
  
  if (digitalRead(2) == 0 && digitalRead(3) == 0 && (millis() - lastDebounceTime) > debounceDelay && no_pulse_latch == 1){  //***************************** Hands detected *****************************
    hands_detected();
  }
  else if (acq_pulse_latch == 1 && digitalRead(2) == 0 && digitalRead(3) == 0){
    acquiring();
  }    
  else if (beat_pulse_latch == 1 && digitalRead(2) == 0 && digitalRead(3) == 0){
    measure_beat();
  }    
  else if (((digitalRead(2) == 1)||(digitalRead(3) == 1)) && (millis() - lastDebounceTime) > debounceDelay && (acq_pulse_latch == 1 || beat_pulse_latch == 1)){ //*************************** Hands Removed ***************************
    no_hands();
  }
  
  a_read = analogRead(A0);
  t.update();  //For updating timer used with diplaying graphic
  delay(1);
}


void hands_detected(){
  if(digitalRead(2) == 0 && digitalRead(3) == 0){  //Added to prevent "no pulse dectected during transition from acq to detected
    Serial.println("Hands detected...");
    no_pulse_latch = 0;
    acq_pulse_latch = 1;
    beat_pulse_latch = 0;
    state = B0;
    num1_old = 10;
    num2_old = 10;
    num3_old = 10;
    lastDebounceTime = millis();
    detachInterrupt(0); 
  }
}

void acquiring(){
  
  sum = 0.0;    
    
  for (i=0; i <= amount; i++){  
    sum = sum + analogRead(A0);
    delay(1);
  }    
  
  average = sum/amount;
  
  Serial.print("Average value = ");
  Serial.println(average);

  while(analogRead(A0) <= average + 20){
    if (digitalRead(2) == 1 || digitalRead(3) == 1){
      break;
    }
    delay(1);
  }  
  beat_time = newtime - oldtime;
  beat_latch = 1;
  
  Serial.println("First Beat");    
  
  no_pulse_latch = 0;
  acq_pulse_latch = 0;
  beat_pulse_latch = 1;     
  debounceDelay = 400;

  state = B10;
  lastDebounceTime = millis();
}

void measure_beat(){
  if (beat_latch == 0 && a_read >= (average+25) && (millis() - lastDebounceTime) > debounceDelay){
    newtime = millis();
    beat_time = newtime - oldtime;
    beat_latch = 1;
    lastDebounceTime = millis();
    oldtime = newtime;
    
    BPM = 60 / (((float) beat_time) / 1000);
    
    if ((BPM < 200.0) && (BPM > 40)){
      Serial.print("BPM: ");
      Serial.println(BPM);
    }
  }
  else if (beat_latch == 1 && a_read < average-20){
    beat_latch = 0;
  }
}

void no_hands(){
  Serial.print("Hands off device...");
  Serial.println(millis());
  no_pulse_latch = 1;
  acq_pulse_latch = 0;
  beat_pulse_latch = 0;
  average = 0.0;
  debounceDelay = 400;
  attachInterrupt(0, right_Hand_Detect, FALLING);
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

void right_Hand_Detect(){
  if(digitalRead(3) == 0 && no_pulse_latch == 1){
    lastDebounceTime = millis();
    //Serial.println(lastDebounceTime);
  }
}
