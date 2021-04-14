// #include <Config.h>

#include <CycleFunctions.h>

Cycle::Cycle()
{
}

void Cycle::init()
{
// Initialize Classes.
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    outputLCD.init();
    outputLCD.startup();
#endif
#if defined(SERIAL_OUTPUT)
    outputSerial.init();
    outputSerial.startup();
#endif
    writeOutput.init();
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    inputDevices.init();
#endif
#if defined(ONLINE)
    serialWIFI.init();
#endif
    temperature.init();
    configEEPROM.init();
    readInput.init();

#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
    writeOutput.fanControl(true); // Turn on fan at boot
#endif
    // Initialize Output Pins / Analog Pins
    for (byte module = 0; module < MODULES_COUNT; module++)
    {
        writeOutput.chargeMosfetOn(module);
        delay(500);
        readInput.batteryVoltage(module);
        readInput.batteryVoltageDrop(module);
        writeOutput.chargeMosfetOff(module); // Turn off the Charge Mosfet
        delay(500);
        readInput.batteryVoltage(module);
        readInput.batteryVoltageDrop(module);
        temperature.getTemperature(module, true);
    }

#if defined(AMBIENT_TEMP_SENSOR)
    temperature.getAmbientTemperature();
#endif
#if defined(ASCD_NANO_4X)
    delay(2000); // ASCD_NANO_4X to let voltages settle
#endif
#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
    writeOutput.fanControl(false); // Turn off fan on boot
#endif
#if defined(ASCD_NANO_4X)
    buzzer.init();
#endif
}

void Cycle::cycleRun()
{
#if defined(ASCD_NANO_4X)
    if (cycleTimer.buttonCycle())
    {
        if (inputDevices.button())
        {
            buzzer.buzzerKeyPress();
            cycleTimer.setLCDActiveModule();
            mainCycle();
        }
    }
#endif
#if defined(LCD_OUTPUT)
    cycleTimer.LCDCycle();
#endif
#if defined(ONLINE)
    serialWIFI.readSerial();
    cycleTimer.serialCycle();
#endif
    if (cycleTimer.mainCycle())
    {
        mainCycle();
    }
#if defined(ONLINE)
    if (cycleTimer.getSerialCycleReady())
    {
        serialWIFI.sendSerial();
    }
#endif
}

void Cycle::mainCycle()
{
#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
    fanOn = false;
#endif
#if defined(ONLINE)
    serialWIFI.clearSerialSendString();
#if defined(AMBIENT_TEMP_SENSOR)
    serialWIFI.ambientTemperatureSerial(temperature.getAmbientTemperature());
#endif
#endif
    for (int module = 0; module < MODULES_COUNT; module++)
    {
        switch (cycleState[module])
        {
        case 0: // Check Battery Voltage
            batteryCheck(module);
            break;
#if defined(ONLINE)
        case 1: // Battery Barcode
            batteryBarcode(module);
            break;
#endif
        case 2: // Charge Battery
            cycleTimer.updateTimer(module);
            if (temperature.processTemperature(module) == 2)
            {
                faultCode[module] = 7;
                processFault(module); // Set the Battery Fault Code to 7 High Temperature
                break;
            }
            if (cycleTimer.getHours(module) == config.chargingTimeout)
            {
                faultCode[module] = 9;
                processFault(module); // Charging has reached Timeout period. Either battery will not hold charge, has high capacity or the TP5100 is faulty
                break;
            }
            batteryCharge(module, true); // True for Charge cycle False for Recharge cycle
#if defined(ASCD_NANO_4X)
            fanOn = true;
#endif
            break;
        case 3: // Check Battery Milli Ohms
            milliOhmsCycle(module);
            break;
        case 4: // Rest Battery
            cycleTimer.updateTimer(module);
            restCycle(module);
            break;
        case 5: // Discharge Battery
            cycleTimer.updateTimer(module);
            if (temperature.processTemperature(module) == 2)
            {
                faultCode[module] = 7;
                processFault(module); // Set the Battery Fault Code to 7 High Temperature
                break;
            }
            dischargeCycle(module);
#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
            fanOn = true;
#endif
            break;
        case 6: // Recharge Battery
            cycleTimer.updateTimer(module);
            if (temperature.processTemperature(module) == 2)
            {
                faultCode[module] = 7;
                processFault(module); // Set the Battery Fault Code to 7 High Temperature
                break;
            }
            if (cycleTimer.getHours(module) == config.chargingTimeout)
            {
                faultCode[module] = 9;
                processFault(module); // Charging has reached Timeout period. Either battery will not hold charge, has high capacity or the TP5100 is faulty
                break;
            }
            batteryCharge(module, false); // True for Charge cycle False for Recharge cycle
#if defined(ASCD_NANO_4X)
            fanOn = true;
#endif
            break;
        case 7: // Completed
            completeCycle(module);
            break;
        }
    }
#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
    writeOutput.fanControl((fanOn) ? true : false); // Checks if any module is charging or discharging and turn on fan or turn off
#endif
}

void Cycle::nextCycle(byte module)
{
    //
    switch (cycleState[module])
    {
    case 0: // Check Battery Voltage
#if defined(ONLINE)
        cycleState[module] = 1;
#else
        temperature.setInitialTemp(module);
        cycleState[module] = 2; // Successfully completed. Got to next cycle
        batteryInitialVoltage[module] = readInput.batteryVoltage(module);
#endif
        break;

#if defined(ONLINE)
    case 1: // Battery Barcode
        temperature.setInitialTemp(module);
        cycleState[module] = 2; // Successfully completed. Got to next cycle
        batteryInitialVoltage[module] = readInput.batteryVoltage(module);
        break;
#endif

    case 2:                                  // Charge Battery
        writeOutput.chargeMosfetOff(module); // Turn off the Charge Mosfet
        cycleState[module] = 3;              // Successfully completed. Got to next cycle
        batteryInitialVoltage[module] = readInput.batteryVoltage(module);
        break;

    case 3: // Check Battery Milli Ohms
        // if (milliOhms[module] > config.highMilliOhms || milliOhms[module] <= 0) // Check if Milli Ohms is greater than the set high Milli Ohms value -  && cycleCount[module] >= 7
        if (milliOhms[module] > config.highMilliOhms) // Check if Milli Ohms is greater than the set high Milli Ohms value -  && cycleCount[module] >= 7
        {
            faultCode[module] = 3; // Set the Battery Fault Code to 3 High Milli Ohms
            processFault(module);
            break;
        }
        else
        {
            batteryVoltage = 0;
            batteryShuntVoltage = 0;
            dischargeAmps = 0;
            cycleState[module] = 4; // Successfully completed. Got to next cycle
            batteryInitialVoltage[module] = readInput.batteryVoltage(module);
        }
        break;

    case 4: // Rest Battery
        temperature.setInitialTemp(module);
        cycleState[module] = 5; // Successfully completed. Got to next cycle
        batteryInitialVoltage[module] = readInput.batteryVoltage(module);
        break;

    case 5: // Discharge Battery
        dischargeCompleted[module] = false;
        if (dischargeMilliamps[module] < config.lowMilliAmps) // No need to recharge the battery if it has low Milliamps
        {
            faultCode[module] = 5; // Set the Battery Fault Code to 5 Low Milliamps
            processFault(module);
            break;
        }
        else
        {
            temperature.setInitialTemp(module);
            if (config.rechargeCycle)
            {
                cycleState[module] = 6; // Successfully completed. Got to next cycle
            }
            else
            {
                cycleState[module] = 7; // Successfully completed. Recharge flag is false
            }
            batteryInitialVoltage[module] = readInput.batteryVoltage(module);
        }
        break;

    case 6:                                  // Recharge Battery
        writeOutput.chargeMosfetOff(module); // Turn off the Charge Mosfet
        faultCode[module] = 0;               // Set the Battery Fault Code to 0 No Faults
        cycleState[module] = 7;              // Successfully completed. Got to next cycle
        batteryInitialVoltage[module] = readInput.batteryVoltage(module);
#if defined(ASCD_NANO_4X)
        buzzer.buzzerFinished();
#endif
        break;
    case 7: // Completed
        // Re-Initialize Variables - Batter removed - Restart the Cycle
        batteryVoltage = 0;
        batteryShuntVoltage = 0;
        dischargeAmps = 0;
        dischargeMilliamps[module] = 0.00;
        milliOhms[module] = 0;
        dischargeCompleted[module] = false;
        batteryInitialVoltage[module] = 0;
        cycleState[module] = 0; // Restart cycle back to detect battery
        temperature.clearHighestTemp(module);
#if defined(ONLINE)
        serialWIFI.resetBarcodeScanned(module);
#endif
        break;
    }
    cycleCount[module] = 0;
    cycleTimer.clearTimer(module);
#if defined(ONLINE)
    serialWIFI.resetInsertDataFlag(module);
#endif
}

void Cycle::processFault(byte module)
{
    writeOutput.chargeMosfetOff(module);    // Turn off the Charge Mosfet
    writeOutput.dischargeMosfetOff(module); // Turn off the Discharge Mosfet
    cycleTimer.clearTimer(module);
    cycleState[module] = 7;
#if defined(ASCD_NANO_4X)
    buzzer.buzzerFinished();
#endif
}

void Cycle::batteryCheck(byte module)
{
    batteryVoltage = readInput.batteryVoltage(module);
#if defined(LCD_OUTPUT)
    if (cycleTimer.getLCDActiveModule() == module)
    {
        outputLCD.batteryCheckLCD(module, batteryVoltage);
    }
#endif
#if defined(SERIAL_OUTPUT)
    outputSerial.batteryCheckSerial(module, batteryVoltage);
#endif
#if defined(ONLINE)
    serialWIFI.batteryCheckSerial(module);
#endif
    if (batteryVoltage >= config.batteryVoltageLeak)
    {
        nextCycle(module);
    }
}

#if defined(ONLINE)
void Cycle::batteryBarcode(byte module)
{
    batteryVoltage = readInput.batteryVoltage(module);
#if defined(LCD_OUTPUT)
    if (cycleTimer.getLCDActiveModule() == module)
    {
        outputLCD.batteryBarcodeLCD(module, batteryVoltage);
    }
#endif
#if defined(SERIAL_OUTPUT)
    outputSerial.batteryBarcodeSerial(module, batteryVoltage);
#endif
    if (serialWIFI.getBarcodeScanned(module))
    {
        nextCycle(module);
    }
    serialWIFI.batteryBarcodeSerial(module);
}
#endif

void Cycle::batteryCharge(byte module, bool chargeRecharge)
{
    writeOutput.chargeMosfetOn(module);
    batteryVoltage = readInput.batteryVoltage(module);
    if (readInput.chargeLed(module) || (chargeRecharge == false && config.storageChargeVoltage > 0 && batteryVoltage > (config.storageChargeVoltage * 1.09)))
    {
        if (cycleCount[module] < 8) // Possible false positive charge LED PIN results mitigation x8 cycles
        {
            writeOutput.chargeMosfetOff(module); // Turn off the Charge Mosfet
            cycleCount[module]++;
        }
        else
        {
#if defined(ONLINE)
            if (serialWIFI.getInsertDataFlag(module))
            {
                nextCycle(module);
            }
            else
            {
                serialWIFI.insertDataFlag(module);
            }
#else
            nextCycle(module);
#endif
        }
    }
#if defined(LCD_OUTPUT)
    if (cycleTimer.getLCDActiveModule() == module)
    {
        outputLCD.batteryChargeLCD(module, chargeRecharge, batteryVoltage, batteryInitialVoltage[module], temperature.getCurrentTemp(module), cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module));
    }
#endif
#if defined(SERIAL_OUTPUT)
    outputSerial.batteryChargeSerial(module, chargeRecharge, batteryVoltage, batteryInitialVoltage[module], temperature.getCurrentTemp(module), cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module));
#endif
#if defined(ONLINE)
    serialWIFI.batteryChargeSerial(module, chargeRecharge, temperature.getInitialTemp(module), batteryInitialVoltage[module], temperature.getCurrentTemp(module), cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module), batteryVoltage, temperature.getHighestTemp(module));
#endif
}

void Cycle::milliOhmsCycle(byte module)
{
    int tempMilliOhms = 0;
    if (cycleCount[module] < 8)
    {
        batteryVoltage = 0;
        batteryShuntVoltage = 0;

        batteryVoltage = readInput.batteryVoltage(module);                                                                                          // Get Battery Voltage with no load
        writeOutput.dischargeMosfetOn(module);                                                                                                      // Turn on the Discharge Mosfet
        batteryShuntVoltage = readInput.batteryVoltage(module);                                                                                     // Get Battery Voltage with load
        writeOutput.dischargeMosfetOff(module);                                                                                                     // Turn off the Discharge Mosfet
        tempMilliOhms = (((batteryVoltage - batteryShuntVoltage) / (batteryShuntVoltage / config.shuntResistor[module]))) + config.offsetMilliOhms; // The Drain-Source On-State Resistance of the Discharge Mosfet
        if (tempMilliOhms > 1000)                                                                                                                   // Max 3 digits on LCD
            tempMilliOhms = 999;
#if defined(LCD_OUTPUT)
        if (cycleTimer.getLCDActiveModule() == module)
        {
            outputLCD.milliOhmsLCD(module, tempMilliOhms);
        }
#endif
#if defined(SERIAL_OUTPUT)
        outputSerial.milliOhmsSerial(module, tempMilliOhms);
#endif
#if defined(ONLINE)
        serialWIFI.milliOhmsSerial(module, tempMilliOhms, batteryVoltage);
#endif
        cycleCount[module]++;
        milliOhms[module] += tempMilliOhms;
    }
    else
    {
        milliOhms[module] = milliOhms[module] / 8;
        nextCycle(module);
    }
}

void Cycle::restCycle(byte module)
{
    batteryVoltage = readInput.batteryVoltage(module); // Get Battery Voltage
#if defined(LCD_OUTPUT)
    if (cycleTimer.getLCDActiveModule() == module)
    {
        outputLCD.batteryRestLCD(module, batteryVoltage, cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module));
    }
#endif
#if defined(SERIAL_OUTPUT)
    outputSerial.batteryRestSerial(module, batteryVoltage, cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module));
#endif
#if defined(ONLINE)
    serialWIFI.batteryRestSerial(module, milliOhms[module], temperature.getCurrentTemp(module), cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module), batteryVoltage);
#endif
    if (cycleTimer.getMinutes(module) == config.restTimeMinutes) // Rest time
    {
        nextCycle(module);
    }
}

void Cycle::dischargeCycle(byte module)
{
    batteryVoltage = 0;
    batteryShuntVoltage = 0;
    dischargeAmps = 0;
    batteryVoltage = readInput.batteryVoltage(module);
    if (batteryVoltage >= config.defaultBatteryCutOffVoltage && dischargeCompleted[module] == false)
    {
        writeOutput.dischargeMosfetOn(module); // Turn on the Discharge Mosfet
        batteryVoltage = readInput.batteryVoltage(module);
        batteryShuntVoltage = readInput.batteryVoltageDrop(module);
        dischargeAmps = (((batteryVoltage - batteryShuntVoltage) / (config.shuntResistor[module] / 1000.0)));
        if (dischargeMilliSecondsPrevious[module] == 0) // First run needs time to calculate time passed
        {
            dischargeMillisTime = 1000; // Discharge cycle trigger is average of 1000 milliseconds
        }
        else
        {
            dischargeMillisTime = millis() - dischargeMilliSecondsPrevious[module]; // Calculate time passed since last discharge cycle trigger
        }
        dischargeMilliamps[module] = dischargeMilliamps[module] + ((((dischargeAmps / 1000.0) * dischargeMillisTime) / 3600));
        dischargeMilliSecondsPrevious[module] = millis();
#if defined(LCD_OUTPUT)
        if (cycleTimer.getLCDActiveModule() == module)
        {
            outputLCD.batteryDischargeLCD(module, batteryVoltage, dischargeAmps, dischargeMilliamps[module], temperature.getCurrentTemp(module), cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module));
        }
#endif
#if defined(SERIAL_OUTPUT)
        outputSerial.batteryDischargeSerial(module, batteryVoltage, dischargeAmps, dischargeMilliamps[module], temperature.getCurrentTemp(module), cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module));
#endif
#if defined(ONLINE)
        serialWIFI.batteryDischargeSerial(module, cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module), temperature.getInitialTemp(module), batteryInitialVoltage[module], temperature.getCurrentTemp(module), batteryVoltage, dischargeAmps, dischargeMilliamps[module], temperature.getHighestTemp(module), milliOhms[module]);
#endif
    }
    else
    {
        dischargeCompleted[module] = true;
        writeOutput.dischargeMosfetOff(module); // Turn off the Discharge Mosfet
#if defined(ONLINE)
        serialWIFI.batteryDischargeSerial(module, cycleTimer.getHours(module), cycleTimer.getMinutes(module), cycleTimer.getSeconds(module), temperature.getInitialTemp(module), batteryInitialVoltage[module], temperature.getCurrentTemp(module), batteryVoltage, dischargeAmps, dischargeMilliamps[module], temperature.getHighestTemp(module), milliOhms[module]);
        if (serialWIFI.getInsertDataFlag(module))
        {
            nextCycle(module);
        }
        else
        {
            serialWIFI.insertDataFlag(module);
        }
#else
        nextCycle(module);
#endif
    }
}

void Cycle::completeCycle(byte module)
{
    batteryVoltage = readInput.batteryVoltage(module);
#if defined(LCD_OUTPUT)
    if (cycleTimer.getLCDActiveModule() == module)
    {
        outputLCD.completeLCD(module, faultCode[module], milliOhms[module], dischargeMilliamps[module], batteryVoltage);
    }
#endif
#if defined(SERIAL_OUTPUT)
    outputSerial.completeSerial(module, faultCode[module], milliOhms[module], dischargeMilliamps[module], batteryVoltage);
#endif
#if defined(ONLINE)
    serialWIFI.completeSerial(module, faultCode[module], batteryVoltage);
#endif
    if (batteryVoltage < config.batteryVoltageLeak)
    {
        nextCycle(module);
    }
}