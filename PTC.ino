#include <GyverDS18.h>
GyverDS18Single ds(7);  // пин
float temp = 10.; // переменная для хранения температуры
float volt = 0.;
int err = 0; // маркер ошибки
float rCoef = 5.0/1023.0*10.7; // перевод в вольты

// пины реле
const int relay1 = 6; // pin R1
const int relay2 = 5; // pin R2
const int relay3 = 4; // pin R3
// начальное состояние
int stateR1 = LOW;
int stateR2 = LOW;
int stateR3 = LOW;


// настройка постоянных времени
unsigned long onDelay = 60000; // время задержки включения
int offFlag = 1 ; // флаг работы
unsigned long currentMillis = 0; // таймер
int voltFlag = 0; // флаг работы по напряжению

int counter = 0;  // флаг прерывания по кнопке
int butFlag = 1;

void setup() {
  Serial.begin(9600);
  // инициализации входов/выходов
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, stateR1);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay2, stateR2);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay3, stateR3);
  pinMode(A0, INPUT);
  volt = (float)analogRead(A0)*rCoef;

  // подключили кнопку на D2 и GND
  pinMode(3, INPUT_PULLUP);
  //diagnostics
  pinMode(13, OUTPUT);
}


void loop() {
  ds.requestTemp(); // запрос температуры

  volt=(float)analogRead(A0)*rCoef;
  if (volt>13.5){
    voltFlag=1;
  }
  else {
    voltFlag=0;
    currentMillis = millis();
  }

  if (err == 0 and millis()-currentMillis>onDelay and offFlag == 1 and voltFlag == 1){
    if (temp<5. and temp>0.){ // первый диапазон суммарное время 60000
      Serial.print("=== 1 ===");
      if (stateR1 == LOW) { // включение первой ступени
        stateR1 = HIGH;
        digitalWrite(relay1, stateR1);
      }
      while (millis()-currentMillis<60000+onDelay){ // задержка на работу
      }
      stateR1 = LOW;
      digitalWrite(relay1, stateR1);
      offFlag=0; // выкл
    }
    if (temp<=0. and temp>-10.){ // второй диапазон суммарное время 180000
      Serial.print("=== 2 ===");
      if (stateR1 == LOW) { // включение первой ступени
        stateR1 = HIGH;
        digitalWrite(relay1, stateR1);
      }
      while (millis()-currentMillis<60000+onDelay){ // задержка на работу
      }
      if (stateR2 == LOW) { // включение второй ступени на 2 минуты
        stateR2 = HIGH;
        digitalWrite(relay2, stateR2);
      }
      while (millis()-currentMillis<180000+onDelay){ // задержка на работу
      }
      stateR1 = LOW;
      stateR2 = LOW;
      digitalWrite(relay1, stateR1);
      digitalWrite(relay2, stateR2);
      offFlag = 0;
    }
    if (temp<=-10. and temp>-20.){ // третий диапазон суммарное время 240000
      Serial.print("=== 3 ===");
      if (stateR1 == LOW) { // включение первой ступени
        stateR1 = HIGH;
        digitalWrite(relay1, stateR1);
      }
      while (millis()-currentMillis<60000+onDelay){ // задержка на работу
      }
      if (stateR2 == LOW) { // включение второй ступени на 3 минуты
        stateR2 = HIGH;
        digitalWrite(relay2, stateR2);
      }
      while (millis()-currentMillis<240000+onDelay){ // задержка на работу
      }
      stateR1 = LOW;
      stateR2 = LOW;
      digitalWrite(relay1, stateR1);
      digitalWrite(relay2, stateR2);
      offFlag = 0;
    }
    if (temp<=-20. and temp>-30.){ // четвертый диапазон суммарное время 360000
      Serial.print("=== 4 ===");
      if (stateR1 == LOW) { // включение первой ступени
        stateR1 = HIGH;
        digitalWrite(relay1, stateR1);
      }
      while (millis()-currentMillis<60000+onDelay){ // задержка на работу
      }
      if (stateR2 == LOW) { // включение второй ступени на 2 минуты
        stateR2 = HIGH;
        digitalWrite(relay2, stateR2);
      }
      while (millis()-currentMillis<180000+onDelay){ // задержка на работу
      }
      if (stateR3 == LOW) { // включение третей ступени на 3 минуты
        stateR3 = HIGH;
        digitalWrite(relay3, stateR3);
      }
      while (millis()-currentMillis<360000+onDelay){ // задержка на работу
      }
      stateR1 = LOW;
      stateR2 = LOW;
      stateR3 = LOW;
      digitalWrite(relay1, stateR1);
      digitalWrite(relay2, stateR2);
      digitalWrite(relay3, stateR3);
      offFlag = 0;
    }
    if (temp<=-30. and temp>-40.){ // пятый диапазон суммарное время 600000
      Serial.print("=== 5 ===");
      if (stateR1 == LOW) { // включение первой ступени
        stateR1 = HIGH;
        digitalWrite(relay1, stateR1);
      }
      while (millis()-currentMillis<60000+onDelay){ // задержка на работу
      }
      if (stateR2 == LOW) { // включение второй ступени на 2 минуты
        stateR2 = HIGH;
        digitalWrite(relay2, stateR2);
      }
      while (millis()-currentMillis<180000+onDelay){ // задержка на работу
      }
      if (stateR3 == LOW) { // включение третей ступени на 3 минуты
        stateR3 = HIGH;
        digitalWrite(relay3, stateR3);
      }
      while (millis()-currentMillis<360000+onDelay){ // задержка на работу
      }
      stateR3 = LOW;
      digitalWrite(relay3, stateR3);
      while (millis()-currentMillis<600000+onDelay){ // задержка на работу
      }
      stateR1 = LOW;
      stateR2 = LOW;
      digitalWrite(relay1, stateR1);
      digitalWrite(relay2, stateR2);
      offFlag = 0;
    }
  }



  if (butFlag and counter==0){
    if (digitalRead(3)==0){
      counter=1;}
    Serial.print("not pushed");
  }

// диагностика
if (counter==0){
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);
}

  // включение по кнопке через минуту после включения и температуре менее 10 градусов
  if (err == 0 and millis()-currentMillis>onDelay and counter == 1 and voltFlag == 1){
      if (butFlag){ // первый диапазон суммарное время 60000
        Serial.print("=== start with button ===");
        if (stateR1 == LOW) { // включение первой ступени
          stateR1 = HIGH;
          digitalWrite(relay1, stateR1);
        }
        while (millis()-currentMillis<120000){ // задержка на работу
        }
        if (stateR2 == LOW) { // включение второй ступени на 2 минуты
          stateR2 = HIGH;
          digitalWrite(relay2, stateR2);
        }
        while (millis()-currentMillis<240000){ // задержка на работу
        }
        stateR1 = LOW;
        stateR2 = LOW;
        digitalWrite(relay1, stateR1);
        digitalWrite(relay2, stateR2);
        butFlag = 0;
    }
  }

  Serial.print("Voltage: ");
  Serial.print(volt);
  delay(500);
  
  readT();


}



void readT(){
  if (ds.readTemp()) {  // если чтение успешно
    temp = ds.getTemp();
    Serial.print("temp: ");
    Serial.println(temp);
    err=0;
    } 
  else {
    Serial.println("error");
    err = 1;
  }
}