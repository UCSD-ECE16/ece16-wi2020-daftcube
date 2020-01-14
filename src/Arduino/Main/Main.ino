/*
 * Main.ino
 * 
 * Owen Bartolf
 * 
 * Options:
 * Define LED, TIMER to enable and disable certain parts
 * of the program. They should all be able to run in parallel, too.
 */

#define LED 1
#define TIMER 1

// Amount of time the loop function yields for before calling active tasks again.
const int TASK_DELAY = 1;

/*
 * Setup is called at startup.
 */
void setup()
{
  #ifdef LED
  challenge1Setup();
  #endif

  #ifdef TIMER
  challenge2Setup();
  #endif
}


/*
 * Loop is called repeatedly by the MCU
 * 
 * Remarks:
 * All of my code follows a task-based pattern. Each condition method
 * is a self-contained task, with a self-contained timer. All
 * loop does is call the task and each method handles the rest.
 * 
 * This ensures maximum extendability and ensures that the main loop will not
 * be blocked by subordinate tasks.
 */
void loop()
{
  #ifdef LED
  executeChallenge1Tasks();
  #endif

  #ifdef TIMER
  executeChallenge2Tasks();
  #endif

  // Wait a TASK_DELAY amount of time before calling everything again.
  delay(TASK_DELAY);
}
