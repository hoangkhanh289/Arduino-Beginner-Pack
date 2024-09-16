#include "WiFi.h"    
#include "esp_now.h"  

uint8_t broadcastAddress[] = { 0x08, 0xB6, 0x1F, 0xB8, 0xE3, 0x68 };

typedef struct struct_message {
  char val1[250];  
} struct_message;

struct_message myData;


esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200); 
  WiFi.mode(WIFI_STA);  
  esp_now_init();       

 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);  
  peerInfo.channel = 0;                             
  peerInfo.encrypt = false;                        


  esp_now_add_peer(&peerInfo);

}

void loop() {
  sending();  
}

void sending() {//Hàm này có chức năng nhận các dữ liệu từ Python(tkinter) thông qua serial và tiến hành gửi đến RX
    String data = "";
    data = Serial.readStringUntil('\r');
    data.toCharArray(myData.val1, sizeof(myData.val1));
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
}
