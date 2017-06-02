#ifndef InputManager_h
#define InputManager_h

#include <Bounce2.h>
#include "Arduino.h"

class InputManager
{
  public:
    InputManager(int BP1, int BP0, int BPEN, int tensionPin);
    int pressedButton();
    float gettension();
    //signals for pushbuttons
    Bounce debouncer_BP1 ;
    Bounce debouncer_BP0 ;
    Bounce debouncer_BPEN ;
    private:
    int _BP1;
    int _BP0;
    int _BPEN;
    int _tensionPin;    // select the input pin for the potentiometer
};

#endif
