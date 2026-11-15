//#include <Arduino.h>

// put function declarations here:
//int myFunction(int, int);

//void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
//}

//void loop() {
  // put your main code here, to run repeatedly:
//}

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP3XX.h>

void setup() {
  Serial.begin(115200);
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
}

void loop() {
  delay(1000);
}