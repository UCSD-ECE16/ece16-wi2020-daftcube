#if OTHER_CHALLENGES

int accelZ_calibratedAverage = 2450;
int accelY_calibratedAverage = 1822;
int accelX_calibratedAverage = 1931;

int accelZ_threshold = 75;
int accelY_threshold = 75;
int accelX_threshold = 75;

// ===== Gesture Code  ========//
unsigned long lastTapDebounce = 0;
#define DEBOUNCE_TIMER_LENGTH 100

bool detectTap(){
  //read the ADC values. Note that the ADC values are global so you don’t need to define a local variable for them. 
  bool tap_detected = false; // first set to false
  if(
    //(
    abs( accelZ_Val - accelZ_calibratedAverage ) > accelZ_threshold 
    //|| abs( accelY_Val - accelY_calibratedAverage ) > accelY_threshold ||
    //abs( accelX_Val - accelX_calibratedAverage ) > accelX_threshold) 
    &&
    ((lastTapDebounce + DEBOUNCE_TIMER_LENGTH) < millis())
  ){
    tap_detected = true; //if the accel values meet the rule, set to true
    lastTapDebounce = millis() + DEBOUNCE_TIMER_LENGTH;
  }
  return tap_detected;
}

void printADC(){ //print the ADC values
  Serial.print("Z:");
  Serial.print(accelZ_Val);
  Serial.print(",");
  Serial.print("Y:");
  Serial.print(accelY_Val);
  Serial.print(",");
  Serial.print("X:");
  Serial.print(accelX_Val);  
  Serial.print(",");
  Serial.print("Z Upper Bound:");
  Serial.print(accelZ_calibratedAverage + accelZ_threshold);
  Serial.print(",");
  Serial.print("Z Lower Bound:");
  Serial.print(accelZ_calibratedAverage - accelZ_threshold);
  Serial.print(",");
  Serial.print("Z Calibrated Avg:");
  Serial.print(accelZ_calibratedAverage);
  Serial.print(",");
  Serial.print("Y Upper Bound:");
  Serial.print(accelY_calibratedAverage + accelY_threshold);
  Serial.print(",");
  Serial.print("Y Lower Bound:");
  Serial.print(accelY_calibratedAverage - accelY_threshold);
  Serial.print(",");
  Serial.print("Y Calibrated Avg:");
  Serial.print(accelY_calibratedAverage);
  Serial.print(",");
  Serial.print("X Upper Bound:");
  Serial.print(accelX_calibratedAverage + accelX_threshold);
  Serial.print(",");
  Serial.print("X Lower Bound:");
  Serial.print(accelX_calibratedAverage - accelX_threshold);
  Serial.print(",");
  Serial.print("X Calibrated Avg:");
  Serial.println(accelX_calibratedAverage);

}

#endif
