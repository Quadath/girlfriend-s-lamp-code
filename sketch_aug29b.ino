
#define STRIP_PIN 2
#define NUMLEDS 60

#include <microLED.h>
#include <IRremote.hpp>


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

const int starButton = 22;

static float r = 0;
static float g = 0;
static float b = 1;

int mode = 1;

microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(3, ENABLE_LED_FEEDBACK);

  
  strip.setBrightness(255);

  for (int i = 0; i < NUMLEDS; i++) {
    strip.set(i, mRGB(r, g, b));
  }
  strip.show();
}

float lerp(float a, float b, float x)
{
  return a + x * (b - a);
}

void loop() {

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);

    switch (IrReceiver.decodedIRData.command) {
      case starButton: {
        mode += 1;
        if (mode == 3) {
          mode = 1;
        }
      }
    }
    
    if (mode == 1) { 
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
        }
      }
      for (int i = 0; i < NUMLEDS; i++) {
        strip.set(i, mRGB(r, g, b));
      }
    } 
    IrReceiver.resume();
  }
  if (IrReceiver.isIdle()) {
   
    if (mode == 2) {
      rainbow();
      switch (IrReceiver.decodedIRData.command) {
        
      }
    }
  }
  strip.show();
  delay(16);
}
void rainbow() {
  static byte counter = 0;
  for (int i = 0; i < NUMLEDS; i++) {
    strip.set(i, mWheel8(counter + i * 255 / NUMLEDS));   // counter смещает цвет
  }
  counter += 3;   // counter имеет тип byte и при достижении 255 сбросится в 0
}
