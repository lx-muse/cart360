#include <CapacitiveSensor.h>

/*The Art of sitting still
 * Marie-Christine Larivière
 * 
 * Travail présenté a Elio Angelo Bidinost
 * 
 * CART360
 * Concordia University
 *  11 Decembre 2020 
 * 
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

 
// *************** variables for hat
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

#define SENSOR_PIN_1   A0
#define SENSOR_PIN_2   A1
#define SENSOR_PIN_3   A2

// capacitive sensor state
boolean sensorState_1 =       false;
int sensorSensitivity  =      7000;          // or capacitive threshold
//boolean prevSensorState_1 = true;


//************* variables for tilt sensors
#define SENSOR_PIN_1   A1
#define SENSOR_PIN_2   A2
#define SENSOR_PIN_3   A3

int tiltV1 = 0;
int tiltV2 = 0;
int tiltV3 = 0;



//************************* Laser variable for coat
#define LASER_PIN       8

#define BRIGHTNESS     50

int delayval = 500; // delay for half a second

#define LEDtest_PIN             3

void setup(){
  // capacitive felting
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // What ?? turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);
   
  //sway sensor
   pinMode(SENSOR_PIN_1, INPUT);
   pinMode(SENSOR_PIN_2, INPUT);
   pinMode(SENSOR_PIN_3, INPUT);

  //out
    pinMode(LASER_PIN, OUTPUT);
   
   //debug
   pinMode(LEDtest_PIN, OUTPUT);
   digitalWrite(LASER_PIN,LOW); // just making sure the laser is off at startup or reset

   
   Serial.println("setup completed");                
}



void loop(){
sway();
readCapSense();


//setPixels();
}

void sway(){
tiltV1 = analogRead(A0); //reading the voltage on A0 and storing the value received in "voltage"
float voltage1 = tiltV1 * (3.3 / 1023.0); // transforming the value stored in "voltage" to readable information
  Serial.print("voltage is "); //sending that sentence to the serial monitor
  Serial.println(voltage1); 
  if (voltage1 > 0){
    
   Serial.println(SENSOR_PIN_1);                // print V sensor output 
 
//   digitalWrite(LEDtest_PIN, HIGH);
     digitalWrite(LASER_PIN , HIGH);

  }

    else{
    digitalWrite(LEDtest_PIN, LOW);
    digitalWrite(LASER_PIN , LOW);
//  pixels.show(); //Show The Color
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
    delay(150);                             // arbitrary delay to limit data to serial port


    
    if (total1 > sensorSensitivity) {
        sensorState_1 = true; //switch button state
         if (sensorState_1 == true) {
//        digitalWrite(LEDtest_PIN, HIGH);
        digitalWrite(LASER_PIN , HIGH);
      }
     }
      
      else {
        sensorState_1 = false;
//      digitalWrite(LEDtest_PIN, LOW);
        digitalWrite(LASER_PIN , LOW);
      }
      //small delay - why?
//      delay (200);

  
}

//void setPixels() {
//
//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//}
