#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// 1. Sustituye estos valores por los de tu red Wi-Fi local
const char* ssid = "Nautilus"; 
const char* password = "20000Leguas";

WebServer server(80); // Objeto del servidor web en el puerto 80 (por defecto HTTP)

// Contenido HTML y CSS que se mostrará en el servidor web
// Nota: Usar R"=====( ... )=====" te permite escribir HTML cómodamente en múltiples líneas
String HTML = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Servidor ESP32</title>
</head>
<body>
  <h1>Mi Primera Pagina con ESP32 Station Mode &#128522;</h1>
  <p>Esta es una página web modificada para la Práctica 3.</p>
</body>
</html>
)=====";

void handle_root() {
  server.send(200, "text/html", HTML);
}

void setup() {
  Serial.begin(115200); // Inicia la comunicación serie a 115200 baudios
  Serial.println("Intentando conectar a ");
  Serial.println(ssid);
  
  // Conectar al módem Wi-Fi
  WiFi.begin(ssid, password);
  
  // Comprobar si está conectado a la red
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado exitosamente");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP()); // Muestra la IP asignada al ESP32
  
  server.on("/", handle_root);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  delay(100);
}

void loop() {
  server.handleClient(); // Escucha a los clientes entrantes
}