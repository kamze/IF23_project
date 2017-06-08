
String makeGPSSentence( ){
  // to acquire the message
  // making the customed sentence:
  // GPSMesssage=YearMonthDay,DateAge,HourMinutesSecondes,TimeAge,Satellites,AgeSat,Longitude,Latitude,AgeLocation,Altitude,AgeAltitude,HDOP,AgeHDOP,SentencesWithFix,FailedChecksum,PassedChecksum\n

  String GPSMesssage="";

  //---------------DATE---------------------

  /*  Serial.print(F("date value :"));
  Serial.println(gps.date.value());
  Serial.print(F("time value :"));
  Serial.println(gps.time.value());


  Serial.print(gps.date.year());
  Serial.print(F(","));
  Serial.print(gps.date.month());
  Serial.print(F(","));
  Serial.print(gps.date.day());
  Serial.print(F(","));
  Serial.print(gps.date.age());
  Serial.print(F(","));

  Serial.print(gps.time.hour());
  Serial.print(F(","));
  Serial.print(gps.time.minute());
  Serial.print(F(","));
  Serial.print(gps.time.second());
  Serial.print(F(","));
  Serial.print(gps.time.age());
  Serial.print(F(","));

  Serial.print(gps.satellites.value());
  Serial.print(F(","));
  Serial.print(gps.satellites.age());
  Serial.print(F(","));

  Serial.print(gps.location.lng(), 6);
  Serial.print(F(","));
  Serial.print(gps.location.lat(), 6);
  Serial.print(F(","));
  Serial.print(gps.location.age());
  Serial.print(F(","));

  Serial.print(gps.altitude.kilometers());
  Serial.print(F(","));
  Serial.print(gps.altitude.age());
  Serial.print(F(","));

  Serial.print(gps.hdop.value());
  Serial.print(F(","));
  Serial.print(gps.hdop.age());
  Serial.print(F(","));

  Serial.print(gps.sentencesWithFix());
  Serial.print(F(","));
  Serial.print(gps.failedChecksum());
  Serial.print(F(","));
  Serial.println(gps.passedChecksum());
  Serial.println();*/

  GPSMesssage+=gps.date.year();
  GPSMesssage+=",";
  GPSMesssage+=gps.date.month();
  GPSMesssage+=",";
  GPSMesssage+=gps.date.day();
  GPSMesssage+=",";

  GPSMesssage+=gps.date.age();
  GPSMesssage+=",";
  GPSMesssage+=gps.time.hour();
  GPSMesssage+=",";
  GPSMesssage+=gps.time.minute();
  GPSMesssage+=",";
  GPSMesssage+=gps.time.second();
  GPSMesssage+=",";
  GPSMesssage+=gps.time.age();
  GPSMesssage+=",";

  GPSMesssage+=gps.satellites.value();
  GPSMesssage+=",";
  GPSMesssage+=gps.satellites.age();
  GPSMesssage+=",";

  GPSMesssage+=String(gps.location.lng(), 6);
  GPSMesssage+=",";
  GPSMesssage+=String(gps.location.lat(), 6);
  GPSMesssage+=",";
  GPSMesssage+=gps.location.age();
  GPSMesssage+=",";

  GPSMesssage+=String(gps.altitude.meters(), 2);
  GPSMesssage+=",";
  GPSMesssage+=gps.altitude.age();
  GPSMesssage+=",";

  GPSMesssage+=gps.hdop.value();
  GPSMesssage+=",";
  GPSMesssage+=gps.hdop.age();
  GPSMesssage+=",";

  GPSMesssage+=gps.sentencesWithFix();
  GPSMesssage+=",";
  GPSMesssage+=gps.failedChecksum();
  GPSMesssage+=",";
  GPSMesssage+=gps.passedChecksum();
  
/*Serial.println(GPSMesssage);
  Serial.println(F("------------------------"));*/
  return GPSMesssage;
}
