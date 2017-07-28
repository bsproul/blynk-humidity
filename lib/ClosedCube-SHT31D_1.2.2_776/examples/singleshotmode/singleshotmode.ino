/*

This is example for SHT3X-DIS Digital Humidity & Temperature Sensors Arduino Library
ClosedCube SHT31-D [Digital I2C] Humidity and Temperature Sensor Breakout 

Initial Date: 06-Oct-2015
Last Updated: 12-Oct-2016

Hardware connections for Arduino Uno:
	VDD to 3.3V DC
	SDA to A4
	SCL to A5
	GND to common ground
	
MIT License

*/

#include <Wire.h>
#include <ClosedCube_SHT31D.h>

ClosedCube_SHT31D sht31d;

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube SHT31D Single Shot Mode Example");
	
	sht31d.begin(0x44);
	Serial.print("SHT31D Serial #");
	Serial.println(sht31d.readSerialNumber());	
}

void loop()
{
	printResult("ClockStrech Mode", sht31d.readTempAndHumidity(REPEATABILITY_LOW, MODE_CLOCK_STRETCH, 50));  
  	delay(250);
	printResult("Pooling Mode", sht31d.readTempAndHumidity(REPEATABILITY_HIGH, MODE_POLLING, 50));
	delay(250);
}

void printResult(String text, SHT31D result) {
	if (result.error == NO_ERROR) {
		Serial.print(text);
		Serial.print(": T=");
		Serial.print(result.t);
		Serial.print("C, RH=");
		Serial.print(result.rh);
		Serial.println("%");
	}
	else {
		Serial.print(text);
		Serial.print(": [ERROR] Code #");
		Serial.println(result.error);
	}
}