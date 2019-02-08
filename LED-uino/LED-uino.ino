#include <Adafruit_NeoPixel.h>

#define PIN 3
#define NUM_LEDS 120
int val;

uint32_t x;
String input;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t blue = strip.Color(0,0,255);
uint32_t red = strip.Color(0,255,0);
uint32_t purple = strip.Color(0,255,255);
uint32_t white = strip.Color(255,255,255);
void colorOn(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    
  }
}
void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600); 
  Serial.write("Hello Im awake\n");
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i*1+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void loop() {
    x = Serial.available();
    if(x>0){
      input = Serial.readStringUntil('\n');
      
      if(input == "red"){
        colorOn(strip.Color(255, 0, 0));
      }
      else if(input == "green"){
        colorOn(strip.Color(0,255,0));
      }
      else if(input == "off"){
        colorOn(strip.Color(0,0,0));
      }
      else if(input == "white"){
        colorOn(strip.Color(255,255,255));
      }
      else if(input == "lue"){
        colorOn(strip.Color(0,0,255));
      }
      else if(input == "purple"){
        colorOn(strip.Color(255,0,255));
      }
      else if(input == "rainbow"){
        while(1 == 1) {
          rainbow(1);
        }
      }
    }
}
