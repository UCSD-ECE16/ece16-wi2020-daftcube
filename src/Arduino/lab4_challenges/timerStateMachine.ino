#if OTHER_CHALLENGES

#define WAITING_FOR_TAP 0
#define COUNTING_UP 1
#define COUNTING_DOWN 2
#define BUZZ 3

#define DELAY_UNTIL_COUNT_DOWN 3000

int timerState = 0;

unsigned long subTimer = 0;

void executeTimerTask()
{
  switch(timerState)
  {
    case WAITING_FOR_TAP:
      
      //showMessage("Tap for Timer!     ", 0, false);
      
      // Transition to self is implied.

      // Transition to COUNTING_UP when tapped!
      if (detectTap())
      {
        // Add to timer and set the subtimer for the first time
        //addTimerOLED();
        subTimer = millis();

        
        timerState = COUNTING_UP;
      }
      
      break;
    
    case COUNTING_UP:
      
      // If we detect a tap, add to OLED.
      if (detectTap())
      {
        subTimer = millis();
        //addTimerOLED();
      }

      // Transition to next state if subtimer expired
      if (subTimer + DELAY_UNTIL_COUNT_DOWN < millis())
      {
        timerState = COUNTING_DOWN;
      }
      
      break;
    
    case COUNTING_DOWN:
  
      runTimerOLED();

      // Transition to self is implied.

      // Transition to BUZZ if time's up!
      if (timer_seconds <= 0)
      {
        timerState = BUZZ;
      }
      
      break;
    
    case BUZZ:
      
      buzzMotor(255);
      //showMessage("Time's up!        ", 0, false);

      // Transition to self is implied.

      if (detectTap()) {
        timerState = WAITING_FOR_TAP;
        buzzMotor(0);
      }
      
      break;
  }
}

#endif
