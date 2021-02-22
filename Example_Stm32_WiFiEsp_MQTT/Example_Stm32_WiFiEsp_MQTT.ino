#include "WiFiEsp.h"
#include "PubSubClient.h"

#define BUTTON_PIN 9
#define LED_PIN PC13


char* wifi_ssid = "your-ssid";
char* wifi_password = "your-pass";

char* mqtt_server = "test.mosquitto.org";
int mqtt_port = 1883;
char* mqtt_clientID = "ESP8266";
char* mqtt_username = "";
char* mqtt_password = "";

char* mqtt_publish_topic = "teste";
char* mqtt_subscribe_topic = "teste";

unsigned long lastclientloop;

WiFiEspClient espClient;
PubSubClient client(espClient);
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void setup_wifi() {

  // initialize serial for ESP module
  Serial1.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial1);
  
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED_PIN, HIGH);   // Turn the LED on
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn the LED off
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_clientID,mqtt_username,mqtt_password)) {
      Serial.println("connected");

      //Subscribe
      client.subscribe(mqtt_subscribe_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char msg[50];
int buttonState = 0;

void loop() {
  if(millis() - lastclientloop > 1000) {
      boolean clientconnected = client.loop();
      if(!clientconnected) {
        reconnect();
      }
      lastclientloop = millis();
  }

}
