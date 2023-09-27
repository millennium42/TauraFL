/* coded by millennium42 13:46 09/18/23 */

// SENSORES DISPOSTOS DA SEGUINTE FORMA
//
// erro -7                                                      erro +7
//   (1) (2) (3) (4) (5) (6) (7) (8) (9)(10)(11)(12)(13)(14)(15)(16)
//                                  | 
//                                  | 
//                                  | 
//                                  | 
//                                 (0)
//                                erro 0 
// 

#include<SoftwareSerial.h>


int sensoresDigital[16];
int sensorPin[16];


void setup(){
//
// Define cada pino relacionado a cada sensor no vetor
//
  sensorPin[0] = 16;  
  sensorPin[1] = 16;  sensorPin[2] = 16;  sensorPin[3] = 16;  sensorPin[4] = 16;
  sensorPin[5] = 16;  sensorPin[6] = 16;  sensorPin[7] = 16;  sensorPin[8] = 16;
  sensorPin[9] = 16;  sensorPin[10] = 16;  sensorPin[11] = 16;  sensorPin[12] = 16;
  sensorPin[13] = 16;  sensorPin[14] = 16;  sensorPin[15] = 16;  sensorPin[16] = 16;
}

//
//Para a funçaõ erro deve ser passado o vetor sensoresDigital
//
int erro(int S[]){

  if( S[7] == 0 && S[8] == 1 && S[9] == 1 &&  S[10] == 0 &&  S[0] == 1 ) return 0;
  
    // Para curva 90 graus

    else if ( S[7] == 0 && S[8] == 1 && S[9] == 1 && S[10] == 1 && S[11] == 1) return +8;
      else if ( S[10] == 0 && S[9] == 1 && S[8] == 1 && S[7] == 1 && S[6] == 1) return -8;

  
    // Para percurso simples, sem gape nem curva 90 graus.

    else if( S[9] == 1  && S[10] == 1 ) return +1;
  
      else if( S[7] == 1 && S[8] == 1 ) return -1;
  
    else if( S[10] == 1 && S[11] == 1 ) return +2;
  
      else if( S[6] == 1 && S[7] == 1 ) return -2;
  
    else if( S[11] == 1 && S[12] == 1 ) return +3;
  
      else if( S[5] == 1 && S[6] == 1 ) return -3;
  
    else if( S[12] == 1 && S[13] == 1 ) return +4;
  
      else if( S[4] == 1 && S[5] == 1 ) return -4;
  
    else if( S[13] == 1 && S[14] == 1 ) return +5;
  
      else if( S[3] == 1 && S[4] == 1 ) return -5;
  
    else if( S[14] == 1 && S[15] == 1 ) return +6;
  
      else if( S[2] == 1 && S[3] == 1 ) return -6;
  
    else if( S[15] == 1 && S[16] == 1 ) return +7;
  
      else if( S[1] == 1 && S[2] == 1 ) return -7;
    
    // Para o Gape

    else return 0;
  
}