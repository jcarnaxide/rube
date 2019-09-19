#include "ultrasonic.h"
#include "smoothing.h"
#include "servo.h"
#include "button.h"

int Ultra1Echo = 40;
int Ultra1Trigger = 38;
UltraSonic *ultra1;
Smoothing *ultra1Smooth;
int ultra1Thresh = 2;

int Ultra2Echo = 4;
int Ultra2Trigger = 5;
UltraSonic *ultra2;
Smoothing *ultra2Smooth;
int ultra2Thresh = 4;

int buttonPin = 36;
Button *button;

int servo1Pin = 10;
int servo1StartPos = 130;
ServoControl *servo1;

int servo2Pin = 3;
int servo2StartPos = 100;
ServoControl *servo2;

int servo3Pin = 7;
int servo3StartPos = 45;
ServoControl *servo3;

int servo4Pin = 9;
int servo4StartPos = 10;
ServoControl *servo4;

enum Steps{
  step1,
  step2,
  step3,
  step4
};
Steps currentStep = step1;

void setup() {
  ultra1 = new UltraSonic(Ultra1Echo, Ultra1Trigger);
  ultra1Smooth = new Smoothing();

  ultra2 = new UltraSonic(Ultra2Echo, Ultra2Trigger);
  ultra2Smooth = new Smoothing();

  button = new Button(buttonPin);

  servo1 = new ServoControl(servo1Pin, servo1StartPos);

  servo2 = new ServoControl(servo2Pin, servo2StartPos);

  servo3 = new ServoControl(servo3Pin, servo3StartPos);

  servo4 = new ServoControl(servo4Pin, servo4StartPos);
  Serial.begin(9600);
}

int calculated;

void loop() {
  //Serial.println(calculated);
  switch(currentStep){
    case step1:
      servo1->moveTo(10);
      delay(100);
      servo1->moveTo(servo1StartPos);
      currentStep = step2;
      break;
      
    case step2:
      /*if(ultra1Smooth->output(ultra1->inches()) < ultra1Thresh){
        servo2->moveTo(10);
        currentStep = step3;
      }*/
      calculated = (6762/(analogRead(A1)-9))-4;
      if(calculated < 15){
        servo2->moveTo(10);
        delay(500);
        servo2->moveTo(servo2StartPos);
        currentStep = step3;
      }
      break;
      
    case step3:
      if(ultra2->inches() < ultra2Thresh){
        servo3->moveTo(90);
        delay(500);
        servo3->moveTo(45);
        currentStep = step4;
      }
      break;
      
    case step4:
      if(button->Pressed()){
        servo4->moveTo(100);
        delay(5000);
        servo4->moveTo(servo4StartPos);
      }
      break;
      
  }
}
