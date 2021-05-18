#include<BitsAndDroidsFlightConnector.h>
BitsAndDroidsFlightConnector connector(false);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  connector.sendSetYokeAxis(A0, false, A1, false, 0, 1023);
  // put your main code here, to run repeatedly:

}
