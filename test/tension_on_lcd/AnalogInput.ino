 #include <LiquidCrystal.h>

 LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;
float volt_value =0;// variable to store the value coming from the sensor

void setup() {
  lcd.begin(8, 2);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  volt_value = map(sensorValue, 0, 1023, 0,7);
   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
   lcd.print("tension");
  lcd.setCursor(0,1);
    lcd.print(volt_value);

    Serial.print("tension");
    Serial.println(volt_value);
  delay(1000);

}
