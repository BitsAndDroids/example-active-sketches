#include <TM1637_6D.h>
#include "BitsAndDroidsFlightConnector.h"

TM1637_6D screen = TM1637_6D(7, 6);
BitsAndDroidsFlightConnector connector(false);

const byte mhzRotA = 12;
const byte mhzRotB = 13;

byte mhzRotAPrev = LOW;
byte mhzRotACurrent = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(15);
  screen.init();
  screen.set(BRIGHT_TYPICAL);
}

void loop() {

  connector.dataHandling();

  screen.displayFloat(connector.getActiveCom1().toFloat());
  
  mhzRotACurrent = digitalRead(mhzRotA);
  if((mhzRotACurrent == HIGH) && (mhzRotAPrev == LOW)){
    if(digitalRead(mhzRotB)==LOW){
      Serial.println(connector.sendCom1WholeDec());
    } else {
       Serial.println(connector.sendCom1WholeInc());
    }
  }

  mhzRotAPrev = mhzRotACurrent;
  // put your main code here, to run repeatedly:

}
