#define CHALLENGE_1 false
#define OTHER_CHALLENGES true
#define FIREWORKS false

#if OTHER_CHALLENGES

// ========   Main   ======== //

void setup()
{
  setupADC();
  setupLed();
  initDisplay();
  //setupMotor();
  Serial.begin(115200);
}

void loop()
{
  Lab3();
}

/*
 * Lab 3 Challenges
 */
void Lab3()
{
  receiveMessage();
  sendData();
  checkMessage();
}

// Contains logic for last lab.
void Lab2_ChallengesFinal()
{
  readADC();
  printADC();
  executeTimerTask();
}

// I did lab C2 and C3 in parallel.
void Lab2_C2C3()
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
