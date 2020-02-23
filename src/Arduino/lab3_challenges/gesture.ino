#if OTHER_CHALLENGES

int accelZ_calibratedAverage = 2450;
int accelY_calibratedAverage = 1822;
int accelX_calibratedAverage = 1931;

int accelZ_threshold = 100;
int accelY_threshold = 100;
int accelX_threshold = 100;

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
  
  //printSerial("Microseconds: ");
  printSerial(micros());
  printSerial(",");
  //printSerial("X:");
  printSerial(accelX_Val);
  printSerial(",");
  //printSerial("Y:");
  printSerial(accelY_Val);
  printSerial(",");
  //printSerial("Z:");
  printlnSerial(accelZ_Val);  
  /*
  printSerial(",");
  printSerial("Z Upper Bound:");
  printSerial(accelZ_calibratedAverage + accelZ_threshold);
  printSerial(",");
  printSerial("Z Lower Bound:");
  printSerial(accelZ_calibratedAverage - accelZ_threshold);
  printSerial(",");
  printSerial("Z Calibrated Avg:");
  printSerial(accelZ_calibratedAverage);
  printSerial(",");
  printSerial("Y Upper Bound:");
  printSerial(accelY_calibratedAverage + accelY_threshold);
  printSerial(",");
  printSerial("Y Lower Bound:");
  printSerial(accelY_calibratedAverage - accelY_threshold);
  printSerial(",");
  printSerial("Y Calibrated Avg:");
  printSerial(accelY_calibratedAverage);
  printSerial(",");
  //printSerial("X Upper Bound:");
  //printSerial(accelX_calibratedAverage + accelX_threshold);
  //printSerial(",");
  //printSerial("X Lower Bound:");
  //printSerial(accelX_calibratedAverage - accelX_threshold);
  //printSerial(",");
  //printSerial("X Calibrated Avg:");
  //printlnSerial(accelX_calibratedAverage);*/
  
}

#endif
