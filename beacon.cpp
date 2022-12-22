#include <FastLED.h>

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 100
#define DATA_PIN 21
#define BRIGHTNESS 25

int speed = 200;
int NUM_RUN = 6;
int NUM_SOL = NUM_RUN*2;
int offset = NUM_RUN*4;

CRGB leds[NUM_LEDS];


void setup() {
  
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  delay(1000);
}

void loop() {


SolidLights();
RunningLights();

}

void RunningLights(){

  for (int dot1 = 0; dot1 < NUM_RUN; dot1++) {
  leds[dot1]                                      = CRGB(255, 255, 255);
  leds[dot1 + NUM_RUN]                            = CRGB(255, 255, 255);
  leds[dot1 + offset]                             = CRGB(255, 255, 255);
  leds[dot1 + NUM_RUN + offset]                   = CRGB(255, 255, 255);
  leds[dot1 + offset*2]                           = CRGB(255, 255, 255);
  leds[dot1 + NUM_RUN + offset*2]                 = CRGB(255, 255, 255);
	
  FastLED.show();
	
  leds[dot1]                                      = CRGB(35, 35, 35);
  leds[dot1 + NUM_RUN]                            = CRGB(35, 35, 35);
  leds[dot1 + offset]                             = CRGB(35, 35, 35);
  leds[dot1 + NUM_RUN + offset]                   = CRGB(35, 35, 35);
  leds[dot1 + offset * 2]                         = CRGB(35, 35, 35);
  leds[dot1 + NUM_RUN + offset * 2]               = CRGB(35, 35, 35);
	
	
  if(dot1>0) leds[dot1 - 1]                       = CRGB(10, 10, 10);
  else leds[dot1+ NUM_RUN * 2 - 1]                = CRGB(10, 10, 10);
  leds[dot1 + NUM_RUN - 1]                        = CRGB(10, 10, 10);
  if(dot1>0) leds[dot1 + offset - 1]              = CRGB(10, 10, 10);
  else leds[dot1 + NUM_RUN * 2 + offset - 1]      = CRGB(10, 10, 10);
  leds[dot1 + NUM_RUN + offset - 1]               = CRGB(10, 10, 10);
  if(dot1>0) leds[dot1 + offset * 2 - 1]          = CRGB(10, 10, 10);
  else leds[dot1 + NUM_RUN * 2 + offset * 2 - 1]  = CRGB(10, 10, 10);
  leds[dot1 + NUM_RUN + offset * 2 - 1]           = CRGB(10, 10, 10);


  if(dot1>1) leds[dot1 - 2]                       = CRGB::Black;
  else leds[dot1 + NUM_RUN * 2 - 2]               = CRGB::Black;
  leds[dot1 + NUM_RUN - 2]                        = CRGB::Black;
  if(dot1>1) leds[dot1 + offset - 2]              = CRGB::Black;
  else leds[dot1 + NUM_RUN * 2 + offset - 2]      = CRGB::Black;
  leds[dot1 + NUM_RUN + offset - 2]               = CRGB::Black;
  if(dot1>1) leds[dot1 + offset * 2 - 2]          = CRGB::Black;
  else leds[dot1 + NUM_RUN * 2 + offset * 2 - 2]  = CRGB::Black;
  leds[dot1 + NUM_RUN + offset * 2 - 2]           = CRGB::Black;		

  
  delay(speed);}

}

void SolidLights(){

  fill_solid( &(leds[NUM_SOL]),             NUM_SOL, CRGB(128, 0, 0));
  fill_solid( &(leds[NUM_SOL + offset]),    NUM_SOL, CRGB(128, 0, 0));
  fill_solid( &(leds[NUM_SOL + offset*2]),  NUM_SOL, CRGB(128, 0, 0));

}
