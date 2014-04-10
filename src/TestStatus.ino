#include <FastSPI_LED2.h>
#include <Animation.h>

#define LED_COUNT 60
struct CRGB leds[LED_COUNT];

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

int mPulseInterval;
char mColor;
int mBrightness;
int mCommandStartTime;
char mLastColor;

void setup()
{
  mPulseInterval = 0;
  mColor = 't';
  mBrightness = 93;

  LEDS.addLeds<WS2811, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0));
  LEDS.setBrightness(mBrightness); // Limit max current draw to 1A
  LEDS.show();
}

void color() {
  switch(mColor) {
    case 'r':
      set_rgb(254, 0, 0);
      return;
    case 'g':
      set_rgb(0, 254, 0);
      return;
    case 'b':
      set_rgb(0, 0, 254);
      return;
    case 'y':
      set_rgb(254, 254, 0);
      return;
    case 'w':
      set_rgb(254, 254, 254);
      return;
    case 't':
      test_sequence();
      return;
    case 'x':
      rainbow();
      return;
    case 'c':
      cop();
      return;
    case 'i':
      indefinite_progress();
      return;
    case 'd':
      deploy();
      return;
  }
}

void draw_rocket(int start){

  int fire_start   = start;
  int fire_stop    = start + 3;
  int rocket_start = fire_stop;
  int rocket_stop  = fire_stop + 4;

  if (rocket_stop >= LED_COUNT)
  {
    return set_color(mLastColor);
  }

  for (int i = fire_start; i < fire_stop; ++i)
  {
    set_led_rgb(i, 254, random(254), 0);
  }

  for (int i = rocket_start; i < rocket_stop; ++i)
  {
    set_led_rgb(i, 0, 0, 255);
  }

  for (int i = rocket_stop; i < LED_COUNT; ++i)
  {
    set_led_rgb(i, 0,0,0);
  }

  for (int i = 0; i < fire_start; ++i)
  {
    set_led_rgb(i, 0,0,0);
  }
}

void deploy(){

  for (int i = 0; i < LED_COUNT; ++i)
  {
    draw_rocket(i);
  }

}

void cop() {
  int now = millis() / 100;
  int phase = now % 5;

  switch(phase) {
    case 0:
    case 1:
      set_rgb(254, 0, 0);
      return;
    case 2:
    case 3:
      set_rgb(0, 0, 254);
      return;
    case 4:
      set_rgb(254, 254, 254);
      return;
  }
}

void indefinite_progress() {
  int time_elapsed = millis() - mCommandStartTime;

  if(time_elapsed > 5000) {
    return set_color(mLastColor);
  }

  int leds_to_show = time_elapsed / (5000 / LED_COUNT);

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if(i <= leds_to_show) {
      leds[i].r = 254;
      leds[i].g = 0;
      leds[i].b = 254;
    } else {
      leds[i].r = 0;
      leds[i].g = 0;
      leds[i].b = 0;
    }
  }
  LEDS.show();
}

bool is_color(char character) {
  return (character == 'r' || character == 'g' || character == 'b' || character == 'y' || character == 'w');
}

void pulse() {
  if (mPulseInterval <= 0) {
    LEDS.setBrightness(mBrightness);
    return;
  }

  int now = (millis() / mPulseInterval) % (93 * 2);
  int phase = 93 - now;
  LEDS.setBrightness(abs(phase * mBrightness / 93));
  LEDS.show();
}

void rainbow() {
  int now = millis() / 50;
  int r = now;
  int g = now + 84;
  int b = now + 84 + 84;

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i].r = (r + i) % 254;
    leds[i].g = (g + i) % 254;
    leds[i].b = (b + i) % 254;
  }
  LEDS.show();
}

void set_brightness(char character) {
  if (character < 48 || 57 < character) {
    return;
  }

  mBrightness = (character - 48) * 10;
}

void set_color(char character) {
  switch(character) {
    case 'r':
    case 'g':
    case 'b':
    case 'y':
    case 'w':
    case 't':
    case 'x':
    case 'c':
    case 'i':
    case 'd':
      mCommandStartTime = millis();
      mLastColor = mColor;
      mColor = character;
      return;
    }
}

void set_pulse_interval(char mode) {
  switch(mode) {
    case 'f':
      mPulseInterval = 2;
      return;
    case 'p':
      mPulseInterval = 4;
      return;
    case 's':
      mPulseInterval = 0;
      return;
  }
}

void set_rgb(int r, int g, int b) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB(r,g,b);
  }
  LEDS.show();
}

void set_led_rgb(int index, int r, int g, int b) {
  leds[index] = CRGB(r,g,b);
  LEDS.show();
}

void test_sequence() {
  int interval = 254 / LED_COUNT;
  for(int i=0; i < LED_COUNT; i += 1) {
    leds[i] = CRGB(254 - (i * interval), 0, (i * interval));
  }
  LEDS.show();
}

void loop() {
  while(Serial.available() > 0) {
    char character = Serial.read();
    set_brightness(character);
    set_color(character);
    set_pulse_interval(character);
  }

  color();
  pulse();
}
