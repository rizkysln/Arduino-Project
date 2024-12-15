#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial mySerial(2, 3); // RX, TX
SoftwareSerial ky (10,11);

void setup () {
  Serial.begin(9600);
	mySerial.begin (9600);
  ky.begin(9600);
	mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
	delay(1);  //wait 1ms for mp3 module to set volume
	mp3_set_volume (30);
}


//
void loop () {       
  if (ky.available())
{
  char data= ky.read();
  Serial.println(data);
  if (data=='A'){
	mp3_play (1);
	delay (3000);}
  if (data=='B'){
  mp3_play (2);
  delay (3000);}
  if (data=='C'){
  mp3_play (3);
  delay (3000);}
  if (data=='D'){
  mp3_play (2);
  delay (3000);}
  if (data=='E'){
  mp3_play (4);
  delay (3000);}
  if (data=='F'){
  mp3_play (5);
  delay (3000);}
  if (data=='G'){
  mp3_play (6);
  delay (3000);}
  if (data=='H'){
  mp3_play (7);
  delay (3000);}
  if (data=='I'){
  mp3_play (8);
  delay (3000);}
  if (data=='J'){
  mp3_play (9);
  delay (3000);}
  if (data=='K'){
  mp3_play (10);
  delay (3000);}
  if (data=='L'){
  mp3_play (11);
  delay (3000);}
  if (data=='Q'){
  mp3_play (12);
  delay (3000);}
  if (data=='R'){
  mp3_play (13);
  delay (3000);}
  if (data=='S'){
  mp3_play (14);
  delay (3000);}
  if (data=='T'){
  mp3_play (15);
  delay (3000);}
  if (data=='U'){
  mp3_play (16);
  delay (3000);}
  if (data=='V'){
  mp3_play (17);
  delay (3000);}
  if (data=='W'){
  mp3_play (18);
  delay (3000);}
  if (data=='X'){
  mp3_play (19);
  delay (3000);}
}
}
