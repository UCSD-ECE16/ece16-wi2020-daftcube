#if ACCEL

//ACCEL VARs
int accelZ = 34;
int accelY = 39; //assign pin value
int accelX = 36; //assign pin value

int accelZ_Val = 0;//set to 0
int accelY_Val = 0;//set to 0
int accelX_Val = 0;//set to 0

// ========   Main   ======== //

void setup()
{
  setupADC();
  initDisplay();
  Serial.begin(115200);
}

void loop()
{
  readADC();
  printADC();

  if ( detectTap() )
  {
    addTimerOLED();
  }

  runTimerOLED();
}

// ======== ADC Code ======== //
void setupADC(){
  //setup each accel pins to be an input pin
  
  pinMode(accelX, INPUT);
  pinMode(accelY, INPUT);
  pinMode(accelZ, INPUT);
}

void readADC(){
  //read each accel pin and assign value to the corresponding Val
  accelX_Val = analogRead(accelX);
  accelY_Val = analogRead(accelY);
  accelZ_Val = analogRead(accelZ);
}




#endif
