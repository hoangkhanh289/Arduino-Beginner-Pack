#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";
const char* URL = "http://192.168.1.4/url/uploaddata.php";

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  String id = "2";
  String data = "hello! i am updated data";
  upload_data(id, data);  // Gọi hàm với tham số
  
  delay(5000);
}

void upload_data(String id, String data) {  // Nhận tham số id và data
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = "id=" + id + "&data=" + data;
  int httpCode = http.POST(postData);
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Dữ liệu nhận được: " + payload);
  } else {
    Serial.println("Lỗi trong POST request");
  }
  http.end();
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
