const char* WIFI_SSID = "mohamed";
const char* WIFI_PASSWORD = "slimen55";
const char* API_URL = "https://agile-education.up.railway.app/WeatherApi/recieveData";
const char* DEVICE_ID = "heltec01";
const unsigned long CHECK_LORA_INTERVAL = 1000;    // Vérifier LoRa chaque 1 seconde
const unsigned long SEND_API_INTERVAL = 10000;     // Envoyer à l'API chaque 10 secondes

// Variables pour le timing
unsigned long lastLoraCheck = 0;
unsigned long lastApiSend = 0;