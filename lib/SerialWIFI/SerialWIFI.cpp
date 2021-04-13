// #include <Config.h>

#include <SerialWIFI.h>

#if defined(ONLINE)
#if defined(ASCD_MEGA_8X)
#define ESP8266 Serial1 // Arduino MEGA Hardware Serial1
#elif defined(ASCD_NANO_4X)
#if defined(SERIAL_PIN_SS)
#include <SoftwareSerial.h>
SoftwareSerial ESP8266(3, 2); // RX , TX
#elif defined(SERIAL_PINS_HS)
#define ESP8266 Serial // Arduino Nano Hardware Serial
#endif
#endif
#endif

SerialWIFI::SerialWIFI()
{
}

void SerialWIFI::init()
{
#if defined(ONLINE)
	#if defined(ASCD_MEGA_8X) || defined(SERIAL_PIN_SS) // If Nano uses Hardware Serial it can't print out on the same serial to console
	//Initialize USB Serial
	#ifndef SERIAL_BEGIN
		#define SERIAL_BEGIN
			Serial.begin(BAUD_RATE);
	#endif
		Serial.setTimeout(5);
	#endif
	//Initialize Software Serial for communication with the ESP8266
	ESP8266.begin(BAUD_RATE_SS);
	ESP8266.setTimeout(5);
#else
	//Initialize USB Serial
	#ifndef SERIAL_BEGIN
		#define SERIAL_BEGIN
			Serial.begin(BAUD_RATE);
	#endif
#endif
}

#if defined(ONLINE)
void SerialWIFI::ambientTemperatureSerial(byte ambientTemperature)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&AT=%d"), ambientTemperature);
}

void SerialWIFI::batteryCheckSerial(byte module)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=0"), module);
}

void SerialWIFI::batteryBarcodeSerial(byte module)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=1"), module);
}

void SerialWIFI::batteryChargeSerial(byte module, bool chargeRecharge, byte batteryInitialTemp, int batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds, int batteryVoltage, byte batteryHighestTemp)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=%d&TI%d=%d&IT%d=%d&IV%d=%d.%02d&CT%d=%d&CV%d=%d.%02d&HT%d=%d"), module, ((chargeRecharge) ? 2 : 6), module, (seconds + (minutes * 60) + (hours * 3600)), module, batteryInitialTemp, module, (int)(batteryInitialVoltage / 1000.0), (int)((batteryInitialVoltage / 1000.0) * 100) % 100, module, batteryTemp, module, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100, module, batteryHighestTemp);
}

void SerialWIFI::milliOhmsSerial(byte module, int milliOhms, int batteryVoltage)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=3&MO%d=%d&CV%d=%d.%02d"), module, module, (int)milliOhms, module, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
}

void SerialWIFI::batteryRestSerial(byte module, int milliOhms, byte batteryTemp, byte hours, byte minutes, byte seconds, int batteryVoltage)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=4&TI%d=%d&CT%d=%d&CV%d=%d.%02d"), module, module, (seconds + (minutes * 60) + (hours * 3600)), module, batteryTemp, module, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
}

void SerialWIFI::batteryDischargeSerial(byte module, byte hours, byte minutes, byte seconds, byte batteryInitialTemp, int batteryInitialVoltage, byte batteryTemp, int batteryVoltage, int dischargeAmps, int dischargeMilliamps, byte batteryHighestTemp, int milliOhms)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=5&TI%d=%d&IT%d=%d&IV%d=%d.%02d&CT%d=%d&CV%d=%d.%02d&HT%d=%d&MA%d=%d&DA%d=%d.%02d&MO%d=%d"), module, module, (seconds + (minutes * 60) + (hours * 3600)), module, batteryInitialTemp, module, (int)(batteryInitialVoltage / 1000.0), (int)((batteryInitialVoltage / 1000.0) * 100) % 100, module, batteryTemp, module, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100, module, batteryHighestTemp, module, dischargeMilliamps, module, (int)(dischargeAmps / 1000.0), (int)((dischargeAmps / 1000.0) * 100) % 100, module, milliOhms);
}

void SerialWIFI::completeSerial(byte module, byte faultCode, int batteryVoltage)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&CS%d=7&CV%d=%d.%02d&FC%d=%d"), module, module, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100, module, faultCode);
}

void SerialWIFI::sendSerial()
{
	if (strcmp(serialSendString, "") != 0) // Check if serialSendString is empty / blank
	{
		ESP8266.println(serialSendString);
		// Serial.println(serialSendString);
		strcpy(serialSendString, "");
	}
}

void SerialWIFI::clearSerialSendString()
{
	strcpy(serialSendString, "");
}

void SerialWIFI::readSerial()
{
	while (ESP8266.available() > 0)
	{
		String returnString = "";
		String receivedMessage = "";
		int returnInt;
		receivedMessage = ESP8266.readString(); // Read the incoming data as string
		delay(10);
		Serial.println(receivedMessage);
		receivedMessage.trim();
		if (receivedMessage.length() > 1) // Multiple CHAR
		{
			for (byte i = 0; i <= receivedMessage.length(); i++)
			{
				// Serial.print(F("i: "));
				// Serial.print(i);
				// Serial.print(F(" Char: "));
				// Serial.println(receivedMessage.charAt(i));
				if (receivedMessage.charAt(i) == ':' || receivedMessage.length() == i)

				{
					returnInt = returnString.toInt();
					if (returnInt != 0)
					{
						returnCodes(returnInt);
					}
					else
					{
						returnCodes(9); // ERROR_SERIAL_OUTPUT
					}
					returnString = "";
				}
				else
				{
					returnString += receivedMessage.charAt(i);
				}
			}
		}
		else
		{ // Single CHAR
			returnInt = receivedMessage.toInt();
			returnCodes(returnInt);
		}
	}
}

void SerialWIFI::returnCodes(int codeID)
{
	int moduleID;
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
	case 10: // RESET
		Serial.println(F("RESET"));
		// reboot();
		break;
	default:
		if (codeID >= 100 && codeID < 200)
		{
			moduleID = codeID - 100;
			barcodeScanned[moduleID] = true;
			Serial.print(F("BARCODE_CONTINUE_"));
			Serial.println(moduleID);
			break;
		}
		else if (codeID >= 200 && codeID < 300)
		{
			moduleID = codeID - 200;
			insertData[moduleID] = true; // Returned from Battery Portal that the data was inserted into the DB successfully.
			Serial.print(F("INSERT_DATA_SUCCESSFUL_"));
			Serial.println(moduleID);
			break;
		}
		else
		{
			Serial.println(F("UKNOWN"));
			break;
		}
	}
}

void SerialWIFI::insertDataFlag(byte module)
{
	sprintf_P(serialSendString + strlen(serialSendString), PSTR("&ID%d"), module);
}

bool SerialWIFI::getBarcodeScanned(byte module)
{
	return barcodeScanned[module];
}

void SerialWIFI::resetBarcodeScanned(byte module)
{
	barcodeScanned[module] = false;
}

bool SerialWIFI::getInsertDataFlag(byte module)
{
	return insertData[module];
}

void SerialWIFI::resetInsertDataFlag(byte module)
{
	insertData[module] = false;
}
#endif