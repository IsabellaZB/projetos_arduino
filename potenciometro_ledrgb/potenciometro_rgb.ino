int potenciometro= A0;
int ledR = 3;
int ledG = 6;
int ledB = 9;
int intensidade;
int valorLido;

void setup(){
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);
    pinMode(potenciometro, INPUT);
}

void loop(){

    valorLido = analogRead(potenciometro);
    
    if(valorLido<= 341){
        intensidade = map(valorLido, 0,341, 0, 255);
        digitalWrite(ledG, LOW);
        digitalWrite(ledB, LOW);
        analogWrite(ledR, intensidade);
    }
    else if(valorlido>=342 && valorLido<= 682){
        intensidade = map(valorLido,341, 682, 0, 255);
        digitalWrite(ledR, LOW);
        digitalWrite(ledB, LOW);
        analogWrite(ledG, intensidade);
    }
    else{
        intensidade = map(valorLido, 681, 1024, 0, 255);
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, LOW);
        analogWrite(ledB, intensidade)
    }
}
