#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bluetooth(10, 11); // Pinos 10 (RX) e 11 (TX) para comunicação Bluetooth

int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int SETA_DIREITA = 6;
int SETA_ESQUERDA = 7;
int BUZINA = 8;
int FAROL = 9;
int LED_EXTRA = 12; // Pino para o LED extra
char comando;

bool setaDireitaPiscando = false;
bool setaEsquerdaPiscando = false;
bool buzinaLigada = false;
bool farolLigado = false;
bool ledExtraLigado = false;

Servo base;
Servo Servofrente;
Servo garra;

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com o computador host (USB)
  bluetooth.begin(9600); // Inicializa a comunicação serial com o módulo Bluetooth
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(SETA_DIREITA, OUTPUT);
  pinMode(SETA_ESQUERDA, OUTPUT);
  pinMode(BUZINA, OUTPUT);
  pinMode(FAROL, OUTPUT);
  pinMode(LED_EXTRA, OUTPUT);
  digitalWrite(FAROL, LOW);
  digitalWrite(LED_EXTRA, LOW);
  
  base.attach(13); // Pino para o servo da base
  Servofrente.attach(22); // Pino para o servo da frente
  garra.attach(23); // Pino para o servo da garra
}

void loop() {
  while (bluetooth.available()) {
    comando = bluetooth.read();
    if (comando == 'F') {
      frente();
    } else if (comando == 'B') {
      tras();
    } else if (comando == 'L') {
      esquerda();
    } else if (comando == 'R') {
      direita();
    } else if (comando == 'A') {
      ligarSetaDireita();
    } else if (comando == 'a') {
      desligarSetaDireita();
    } else if (comando == 'P') {
      ligarSetaEsquerda();
    } else if (comando == 'p') {
      desligarSetaEsquerda();
    } else if (comando == 'H') {
      ligarSetasSimultaneamente();
    } else if (comando == 'h') {
      desligarSetasSimultaneamente();
    } else if (comando == 'V') {
      desligarBuzina();
    } else if (comando == 'v') {
      ligarBuzina();
    } else if (comando == 'Y') {
      ligarFarol();
    } else if (comando == 'y') {
      desligarFarol();
    } else if (comando == 'E') {
      ligarLedExtra();
    } else if (comando == 'e') {
      desligarLedExtra();
    } else if (comando == 'g') {
      base.write(0); // Comando para mover a base para a posição 0°
    } else if (comando == 'G') {
      base.write(180); // Comando para mover a base para a posição 180°
    } else if (comando == 'm') {
      Servofrente.write(90); // Comando para mover a parte da frente para a posição 90°
    } else if (comando == 'M') {
      Servofrente.write(140); // Comando para mover a parte da frente para a posição 0°
    } else if (comando == 'o') {
      garra.write(180); // Comando para abrir a garra (posição 180°)
    } else if (comando == 'O') {
      garra.write(0); // Comando para fechar a garra (posição 0°)
    } else {
      parado();
    }
  }
  
  if (setaDireitaPiscando) {
    if (millis() % 1000 < 500) {
      digitalWrite(SETA_DIREITA, HIGH);
    } else {
      digitalWrite(SETA_DIREITA, LOW);
    }
  }
  
  if (setaEsquerdaPiscando) {
    if (millis() % 1000 < 500) {
      digitalWrite(SETA_ESQUERDA, HIGH);
    } else {
      digitalWrite(SETA_ESQUERDA, LOW);
    }
  }
  
  if (buzinaLigada) {
    tocarBuzina();
  }
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void tras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parado() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void ligarSetaDireita() {
  setaDireitaPiscando = true;
}

void desligarSetaDireita() {
  setaDireitaPiscando = false;
  digitalWrite(SETA_DIREITA, LOW);
}

void ligarSetaEsquerda() {
  setaEsquerdaPiscando = true;
}

void desligarSetaEsquerda() {
  setaEsquerdaPiscando = false;
  digitalWrite(SETA_ESQUERDA, LOW);
}

void ligarSetasSimultaneamente() {
  setaDireitaPiscando = true;
  setaEsquerdaPiscando = true;
}

void desligarSetasSimultaneamente() {
  setaDireitaPiscando = false;
  setaEsquerdaPiscando = false;
  digitalWrite(SETA_DIREITA, LOW);
  digitalWrite(SETA_ESQUERDA, LOW);
}

void ligarBuzina() {
  buzinaLigada = true;
}

void desligarBuzina() {
  buzinaLigada = false;
  noTone(BUZINA);
}

void tocarBuzina() {
  tone(BUZINA, 1000);
}

void ligarFarol() {
  farolLigado = true;
  digitalWrite(FAROL, HIGH);
}

void desligarFarol() {
  farolLigado = false;
  digitalWrite(FAROL, LOW);
}

void ligarLedExtra() {
  ledExtraLigado = true;
  digitalWrite(LED_EXTRA, HIGH);
}

void desligarLedExtra() {
  ledExtraLigado = false;
  digitalWrite(LED_EXTRA, LOW);
}
