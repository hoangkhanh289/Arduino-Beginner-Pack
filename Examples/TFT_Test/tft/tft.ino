#include <TFT_eSPI.h>
#include "Image1.h"  //Tệp bitmap
TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.init();
  tft.setSwapBytes(true);

  tft.setRotation(1);  //chọn chiều màn hình
  // Đẩy ảnh bitmap lên màn hình
  // Chiều rộng và Chiều cao được cho là được xác định trong tệp Image1.h
  tft.pushImage(0, 0, Width, Height, image1);  //hàm hiển trị bitmap,số "0" đầu là vị trí bắt đầu vẽ củ chiều rộng,số "0" thứ 2 là vị trí bắt đầu vẽ củ chiều cao
  // Đặt màu chữ thành màu trắng và vẽ "Hello"
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Hello", 10, 10, 4);  // Vẽ "Hello" tại tọa độ (10, 10)

  tft.setTextColor(TFT_RED);  // Đặt màu chữ thành màu đỏ và in "TFT" trên màn hình
  tft.println("TFT");
  tft.setCursor(75, 180, 4);  // Đặt vị trí con trỏ cho văn bản
}
void loop() {
}
//Nếu bạn thắt mắc phần nào có thể bình luận cho tôi