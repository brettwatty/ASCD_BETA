// ASDC Nano 4x Arduino Charger / Discharger
// ---------------------------------------------------------------------------
// Created by Brett Watt on 03/12/2019
// Copyright 2018 - Under creative commons license 3.0:
//
// This software is furnished "as is", without technical support, and with no
// warranty, express or implied, as to its usefulness for any purpose.
//
// @brief
// ASDC Nano 4x Arduino Charger / Discharger
// Main code for the ESP8266 ESP-01
// Version 2.0.0
//
// @author Email: info@vortexit.co.nz
//           Web: www.vortexit.co.nz

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include "index.h" // HTML webpage contents with javascripts

const IPAddress apIP(192, 168, 0, 1);
const char *apSSID = "ESP8266_SETUP";
char SSID[32];
char Pass[64];
char PortalServer[64];
char UserHash[16];
char CDUnitID[8];
char BaudRate[8];
String commaSSID = "";

// readPage Variables
char serverResult[32];  // String for incoming serial data
int stringPosition = 0; // String index counter readPage()
bool startRead = false; // Is reading? readPage()

String updateUnitDataString = "";

WiFiClient client;

ESP8266WebServer server(80); //Server on port 80
DNSServer dnsServer;

void handleRoot()
{
    String page = mainPage;              //Read HTML contents
    server.send(200, "text/html", page); //Send web page
//server.send(200, "text/html", "<span>hello</span>"); //Send web page
}

void handleSettings()
{
    String strSSID = server.arg("SSID");
    Serial.print("SSID: ");
    Serial.println(strSSID);
    String strPass = server.arg("Pass");
    Serial.print("Pass: ");
    Serial.println(strPass);
    String strPortalServer = server.arg("Server");
    strPortalServer.toLowerCase();
    Serial.print("Server: ");
    Serial.println(strPortalServer);
    String strUserHash = server.arg("UserHash");
    strUserHash.toLowerCase();
    Serial.print("UserHash: ");
    Serial.println(strUserHash);
    String strCDUnitID = server.arg("CDUnitID");
    Serial.print("CDUnitID: ");
    Serial.println(strCDUnitID);
    String strBAUDRate = server.arg("BAUDRate");
    Serial.print("BAUDRate: ");
    Serial.println(strBAUDRate);
    // Clear EEPROM
    for (int i = 0; i < 192; ++i)
    {
        EEPROM.write(i, 0);
    }
    // Write to EEPROM
    for (int i = 0; i < strSSID.length(); ++i)
    {
        EEPROM.write(i, strSSID[i]);
    }
    for (int i = 0; i < strPass.length(); ++i)
    {
        EEPROM.write(32 + i, strPass[i]);
    }
    for (int i = 0; i < strPortalServer.length(); ++i)
    {
        EEPROM.write(96 + i, strPortalServer[i]);
    }
    for (int i = 0; i < strUserHash.length(); ++i)
    {
        EEPROM.write(160 + i, strUserHash[i]);
    }
    for (int i = 0; i < strCDUnitID.length(); ++i)
    {
        EEPROM.write(176 + i, strCDUnitID[i]);
    }
    for (int i = 0; i < strBAUDRate.length(); ++i)
    {
        EEPROM.write(184 + i, strBAUDRate[i]);
    }
    EEPROM.commit();
    Serial.println("Write EEPROM done!");

    server.send(200, "text/plane", "Successful - Device will Restart"); //Send web page
    delay(2000);
    ESP.restart();
}

void handleSSID()
{
    server.send(200, "text/plane", commaSSID); //Send web page
}

void setup(void)
{
    delay(5000);
    Serial.begin(115200);
    Serial.setTimeout(5);
    EEPROM.begin(512);
    Serial.println("Test");
    Serial.println("1234");
    /*
    if (readEEPROM())
    {
        //        scanSSID();
        if (!connectWIFI())
        {
            startAP();
        }
    }
    else
    {
        //        scanSSID();
        startAP();
    }*/
    startAP();
    delay(100);
    // Settings Web Page
    server.on("/", handleRoot);
    server.on("/saveSettings", handleSettings);
    server.on("/getSSID", handleSSID);
    server.begin(); //Start server
    Serial.println("HTTP server started");
}

void loop(void)
{
    server.handleClient(); //Handle client requests
    /*
    static long masterReplyMillis;
    long currentMillis = millis();
    static bool masterReply = false;
    if (masterReply)
    {

        if (updateUnitDataString != "")
        {
            String resultUpdateUnitData = updateUnitData();
            updateUnitDataString = "";
            Serial.println(resultUpdateUnitData);
        }
        else
        {
            while (Serial.available())
            {
                updateUnitDataString = Serial.readString(); // read the incoming data as string
                updateUnitDataString.trim();
            }
        }
    }
    else
    {
        if (currentMillis - masterReplyMillis >= 200) // Every 200 millis
        {
            Serial.println(WiFi.softAPIP());
            while (Serial.available())
            {
                String recievedMessage = "";
                recievedMessage = Serial.readString(); // Read the incoming data as string
                recievedMessage.trim();
                if (recievedMessage == "0")
                {
                    masterReply = true;
                }
            }
            masterReplyMillis = currentMillis;
        }
    }
    */
}

void startAP()
{

//    WiFi.disconnect();
//    delay(100);
    WiFi.mode(WIFI_AP);
//    delay(100);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
//    delay(100);
    // WiFi.softAPConfig( IPAddress(192, 168, 1, 1),  IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP(apSSID);
    // IPAddress myIP = WiFi.softAPIP();
    delay(100);
    dnsServer.start(53, "*", apIP);
    delay(100);
    Serial.print("AP IP Address: ");
    // Serial.println(myIP);
    // Serial.println(apIP);
    Serial.print("AP Name: ");
    Serial.println(apSSID);
}

String updateUnitData()
{
    if (client.connect(PortalServer, 80))
    {
        client.print("GET /update_unit_data.php?");
        client.print("UH=");
        client.print(UserHash);
        client.print("&");
        client.print("CD=");
        client.print(CDUnitID);
        client.print(updateUnitDataString);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(PortalServer);
        client.println("Connection: close");
        client.println();
        client.println();
        return readPage();
    }
    else
    {
        return "1";
    }
}

String readPage()
{
    stringPosition = 0;
    unsigned long startTime = millis();
    memset(&serverResult, 0, 32); //Clear serverResult memory
    while (true)
    {
        if (millis() < startTime + 3750) // Time out of 3750 milliseconds (Possible cause of crash on Ethernet)
        {
            if (client.available())
            {
                char c = client.read();
                if (c == '<') //'<' Start character
                {
                    startRead = true; //Ready to start reading the part
                }
                else if (startRead)
                {
                    if (c != '>') //'>' End character
                    {
                        serverResult[stringPosition] = c;
                        stringPosition++;
                    }
                    else
                    {
                        startRead = false;
                        client.stop();
                        client.flush();
                        return String(serverResult);
                    }
                }
            }
        }
        else
        {
            client.stop();
            client.flush();
            return "2"; //TIMEOUT
        }
    }
}

bool connectWIFI()
{
    byte count = 0;
    WiFi.disconnect();
    WiFi.begin(SSID, Pass); //Connect to your WiFi router
    Serial.println("");
    Serial.print("Connecting to AP: ");
    Serial.println(SSID);
    // Wait for connection
    while (count < 30)
    {
        Serial.print(".");
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("");
            Serial.println("Connected");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP()); //IP address assigned to your ESP
            return true;
        }
        delay(500);
        count++;
    }
    Serial.println("");
    Serial.println("Can't connect to WIFI");
    return false;
}

void scanSSID()
{
    Serial.println("Searching for WIFI AP's");
    WiFi.disconnect();
    delay(100);
    WiFi.mode(WIFI_STA);
    delay(100);
    byte countSSID = WiFi.scanNetworks();
    Serial.print("Found: ");
    Serial.print(countSSID);
    Serial.println(" AP(s)");
    for (byte i = 0; i < countSSID; ++i)
    {
        if (i != 0)
            commaSSID += ",";
        commaSSID += WiFi.SSID(i);
        Serial.println(WiFi.SSID(i));
    }
}

bool readEEPROM()
{
    /*if (EEPROM.read(0) != 0)
    {
        for (int i = 184; i < 192; ++i)
        {
            BaudRate[i - 184] = char(EEPROM.read(i));
        }
        int intBaudRate = atoi(BaudRate);
        Serial.begin(intBaudRate);
        Serial.println("");
        Serial.println("Reading EEPROM:");
        Serial.print("Baud Rate: ");
        Serial.println(intBaudRate);
        for (int i = 0; i < 32; ++i)
        {
            SSID[i] = char(EEPROM.read(i));
        }
        Serial.print("SSID: ");
        Serial.println(SSID);
        for (int i = 32; i < 96; ++i)
        {
            Pass[i - 32] = char(EEPROM.read(i));
        }
        Serial.print("Pass: ");
        Serial.println(Pass);
        for (int i = 96; i < 160; ++i)
        {
            PortalServer[i - 96] = char(EEPROM.read(i));
        }
        Serial.print("Server: ");
        Serial.println(PortalServer);
        for (int i = 160; i < 176; ++i)
        {
            UserHash[i - 160] = char(EEPROM.read(i));
        }
        Serial.print("User Hash: ");
        Serial.println(UserHash);
        for (int i = 176; i < 184; ++i)
        {
            CDUnitID[i - 176] = char(EEPROM.read(i));
        }
        Serial.print("CDUnitID: ");
        Serial.println(CDUnitID);
        return true;
    }
    else
    {
        Serial.println("No stored config found");
        return false;
    }
    */
    return false;
}