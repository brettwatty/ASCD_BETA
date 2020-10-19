#ifndef CLIENT_WIFI_H
#define CLIENT_WIFI_H

#include <Arduino.h>
#include <Config.h>
#include <ESP8266WiFi.h>

class ClientWIFI
{
private:
    char serverResult[32];  // String for incoming serial data
    int stringPosition = 0; // String index counter readPage()
    bool startRead = false; // Is reading? readPage()
    String updateUnitDataString;

    // Private Class Functions
    Config config;
    WiFiClient client;

public:
    // Public Class Functions
    ClientWIFI();
    void init();
    void cycleClientWifi();
    String updateUnitData();
    String readPage();
};

#endif