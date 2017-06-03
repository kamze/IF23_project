

void makeGPSSentence(TinyGPSPlus gps){
  // to acquire the message
  // making the customed sentence:
  // GPSMesssage=YearMonthDay,DateAge,HourMinutesSecondes,TimeAge,Satellites,AgeSat,Longitude,Latitude,AgeLocation,Altitude,AgeAltitude,HDOP,AgeHDOP,SentencesWithFix,FailedChecksum,PassedChecksum\n

  String GPSMesssage="";

  //---------------DATE---------------------

  Serial.print(gps.date.year());
  Serial.print(F(","));

  GPSMesssage+=gps.date.year();
  GPSMesssage+=",";

  Serial.print(gps.date.month());
  Serial.print(F(","));

  GPSMesssage+=gps.date.month();
  GPSMesssage+=",";

  Serial.print(gps.date.day());
  Serial.print(F(","));

  GPSMesssage+=gps.date.day();
  GPSMesssage+=",";

  Serial.print(gps.date.age());
  Serial.print(F(","));

  GPSMesssage+=gps.date.age();
  GPSMesssage+=",";

  //---------------TIME---------------------

  Serial.print(gps.time.hour());
  Serial.print(F(","));

  GPSMesssage+=gps.time.hour();
  GPSMesssage+=",";

  Serial.print(gps.time.minute());
  Serial.print(F(","));

  GPSMesssage+=gps.time.minute();
  GPSMesssage+=",";

  Serial.print(gps.time.second());
  Serial.print(F(","));

  GPSMesssage+=gps.time.second();
  GPSMesssage+=",";

  Serial.print(gps.time.age());
  Serial.print(F(","));

  GPSMesssage+=gps.time.age();
  GPSMesssage+=",";

  //---------------Satellites---------------------
  Serial.print(gps.satellites.value());
  Serial.print(F(","));

  GPSMesssage+=gps.satellites.value();
  GPSMesssage+=",";

  Serial.print(gps.satellites.age());
  Serial.print(F(","));

  GPSMesssage+=gps.satellites.age();
  GPSMesssage+=",";

  //---------------Location---------------------

  Serial.print(gps.location.lng(), 6);
  Serial.print(F(","));

  GPSMesssage+=String(gps.location.lng(), 6);
  GPSMesssage+=",";

  Serial.print(gps.location.lat(), 6);
  Serial.print(F(","));

  GPSMesssage+=String(gps.location.lat(), 6);
  GPSMesssage+=",";

  Serial.print(gps.location.age());
  Serial.print(F(","));

  GPSMesssage+=gps.location.age();
  GPSMesssage+=",";

  //---------------Altitude---------------------

  Serial.print(gps.altitude.kilometers());
  Serial.print(F(","));

  GPSMesssage+=String(gps.altitude.kilometers(), 6);
  GPSMesssage+=",";

  Serial.print(gps.altitude.age());
  Serial.print(F(","));

  GPSMesssage+=gps.altitude.age();
  GPSMesssage+=",";

  //---------------HDOP---------------------

  Serial.print(gps.hdop.value());
  Serial.print(F(","));

  GPSMesssage+=gps.hdop.value();
  GPSMesssage+=",";

  Serial.print(gps.hdop.age());
  Serial.print(F(","));

  GPSMesssage+=gps.hdop.age();
  GPSMesssage+=",";

  //---------------Stat---------------------

  Serial.print(gps.sentencesWithFix());
  Serial.print(F(","));

  GPSMesssage+=gps.sentencesWithFix();
  GPSMesssage+=",";

  Serial.print(gps.failedChecksum());
  Serial.print(F(","));

  GPSMesssage+=gps.failedChecksum();
  GPSMesssage+=",";

  Serial.println(gps.passedChecksum());
  GPSMesssage+=gps.passedChecksum();

  Serial.println(GPSMesssage);
  Serial.println(F("------------------------"));

}
