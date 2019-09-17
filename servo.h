#include <Servo.h>

class ServoControl {
  public:
    ServoControl(const int pin, int startPos);
    void moveTo(int degree);
    void moveToSlowly(int degree);
    int pos;
  private:
    Servo myservo;
};

ServoControl::ServoControl(const int pin, int startPos){
  this->myservo.attach(pin);
  this->pos = startPos;
  this->myservo.write(this->pos);
}

void ServoControl::moveTo(int degree){
  int bounded;
  if(degree < 0){
    bounded = 0;
  }
  else if (degree > 180){
    bounded = 180;
  }
  else{
    bounded = degree;
  }
  this->myservo.write(bounded);
  delay(100);
}

void ServoControl::moveToSlowly(int degree){
  if(degree < this->pos){
    for(int i = this->pos; i >= degree; i--) // move downward from current position to input degree
    {                                  // in steps of 1 degree 
      this->myservo.write(this->pos);
      delay(15);                       // waits 15ms for the servo to move smoothly
    }
  }
  else if(degree > this->pos){
    for(int i = this->pos; i <= degree; i++) // move downward from current position to input degree
    {                                  // in steps of 1 degree 
      this->myservo.write(this->pos);
      delay(15);                       // waits 15ms for the servo to move smoothly
    }
  }
}
