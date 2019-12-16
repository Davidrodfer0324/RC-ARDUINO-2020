#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotorAD = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorAT = AFMS.getMotor(3);

void setup() {
  Serial.begin(115200);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(38, INPUT);

  AFMS.begin();
  myMotorAD->setSpeed(100);
  myMotorAT->setSpeed(100);
}

void loop() {
  int S1 = digitalRead(38);

  int v1 = digitalRead(8);
  int v2 = digitalRead(9);
m:
  if (v1 == 0 && v2 == 0) { //LINEA NEGRA
    myMotorAD->run(FORWARD);
    myMotorAT->run(FORWARD);
  }

  if (v1 == 1 && v2 == 0) { // IZQUIERDA
    myMotorAD->run(FORWARD);
    myMotorAT->run(BACKWARD);
  }

  if (v1 == 0 && v2 == 1) { //DERECHA
    myMotorAD->run(BACKWARD);
    myMotorAT->run(FORWARD);
  }

  if (S1 == 0) {
    esquivo();
  } else {
    goto m;
  }
}
