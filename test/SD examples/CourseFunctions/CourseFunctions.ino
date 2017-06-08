
#include <SPI.h>
#include <SD.h>

void WriteLine2File( File myFile);
void readFunction(String fileName);

bool isStarted=true;
String line ="test 1 1 1 ";
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  Serial.println("Creating example.txt...");

//-----------------Write File -----------------
//  myFile = SD.open("IF232017/tour3.txt", FILE_WRITE);

  // if the file opened okay, write to it:
overWriteLine2File("Compagne.txt","1)");
readFunction("Compagne.txt");

WriteLine2File("Compagne.txt","2)");
WriteLine2File("Compagne.txt","3)");

readFunction("Compagne.txt");

//-------------------Read File------------------
}

void loop() {
  // nothing happens after setup
}


void WriteLine2File( String fileName, String line) {
 File myFile = SD.open("Compagne.txt", FILE_WRITE);

  if (myFile) {
     myFile.println(line);
       myFile.close();


   } else {
     Serial.println("error opening test.txt");
   }
 }

void overWriteLine2File( String fileName, String line) {
  File myFile = SD.open("Compagne.txt", O_WRITE | O_CREAT | O_TRUNC);

  if (myFile) {
     myFile.println(line);
       myFile.close();


   } else {
     Serial.println("error opening test.txt");
   }
 }
void readFunction(String fileName) {
  //  myFile = SD.open("IF232017/tour3.txt
 File myFile = SD.open(fileName);

    if (myFile) {
      Serial.print(fileName);
      Serial.println(": ");

      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
}
