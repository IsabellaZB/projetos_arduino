#include <Ultrasonic.h> //biblioteca do sensor de distância
#include <Servo.h> 

Ultrasonic sensor_distancia(12, 13); 
Servo motor;
int sensor_luz = A0;
int buzzer = 6;
int botao = 5;
int led = 7;

void setup(){
    pinMode(led, OUTPUT);

   // pinMode(sensor_distancia, INPUT); NAO É PRA BOTAR O PINMODE DO ULTRASONICO, JA TA NA BIBLIOTECA.
    pinMode(buzzer, OUTPUT);
    pinMode(sensor_luz, INPUT);//luminosidade
    pinMode(botao, INPUT);
    motor.attach(9);
}

void loop(){

    if(sensor_distancia.read() < 300 && analogRead(sensor_luz)<=600){
        acionarAlarme();
    }
    
    if(digitalRead(botao,HIGH)){
        pararAlarme();
    }

    void pararAlarme(){
            digitalWrite(led, LOW);
            noTone(buzzer);
     }
    }

    void trancarPorta(){
        motor.write(0);
    }

    void piscarLampada(){
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
    }

    void sirene(){
        tone(buzzer,494);
        delay(1000);
        noTone(buzzer);
        delay(500);
    }

    void acionarAlarme(){
            sirene();
            trancarPorta();
            piscarLampada();
        }
    
}
