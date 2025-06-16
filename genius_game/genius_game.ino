int ledVermelho = 2;
int ledVerde = 3;
int ledAzul = 4;
int ledAmarelo = 5;

int botaoVermelho = 6;
int botaoVerde = 7;
int botaoAzul = 8;
int botaoAmarelo = 9;

int buzzer = 11;

int rodadaAtual = 0;
int ledsRespondidos = 0;
int rodadaLimite = 20;

int sequenciaLeds[rodadaLimite];

enum estados {
  PRONTO_PARA_PROXIMA_RODADA,
  USUARIO_JOGANDO,
  DERROTA,
  VITORIA
};

int sortear(){
  return random(ledVermelho,ledAmarelo+1);
}

void iniciarJogo(){
  int jogo = analogRead(0);
  randomSeed(jogo);
  for(int i=0; i<rodadaLimite; i++){
    sequenciaLeds[i]=sortear();
  }
}

void piscarLed(int corLed){
  verificarSomLed(corLed);
  digitalWrite(corLed, HIGH);
  delay(500);
  digitalWrite(corLed, LOW);
  delay(500);
}

void tocarSom(int frequencia){
  tone(buzzer, frequencia);
  delay(500);
  noTone(buzzer);
}

void verificarSomLed(int corLed){
  switch (corLed){
    case ledVermelho:
      tocarSom(500);
      break;
    case ledVerde:
      tocarSom(1000);
      break;
    case ledAzul:
      tocarSom(1500);
      break;
    case ledAmarelo:
    tocarSom(2000);
    break;
  }
}

int verificarEstadoAtual() {
  if (rodadaAtual <= rodadaLimite) {
    rodaAtual++;
    
    if (ledsRespondidos == rodadaAtual) {  //quando o jogador apertar todos os botoes na ordem
      return PRONTO_PARA_PROXIMA_RODADA;
    } else {  //quando o jogador nao apertar todos os botoes
      return USUARIO_JOGANDO;
    }
  } else if (rodadaAtual == rodadaLimite + 1) {  //quando o jogador acertar as 20 sequencias
    return VITORIA;
  } else {  //quando o jogador errar a sequencia
    return DERROTA;
  }
}

void finalizarJogoVitoria(){
  for(int i = 0; i < 5; i++){
    tocarSom(2000);
    piscarLed(ledVermelho);
    tocarSom(2500);
    piscarLed(ledVerde);
    tocarSom(3000);
    piscarLed(ledAzul);
    tocarSom(3500);
    piscarLed(ledAmarelo);
  }
}

void finalizarJogoDerrota(){
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledAzul, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  delay(250);
  tone(buzzer, 392, 450);
  delay(50);
  digitalWrite(ledVermelho, LOW);
  tone(buzzer, 330, 450);
  delay(50);
  digitalWrite(ledVerde, LOW);
  tone(buzzer, 300, 450);
  delay(50);
  digitalWrite(ledAzul, LOW);
  tone(buzzer, 262, 700);
  digitalWrite(ledAmarelo, LOW);
}

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);

  pinMode(botaoVermelho, INPUT_PULLUP);
  pinMode(botaoVerde, INPUT_PULLUP);
  pinMode(botaoAzul, INPUT_PULLUP);
  pinMode(botaoAmarelo, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
}
