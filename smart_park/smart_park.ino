#include <Ultrasonic.h>
Ultrasonic sensor_distancia(12, 13);
int green = 7;
int red = 8;
int distancia;

  void setup() {
    pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);
  }

  void loop() {

    distancia = sensor_distancia.read();
    if(distancia>4){ //vaga livre
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
   }else{ //vaga ocupada
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
  }
  delay(300);
}
