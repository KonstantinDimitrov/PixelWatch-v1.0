#include <Wire.h>              // I2C aka TWI library
#include <Time.h>              // Time manipulation librarry
#include <DS1307RTC.h>         // RTC library
#include <Adafruit_NeoPixel.h> // NeoPixel library

#define PIN  7       // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 12 // How many NeoPixels are attached to the Arduino?

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();          // This initializes the NeoPixel library.
  pixels.setBrightness(25);// Sets brightness of NeoPixels
  Wire.begin();            // This initializes the Wire library.
}

void loop()
{
tmElements_t tm;
      RTC.read(tm); // Reads time from RTC
      
  uint8_t numHourPixels = tm.Hour;                // Time hours
  uint8_t numMinPixels = ((tm.Minute) * 12) / 59; // Time minutes
  uint8_t numSecondPixels = ((tm.Second)*12)/60;  // Time seconds

  if (numSecondPixels == 0)
    numSecondPixels = 12;
  if (numHourPixels == 0)
    numHourPixels = 12;
  if (numHourPixels > 12)
    numHourPixels -= 12;
    if (numMinPixels == 0)
    numMinPixels = 12;

  uint8_t r, g, b;
  for (int i=0; i<12; i++) {
    r = 0;
    g = 0;
    b = 0;
    if (i == numMinPixels - 1)
      r = 255;                        // Set color for the minutes
    if (i == numSecondPixels - 1)
      g = 255;                        // Set color for the seconds
    if (i == numHourPixels - 1)
      b = 255;                        // Set color for the hours

    pixel.setPixelColor(i, r, g, b); // Pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}



