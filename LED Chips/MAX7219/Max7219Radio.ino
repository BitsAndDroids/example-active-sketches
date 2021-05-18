#include<BitsAndDroidsFlightConnector.h>
#include<LedControl.h>

BitsAndDroidsFlightConnector connector(false);
LedControl segmentDisplay = LedControl(12,11,10,2);

int bufferArray[6];


long  activeCom1 = 666666L;
long  oldActiveCom1= 0L;

long  standbyCom1 = 666666L;
long  oldStandbyCom1= 0L;



void printNumbers(long numberToPrint, int screen){
   /* Our frequency has 6 digits there we loop through this code block as long as: i (our counter) is smaller than 6.
  This is because an array starts counting at 0, in our case frequency = 6 digits in our array they would be stored in 0, 1, 2, 3, 4, 5. Therefor < 6 */  
for (int i = 0; i < 6; i++) { 
    
  
   bufferArray[i] = numberToPrint % 10;
   if(i == 3){
    segmentDisplay.setDigit(screen, i, bufferArray[i], true);
   } else{
     segmentDisplay.setDigit(screen, i, bufferArray[i], false);
   }
    numberToPrint /= 10;
   }
   
         /*Divide the numberToPrint to ensure the next loop through this block checks the next tenfold. 
   In this example 123456 / 10 leaves us with 12345 (since it's an int the decimal gets ommited).
   The next loop we encounter 12345 / 10 = 1234, etc. etc. By calculating the remainder we can loop through each character per loop*/


    }
   



void setup() {
  //We start our Serial connection
  Serial.begin(115200);
  //How long the Arduino waits before moving on to the next incomming value
  Serial.setTimeout(15);

  //This block enables our screen, 
  segmentDisplay.shutdown(0,false);
  //Sets the intensity to 8(a medium brightness)
  segmentDisplay.setIntensity(0,4);
  //And clear any possible characters that are displayed at the start
  segmentDisplay.clearDisplay(0);

  //repeat the block above for the second screen
  segmentDisplay.shutdown(1,false);
  segmentDisplay.setIntensity(1,4);
  segmentDisplay.clearDisplay(1);
}

void loop() {
  connector.dataHandling();
  activeCom1 = connector.getActiveCom1();
  if(activeCom1 != oldActiveCom1){
    
    printNumbers(activeCom1, 0);
    oldActiveCom1 = activeCom1;
  }
  
  standbyCom1 = connector.getStandbyCom1();
  if(standbyCom1 != oldStandbyCom1){

    printNumbers(standbyCom1, 1);
    oldStandbyCom1 = standbyCom1;
  }
  
  
  
  
}
