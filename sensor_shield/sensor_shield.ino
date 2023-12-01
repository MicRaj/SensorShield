// *************** //
//  Sensor Shield  // 
// *************** //
// TL2060 | MR2207 //
// *************** //

// Inclusions
#include <SoftWire.h>
#include <HIH61xx.h>
#include <AsyncDelay.h>

//Constants
#define TSLPIN A1 //tell the program what pin the TSL257 is attached to

// Variables
int chk;
int sensorValue = 0; //variable to store the value coming from the sensor
SoftWire sw(SDA, SCL);
HIH61xx<SoftWire> hih(sw);
AsyncDelay samplingInterval; 
uint8_t i2cRxBuffer[4];
uint8_t i2cTxBuffer[32];


void setup() { // put your setup code here, to run once:

    Serial.begin(9600);

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
}

bool printed = true; 

void loop() { //put your main code here, to run repeatedly:
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
