#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <NewPing.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotorAD = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorAT = AFMS.getMotor(2);

NewPing sonar[2] = {
  NewPing(9, 8, 15), // Each sensor's trigger pin, echo piN
  NewPing(11, 10, 15),
};

int FG = 0;
int buzz = 68;

void setup() {
  Serial.begin(115200);

  Serial.print("ROBOCUP JUNIOR 2020");
  pinMode(12, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(A6, INPUT);
  pinMode(68, OUTPUT);
  AFMS.begin();
}

void loop() {
  int S1 = digitalRead(6);
  int S2 = digitalRead(5);
  int S3 = digitalRead(4);
  int av = digitalRead(12);
  int val = analogRead(A6);
  // int tl = map(val, 0, 1023, 0 , 1);

  FG = 0;

  if (av == 0) FG = 1;
  if (val > 1000) FG = 2;
  if (sonar[0].ping_cm() == 5) FG = 3;
  if (sonar[1].ping_cm() == 5) FG = 4;

  switch (FG) {
    case 1:
      esquivo();
      break;

    case 2:
      myMotorAD->setSpeed(20);
      myMotorAT->setSpeed(20);
      myMotorAD->run(FORWARD);
      myMotorAT->run(FORWARD);
      break;

    case 3:
      Serial.println(" AZUL ULTRASONICO IZQUIERDA ");
      myMotorAD->run(RELEASE);
      myMotorAT->run(RELEASE);
      delay(1300);

      digitalWrite(buzz, HIGH);
      delay(150);
      digitalWrite(buzz, LOW);
      break;

    case 4:
      Serial.println(" AZUL ULTRASONICO DERECHA  ");
      myMotorAD->run(RELEASE);
      myMotorAT->run(RELEASE);
      delay(1300);

      digitalWrite(buzz, HIGH);
      delay(150);
      digitalWrite(buzz, LOW);
      break;

    default:
      myMotorAD->setSpeed(85);
      myMotorAT->setSpeed(85); // 1 == NEGRO // 0 == BLANCO
      if (S2 == 1) { //LINEA NEGRA //0 0
        myMotorAD->run(FORWARD);
        myMotorAT->run(FORWARD);
      } else if (S1 == 1) {
        myMotorAD->run(RELEASE);
        myMotorAT->run(RELEASE);
        delay(100);
        myMotorAD->run(BACKWARD);
        myMotorAT->run(FORWARD);
        delay(110);
      } else if (S3 == 1) {
        myMotorAD->run(RELEASE);
        myMotorAT->run(RELEASE);
        delay(90);
        myMotorAD->run(FORWARD);
        myMotorAT->run(BACKWARD);
        delay(90);
      }
      break;
  }
}
