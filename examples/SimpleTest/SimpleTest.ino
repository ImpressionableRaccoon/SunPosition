#include "SunPosition.h"

SunPosition sun;

void setup() {
  Serial.begin(9600);

  sun = SunPosition(2021, 9, 3, 9, 0, 0, 46, -130);

  Serial.print("Azimuth: ");
  Serial.println(sun.azimuth, 3);
  Serial.print("Elevation: ");
  Serial.println(sun.elevation, 3);
}

void loop() {

}