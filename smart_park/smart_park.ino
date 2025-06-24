/************ BIBLIOTECAS ************/
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/************ OBJETOS ************/
Ultrasonic sensor_distancia(12, 13);
LiquidCrystal_I2C lcd(0x27, 16, 2);

/************ VARIÁVEIS DE COMPONENTES ************/
// LEDs normais
int green = 7;
int red = 8;

// LED RGB
int rgbRed = 6;
int rgbGreen = 5;
int rgbBlue = 4;

// Botão
int botao = 2;

/************ VARIÁVEIS AUXILIARES ************/
int click = 1;  //armazena a quantidade de vezes que o botão foi clicado
int distancia;  //armazena a distância em cm lida pelo sensor ultrassônico
int vagas;

// Função para acender o led RGB com uma cor específica
void configurarRGB(int r, int g, int b) {
  analogWrite(rgbRed, r);
  analogWrite(rgbGreen, g);
  analogWrite(rgbBlue, b);
}

/*Função para verificar quantas vezes o botão foi clicado
1 clique = vaga PCD
2 cliques = vaga comum
*/
void verificarCliques(){
  
  // Se o botão estiver pressionado (LOW), entra no modo PCD
  if (digitalRead(botao) == LOW) {
    if (click == 1) {
      click = 2;
    } else {
      click = 1;
    }
  }

  if (click == 1) {
    verificarVagaPCD();
  }
  if (click == 2) {
    verificarVaga();
  }
}

//Função para acionar os leds referente à vaga para PCDs
void verificarVagaPCD() {
  // Desliga os LEDs da vaga comum
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);

  /*Verifica se há algum veículo na vaga
  Acende azul para livre ou vermelho para ocupado
*/
  if (distancia > 4) {
    configurarRGB(0, 0, 255);  // acender o led com a cor azul
  } else {
    configurarRGB(255, 0, 0);  // acender o led com a cor vermelha
  }
}

//Função para acionar os leds referente à vaga comum
void verificarVaga() {
  //Desliga o led rgb da vaga PCD
  configurarRGB(0, 0, 0);

  if (distancia > 4) {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } else {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  }
}


int sortearQuantidadeVagas() {
  vagas = random(0, 9);
  return vagas;
}

void exibirQuantidadeVagas() {
  // LCD exibe vaga normal
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(vagas);
  lcd.print(" vagas livres");
  lcd.setCursor(0, 1);
  lcd.print("     <---");
  delay(1500);
}

void setup() {
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);

  pinMode(botao, INPUT_PULLUP);  // Botão entre pino 2 e GND

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
}

void loop() {
  distancia = sensor_distancia.read();
  verificarCliques();
  sortearQuantidadeVagas();
  exibirQuantidadeVagas();
}
