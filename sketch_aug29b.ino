
#define STRIP_PIN 2
#define NUMLEDS 60

#include <microLED.h>
#include <FastLEDsupport.h>    // нужна для шума
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
const int rerButton = 13;

const int arrowUp = 24;
const int arrowDown = 82;
const int arrowRight = 90;
const int arrowLeft = 8;

static bool ON = true;

static float r = 200;
static float g = 0;
static float b = 100;

static int bright = 100;

//GRADIENT
static float gradR = 0;
static float gradG = 0;
static float gradB = 255;

static float _gradR = 0;
static float _gradG = 255;
static float _gradB = 0;

static int gradColor = 1;

//RAINBOW
static float rainbowSpeed = 3;

//RUNNING DOTS

static float dotsR = 0;
static float dotsG = 200;
static float dotsB = 30;

static int dotSpeed = 100;

//PULSE


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
        if (mode == 6) {
          mode = 1;
          strip.setBrightness(bright);
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
      case button0: {
       ON = !ON;
      }
    }
    strip.setBrightness(bright);
    
    if (mode == 1) { 
       switch (IrReceiver.decodedIRData.command) {
        case button1: {
          r += 5;
          if (r > 255) r = 255;
        } break;
        case button4: {
            r -= 5;
            if (r < 0) r = 0;
          } break;
  
        case button2: {
            g += 5;
            if (g > 255) g = 255;
          } break;
        case button5: {
            g -= 5;
            if (g < 0) g = 0;
          } break;
  
        case button3: {
            b += 5;
            if (b > 255) b = 255;
          } break;
        case button6: {
            b -= 5;
            if (b < 0) b = 0;
        }
      }
    }
    else if (mode == 2) {
      switch (IrReceiver.decodedIRData.command) {
        case rerButton: {
          gradColor++;
          if (gradColor > 2) {
            gradColor = 1;
          }
        }
        case button1: {
    if (gradColor == 1) {
        gradR += 5; 
        if (gradR > 255) gradR = 255;
    } else {
        _gradR += 5;
        if (_gradR > 255) _gradR = 255;
        }
    } break;
    case button4: {
        if (gradColor == 1) {
            gradR -= 5; 
            if (gradR < 0) gradR = 0;
        } else {
            _gradR -= 5;
            if (_gradR < 0) _gradR = 0;
            }
        } break;
    case button2: {
        if (gradColor == 1) {
            gradG += 5; 
            if (gradG > 255) gradG = 255;
        } else {
            _gradG += 5;
            if (_gradG > 255) _gradG = 255;
            }
        } break;
    case button5: {
        if (gradColor == 1) {
            gradG -= 5; 
            if (gradG < 0) gradG = 0;
        } else {
            _gradG -= 5;
            if (_gradG < 0) _gradG = 0;
            }
        } break;
    case button3: {
        if (gradColor == 1) {
            gradB += 5; 
            if (gradB > 255) gradB = 255;
        } else {
            _gradB += 5;
            if (_gradB > 255) _gradB = 255;
            }
        } break;
    case button6: {
        if (gradColor == 1) {
            gradB -= 5; 
            if (gradB < 0) gradB = 0;
        } else {
            _gradB -= 5;
            if (_gradB < 0) _gradB = 0;
            }
        } break;
       }
    }
    else if (mode == 3) {
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
    else if (mode == 4) {
      switch (IrReceiver.decodedIRData.command) {
        case button1: {
          dotsR += 5;
          if (dotsR > 255) dotsR = 255;
        } break;
        case button4: {
            dotsR -= 5;
            if (dotsR < 0) dotsR = 0;
          } break;
  
        case button2: {
            dotsG += 5;
            if (dotsG > 255) dotsG = 255;
          } break;
        case button5: {
            dotsG -= 5;
            if (dotsG < 0) dotsG = 0;
          } break;
  
        case button3: {
            dotsB += 5;
            if (dotsB > 255) dotsB = 255;
          } break;
        case button6: {
            dotsB -= 5;
            if (dotsB < 0) dotsB = 0;
        } break;
        case arrowLeft: {
          dotSpeed += 10;
          if (dotSpeed > 3000) dotSpeed = 3000;
        } break;
        case arrowRight: {
          dotSpeed -= 10;
          if (dotSpeed < 10) dotSpeed = 10;
        }
      }
    }
    
    IrReceiver.resume();
  }
  if (IrReceiver.isIdle()) {
    if(ON) {
      strip.setBrightness(bright);
      switch(mode) {
        case 1: {
          strip.fill(0, NUMLEDS, mRGB(r, g, b));
        } break;
        case 2: {
            strip.fillGradient(0, NUMLEDS / 2, mRGB(gradR, gradG, gradB), mRGB(_gradR, _gradG, _gradB));
            strip.fillGradient(NUMLEDS / 2, NUMLEDS, mRGB(_gradR, _gradG, _gradB), mRGB(gradR, gradG, gradB));
        } break;
        case 3: {
          rainbow();
        } break;
        case 4: {
          runningDots();
        } break;
        case 5: {
          colorCycle();
          breathing();
        }
      }
    } else {
      strip.setBrightness(0);
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
}

void runningDots() {
  static byte counter = 0;
  // перемотка буфера со сдвигом (иллюзия движения пикселей)
  for (int i = 0; i < NUMLEDS - 1; i++) strip.leds[i] = strip.leds[i + 1];

  // каждый третий вызов - последний пиксель красным, иначе чёрным
  if (counter % 3 == 0) strip.leds[NUMLEDS - 1] = mRGB(dotsR, dotsG, dotsB);
  else strip.leds[NUMLEDS - 1] = mBlack;
  counter++;
  delay(dotSpeed);   // дополнительная задержка
}
void colorCycle() {
  static byte counter = 0;
  strip.fill(mWheel8(counter));
  counter += 2;
}
void breathing() {
  static int dir = 1;
  static int bright = 0;
  bright += dir * 10;    // 5 - множитель скорости изменения

  if (bright > 255) {
    bright = 255;
    dir = -1;
  }
  if (bright < 30) {
    bright = 30;
    dir = 1;
  }
  strip.setBrightness(bright);
}
