
#define STRIP_PIN 2
#define NUMLEDS 60

#include <microLED.h>
#include <IRremote.hpp>
#include "FastLED.h"

CRGB leds[NUMLEDS];

const int button0 = 25;
const int button1 = 69;
const int button2 = 70;
const int button3 = 71;
const int button4 = 68;
const int button5 = 64;
const int button6 = 67;
const int button7 = 7;
const int button8 = 21;
const int button9 = 9;

static float r = 0;
static float g = 0;
static float b = 10;


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(3, ENABLE_LED_FEEDBACK);

  FastLED.addLeds<NEOPIXEL, STRIP_PIN>(leds, NUMLEDS);
  FastLED.setBrightness(50);

  for (int i = 0; i < NUMLEDS; i++) {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}

float lerp(float a, float b, float x)
{
  return a + x * (b - a);
}

void loop() {

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);
    switch (IrReceiver.decodedIRData.command) {
      case button1: {
          r += 2;
          if (r > 255) r = 255;
        } break;
      case button4: {
          r -= 2;
          if (r < 0) r = 0;
        } break;

      case button2: {
          g += 2;
          if (g > 255) g = 255;
        } break;
      case button5: {
          g -= 2;
          if (g < 0) g = 0;
        } break;

      case button3: {
          b += 2;
          if (b > 255) b = 255;
        } break;
      case button6: {
          b -= 2;
          if (b < 0) b = 0;
        } break;
    }
    delay(1);

    for (int i = 0; i < NUMLEDS; i++) {
      leds[i] = CRGB(r, g, b);
    }
    FastLED.show();
    IrReceiver.resume();
  }

}
