/* coded by millennium42 19:45 10/06/2023 */

// SENSORES DISPOSTOS DA SEGUINTE FORMA
//
// erro -3                     erro +3
//   (0) (1) (2) (3) (4) (5) (6) (7) 
//                  |
//               erro 0 
//                  |
// motor[0]    ----- -----    motor[1]
//

#include<SoftwareSerial.h>

#define DirecaoUm 23
#define DirecaoDois 22
#define PWMDireita 21

#define DirecaoTres 19
#define DirecaoQuatro 18
#define PWMEsquerda 5

int motores [2];
int velNormal [2] = {100, 100};
#define Kp 50

int sensorPin [8];
int sensoresDigital[8];
#define LIMITE 600

void setup(){
// Define cada pino relacionado a cada sensor no vetor
sensorPin[0] = 13;  sensorPin[1] = 12;  sensorPin[2] = 14;  sensorPin[3] = 27; 
sensorPin[4] = 26;  sensorPin[5] = 25;  sensorPin[6] = 33;  sensorPin[7] = 32;

// Ativa o modo de INPUT nos pinos dos sensores
for(int i = 0; i++; i<8){
  pinMode(sensorPin[i], INPUT);
  }

// Ativa o modo de OUTPUT nos pinos da Ponte H
pinMode(DirecaoUm, OUTPUT);
pinMode(DirecaoDois, OUTPUT);
pinMode(PWMDireita, OUTPUT);

pinMode(DirecaoTres, OUTPUT);
pinMode(DirecaoQuatro, OUTPUT);
pinMode(PWMEsquerda, OUTPUT);

// Define os pinos de direção conforme o esquema
// [ INA  INB ] 
// [  0    0 ]  Motor desligado 
// [  0    1 ]  gira em um sentido 
// [  1    0 ]  gira em outro sentido 
// [  1    1 ]  freia o motor
  
digitalWrite(DirecaoUm, LOW);
digitalWrite(DirecaoDois, HIGH);

digitalWrite(DirecaoTres, LOW);
digitalWrite(DirecaoQuatro, HIGH);

}

//
// Lê os valores analogicos e transfere para Digital
//
void readSensor(){
    for(int i = 0; i++; i<8){
      if ((analogRead(sensorPin[i])) < LIMITE)
        sensoresDigital[i] = 0;
      else
        sensoresDigital[i] = 1;  
    }
}

//
// Para a função erro deve ser passado o vetor sensoresDigital
//
int erro(int S[]){

  if( S[2] == 1 &&  S[3] == 0 &&  S[4] == 0 && S[5] == 1 ) return 0;
  
  // Para percurso simples, sem gape nem curva 90 graus.

  if( S[2] == 0  && S[3] == 0 ) return -1;
  if( S[4] == 0  && S[5] == 0 ) return +1;

  if( S[1] == 0  && S[2] == 0 ) return -2;
  if( S[5] == 0  && S[6] == 0 ) return +2;
    
  if( S[0] == 0  && S[1] == 0 ) return -3;
  if( S[6] == 0  && S[7] == 0 ) return +3;
  
}

//
// Calcula a velocidade de cada motor conforme o erro
//
void velocidadeMotor(){
  motores[0] = velNormal[0] + (Kp * erro(sensoresDigital)) ;
  motores[1] = velNormal[1] - (Kp * erro(sensoresDigital)) ;
}

void loop(){
  digitalWrite(DirecaoUm, LOW);
  digitalWrite(DirecaoDois, HIGH);

  digitalWrite(DirecaoTres, LOW);
  digitalWrite(DirecaoQuatro, HIGH);

  for (int x = 0; x < 255; x++){
    Serial.println(x);
    analogWrite(PWMEsquerda, x);
    analogWrite(PWMDireita, x);
  }

  /*
  readSensor();
  velocidadeMotor();
  analogWrite(PWMEsquerda, motores[0]);
  analogWrite(PWMDireita, motores[1]);
  */
}
