#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xEF, 0xFE, 0xED
};

IPAddress ip(192,168,1,45);

EthernetServer server(80);

OneWire ourWire(2);    //Se establece el pin 2 como bus wire

DallasTemperature sensors(&ourWire);   //Se declara una variable u objeto para nuestro sensor

void setup() {
  delay(1000);
  //pinMode(LED_BUILTIN, OUTPUT);     //Inicialización del led integrado como pin de salida (OUTPUT)
  Serial.begin(9600);
  sensors.begin();    //Se inicia el sensor
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {

  EthernetClient cliente = server.available();
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp = sensors.getTempCByIndex(0);  //Se obtiene la temperatura en grados Centigrados

  //Serial.print("Temperatura= ");
  //Serial.print(temp);
  //Serial.print(" C° \n");
  if (cliente) {
    boolean currentLineIsBlank = true;

    while(cliente.connected()){
      if (cliente.available()){
        char c = cliente.read();

        if (c == '\n' && currentLineIsBlank) {
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println("Connection: close");
          cliente.println("Refresh: 10");
          cliente.println();
          cliente.println("<!DOCTYPE HTML>");
          cliente.println("<html>");
          cliente.println("<HEAD>");
          cliente.println("<TITLE>Monitoreo de Calidad del agua</TITLE>");
          cliente.println("</HEAD>");
          cliente.println("<BODY>");
          cliente.println("<br/>");
          cliente.println("<H1>Monitoreo de la calidad del agua con Arduino y sensor ds1820</H1>");
          cliente.println("<br/>");
          cliente.println("<p>Temperatura ");
          cliente.print(temp);
          cliente.print(" C°</p>");
          cliente.println("</BODY>");
          cliente.println("</html>");
          break;
        }
        if (c== '\n'){
          currentLineIsBlank = true;
        }
        else  if (c != '\r'){
          currentLineIsBlank = false;
        }
      }
    }
    delay(15);
    cliente.stop();
  }
  
  //sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  //float temp = sensors.getTempCByIndex(0);  //Se obtiene la temperatura en grados Centigrados

  //Serial.print("Temperatura= ");
  //Serial.print(temp);
  //Serial.print(" C° \n");
  //delay(1000);

}
