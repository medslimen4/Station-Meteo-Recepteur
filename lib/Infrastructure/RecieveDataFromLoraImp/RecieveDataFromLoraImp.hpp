#include "../lib/Domain/Services/IRecieveDataFromLora.hpp"
#include <heltec.h>

class RecieveDataFromLoraImp : public IRecieveDataFromLora
{
public:
    void InitLora() override;
    WeatherStationData getData() override;
};