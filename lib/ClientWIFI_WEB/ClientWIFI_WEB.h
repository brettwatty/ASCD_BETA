#ifndef CLIENT_WIFI_WEB_H
#define CLIENT_WIFI_WEB_H

#include <Arduino.h>
#include <Config.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

class ClientWIFI_WEB
{
private:
    const char *SSID = "ASCD_Setup";

    bool emptyEEPROM;
    byte addressEEPROM = 0;
    byte addressCountEEPROM = 0;
    String commaSSID;

    // char wifiSSID[32];
    // char wifiPassword[64];

    const char *wifiSSID = "Taihoro";
    // const char *wifiPassword = "future-orient3d";
    const char *wifiPassword = "future-orient3d11"; // WRONG PASSWORD for testing

    // Private Class Functions
    Config config;
    ESP8266WebServer server;

    void scanSSID();

public:
    // Public Class Functions
    ClientWIFI_WEB();
    void init();
    void modeAP();
    void cycleClientWifi();
    void handleRoot();
    void handleSSID();
    
    void getEEPROM();
    void setEEPROM();
    void setAddressSize();
    void checkEEPROMEmpty();
    bool connectWIFI();
};

#endif