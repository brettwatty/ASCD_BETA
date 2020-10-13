#include <ClientWIFI.h>

// #include <Config.h>

ClientWIFI::ClientWIFI()
{
}

void ClientWIFI::init()
{
    delay(5000);
    Serial.begin(57600);
    Serial.setTimeout(5);
    WiFi.begin(ssid, password);
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
    if (client.connect(server, 80))
    {
        client.print("GET /update_unit_data_dev.php?");
        client.print("UH=");
        client.print(userHash);
        client.print("&");
        client.print("CD=");
        client.print(CDUnitID);
        client.print(updateUnitDataString);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
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
