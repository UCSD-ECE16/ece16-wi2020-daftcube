/* 
 *  Timer.ino
 *  
 *  Owen Bartolf
 * 
 * Remarks:
 * Timer depends on Button.
 * 
 * Options
 * BENCHMARK_ENABLED: If defined, will run the benchmark serial printing code.
 */
#define BENCHMARK_ENABLED

#ifdef TIMER

const int BUTTON_PRESS_TIME_TO_ADD_ONE_SECOND = 1000;
const int BUTTON_PRESS_TIME_TO_REMOVE_ONE_SECOND = 200;

int challenge2Timer_seconds = 0; // The main timer
int subTimer = 0; // Subtimer for tracking how long the button has been held down for.

byte state = 0; // A simple variable to keep track of what state we are (See state machine diagram)

#ifdef BENCHMARK_ENABLED
bool isRunningBenchmark = false;
unsigned long benchmarkStartTime = 0;
#endif

// Benchmark

/*
 * Setup is called at initialization.
 */
void challenge2Setup()
{
  // Setup submodules.
  setupMessage();
  setupButton();
}

/*
 * Loop is called repeatedly as long as the MCU has power.
 */
void executeChallenge2Tasks()
{
  /*
   * Simple State Machine
   * 
   * -------------------------------------
   * |                                   |
   * |                                   |
   * V                                   |
   * [WAITING (0)]                       |
   * |                                   |
   * | Button pressed for first time     |
   * V                                   |
   * [COUNTING_UP (1)]                   |
   * |                                   |
   * | Button released for first time    |
   * V                                   |
   * [COUNTING_DOWN (2)]                 |
   * |                                   |
   * |                                   |
   * |                                   |
   * -------------------------------------
   */

  switch(state)
  {
    // [ START ]
    case 0:

      // TRANSITION
      // If we detect a button press, advance the state.
      if (getButton())
      {
        transitionState();

        
        #ifdef BENCHMARK_ENABLED

        isRunningBenchmark = true;
        benchmarkStartTime = micros();
        
        #endif
      }
      
      break;
    // [ COUNTING_UP ]
    case 1:

      subTimer++; // Increase the time since the button was last pushed.
      
      // If the subtimer is at the time needed to add one to the timer...
      if (subTimer >= BUTTON_PRESS_TIME_TO_ADD_ONE_SECOND)
      {
        // Add to master timer and reset subtimer.
        addTimer();
        subTimer = 0;

        
        #ifdef BENCHMARK_ENABLED
        if (isRunningBenchmark)
        {
          isRunningBenchmark = false;
          unsigned long benchmarkTime = micros() - benchmarkStartTime;
          Serial.print("Benchmark: ");
          Serial.println(benchmarkTime);
        }
        #endif
      }

      // TRANSITION
      // If we no longer detect a button press, advance the state.
      if (!getButton())
      {
        transitionState();

        // Reset subtimer.
        subTimer = 0;
      }
      break;
    // [ COUNTING_DOWN ]
    case 2:

      subTimer++; // Add to subtimer
      if (subTimer >= BUTTON_PRESS_TIME_TO_REMOVE_ONE_SECOND)
      {
        subTimer = 0;
        runTimer();
      }

      // TRANSITION
      // If the master timer is zero, go back to the first state.
      if (challenge2Timer_seconds <= 0)
      {
        transitionState();

        // Reset subtimer.
        subTimer = 0;
      }
      break;
  }
}

/*
 * addTimer is a utility function that adds one second to the timer when called.
 */
void addTimer()
{
  challenge2Timer_seconds++;
  printTime(challenge2Timer_seconds);
}

/*
 * runTimer ticks down the timer by a single increment.
 */
void runTimer()
{
  challenge2Timer_seconds--;
  printTime(challenge2Timer_seconds);
}

/*
 * transitionState() moves the program to the next timer state.
 */
void transitionState()
{
  state = (state + 1) % 3;
  printStateMachineTransition(state);
}

#endif
