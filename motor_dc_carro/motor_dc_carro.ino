#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int motorA6 = 6;
int motorA9 = 9;
int motorB10 = 10;
int motorB11 = 11;
int buzzer = 5;
int botao = 3;

int potenciometro = A0;
int velocidade;
int valorLido;

#define endereco 0x27 
#define colunas 16
#define linhas 2

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  delay(2000);

  Serial.begin(9600);
  pinMode(motorA6, OUTPUT);
  pinMode(motorA9, OUTPUT);
  pinMode(motorB10, OUTPUT);
  pinMode(motorB11, OUTPUT);
  pinMode(potenciometro, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
}

void loop() {
  valorLido = analogRead(potenciometro);
  velocidade = map(valorLido, 0, 1023, 0, 255); // mantém de 0 a 255

  Serial.println(velocidade);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Velocidade:");
  lcd.setCursor(0, 1);
  lcd.print(velocidade);
  lcd.print(" km/h");

  delay(500);

  // Buzina
  if (digitalRead(botao) == LOW) {
    tone(buzzer, 500);
  } else {
    noTone(buzzer);
  }

  // Carro andar com valor de 0 a 255
  analogWrite(motorA6, velocidade);
  analogWrite(motorB11, velocidade);
}
