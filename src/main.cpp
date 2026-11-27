#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP3XX.h>

//code running from pico

void scanI2CBus() {
  int devicesFound = 0; //set number of devices found to 0

  //send print statement through serial USB connection to output screen
  Serial.println("\nScanning I2C0 bus (GP4=SDA, GP5=SCL) at 400 kHz...");

  //Valid 7-bit I2C addresses run from 0x01 (1) to 0x7E (126)
  //Check valid connection
  //unit8_t is an unsigned integer of 8 bits (data type)
  //for address in range(0x01, 0x7F): (address increases by 1 )
  //check each address for its connection 
  for (uint8_t address = 0x01; address <= 0x7E; address++) {
    Wire.beginTransmission(address); //start condition and transmit 7-bit address
    uint8_t status = Wire.endTransmission(); // Complete frame and return handshake status code

    if (status == 0) { //everything fine
      Serial.print("  [ACK] Found device at 0x");
      if (address < 0x10) {
        Serial.print("0"); // Leading zero for single-digit hex values (0x01..0x0F)
      }
      Serial.print(address, HEX);
      
      // Identify known peripheral addresses on this avionics bus
      //component is MPU-6050 if it only has 0x68 addresses
      if (address == 0x68) {
        Serial.print(" (MPU-6050)"); 
      //else component is BMP388 with 0x77 addresses
      } else if (address == 0x77) {
        Serial.print(" (BMP388)");
      }
      //print new line and add one to num. devices found
      Serial.println();
      devicesFound++;

      // Bus fault / error condition on the I2C bus
    } else if (status == 4) {
      Serial.print("  [ERR] Bus fault at 0x");
      if (address < 0x10) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
if (devicesFound == 0) {
    Serial.println("  No I2C devices responded.");
  } else {
    Serial.print("Scan complete. Total ACK devices: ");
    Serial.println(devicesFound);
  }
}

void setup() {
  //open link between pico and computer
  Serial.begin(115200);

  // Wait up to 2.5 seconds for Serial Monitor USB to be ready without blocking autonomous startup
  uint32_t startTime = millis();
  while (!Serial && (millis() - startTime < 2500)) {
    delay(10);
  }

  // Route I2C0 to GP4 (SDA) and GP5 (SCL)
  //GP4 = data, GP5 = clock
  // Configure I2C0 pins (GP4 = SDA serial data, GP5 = SCL serial clock) at 400 kHz
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  Wire.setClock(400000);
}

//call scanI2CBus() 
//void = no return value
void loop() {
  scanI2CBus();
  delay(3000); // Pause 3000 ms (3 s) before repeating bus scan
}