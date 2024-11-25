    #include <string>   
    #include <ctime>
    #pragma once

    struct WindSpeed {
        std::string sensorModel;    // Modèle du capteur, ex: "Anémomètre"
        float vitesseVentkmh;  // Vitesse du vent en m/s
    };