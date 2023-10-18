/*
   code write for project:
   https://github.com/Ni3nayka/Encoders

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  February 2022
   modify: April 2023
*/

#pragma once

//#include "PinChangeInterrupt.h"
#include "Pins.h"
#include "EncMotor.h"
//#include "EncMotor_1.h"

#ifndef ENC_MOTOR_PARROT_CM
#define ENC_MOTOR_PARROT_CM 157
#endif
#ifndef ENC_MOTOR_PARROT_ANGLE
#define ENC_MOTOR_PARROT_ANGLE 25
#endif

#define MAX_ENCODERS_QUANTITY 4 // 10

class Encoders {
  public:

    int add(int pin_1, int pin_2=-1); // return number
    void reverse(int number);
    
    long int value[MAX_ENCODERS_QUANTITY] = {0};
    long int read(int number);
    void clear(int number);

    // =========================================================
    enc_motor motor_A;
    
    void setup() {
      Encoders::motor_A.setup(L298P_PWMA,L298P_DIRA,L298P_ENCA1,L298P_ENCA2);
    }
    void motors(long int speed_a, long int speed_b) {
      Encoders::motor_A.run(speed_a);
    }
    void enc_run_update() {
      
    }
  

//    void reverse_motor_A() { Encoders::motor_A.reverse_motor = Encoders::motor_A.reverse_motor==1?-1:1; }
//    void reverse_motor_B() { Encoders::motor_B.reverse_motor = Encoders::motor_B.reverse_motor==1?-1:1; }
//    void reverse_enc_A() { Encoders::motor_A.reverse_enc = !Encoders::motor_A.reverse_enc; }
//    void reverse_enc_B() { Encoders::motor_B.reverse_enc = !Encoders::motor_B.reverse_enc; }
    
//  private:
//    int reverse_MA, reverse_MB; 
//    bool reverse_EA, reverse_EB; 
};

Encoders encoders;
