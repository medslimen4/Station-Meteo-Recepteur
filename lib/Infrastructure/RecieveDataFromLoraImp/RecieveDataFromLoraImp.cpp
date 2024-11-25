#include "RecieveDataFromLoraImp.hpp"
#include <iostream> // Pour l'exemple

#define BAND 868E6
#define RECEIVER_ADDRESS 0xBB
// Méthode d'initialisation du module Lora
void RecieveDataFromLoraImp::InitLora()
{
    // Initialize the Heltec module
    Heltec.begin(true, true, true, true, BAND);

    // Initialize LoRa communication
    if (!LoRa.begin(BAND, true))
    {
        Serial.println("Failed to initialize LoRa!");
        while (1);
            
    }
    // Display waiting message on the OLED screen
    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(0, 0, "LoRa Receiver");
    Heltec.display->drawString(0, 20, "Waiting for Weather Data...");
    Heltec.display->display();
}

// Méthode de récupération des données depuis le module Lora
WeatherStationData RecieveDataFromLoraImp::getData() {
    // Initialize the WeatherStationData object to hold the received data
    WeatherStationData data;

    // Check if there's a new LoRa packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String receivedMessage = "";

        // Read the LoRa packet into the receivedMessage string
        while (LoRa.available()) {
            receivedMessage += (char)LoRa.read();
        }

        // Log the received message
        Serial.println("Received Message: " + receivedMessage);

        // Parse the received data into variables
        int firstComma = receivedMessage.indexOf(',');
        int secondComma = receivedMessage.indexOf(',', firstComma + 1);
        int thirdComma = receivedMessage.indexOf(',', secondComma + 1);
        int fourthComma = receivedMessage.indexOf(',', thirdComma + 1);
        int fifthComma = receivedMessage.indexOf(',', fourthComma + 1);

        String receiverAddress = receivedMessage.substring(0, firstComma);
        String senderAddress = receivedMessage.substring(firstComma + 1, secondComma);
        float temperature = receivedMessage.substring(secondComma + 1, thirdComma).toFloat();
        float humidity = receivedMessage.substring(thirdComma + 1, fourthComma).toFloat();
        float windSpeed = receivedMessage.substring(fourthComma + 1, fifthComma).toFloat();
        String windDirection = receivedMessage.substring(fifthComma + 1);  // Now treating wind direction as a string

        // Check if the message is meant for this receiver
        if (receiverAddress.equals(String(RECEIVER_ADDRESS, HEX))) {
            // Set the received data into the WeatherStationData object
            data.temperatureHumidityData.temperatureCelsius = temperature;
            data.temperatureHumidityData.humidityPercentage = humidity;
            data.windSpeed.vitesseVentkmh = windSpeed;
            data.windData.windDirectionCompass = windDirection.c_str();  // Set the string wind direction

            // Optionally, display data on the OLED screen
            Heltec.display->clear();
            Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
            Heltec.display->setFont(ArialMT_Plain_10);
            Heltec.display->drawString(0, 0, "Sender: 0x" + senderAddress);
            Heltec.display->drawString(0, 12, "Temp: " + String(temperature) + " C");
            Heltec.display->drawString(0, 24, "Humidity: " + String(humidity) + " %");
            Heltec.display->drawString(0, 36, "Wind: " + String(windSpeed) + " m/s, " + windDirection);
            Heltec.display->display();
        } else {
            Serial.println("Message not intended for this receiver.");
        }
    }

    // Return the populated WeatherStationData object
    return data;
}