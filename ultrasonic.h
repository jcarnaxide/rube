class UltraSonic {
  public:
    UltraSonic(const int echoPin, const int triggerPin);
    long inches();
	  long centimeters();
  private:
	  void trigger();
	  long microsecondsToInches(long microseconds);
	  long microsecondsToCentimeters(long microseconds);
    int echoPin;
    int triggerPin;
};

UltraSonic::UltraSonic(const int echoPin, const int triggerPin){
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  this->echoPin = echoPin;
  this->triggerPin = triggerPin;
}

void UltraSonic::trigger(){
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(this->triggerPin, LOW);
}

long UltraSonic::microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long UltraSonic::microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

long UltraSonic::inches(){
  long inches, duration = 0;
  
  trigger();
  duration = pulseIn(this->echoPin, HIGH);
  inches = microsecondsToInches(duration);
  delay(100);
  
  return inches;
}

long UltraSonic::centimeters(){
  long centimeters, duration = 0;
  
  trigger();
  duration = pulseIn(this->echoPin, HIGH);
  centimeters = microsecondsToCentimeters(duration);
  delay(100);
    
  return centimeters;
}
