//Add necessary libraries
#include <esp_now.h>  //To access the esp now functions
#include <WiFi.h>     //To Add Wifi Capabilities on ESP32

/*define the data types of  the multiple variables structured and
renamed all of it as struct_message*/
typedef struct struct_message {
    char a[32];
    bool e;
} struct_message;
bool coffeeTime = false;
const byte ledPin = 14;
// Create a variable struct_message called myData
struct_message myData;

// function called when the data is received and prints it
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  coffeeTime = myData.e;
  Serial.println();
}
 
void setup() {
  //Set the baud rate for serial communication with ESP
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);  //Starts the wifi

 // Init ESP-NOW and returns its status
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv); //call the function OnDataRecv after receiving ESPNOW data
}
void loop() {
  if(coffeeTime){
    digitalWrite(ledPin, HIGH);
  } else{
    digitalWrite(ledPin, LOW);
  }
}