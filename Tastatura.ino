#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

const byte ROWS = 4;
const byte COLS = 3;

const String password = "1234"; // sifra
String input_password; 

int buzzer = 12;
 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {8, 7, 6};
 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 20, 4);  

void refres_posle_sifre(){
   lcd.clear();
   lcd.setCursor(0, 1);
}

void refres_pocetni(){
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Unesite sifru:");
}

void buzz_error(){
  unsigned char i;
  
  for(i = 0; i < 40; i++){
      digitalWrite(buzzer, HIGH);
      delay(10); // dilej 10 ms
      digitalWrite(buzzer, LOW);
      delay(1); // dilej 1 ms
    }
}

void buzz_good(){
  unsigned char i;
      
  for(i = 0; i < 100; i++){
      digitalWrite(buzzer, HIGH);
      delay(1); // dilej 1 ms
      digitalWrite(buzzer, LOW);
      delay(1); // dilej 1 ms
    }  
}
 
void setup(){
  Serial.begin(9600);
  
  lcd.backlight();
  lcd.init(); 
  
  refres_pocetni();

  pinMode(buzzer,OUTPUT);
}
  
void loop(){
  
  char key = customKeypad.getKey();
 
  if (key){
    //Serial.println(key);
    
    if(key == '*') {
      input_password = ""; // resetovanje varijable za unos sifre
      refres_pocetni(); 
    } 
    else if(key == '#') {
      if(password == input_password) {
        //Serial.println("Sifra je tacna");
        refres_posle_sifre();
        lcd.print("Dobrodosli!");
        buzz_good();
        delay(2000);
        refres_pocetni();
        
      } 
      else {
        //Serial.println("Sifra nije tacna, pokusajte ponovo");
        refres_posle_sifre(); 
        lcd.print("Pogresna sifra!");
        buzz_error();
        delay(2000);
        refres_pocetni();
      }
      input_password = ""; // resetovanje varijable za unos sifre
    } 
    else {
      input_password += key; // dodavanje unetih karaktera i formiranje sifre
      lcd.setCursor(0, 1); 
      lcd.print(input_password);
    }
  }
}
