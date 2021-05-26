#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> // Download library

const char* ssid="Hotspot-Harian"; // SSID wifimu
const char* pass="17171717"; // Password wifimu
const char* brokerUser = "kelompok5";
const char* brokerPass = "kelompok5";
const char* broker = "192.227.88.110";
const char* outTopic ="vokasipedia";
const char* inTopic ="Displays/vokasipedia/in";
WiFiClient espClient;
PubSubClient client(espClient);
long currentTime, lastTime;
int count = 0;
char messages[50];

void setupWifi(){
    delay(100);
    Serial.print("\nConnecting to");
    Serial.println(ssid);WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print("-");
    }
    Serial.print("\nConnected to ");
    Serial.println(ssid);
}
void reconnect(){
    while(!client.connected()){
        Serial.print("\nConncting to ");
        Serial.println(broker);
        if(client.connect("bab12", brokerUser, brokerPass)){
            // if(client.connect("espnext01")){
            Serial.print("\nConnected to ");
            Serial.println(broker);
            client.subscribe(inTopic);
        } else {
            Serial.println("\n Trying to reconnect");
            delay(5000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Nachricht empfangen: ");
    Serial.println(topic);
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
    }
    Serial.println();
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    setupWifi();
    client.setServer(broker, 1883);
    client.setCallback(callback);
}
void loop() {
    // put your main code here, to run repeatedly:
    if (!client.connected()){
        reconnect();}
        client.loop();
        currentTime = millis();
    if(currentTime - lastTime > 2000){
        count++;
        snprintf(messages, 75, "Nicky: %ld", count); // count dirubah jadi nama
        Serial.print("Sending Messages: ");
        Serial.println(messages);
        client.publish(outTopic, messages);
        lastTime = millis();
    }
}
