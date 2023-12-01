// *************** //
//  Sensor Shield  // 
// *************** //
// TL2060 | MR2207 //
// *************** //

// Inclusions
#include <SoftWire.h>
#include <HIH61xx.h>
#include <AsyncDelay.h>

#include <Adafruit_MMA8451.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>


//Constants
#define TSLPIN A1 //tell the program what pin the TSL257 is attached to

// Variables
int chk;
int sensorValue = 0; //variable to store the value coming from the sensor
Adafruit_MMA8451 mma = Adafruit_MMA8451();
SoftWire sw(SDA, SCL);
HIH61xx<SoftWire> hih(sw);
AsyncDelay samplingInterval; 

uint8_t i2cRxBuffer[4];
uint8_t i2cTxBuffer[32];



void setup() { // put your setup code here, to run once:

    Serial.begin(9600);
    Serial.println("Adafruit MMA8451 test!");
    
    // The pin numbers for SDA/SCL can be overridden at runtime.
    sw.setSda(A4); //DATA PIN ALLOCATION
    sw.setScl(A5); //CLOCK PIN ALLOCATION
    sw.setRxBuffer(i2cRxBuffer, sizeof(i2cRxBuffer));
    //sw.setTxBuffer(i2cTxBuffer, sizeof(i2cTxBuffer));
    // HIH61xx doesn't need a TX buffer at all but other I2C devices probably will.
    //sw.setTxBuffer(i2cTxBuffer, sizeof(i2cTxBuffer));
    sw.setTxBuffer(NULL, 0);
    sw.begin(); // Sets up pin mode for SDA and SCL
    hih.initialise();
    samplingInterval.start(1000, AsyncDelay::MILLIS);
    if (! mma.begin()) {
      Serial.println("Couldnt start");
    while (1);
    }
    Serial.println("MMA8451 found!");
    mma.setRange(MMA8451_RANGE_2_G);
    Serial.print("Range = "); Serial.print(2 << mma.getRange());
    Serial.println("G");
    }




bool printed = true; 

void loop() { //put your main code here, to run repeatedly:
   // Read the 'raw' data in 14-bit counts
    mma.read();
    Serial.print("X:\t"); Serial.print(mma.x);
    Serial.print("\tY:\t"); Serial.print(mma.y);
    Serial.print("\tZ:\t"); Serial.print(mma.z);
    Serial.println();
/* Get a new sensor event */
    sensors_event_t event;
    mma.getEvent(&event);
/* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
   
    Serial.println("m/s^2 ");
/* Get the orientation of the sensor */
    uint8_t o = mma.getOrientation();
    switch (o) {
        case MMA8451_PL_PUF:
          Serial.println("Portrait Up Front");
        break;
        case MMA8451_PL_PUB:
          Serial.println("Portrait Up Back");
        break;
        case MMA8451_PL_PDF:
          Serial.println("Portrait Down Front");
        break;
        case MMA8451_PL_PDB:
          Serial.println("Portrait Down Back");
        break;
        case MMA8451_PL_LRF:
          Serial.println("Landscape Right Front");
        break;
        case MMA8451_PL_LRB:
          Serial.println("Landscape Right Back");
        break;
        case MMA8451_PL_LLF:
          Serial.println("Landscape Left Front");
        break;
        case MMA8451_PL_LLB:
          Serial.println("Landscape Left Back");
        break;
        }
      Serial.println();
    delay(500);
  

    if (samplingInterval.isExpired() && !hih.isSampling()) {
      hih.start();
      printed = false;
      samplingInterval.repeat();
      Serial.println("Sampling started (using SoftWire library)");
    }

    hih.process();


    if (hih.isFinished() && !printed) {
      printed = true;
    // Print saved values
      Serial.print("RH: ");
      Serial.print(hih.getRelHumidity() / 100.0);
      Serial.println(" %");
      Serial.print("Ambient: ");
      Serial.print(hih.getAmbientTemp() / 100.0);
      Serial.println(" deg C");
      Serial.print("Status: ");
      Serial.println(hih.getStatus());
}
  
    sensorValue = analogRead(TSLPIN); //read light value from sensor
    Serial.println(sensorValue); //prints value from the sensor to serial monitor
    delay(1000); //Delay 1000ms = 1 sec
}
