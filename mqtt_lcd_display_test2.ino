#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient/

char *wifi_ssid = "ssid";
char *wifi_password = "password";

char *mqtt_server    = "mqtt.example.com";
int  mqtt_port      = 1883;
char *mqtt_username = "username";
char *mqtt_password = "password";
char *mqtt_topic    = "topic";

WiFiClient wifi_client;
PubSubClient mqtt_client(mqtt_server, mqtt_port, mqtt_sub_callback, wifi_client);

void setup() {
  Wire.begin(5, 4);
  aqm0802_init();

  aqm0802_print("MQTT LCDDisplay ");
  delay(2000);

  WiFi.begin(wifi_ssid, wifi_password);
  int wifi_count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (wifi_count % 2 == 0) aqm0802_print("WIFI    conn... ");
    else                     aqm0802_print("WIFI    conn..  ");
    wifi_count ++;
    delay(500);
  }

  aqm0802_print("MQTT    conn... ");
  delay(1000);

  if (mqtt_client.connect("client_id", mqtt_username, mqtt_password) == false) {
    aqm0802_print("conn failed...  ");
    delay(3000);
    reboot();
  }
  aqm0802_print("connected!      ");
  delay(500);
  aqm0802_clear();

  mqtt_client.subscribe(mqtt_topic);
}

void loop() {
  // for MQTT
  if (!mqtt_client.connected()) {
    reboot();
  }
  mqtt_client.loop();

  // something to do here...
}

void mqtt_sub_callback(char* topic, byte* payload, unsigned int length) {
  aqm0802_print((char*)payload, length);
}

// ESP8266 special
void reboot() {
  delay(1000);
  ESP.restart();
  while (true) {};
}

