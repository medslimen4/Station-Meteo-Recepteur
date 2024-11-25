#pragma once
#include "../lib/Domain/Entity/TemperatureHumidityData.hpp"
#include "../lib/Domain/Entity/WindData.hpp"
#include <string>   
#include <ctime>
#include "WindSpeed.hpp"
struct  WeatherStationData
{
    TemperatureHumidityData temperatureHumidityData; // Données du capteur de température et d'humidité
    WindSpeed windSpeed;                       // Données du capteur de précipitations
    WindData windData;                               // Données du capteur de vent
};