#include <HTTPClient.h>
#include <ESP32_Servo.h>

const char* ssid = "Fortal";
const char* password =  "pingulinha";
//const char* ssid = "Leoba phone";
//const char* password =  "93945560";

Servo dedao, indicador, medio, anular, dedinho, pulso;
int pos = 0;

HTTPClient http;

int last_dedao = 0;
int last_indicador = 0;
int last_medio = 0;
int last_anular = 0;
int last_dedinho = 0;
int last_pulso = 0;

void servosWrite(int dedao_grau, int indicador_grau, int medio_grau, int anular_grau, int dedinho_grau, int pulso_grau)
{
  last_dedao = servoMove(dedao, last_dedao, dedao_grau);
  last_indicador = servoMove(indicador, last_indicador, indicador_grau);
  last_medio = servoMove(medio, last_medio, medio_grau);
  last_anular = servoMove(anular, last_anular, anular_grau);
  last_dedinho = servoMove(dedinho, last_dedinho, dedinho_grau);
  last_pulso = servoMove(pulso, last_pulso, pulso_grau);

  //  dedao.write(dedao_grau);
  //  indicador.write(indicador_grau);
  //  medio.write(medio_grau);
  //  anular.write(anular_grau);
  //  dedinho.write(dedinho_grau);
  //  pulso.write(pulso_grau);
}

int servoMove(Servo servo_i, int begin_angle, int end_angle) {
  if (begin_angle < end_angle) {
    for (pos = begin_angle; pos <= end_angle; pos++) {
      servo_i.write(pos);
      delay(20);
    }
  }
  else {
    for (pos = begin_angle; pos >= end_angle; pos--) {
      // in steps of 1 degree
      servo_i.write(pos);
      delay(20);
    }
  }
  return end_angle;
}

void setup() {

  dedao.attach(2);
  indicador.attach(0);
  medio.attach(4);
  anular.attach(16);
  dedinho.attach(17);
  pulso.attach(5);

  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  http.begin("http://emotiv.ddns.net:80/servovalues");
  //  http.begin("http://192.168.15.7:5002/servovalues");
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    int httpCode = http.GET();                                        //Make the request

    if (httpCode > 0) { //Check for the returning code

      String payload = http.getString();

      if (payload != "false") {
        int value = payload.toInt();
        Serial.println(value);

        switch (value) {
          case 0:
            servosWrite(80, 80, 0, 0, 5, 0);
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
        delay(200);
      }
      else {
        Serial.println(payload);
        delay(2000);
      }
    }

    else {
      delay(5000);
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
}
