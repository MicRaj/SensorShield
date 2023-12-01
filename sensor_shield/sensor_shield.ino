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

void setup() { // put your setup code here, to run once:
  #if F_CPU >= 12000000UL
    Serial.begin(9600);
  #else
    Serial.begin(9600);
    HIH61xx<SoftWire> hih(sw);
    AsyncDelay samplingInterval;
// SoftWire requires that the programmer declares the buffers used. This allows the amount
    of memory used to be set
// according to need. For the HIH61xx only a very small RX buffer is needed.
    uint8_t i2cRxBuffer[4];
    uint8_t i2cTxBuffer[32];
  #endif
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

void loop() { //put your main code here, to run repeatedly:
    sensorValue = analogRead(TSLPIN); //read light value from sensor
    Serial.println(sensorValue); //prints value from the sensor to serial monitor
    delay(100); //Delay 1000ms = 1 sec
}
