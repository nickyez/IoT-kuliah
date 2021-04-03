#include <WiFi.h>
#include <HTTPClient.h>
int randNumber;
const char* ssid = "RUMAH"; // Nama wifi kalian
const char* password = "11111111"; //Password Kalian
String serverName = "http://139.162.44.93/insert_data.php/"; // alamat server kita
String namaPengguna = "NickyErlangga" // Nama kalian tanpa tanda spasi
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
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
    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}
                   
void loop() {
    //Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay) {
        //Check WiFi connection status
        if(WiFi.status()== WL_CONNECTED){
            HTTPClient http;
            randNumber = random(100);
            String serverPath = serverName + "?&nama_sensor=SensorDHT11&nilai=" + randNumber + "&user=" + namaPengguna; 
            // Your Domain name with URL path or IP address with path
            http.begin(serverPath.c_str());
            // Send HTTP GET request
            int httpResponseCode = http.GET();
            if (httpResponseCode>0) {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);String payload = http.getString();
                Serial.println(payload);
            }else {
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
