#include "GetDataFromLora.hpp"

// Constructor with dependency injection
GetDataFromLora::GetDataFromLora(IRecieveDataFromLora* service)
    : receiveDataService(service)
{
}

// Call InitLora on the injected service
void GetDataFromLora::InitLora()
{
    receiveDataService->InitLora();
}

// Get data from the injected service
WeatherStationData GetDataFromLora::getData()
{
    return receiveDataService->getData();
}
