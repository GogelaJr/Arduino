#include <LiquidCrystal.h> 
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


 
#define SS_PIN 53
#define RST_PIN 22
#define LEDGREEN 24
#define LEDRED 25



int angle = 0;
int Contrast=100;
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo;  

 void setup()
 {  
    pinMode(LEDGREEN, OUTPUT);
    pinMode(LEDRED, OUTPUT);
    servo.attach(23);
    servo.write(angle);
    Serial.begin(9600);   
    SPI.begin();      
    mfrc522.PCD_Init();   
    Serial.println("Approximate your card to the reader...");
    Serial.println();
    analogWrite(6,Contrast);
    lcd.begin(16, 2);
  } 
     void loop()
 { 
  

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BA F4 1A 86")
  {
    Serial.println("Authorized access");
    Serial.println();   
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");  
    lcd.setCursor(4, 0);
    digitalWrite(LEDGREEN, HIGH);
    lcd.print("Welcome");
    lcd.setCursor(5, 1);
    lcd.print("Ilia");
    servo.write(90);
    delay(3000);
    digitalWrite(LEDGREEN, LOW);
    servo.write(0);
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(2, 0);
    lcd.print("Put your card");
    lcd.setCursor(2, 1);
    lcd.print("on the Reader");
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(LEDRED, HIGH);
    servo.write(0);
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(5, 0);
    lcd.print("Access");
    lcd.setCursor(5, 1);
    lcd.print("Denied!");    
    delay(3000);
    digitalWrite(LEDRED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    lcd.setCursor(2, 0);
    lcd.print("Put your card");
    lcd.setCursor(2, 1);
    lcd.print("on the Reader");
    delay(2000);
  }
 
 }
