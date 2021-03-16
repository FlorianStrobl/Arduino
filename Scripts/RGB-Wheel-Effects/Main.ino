#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define INPIN_MODE 3
#define INPIN_SPEED 4
#define INPIN_BRIGHTNESS 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

const short defaultDelay = 50;
const short defaultSpeed = 300;
const short defaultBrightness = 50;
const short startAnimationTime = 75;

byte mode = 0;
short color = 0;
short speedS = defaultSpeed;
short brightness = defaultBrightness;

bool buttonDown = true;
int timePassed = 0;

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();

  attachInterrupt(digitalPinToInterrupt(INPIN_MODE), ModeButton, RISING);
  attachInterrupt(digitalPinToInterrupt(INPIN_SPEED), SpeedButton, RISING);
  attachInterrupt(digitalPinToInterrupt(INPIN_BRIGHTNESS), BrightnessButton, RISING);

  State();

  startAnimation();
}

void loop() {
  switch (mode) {
    case 0:
      rainbow(speedS);
      break;
    case 1:
      rainbowPerPixel(speedS / 10);
      break;
    case 2:
      OneColor();
      break;
  }
}

void State() {
  Serial.println("Mode: " + (String)mode + " - " + "Brightness: " + (String)brightness + " - " + "Speed: " + (String)speedS + " - " + "Color: " + (String)color);
}

void EveryLed(int rgb[3]) {
  for (int i = 0; i < strip.numPixels(); ++i)
    strip.setPixelColor(i, strip.Color(rgb[0], rgb[1], rgb[2]));
}


void startAnimation() {
  for (int i = 0; i < strip.numPixels() * 2; ++i) {
    strip.setPixelColor(i % strip.numPixels(), strip.Color(0, 0, i < 12 ? 255 : 0));
    strip.show();
    delay(startAnimationTime);
  }
}
