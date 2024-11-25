#include <Arduino.h>
#include "../lib/Business/GetDataFromLora/GetDataFromLora.hpp"
#include "../lib/Infrastructure/RecieveDataFromLoraImp/RecieveDataFromLoraImp.hpp"
#include "../lib/Business/SendDataToAPI/SendDataToAPI.hpp"
#include "../lib/Infrastructure/SendDataToAPIImp/SendDataToAPIImp.hpp"
#include "../include/Bsp.hpp"
// put function declarations here:
  

// Variable pour stocker les dernières données valides
WeatherStationData lastValidData;
bool hasNewValidData = false;

// Instances statiques globales
static RecieveDataFromLoraImp loraService;
static GetDataFromLora dataManager(&loraService);

static SendDataToAPIImp apiService(WIFI_SSID, WIFI_PASSWORD, API_URL, DEVICE_ID);
static SendDataToAPI apiManager(&apiService);

// Fonction pour vérifier si les données sont valides
bool isValidData(const WeatherStationData& data) {
    if (data.temperatureHumidityData.temperatureCelsius < 5 || 
        data.temperatureHumidityData.temperatureCelsius > 50) {
        return false;
    }
    
    // Vérifier si l'humidité est dans une plage valide (0-100%)
   /* if (data.temperatureHumidityData.humidityPercentage < 0 || 
        data.temperatureHumidityData.humidityPercentage > 100) {
        return false;
    }
    
    // Vérifier si la vitesse du vent est positive
    if (data.windSpeed.vitesseVentkmh < 0) {
        return false;
    }
    
    // Vérifier si la direction du vent n'est pas vide
    if (data.windData.windDirectionCompass.empty()) {
        return false;
    } */
    
    return true;
}

void displayData(const WeatherStationData& data) {
    Serial.println("\n--- Weather Station Data ---");
    Serial.print("Temperature: ");
    Serial.print(data.temperatureHumidityData.temperatureCelsius);
    Serial.println(" °C");
    
    Serial.print("Humidity: ");
    Serial.print(data.temperatureHumidityData.humidityPercentage);
    Serial.println(" %");
    
   // Serial.print("Wind Speed: ");
   // Serial.print(data.windSpeed.vitesseVentkmh);
   // Serial.println(" km/h");
    
   Serial.print("Wind Direction: ");
    Serial.println(data.windData.windDirectionCompass.c_str());
}

void setup() {
    // Initialisation de la communication série
    Serial.begin(115200);
    Serial.println("Starting Weather Station Receiver...");
    
    // Initialisation du module LoRa
    dataManager.InitLora();
    
    // Initialisation de la connexion API
    apiManager.InitApi();
    
    Serial.println("Setup completed - Ready to receive and send data");
}

void loop() {
    unsigned long currentMillis = millis();

    // Vérification des données LoRa chaque seconde
    if (currentMillis - lastLoraCheck >= CHECK_LORA_INTERVAL) {
        WeatherStationData currentData = dataManager.getData();
        
        if (isValidData(currentData)) {
            lastValidData = currentData;
            hasNewValidData = true;
            Serial.println("New valid data received from LoRa");
            displayData(lastValidData);
        }
        
        lastLoraCheck = currentMillis;
    }

    // Envoi à l'API toutes les 10 secondes si des nouvelles données sont disponibles
    if (currentMillis - lastApiSend >= SEND_API_INTERVAL) {
        if (hasNewValidData) {
            Serial.println("Sending data to API...");
            apiManager.sendData(lastValidData);
            hasNewValidData = false;  // Réinitialiser le flag après l'envoi
            Serial.println("Data sent successfully");
        } else {
            Serial.println("No new data to send to API");
        }
        
        lastApiSend = currentMillis;
    }
}