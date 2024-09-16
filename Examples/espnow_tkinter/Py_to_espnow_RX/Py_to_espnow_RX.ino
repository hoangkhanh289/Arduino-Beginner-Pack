#include <WiFi.h>
#include <esp_now.h>
#include <TFT_eSPI.h>
#include "Image1.h"
#include <math.h>
TFT_eSPI tft = TFT_eSPI();



// Định nghĩa cấu trúc dữ liệu để nhận từ ESP-NOW
typedef struct struct_message {
  char val1[250];

} struct_message;

struct_message myData;

unsigned long previousMillis = 0;
const long interval = 100;

// Hàm callback khi nhận dữ liệu từ ESP-NOW
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  //Ở đây chúng ta đã nhận được dữ liệu từ TX và nó là biến myData.val1 (có thể dùng ì tại đây đeer thực hiện các công việc)

//=> Phần này dùng để hiển thị TFT có thể bỏ ,không ảnh hưởng đến chức năng
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    backgroud();
  }
  tft.setTextColor(TFT_RED);
  tft.setTextSize(7);  
  tft.drawString(myData.val1, 60, 100);
  //<=
}

void setup() {
  Serial.begin(115200);
//=> Phần này dùng để hiển thị TFT có thể bỏ ,không ảnh hưởng đến chức năng
  tft.begin(); 
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(1);  
  backgroud();         
//<=
  WiFi.mode(WIFI_STA); 
  esp_now_init();     
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop() {
}


//=> Phần này dùng để hiển thị TFT có thể bỏ ,không ảnh hưởng đến chức năng
void backgroud() {
  tft.pushImage(0, 0, 320, 240, image);  // Hiển thị hình ảnh nền
}
//<=