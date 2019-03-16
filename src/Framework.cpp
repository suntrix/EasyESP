#include "Framework.h"

#include <ESP8266httpUpdate.h>

#include <Wire.h>

namespace EasyESP {
    Framework::Framework(Config config) {
        _config = config;
    }

    void Framework::setup(callback_t callback) {
        Serial.begin(EASYESP_SERIAL_BAUD);
        Serial.setTimeout(EASYESP_SERIAL_TIMEOUT);

        while(!Serial) {}

        _statusLED.setupLEDStart();

        Serial.println("\nBoot device...");
        printDeviceInfo();
        
        if (connectToWifi()) {
            _statusLED.setupLEDStop();

            checkForUpdates();

            _statusLED.setupLEDStart();
        }

        _watchdog.startGuarding(EASYESP_WATCHDOG_SETUP_TIMEOUT);

        callback(&_watchdog, &_statusLED);

        _watchdog.finishGuarding();
        _statusLED.setupLEDStop();

        Serial.println("\nBoot device... DONE!");
    }

    void Framework::loop(callback_t callback) {
        _watchdog.startGuarding(EASYESP_WATCHDOG_LOOP_TIMEOUT);

        callback(&_watchdog, &_statusLED);

        _watchdog.finishGuarding();
    }

    void Framework::printDeviceInfo() {
        Serial.println("\nDEVICE INFO");
        Serial.println("-------------------------------------");
        
        const uint32_t vcc = ESP.getVcc();
        Serial.print("VCC: "); 
        Serial.println(vcc);

        Serial.print("hostname: "); 
        Serial.println(WiFi.hostname());

        Serial.print("macAddress: "); 
        Serial.println(WiFi.macAddress());

        Serial.println("-------------------------------------");
    }

    bool Framework::connectToWifi() {
        Serial.println("\nCONNECT TO WIFI");
        Serial.println("-------------------------------------");

        if (_config.ssid != NULL && _config.password != NULL) {
            unsigned long timeout = millis() + EASYESP_WIFI_TIMEOUT;

            WiFi.begin(_config.ssid, _config.password);

            Serial.print(String(" "));

            while (!WiFi.isConnected()) {
                if (WiFi.status() == WL_CONNECT_FAILED || millis() > timeout) {
                    Serial.println(" failed!");
                    break;
                }

                delay(250);
                Serial.print(".");
            }

            if (WiFi.isConnected()) {
                Serial.println(" connected!");
                Serial.println("<---- WIFI INFO ---->");
                WiFi.printDiag(Serial);
                Serial.println("<------------------->");
            }
        } else {
            Serial.println("EASYESP_WIFI_* is NOT defined!");
        }

        Serial.println("-------------------------------------");

        return WiFi.isConnected();
    }

    void Framework::checkForUpdates(bool useHttps) {
        Serial.println("\nOTA FIRMWARE UPDATE");
        Serial.println("-------------------------------------");

        if (_config.versionName) {

            t_httpUpdate_return result;

            if (useHttps && _config.otaHttpsUrl != NULL && _config.otaHttpsFingerPrint != NULL) {
                Serial.print("Trying over HTTPS...");
                result = ESPhttpUpdate.update(_config.otaHttpsUrl, _config.versionName, _config.otaHttpsFingerPrint);
            } else {
                Serial.print("Trying over HTTP...");
                result = ESPhttpUpdate.update(_config.otaHttpUrl, _config.versionName);
            }

            bool retryOverHttp = false;
            
            switch(result) {
                case HTTP_UPDATE_FAILED:
                    Serial.println(" failed!");
                    
                    Serial.print("  Update error code: "); 
                    Serial.println(ESPhttpUpdate.getLastError());
                    
                    Serial.print("  Update error: "); 
                    Serial.println(ESPhttpUpdate.getLastErrorString());

                    retryOverHttp = useHttps;

                    break;
                case HTTP_UPDATE_NO_UPDATES:
                    Serial.println(" no update available");
                    break;
                case HTTP_UPDATE_OK:
                    Serial.println(" update finished");
                    break;
            }

            if (retryOverHttp) {
                if (_config.otaHttpUrl) {
                    Serial.println("Retrying over HTTP...");
                    checkForUpdates(false);
                }
            }
        } else {
            Serial.println("EASYESP_OTA_* is NOT defined!");
        }

        Serial.println("-------------------------------------");
    }

    void Framework::deepSleep(uint64_t sleepTime) {
        if (_watchdog.isGuarding()) {
            _watchdog.finishGuarding();
        }

        char output[50];
        sprintf(output, "Going into deep sleep for %.4f seconds", sleepTime / 1e6);

        Serial.println();
        Serial.print(output);

        ESP.deepSleep(sleepTime);
        while(true){};
    }

    void Framework::scanPorts() {
        uint8_t portArray[] = {16, 5, 4, 0, 2, 14, 12, 13};
        String portMap[] = {"GPIO16", "GPIO5", "GPIO4", "GPIO0", "GPIO2", "GPIO14", "GPIO12", "GPIO13"};
        
        for (uint8_t i = 0; i < sizeof(portArray); i++) {
            for (uint8_t j = 0; j < sizeof(portArray); j++) {
                if (i != j){
                    Serial.print("Scanning (SDA : SCL) - " + portMap[i] + " : " + portMap[j] + " - ");

                    Wire.begin(portArray[i], portArray[j]);

                    _checkIfExistI2C();
                }
            }
        }
    }

    void Framework::signalError(uint8_t error) {
        _statusLED.signalError(error);
    }

    void Framework::_checkIfExistI2C() {
        byte error, address;
        int nDevices = 0;

        for (address = 1; address < 127; address++ )  {
            // The i2c_scanner uses the return value of
            // the Write.endTransmisstion to see if
            // a device did acknowledge to the address.
            Wire.beginTransmission(address);
            error = Wire.endTransmission();

            if (error == 0){
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
            } else if (error == 4) {
            Serial.print("Unknow error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
            }
        }

        if (nDevices == 0) {
            Serial.println("No I2C devices found");
        } else {
            Serial.println("**********************************\n");
        }
    }
}