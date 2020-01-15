/*
 * Message.ino
 * 
 * Owen Bartolf
 * 
 * Remarks:
 * Message.ino depends on Timer.ino to be enabled.
 * 
 * Options:
 * SHOW_STATE_MACHINE_TRANSITIONS: If true, the program will print state machine changes
 *  to the serial monitor.
 */

#ifdef TIMER
#define SHOW_STATE_MACHINE_TRANSITIONS true

/*
 * Setup is called at initialization.
 */
void setupMessage()
{
  Serial.begin(9600);
}

/*
 * printTime() is a utility method that prints the current time.
 */
void printTime(int timeToPrint)
{
  Serial.print("Current Time: ");
  Serial.println(timeToPrint);
}

/*
 * printStateMachineTransition() prints a notification of a state machine
 * transition to the serial monitor.
 */
void printStateMachineTransition(int newState)
{
  if (SHOW_STATE_MACHINE_TRANSITIONS)
  {
    Serial.print("Internal State Machine Transition. New State: ");
    switch(newState)
    {
      case 0:
        Serial.println("[START]");
        break;
      case 1:
        Serial.println("[COUNTING UP]");
        break;
      case 2:
        Serial.println("[COUNTING DOWN]");
        break;
      default:
        Serial.println("[UNKNOWN STATE]");
        break;
    }
  }
}

#endif
