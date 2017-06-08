
/**
 * This is the structure of the modelled menu
 *
 *      Batterie ok ? if used return 1 " L1: Batterie; L2 e %"
 *      Court: ok?
 *      Moyen ok?
 *      Tour3 ok ? we write gps data in it
 *      Compagne ok ? we write gps data in it
 *      Batiment ok ? we write gps data in it
 *      Coord ok? "L1: latitude;L2 longitude"
 *      Time ok? "L1:date  ; L2:time"
 *      Status ok? "L1: sat nomber;L2 Hdop"
 *      Tour3 ok ? serial print Tour3
 *      Compagne ok ? serial print Compagne
 *      Batiment ok ? serial print Batiment
 */

 void DisplayText(String line1,String line2){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(line1);
   lcd.setCursor(0, 1);
   lcd.print(line2);
 }
 // Display somthing on line 1 and 2 of the lcd screen
 void DisplayValues(float value1,float value2, byte precision=3){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(value1,precision);
   lcd.setCursor(0, 1);
   lcd.print(value2,precision);
 }
 // displaying something with line & text on a specific lcd line
 void DisplayTextfloat(String text,float value, byte precision=3, byte line=0){
   text+=String(value,precision);
   lcd.clear();
   lcd.setCursor(0, line);
   lcd.print(text);
 }

 void DisplayTextint(String text1,String text2,unsigned long int value1,unsigned long int value2){

   text1+=String(value1);
   text2+=String(value2);

   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(text1);
   lcd.setCursor(0, 1);
   lcd.print(text2);
 }

 void MainMenuDisplay()
 {
     lcd.clear();
     lcd.setCursor(0,0);
     switch (mainMenuPage)
     {
         case UBattery:
           DisplayText("Battery","");
           break;

         case UonOff:
           DisplayText("ON-OFF","");
           break;

         case UCourt:
           DisplayText("Sampling","Court");
           break;

         case UMoyen:
         DisplayText("Sampling","Moyen");
           break;

         case UTour3:
           DisplayText("Itenrair","Tour3");
           break;

         case UCompagne:
         DisplayText("Itenrair","Compagne");
           break;

         case UBatiment:
         DisplayText("Itenrair","Batiment");
           break;

         case UCoord:
           DisplayText("Afficher","Coord");
           break;

         case UTime:
           DisplayText("Afficher","Time");
           break;

         case UStatus:
           DisplayText("Afficher","Status");
           break;

         case UAltitude:
           DisplayText("Afficher","Altitude");
           break;

         case USendTour3:
           DisplayText("Send:","Tour3");
           break;

         case USendCompagne:
           DisplayText("Send:","Compagne");
           break;

         case USendBatiment:
           DisplayText("Send:","Batiment");
           break;
     }

 }

 void MainMenuBtn()
 {
   // right
     if(btn_push == 'R')
     {
         mainMenuPage++;
         if(mainMenuPage > mainMenuTotal)
           mainMenuPage = 1;
     }
     // left
     else if(btn_push == 'L')
     {
         mainMenuPage--;
         if(mainMenuPage == 0)
           mainMenuPage = mainMenuTotal;
     }

     if(mainMenuPage != mainMenuPageOld) //only update display when page change
     {
         MainMenuDisplay();
         mainMenuPageOld = mainMenuPage;
     }
 }

 char ReadKeypad()
 {
   byte keypad_value = BP_mnger.pressedButton();
   if(keypad_value == 1)
    return 'S'; // Select
   else if(keypad_value==2)
    return 'L'; // left
   else if(keypad_value==3)
     return 'R'; // right
   else if(keypad_value==4)
     return 'A'; // shortcut to activate GPS
   else
     return 'N';

 }

 void dealWithUsedEvents()
 {
   if(btn_push == 'S')//enter selected menu
   {
     switch (mainMenuPage) {
       case UBattery:
         DisplayTextfloat("Bat:",BP_mnger.gettension(),1,0);
         break;

       case UonOff:
         isStarted=!isStarted;
         if(isStarted)DisplayText("GPS","Started");
         else {DisplayText("GPS","Stoped");}
         break;

       case UCourt:
         DisplayText("Court","choisi");
         GPSSearchPeriod=2000;
         break;

       case UMoyen:
         DisplayText("Moyen","choisi");
         GPSSearchPeriod=15000;
         break;

       case UTour3:
         DisplayText("Tour3","choisi");
         FileName="IF232017/tour3.txt";
         fileIsChanged=true;
         break;

       case UCompagne:
       DisplayText("Compagne","choisi");
       FileName="IF232017/Compagne.txt";
       fileIsChanged=true;
         break;

       case UBatiment:
       DisplayText("Batiment","choisi");
       FileName="IF232017/Batiment.txt";
       fileIsChanged=true;
        break;

       case UCoord:
         DisplayValues(gps.location.lat(),gps.location.lng(),7 );
         break;

       case UTime:

       DisplayTextint("D:","T:",gps.date.value(),gps.time.value());
         break;

       case UStatus:
       DisplayTextint("Sat:","HDOP",gps.satellites.value(),gps.hdop.value());
         break;

       case UAltitude:
         DisplayTextfloat("A:",gps.altitude.meters(),6,0);
         break;

       case USendTour3:
         readFunction("IF232017/tour3.txt");
         DisplayText("Tour3 ","is sent");
         break;

       case USendCompagne:
         readFunction("IF232017/Compagne.txt");
         DisplayText("Compagne","is sent");
         break;

       case USendBatiment:
         readFunction("IF232017/Batiment.txt");
         DisplayText("Batiment","is sent");
         break;

       }

   }}
