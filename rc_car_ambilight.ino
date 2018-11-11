#include <Adafruit_NeoPixel.h>

#define PIN_L1 8
#define PIN_L2 9
#define NUM_LEDS 9
#define BRIGHTNESS 250

Adafruit_NeoPixel l1 = Adafruit_NeoPixel(NUM_LEDS, PIN_L1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel l2 = Adafruit_NeoPixel(NUM_LEDS, PIN_L2, NEO_GRBW + NEO_KHZ800);

int ch3;
int c;
bool state;

void setup() {
  
  l1.setBrightness(BRIGHTNESS);
  l2.setBrightness(BRIGHTNESS);
  l1.begin();
  l2.begin();
  l1.show(); // Initialize all pixels to 'off'
  l2.show(); // Initialize all pixels to 'off'

  colorWipe(l1.Color(255, 100, 0), 50); // yellow
  wipeOut(50);
  colorWipe(l1.Color(255, 100, 0), 50); // yellow
  wipeOut(50);
  colorWipe(l1.Color(255, 100, 0), 50); // yellow
  wipeOut(50);

  pinMode(6, INPUT); // Set our input pins as such 

  c = 0;
  state = false;
 
}

void loop() {
  
  
  ch3 = pulseIn(6, HIGH, 25000); 

  if(ch3>1500 && !state) {
      state = true;
      c++;
  }

  if(ch3<1500 && state) {
      state = false;
      c++;
  }

  

  switch(c){
    case 0 : wipeOut(10); break;
    case 1 : colorWipe(l1.Color(255,255,255, 255),10); break;
    case 2 : colorWipe(l1.Color(0,0,255), 10); break;
    case 3 : colorWipe(l1.Color(255,0,0),10); break;
    case 4 : colorWipe(l1.Color(0,255,0),10); break;

  }

  if(c>4) c = 0;

}


// Fill the dots one after the other with a color
void colorWipe(uint32_t color, uint8_t wait) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    setPixel(i, color);  
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void wipeOut(uint8_t wait) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    setPixel(i, l1.Color(0,0,0));  
    delay(wait);
  }
}

void setPixel(uint8_t i, uint32_t color){
    l1.setPixelColor(i, color);
    l1.show();
    l2.setPixelColor(i, color);
    l2.show();
}

void setLine(uint32_t color){

  for(uint16_t i=0; i<NUM_LEDS; i++) {
    setPixel(i, color);   
  }

}

