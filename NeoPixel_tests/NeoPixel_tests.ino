

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// PIN 6 is connected to NeoPixel input
// pinA is connected to analog 0
#define PIN   13
#define pinA  A0
#define piezo_pin A1


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      97

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//For analog reading smoothing
const int numReadings = 35;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

////For analog reading smoothing
//const int numReadings_piezo = 40;
//int readings_piezo[numReadings];      // the readings from the analog input
//int readIndex_piezo = 0;              // the index of the current reading
//int total_piezo = 0;                  // the running total
//int average_piezo = 0;                // the average


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
  Serial.begin(9600);
  pinMode(piezo_pin, INPUT);
  pinMode(pinA, INPUT);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin();
  // This initializes the NeoPixel library.
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }



}

char green_flag = 0;
char blue_flag = 1;
char haha_flag = 0;


void loop() {


  int piezo_a = analogRead(piezo_pin);

  if(piezo_a > 150){
    delay(85);
    if(green_flag == 1){
      green_flag = 0;
      blue_flag = 1;
      haha_flag = 0;
    }else if (blue_flag == 1) {
      green_flag = 0;
      blue_flag = 0;
      haha_flag = 1;  
    }else{
      green_flag = 1;
      blue_flag = 0;
      haha_flag = 0;
    }
    
  }
  
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(pinA);
  //Serial.print(analogRead(pinA));
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

//  Serial.print("  greenflag=");
//  Serial.print(int(green_flag));
//  Serial.print("  blueflag=");
//  Serial.print(int(blue_flag));
//  Serial.print("  hahaflag=");
//  Serial.print(int(haha_flag));
//  Serial.print("  ");
//  Serial.print(piezo_a);
//  Serial.print("  ");
//  Serial.println(average);

  uint16_t value_4 = map(average, 100, 690, 0, pixels.numPixels());
  uint16_t value_5 = map(average, 10, 700, 0, 255);
    
  

// for for loops
//0-32
//33-66
//67-81
//81-96
//
//  for(uint16_t i=66; i<78;i++){
//    pixels.setPixelColor(i,255,0,0);
//    pixels.setPixelColor(i+1,255,0,0);
//    pixels.setPixelColor(i+2,255,0,0);
//    pixels.setPixelColor(i+3,0,0,0);
//    pixels.setPixelColor(i+4,0,0,0);
//    pixels.setPixelColor(i+5,0,0,0);
//    pixels.setPixelColor(i+6,0,0,0);
//    pixels.setPixelColor(i+7,0,0,0);
//    pixels.setPixelColor(i+8,0,0,0);
//    pixels.setPixelColor(i+9,0,0,0);
//    pixels.setPixelColor(i-1,0,255,0);
//    pixels.setPixelColor(i-2,0,0,0);
//    pixels.setPixelColor(i-3,0,0,0);
//    pixels.setPixelColor(i-4,0,0,0);
//    pixels.setPixelColor(i-5,0,0,0);
//    pixels.setPixelColor(i-6,0,0,0);
//    pixels.setPixelColor(i-7,0,0,0);
//    pixels.setPixelColor(i-8,0,0,0);
//    for (uint16_t i=0; i<32; i++){
//      pixels.setPixelColor(i,127 ,127,17);
//    }
//    for (uint16_t i=33; i<66; i++){
//      pixels.setPixelColor(i,127 ,12,127);
//    }
//    for (uint16_t i=81; i<96; i++){
//      pixels.setPixelColor(i, 27, 127, 127);
//    }
//    delay(20);
//    pixels.show();
//    //pixels.setPixelColor((i+3), 0, 0, 0);
//
//  }
//
//  for(uint16_t i=78; i>67; i--){
//    pixels.setPixelColor(i,255,0,0);
//    pixels.setPixelColor(i-1,255,0,0);
//    pixels.setPixelColor(i-2,255,0,0);
//    pixels.setPixelColor(i+3,0,0,0);
//    pixels.setPixelColor(i+4,0,0,0);
//    pixels.setPixelColor(i+5,0,0,0);
//    pixels.setPixelColor(i+6,0,0,0);
//    pixels.setPixelColor(i+7,0,0,0);
//    pixels.setPixelColor(i+8,0,0,0);
//    pixels.setPixelColor(i+9,0,0,0);
//    pixels.setPixelColor(i-1,0,0,0);
//    pixels.setPixelColor(i-2,0,0,0);
//    pixels.setPixelColor(i-3,0,0,0);
//    pixels.setPixelColor(i-4,0,0,0);
//    pixels.setPixelColor(i-5,0,0,0);
//    pixels.setPixelColor(i-6,0,0,82);
//    pixels.setPixelColor(i-7,0,10,0);
//    pixels.setPixelColor(i-8,0,0,0);
//    for (uint16_t i=0; i<32; i++){
//      pixels.setPixelColor(i,187 ,178,0);
//    }
//    for (uint16_t i=33; i<66; i++){
//      pixels.setPixelColor(i, 200, 0, 127);
//    }
//    for (uint16_t i=81; i<96; i++){
//      pixels.setPixelColor(i, 20, 0, 127);
//    }
//    delay(20);
//    pixels.show();
//  }


 
  //Start of the line
  for (uint16_t i=0; i<value_4; i++){
    if(green_flag == 1){
      pixels.setPixelColor(i, 0, 127,0);
        }else if(blue_flag == 1){
      pixels.setPixelColor(i, 127,0,0);
    }else if(haha_flag == 1){
      pixels.setPixelColor(i, 0,0, 0);
    }
  }
  //End of the line
  for (uint16_t i=value_4; i<pixels.numPixels(); i++){
        if(green_flag == 1){
      pixels.setPixelColor(i, 127, 127,0);
        }else if(blue_flag == 1){
      pixels.setPixelColor(i, 0,0,127);
    }else if(haha_flag == 1){
      pixels.setPixelColor(i, 0, 0, 0); 
    }
  }
  pixels.show();
  

}
