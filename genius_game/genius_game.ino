#define ledVermelho 2
#define ledVerde 3
#define ledAzul 4
#define ledAmarelo 5

int botaoVermelho = 6;
int botaoVerde = 7;
int botaoAzul = 8;
int botaoAmarelo = 9;

int buzzer = 11;

int indefinido = -1;
int rodadaAtual = 0;
int ledsRespondidos = 0;

#define rodadaLimite 20

int sequenciaLeds[rodadaLimite];

enum estados {
  PRONTO_PARA_PROXIMA_RODADA,
  USUARIO_JOGANDO,
  DERROTA,
  VITORIA
};

int sortear() {
  return random(ledVermelho, ledAmarelo + 1);
}

void iniciarJogo() {
  int jogo = analogRead(0);
  randomSeed(jogo);
  for (int i = 0; i < rodadaLimite; i++) {
    sequenciaLeds[i] = sortear();
  }
}

void piscarLed(int corLed) {
  digitalWrite(corLed, HIGH);
  verificarSomLed(corLed);
  digitalWrite(corLed, LOW);
  delay(500);
}

void tocarSom(int frequencia) {
  tone(buzzer, frequencia);
  delay(500);
  noTone(buzzer);
}

void verificarSomLed(int corLed) {
  switch (corLed) {
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
void checarResposta() {
  int resposta = checarCorBotao();
  Serial.println(resposta);
  delay(50);
  if (resposta == indefinido) {
    return;
  }
  if (resposta == sequenciaLeds[ledsRespondidos]) {
    ledsRespondidos++;
  } else {
    rodadaAtual = rodadaLimite + 2;  //Quando a rodadaAtual for 22, houve derrota, poderia ser 300 até, é simbólico.
  }
}

void gerarRodada() {
  for (int i = 0; i < rodadaAtual; i++) {
    piscarLed(sequenciaLeds[i]);
  }
}

void prepararProximaRodada() {
  rodadaAtual++;
  ledsRespondidos = 0;
  if (rodadaAtual <= rodadaLimite) {
    gerarRodada();
  }
}

int verificarEstadoAtual() {
  if (rodadaAtual <= rodadaLimite) {

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

int checarCorBotao() {
  if (digitalRead(botaoVermelho) == LOW) {
    piscarLed(ledVermelho);
    return ledVermelho;
  }

  if (digitalRead(botaoVerde) == LOW) {
    piscarLed(ledVerde);
    return ledVerde;
  }

  if (digitalRead(botaoAzul) == LOW) {
    piscarLed(ledAzul);
    return ledAzul;
  }

  if (digitalRead(botaoAmarelo) == LOW) {
    piscarLed(ledAmarelo);
    return ledAmarelo;
  }
  return indefinido;
}

void finalizarJogoVitoria() {
  for (int i = 0; i < 5; i++) {
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

void finalizarJogoDerrota() {
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

  // iniciarJogo();

  finalizarJogoVitoria();
}

void loop() {

  // switch (verificarEstadoAtual()) {
  //   case DERROTA:
  //   Serial.println("Perdeu!");
  //     finalizarJogoDerrota();
  //     break;
  //   case VITORIA:
  //   Serial.println("Venceu!");
  //     finalizarJogoVitoria();
  //     break;
  //   case USUARIO_JOGANDO:
  //   Serial.println("Responde Logo!");
  //     checarResposta();
  //     break;
  //   case PRONTO_PARA_PROXIMA_RODADA:
  //     Serial.println("Bora lá mais uma meu patrão!");
  //     prepararProximaRodada();
  //     break;
  // }
  // delay(200);
}
