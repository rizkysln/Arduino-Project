//install library CTBot dlu

#include "CTBot.h"
CTBot myBot;

String ssid = "SMART_HOME"; //ganti jadi nama wifi kelen     
String pass = "merahtua"; //ganti jadi password wifi kelen
String token = "5841058236:AAE6a5wsLpE-w5MJwV9Pcv8RE3UfkDlog8M"; //ganti pake auth token bot telegram kelen   
uint8_t redLed = D1;               
uint8_t greenLed = D2;                       
                                    

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Sebentar...");
  delay(2000);
  Serial.println("Menghubungkan ke Telegram...");
  Serial.println("Bot = @KySmartHomeBot");
  Serial.println("Jangan lupa follow IG: @rizkysln_");

  myBot.wifiConnect(ssid, pass);

  myBot.setTelegramToken(token);

  if (myBot.testConnection())
    Serial.println("\ntestConnection Terhubung");
  else
    Serial.println("\ntestConnection Tidak Terhubung");

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(redLed, LOW); 
  digitalWrite(greenLed, LOW);

}

void loop() {
  TBMessage msg;

  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("/command1")) {              
      digitalWrite(redLed, HIGH);                               
      myBot.sendMessage(msg.sender.id, "Lampu Pertama Hidup Sekarang");  
    }
    else if (msg.text.equalsIgnoreCase("/command2")) {        
      digitalWrite(redLed, LOW);                              
      myBot.sendMessage(msg.sender.id, "Lampu Pertama Mati Sekarang"); 
    }
    else if (msg.text.equalsIgnoreCase("/command3")) {              
      digitalWrite(greenLed, HIGH);                               
      myBot.sendMessage(msg.sender.id, "Lampu Kedua Hidup Sekarang");  
    }
    else if (msg.text.equalsIgnoreCase("/command4")) {         
      digitalWrite(greenLed, LOW);                              
      myBot.sendMessage(msg.sender.id, "Lampu Kedua Mati Sekarang"); 
    }
    else {                                                    
      
      String reply;
      reply = (String)"Selamat Datang " + msg.sender.username + (String)". Coba Hidupkan Lampu atau Matikan Lampu dengan klik menu di sudut kiri atas keyboard.";
      myBot.sendMessage(msg.sender.id, reply);             
    }
  }
  
  delay(50);
}

