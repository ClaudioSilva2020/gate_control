#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "comm_manager.h"
#include "switches.h"

const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* topic_a = "gate_a";
const char* topic_b = "gate_b";
const char* mqtt_username = "gm";
const char* mqtt_password = "gm123";

#define TIME_TO_WAIT  1000

CommManager commManager(SSID_P, PASSWORD, mqttServer, mqttPort, mqtt_username, mqtt_password);
switches gate_a(GATE_A);
switches gate_b(GATE_B); 


/**
 * @brief 
 * * Função callback para requisições MQTT
 * 
 * @param topic  Tópico MQTT do projeto active_pump
 * @param payload Mensagem 
 * @param length  Tamanho da menagem
 */
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");

  String message;

  for (int i = 0; i < length; i++)
  {
    message += (char) payload[i];
  }
  Serial.println(message);
  if (strcmp(topic, topic_a) == 0)
  {
    Serial.print(topic_a);
    Serial.println(message);
    if (message == "on")
    {
        Serial.println("Abrir ou fechar portão");
        gate_a.switches_toogle(TIME_TO_WAIT);
    }
    if (message == "off")
    {
        Serial.println("Fechar ou abrir Portão");
        gate_a.switches_toogle(TIME_TO_WAIT);
    }
  }else if (strcmp(topic, topic_b) == 0)
  {
    Serial.print(topic_b);
    Serial.println(message);
    if (message == "on")
    {
        Serial.println("Abrir ou fechar  Portão");
        gate_b.switches_toogle(TIME_TO_WAIT);
    }
    if (message == "off")
    {
        Serial.println("Fechar ou abrir Portão");
        gate_b.switches_toogle(TIME_TO_WAIT);
    }
  }
  
  
  
  Serial.println();
  Serial.println("-----------------------");
}

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  
  commManager.wifi_init();
  gate_a.switches_turnoff();
  gate_b.switches_turnoff();
  commManager.mqtt_init();
  commManager.setCallback(callback);
  commManager.connect();

  commManager.publish(topic_a, "join in GM");
  commManager.subscribe(topic_a);
  commManager.publish(topic_b, "join in GM");
  commManager.subscribe(topic_b);
}

void loop() 
{
  commManager.loop();
  
  
  delay(100);
  
}
