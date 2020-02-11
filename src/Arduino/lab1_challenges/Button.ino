/*
 * Button.ino
 * 
 * Owen Bartolf
 * 
 * Represents a button that can be used to receive a digital input.
 */

#ifdef TIMER

const int BUTTON_INPUT_PIN = 25; // Pin for button.

/*
 * Setup is called at initialization.
 */
void setupButton()
{
  pinMode(BUTTON_INPUT_PIN, INPUT);
}

/*
 * Returns true when the button is pressed, false otherwise.
 */
bool getButton()
{ 
  bool currentState = digitalRead(BUTTON_INPUT_PIN);
  return !currentState; // We're using a pull-up resistor, so we must invert the result.
}

#endif
