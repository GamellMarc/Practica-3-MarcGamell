#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Nautilus";
const char* password = "20000Leguas";

AsyncWebServer server(80);

// HTML con JavaScript corregido para usar parámetros de descarga
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 File Manager</title>
  <style>
    body { font-family: Arial; padding: 20px;}
    ul { list-style-type: none; padding: 0;}
    li { margin: 10px 0; background: #f4f4f4; padding: 10px; border-radius: 5px;}
    #fileInput { display: none; }
    button { padding: 10px 15px; background: #007BFF; color: white; border: none; border-radius: 5px; cursor: pointer;}
    button:hover { background: #0056b3; }
  </style>
</head>
<body>
  <h2>Gestor de Archivos ESP32</h2>
  <button onclick="document.getElementById('fileInput').click();">Subir Archivo</button>
  <input type="file" id="fileInput" onchange="uploadFile()" multiple>
  <ul id="fileList"></ul>

  <script>
  document.addEventListener('DOMContentLoaded', function (e) {
    fetch('/list').then(response => response.json())
      .then(data => {
        var fileList = document.getElementById('fileList');
        data.forEach(file => {
          var li = document.createElement('li');
          var a = document.createElement('a');
          a.href = `/download?file=${file}`; 
          a.text = "Descargar: " + file;
          li.appendChild(a);
          fileList.appendChild(li);
        });
      });
  });

  function uploadFile() {
    var files = document.getElementById('fileInput').files;
    var formData = new FormData();
    for (var i = 0; i < files.length; i++) {
      formData.append('file', files[i]);
    }

    fetch('/upload', {method: 'POST', body: formData})
      .then(response => {
        if (response.ok) {
          console.log('Upload successful');
          location.reload();
        } else {
          console.error('Upload failed');
          alert('Error al subir el archivo');
        }
      });
  }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  
  if(!SPIFFS.begin(true)){
      Serial.println("Error al montar SPIFFS");
      return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi..");
  }
  Serial.println("Conectado a la red WiFi");
  Serial.print("IP del Gestor de Archivos: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/list", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "[";
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while(file){
        if(json != "[") json += ',';
        String fileName = String(file.name());
        if(fileName.startsWith("/")) {
          fileName = fileName.substring(1);
        }
        json += "\"" + fileName + "\"";
        file = root.openNextFile();
    }
    json += "]";
    request->send(200, "application/json", json);
    file.close();
  });

  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request){},
    [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
      if(!index){
        Serial.printf("Iniciando subida: %s\n", filename.c_str());
        request->_tempFile = SPIFFS.open("/" + filename, "w");
      }
      if(len){
        request->_tempFile.write(data, len);
      }
      if(final){
        Serial.printf("Subida finalizada: %s (%u bytes)\n", filename.c_str(), index+len);
        request->_tempFile.close();
      }
  });

  server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasParam("file")){
      String filename = "/" + request->getParam("file")->value();
      Serial.print("Solicitando: ");
      Serial.println(filename);
      
      if(SPIFFS.exists(filename)){
        request->send(SPIFFS, filename, "application/octet-stream", true);
      } else {
        request->send(404, "text/plain", "Archivo no encontrado");
      }
    } else {
      request->send(400, "text/plain", "Peticion incorrecta");
    }
  });

  server.begin();
}

void loop() {
  // El loop se queda vacío al usar un servidor asíncrono
}