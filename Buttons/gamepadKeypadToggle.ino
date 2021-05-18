#include <HID-Project.h>
#include <HID-Settings.h>
#include <Keypad.h>

#define ENABLE_PULLUPS
const byte ROWS = 3; //four rows
const byte COLS = 3; //three columns
byte keys[ROWS][COLS] = {
{1,2,3},
{4,5,6},
{7,8,9},
};
const byte toggle3A = 9;
const byte toggle3B = 16;
const byte toggle2A = 15;
const byte toggle2B = 14;
const byte looseButton = 8;
byte rowPins[ROWS] =  { 4, 3, 2}; 
byte colPins[COLS] = {5,6,7}; 

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




void setup() {

    pinMode(toggle3A, INPUT_PULLUP);
    pinMode(toggle3B, INPUT_PULLUP);
    pinMode(toggle2A, INPUT_PULLUP);
    pinMode(toggle2B, INPUT_PULLUP);
    pinMode(looseButton, INPUT_PULLUP);

    Gamepad.begin();
}


void loop() {
    byte toggle3AState = digitalRead(toggle3A);
    if(toggle3AState == LOW){
      Gamepad.press(10);

    }
     else if(toggle3AState == HIGH){
       Gamepad.release(10);

    }
    byte toggle3BState = digitalRead(toggle3B);
    
    if(toggle3BState == LOW){
      Gamepad.press(11);

    } else if(toggle3BState == HIGH){
       Gamepad.release(11);

    }
    
    if(digitalRead(toggle2A) == LOW){
      Gamepad.press(12);
    }
    if(digitalRead(toggle2B) == LOW){
      Gamepad.press(13);

    }
    if(digitalRead(looseButton) == LOW){
      Gamepad.press(16);

    }  else if(digitalRead(looseButton) == HIGH){
      Gamepad.release(16);
      
    }


    if(digitalRead(toggle2A) == HIGH){
      Gamepad.release(12);

    }
    if(digitalRead(toggle2B) == HIGH){
      Gamepad.release(13);

    }
 
    Gamepad.write();
    
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++) 
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:{
                      Gamepad.press(kpd.key[i].kchar);
                      Gamepad.write();
                      break;
                    }
     
                    case HOLD:break;
                    

                    case RELEASED:{
                      Gamepad.release(kpd.key[i].kchar);
                      Gamepad.write();
                      break;
                    }
      
                    case IDLE:break;
 
                } 

            }
        }
    }
    
}  
