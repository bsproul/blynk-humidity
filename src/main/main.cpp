#include <WEMOS_SHT3X.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>

#define BLYNK_PRINT Serial

SHT3X sht30(0x45);

char auth[] = "f241426017544105b29bfa0a3d6b4f86";
//char ssid[] = "The Naked Gun";
//char pass[] = "gentlehill283";

char ssid[] = "Pivotal";
char pass[] = "arid22volt";

int frequency = 3000;//20 * 60 * 1000;

SimpleTimer timer;
unsigned long lastNotified;


// const int sclPin = D1;
// const int sdaPin = D2;

// void scan()
// {
//   byte error, address;
//   int nDevices;
//
//   Serial.println("Scanning...");
//
//   nDevices = 0;
//   for (address = 1; address < 127; address++)
//   {
//     // The i2c scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//
//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address < 16) {
//         Serial.print("0");
//       }
//       Serial.print(address, HEX);
//       Serial.println(" !");
//
//       nDevices++;
//     }
//     else if (error == 4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address < 16) {
//         Serial.print("0");
//       }
//       Serial.println(address, HEX);
//     }
//   }
//   if (nDevices == 0) {
//     Serial.println("No I2C devices found\n");
//   }
//   else {
//     Serial.println("Done.\n");
//   }
//
// }

void sendData(){
  // scan();

  int res = sht30.get();
  float h = sht30.humidity;
  float t = sht30.cTemp;
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, t);

  // Serial.print("H: ");
  // Serial.print(h);
  // Serial.print(" T: ");
  // Serial.println(t);

  unsigned long currentTime = millis();
  if(currentTime - lastNotified > frequency){
    if (h < 65){
      Blynk.notify("Humidity below 65%");
      lastNotified = currentTime;
    } else if (h > 74){
      Blynk.notify("Humidity above 74%");
      lastNotified = currentTime;
    }

    if (t > 23){
      Blynk.notify("Temperature above 23°C");
      lastNotified = currentTime;
    }
  }

  if(currentTime < lastNotified){
    lastNotified = currentTime;
  }
}

void setup(){
  // Wire.begin(sdaPin, sclPin);

  Serial.begin(9600);
  lastNotified = millis();

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(frequency, sendData);
}

void loop(){
  Blynk.run();
  timer.run();
}
