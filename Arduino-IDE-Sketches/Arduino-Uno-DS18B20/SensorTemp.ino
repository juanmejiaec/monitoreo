#include <OneWire.h>
#include <DallasTemperature.h>

OneWire ourWire(2);    //Se establece el pin 2 como bus wire

DallasTemperature sensors(&ourWire);   //Se declara una variable u objeto para nuestro sensor

void setup() {
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);     //Inicialización del led integrado como pin de salida (OUTPUT)
  Serial.begin(9600);
  sensors.begin();    //Se inicia el sensor
}

void loop() {

  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp = sensors.getTempCByIndex(0);  //Se obtiene la temperatura en grados Centigrados

  Serial.print("Temperatura= ");
  Serial.print(temp);
  Serial.print(" C° \n");
  delay(1000);

}
