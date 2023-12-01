// *************** //
//  Sensor Shield  // 
// *************** //
// TL2060 | MR2207 //
// *************** //

//Constants
#define TSLPIN A1 //tell the program what pin the TSL257 is attached to
//Variables
int chk;
int sensorValue = 0; //variable to store the value coming from the sensor
void setup() { // put your setup code here, to run once:
    Serial.begin(9600); // USB baud rate
}
void loop() { //put your main code here, to run repeatedly:
    sensorValue = analogRead(TSLPIN); //read light value from sensor
    Serial.println(sensorValue); //prints value from the sensor to serial monitor
    delay(1000); //Delay 1000ms = 1 sec
}
