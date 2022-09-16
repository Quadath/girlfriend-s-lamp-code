
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

const int arrowUp = 24;
const int arrowDown = 82;
const int arrowRight = 90;
const int arrowLeft = 8;

static float r = 200;
static float g = 0;
static float b = 100;

static int bright = 100;





//RAINBOW
static float rainbowSpeed = 3;


int mode = 1;

microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(3, ENABLE_LED_FEEDBACK);
  strip.setBrightness(bright);
  for (int i = 0; i < NUMLEDS; i++) {
    strip.set(i, mRGB(r, g, b));
  }
  strip.show();
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
      } break;
      case arrowUp: {
        bright++;
        if (bright > 255) {
          bright = 255;
        }
      } break;
      case arrowDown: {
        bright--;
        if (bright < 0) {
          bright = 0;
        }
      } break;
    }
    strip.setBrightness(bright);
    
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
    }
    else if (mode == 2) {
      switch (IrReceiver.decodedIRData.command) {
        case arrowLeft: {
          rainbowSpeed -= .1f;
          if (rainbowSpeed < 0) {
            rainbowSpeed = 0;
          }
        } break;
        case arrowRight: {
          rainbowSpeed += .1f;
        }
      }
    }
    
    IrReceiver.resume();
  }
  if (IrReceiver.isIdle()) {
    switch(mode) {
      case 1: {
        strip.fill(0, NUMLEDS, mRGB(r, g, b));
      } break;
      case 2: {
        rainbow();
      } break;
    }
  }
  strip.show();
  delay(16);
}

void rainbow() {
  static float counter = 0;
  for (int i = 0; i < NUMLEDS; i++) {
    strip.set(i, mWheel8((int)counter + i * 255 / NUMLEDS));   // counter смещает цвет
  }
  counter += rainbowSpeed;   // counter имеет тип byte и при достижении 255 сбросится в 0
  if (counter > 255) {
    counter = 0;
  }
  Serial.print(counter);
  Serial.print("   ");
  Serial.print(rainbowSpeed);
  Serial.println();
}
