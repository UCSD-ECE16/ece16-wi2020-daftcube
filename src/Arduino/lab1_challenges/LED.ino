/*
 * LED.ino
 * 
 * Owen Bartolf
 * 
 * Options:
 * LED_IS_SEQUENTIAL (true / false): When IsSequential is true, each challenge will loop through
 * itself in sequence. If false, each challenge will run simultaneously.
 */

#ifdef LED
#define LED_IS_SEQUENTIAL false

// If we are using sequential mode, this variable will keep track of the current challenge we are on.
int condition = 0;
int sequentialMasterTimer = 0;
const int SEQUENTIAL_TIME_PER_CHALLENGE = 4000;

// LED pins. I elected them to be constants.
bool onboardLEDIsToggled = false;
const int RED_LED = 26;
const int YELLOW_LED = 27;
const int BLUE_LED = 13;

// Timer for each LED. Allows operation in parallel.
int timerState[6] = {0, 0, 0, 0, 0, 0};

/*
 * Sets up all of the resources that Challenge 1 depends on.
 */
void challenge1Setup()
{
  // Setup GPIO as output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

/*
 * Executes all of the tasks associated with Challenge 1.
 */
void executeChallenge1Tasks()
{
  if (LED_IS_SEQUENTIAL)
  {
    // Sequential tasks
    switch(condition)
    {
       case 0: condition1(); break;
       case 1: condition2(); break;
       case 2: condition3(); break;
       case 3: condition4(); break;
       case 4: condition5(); break;
       case 5: condition6(); break;
    }

    // Add to our master timer. If we need to cycle, do.
    sequentialMasterTimer += TASK_DELAY;
    if (sequentialMasterTimer >= SEQUENTIAL_TIME_PER_CHALLENGE)
    {
      condition = (condition + 1) % 6; // Increment challenge
      sequentialMasterTimer = 0; // Reset timer.

      // Reset LEDs to off after cycling
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  else
  {
    // Run every task in parallel except the onboard LEDs, which will run sequentially.

    // Onboard LED only.
    switch(condition)
    {
       case 0: condition1(); break;
       case 1: condition2(); break;
       case 2: condition3(); break;
    }

    // Run others in parallel
    condition4();
    condition5();
    condition6();

    // Add to our master timer. If we need to cycle, do.
    sequentialMasterTimer += TASK_DELAY;
    if (sequentialMasterTimer >= SEQUENTIAL_TIME_PER_CHALLENGE)
    {
      condition = (condition + 1) % 3; // Increment challenge
      sequentialMasterTimer = 0; // Reset timer.
    }
  }
}


// Onboard LED Blink 1 HZ
void condition1()
{
  if (onboardLEDIsToggled)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Increment timer for this task.
  timerState[0] += TASK_DELAY;
  if (timerState[0] >= 1000) // 1Hz = 1000 ms
  {
    onboardLEDIsToggled = !onboardLEDIsToggled; // Toggle LED every second.
    timerState[0] = 0; // Reset timer
  }
}

// Onboard LED Blink 10 HZ
void condition2() 
{
  if (onboardLEDIsToggled)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Increment timer for this task.
  timerState[1] += TASK_DELAY;
  if (timerState[1] >= 100) // 10Hz = 100ms
  {
    onboardLEDIsToggled = !onboardLEDIsToggled; // Toggle LED every second.
    timerState[1] = 0; // Reset timer
  }
}

// Onboard LED Blink 50 Hz
void condition3()
{
  if (onboardLEDIsToggled)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Increment timer for this task.
  timerState[2] += TASK_DELAY;
  if (timerState[2] >= 20) // 50Hz = 1 / 50 = 20 ms
  {
    onboardLEDIsToggled = !onboardLEDIsToggled; // Toggle LED every second.
    timerState[2] = 0; // Reset timer
  }
}

// 1s / 100ms Red LED
bool condition4LEDIsToggled = true;
void condition4() 
{
  // Toggle LED
  if (condition4LEDIsToggled)
  {
    digitalWrite(RED_LED, HIGH);
  }
  else
  {
    digitalWrite(RED_LED, LOW);
  }
  
  // Increment timer for this task.
  timerState[3] += TASK_DELAY;
  if (condition4LEDIsToggled && timerState[3] >= 1000) // 1 s, ON
  {
    condition4LEDIsToggled = false; // Turn off for next cycle
    timerState[3] = 0; // Reset timer
  }
  else if(!condition4LEDIsToggled && timerState[3] >= 100) // 100 ms, OFF
  {
    condition4LEDIsToggled = true; // Turn on for next cycle
    timerState[3] = 0; // Reset timer
  }
}

// 200ms / 50ms Yellow LED
bool condition5LEDIsToggled = true;
void condition5() 
{
  // Toggle LED
  if (condition5LEDIsToggled)
  {
    digitalWrite(YELLOW_LED, HIGH);
  }
  else
  {
    digitalWrite(YELLOW_LED, LOW);
  }
  
  // Increment timer for this task.
  timerState[4] += TASK_DELAY;
  if (condition5LEDIsToggled && timerState[4] >= 200) // 200 ms, ON
  {
    condition5LEDIsToggled = false; // Turn off for next cycle
    timerState[4] = 0; // Reset timer
  }
  else if(!condition5LEDIsToggled && timerState[4] >= 50) // 50 ms, OFF
  {
    condition5LEDIsToggled = true; // Turn on for next cycle
    timerState[4] = 0; // Reset timer
  }
}

bool condition6LEDIsToggled = true;
void condition6() 
{
  // Toggle LED
  if (condition6LEDIsToggled)
  {
    digitalWrite(BLUE_LED, HIGH);
  }
  else
  {
    digitalWrite(BLUE_LED, LOW);
  }
  
  // Increment timer for this task.
  timerState[5] += TASK_DELAY;
  if (condition6LEDIsToggled && timerState[5] >= 20) // 20 ms, ON
  {
    condition6LEDIsToggled = false; // Turn off for next cycle
    timerState[5] = 0; // Reset timer
  }
  else if(!condition6LEDIsToggled && timerState[5] >= 10) // 10 ms, OFF
  {
    condition6LEDIsToggled = true; // Turn on for next cycle
    timerState[5] = 0; // Reset timer
  }
}



#endif
