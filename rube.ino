#include "ultrasonic.h"
#include "smoothing.h"
#include "servo.h"
#include "button.h"

int Ultra1Echo = 9;
int Ultra1Trigger = 8;
UltraSonic *ultra1;
Smoothing *ultra1Smooth;
int ultra1Thresh = 2;

int button1Pin = 12;
Button *button1;

int button2Pin = 2;
Button *button2;
int button3Pin = 3;
Button *button3;
int button4Pin = 4;
Button *button4;
int button5Pin = 5;
Button *button5;
int button6Pin = 13;
Button *button6;
int button7Pin = 7;
Button *button7;

int servo1Pin = 10;
int servo1StartPos = 180;
ServoControl *servo1;

int servo2Pin = 11;
int servo2StartPos = 180;
ServoControl *servo2;

int servo3Pin = 6;
int servo3StartPos = 45;
ServoControl *servo3;

enum Steps{
  step1,
  step2,
  step3,
  step4,
  step5,
  step6,
  step7,
  step8,
  lastStep
};
Steps currentStep = step1;

void setup() {
  ultra1 = new UltraSonic(Ultra1Echo, Ultra1Trigger);
  ultra1Smooth = new Smoothing(8);

  button1 = new Button(button1Pin);
  button2 = new Button(button2Pin);
  button3 = new Button(button3Pin);
  button4 = new Button(button4Pin);
  button5 = new Button(button5Pin);
  button6 = new Button(button6Pin);
  button7 = new Button(button7Pin);

  servo1 = new ServoControl(servo1Pin, servo1StartPos);
  servo2 = new ServoControl(servo2Pin, servo2StartPos);
  servo3 = new ServoControl(servo3Pin, servo3StartPos);
  Serial.begin(9600);
}

int calculated;

void loop() {
  //Serial.println(calculated);
  switch(currentStep){
    case step1:
      if(button1->Pressed()){
        servo1->moveTo(100);
        currentStep = step2;
      }
      break;
      
    case step2:
      if(ultra1Smooth->output(ultra1->inches()) < ultra1Thresh){
        servo2->moveTo(160);
        currentStep = step3;
      }
      break;
      
    case step3:
      while(digitalRead(button2Pin) != HIGH){ }
      Serial.println("Got 1 Here");
      servo2->moveTo(135);
      currentStep = step4;
      break;
      
    case step4:
      while(digitalRead(button3Pin) != HIGH){ }
      Serial.println("Got 2 Here");
      servo2->moveTo(100);
      currentStep = step5;
      break;
      
    case step5:
      while(digitalRead(button4Pin) != HIGH){ }
      Serial.println("Got 3 Here");
      servo2->moveTo(70);
      currentStep = step6;
      break;
      
    case step6:
      while(digitalRead(button5Pin) != HIGH){ }
      Serial.println("Got 4 Here");
      servo2->moveTo(35);
      delay(200);
      servo2->moveTo(10);
      currentStep = step7;
      break;
      
    case step7:
      while(digitalRead(button6Pin) != HIGH){ }
      Serial.println("Got 5 Here");
      servo2->moveTo(0);
      currentStep = step8;
      break;
      
    case step8:
      while(digitalRead(button7Pin) != HIGH){ }
      Serial.println("Got 6 Here");
      servo3->moveTo(90);
      delay(500);
      servo3->moveTo(45);
      currentStep = lastStep;
      break;

    case lastStep:
      while(1){};
      break;
  }
}
