# Pràctica 3 - Processadors Digitals: Connectivitat Wi-Fi i Servidors

Aquest repositori conté els projectes i la memòria corresponents a la **Pràctica 3** de l'assignatura de Processadors Digitals. L'objectiu principal d'aquesta pràctica és explorar les capacitats de connectivitat sense fils del microcontrolador **ESP32-S3**, implementant servidors web, actualitzacions remotes i sistemes de gestió de fitxers.

## 📂 Estructura del Repositori

El repositori està dividit en les següents carpetes i fitxers:

* **`Practica3A/`**: Conté el projecte base d'introducció a la connectivitat.
    * Connexió a una xarxa Wi-Fi existent (Mode Station / STA).
    * Creació d'un servidor HTTP bàsic (basat en *polling*) per enviar i mostrar una pàgina web HTML.

* **`Practica3Complementari1/`**: Conté el projecte d'actualitzacions sense fils (OTA).
    * Configuració del protocol *Over-The-Air* (OTA).
    * Ús de funcions no bloquejants (`millis()`) per mantenir l'escolta del servei en segon pla.
    * Enviament de nou firmware a través de la xarxa Wi-Fi local des de PlatformIO.

* **`Practica3Complementari2/`**: Conté el projecte de Servidor Web Asíncron i Gestor d'Arxius.
    * Ús de memòria Flash interna com a disc d'emmagatzematge amb el sistema de fitxers SPIFFS.
    * Implementació de llibreries asíncrones (`AsyncTCP` i `ESPAsyncWebServer`) per alliberar el 100% del bucle principal (`loop`).
    * Disseny d'una interfície web interactiva per llistar, pujar i descarregar fitxers remotament.

* **`InformePràctica3PD.pdf`**: Memòria completa de la pràctica. Inclou l'explicació detallada de l'arquitectura de xarxa, diagrames de flux, diagrames de temps i una anàlisi exhaustiva de l'evolució de l'ocupació de la CPU en els diferents models de servidor.

## 🛠️ Tecnologies i Maquinari Utilitzat

* **Placa:** YD-ESP32-S3 (Compatible amb ESP32-S3-DevKitC-1) amb mòdul Wi-Fi/Bluetooth integrat.
* **Entorn de desenvolupament:** Visual Studio Code + extensió PlatformIO
* **Llenguatge:** C++ (Framework d'Arduino)
* **Llibreries externes:** `AsyncTCP`, `ESPAsyncWebServer`, `ArduinoOTA`.

## 👤 Autor
**Marc Gamell**
