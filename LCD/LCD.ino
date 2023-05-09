#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   22     
#define SS_PIN    53    

MFRC522 mfrc522(SS_PIN, RST_PIN);



MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);  
  while (!Serial);     
  SPI.begin();         
  mfrc522.PCD_Init();  
  Serial.println(F("Warning: this example overwrites the UID, use with CAUTION!"));
  
}


void loop() {
  
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } 
  Serial.println();

  Serial.println(F("New UID and contents:"));
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  delay(2000);
}
