#include <MuxShield.h> 
#include <Wire.h>   //To enable the use of the Arduino's timer 

MuxShield muxShield; 

long duration, distance;
unsigned long pulse_length, timestampPulseGenerated, timestampPulseReceived, interval, distanceToObject; 
int i;
int led = 13;
float ultrasonicValues[6] = {0,0,0,0,0,0}; 

char inbyte = 0; 

void setup() {
Serial.begin(9600);
muxShield.setMode(1, DIGITAL_IN); //echoPins
muxShield.setMode(2, DIGITAL_OUT); //trigPins
pinMode(led, OUTPUT); 
digitalWrite(led, LOW);
Wire.begin();      //Enabling the timer 
}

void loop() {
 readUltraSonic(6); 
 androidSend(6);
 if (Serial.available() > 0)
  {
    inbyte = Serial.read();
    if (inbyte == '0')
    {
      //LED off
      digitalWrite(led, LOW);
    }
    if (inbyte == '1')
    {
      //LED on
      digitalWrite(led, HIGH);
    }
  }
  delay(2000);
  }

void readUltraSonic(int number) {
  for (i = 0; i < number; i++) {
    ultraSonic(1, 2, i, i); 
    ultrasonicValues[i]= distanceToObject;
    }
   delay(2000);
  }


void ultraSonic(int row_echo, int row_trigger, int place_echo, int place_trigger) {
  muxShield.digitalWriteMS(row_trigger, place_trigger, LOW); 
  delayMicroseconds(2); 
  muxShield.digitalWriteMS(row_trigger, place_trigger, HIGH); 
  delayMicroseconds(10); 
  muxShield.digitalWriteMS(row_trigger, place_trigger, LOW); 

  while (muxShield.digitalReadMS(row_echo, place_echo) == LOW) {
    
    }
  timestampPulseGenerated = micros(); 

  while (muxShield.digitalReadMS(row_echo, place_echo) == HIGH) {
    
    }
  timestampPulseReceived = micros(); 

  interval = timestampPulseReceived - timestampPulseGenerated; 
  distanceToObject = (interval/29.1)/2; 
  return distanceToObject; 
  }

void androidSend(int n) {
  Serial.print('#');
  for (int k = 0; k < n; k++) {
    Serial.print(ultrasonicValues[k]); 
    Serial.print('+');
    }
Serial.print('~');
Serial.println();
delay(10);
  }



