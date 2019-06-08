int son = 70; 
int volume;
#include <SPI.h>
#include <SD.h> // Include the SD library
#define SDPIN 10 // Chip Select SD drive
#include <TMRpcm.h> // .wav file management

File myFile;
TMRpcm tmrpcm;

void setup() {                
  Serial.begin(115200); 

  tmrpcm.speakerPin = 9; // Speaker on pin 9
  tmrpcm.setVolume(4); // volume management from 0 to 7
  tmrpcm.quality(1); // audio quality 0 or 1

  // Initialisation de la carte SD
  if (!SD.begin(SDPIN)) { 
    Serial.println("initialization failed!"); //  If there is a problem "initialization failed!" will be displayed on the monitor
    return;
  }
}

void loop() {
 
   volume = analogRead(A0); // Reads the value from the Analog PIN A0
   volume = map(volume, 200, 1000, 0, 120); // Re-calibrates the value between 200 and 1000 over a range between 0 and 120
   volume = constrain(volume, 0, 100); // limit the value of the volume variable between 0 and 100
   
   //Debug mode
   Serial.println(volume); // show the value on the serial plotter

   
  
 if(volume>=son)
 {
   tmrpcm.play("sound32.wav"); // Play sound "sound32.wav"
   delay(32500);
 }  
 

}
