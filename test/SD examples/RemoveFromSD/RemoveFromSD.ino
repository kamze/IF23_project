/*
  SD card basic file example

 This example shows how to create and destroy an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  if (SD.exists("201438.GP")) {
    Serial.println("CAMPAGNE.TXT exists.");
     Serial.println("Removing CAMPAGNE.TXT...");
      SD.remove("201438.GP");
      SD.remove("171334.GP");
      SD.remove("13410.GP");
      SD.remove("132411.GP");
      SD.remove("TEST.TXT");

      SD.rmdir("ANDROID");
     SD.mkdir("SYSTEM~1");
     
  } else {
    Serial.println("CAMPAGNE.TXT doesn't exist.");
  }

  // Check to see if the file exists:
  if (SD.exists("CAMPAGNE.TXT")) {
    Serial.println("CAMPAGNE.TXT exists.");
  } else {
    Serial.println("CAMPAGNE.TXT doesn't exist.");
  }

}

void loop() {
  // nothing happens after setup finishes.
}



