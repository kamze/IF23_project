#include "Arduino.h"
#include "GPSPlus.h"
#include <SoftwareSerial.h>

GPSPlus::GPSPlus(uint32_t GPSBaud, byte RXPin, byte TXPin): ss(RXPin,TXPin),  _GPSBaud(GPSBaud)
{

}

bool GPSPlus::update()
{
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      }
  }
  return gps.date.isUpdated()|gps.location.isUpdated()|gps.time.isUpdated()|gps.altitude.isUpdated()|gps.satellites.isUpdated()|gps.hdop.isUpdated();
}

// acquire the voltage

float GPSPlus::getlatitude(){
  float volt_value=5.3;
  return volt_value;
}
