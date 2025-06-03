#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Configurações de Wifi

// IP estático desejado
// IPAddress local_IP(172,17,86,7);     // IP do ESP32 na rede
// IPAddress gateway(172,17,86,254);       // IP do roteador
// IPAddress subnet(255,255,255,0);      // máscara de sub-rede
// IPAddress primaryDNS(8,8,8,8);        // DNS primário (ex: Google)
// IPAddress secondaryDNS(8,8,4,4);      // DNS secundário (opcional)
const char* ssid = "ZAA-Automacao";
const char* password = "septimio";

// Configurações do MQTT Broker
const char* mqtt_server = "192.168.0.84";
const int port = 1883;
const char* topic = "leituras/im_here";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
    delay(10);
    // configura IP estático
    // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    //     Serial.println("Falha ao configurar IP estático");
    // }

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
        Serial.print("Attempting MQTT connection to ");
        Serial.print(mqtt_server);
        Serial.print("...");
        // Attempt to connect
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

