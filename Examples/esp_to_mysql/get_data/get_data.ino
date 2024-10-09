#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  

const char* ssid = "";
const char* password = "";
const char* URL = "http://192.168.1.4/url/getdata.php";

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  String id = "1";  
  
  getdata(id);

  delay(5000);
}

void getdata(String id) {  
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST("id=" + id);
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Dữ liệu nhận được: " + payload);


    int jsonStart = payload.indexOf("{"); 
    if (jsonStart != -1) {
      String jsonData = payload.substring(jsonStart); 
      Serial.println("Dữ liệu JSON: " + jsonData);
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, jsonData);
      if (!error) {
        if (doc.containsKey("error")) {
          Serial.println(doc["error"].as<String>());
        } else {
          Serial.print("ID: ");
          Serial.println(doc["id"].as<int>());
          Serial.print("Data: ");
          Serial.println(doc["data"].as<String>());
        }
      } else {
        Serial.println("Lỗi trong việc phân tích cú pháp JSON");
      }
    } else {
      Serial.println("Không tìm thấy dữ liệu JSON trong phản hồi");
    }
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
