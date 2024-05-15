#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "Desktop_F0011871";
const char* password = "9148101930009132";

#define Sensor 36
bool flag = 1;

// +international_country_code + phone number
// Brasil +55, example: +5511988888888
String phoneNumber = "+5515998547136"; //Número de telefone
String apiKey = "3719053"; //Api gerado pelo bot

void sendMessage(String message) { //Estrutura para enviar informações para o Bot

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da mensagem");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(Sensor, INPUT); //Entrada do sensor

 
  WiFi.begin(ssid, password); //Conexão do wi-fi
  Serial.println("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado ao WiFi neste IP ");
  Serial.println(WiFi.localIP());
}

void loop() {

  int Porta = digitalRead(Sensor);


  if (Porta == 1) {
    
    if (flag) {
      sendMessage("Alarme Ativado");
      flag = 0;
    }
  } else {
    
    flag = 1;
  }
}