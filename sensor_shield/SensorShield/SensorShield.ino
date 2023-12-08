#include <Adafruit_MMA8451.h>
#include<Wire.h>

#define Addr 0x27
#define TSLPIN A1          // connection pin for TSL
#define gLED          11   // connection pin for green LED
#define yLED          12   // connection pin for yellow LED
#define rLED          13   // connection pin for red LED

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int chk;
int sensorValue = 0; //variable to store the value coming from the sensor

void setup(void) {
  Wire.begin();
  pinMode(gLED, OUTPUT);
  pinMode(yLED, OUTPUT);
  pinMode(rLED, OUTPUT);
  Serial.begin(9600);
  delay(300);
  mma.begin();
 }

void loop() {
  int sensorValue = analogRead(TSLPIN);           //read TSL257 sensor
  float light = sensorValue*0.09794319295;        //converts TSL257 output to %
  Serial.print(sensorValue);
  Serial.print(String("Light Level: ") + light + String(" %")); Serial.print("\t"); delay(20);  
  
  unsigned int data[4];
  Wire.beginTransmission(Addr);
  Wire.endTransmission();
  Wire.requestFrom(Addr, 4);
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  float humidity = ((((data[0] & 0x3F) * 256.0) + data[1]) * 100.0) / 16382.0;
  int temp = ((data[2] * 256) + (data[3] & 0xFC)) / 4;
  float cTemp = (temp / 16382.0) * 165.0 - 40.0;

  Serial.print(humidity + String(" %RH"));  Serial.print("\t");  //prints Humidity
  Serial.print(cTemp + String(" degC"));  Serial.print("\t"); //prints Humidity 
  delay(50);
  
  mma.read();                 //Read the 'raw' data in 14-bit counts
  sensors_event_t event;      //Get a new sensor event
  mma.getEvent(&event);       //Get a new sensor event 
 Serial.print(String("X: \t") + event.acceleration.x + String(" m/s2")); Serial.print("\t");   //prints x accell
 Serial.print(String("Y: \t") + event.acceleration.y + String(" m/s2")); Serial.print("\t");   //prints y accell
 Serial.println(String("Z: \t") + event.acceleration.z + String(" m/s2"));                     //prints z accell
 delay(200);


if (light > 75) {digitalWrite(gLED, HIGH);}                 else {digitalWrite(gLED, LOW);}
if (humidity > 60) {digitalWrite(yLED, HIGH);}              else {digitalWrite(yLED, LOW);}
if (event.acceleration.z > 9.5) {digitalWrite(rLED, HIGH);} else {digitalWrite(rLED, LOW);}
delay(200);
 
}
