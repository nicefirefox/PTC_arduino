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
unsigned long onDelay = 30000; // время задержки включения
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

  // определение начальных условий
  ds.requestTemp(); // запрос температуры

  volt=(float)analogRead(A0)*rCoef; // измерение напряжения
  

  if (butFlag and counter==0){
    if (digitalRead(3)==0){
      counter=1;}
    Serial.print(temp);
    Serial.print(volt);
    Serial.print("not pushed\n");
  }

  // диагностика числа нажатий
  if (counter==0){
    digitalWrite(13, HIGH);
    delay(300);
    digitalWrite(13, LOW);
  }

  Serial.print("Voltage: ");
  Serial.print(volt);
  delay(500);
  readT();

  // включение по кнопке через 30ctr после включения и температуре менее 10 градусов
  if (counter==1 and err == 0 and millis()>onDelay and temp<10 and volt>13.5 and offFlag==1){ // кнопка
    currentMillis=millis();
    Serial.print("=== button ===");
    if (stateR2 == LOW and stateR3 == LOW) { // включение второй ступени на 4 минуты
      stateR2 = HIGH;
      stateR3 = HIGH;
      digitalWrite(relay2, stateR2);
      digitalWrite(relay3, stateR3);
    }
    while (millis()-currentMillis<300000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR2 = LOW;
    stateR3 = LOW;
    digitalWrite(relay2, stateR2);
    digitalWrite(relay3, stateR3);
    counter=0;
    butFlag=0;
  }

  // основной цикл
  if (err == 0 and millis()>onDelay and temp<5 and temp>0 and volt>13.5 and offFlag==1){ // первый диапазон - 1 ступень пока температура не поднимется до 30 градусов или не пройдет 10 мин
    currentMillis=millis();
    Serial.print("=== 1 ===");
    if (stateR1 == LOW) { // включение первой ступени
      stateR1 = HIGH;
      digitalWrite(relay1, stateR1);
    }
    while (millis()-currentMillis<300000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR1 = LOW;
    digitalWrite(relay1, stateR1);
    offFlag=0; // выкл
  }
  

  if (err == 0 and millis()>onDelay and temp<=0 and temp>-10 and volt>13.5 and offFlag==1){ // второй диапазон - 1 ступень пока температура не поднимется до 30 градусов или не пройдет 10 мин
    currentMillis=millis();
    Serial.print("=== 2 ===");
    if (stateR1 == LOW) { // включение первой ступени
      stateR1 = HIGH;
      digitalWrite(relay1, stateR1);
    }
    while (millis()-currentMillis<60000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR1 = LOW;
    digitalWrite(relay1, stateR1);

    if (stateR2 == LOW and stateR3 == LOW and temp<30) { // включение второй ступени на 4 минуты
      stateR2 = HIGH;
      stateR3 = HIGH;
      digitalWrite(relay2, stateR2);
      digitalWrite(relay3, stateR3);
    }
    while (millis()-currentMillis<300000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR2 = LOW;
    stateR3 = LOW;
    digitalWrite(relay3, stateR3);
    digitalWrite(relay2, stateR2);
    offFlag = 0;
  }

  if (err == 0 and millis()>onDelay and temp<=-10 and temp>-15 and volt>13.5 and offFlag==1){ // третий диапазон - 1 ступень пока температура не поднимется до 30 градусов или не пройдет 10 мин
    currentMillis=millis();
    Serial.print("=== 3 ===");
    if (stateR1 == LOW) { // включение первой ступени
      stateR1 = HIGH;
      digitalWrite(relay1, stateR1);
    }
    while (millis()-currentMillis<60000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR1 = LOW;
    digitalWrite(relay1, stateR1);

    if (stateR2 == LOW and stateR3 == LOW and temp<30) { // включение второй ступени на 4 минуты
      stateR2 = HIGH;
      stateR3 = HIGH;
      digitalWrite(relay2, stateR2);
      digitalWrite(relay3, stateR3);
    }
    while (millis()-currentMillis<600000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR2 = LOW;
    stateR3 = LOW;
    digitalWrite(relay3, stateR3);
    digitalWrite(relay2, stateR2);
    offFlag = 0;
  }

  if (err == 0 and millis()>onDelay+30000 and temp<=-15 and volt>13.5 and offFlag==1){ // четвертый диапазон - 1 ступень пока температура не поднимется до 30 градусов или не пройдет 10 мин
    currentMillis=millis();
    Serial.print("=== 4 ===");
    if (stateR1 == LOW) { // включение первой ступени
      stateR1 = HIGH;
      digitalWrite(relay1, stateR1);
    }
    while (millis()-currentMillis<60000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR1 = LOW;
    digitalWrite(relay1, stateR1);

    if (stateR2 == LOW and stateR3 == LOW and temp<30) { // включение второй ступени на 4 минуты
      stateR2 = HIGH;
      stateR3 = HIGH;
      digitalWrite(relay2, stateR2);
      digitalWrite(relay3, stateR3);
    }
    while (millis()-currentMillis<300000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    if (stateR1 == LOW and temp<30) { // включение первой ступени
      stateR1 = HIGH;
      digitalWrite(relay1, stateR1);
    }
    while (millis()-currentMillis<600000 and temp<30){ // задержка на работу
      ds.requestTemp();
      delay(5000);
      readT();
    }
    stateR1 = LOW;
    stateR2 = LOW;
    stateR3 = LOW;
    digitalWrite(relay3, stateR3);
    digitalWrite(relay2, stateR2);
    digitalWrite(relay1, stateR1);
    offFlag = 0;
  }


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