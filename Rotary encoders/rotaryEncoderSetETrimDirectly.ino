#include <BitsAndDroidsFlightConnector.h>

BitsAndDroidsFlightConnector connector(false);

#define rotary1PinA 14
#define rotary1PinB 15
int value = 0;
int steps = 10;
byte rotary1PinACurrentState = LOW;
byte rotary1PinALastState = LOW;

void setup() {
  pinMode (rotary1PinA, INPUT);
  pinMode (rotary1PinB, INPUT);
  Serial.begin(115200);

}

void loop() {
  rotary1PinACurrentState = digitalRead(rotary1PinA);
  if((rotary1PinACurrentState == LOW) && (rotary1PinALastState == HIGH)){
    if(digitalRead(rotary1PinB) == LOW){
      value += steps;
     connector.sendSetElevatorTrim(value);
    } else{
      value -= steps;
     connector.sendSetElevatorTrim(value);
     }
  }
  rotary1PinALastState = rotary1PinACurrentState;
}
