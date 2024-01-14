/*
   code write for project:
   https://github.com/Ni3nayka/arduino_encoder

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  october 2023
   modify: november 2023

   link:
   arduino:
   https://github.com/NicoHood/PinChangeInterrupt
   https://habr.com/ru/articles/527044/
   http://cppstudio.com/post/6964/
   ESP32:
   https://dzen.ru/a/X52dzrCeeXzrYfB6

*/

#pragma once

#define ENC_NONE -1
#define MAX_QUANTITY_ENC 8

#if(defined(__AVR_ATmega328P__)) 
// #include "PinChangeInterrupt.h"
#define ENC_SETUP_INTERRUPT(interrupt_pin,interrupt_fun) attachPCINT(digitalPinToPCINT(interrupt_pin), interrupt_fun, CHANGE); 
#elif (defined(ESP32)) 
#define ENC_SETUP_INTERRUPT(interrupt_pin,interrupt_fun) attachInterrupt(digitalPinToInterrupt(interrupt_pin), interrupt_fun, CHANGE); 
// #else
// #error "lib not supported this board"
#endif

#define ENC_SETUP_IF_FOR_INTERRUPT(enc_number_test,pin_a,pin_b,fun_1,fun_2) if (Encoder::enc_number==enc_number_test) { \
  ENC_SETUP_INTERRUPT(pin_a,fun_1); if (pin_b!=ENC_NONE) ENC_SETUP_INTERRUPT(pin_b,fun_2); }

int enc_counter__NOT_USING = 0;
bool enc_dat__NOT_USING[MAX_QUANTITY_ENC][6] = {0}; // [enc_number] [a_new,a_last,b_new,b_last,reverse_enc,one_pin_enc_flag]
long int enc_count__NOT_USING[MAX_QUANTITY_ENC] = {0};

class Encoder {
  public:
    Encoder() {
      Encoder::enc_number = enc_counter__NOT_USING;
      enc_counter__NOT_USING++;
    }

    void setup(int pin_a, int pin_b=ENC_NONE) {
      pinMode(pin_a,INPUT);
      if (pin_b!=ENC_NONE) 
        pinMode(pin_b,INPUT);
      enc_dat__NOT_USING[Encoder::enc_number][0] = digitalRead(pin_a);
      enc_dat__NOT_USING[Encoder::enc_number][2] = pin_b!=ENC_NONE?digitalRead(pin_b):0;
      enc_dat__NOT_USING[Encoder::enc_number][1] = enc_dat__NOT_USING[Encoder::enc_number][0];
      enc_dat__NOT_USING[Encoder::enc_number][3] = enc_dat__NOT_USING[Encoder::enc_number][2];
      enc_dat__NOT_USING[Encoder::enc_number][4] = 0;
      enc_dat__NOT_USING[Encoder::enc_number][5] = (pin_b==ENC_NONE);
      enc_count__NOT_USING[Encoder::enc_number] = 0;
      ENC_SETUP_IF_FOR_INTERRUPT(0,pin_a,pin_b,Encoder::interrupt_enc_1,Encoder::interrupt_enc_2);
      ENC_SETUP_IF_FOR_INTERRUPT(1,pin_a,pin_b,Encoder::interrupt_enc_3,Encoder::interrupt_enc_4);
      ENC_SETUP_IF_FOR_INTERRUPT(2,pin_a,pin_b,Encoder::interrupt_enc_5,Encoder::interrupt_enc_6);
      ENC_SETUP_IF_FOR_INTERRUPT(3,pin_a,pin_b,Encoder::interrupt_enc_7,Encoder::interrupt_enc_8);
      ENC_SETUP_IF_FOR_INTERRUPT(4,pin_a,pin_b,Encoder::interrupt_enc_9,Encoder::interrupt_enc_10);
      ENC_SETUP_IF_FOR_INTERRUPT(5,pin_a,pin_b,Encoder::interrupt_enc_11,Encoder::interrupt_enc_12);
      ENC_SETUP_IF_FOR_INTERRUPT(6,pin_a,pin_b,Encoder::interrupt_enc_13,Encoder::interrupt_enc_14);
      ENC_SETUP_IF_FOR_INTERRUPT(7,pin_a,pin_b,Encoder::interrupt_enc_15,Encoder::interrupt_enc_16);
    }
    
    void reverse() {
      enc_dat__NOT_USING[Encoder::enc_number][4] = !enc_dat__NOT_USING[Encoder::enc_number][4];
    }

    long int get() {
      return enc_count__NOT_USING[Encoder::enc_number];
    }

    void clear() {
      enc_count__NOT_USING[Encoder::enc_number] = 0;
    }
    
  private:
    int enc_number;
    
    static void interrupt_common(int interrupt_number) {
      /* shematic:
       * // update data
       * enc_dat_(A/B)_real = !enc_dat_(A/B)_real;
       * // operating
       * if ((enc_dat_A_real!=enc_dat_B_last)!=reverse_enc_flag) enc++;
       * else enc--;
       * // save
       * enc_dat_A_last = enc_dat_A_real;
       * enc_dat_B_last = enc_dat_B_real;
       */
      int enc_number = (interrupt_number-1)/2;
      enc_dat__NOT_USING[enc_number][0] = enc_dat__NOT_USING[enc_number][0]!=(interrupt_number%2);
      enc_dat__NOT_USING[enc_number][2] = enc_dat__NOT_USING[enc_number][2]==(interrupt_number%2);
      enc_count__NOT_USING[enc_number] += int(((enc_dat__NOT_USING[enc_number][0]!=enc_dat__NOT_USING[enc_number][3])||enc_dat__NOT_USING[enc_number][5])!=enc_dat__NOT_USING[enc_number][4])*2-1;
      enc_dat__NOT_USING[enc_number][1] = enc_dat__NOT_USING[enc_number][0];
      enc_dat__NOT_USING[enc_number][3] = enc_dat__NOT_USING[enc_number][2];
    }
    
    static void interrupt_enc_1()  { Encoder::interrupt_common(1);  }
    static void interrupt_enc_2()  { Encoder::interrupt_common(2);  }
    static void interrupt_enc_3()  { Encoder::interrupt_common(3);  }
    static void interrupt_enc_4()  { Encoder::interrupt_common(4);  }
    static void interrupt_enc_5()  { Encoder::interrupt_common(5);  }
    static void interrupt_enc_6()  { Encoder::interrupt_common(6);  }
    static void interrupt_enc_7()  { Encoder::interrupt_common(7);  }
    static void interrupt_enc_8()  { Encoder::interrupt_common(8);  }
    static void interrupt_enc_9()  { Encoder::interrupt_common(9);  }
    static void interrupt_enc_10() { Encoder::interrupt_common(10); }
    static void interrupt_enc_11() { Encoder::interrupt_common(11); }
    static void interrupt_enc_12() { Encoder::interrupt_common(12); }
    static void interrupt_enc_13() { Encoder::interrupt_common(13); }
    static void interrupt_enc_14() { Encoder::interrupt_common(14); }
    static void interrupt_enc_15() { Encoder::interrupt_common(15); }
    static void interrupt_enc_16() { Encoder::interrupt_common(16); }
};
