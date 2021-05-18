#include <BitsAndDroidsFlightConnector.h>
BitsAndDroidsFlightConnector connector(false);

#define amntPins 11

enum actions{
  ALT = 0,
  BAT = 1,
  FUEL_PUMP = 2,
  BCN = 3,
  LAND = 4,
  TAXI = 5,
  NAV = 6,
  STROBE = 7,
  PITOT_HEAT = 8,
  AVIONICS_MASTER1 = 9,
  AVIONICS_MASTER2 = 10
};

const byte togglePins[amntPins] = {2,3,4,5,6,7,8,9,14,16,10};
byte lastToggleState[amntPins];
int valueToSend;
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < amntPins ; i++) {
   pinMode(togglePins[i], INPUT_PULLUP);
   lastToggleState[i] == HIGH;
  }
  // put your setup code here, to run once:

}

void loop() {
  for (int i = 0; i < amntPins; i++) {
    byte currentState = digitalRead(togglePins[i]);
    if( currentState != lastToggleState[i]){
      if(currentState == HIGH){
        switch(i){
          case ALT:{
            valueToSend =  connector.sendToggleAlternator1();
            break;
          }
          case BAT:{
            valueToSend = connector.sendToggleMasterBattery1();
            break;
          }
          case FUEL_PUMP:{
            valueToSend = connector.sendFuelPump();
            break;
          }
          case BCN: {
            valueToSend = connector.sendToggleBeaconLights();
            break;
          }
          case LAND: {
            valueToSend = connector.sendLandingLightsOn();
            break;
          }
          case TAXI: {
            valueToSend = connector.sendToggleTaxiLights();
            break;
          }
          case NAV: {
            valueToSend = connector.sendToggleNavLights();
            break;
          }
          case STROBE: {
            valueToSend = connector.sendStrobesOn();
            break;
          }
          case PITOT_HEAT: {
            valueToSend = connector.sendPitotHeatOn();
            break;
          } 
          case AVIONICS_MASTER1:{
            valueToSend = connector.sendAvionicsMaster1Off();
            break;
          }
          case AVIONICS_MASTER2:{
            valueToSend = connector.sendAvionicsMaster2Off();
            break;
          }
        }
      } else{
        switch(i){
          case ALT:{
            valueToSend =  connector.sendToggleAlternator1();
            break;
          }
          case BAT:{
            valueToSend = connector.sendToggleMasterBattery1();
            break;
          }
          case FUEL_PUMP:{
            valueToSend = connector.sendFuelPump();
            break;
          }
          case BCN: {
            valueToSend = connector.sendToggleBeaconLights();
            break;
          }
          case LAND: {
            valueToSend = connector.sendLandingLightsOff();
            break;
          }
          case TAXI: {
            valueToSend = connector.sendToggleTaxiLights();
            break;
          }
          case NAV: {
            valueToSend = connector.sendToggleNavLights();
            break;
          }
          case STROBE: {
            valueToSend = connector.sendStrobesOff();
            break;
          }
          case PITOT_HEAT: {
            valueToSend = connector.sendPitotHeatOff();
            break;
          } 
          case AVIONICS_MASTER1:{
            valueToSend = connector.sendAvionicsMaster1On();
            break;
          }
          case AVIONICS_MASTER2:{
            valueToSend = connector.sendAvionicsMaster2On();
            break;
          }
          Serial.println();
        }
      }
    delay(100);
    lastToggleState[i] = currentState;
    Serial.println(valueToSend);     
    }
    
  }
  // put your main code here, to run repeatedly:

}
