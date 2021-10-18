#include<LiquidCrystal.h>
#include<IRremote.h>

LiquidCrystal lcd(6,7,8,9,10,11);
int IRpin = 12;
IRrecv IR(IRpin);
decode_results result;

int motor1for = 1;
int motor1back = 2;
int motor2for = 3;
int motor2back = 4;
int enable = 5;

void setup(){
  pinMode(motor1for,OUTPUT);
  pinMode(motor1back,OUTPUT);
  pinMode(motor2for,OUTPUT);
  pinMode(motor2back,OUTPUT);
  pinMode(enable,OUTPUT);
  
  lcd.begin(16,2);
  IR.enableIRIn();
  take_cmd();
  
}
void take_cmd(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("WAITING FOR");
  lcd.setCursor(4,1);
  lcd.print("COMMAND");
}
void loop(){
  if (IR.decode(&result)){
  if (result.value == 0xFD08F7){
    digitalWrite(enable, HIGH);
    digitalWrite(motor1for,HIGH);
    digitalWrite(motor1back,LOW);
    digitalWrite(motor2for, HIGH);
    digitalWrite(motor2back, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOVING FORWARD");
    IR.resume();
  }
  else if (result.value == 0xFD8877){
    digitalWrite(enable, HIGH);
    digitalWrite(motor1for,LOW);
    digitalWrite(motor1back,HIGH);
    digitalWrite(motor2for, LOW);
    digitalWrite(motor2back, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOVING BACKWARD");
    IR.resume();
  }
  else if (result.value == 0xFD48B7){
    digitalWrite(enable, HIGH);
    digitalWrite(motor1for,HIGH);
    digitalWrite(motor1back,LOW);
    digitalWrite(motor2for, LOW);
    digitalWrite(motor2back, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOVING RIGHT");
    IR.resume();
  }
  else if (result.value == 0xFD28D7){
    digitalWrite(enable, HIGH);
    digitalWrite(motor1for,LOW);
    digitalWrite(motor1back,LOW);
    digitalWrite(motor2for, HIGH);
    digitalWrite(motor2back, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOVING LEFT");
    IR.resume();
  }
   else if (result.value == 0xFD00FF){
     digitalWrite(enable, LOW);
     digitalWrite(motor1for,LOW);
     digitalWrite(motor1back,LOW);
     digitalWrite(motor2for, LOW);
     digitalWrite(motor2back, LOW);
     take_cmd();
     IR.resume();
   }
    else if (result.value == 0xFD30CF){
     digitalWrite(enable, LOW);
     digitalWrite(motor1for,LOW);
     digitalWrite(motor1back,LOW);
     digitalWrite(motor2for, LOW);
     digitalWrite(motor2back, LOW);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("STOPPED");
     IR.resume(); 
    }
    else if (result.value == 0xFDA857){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ACCELERATING");
      for (int i = 0;i < 256;i++){
        analogWrite(enable, i);
        digitalWrite(motor1for,HIGH);
        digitalWrite(motor1back,LOW);
        digitalWrite(motor2for, HIGH);
        digitalWrite(motor2back, LOW);
        delay(10);
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MAXIMUM SPEED");
      IR.resume();
    }
    else if (result.value == 0xFD6897){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DECCELERATING");
      for (int i = 255;i >= 0;i--){
        analogWrite(enable, i);
        digitalWrite(motor1for,HIGH);
        digitalWrite(motor1back,LOW);
        digitalWrite(motor2for, HIGH);
        digitalWrite(motor2back, LOW);
        delay(10);
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MINIMUM SPEED");
      IR.resume();
    }
  }
}
