#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>           // Inclure la librairie SD
#include <TMRpcm.h>       // Gestion de fichier .wav

SoftwareSerial mySerial(7,8);

#define SDPIN 10          // Chip Select du lecteur SD

File myFile;
TMRpcm tmrpcm;

int Bp = 3;
int RPWM_Output = 5;
int LPWM_Output = 6;
int son = 80; 
int vol;
int memoire = 0; // La mémoire de l'état du volume
int i = 0;
int moteur = 0;
int notif;

unsigned long dateDernierChangement = 0;
unsigned long intervalle = 32000;
unsigned long dateCourante;

void setup() 
{
  
//Berceuse
  tmrpcm.speakerPin = 9;   // Speaker sur la pin 9
  tmrpcm.setVolume(4);     // gestion du volume de 0 à 7
  tmrpcm.quality(1);       // qualitée audio 0 ou 1

//App bluetooth
  mySerial.begin(9600);  

//Moteur
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
   
}


void loop() 
{

//detection pleur
  vol = analogRead(A0);                  // Reads the value from the Analog PIN A0
   
  vol = map(vol, 200, 1000, 0, 100);  // Ré-étalonne la valeur entre 200 et 1000 sur une fourchette entre 0 et 100

  vol = constrain(vol, 0, 100);       // limite la valeur de la variable volume entre 0 et 100
   
  dateCourante = millis();
  intervalle = dateCourante - dateDernierChangement;
   
  if(vol>=son && intervalle >32000)
   {
     tmrpcm.play("sound32.wav");             // Joue le son "sound32.wav"
     dateDernierChangement = dateCourante;
     i++;
   }
   
  if(i == 2)
   {
     notif = 1;
     i = 0;
   }
  
//App bluetooth
  mySerial.println(notif);
  mySerial.print(vol);   
  mySerial.print(",");
  delay(1000);
    
//Commande moteur
  int sensorValue = (analogRead(A1))/4;
 
  if((digitalRead(Bp) ==1 && sensorValue <= 80) || (intervalle < 32000))
   {
     analogWrite(LPWM_Output, 0);
     analogWrite(RPWM_Output, sensorValue);
     delay(2000);
     analogWrite(LPWM_Output, sensorValue);
     analogWrite(RPWM_Output, 0);
     delay(2000);
   }
  else if((digitalRead(Bp) ==1 && sensorValue >80 && sensorValue <=255) || (intervalle < 32000))
        {
          analogWrite(LPWM_Output, 0);
          analogWrite(RPWM_Output, sensorValue);
          delay(1000);
          analogWrite(LPWM_Output, sensorValue);
          analogWrite(RPWM_Output, 0);
          delay(1000);
        }
       
  analogWrite(LPWM_Output, 0);
  analogWrite(RPWM_Output, 0);
   
}

