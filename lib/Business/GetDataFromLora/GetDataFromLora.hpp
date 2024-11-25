#include "../lib/Domain/Services/IRecieveDataFromLora.hpp"
#include "../lib/Domain/Entity/WeatherStationData.hpp"

class GetDataFromLora
{
private:
    IRecieveDataFromLora* receiveDataService; // Dependency Injection

public:
    GetDataFromLora(IRecieveDataFromLora* service);
    void InitLora();
    WeatherStationData getData();
};
