int ledVermelho = 2;
int ledVerde = 3;
int sensor = A0;
int valor;

void setup() {
  pinMode (ledVermelho, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (sensor, INPUT);
  Serial.begin  (9600);
}

void loop() {
  valor = analogRead(sensor);
  Serial.println(valor);
  delay (500);
  if(valor<400){
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else if(valor>=400 && valor<=700){
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, HIGH);
  } else{
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
  }
}
