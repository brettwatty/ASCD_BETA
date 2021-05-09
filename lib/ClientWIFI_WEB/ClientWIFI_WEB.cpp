#include <ClientWIFI_WEB.h>

#include "ClientWIFI_WEB_Page.h"

ClientWIFI_WEB::ClientWIFI_WEB()
{
}

void ClientWIFI_WEB::init()
{
    // -------------------------------------------------
    // Serial
    // delay(5000); // Delay to wait for Arduino to start
    Serial.begin(BAUD_RATE_ESP);
    Serial.setTimeout(5);
    Serial.println();
    Serial.println();
    // -------------------------------------------------
    // EEPROM

    EEPROM.begin(512);

    setAddressSize();
    checkEEPROMEmpty();
    emptyEEPROM = false;
    if (emptyEEPROM == true)
    {
        Serial.println(F("EEPROM is empty - Setting WIFI Mode to AP for setup"));
        Serial.println();
        modeAP();
    }
    else
    {
        Serial.print(F("EEPROM is not empty - Checking connection to AP"));
        if (!connectWIFI())
        {
            Serial.println();
            Serial.print(F("Can't connect to AP: "));
            Serial.println(wifiSSID);
            Serial.println(F("Setting WIFI Mode to AP for setup"));
            Serial.println();
            modeAP();
        }
        else
        {
            Serial.println();
            Serial.print(F("Connected to AP: "));
            Serial.println(wifiSSID);
        }
    }

    // -------------------------------------------------
}

bool ClientWIFI_WEB::connectWIFI()
{
    byte count = 0;
    WiFi.disconnect();
    delay(1000);
    WiFi.begin(wifiSSID, wifiPassword); //Connect to your WiFi router
    // Serial.println("");
    // Serial.print("Connecting to AP: ");
    // Serial.println(SSID);
    // Wait for connection
    while (count < 30)
    {
        Serial.print(".");
        if (WiFi.status() == WL_CONNECTED)
        {
            // Serial.println("");
            // Serial.println("Connected");
            // Serial.print("IP address: ");
            // Serial.println(WiFi.localIP()); //IP address assigned to your ESP
            return true;
        }
        delay(500);
        count++;
    }
    // Serial.println("");
    // Serial.println("Can't connect to WIFI");
    return false;
}

void ClientWIFI_WEB::modeAP()
{
    scanSSID();
    delay(500);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(SSID);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP SSID: ");
    Serial.println(SSID);
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", [this] { handleRoot(); });
    server.on("/getSSID", [this] { handleSSID(); });
    server.begin(80);
    Serial.println("HTTP server started");
}

void ClientWIFI_WEB::cycleClientWifi()
{
    server.handleClient();
}

void ClientWIFI_WEB::handleRoot()
{
    server.send(200, "text/html", mainPage);
    // server.send(200, "text/html", "hello bretto");
}

void ClientWIFI_WEB::handleSSID()
{
    server.send(200, "text/plane", commaSSID); //Send web page
}

void ClientWIFI_WEB::scanSSID()
{
    Serial.println(F("Searching for WIFI AP's"));
    WiFi.disconnect();
    delay(100);
    WiFi.mode(WIFI_STA);
    delay(100);
    byte countSSID = WiFi.scanNetworks();
    Serial.print(F("Found: "));
    Serial.print(countSSID);
    Serial.println(F(" AP(s)"));
    for (byte i = 0; i < countSSID; ++i)
    {
        if (i != 0)
            commaSSID += ",";
        commaSSID += WiFi.SSID(i);
        Serial.println(WiFi.SSID(i));
    }
    Serial.println();
}

void ClientWIFI_WEB::getEEPROM()
{
    addressEEPROM = 0;

    EEPROM.get(addressEEPROM, wifiSSID);
    addressEEPROM += sizeof(wifiSSID);

    EEPROM.get(addressEEPROM, wifiPassword);
    addressEEPROM += sizeof(wifiPassword);
}

void ClientWIFI_WEB::setAddressSize()
{
    addressCountEEPROM = 0;
    addressCountEEPROM += sizeof(wifiSSID);
    addressCountEEPROM += sizeof(wifiPassword);
}

void ClientWIFI_WEB::checkEEPROMEmpty()
{
    byte countEmptyAddresses = 0;
    byte valueEEPROM;
    for (byte i = 0; i < addressCountEEPROM; i++)
    {
        valueEEPROM = EEPROM.read(i);
        if (valueEEPROM == 255)
        {
            countEmptyAddresses++;
        }
    }
    if (addressCountEEPROM == countEmptyAddresses)
    {
        // EEPROM is EMPTY
        emptyEEPROM = true;
    }
    else
    {
        // EEPROM is NOT EMPTY
        emptyEEPROM = false;
    }
}