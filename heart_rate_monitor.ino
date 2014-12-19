/*
***************************************************
*************PASCO HAND GRIP HEART RATE************
***************************************************

By: Andrew Gray
Date started: December 19, 2014
*/
int beat = 2;  //Pin reading red LED (interrupt 0)
int acqr = 4;  //Pin reading green LED
int stby = 3;  //Pin reading yellow LED (interrupt 1)

//Variables used to measure heart rate
unsigned long oldtime = 0;
unsigned long newtime = 0;
int beat_time = 0;
float BPM = 0.0;

//Latches used for different states
//program starts with no heart rate detected
boolean no_pulse_latch = 1;
boolean acq_pulse_latch = 0;
boolean beat_pulse_latch = 0;

//Variables used to debounce hand sensors
long lastDebounceTime = 0;
long debounceDelay = 300;  //minimum time required to transition between states

void setup()
{
  attachInterrupt(0, BPM_timer, RISING);  //Interrupt used to get accurate measurement for BPM

  //Place yellow and green LED pins as input
  pinMode(acqr, INPUT);
  pinMode(stby, INPUT);
  
  //Default baudrate for Sparkfun LCD backpack (160x128 pixels)
  Serial.begin(115200);
  
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
  
  //Heart rate detected, calculate BPM and display in debug window
  else if (no_pulse_latch == 0 && acq_pulse_latch == 0 && beat_pulse_latch == 1){  
    attachInterrupt(1, no_pulse, RISING);
    beat_time = newtime - oldtime;
    BPM = 60 / (((float) beat_time) / 1000);
      
    if ((int) BPM >= 35 && (int) BPM <= 225){
      Serial.println((int) BPM);  
    }
  }
  delay(10);
}

//Function for heart rate detection (red LED)
void BPM_timer(){
  no_pulse_latch = 0;
  acq_pulse_latch = 0;
  beat_pulse_latch = 1;
  oldtime = newtime;
  newtime = millis();
}

//Function run when no pulse detected (yellow LED)
void no_pulse(){
  Serial.println("No pulse detected...");
  no_pulse_latch = 1;
  acq_pulse_latch = 0;
  beat_pulse_latch = 0;
  lastDebounceTime = millis();
  detachInterrupt(1);
}

//Function for pulse detected but no beat yet (green LED)
void acquiring(){
  no_pulse_latch = 0;
  acq_pulse_latch = 1;
  beat_pulse_latch = 0;
  Serial.println("Acquiring pulse...");
  lastDebounceTime = millis();
}
