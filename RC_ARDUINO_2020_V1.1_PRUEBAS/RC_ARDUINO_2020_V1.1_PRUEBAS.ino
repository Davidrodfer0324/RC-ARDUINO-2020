#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotorAD = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorAT = AFMS.getMotor(2);

int FG = 0;

void setup() {
  Serial.begin(115200);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(40, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);

  AFMS.begin();
  myMotorAD->setSpeed(70);
  myMotorAT->setSpeed(70);
}

void loop() {
  int S1 = digitalRead(40);
  int LDRL = analogRead(A9);
  int LDRR = analogRead(A8);
  int v1 = digitalRead(8);
  int v2 = digitalRead(9);
  FG = 0;

  if (LDRL > 440) FG = 3;
  if (LDRR > 265) FG = 2;
  if (LDRL > 440 && LDRR > 265) FG = 4;
  if (S1 == 0) FG = 1;

  switch (FG) {
    case 1:
      esquivo();
      break;

    case 2:
      myMotorAD->run(BACKWARD); //BACK
      myMotorAT->run(FORWARD);  //FOR
      delay(250);
      break;

    case 3:
      myMotorAD->run(BACKWARD);   //FOR
      myMotorAT->run(FORWARD);  //BACK
      delay(250);
      break;

    case 4:
      myMotorAD->run(RELEASE);
      myMotorAT->run(RELEASE);
      break;


    default:
      if (v1 == 0 && v2 == 0) { //LINEA NEGRA //0 0
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

      if (v1 == 1 && v2 == 1) { //GAB
        myMotorAD->run(FORWARD);
        myMotorAT->run(FORWARD);
      }
      break;
  }
}
