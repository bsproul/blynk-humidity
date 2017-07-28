#include <WEMOS_SHT3X.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

SHT3X sht30(0x45);

char auth[] = "f241426017544105b29bfa0a3d6b4f86";
//char ssid[] = "The Naked Gun";
//char pass[] = "gentlehill283";

char ssid[] = "Pivotal";
char pass[] = "arid22volt";

int frequency = 1000;//20 * 60 * 1000;

SimpleTimer timer;
unsigned long lastNotified;

void sendData(){
  Serial.println("TICK!");
  float h = sht30.humidity;
  float t = sht30.cTemp;
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, t);

  Serial.print("H: ");
  Serial.print(h);
  Serial.print(" T: ");
  Serial.println(t);

  unsigned long currentTime = millis();
  if(currentTime - lastNotified > frequency){
    Serial.println("notify!");
    if (h < 65){
      Blynk.notify("Humidity below 65");
      lastNotified = currentTime;
    } else if (h > 75){
      Blynk.notify("Humidity above 75");
      lastNotified = currentTime;
    }
  }

  if(currentTime < lastNotified){
    lastNotified = currentTime;
  }
}

void setup(){
  Serial.println("setup!");
  Serial.begin(9600);
  lastNotified = millis();

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(frequency, sendData);
}

void loop(){
  Serial.println("loop!");
  Blynk.run();
  timer.run();
}
