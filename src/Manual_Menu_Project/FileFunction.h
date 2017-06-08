
void WriteLine2File( String fileName, String line) {
 File myFile = SD.open(fileName, FILE_WRITE);

  if (myFile) {
     myFile.println(line);
       myFile.close();


   } else {
     Serial.println(F("error opening file in write"));
   }
 }

void overWriteLine2File( String fileName, String line) {
  File myFile = SD.open(fileName, O_WRITE | O_CREAT | O_TRUNC);

  if (myFile) {
     myFile.println(line);
       myFile.close();


   } else {
     Serial.println(F("error opening file in overw"));
   }
 }

void readFunction(String fileName) {
 File myFile = SD.open(fileName);

    if (myFile) {


      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println(F("error opening the file in read"));
    }
}
