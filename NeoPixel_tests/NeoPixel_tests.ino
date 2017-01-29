// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN   6
#define pinA  A0


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      108

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int numReadings = 40;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


int delayval = 1; // delay for half a second

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

void setup() {
  pinMode(pinA, INPUT);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
//  while (millis() < 5000) {
//    sensorValue = analogRead(pinA);
//
//    // record the maximum sensor value
//    if (sensorValue > sensorMax) {
//      sensorMax = sensorValue;
//    }
//
//    // record the minimum sensor value
//    if (sensorValue < sensorMin) {
//      sensorMin = sensorValue;
//    }
//  }
}

void loop() {
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(pinA);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;

  uint16_t value_4 = map(average, 80, 645, 0, pixels.numPixels());
  uint16_t value_5 = map(average, 80, 645, 0, 255);
  for (uint16_t i=0; i<value_4; i++){
    
    pixels.setPixelColor(i, 127, 0,0);
  }  
  for (uint16_t i=value_4; i<pixels.numPixels(); i++){ 
  pixels.setPixelColor(i, 0,0,127);
}
  pixels.show();
  

}
