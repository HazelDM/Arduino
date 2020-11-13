#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define PIN D2
#define NUMPIXELS 16
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char auth[] = "Your Blynk Auth Code";
char ssid[] = "Wi-Fi";
char pwd[] = "Wi-Fi Password";

int msg = 0; //Esta variable va a guardar el estado que se quiere enviar. 1 = Happy, 2 = Sad, 3 = Cebra.

// INICIALIZACIÓN //
void setup()
{
  Blynk.virtualWrite(V5,0);
  Blynk.virtualWrite(V6,0);
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pwd);
  
  pixels.begin();
  pixels.clear();
}

//V2 es el pin al que está conectado la cebra//
BLYNK_WRITE(V2)
{
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
    
  Serial.println(R);
  Serial.println(G);
  Serial.println(B);

  //Como se está activando la cebra, apago los otros botones//
  Blynk.virtualWrite(V5,0);
  Blynk.virtualWrite(V6,0);
  msg = 3;

  for(int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(R,G,B));
    pixels.show();
  }
}

BLYNK_WRITE(V5)
{
  int happy = param.asInt();
  if (happy == 1)
  {
    Blynk.virtualWrite(V6,0); //apaga SAD si estuviera encendido
    msg = 1;
  }
  else 
  {
    msg = 0;
  }
}

BLYNK_WRITE(V6)
{
  int sad = param.asInt();
  if (sad == 1)
  {
    Blynk.virtualWrite(V5,0);
    msg = 2;
  }
  else
  {
    msg = 0;
  }
}

void Happy()
{
  int R = random(100,255);
  int G = random(255);
  int B = random(255);
  int y = 0;
  
  for (int i = 0; i < NUMPIXELS; i++)
  {
        y = i - 1;
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        pixels.setPixelColor(y, pixels.Color(R, G, B));
        pixels.show();
        delay(100);
  }
  pixels.setPixelColor(15, pixels.Color(R, G, B));
  pixels.show();
}

void Sad()
{
  int R = 0;
  int G = random(255);
  int B = random(255);
 
  for(int i = 0; i < NUMPIXELS; i++)
  {
      pixels.setPixelColor(i, pixels.Color(R,G,B));
      pixels.show();
      delay(100);
  }
  for(int i = 0; i < NUMPIXELS; i++)
  {
      pixels.setPixelColor(i, pixels.Color(R,G/10,B/10));
      pixels.show();
      delay(100);
  }
}

void Apagar()
{
  for(int i = 0; i < NUMPIXELS; i++)
  {
      pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show();
      delay(100);
  }
}

void loop()
{
  Blynk.run();
  switch (msg) 
  {
    case 0:
     Apagar();
     break;
    case 1:
     Happy();
     break;
    case 2:
     Sad();
     break;  
  }
}
