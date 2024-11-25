#pragma once
#include "../lib/Domain/Entity/WeatherStationData.hpp"
class IRecieveDataFromLora {
public:
    virtual void InitLora() = 0;
    virtual WeatherStationData getData() = 0;
};