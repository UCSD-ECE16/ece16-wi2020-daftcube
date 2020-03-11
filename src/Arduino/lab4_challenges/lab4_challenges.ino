
#include <heartRate.h>
#include <MAX30105.h>
#include <spo2_algorithm.h>


#define CHALLENGE_1 false
#define OTHER_CHALLENGES true
#define FIREWORKS false
#define OLED_ADVANCED true

#if OTHER_CHALLENGES

// ========   Main   ======== //

int timer_seconds = 0;

void setup()
{
  setupADC();
  setupLed();
  setupOled();
  setupSerial();
  setupHR();

  delay(2000);
}

void loop()
{
  Lab4();
}

/*
 * Lab 3 Challenges
 */
void Lab4()
{
  receiveMessage();
  sendData();
  checkMessage();
  readHR();
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
    //addTimerOLED();
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
