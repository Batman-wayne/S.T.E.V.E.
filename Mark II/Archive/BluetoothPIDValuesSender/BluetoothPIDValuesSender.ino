#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial BT(3,4);  //RX, TX

float p_roll_float, p_pitch_float, p_yaw_float, i_roll_float, i_pitch_float, i_yaw_float, d_roll_float, d_pitch_float, d_yaw_float;
float p_roll_dump, p_pitch_dump, p_yaw_dump, i_roll_dump, i_pitch_dump, i_yaw_dump, d_roll_dump, d_pitch_dump, d_yaw_dump;
unsigned int p_roll_int, p_pitch_int, p_yaw_int, i_roll_int, i_pitch_int, i_yaw_int, d_roll_int, d_pitch_int, d_yaw_int, x;
unsigned int calibration[8];
byte cali[18];
byte data, p_roll_byteu, p_pitch_byteu, p_yaw_byteu, i_roll_byteu, i_pitch_byteu, i_yaw_byteu, d_roll_byteu, d_pitch_byteu, d_yaw_byteu, p_roll_bytel, p_pitch_bytel, p_yaw_bytel, i_roll_bytel, i_pitch_bytel, i_yaw_bytel, d_roll_bytel, d_pitch_bytel, d_yaw_bytel;
byte p_roll_byte, p_pitch_byte, p_yaw_byte, i_roll_byte, i_pitch_byte, i_yaw_byte, d_roll_byte, d_pitch_byte, d_yaw_byte;
byte lower, upper;
/*
String p_roll = "1.3";
String p_pitch = "13.5";
String p_yaw = "366.6";
String i_roll = "15.6";
String i_pitch = "86.6";
String i_yaw = "154.3";
String d_roll = "143.2";
String d_pitch = "187.3";
String d_yaw = "252.3";
*/
void setup() {

  Wire.begin(8);
  Serial.begin(9600);
  BT.begin(9600);
  Wire.onRequest(requestEvent);

  p_roll_float = p_roll.toFloat();
  p_pitch_float = p_pitch.toFloat();
  p_yaw_float = p_yaw.toFloat();
  i_roll_float = i_roll.toFloat();
  i_pitch_float = i_pitch.toFloat();
  i_yaw_float = i_yaw.toFloat();
  d_roll_float = d_roll.toFloat();
  d_pitch_float = d_pitch.toFloat();
  d_yaw_float = d_yaw.toFloat();
}

void loop() {
  p_roll_float += 0.32;
  p_pitch_float += 1.31;
  p_yaw_float += 0.67;
  i_roll_float += 2.45;
  i_pitch_float += 0.84;
  i_yaw_float += 6.24;
  d_roll_float += 9.33;
  d_pitch_float += 102.37;
  d_yaw_float += 43.69;
  
  p_roll_dump = p_roll_float;
  p_pitch_dump = p_pitch_float;
  p_yaw_dump = p_yaw_float;
  i_roll_dump = i_roll_float;
  i_pitch_dump = i_pitch_float;
  i_yaw_dump = i_yaw_float;
  d_roll_dump = d_roll_float;
  d_pitch_dump = d_pitch_float;
  d_yaw_dump = d_yaw_float;

  p_roll_dump = p_roll_float * 100.0;
  p_pitch_dump = p_pitch_float * 100.0;
  p_yaw_dump = p_yaw_float * 100.0;
  i_roll_dump = i_roll_float * 100.0;
  i_pitch_dump = i_pitch_float * 100.0;
  i_yaw_dump = i_yaw_float * 100.0;
  d_roll_dump = d_roll_float * 100.0;
  d_pitch_dump = d_pitch_float * 100.0;
  d_yaw_dump = d_yaw_float * 100.0;

  if (p_roll_dump >= 65500)p_roll_dump -= 65400;
  if (p_pitch_dump >= 65500)p_pitch_dump -= 65400;
  if (p_yaw_dump >= 65500)p_yaw_dump -= 65400;
  if (i_roll_dump >= 65500)i_roll_dump -= 65400;
  if (i_pitch_dump >= 65500)i_pitch_dump -= 65400;
  if (i_yaw_dump >= 65500)i_yaw_dump -= 65400;
  if (d_roll_dump >= 65500)d_roll_dump -= 65400;
  if (d_pitch_dump >= 65500)d_pitch_dump -= 65400;
  if (d_yaw_dump >= 65500)d_yaw_dump -= 65400;

  p_roll_int = (unsigned int) p_roll_dump;
  p_pitch_int = (unsigned int) p_pitch_dump;
  p_yaw_int = (unsigned int) p_yaw_dump;
  i_roll_int = (unsigned int) i_roll_dump;
  i_pitch_int = (unsigned int) i_pitch_dump;
  i_yaw_int = (unsigned int) i_yaw_dump;
  d_roll_int = (unsigned int) d_roll_dump;
  d_pitch_int = (unsigned int) d_pitch_dump;
  d_yaw_int = (unsigned int) d_yaw_dump;

  p_roll_byte = (byte) p_roll_int;
  p_pitch_byte = (byte) p_pitch_int;
  p_yaw_byte = (byte) p_yaw_int;
  i_roll_byte = (byte) i_roll_int;
  i_pitch_byte = (byte) i_pitch_int;
  i_yaw_byte = (byte) i_yaw_int;
  d_roll_byte = (byte) d_roll_int;
  d_pitch_byte = (byte) d_pitch_int;
  d_yaw_byte = (byte) d_yaw_int;

  separate(p_roll_int, p_roll_byte, &p_roll_bytel, &p_roll_byteu);
  separate(p_pitch_int, p_pitch_byte, &p_pitch_bytel, &p_pitch_byteu);
  separate(p_yaw_int, p_yaw_byte, &p_yaw_bytel, &p_yaw_byteu);
  separate(i_roll_int, i_roll_byte, &i_roll_bytel, &i_roll_byteu);
  separate(i_pitch_int, i_pitch_byte, &i_pitch_bytel, &i_pitch_byteu);
  separate(i_yaw_int, i_yaw_byte, &i_yaw_bytel, &i_yaw_byteu);
  separate(d_roll_int, d_roll_byte, &d_roll_bytel, &d_roll_byteu);
  separate(d_pitch_int, d_pitch_byte, &d_pitch_bytel, &d_pitch_byteu);
  separate(d_yaw_int, d_yaw_byte, &d_yaw_bytel, &d_yaw_byteu);
  cali[0] = p_roll_byteu;
  cali[1] = p_roll_bytel;
  cali[2] = p_pitch_byteu;
  cali[3] = p_pitch_bytel;
  cali[4] = p_yaw_byteu;
  cali[5] = p_yaw_bytel;
  cali[6] = i_roll_byteu;
  cali[7] = i_roll_bytel;
  cali[8] = i_pitch_byteu;
  cali[9] = i_pitch_bytel;
  cali[10] = i_yaw_byteu;
  cali[11] = i_yaw_bytel;
  cali[12] = d_roll_byteu;
  cali[13] = d_roll_bytel;
  cali[14] = d_pitch_byteu;
  cali[15] = d_pitch_bytel;
  cali[16] = d_yaw_byteu;
  cali[17] = d_yaw_bytel;
  delay(2000);
}


void separate(unsigned int x, byte input, byte *lowerbyte, byte *upperbyte) {
  byte temp = B00000000;
  *lowerbyte = input;
  *upperbyte = x >> 8;
  temp = B00000000;
  *upperbyte |= temp;
}

void requestEvent() {
  Wire.write(cali, 18);
}


