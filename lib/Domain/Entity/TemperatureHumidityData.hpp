#pragma once
#include <string>   
#include <ctime>
struct TemperatureHumidityData 
{
    std::string sensorModel;   // Modèle du capteur, ex: "DHT22 or BME620 next time"
    float temperatureCelsius;  // Température en degrés Celsius
    float humidityPercentage;  // Humidité en pourcentage

};
