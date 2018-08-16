#include <avr/sleep.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <avr/sleep.h>
#include <Adafruit_GPS.h>
#include <MuxShield.h>

SoftwareSerial mySerial(5, 3);     //RX, TX
MuxShield muxShield; 
Adafruit_GPS GPS(&mySerial);

#define GPSECHO true //True for debugging, false for actual use 
#define LOG_FIXONLY false //True means it only logs when it has a signal, false means debugging 
#define chipSelect 9      //Pin for SD card 
#define ledPin 13         //Pin for led 

File logfile;

boolean usingInterrupt = false;
void useInterrupt(boolean);

// read a Hex value and return the decimal equivalent
uint8_t parseHex(char c) {
  if (c < '0')
    return 0;
  if (c <= '9')
    return c - '0';
  if (c < 'A')
    return 0;
  if (c <= 'F')
    return (c - 'A')+10;
}

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\r\nUltimate GPSlogger Shield");
  pinMode(ledPin, OUTPUT);
  pinMode(9, OUTPUT);
  muxShield.setMode(1, DIGITAL_IN);
  muxShield.setMode(2, DIGITAL_OUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }
  char filename[15];
  strcpy(filename, "GPSLOG00.TXT");
  for (uint8_t i=0; i<100; i++) {
    filename[6] = '0' + i/10;
    filename[7] = '0' + i%10;
    if (! SD.exists(filename)) {
      break;
    }
   }

   logfile = SD.open(filename, FILE_WRITE);
   if( ! logfile ) {
    Serial.print("Couldnt create "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to "); 
  Serial.println(filename);

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_NOANTENNA);
  useInterrupt(true);
  Serial.println("Ready!");
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  #ifdef UDR0
      if (GPSECHO)
        if (c) UDR0 = c;  
  #endif
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  }
  else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}
 
void loop() {
  muxShield.digitalWriteMS(2,0,HIGH); 
  Serial.println(muxShield.digitalReadMS(1,0));
   if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  if (GPS.newNMEAreceived()) {
    char *stringptr = GPS.lastNMEA();
    if (!GPS.parse(stringptr))
      return;

    Serial.println("OK");
    if (LOG_FIXONLY && !GPS.fix) {
      Serial.print("No Fix");
      return;
    }

    Serial.println("Log");

    uint8_t stringsize = strlen(stringptr);
    if (stringsize != logfile.write((uint8_t *)stringptr, stringsize))    //write the string to the SD file
        error(4);
    if (strstr(stringptr, "RMC") || strstr(stringptr, "GGA"))   logfile.flush();
    Serial.println();
  }
}
