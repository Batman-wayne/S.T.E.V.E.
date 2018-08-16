#include <Wire.h>

unsigned int p_roll_int, p_pitch_int, p_yaw_int, i_roll_int, i_pitch_int, i_yaw_int, d_roll_int, d_pitch_int, d_yaw_int;
int count;
byte p_roll_byteu, p_pitch_byteu, p_yaw_byteu, i_roll_byteu, i_pitch_byteu, i_yaw_byteu, d_roll_byteu, d_pitch_byteu, d_yaw_byteu;
byte p_roll_bytel, p_pitch_bytel, p_yaw_bytel, i_roll_bytel, i_pitch_bytel, i_yaw_bytel, d_roll_bytel, d_pitch_bytel, d_yaw_bytel;
float rec_values[18];
float p_roll_float, p_pitch_float, p_yaw_float, i_roll_float, i_pitch_float, i_yaw_float, d_roll_float, d_pitch_float, d_yaw_float;
float p_roll_dump, p_pitch_dump, p_yaw_dump, i_roll_dump, i_pitch_dump, i_yaw_dump, d_roll_dump, d_pitch_dump, d_yaw_dump;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(8, 18);

  if (Wire.available() <= 18) {
    p_roll_byteu = Wire.read();
    p_roll_bytel = Wire.read();
    p_pitch_byteu = Wire.read();
    p_pitch_bytel = Wire.read();
    p_yaw_byteu = Wire.read();
    p_yaw_bytel = Wire.read();
    i_roll_byteu = Wire.read();
    i_roll_bytel = Wire.read();
    i_pitch_byteu = Wire.read();
    i_pitch_bytel = Wire.read();
    i_yaw_byteu = Wire.read();
    i_yaw_bytel = Wire.read();
    d_roll_byteu = Wire.read();
    d_roll_bytel = Wire.read();
    d_pitch_byteu = Wire.read();
    d_pitch_bytel = Wire.read();
    d_yaw_byteu = Wire.read();
    d_yaw_bytel = Wire.read();
  }

  intconstruct(&p_roll_int, &p_roll_byteu, &p_roll_bytel);
  intconstruct(&p_pitch_int, &p_pitch_byteu, &p_pitch_bytel);
  intconstruct(&p_yaw_int, &p_yaw_byteu, &p_yaw_bytel);
  intconstruct(&i_roll_int, &i_roll_byteu, &i_roll_bytel);
  intconstruct(&i_pitch_int, &i_pitch_byteu, &i_pitch_bytel);
  intconstruct(&i_yaw_int, &i_yaw_byteu, &i_yaw_bytel);
  intconstruct(&d_roll_int, &d_roll_byteu, &d_roll_bytel);
  intconstruct(&d_pitch_int, &d_pitch_byteu, &d_pitch_bytel);
  intconstruct(&d_yaw_int, &d_yaw_byteu, &d_yaw_bytel);

  p_roll_dump = (float) p_roll_int;
  p_pitch_dump = (float) p_pitch_int;
  p_yaw_dump = (float) p_yaw_int;
  i_roll_dump = (float) i_roll_int;
  i_pitch_dump = (float) i_pitch_int;
  i_yaw_dump = (float) i_yaw_int;
  d_roll_dump = (float) d_roll_int;
  d_pitch_dump = (float) d_pitch_int;
  d_yaw_dump = (float) d_yaw_int;

  p_roll_float = p_roll_dump / 100.00;
  p_pitch_float = p_pitch_dump / 100.00;
  p_yaw_float = p_yaw_dump / 100.00;
  i_roll_float = i_roll_dump / 100.00;
  i_pitch_float = i_pitch_dump / 100.00;
  i_yaw_float = i_yaw_dump / 100.00;
  d_roll_float = d_roll_dump / 100.00;
  d_pitch_float = d_pitch_dump / 100.00;
  d_yaw_float = d_yaw_dump / 100.00;

  Serial.print("P_roll is: "); Serial.print(p_roll_float); Serial.print('\t');
  Serial.print("P_pitch is: "); Serial.print(p_pitch_float); Serial.print('\t');
  Serial.print("P_yaw is: "); Serial.print(p_yaw_float); Serial.print('\t');
  Serial.print("I_roll is: "); Serial.print(i_roll_float); Serial.print('\t');
  Serial.print("I_pitch is: "); Serial.print(i_pitch_float); Serial.print('\t');
  Serial.print("I_yaw is: "); Serial.print(i_yaw_float); Serial.print('\t');
  Serial.print("D_roll is: "); Serial.print(d_roll_float); Serial.print('\t');
  Serial.print("D_pitch is: "); Serial.print(d_pitch_float); Serial.print('\t');
  Serial.print("D_yaw is: "); Serial.print(d_yaw_float); Serial.print('\t');

  Serial.println();
  delay(2000);
}

void intconstruct(unsigned int *y, byte *upperbyte, byte *lowerbyte) {
  *y = 0b0000000000000000;
  unsigned int s, g;
  s = (unsigned int) * upperbyte;
  g = s << 8;
  *y |= g;
  *y |= *lowerbyte;
}
