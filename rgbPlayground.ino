#include "SPI.h"
#include "WS2801.h"

/*****************************************************************************
Example sketch for driving WS2801 pixels
*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin = 2;
int clockPin = 3;
// Don't forget to connect the ground wire to Arduino ground, and the +5V wire to a +5V supply


// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
WS2801 strip = WS2801(25, dataPin, clockPin);

// Optional: leave off pin #s to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//WS2801 strip = WS2801(25);

void setup() {
    
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();
  
  Serial.begin(9600);
}


void loop() {
  // Some example procedures showing how to display to the pixels
  
  //colorWipe(Color(255, 0, 0), 50); //red
  //colorWipe(Color(0, 255, 0), 50); //green
  //colorWipe(Color(0, 0, 255), 50); //blue
  //colorWipe(Color(255, 0, 255), 50); //pink
  //colorWipe(Color(0, 255, 255), 50); 
  //colorWipe(Color(255, 255, 0), 50); //yellow
  //colorWipe(Color(255, 255, 255), 50); //white
  //rainbow(20);
  //rainbowCycle(10);
  //randomWipe(100);
  //cylonEffect(40);
  //cylonEffect2(40); //new
  //colorCycle(); //new
  xmasEffect(240);
  //ramp();
}

void ramp() {
  int i, j, interval;
  uint32_t c;
  
  for(j = 3; j < 256; j++) {
    c = Color(j, j, j);
    for(i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
    }
    strip.show();
    //interval = int(10 * sin(j*2*3.1459/256)); //Trying to get fancy here with varying the rate of fade
    //delay(interval);
    Serial.println(10);
  }
  for(j = 255; j > 3; j--) {
    c = Color(j, j, j);
    for(i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
    }
    strip.show();
    delay(10);
  }
}      

void xmasEffect(uint8_t wait) {5
  int color, i;
  uint32_t c;
  
  for (i = 0; i < strip.numPixels(); i++) {
    color = int(random(1, 7));
    switch (color) {
      case 1:
        c = Color(255, 0, 0);  //red
        break;
      case 2:
        c = Color(0, 255, 0);  //green
        break;
      case 3:
        c = Color(0, 0, 255);  //blue
        break;
      case 4:
        c = Color(255, 0, 255);//pink
        break;
      case 5:
      c = Color(255, 255, 0);  //yellow
        break;
      case 6:
        c = Color(0, 255, 255);
        break; 
      default:
        c = Color(255, 255, 255); //white
        
    }
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}
      
//RAB created this subroutine to cause a lit element to go back and forth accross the strip.
void cylonEffect(uint8_t wait) {
  strip.show();  //blank the strip
  int i, j;
  uint32_t on, off, blue;
  
  on = Color(255, 0, 0);
  off = Color(0, 0, 0);
  blue = Color(0, 0, 255);
  
  for (i = 0; i < strip.numPixels(); i++) {   
    strip.setPixelColor(i, on);
    Serial.println(i);
    if (i>0) {
      strip.setPixelColor(i-1, off);
    }
    strip.show();
    delay(wait);
  }
  strip.setPixelColor(i-1, off);
  strip.show();
  
 for (j = strip.numPixels()-1; j > 0; j--) {
    strip.setPixelColor(j, blue);
    if (j<strip.numPixels()) {
      strip.setPixelColor(j+1, off);
    }
    strip.show();
    delay(wait);
  }
  strip.setPixelColor(j, off);
  strip.show();
}
  
// RAB created this subroutine which wipes the led strip with a random color
void randomWipe(uint8_t wait) {
  int i;
  byte random_r, random_g, random_b;
  uint32_t c;
  
  random_r = byte(random(0,256));
  random_g = byte(random(0,256));
  random_b = byte(random(0,256));
  c = Color(random_r, random_g, random_b);
  Serial.println(c);
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
