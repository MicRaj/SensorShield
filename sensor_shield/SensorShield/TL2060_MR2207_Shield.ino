/*///////////////////////////////////////////////////////////////////////
*************************************************************************
|||||||||||||||||||||||||||| TL2060 & MR2207 ||||||||||||||||||||||||||||
|||||||||||||||||||||||||||| Arduino Shield  ||||||||||||||||||||||||||||
*************************************************************************
/////////////////////////////////////////////////////////////////////////

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This Code was Adapted from that Provided in the Labscript for ESDM2 

(Adapted from: M.T. Cole, ESDM2 lab script, 2017)

(Source:	K. Townsend,	Adafruit Industries,
https://learn.adafruit.com/adafruit-mma8451-accelerometer-breakout/wiring-and-test,
2018)

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <Adafruit_MMA8451.h>
#include <Wire.h>

// MMA8451 & TSL257 Funtioning With LED's Functional. 
// HIH6160 was Attempted However Would Output Constant Values so N/A.

Adafruit_MMA8451 mma = Adafruit_MMA8451();		// Define MMA

int TSL257Output = 0;

void setup(void) {
	Wire.begin();					// Initialise TSL
	
	pinMode(11, OUTPUT);				// Setup LED's
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);

	Serial.begin(9600);
	delay(100);
	
	mma.begin();					// Initialise MMA
}

void loop() {
	int TSL257Output = analogRead(A1); 		// TSL257 RAW
	float Luminosity = TSL257Output * 0.0976525;	// RAW * 100/1024 = Relative%
//  Serial.println(TSL257Output);
	Serial.print(String("Relative Luminosity: ") + Luminosity + String("% \n"));
	delay(20);
	
	if (Luminosity < 50) {				// Set Yellow LED HIGH if Relative is < 50% 
   		digitalWrite(11, HIGH);
 	} else {
		digitalWrite(11, LOW);
	} 
	

	mma.read();					// Read MMA8451, Take X Y Z Values & Take Orientation Then Print to Console
	sensors_event_t event;
	mma.getEvent(&event);

	Serial.print(String("X: ") + event.acceleration.x + String("ms^-2 \n"));    
 	Serial.print(String("Y: ") + event.acceleration.y + String("ms^-2 \n")); 
 	Serial.print(String("Z: ") + event.acceleration.z + String("ms^-2 \n"));       

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
	delay(200);
	
	if (event.acceleration.z > 7) {            // Set Red LED High if Above ms^-2 Z-axis Acceleration
		digitalWrite(13, HIGH);
	} else {
		digitalWrite(13, LOW);
	}

  delay(500);              	
}