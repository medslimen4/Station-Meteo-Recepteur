#include "../lib/Domain/Services/ISendDataToAPI.hpp"
#include "../lib/Domain/Entity/WeatherStationData.hpp"

class SendDataToAPI
{
private:
    ISendDataToAPI* sendDataService; // Dependency Injection

public:
    SendDataToAPI(ISendDataToAPI* service);
    void InitApi();
    void sendData(const WeatherStationData& data);
};
