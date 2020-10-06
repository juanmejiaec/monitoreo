#include <ESP8266WiFi.h>
const char* ssid="MYE 2.4GHz_plus";
const char* password="43496775";
int ledAzul = 5;
void setup() {
 Serial.begin(9600);
 pinMode(ledAzul, OUTPUT);
  Serial.println();
  Serial.print("Conectandose al WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Conectando");
 while( WiFi.status() != WL_CONNECTED ){

    delay(500);
    Serial.print(".");
  }
      Serial.println("Wifi Conectado exitosamente");
    Serial.print("Dirección IP del NodeMCU : ");
    Serial.println(WiFi.localIP() ); 
}

void loop() {

}
