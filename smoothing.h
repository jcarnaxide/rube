class Smoothing{
  public:
    Smoothing();
    int output(int input);
  private:
    static const int numReadings = 10;
    int readings[numReadings];      // the readings from the analog input
    int readIndex;              // the index of the current reading
    int total;                  // the running total
    int average;                // the average
};

Smoothing::Smoothing(){
  readIndex = 0;
  total = 0;
  average = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

int Smoothing::output(int input){
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = input;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  delay(1);        // delay in between reads for stability
  return average;
}
