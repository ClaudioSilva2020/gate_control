/**
 * @file comm_manager.cpp
 * @author Cláudio Silva (claudiosilva@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "comm_manager.h"

#include <ESP8266WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient); 


CommManager::CommManager(const char* ssid, const char* password, const char* mqttServer, const int mqttPort, const char* mqtt_username, const char* mqtt_password)
    : ssid(ssid), password(password), mqttServer(mqttServer), mqttPort(mqttPort) , mqtt_username(mqtt_username), mqtt_password(mqtt_password)
{
}

CommManager::~CommManager()
{
}

void CommManager::begin()
{
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
    client.setClient(espClient);
    client.setServer(mqttServer, mqttPort);
}

void CommManager::wifi_init()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Conectando ao wifi ...");
    }
    Serial.println("Conectado ao wifi");
}

void CommManager::mqtt_init()
{
    client.setServer(mqttServer, mqttPort);
}

bool CommManager::isConnected()
{
    return client.connected();
}

void CommManager::loop()
{
    if (!client.connected())
    {
        connect();
    }
    client.loop();
}

void CommManager::test_conn()
{
  if (!client.connected())
  {
      connect();
  }
}

void CommManager::connect()
{
    while (!client.connected())
    {
        String client_id = "WLMCLIENT-";
        client_id += String(WiFi.macAddress());
        Serial.println("Connectando ao MQTT...");
        Serial.printf("O cliente %s conectou ao MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str()), mqtt_username, mqtt_password)
        {
            Serial.println("Conectado ao MQTT broker EMQX");
        }else
        {
            Serial.print("Falha ao conectar com o MQTT, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

bool CommManager::publish(const char* topic, const char* payload) {
  return client.publish(topic, payload, true);
}

bool CommManager::subscribe(const char* topic)
{
  return client.subscribe(topic);
}

void CommManager::setCallback(MQTT_CALLBACK_SIGNATURE)
{
    client.setCallback(callback);
}
