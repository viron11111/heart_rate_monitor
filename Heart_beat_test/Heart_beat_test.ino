#include "Timer.h"
#include "fontsLCD.h"
#include <SoftwareSerial.h>

fontsLCD f;  //initialize font library
int no_pulse_counter = 0;
int beat_acquiring_counter = 0; //counter for adjusting screen saver
int change_number_counter = 0;
int heart_counter = 0;

Timer t;  //initialize timer library

int amount = 1500;
unsigned int a_read = 0;
float sum = 0.0;
float average = 0.0;
int i = 0;

long lastDebounceTime = 0;
long debounceDelay = 1500;

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
int high_value = 0;
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
  
  t.every(100, display);
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
    //Serial.println("Hands detected...");
    no_pulse_latch = 0;
    acq_pulse_latch = 1;
    beat_pulse_latch = 0;
    state = B10;
    num1_old = 10;
    num2_old = 10;
    num3_old = 10;
    lastDebounceTime = millis();
    detachInterrupt(0); 
    //attachInterrupt(1, no_hands, RISING);
  }
}

void acquiring(){
  state = B10;
  sum = 0.0;   
  high_value = 0;
    
  for (i=0; i <= amount; i++){
    if( analogRead(A0) > high_value){
      high_value = analogRead(A0);
    }
    sum = sum + analogRead(A0);
    t.update();  //For updating timer used with diplaying graphic
    delay(1);
  }    
  
  average = sum/amount;
  Serial.print("Average value = ");
  Serial.println(average);
  Serial.print("high value = ");
  Serial.println(high_value);

  while(analogRead(A0) <= average + 25){
    if (digitalRead(2) == 1 || digitalRead(3) == 1){
      break;
    }
    t.update();  //For updating timer used with diplaying graphic
    delay(1);
  }  
  

  beat_time = newtime - oldtime;
  beat_latch = 1;
  
  debounceDelay = 350;  //prevents multiple beat interruptions (too long and you may miss a beat)
 
  //Serial.println("First Beat");    
  
  no_pulse_latch = 0;
  acq_pulse_latch = 0;
  beat_pulse_latch = 1;    
  lastDebounceTime = millis();
  
  change_number_counter = 21;  //improve transition time from acq to measuring beat time
  BPM_old = 0.0;
  if (digitalRead(2) == 1 || digitalRead(3) == 1){
    no_hands();
  }  
}

void measure_beat(){
  
  t.update();  //For updating timer used with diplaying graphic
  if (beat_latch == 0 && a_read >= (average+40) && (millis() - lastDebounceTime) > debounceDelay){
    state = B11;
    newtime = millis();
    beat_time = newtime - oldtime;    
    lastDebounceTime = millis();
    oldtime = newtime;
    
    BPM = 60 / (((float) beat_time) / 1000);
    beat_latch = 1;    
    //Serial.print("BPM_old: ");
    //Serial.println(BPM_old);    
    //Serial.print("BPM_new: ");
    //Serial.println(BPM_new);
    
    /*if (BPM_old < 1){
      beat_latch = 0;
      BPM_old = BPM_new;
      BPM = 0.0;
      beat_latch = 0;
    }
    else{
      state = B11;
      if (abs(BPM_old - BPM_new) > 15){
        BPM = (BPM_old + BPM_new)/2.0;
        BPM_old = BPM_new;
      }
      else{
        BPM = BPM_new;
        BPM_old = BPM_new;
      }
      beat_latch = 1;
    }*/
    
    
  }
  else if (beat_latch == 1 && a_read < average-20){
    beat_latch = 0;
  }
}

void no_hands(){
  //detachInterrupt(1);
  debounceDelay = 1500;
  state = B0;
  no_pulse_latch = 1;
  acq_pulse_latch = 0;
  beat_pulse_latch = 0;
  average = 0.0;
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
    //heart_counter = 0;
    heart_counter++;
    if (heart_counter >= 2){
      heart_counter = 0;
    }
    //state = B100;
  }
  else if (state == B0 && no_pulse_counter >= 21){
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
    lastDebounceTime = millis();
}
