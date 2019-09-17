#include "ultrasonic.h"
#include "smoothing.h"
#include "servo.h"
#include "button.h"

UltraSonic *ultra1 = new UltraSonic(40, 38);
Smoothing *ultra1Smooth = new Smoothing();
int ultra1Thresh = 5;

UltraSonic *ultra2 = new UltraSonic(4, 5);
Smoothing *ultra2Smooth = new Smoothing();
int ultra2Thresh = 5;

Button* button = new Button(36);

int servo1StartPos = 0;
ServoControl* servo1 = new ServoControl(10, servo1StartPos);

int servo2StartPos = 0;
ServoControl* servo2 = new ServoControl(3, servo2StartPos);

int servo3StartPos = 45;
ServoControl* servo3 = new ServoControl(7, servo3StartPos);

int servo4StartPos = 0;
ServoControl* servo4 = new ServoControl(9, servo4StartPos);

enum Steps{
  step1,
  step2,
  step3,
  step4
};
Steps currentStep = step1;

void setup() {

}

void loop() {

  switch(currentStep){
    case step1:
      servo1->moveToSlowly(90);
      currentStep = step2;
      break;
      
    case step2:
      if(ultra1Smooth->output(ultra1->centimeters()) < ultra1Thresh){
        servo2->moveToSlowly(180);
        currentStep = step3;
      }
      break;
      
    case step3:
      if(ultra2Smooth->output(ultra2->centimeters()) < ultra2Thresh){
        servo3->moveToSlowly(75);
        currentStep = step4;
      }
      break;
      
    case step4:
      if(button->Pressed()){
        servo4->moveToSlowly(90);
        return 0;
      }
      break;
      
  }
}
