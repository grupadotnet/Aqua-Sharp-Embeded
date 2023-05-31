

//  class CreateMeasurementViewModel()
// {
//    public DateTime Time
//    public float Temperature
//    public float Ph
//    public uint TDS
//    public bool LightOn
//    public int AquariumId
//    notacja iso rok-miesiac-dzientygodnia-czas
// }

#include <OneWire.h>
#include <DallasTemperature.h>
#include <FastLED.h>
#include <EEPROM.h> //?
#include "GravityTDS.h"
#include <Average.h>

#define NUM_LEDS 30
#define DATA_PIN 6

#define ONE_WIRE_BUS 0
#define TdsSensorPin A1

DEFINE_GRADIENT_PALETTE(sun_rise){
    0, 0, 0, 0,          // black
    128, 255, 0, 0,      // red
    224, 255, 255, 0,    // bright yellow
    255, 255, 255, 255}; // full white

DEFINE_GRADIENT_PALETTE(sunset){
    255, 255, 255, 255,
    224, 255, 255, 0,
    128, 255, 0, 0,
    0, 0, 0, 0};

CRGB leds[NUM_LEDS];

GravityTDS gravityTds;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  pixels.begin();
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);      // reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024); // 1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
  Serial.print(getTemperature(1000)); // parametr delay
  Serial.println("C");
  getLighting();
  Serial.println(getPh());
  Serial.print("TDS Value:");
  Serial.print(getTds(1000), 0);
  Serial.println("ppm");
}

float getTemperature(int TEMP_DELAY)
{
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
  delay(TEMP_DELAY);
}

void getLighting()
{
  sunrise();
  FastLED.show();
}

void sunrise()
{

  static const uint8_t sunriseLength = 60; // total sunrise length, in minutes

  // how often (in seconds) should the heat color increase?

  // for the default of 30 minutes, this should be about every 7 seconds

  // 7 seconds x 256 gradient steps = 1,792 seconds = ~30 minutes

  static const uint8_t interval = (sunriseLength * 60) / 256;

  // current gradient palette color index

  static uint8_t heatIndex = 0; // start out at 0

  // HeatColors_p is a gradient palette built in to FastLED

  // that fades from black to red, orange, yellow, white

  // feel free to use another palette or define your own custom one  HeatColors_p  ColorFromPalette(HeatColors_p, heatIndex ); RainbowColors_p

  CRGB color = ColorFromPalette(HeatColors_p, heatIndex);

  // fill the entire strip with the current color

  fill_solid(leds, NUM_LEDS, color);

  // slowly increase the heat

  EVERY_N_SECONDS(interval)
  {

    // stop incrementing at 255, we don't want to overflow back to 0

    if (heatIndex < 240)
    {

      heatIndex++;
    }
  }
}

float getPh()
{
  int Volty = analogRead(A7);
  float V = (float)Volty * 5.0 / 1024.0;
  float peha = (float)V * 2.8;
  sredniaPH.push(peha);
  sredniaPH.mean();
  float pH = ((float)sredniaPH.mean());
  return pH;
  delay(1000);
}

uint getTds(int TEMP_DELAY)
{
  gravityTds.setTemperature(25); // set the temperature and execute temperature compensation
  gravityTds.update();           // sample and calculate
  uint tdsValue = gravityTds.getTdsValue();
  return tdsValue;
  delay(TEMP_DELAY);
}