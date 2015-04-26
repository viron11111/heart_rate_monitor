int amount = 1000;
unsigned int a_read = 0;
float sum = 0.0;
float average = 0.0;
int i = 0;

long lastDebounceTime = 0;
long debounceDelay = 400;

long counter = 0;

boolean no_pulse_latch = 1;
boolean acq_pulse_latch = 0;
boolean beat_pulse_latch = 0;
boolean beat_latch = 0;

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

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(2, INPUT); // Setup for leads off detection LO +
  pinMode(3, INPUT); // Setup for leads off detection LO -

  attachInterrupt(0, right_Hand_Detect, FALLING);
  
  i = 0;
}

void loop() {
  
  if (digitalRead(2) == 0 && digitalRead(3) == 0 && (millis() - lastDebounceTime) > debounceDelay && no_pulse_latch == 1){  //***************************** Hands detected *****************************
    Serial.print("detecting beat...");
    Serial.println(millis());
    no_pulse_latch = 0;
    acq_pulse_latch = 1;
    beat_pulse_latch = 0;    
    beat_latch = 0;
    
    lastDebounceTime = millis();
    detachInterrupt(0); 
    //attachInterrupt(1, hands_Off, RISING);   
  }
  else if (acq_pulse_latch == 1 && digitalRead(2) == 0 && digitalRead(3) == 0){
    sum = 0.0;    
    
    for (i=0; i <= amount; i++){  
      sum = sum + analogRead(A0);
      delay(1);
    }    
    
    average = sum/amount;
    
    Serial.print("Average value = ");
    Serial.println(average);

    while(analogRead(A0) <= average + 20){
      delay(1);
    }  
    beat_time = newtime - oldtime;
    beat_latch = 1;
    
    Serial.println("First Beat");    
    
    no_pulse_latch = 0;
    acq_pulse_latch = 0;
    beat_pulse_latch = 1;     
    debounceDelay = 400;
  }  
  
  else if (beat_pulse_latch == 1 && digitalRead(2) == 0 && digitalRead(3) == 0){
    int difference = 0;
    difference = a_read - average;
    /*Serial.print("average: ");
    Serial.print(average);
    Serial.print(" a_read: ");
    Serial.print(a_read);
    Serial.print(" difference: ");
    Serial.println(difference);
    delay(100);*/

    //Serial.println(difference);
    if (beat_latch == 0 && a_read >= (average+25) && (millis() - lastDebounceTime) > debounceDelay){
      newtime = millis();
      beat_time = newtime - oldtime;
      //Serial.print(difference);
      //Serial.println(" Beat time");
      beat_latch = 1;
      lastDebounceTime = millis();
      oldtime = newtime;
      
      BPM = 60 / (((float) beat_time) / 1000);
      Serial.print("BPM: ");
      Serial.println(BPM);
    }
    else if (beat_latch == 1 && a_read < average-20){
      beat_latch = 0;
      //Serial.println("cleared latch....");
      
    }
    

    
  }  
  
  
  
  else if (((digitalRead(2) == 1)||(digitalRead(3) == 1)) && (millis() - lastDebounceTime) > debounceDelay && (acq_pulse_latch == 1 || beat_pulse_latch == 1)){ //*************************** Hands Removed ***************************
    Serial.print("Hands off device...");
    Serial.println(millis());
    no_pulse_latch = 1;
    acq_pulse_latch = 0;
    beat_pulse_latch = 0;
    average = 0.0;
    debounceDelay = 400;
    attachInterrupt(0, right_Hand_Detect, FALLING);
  }
  
  a_read = analogRead(A0);
  delay(1);

}

void right_Hand_Detect(){
  if(digitalRead(3) == 0 && no_pulse_latch == 1){
    lastDebounceTime = millis();
    //Serial.println(lastDebounceTime);
  }
}
