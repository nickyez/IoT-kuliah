#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define LED 2
int randNumber;

const char* ssid = "RUMAH";
const char* password = "11111111";
//Your Domain name with URL path or IP address with path
String serverName = "http://47.254.251.186/iot/service_lamp.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
    pinMode(LED,OUTPUT);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing
    the first reading.");
}
void loop() {
    //Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay) {
        //Check WiFi connection status
        if(WiFi.status()== WL_CONNECTED){
            HTTPClient http;
            randNumber = random(100);
            String serverPath = serverName;
            // Your Domain name with URL path or IP address with path
            http.begin(serverPath.c_str());
            // Send HTTP GET request
            int httpResponseCode = http.GET();
            if (httpResponseCode>0) {
                char json[500];
                String payload = http.getString();
                // Serial.println(payload);
                payload.toCharArray(json, 500);
                StaticJsonDocument<384> doc;
                DeserializationError error = deserializeJson(doc, json);
                const char* token=doc[0]["status_lampu"];
                //Serial.println(token);
                //Serial.print("nyoba ");
                String kondisilamp = String(token);
                if (kondisilamp=="yes"){
                    digitalWrite(LED,HIGH);
                    Serial.print("nyala");
                }
                if (kondisilamp=="no"){
                    digitalWrite(LED,LOW);
                    Serial.print("mati");
                }
            }else {
                Serial.print("Error code: ");
                Serial.println(httpResponseCode);
            }
            // Free resources
            http.end();
        }else {
            Serial.println("WiFi Disconnected");
        }lastTime = millis();
    }
}
