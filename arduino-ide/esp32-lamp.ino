#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define LED1 2
#define LED2 4
#define LED3 16
int randNumber;

//SSID dan Password wifi atau hotspot kalian
const char* ssid = "RUMAH";
const char* password = "11111111";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.227.88.110/kelompok5_iot/lampu/service_lamp.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
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
                const char* token1=doc[0]["status_lampu"];
                const char* token2=doc[1]["status_lampu"];
                const char* token3=doc[2]["status_lampu"];
                //Serial.println(token);
                //Serial.print("nyoba ");
                String kondisilamp1 = String(token1);
                String kondisilamp2 = String(token2);
                String kondisilamp3 = String(token3);
                if (kondisilamp1=="yes"){
                    digitalWrite(LED1,HIGH);
                    Serial.print("nyala");
                }
                if (kondisilamp1=="no"){
                    digitalWrite(LED1,LOW);
                    Serial.print("mati");
                }
                if (kondisilamp2=="yes"){
                    digitalWrite(LED2,HIGH);
                    Serial.print("nyala");
                }
                if (kondisilamp2=="no"){
                    digitalWrite(LED2,LOW);
                    Serial.print("mati");
                }
                if (kondisilamp3=="yes"){
                    digitalWrite(LED3,HIGH);
                    Serial.print("nyala");
                }
                if (kondisilamp3=="no"){
                    digitalWrite(LED3,LOW);
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
