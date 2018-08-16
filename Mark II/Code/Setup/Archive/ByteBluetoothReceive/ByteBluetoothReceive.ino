#include <SoftwareSerial.h>
SoftwareSerial BT(10,11);                //RX, TX

byte data;
char var = 0;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  while (BT.available())data = BT.read();   //This and the next line set anything still in the buffer to 0
  data = 0;          
}

void loop() {
  if (BT.available() > 0) {
    var = BT.read();
    Serial.print(var);
    }
    delay(100);
}


