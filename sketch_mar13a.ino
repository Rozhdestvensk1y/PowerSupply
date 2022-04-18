#include <LiquidCrystal.h>
LiquidCrystal lcd( 11, 12, 4, 5, 6, 7);

#define maxA 3
float sumU1 = 0, aU1 = 0; 
float sumU2 = 0, aU2 = 0;
float sumU3 = 0, aU3 = 0;
float sumI1 = 0, aI1 = 0; 
float sumI2 = 0, aI2 = 0;
float sumI3 = 0, aI3 = 0;
float U1,U2,U3;
float I1,I2,I3;
bool q1,q2,q3;
float r2 = 20000.0;
float r1 = 51000.0;
int index = 10;

void setup() 
{
  q1 = true;
  q2 = true;
  q3 = true;
  lcd.begin(20,4);
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop() 
{

   lcd.print("U1");
   lcd.setCursor(7,0);
   lcd.print("U2");
   lcd.setCursor(14,0);
   lcd.print("U3");
  
   printV();

   lcd.setCursor(0,2);
   lcd.print("I1");
   lcd.setCursor(7,2);
   lcd.print("I2");
   lcd.setCursor(14,2);
   lcd.print("I3");
   lcd.setCursor(0,3);
   
   printA();
   
   delay(100);
   lcd.clear();
   /*
   //index++;
   x = ((analogRead(A0) * 5.0)/1024.0) / (r2/(r1+r2));
   sumU1 = sumU1 + x - aU1;
   aU1 = sumU1/index;
   lcd.setCursor(0,0);
   lcd.print(a); */ 
}

void printV()
{
  lcd.setCursor(0,1);
   U1 = (readMedian(A0,20) * 5.0)/1024.0;
   U1 = U1 / (r2/(r1+r2));
   
   sumU1 = sumU1 + U1 - aU1;
   aU1 = sumU1/index;
   lcd.print(aU1);
   
   lcd.setCursor(7,1);
   
   U2 = (readMedian(A2,20) * 5.0)/1024.0;
   U2 = U2 / (r2/(r1+r2));
   sumU2 = sumU2 + U2 - aU2;
   aU2 = sumU2/index;
   lcd.print(aU2);
   
   lcd.setCursor(14,1);
   
   U3 = (readMedian(A4,20) * 5.0)/1024.0;
   U3 = U3 / (r2/(r1+r2));
   sumU3 = sumU3 + U3 - aU3;
   aU3 = sumU3/index;
   lcd.print(aU3);
}

void printA()
{
   I1 = analogRead(A1) * 0.0467 - 23.417;
   //I1 = analogRead(A1);
   sumI1 = sumI1 + I1 - aI1;
   aI1 = sumI1/index;
   if (aI1 >= maxA || !q1)
   {
      q1 = false;
      digitalWrite(9, HIGH);
      lcd.print("err");
   }
   else
   {
      lcd.print(aI1);
   }
   lcd.setCursor(7,3);
   
   I2 = analogRead(A3) * 0.0488 -24.413;
   sumI2 = sumI2 + I2 - aI2;
   aI2 = sumI2/index;
   if (aI2 >= maxA || !q2)
   {
      q2 = false;
      digitalWrite(10,HIGH);
      lcd.print("err");
   }
   else
   {
     lcd.print(aI2);
   }   
    lcd.setCursor(14,3);
    
   I3 = analogRead(A5) * 0.0424 - 21.417;
   sumI3 = sumI3 + I3 - aI3;
   aI3 = sumI3/index;
   if (aI3 >= maxA || !q3)
   {
      q3 = false;
      digitalWrite(8,HIGH);
      lcd.print("err");
   }
   else
   {
     lcd.print(aI3);
   }
}

int readMedian (int pin, int samples){
  // массив для хранения данных
  int raw[samples];
  // считываем вход и помещаем величину в ячейки массива
  for (int i = 0; i < samples; i++){
    raw[i] = analogRead(pin);
  }
  // сортируем массив по возрастанию значений в ячейках
  int temp = 0; // временная переменная

  for (int i = 0; i < samples; i++){
    for (int j = 0; j < samples - 1; j++){
      if (raw[j] > raw[j + 1]){
        temp = raw[j];
        raw[j] = raw[j + 1];
        raw[j + 1] = temp;
      }
    }
  }
  // возвращаем значение средней ячейки массива
  return raw[samples/2];
}
