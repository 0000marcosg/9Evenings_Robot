//Robot_9Evenings

#include <AFMotor.h>
int paso;
int direccion;

int trig1 = 14;
int trig2 = 17;
int echo1 = 15;
int echo2 = 16;

int seguridad_a;
int seguridad_at;

AF_DCMotor motor_a_i(3);
AF_DCMotor motor_a_d(4);
AF_DCMotor motor_at_i(2);
AF_DCMotor motor_at_d(1);

void setup() {
  Serial.begin(9600);

  // turn on motor
  motor_a_i.setSpeed(255);
  motor_a_d.setSpeed(255);
  motor_at_i.setSpeed(255);
  motor_at_d.setSpeed(255);

  motor_a_i.run(RELEASE);
  motor_a_d.run(RELEASE);
  motor_at_i.run(RELEASE);
  motor_at_d.run(RELEASE);

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);

}

void loop() {
  paso = random(-1, 2);
  direccion = random(-1, 2);

  int dist_adelante = dist_sensor1();
  int dist_atras = dist_sensor2();

  if (paso == -1) {

    if (dist_atras > 50) {
      seguridad_at = 4;
      atras();
    }
    else {
      seguridad_at = 0;
      switch (direccion) {
        case -1:
          atras_i();
          break;
        case 0:
          atras();
          break;
        case 1:
          atras_d();
          break;
      }
    }
  }
  if (paso == 1) {

    if (dist_adelante > 50) {
      seguridad_a = 4;
      atras();
    }
    else {
      seguridad_at = 0;
      switch (direccion) {
        case -1:
          adelante_i();
          break;
        case 0:
          adelante();
          break;
        case 1:
          adelante_d();
          break;
      }
    }
  }

  if (paso == 0) {
    detener();
  }

  Serial.println(paso);
  //delay(500);


}

void adelante() {
  //adelante
  motor_a_i.run(FORWARD);
  motor_a_d.run(FORWARD);
  motor_at_i.run(FORWARD);
  motor_at_d.run(FORWARD);
  Serial.println("adelante");
  delay(500 * seguridad_a);
}

void atras() {
  //atras
  motor_a_i.run(BACKWARD);
  motor_a_d.run(BACKWARD);
  motor_at_i.run(BACKWARD);
  motor_at_d.run(BACKWARD);
  Serial.println("atras");
  delay(500 * seguridad_at);
}

void detener() {
  //detenido
  motor_a_i.run(RELEASE);
  motor_a_d.run(RELEASE);
  motor_at_i.run(RELEASE);
  motor_at_d.run(RELEASE);
  Serial.println("detenido");
  delay(300);
}

void adelante_i() {
  motor_a_i.run(FORWARD);
  motor_at_i.run(FORWARD);
  Serial.println("adelante_i");
  delay(300);
}

void adelante_d() {
  motor_a_d.run(FORWARD);
  motor_at_d.run(FORWARD);
  Serial.println("adelante_d");
  delay(300);

}

void atras_i() {
  motor_a_i.run(BACKWARD);
  motor_at_i.run(BACKWARD);
  Serial.println("atras_i");
  delay(500);
}

void atras_d() {
  motor_a_d.run(BACKWARD);
  motor_at_d.run(BACKWARD);
  Serial.println("atras_d");
  delay(500);
}

int dist_sensor1() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(5);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  int tiempo = pulseIn(echo1, HIGH);
  int distancia = int(0.017 * tiempo);
  //Serial.println(distancia);

  if (distancia < 0) {
    distancia = 20;
  }

  if (distancia > 200) {
    distancia = 200;
  }
  return distancia;
}

int dist_sensor2() {
  digitalWrite(trig2, LOW);
  delayMicroseconds(5);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  int tiempo = pulseIn(echo2, HIGH);
  int distancia = int(0.017 * tiempo);
  //Serial.println(distancia);

  if (distancia < 0) {
    distancia = 0;
  }

  if (distancia > 200) {
    distancia = 200;
  }
  return distancia;
}
