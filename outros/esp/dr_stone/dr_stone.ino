#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Configurações de Wifi
const char* ssid = "TCEGO-PUBLIC";
const char* password = "";

// Configurações do MQTT Broker
const char* mqtt_server = "172.19.19.136";
const int port = 1883;
const char* topic = "leituras/dr_stone";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}



void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        //  if (client.connect("ESP8266Client")) {
        if (client.connect("mosquito-lima")) {
            Serial.println("connected");
            // Subscribe
            // client.subscribe(topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(9600);
    setup_wifi();
    client.setServer(mqtt_server, port);
}


int contagem = 0;
const int intervalo = 60;

void loop() {
    // Conexão com a internet
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    String s = String(contagem);
    client.publish(topic, s.c_str());
    contagem = contagem + intervalo;
      
    delay(1000*intervalo); 
}

