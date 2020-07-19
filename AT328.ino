#include <SoftwareSerial.h>

SoftwareSerial mySerial(13,12);

int motor;
int RPWM=5;
int LPWM=3;
const int A = 2;
const int B = 4;
const int C = 7;
const int D = 8;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
    pinMode(A, INPUT);
    pinMode(B, INPUT);
    pinMode(C, INPUT);
    pinMode(D, INPUT);
    pinMode(RPWM,OUTPUT);
    pinMode(LPWM,OUTPUT);
}

void loop() {
  if (mySerial.available()>0)
  {
    motor=mySerial.read();
    if (motor == 55){
      lambat()
    }
    if (motor == 125){
      sedang()
    }
    if (motor == 200){
      kencang()
    }
    if (motor == 255){
      ngebut()
    }
  }
  
  if(digitalRead(A) == LOW){
    lambat();
  }
  else if (digitalRead(B) == LOW){
    sedang();
  }
  else if (digitalRead(C) == LOW){
    kencang();
  }
  else if (digitalRead(D) == LOW){
    ngebut();
  }
  else {
    mati();
  }
}

void mati(){
  analogWrite(LPWM,0);
  analogWrite(RPWM,0);
}

void lambat(){
  analogWrite(LPWM,55);
  analogWrite(RPWM,0);
}

void sedang(){
  analogWrite(LPWM,125);
  analogWrite(RPWM,0);
}

void kencang(){
  analogWrite(LPWM,200);
  analogWrite(RPWM,0);
}

void ngebut(){
  analogWrite(LPWM,255);
  analogWrite(RPWM,0);
}
