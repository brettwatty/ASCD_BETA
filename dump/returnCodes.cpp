#include "returnCodes.h"

returnCodes::returnCodes(byte codeID, bool debugMode = true)
{
    this->codeID = codeID;
    this->debugMode = debugMode;
    process();
}

void returnCodes::init()
{
}

void returnCodes::process()
{
    switch (codeID)
    {
    case 0: // SUCCESSFUL
        Serial.println(F("SUCCESSFUL"));
        break;
    case 1: // CONNECTION ERROR
        Serial.println(F("CONNECTION_ERROR"));
        break;
    case 2: // TIMEOUT
        Serial.println(F("TIMEOUT"));
        break;
    case 3: // ERROR_DATABASE
        Serial.println(F("ERROR_DATABASE"));
        break;
    case 4: // ERROR_MISSING_DATA
        Serial.println(F("ERROR_MISSING_DATA"));
        break;
    case 5: // ERROR_NO_BARCODE_DB
        Serial.println(F("ERROR_NO_BARCODE_DB"));
        break;
    case 6: // ERROR_NO_BARCODE_INPUT
        Serial.println(F("ERROR_NO_BARCODE_INPUT"));
        break;
    case 7: // ERROR_DATABASE_HASH_INPUT
        Serial.println(F("ERROR_DATABASE_HASH_INPUT"));
        break;
    case 8: // ERROR_HASH_INPUT
        Serial.println(F("ERROR_HASH_INPUT"));
        break;
    case 9: // ERROR_SERIAL_OUTPUT
        Serial.println(F("ERROR_SERIAL_OUTPUT"));
        break;
    case 100: // BARCODE_CONTINUE_0
        module[0].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_0"));
        break;
    case 101: // BARCODE_CONTINUE_1
        module[1].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_1"));
        break;
    case 102: // BARCODE_CONTINUE_2
        module[2].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_2"));
        break;
    case 103: // BARCODE_CONTINUE_3
        module[3].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_3"));
        break;
    case 104: // BARCODE_CONTINUE_4
        module[4].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_4"));
        break;
    case 105: // BARCODE_CONTINUE_5
        module[5].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_5"));
        break;
    case 106: // BARCODE_CONTINUE_6
        module[6].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_6"));
        break;
    case 107: // BARCODE_CONTINUE_7
        module[7].batteryBarcode = true;
        Serial.println(F("BARCODE_CONTINUE_7"));
        break;
    case 200: // INSERT_DATA_SUCCESSFUL_0
        module[0].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_0"));
        break;
    case 201: // INSERT_DATA_SUCCESSFUL_1
        module[1].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_1"));
        break;
    case 202: // INSERT_DATA_SUCCESSFUL_2
        module[2].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_2"));
        break;
    case 203: // INSERT_DATA_SUCCESSFUL_3
        module[3].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_3"));
        break;
    case 204: // INSERT_DATA_SUCCESSFUL_4
        module[4].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_4"));
        break;
    case 205: // INSERT_DATA_SUCCESSFUL_5
        module[5].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_5"));
        break;
    case 206: // INSERT_DATA_SUCCESSFUL_6
        module[6].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_6"));
        break;
    case 207: // INSERT_DATA_SUCCESSFUL_7
        module[7].insertData = true;
        Serial.println(F("INSERT_DATA_SUCCESSFUL_7"));
        break;
    default:
        Serial.println(F("UKNOWN"));
        break;
    }
}