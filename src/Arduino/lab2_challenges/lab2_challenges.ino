#define CHALLENGE_1 false
#define OTHER_CHALLENGES true
#define FIREWORKS false

#if OTHER_CHALLENGES

// ========   Main   ======== //

void setup()
{
  setupADC();
  initDisplay();
  setupMotor();
  Serial.begin(115200);
}

void loop()
{
  readADC();
  printADC();
  executeTimerTask();
}

// I did lab C2 and C3 in parallel.
void Lab_C2C3()
{
  readADC();
  //printADC();

  if ( detectTap() )
  {
    addTimerOLED();
  }

  runTimerOLED();
  receiveMessage();
}


/*
void Lab_C4()
{
  readADC();
  printADC();

  if ( detectTap() )
  {
    addTimerOLED();
  }

  runTimerOLED();
}
*/
#endif
