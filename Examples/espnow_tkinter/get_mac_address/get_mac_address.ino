#include <WiFi.h>          
#include <esp_wifi.h>      

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();  
  delay(100);  
  
  String macAddress = WiFi.macAddress();
  Serial.print("MAC Address using WiFi library: ");
  Serial.println(macAddress);
  uint8_t mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, mac);  
  Serial.print("MAC Address using esp_wifi_get_mac: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);  
    if (i < 5) Serial.print(":");   
  }
  Serial.println();
}
void loop() {
}
