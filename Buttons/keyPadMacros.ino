#include <HID-Project.h>
#include <HID-Settings.h>
#include <Keypad.h>
/* @file MultiKey.ino
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/

#define ENABLE_PULLUPS
const byte ROWS = 3; //four rows
const byte COLS = 3; //three columns
byte keys[ROWS][COLS] = {
{1,2,3},
{4,5,6},
{7,8,9},
};

byte rowPins[ROWS] =  { 2, 4, 3}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {5,6,7}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );





void setup() {

    Keyboard.begin();
}


void loop() {
   
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:{
                      switch(kpd.key[i].kchar){
                        case 1: 
                        Keyboard.println("discord.com/invite/nRCe8Y9DzD​");
                        Keyboard.println("www.instagram.com/bitsanddroids");
                        Keyboard.println("www.patreon.com/BitsAndDroids");
                        delay(200);
                        break;
                        case 2:
                        break;
                         case 3:
                        break;
                         case 4:
                        break;
                         case 5:
                        break;
                         case 6:
                        break;
                         case 7:
                        break;
                         case 8:
                        break;
                        case 9:              
                        break;
                      };
             
                    }
     
                    case HOLD:break;
                    

                    case RELEASED:{
                     
                      break;
                    }
      
                    case IDLE:break;
 
                } 

            }
        }
    }
    
}  // End loop
