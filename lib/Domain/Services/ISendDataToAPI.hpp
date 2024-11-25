#pragma once
#include "../lib/Domain/Entity/WeatherStationData.hpp"
class ISendDataToAPI {
public:
    virtual void InitApi() = 0;
    virtual void sendData(const WeatherStationData& data) = 0;
};