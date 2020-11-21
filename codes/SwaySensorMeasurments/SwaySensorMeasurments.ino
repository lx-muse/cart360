/***** A file to measure the voltage differences from my analog sway sensor
and use it as an input for LED neopixel

Prototype for CART360
MC Larivière
*/

#include  <Adafruit_NeoPixel.h>

// light strip

#define LED_PIN         3
#define LED_COUNT       10


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)




//
#define SENSOR_PIN_1   A1
#define SENSOR_PIN_2   A2
#define SENSOR_PIN_3   A3



void setup() {
  //LED setup
  Serial.begin(57600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //Sensor setup
  pinMode(SENSOR_PIN_1, INPUT);
  pinMode(SENSOR_PIN_2, INPUT);
  pinMode(SENSOR_PIN_3, INPUT);

  
  Serial.println("setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  sway();

}

/* This function showlight when contact when contact is made
 * 
 * This function should also reads the analog voltage value from each of the sway sensor pin
 * 
 * 
 */
void sway(){
  if (analogRead(SENSOR_PIN_1) || analogRead(SENSOR_PIN_2) || analogRead(SENSOR_PIN_3) > 0){
   setPixels();
   delay(50);
     Serial.println("setPixels");
  }

    else{
  strip.show(); //Show The Color
  delay(100);

    }
 
}



void setPixels(){
  
  strip.setPixelColor(0, 255, 0, 0); //RED
  strip.show(); //Show The Color
  delay(1000);
  strip.setPixelColor(0, 0, 255, 0); //Green
  strip.show(); //Show The Color
  delay(1000);
  strip.setPixelColor(0, 0, 0, 255); //Blue
  strip.show(); //Show The Color
  delay(1000);

  
}







/* REFERENCES
 *  NEOPIXEL STRIPS?
 * https://www.arduinoplatform.com/arduino-visual-output/controlling-and-powering-neopixels-with-arduino/
 * 
 */
