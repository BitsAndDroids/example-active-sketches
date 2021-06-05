//Add necessary libraries
#include <esp_now.h>  //To access the esp now functions
#include <WiFi.h>     //To Add Wifi Capabilities on ESP32

//save the MAC Address in an array named broadcastAddress;
uint8_t broadcastAddress[] = {0xB8, 0xF0, 0x09, 0xCC, 0x94, 0xEC}; //MAC address of my receiver

/*define the data types of  the multiple variables structured and
renamed all of it as struct_message*/
typedef struct struct_message {
  char a[32];
  bool landed;
} struct_message;
const byte btnPin = 14;
// Create a struct_message called myData
struct_message myData;

// function called when data is sent to print its status
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
  //Set the baud rate for serial communication with ESP
  Serial.begin(115200);
  pinMode(btnPin, INPUT_PULLUP);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);//Starts the wifi

  // Init ESP-NOW and returns its status
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //call the function OnDataSent after sending ESPNOW data
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo; //initialize and assign the peer information as a pointer to an addres
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); //copy the value of  broadcastAddress with 6 bytes to peerInfo.peer_addr
  peerInfo.channel = 0;  //channel at which the esp talk. 0 means undefined and data will be sent on the current channel. 1-14 are valid channels which is the same with the local device 
  peerInfo.encrypt = false; //not encrypted
  
  
  //Add the device to the paired device list 
  if (esp_now_add_peer(&peerInfo) != ESP_OK){ 
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  strcpy(myData.a, "Is it coffee time?"); //save "THIS IS A CHAR" to variable a of my "data" defined earlier
  

  //Send data less than or equal 250 bytes via ESP-NOW and returns its status
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
  if(digitalRead(btnPin) == LOW){
    myData.landed = true;
  } else{
    myData.landed = false;
  }
}