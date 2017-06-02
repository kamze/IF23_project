#include <Bounce2.h>
#include "InputManager.h"


InputManager BP_mnger(15,16,17,A0);
void setup() {
  Serial.begin(9600);
}

void loop() {
  int pressedBp;
  pressedBp=BP_mnger.pressedButton();
if (pressedBp!=0 && pressedBp!=1) {
  Serial.print("pressedBp: ");
  Serial.println(pressedBp);
}

  if (pressedBp==1) {
    Serial.print("tension: ");
    Serial.println(BP_mnger.gettension());

   }

}
