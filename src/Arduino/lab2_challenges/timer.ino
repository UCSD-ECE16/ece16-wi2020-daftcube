// ========= Timer Var ========= //

unsigned long subTimerMs = 0; //initiate the last tap time at 0

// ========== Timer Code ========= //
void runTimerOLED() {
  if (millis() > subTimerMs)
  {
    subTimerMs = millis() + 1000;
    timer_seconds -= 1;
    if (timer_seconds <= 0) { timer_seconds = 0; }

    String stringTime = String(timer_seconds);
    stringTime.toCharArray(message_buffer,4); //convert string to char buffer
    
    // show message_buffer with showMessage
    showMessage(message_buffer, 0, true);
  }
}

void pauseForThreeSeconds()
{
  subTimerMs = millis() + 3000;
}
