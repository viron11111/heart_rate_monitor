


int beat = 2;
int acqr = 4;
int stby = 3;

unsigned long oldtime = 0;
unsigned long newtime = 0;
int beat_time = 0;
float BPM = 0.0;

boolean no_pulse_latch = 1;
boolean acq_pulse_latch = 0;
boolean beat_pulse_latch = 0;

long lastDebounceTime = 0;
long debounceDelay = 300;
int buttonState;
int lastButtonState = LOW;

void setup()
{
  attachInterrupt(0, BPM_timer, RISING);
  //attachInterrupt(1, no_pulse, RISING);
  pinMode(acqr, INPUT);
  //pinMode(beat, INPUT);
  pinMode(stby, INPUT);
  
  Serial.begin(115200);
  
  no_pulse();
}

void loop()
{
  //Serial.print(no_pulse_latch);
  //Serial.print(acq_pulse_latch);
  //Serial.println(beat_pulse_latch); 
  //Serial.println("start");

  if(no_pulse_latch == 0 && digitalRead(stby) == 1){
    if((millis() - lastDebounceTime) > debounceDelay){
      no_pulse();
    }    
  }
  else if (no_pulse_latch == 1 && acq_pulse_latch == 0 && beat_pulse_latch == 0 && digitalRead(acqr) == 1){  
    if((millis() - lastDebounceTime) > debounceDelay){
      acquiring();
    }    
  }
  else if (no_pulse_latch == 0 && acq_pulse_latch == 0 && beat_pulse_latch == 1){  
    attachInterrupt(1, no_pulse, RISING);
    beat_time = newtime - oldtime;
    BPM = 60 / (((float) beat_time) / 1000);
      
    if ((int) BPM >= 35 && (int) BPM <= 225){
      Serial.println((int) BPM);  
    }
  }
    

  //lastButtonState = digitalRead(acqr);
  delay(10);
}

void BPM_timer(){
  //Serial.println((int) BPM);
  no_pulse_latch = 0;
  acq_pulse_latch = 0;
  beat_pulse_latch = 1;
  oldtime = newtime;
  newtime = millis();
}

void no_pulse(){
  //delay(10);
  Serial.println("No pulse detected...");
  no_pulse_latch = 1;
  acq_pulse_latch = 0;
  beat_pulse_latch = 0;
  lastDebounceTime = millis();
  detachInterrupt(1);
}

void acquiring(){
  no_pulse_latch = 0;
  acq_pulse_latch = 1;
  beat_pulse_latch = 0;
  Serial.println("Acquiring pulse...");
  //Serial.print("deb time: ");
  //Serial.println(millis() - lastDebounceTime);
  lastDebounceTime = millis();
}
