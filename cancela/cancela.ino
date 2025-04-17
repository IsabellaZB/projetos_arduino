#include<Servo.h>
Servo motor;
int ledRed = 3;
int ledGreen = 4;
int botao = 5;
int buzzer = 6;

void setup(){
pinMode(ledRed, OUTPUT);
pinMode(ledGreen, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(botao, INPUT);
motor.attach(9);
motor.write(0);
}
void loop(){
if(digitalRead(botao)== HIGH){
    motor.write(90);
    digitalWrite(ledGreen, HIGH);
    tone(buzzer,494);
}
    digitalWrite(ledRed, HIGH);
    noTone(buzzer);
    motor.write(0);
}
