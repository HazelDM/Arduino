#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define PIN D2
#define NUMPIXELS 16
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char auth[] = "X5_YyVt5XTy6JTN00k3gyxCrn9uRGH3u";
char ssid[] = "Alkitran Wi-Fi";
char pwd[] = "1103062871";

int ValorR = 0;
int ValorG = 0;
int ValorB = 0;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pwd);
  pixels.begin();
  pixels.clear();
}

BLYNK_WRITE(V2)
{
  ValorR = param[0].asInt();
  ValorG = param[1].asInt();
  ValorB = param[2].asInt();
  
  Serial.println(ValorR);
  Serial.println(ValorG);
  Serial.println(ValorB);

  Blynk.virtualWrite(V4,ValorR);
  Blynk.virtualWrite(V5,ValorG);
  Blynk.virtualWrite(V6,ValorB);

  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(ValorR,ValorG,ValorB));
    pixels.show();
  }
}

BLYNK_WRITE(V4)
{
  ValorR = param.asInt();
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(ValorR,ValorG,ValorB));
    pixels.show();
  }
}

BLYNK_WRITE(V5)
{
  ValorG = param.asInt();
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(ValorR,ValorG,ValorB));
    pixels.show();
  }

}

BLYNK_WRITE(V6)
{
  ValorB = param.asInt();
  for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(ValorR,ValorG,ValorB));
    pixels.show();
  }
}

void loop()
{
  Blynk.run();
}
