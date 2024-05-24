#include <Arduino.h>
#include <Servo.h>

Servo servo1;

const int PIN_TRIGGER = 10;
const int PIN_ECHO = 11;

int ENA = 3;
int IN1 = 5;
int IN2 = 4;
int IN3 = 9;
int IN4 = 8;
int ENB = 6;

int leer_izquierda = 0;
int leer_derecha = 0;

int lectura_ultrasonido();
void avanzar();
void izquierda();
void derecha();
void retroceder();
void detener();

void setup()
{

    Serial.begin(9600);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    digitalWrite(ENA, HIGH);
    analogWrite(ENA, 255);

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    digitalWrite(PIN_TRIGGER, LOW);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    digitalWrite(ENB, HIGH);
    analogWrite(ENB, 255);
    servo1.attach(12);
    servo1.write(90);
}


void loop()
{
    delay(500);
    int distancia = lectura_ultrasonido();
    Serial.println(distancia);
     
    if ( distancia >= 100){
      Serial.print("avanzaaaaaaaa\n");
      avanzar();
    }
    else if (distancia >= 50 && distancia <= 100){
      Serial.print("izquierdaaaaaaaa");
      izquierda();
    }
    else if (distancia < 50){
      Serial.print("detenerrrrrrr");
      detener();
      servo1.write(10);
      delay(600);
      leer_derecha = lectura_ultrasonido();
      servo1.write(90);
      delay(600);
      servo1.write(170);
      delay(600);
      leer_izquierda = lectura_ultrasonido();
      servo1.write(90);
      delay(600);

      if (leer_derecha > leer_izquierda){
        Serial.println("gira a la derecha");
        derecha();
      }
      if (leer_izquierda >= leer_derecha){
        Serial.println("Gira a la izquierda");
        izquierda();
      }

    }
   
}

int lectura_ultrasonido()
{
    long duracion;
    int distancia;

    digitalWrite(PIN_ECHO, LOW);
    digitalWrite(PIN_TRIGGER, LOW);
    delayMicroseconds(2);

    digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGGER, LOW);

    duracion = pulseIn(PIN_ECHO, HIGH);
    distancia = ((float)duracion * 0.034) / 2;

    return distancia;
}


void avanzar()
{
    digitalWrite(IN2, 0);
    digitalWrite(IN1, 1);
    digitalWrite(IN4, 1);
    digitalWrite(IN3, 0);
}

void detener()
{
    digitalWrite(IN2, 0);
    digitalWrite(IN1, 0);
    digitalWrite(IN4, 0);
    digitalWrite(IN3, 0);
}

void izquierda()
{
    digitalWrite(IN2, 1);
    digitalWrite(IN1, 0);
    digitalWrite(IN4, 1);
    digitalWrite(IN3, 0);
}

void retroceder()
{
    digitalWrite(IN2, 1);
    digitalWrite(IN1, 0);
    digitalWrite(IN4, 0);
    digitalWrite(IN3, 1);
}

void derecha()
{
    digitalWrite(IN2, 0);
    digitalWrite(IN1, 1);
    digitalWrite(IN4, 0);
    digitalWrite(IN3, 1);
}