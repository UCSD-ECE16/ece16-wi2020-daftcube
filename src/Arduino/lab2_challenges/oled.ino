#ifdef ACCEL

int timer = 0;

// =========== OLED Code ============ //

// ----------------------------------------------------------------
// Initialize the OLED with base font for fast refresh
// ----------------------------------------------------------------
void initDisplay() {
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setCursor(0, 0);
}

// ----------------------------------------------------------------
// A function to write a message on the display
// "row" specifies which row to print on... 1, 2, 3, etc.
// "clearDisplay" specifies if everything should be wiped or not
// ----------------------------------------------------------------
void showMessage(const char * message, int row, bool clearDisplay) {
  if(clearDisplay){
    u8x8.clearDisplay();
  }
  u8x8.setCursor(0, row);
  u8x8.print(message);
}

char message_buffer[4];
int timer_seconds = 0;

void addTimerOLED(){
  //increment timer_seconds
  timer_seconds++;
  pauseForThreeSeconds();
  
  String stringTime = String(timer_seconds);
  stringTime.toCharArray(message_buffer,4); //convert string to char buffer
  
  // show message_buffer with showMessage
  showMessage(message_buffer, 0, true);
}



#endif
