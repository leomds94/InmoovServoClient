#include <ESP32_Servo.h>

Servo dedao, indicador, medio, anular, dedinho, pulso;
int pos = 0;

int value;

int last_dedao = 0;
int last_indicador = 0;
int last_medio = 0;
int last_anular = 0;
int last_dedinho = 0;
int last_pulso = 0;

void servosWrite(int dedao_grau, int indicador_grau, int medio_grau, int anular_grau, int dedinho_grau, int pulso_grau)
{
  dedao.write(dedao_grau);
  indicador.write(indicador_grau);
  medio.write(medio_grau);
  anular.write(anular_grau);
  dedinho.write(dedinho_grau);
  pulso.write(pulso_grau);
}

void setup() {

  dedao.attach(15);
  indicador.attach(18);
  medio.attach(19);
  anular.attach(21);
  dedinho.attach(22);
  pulso.attach(5);

  Serial.begin(115200);

  servosWrite(80, 80, 0, 0, 5, 0);
}

void loop() {
  if (Serial.available() > 0) {
    value = Serial.read() - 48;
    switch (value) {
      case 0:
        servosWrite(70, 90, 0, 0, 0, 0);
        break;
      case 1:
        servosWrite(0, 0, 90, 90, 85, 0);
        break;
      case 2:
        servosWrite(0, 80, 90, 90, 5, 0);
        break;
      case 3:
        servosWrite(80, 5, 90, 90, 5, 0);
        break;
      case 4:
        servosWrite(80, 5, 90, 90, 85, 0);
        break;
      case 5:
        servosWrite(80, 80, 0, 0, 5, 90);
        break;
    }
    Serial.print(value);
    delay(1000);
  }
}
