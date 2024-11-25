#include "../lib/Infrastructure/SendDataToAPIImp/SendDataToAPIImp.hpp"

SendDataToAPIImp::SendDataToAPIImp(const char* wifi_ssid, const char* wifi_password,
                                 const char* api_url, const char* device_id)
    : ssid(wifi_ssid), password(wifi_password), apiUrl(api_url), deviceId(device_id)
{
}

void SendDataToAPIImp::InitApi() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to WiFi network");
}

void SendDataToAPIImp::sendData(const WeatherStationData& data) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected. Attempting to reconnect...");
        InitApi();
    }

    HTTPClient http;
    
    // Add "http://" if not present
    String fullUrl = String(apiUrl);
    if (!fullUrl.startsWith("http://") && !fullUrl.startsWith("https://")) {
        fullUrl = "http://" + fullUrl;
    }
    
    http.begin(fullUrl.c_str());
    http.addHeader("Content-Type", "application/json");
    
    StaticJsonDocument<1024> doc;
    
    // Set deviceId
    doc["deviceId"] = deviceId;
    
    // Temperature and humidity data
    JsonObject temperatureHumidityData = doc.createNestedObject("temperatureHumidityData");
    temperatureHumidityData["sensorModel"] = "DHT22";
    temperatureHumidityData["temperatureCelsius"] = data.temperatureHumidityData.temperatureCelsius;
    temperatureHumidityData["humidityPercentage"] = data.temperatureHumidityData.humidityPercentage;
    
    // Windspeed data
    JsonObject windspeed = doc.createNestedObject("windspeed");
    windspeed["sensorModel"] = "Anémomètre";
    windspeed["vitesseVentkmh"] = data.windSpeed.vitesseVentkmh;
    
    // Wind direction data
    JsonObject windData = doc.createNestedObject("windData");
    windData["sensorModel"] = "Gyroscope";
    windData["windDirectionCompass"] = data.windData.windDirectionCompass.empty() ? "" : data.windData.windDirectionCompass;
    
    String jsonString;
    serializeJson(doc, jsonString);
    
    Serial.println("Sending JSON:");
    Serial.println(jsonString);
    
    int httpResponseCode = http.POST(jsonString);
    
    if (httpResponseCode > 0) {
        Serial.printf("HTTP Response code: %d\n", httpResponseCode);
        String response = http.getString();
        Serial.println("Response: " + response);
    } else {
        Serial.printf("Error sending HTTP POST: %d\n", httpResponseCode);
    }
    
    http.end();
}