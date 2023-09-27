/* coded by millennium42 15:50 09/27/23 */

// SENSORES DISPOSTOS DA SEGUINTE FORMA
//
// erro -3                     erro +3
//   (0) (1) (2) (3) (4) (5) (6) (7) 
//                  |
//               erro 0 
//                  |
// motor[0]    ----- -----    motor[1]
//
//
// erro -4 => Noventa Graus Direita
// erro +4 => Noventa Graus Esquerda
//

#include<SoftwareSerial.h>

#define LIMITE 700 
#define velNormal  120
#define Kp 50

#define velNoventaED 900;
#define velNoventaDD 100;
#define velNoventaEE 100;
#define velNoventaDE 900;

int sensoresDigital[8];
int sensoresAnalog[8];

int motores[2];

int sensorPin[8];


void setup(){
  
// Define cada pino relacionado a cada sensor no vetor

sensorPin[0] = 14;  sensorPin[1] = 27;  sensorPin[2] = 26;  sensorPin[3] = 25; 
sensorPin[4] = 33;  sensorPin[5] = 32;  sensorPin[6] = 35;  sensorPin[7] = 34;

// Ativa o modo de INPUT nos pinos dos sensores

for(int i = 0; i++; i<8){
  pinMode(sensorPin[i], INPUT);
  }

}

//
// Lê os valores analogicos e transfere para Digital
//
void readSensor(){
    for(int i = 0; i++; i<8){
      sensoresAnalog[i] = analogRead(sensorPin[i]);
      if (sensoresAnalog[i] < LIMITE)
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
  
  // Para curvas de 90 graus
  if( S[3] == 0 &&  S[4] == 0 &&  S[5] == 0 && S[6] == 0 && S[7] == 0) return +4;

  if( S[0] == 0 &&  S[1] == 0 &&  S[2] == 0 && S[3] == 0 && S[4] == 0) return -4;

  // Para percurso simples, sem gape nem curva 90 graus.

  if( S[2] == 1  && S[3] == 1 ) return -1;
  if( S[4] == 1  && S[5] == 1 ) return +1;

  if( S[1] == 1  && S[2] == 1 ) return -2;
  if( S[5] == 1  && S[6] == 1 ) return +2;
    
  if( S[0] == 1  && S[1] == 1 ) return -3;
  if( S[6] == 1  && S[7] == 1 ) return +3;
  
  // Para o Gape
  
  return 0;
  
}

//
// Calcula a velocidade de cada motor conforme o erro
//
void velocidadeMotor(){
  if (erro(sensoresDigital) > 3){
    motores[0] = velNoventaED ;
    motores[1] = velNoventaDD ;
  }
  if (erro(sensoresDigital) < -3){
    motores[0] = velNoventaEE ;
    motores[1] = velNoventaDE ;
  }
  else {
  motores[0] = velNormal + (Kp * erro(sensoresDigital)) ;
  motores[1] = velNormal - (Kp * erro(sensoresDigital)) ;
  }
}
