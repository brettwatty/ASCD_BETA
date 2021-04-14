#include <ClientWIFI.h>

ClientWIFI::ClientWIFI()
{
}

void ClientWIFI::init()
{
    delay(5000);
    Serial.begin(BAUD_RATE_ESP);
    Serial.setTimeout(5);
    WiFi.begin(config.ssid, config.password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

void ClientWIFI::cycleClientWifi()
{
    if (updateUnitDataString != "")
    {
        String resultUpdateUnitData = updateUnitData();
        updateUnitDataString = "";
        Serial.println(resultUpdateUnitData);
    }
    else
    {
        while (Serial.available() > 0)
        {
            updateUnitDataString = Serial.readString(); // read the incoming data as string
            updateUnitDataString.trim();
        }
    }
}

String ClientWIFI::updateUnitData()
{
    if (client.connect(config.server, 80))
    {
        client.print("GET /update_unit_data.php?");
        client.print("UH=");
        client.print(config.userHash);
        client.print("&");
        client.print("CD=");
        client.print(config.CDUnitID);
        client.print(updateUnitDataString);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(config.server);
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

String ClientWIFI::readPage()
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
