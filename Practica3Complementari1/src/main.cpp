#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h> // Usamos la librería oficial del ESP32


//CÓDIGO CON EL QUE SE HA INICIALIZADO EL OTA

const char* ssid = "Nautilus";
const char* password = "20000Leguas";

void setup() {
  Serial.begin(115200);
  while (!Serial);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.begin(); // Arrancamos el servicio OTA oficial
}

void loop() {
  ArduinoOTA.handle(); // El ESP32 se queda escuchando
}

//CÓDIGO CON EL QUE SE HA EJECUTADO EL PROGRAMA DESDE EL PORTÁTIL

// #include <Arduino.h>
// #include <WiFi.h>
// #include <ESPmDNS.h>      // Requisito interno para OTA en ESP32
// #include <WiFiUdp.h>      // Requisito interno para OTA en ESP32
// #include <ArduinoOTA.h>
// 
// const char* ssid = "Nautilus";
// const char* password = "20000Leguas";
// 
// unsigned long tiempoAnterior = 0;
// 
// void setup() {
//   Serial.begin(115200);
//   while (!Serial);
// 
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
// 
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// 
//   ArduinoOTA.begin(); 
// }
// 
// void loop() {
//   ArduinoOTA.handle(); // Esto debe ejecutarse sin pausas largas
// 
//   // Usamos millis() en lugar de delay() para no bloquear la escucha del OTA
//   if (millis() - tiempoAnterior > 2000) {
//     Serial.println("¡Actualizacion por Wi-Fi completada con exito! Version 2.0");
//     tiempoAnterior = millis();
//   }
// }