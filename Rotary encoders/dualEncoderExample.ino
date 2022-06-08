#include <Encoder.h>
#include <BitsAndDroidsFlightConnector.h>

BitsAndDroidsFlightConnector connector = BitsAndDroidsFlightConnector();

//For best results use interupt pins:
//Arduino Mega pins 2,3,18,19,20,21
//Arduino Uno pins 2,3
//Arduino Micro/Leonardo 0,1,2,3,7
//Other brands lookup which pins are interupt capable
Encoder innerEncoder(2,3);
Encoder outerEncoder(18,19);

const byte switchPin = 4;

long oldPositionInner = -9999;
long oldPositionOuter = -9999;

byte oldBtnState = HIGH;

void setup() {
  //The default rate at which the connector communicates
  Serial.begin(115200);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {

  long innerValue = innerEncoder.read();
  if(innerValue != oldPositionInner){ 
    //By determining if the value is bigger or smaller than the oldValue 
    //we can determine which direction we're turning 
    if(innerValue > oldPositionInner){
      connector.send(sendCom1FractInc);
    } else {
      connector.send(sendCom1FractDecr);
    }
    //Make sure to set the value to the old value
    oldPositionInner = innerValue;
  }

  long outerValue = outerEncoder.read();
  if(outerValue != oldPositionOuter){  
    if(outerValue > oldPositionOuter){
      connector.send(sendCom1WholeInc);
    } else {
      connector.send(sendCom1WholeDec);
    }
    oldPositionOuter = outerValue;
  }

  
  byte currentButtonState = digitalRead(switchPin);
  if(currentButtonState != oldBtnState){
    //Swap coms when the button state changed from HIGH to LOW
    if(oldBtnState == HIGH){
      connector.send(sendSwapCom1);
    }
    oldBtnState = currentButtonState;
  }
  

}
