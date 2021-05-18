#include <BitsAndDroidsFlightConnector.h>
BitsAndDroidsFlightConnector connector = BitsAndDroidsFlightConnector(true);
void setup() {
  Serial.begin(115200);

}
void loop() {
  connector.simpleInputHandling(A2);
  connector.mixtureInputHandling(A2,A2);
  connector.propsInputHandling(A2, A2);

}
