class Button {
  public:
    Button(const int pin);
    bool Pressed();
  private:
    int pin;
    int buttonState;             // the current reading from the input pin
    int lastButtonState = LOW;   // the previous reading from the input pin
    long lastDebounceTime = 0;  // the last time the output pin was toggled
    long debounceDelay = 50;    // the debounce time; increase if the output flickers
};

Button::Button(const int pin){
  pinMode(pin, INPUT);
  this->pin = pin;
}

bool Button::Pressed(){
  bool return_val = false;
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(this->pin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != this->lastButtonState) {
    // reset the debouncing timer
    this->lastDebounceTime = millis();
  }

  if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != this->buttonState) {
      this->buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (this->buttonState == HIGH) {
        return_val = true;
      }
    }  
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  this->lastButtonState = reading;
    
  return return_val;
}
