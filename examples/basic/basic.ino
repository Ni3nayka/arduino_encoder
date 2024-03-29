/*
   code write for project:
   https://github.com/Ni3nayka/arduino_encoder

   author: Egor Bakay <egor_bakay@inbox.ru> Ni3nayka
   write:  november 2023
   modify: january  2024
*/


// #define ENC_SAVE_MODE // если при работе энкодеров возникают проблемы
                         // (как правило из-за сторонних библиотек)
                         // расскоментируйте эту строку (с ENC_SAVE_MODE)
                         
#include <arduino_encoder.h>  // Подключаем библиотеку

// Создаем объекты для работы с:
Encoder enc1;                 // первым энкодером
Encoder enc2;                 // вторым энкодером
Encoder enc3;                 // третьим энкодером

void setup() {
  // Базовая установка
  Serial.begin(9600);         // Включаем монитор порта

  // Инициализируем энкодеры, указывая на каких пинах они находятся
  enc1.setup(5,6);            // Энкодер 1 подключен к пинам D5 и D6 (двунаправленный) 
  enc2.setup(7,8);            // Энкодер 2 подключен к пинам D7 и D8 (двунаправленный) 
  enc3.setup(A3);             // Энкодер 3 подключен к пину A3 (однонаправленный) 

  // При необходимости можем "развернуть" энкодер (если энкодер работает не в ту сторону, можно использовать несколько раз)
  enc1.reverse();             // Меняем направление энкодера 1
  enc1.reverse();             // Меняем направление энкодера 1 (т.е. возвращаемся к изначальному состоянию)
  enc2.reverse();             // Меняем направление энкодера 2
  enc3.reverse();             // Меняем направление энкодера 3

  // считываем значения с энкодеров:
  Serial.println(enc1.get()); // Выводим показания энкодера 1
  Serial.println(enc2.get()); // Выводим показания энкодера 2 
  Serial.println(enc3.get()); // Выводим показания энкодера 3

  // при необходимости можем обнулить энкодеры
  enc1.clear();               // Обнуляем энкодер 1
  enc2.clear();               // Обнуляем энкодер 2
  enc3.clear();               // Обнуляем энкодер 3
}

void loop() {}
