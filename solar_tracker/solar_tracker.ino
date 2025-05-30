 #include <Servo.h>

Servo motor;

int ldr_direita = A0;
int ldr_esquerda = A1;
int placa_solar = A2;

int leitura_direita = 0;
int leitura_esquerda = 0;
int leitura_placa = 0;

int pos = 90;
int delta = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ldr_direita, INPUT);
  pinMode(ldr_esquerda, INPUT);
  pinMode(placa_solar, INPUT);
  
  motor.attach(5);
  motor.write(pos);
  delay(1000); // tempo para estabilizar o sistema
}

void loop() {
  leitura_direita = analogRead(ldr_direita); 
  leitura_esquerda = analogRead(ldr_esquerda);
  leitura_placa = analogRead(placa_solar);

  // Exibe leituras
  Serial.print("LDR Direita: ");
  Serial.print(leitura_direita);
  Serial.print(" | LDR Esquerda: ");
  Serial.print(leitura_esquerda);
  Serial.print(" | Placa Solar: ");
  Serial.print(leitura_placa);


int diferenca = leitura_direita - leitura_esquerda;
Serial.print("Diferenca: ");
Serial.println(diferenca);

//int passo = map(diferenca, delta, 1023, 1, 15);

  // Verifica direção da luz e move o servo
  if (leitura_direita > (leitura_esquerda + delta)) {
    pos=pos+5;
    Serial.println(" -> Movendo para DIREITA");
  } else if (leitura_esquerda > (leitura_direita + delta)) {
    pos=pos-5;
    Serial.println(" -> Movendo para ESQUERDA");
  } else {
    Serial.println(" -> Posição mantida");
  }

  // Limita o ângulo do servo
  if (pos > 180) pos = 180;
  if (pos < 0) pos = 0;

  motor.write(pos);
  delay(500);
}