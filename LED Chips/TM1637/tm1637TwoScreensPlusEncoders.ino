#include <TM1637_6D.h>
#include<BitsAndDroidsFlightConnector.h>
#include<Encoder.h>
//connector
BitsAndDroidsFlightConnector connector(false);
//Rotary block
const byte innerA = 2;
const byte innerB = 4;
const byte outerA = 3;
const byte outerB = 5;
Encoder rotaryInner(innerA, innerB);
Encoder rotaryOuter(outerA, outerB);
long oldMhzPosition = -999;
long newMhzPosition;
long oldKhzPosition = -999;
long newKhzPosition;
//Screens
const byte dioActive = 8;
const byte clkActive = 11;
const byte dioStandby = 9;
const byte clkStandby = 10;
TM1637_6D segActiveFreq(clkActive,dioActive);
TM1637_6D segStandbyFreq(clkStandby, dioStandby);
//Button
const byte btn = 7;
const byte encoderBtn = 6;
//Variables to check against
String oldActiveCom ="123.456";
String oldStandbyCom="123.456";
String newActiveCom;
String newStandbyCom;
void setup() {
  
  Serial.begin(115200);
  Serial.setTimeout(15);
  pinMode(encoderBtn, INPUT_PULLUP);
  segActiveFreq.init();
  segActiveFreq.set(BRIGHT_TYPICAL);
  segStandbyFreq.init();
  segStandbyFreq.set(BRIGHT_TYPICAL);
  segActiveFreq.displayFloat(123.456);
  segStandbyFreq.displayFloat(123.456);
}
void loop() {
  connector.dataHandling();
  newActiveCom = connector.getActiveCom1();
  if(newActiveCom != oldActiveCom){
    segActiveFreq.displayFloat(newActiveCom.toFloat());
    oldActiveCom = newActiveCom;
  }
  newStandbyCom = connector.getStandbyCom1();
  if(newStandbyCom != oldStandbyCom){
    segStandbyFreq.displayFloat(newStandbyCom.toFloat());
    oldStandbyCom = newStandbyCom;
  }
  
  newMhzPosition = rotaryOuter.read();
  // This is an example if your encoder is too responsive
  if(newMhzPosition != oldMhzPosition){
    //if the step is bigger than 2 indents
    if(newMhzPosition - oldMhzPosition >= 2){
       Serial.println(connector.sendCom1WholeInc()); 
    } else if(newMhzPosition - oldMhzPosition <= -2){
      Serial.println(connector.sendCom1WholeDec());
    }
    oldMhzPosition = newMhzPosition;
  }
  newKhzPosition = rotaryInner.read();
  if(newKhzPosition != oldKhzPosition){
    if(newKhzPosition > oldKhzPosition){
      Serial.println(connector.sendCom1FractInc());
  } else{
    Serial.println(connector.sendCom1FractDecr());
  }
  oldKhzPosition = newKhzPosition;
  }
  if(digitalRead(encoderBtn) == LOW){
    Serial.println(connector.sendSwapCom1());
    delay(200);
  }
}
