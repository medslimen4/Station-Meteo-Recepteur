#pragma once
#include "../lib/Domain/Services/ISendDataToAPI.hpp"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class SendDataToAPIImp : public ISendDataToAPI
{
private:
    const char *ssid;
    const char *password;
    const char *apiUrl;
    const char *deviceId;

public:
    SendDataToAPIImp(const char *wifi_ssid, const char *wifi_password,
                     const char *api_url, const char *device_id);
    void InitApi() override;
    void sendData(const WeatherStationData &data) override;
};