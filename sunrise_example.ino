// //#include "FastLED.h"

// #define NUM_LEDS 6

// #define DATA_PIN 13

// DEFINE_GRADIENT_PALETTE( sun_rise ) {
//   0,     0,  0,  0,   //black
// 128,   255,  0,  0,   //red
// 224,   255,255,  0,   //bright yellow
// 255,   255,255,255 }; //full white

// DEFINE_GRADIENT_PALETTE( sunset ) {
// 255,   255,255,255,
// 224,  255,  255, 0,
// 128, 255, 0, 0,
// 0,0,0,0};

// CRGB leds[NUM_LEDS];

// void setup() {

//       FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

// }

// void loop() {

//   sunrise();

//   FastLED.show();

// }

// void sunrise() {

//   // total sunrise length, in minutes

//   static const uint8_t sunriseLength = 60;

//   // how often (in seconds) should the heat color increase?

//   // for the default of 30 minutes, this should be about every 7 seconds

//   // 7 seconds x 256 gradient steps = 1,792 seconds = ~30 minutes

//   static const uint8_t interval = (sunriseLength * 60) / 256;

//   // current gradient palette color index

//   static uint8_t heatIndex = 0; // start out at 0

//   // HeatColors_p is a gradient palette built in to FastLED

//   // that fades from black to red, orange, yellow, white

//   // feel free to use another palette or define your own custom one  HeatColors_p  ColorFromPalette(HeatColors_p, heatIndex ); RainbowColors_p

//   CRGB color = ColorFromPalette(HeatColors_p, heatIndex );

//   // fill the entire strip with the current color

//   fill_solid(leds, NUM_LEDS, color);

//   // slowly increase the heat

//   EVERY_N_SECONDS(interval) {

//     // stop incrementing at 255, we don't want to overflow back to 0

//     if(heatIndex < 240) {

//       heatIndex++;

//     }

//   }

// }
