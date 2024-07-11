
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#include <time.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();
SoftwareSerial bluetooth(2, 3);

#define PINO_SS 10
#define PINO_RST 9
#define LED_PIN  8
int segs = 0;
int mins = 0;
int hrs = 0;
unsigned long atual;
unsigned long ini;
int incomingByte;
String hora;
String horario;
String minutos;
String segundos;

MFRC522 mfrc522(PINO_SS, PINO_RST);

void setup()
{
  bluetooth.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  SPI.begin();
  mfrc522.PCD_Init();

  display.clearDisplay();
  display.setCursor(10, 10);
  display.print("SISTEMA");
  display.display();

  display.setCursor(10, 20);
  display.print("DE PONTO");
  display.display();
  delay(3000);

  hrs = 21;
  mins = 04;
  segs = 00;
}

void loop()
{
  atual = millis();
  if ((atual - ini) > 1000){
    ini = ini +1000;

    segs +=1;
    if (segs > 59){
      mins +=1;
      segs = 0;
    }
    if (mins > 59){
      hrs += 1;
      mins = 0;
    }
    if (hrs > 23){
      hrs = 0;
    }
  }

  display.clearDisplay();
  display.setCursor(10, 10);
  display.print("APROXIME O CRACHA");
  display.display();
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String conteudo= "";

  byte letra;

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     if(mfrc522.uid.uidByte[i] < 0x10){
        Serial.print(" 0");
     }
     else{
        Serial.print(" ");
     }
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     Serial.print("   ");

     if(mfrc522.uid.uidByte[i] < 0x10){
        conteudo.concat(String(" 0"));
     }
     else{
        conteudo.concat(String(" "));
     }
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  conteudo.toUpperCase();
  if (conteudo.substring(1) == "E3 BB DC 0F")
  {
      display.clearDisplay();
      display.setCursor(10, 10);
      display.print("Ponto Batido");
      display.display();

      horario = String(hrs);
      minutos = String(mins);
      segundos = String(segs);

      if(hrs < 10) {
        horario = "0" + horario;
      }
      if(mins < 10) {
        minutos = "0" + minutos;
      }
      if(segs < 10) {
        segundos = "0" + segundos;
      }

      hora = String(horario) + ":" + String(minutos) + ":" + String(segundos);

      bluetooth.println();
      bluetooth.print(hora);
      bluetooth.print(" ");
      bluetooth.print("Jennifer Torchelsen");

      digitalWrite(LED_PIN,HIGH);
      delay(2000);
      digitalWrite(LED_PIN,LOW);
      display.clearDisplay();
  }
  delay(100);

  if (conteudo.substring(1) == "53 01 AE 0F")
  {
      display.clearDisplay();
      display.setCursor(10, 10);
      display.print("Ponto Batido");
      display.display();

      horario = String(hrs);
      minutos = String(mins);
      segundos = String(segs);

      if(hrs < 10) {
        horario = "0" + horario;
      }
      if(mins < 10) {
        minutos = "0" + minutos;
      }
      if(segs < 10) {
        segundos = "0" + segundos;
      }

      hora = String(horario) + ":" + String(minutos) + ":" + String(segundos);

      bluetooth.println();
      bluetooth.print(hora);
      bluetooth.print(" ");
      bluetooth.print("Cristoffer Laner");

      digitalWrite(LED_PIN,HIGH);
      delay(2000);
      digitalWrite(LED_PIN,LOW);
      display.clearDisplay();
  }

  delay(100);

  if (conteudo.substring(1) == "A3 72 AF 0D")
  {
      display.clearDisplay();
      display.setCursor(10, 10);
      display.print("Ponto Batido");
      display.display();
      horario = String(hrs);
      minutos = String(mins);
      segundos = String(segs);

      if(hrs < 10) {
        horario = "0" + horario;
      }
      if(mins < 10) {
        minutos = "0" + minutos;
      }
      if(segs < 10) {
        segundos = "0" + segundos;
      }

      hora = String(horario) + ":" + String(minutos) + ":" + String(segundos);

      bluetooth.println();
      bluetooth.print(hora);
      bluetooth.print(" ");
      bluetooth.print("Samuel Fischer");

      digitalWrite(LED_PIN,HIGH);
      delay(2000);
      digitalWrite(LED_PIN,LOW);
      display.clearDisplay();
  }
  delay(100);
}
