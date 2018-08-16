void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); 
  DDRD |= 0b10000000;                  //Set Pin 7 as an output, everything else as inputs             
}

void loop() {
  int state = digitalRead(2);
  if (state == HIGH) {
    Serial.println("Bluetooth On");
    PORTD = 0b10000000;               //Set Pin 7 high
    }
  if (state == LOW) {
    Serial.println("Bluetooth Off");
    PORTD = 0b00000000;               //Set Pin 7 low
    }
  delay(100);
}
