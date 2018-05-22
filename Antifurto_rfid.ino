#include <SPI.h>
#include <MFRC522.h>


//SDA ===> Pin10
//SCK ===> Pin13
//MOSI ===> Pin11
//MISO ===> Pin12
//RST ===> Pin9
//3.3v ===> 3.3v
//GND ===> GND
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String password = "15 3A 97 03";

int pinoLiberado = 8;

String logp;
void logWrite(String st){
  if(logp == st){return;}
  Serial.println(st);
  logp = st;
}
 
void setup(){
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  pinMode(pinoLiberado, OUTPUT);
  logWrite("Informe o UID via leitor RFID.");
}

int tentativa = 0;
void loop(){
  if(tentativa >= 2){
    logWrite("Card não esta presente ou impossível ler.");
    digitalWrite(pinoLiberado, LOW);
  }
  
  if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
    //logWrite("Card presente e lido");
    tentativa = 0;
    
    String uid = "";
    byte letra;
    
    for(byte i = 0; i < mfrc522.uid.size; i++){
       uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    uid.toUpperCase();
    uid = uid.substring(1);
  
    if(uid == password){
      logWrite("Acesso Liberado");
      digitalWrite(pinoLiberado, HIGH);
    }else{
      logWrite("UID "+uid+" é incorreto.");
    }
  }else{
    tentativa ++;
    return; 
  }




  
}
