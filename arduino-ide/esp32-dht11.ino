#include <WiFi.h>
#include <HTTPClient.h>
#include <DHTesp.h>

DHTesp dht;
/** Task handle for the light value read task */
TaskHandle_t tempTaskHandle = NULL;
/** Pin number for DHT11 data pin */
int dhtPin = 15;

int randNumber;


// Data yang harus disesuaikan
const char* ssid = "WLAN-Spark";
const char* password = "10101010";
String nama = "Nicky";
// -end-


String serverName = "http://192.227.88.110/kelompok5_iot/insert_data.php";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  dht.setup(dhtPin, DHTesp::DHT11);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
void loop() {
  //Send an HTTP POST request every 10 minutes
  TempAndHumidity lastValues = dht.getTempAndHumidity();
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      randNumber = random(100);
      String temp = String(lastValues.temperature,0);
      String humi = String(lastValues.humidity,0);
      String serverPath = serverName + "?&nama_sensor=DHT11_"+ nama +"&temp=" + temp + "&humi=" + humi;
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);String payload = http.getString();
      Serial.println(payload);
      }
      else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
