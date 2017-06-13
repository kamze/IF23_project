#include <SD.h>

File file;  // test file
const uint8_t SD_CS = 10; // SD chip select
//------------------------------------------------------------------------------
// call back for file timestamps
void dateTime(uint16_t* date, uint16_t* time) {


  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(1994, 9, 21);

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(10, 36, 10);
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);


  // set date time callback function
  SdFile::dateTimeCallback(dateTime); 

  if (!SD.begin(SD_CS)) {
    Serial.println("SD.begin failed");
    while(1);
  }
  file = SD.open("TEST_SD.TXT", FILE_WRITE);
  file.close();
  Serial.println("Done");
}
//------------------------------------------------------------------------------
void loop() {}
