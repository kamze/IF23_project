#ifndef GPSPlus_h
#define GPSPlus_h

#include "Arduino.h"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

/*
   This class sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial.
*/
class GPSPlus
{
  public:
    GPSPlus(uint32_t GPSBaud, byte RXPin, byte TXPin);
    bool update();
    float getlatitude();

    // The TinyGPS++ object
    TinyGPSPlus gps;
    private:
      uint32_t _GPSBaud;

      // The serial connection to the GPS device
      //RX=3; TX=2
      SoftwareSerial ss;
};

#endif
