#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

// 2 : Trigger on with button
#define LED_PIN                 3
//#define BUTTON_PIN            2
boolean sensorState_1 =       false;
int sensorSensitivity  =      500;

//boolean prevSensorState_1 = true;

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // What ?? turn off autocalibrate on channel 1 - just as an example
   Serial.begin(115200);
   pinMode(LED_PIN, OUTPUT);
}

void loop()                    
{
  //variables and measures for sensor inputs
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);   // changing this parameter calibrates sensitivity too
    long total2 =  cs_4_6.capacitiveSensor(30);
    long total3 =  cs_4_8.capacitiveSensor(30);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3

    delay(10);                             // arbitrary delay to limit data to serial port


    
    if (total1 > sensorSensitivity) {
        sensorState_1 = true; //switch button state
         if (sensorState_1 == true) {
        digitalWrite(LED_PIN, HIGH);
      }
     }
      
      else {
        sensorState_1 = false;
        digitalWrite(LED_PIN, LOW);
      }
      //small delay - why?
//      delay (200);


// Keeping the previous state makes it a touch switch
//
//   if(total1 > sensorSensitivity) {
//   // if we are changing state
//   if(sensorState_1 != prevSensorState_1) {
////    delay(200);
//    sensorState_1 = !sensorState_1;
//    prevSensorState_1 = sensorState_1;
//   }
//  }
//  // switch the prev state to be the OPPOSITE of button state
//  // when buttonVal is LOW...
//  else {
//    prevSensorState_1 = !sensorState_1;
//  }
//   
//  if(sensorState_1 == true) {
//    digitalWrite(LED_PIN,HIGH);
//  } else {
//    digitalWrite(LED_PIN,LOW);
//     
//}

}
