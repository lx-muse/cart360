#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>


/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
//CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

// *************** variables for hat
0
#define SENSOR_PIN_1   A1
#define SENSOR_PIN_2   A2
#define SENSOR_PIN_3   A3

int tiltVal1 = 0;
int tiltVal2 = 0;
int tiltVal3 = 0;



#define LEDtest_PIN             3
//#define BUTTON_PIN            2
// capacitive sensor state
boolean sensorState_1 =       false;

int sensorSensitivity  =      7000;          // or capacitive threshold
//boolean prevSensorState_1 = true;

//*************************neoPixel variable for coat
#define PIN            10
#define NUMPIXELS      1
#define BRIGHTNESS     50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

void setup(){
  // capacitive dreadlock
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // What ?? turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);
   
  //sway sensor
   pinMode(SENSOR_PIN_1, INPUT);
   pinMode(SENSOR_PIN_2, INPUT);
   pinMode(SENSOR_PIN_3, INPUT);
   
   //debug
   pinMode(LEDtest_PIN, OUTPUT);
   
   pixels.setBrightness(BRIGHTNESS);
   pixels.begin(); // This initializes the NeoPixel library.
   
   Serial.println("setup completed");                
}



void loop(){
sway();
readCapSense();
setPixels();
}

void sway(){

  
  if (analogRead(SENSOR_PIN_1) || analogRead(SENSOR_PIN_2) || analogRead(SENSOR_PIN_3) > 0){
   delay(50);
//   Serial.println(SENSOR_PIN_1);                // print sensor output 
//   Serial.println(SENSOR_PIN_2);                // print sensor output 
//   Serial.println(SENSOR_PIN_3);                // print sensor output 
//   digitalWrite(LEDtest_PIN, HIGH);


  }

    else{
    digitalWrite(LEDtest_PIN, LOW);

  pixels.show(); //Show The Color
  delay(100);

    }
}



void readCapSense(){
  //variables and measures for sensor inputs
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(2000);   // changing this parameter calibrates sensitivity too
//    long total2 =  cs_4_6.capacitiveSensor(2000);
//    long total3 =  cs_4_8.capacitiveSensor(2000);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

//    Serial.print(total1);                  // print sensor output 1
//    Serial.print("\t");
//    Serial.print(total2);                  // print sensor output 2
//    Serial.print("\t");
    Serial.println(total1);                // print sensor output 3
//
    delay(10);                             // arbitrary delay to limit data to serial port


    
    if (total1 > sensorSensitivity) {
        sensorState_1 = true; //switch button state
         if (sensorState_1 == true) {
        digitalWrite(LEDtest_PIN, HIGH);
      }
     }
      
      else {
        sensorState_1 = false;
        digitalWrite(LEDtest_PIN, LOW);
      }
      //small delay - why?
//      delay (200);

  
}

void setPixels() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}
