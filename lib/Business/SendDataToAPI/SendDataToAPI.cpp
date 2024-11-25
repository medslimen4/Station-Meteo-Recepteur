#include "SendDataToAPI.hpp"

// Constructor with dependency injection
SendDataToAPI::SendDataToAPI(ISendDataToAPI* service)
    : sendDataService(service)
{
}

// Call InitApi on the injected service
void SendDataToAPI::InitApi()
{
    sendDataService->InitApi();
}

// Send data to the injected service
void SendDataToAPI::sendData(const WeatherStationData& data)
{
    sendDataService->sendData(data);
}
