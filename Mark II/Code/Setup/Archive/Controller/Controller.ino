 #include <SoftwareSerial.h>
SoftwareSerial BTserial(3, 2); // RX | TX
int analogpin = 0;
int c = ' ';
void setup() {
  BTserial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  
 
    c = analogRead(analogpin);
    BTserial.println(c);
    Serial.println(c);
}



