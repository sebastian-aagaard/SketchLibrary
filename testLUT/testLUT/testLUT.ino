#include "lut.h"

unsigned int displayInt;
unsigned int _findPower = 220;
  int len = sizeof(correctedLaserPower) / sizeof(correctedLaserPower[0]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);  // wait for serial port to connect. Needed for native USB
  Serial.println(sizeof(correctedLaserPower));
//  Serial.println(sizeof(correctedLaserPower[1]));
Serial.print("read ");
  Serial.println(pgm_read_word(&(correctedLaserPower[1]._setPwrAnalogValue)));

  for (byte k = 0; k < len; k++) {
    displayInt = pgm_read_byte_near(correctedLaserPower + k);
    if (displayInt == _findPower ) {
      int setValue = pgm_read_word(&(correctedLaserPower[displayInt]._setPwrAnalogValue));
      Serial.print("Desired Power: ");
      Serial.println(displayInt);
      Serial.print("Corresponds to a set value of: ");
      Serial.println(pgm_read_word(&(correctedLaserPower[displayInt]._setPwrAnalogValue)));
      analogWrite(A22, setValue);
    }

  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
