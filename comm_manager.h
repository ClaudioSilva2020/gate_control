/**
 * @file comm_manager.h
 * @author Cláudio Silva (claudiosilva@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __COMM_MANAGER_H__
#define __COMM_MANAGER_H__

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define SSID_P      "Claudio_2.4G"
#define PASSWORD    "*******"



class CommManager
{
    private:
        const char* ssid;
        const char* password;
        const char* mqttServer;
        const char* mqtt_username;
        const char* mqtt_password; 
        const int mqttPort;
    public:
        /**
         * @brief Construct a new Comm Manager object
         * 
         * @param ssid 
         * @param password 
         * @param mqttServer 
         * @param mqttPort 
         * @param mqtt_username 
         * @param mqtt_password 
         */
        CommManager(const char* ssid, const char* password, const char* mqttServer, const int mqttPort, const char* mqtt_username, const char* mqtt_password);
        /**
         * @brief Destroy the Comm Manager object
         * 
         */
        ~CommManager();
        /**
         * @brief 
         * * Inicia wifi e MQTT 
         * ! Não idicada pro uso
         */
        void begin();
        /**
         * @brief 
         * * Inicializa o WIFI
         */
        void wifi_init();
        /**
         * @brief 
         * * Inicializa mqtt
         * 
         */
        void mqtt_init();
        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool isConnected();
        /**
         * @brief 
         * 
         */
        void connect();
        /**
         * @brief 
         * 
         */
        void loop();
        /**
         * @brief 
         * 
         */
        void test_conn();
        /**
         * @brief 
         * 
         * @param topic 
         * @param payload 
         * @return true 
         * @return false 
         */
        bool publish(const char* topic, const char* payload);
        /**
         * @brief 
         * 
         * @param topic 
         * @return true 
         * @return false 
         */
        bool subscribe(const char* topic);
        /**
         * @brief Set the Callback object
         * 
         */
        void setCallback(MQTT_CALLBACK_SIGNATURE);
};
#endif
