#if OLED

#include <Wire.h>
#include "U8x8lib.h"

// OLED setup
#define OLED_RESET 4 // this value resets the OLED
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(OLED_RESET);

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
void showMessage(const char * message, int row, bool cleardisplay) {
  if(cleardisplay){
    u8x8.clearDisplay();
  }
  u8x8.setCursor(0, row);
  u8x8.print(message);
}


void setup()
{
  initDisplay();
  showMessage("Initializing...", 1, true);
  showMessage("Success!", 2, false);
}

void loop()
{
  delay(3000);
  showMessage("The Industrial", 1, true);
  showMessage("Revolution and", 2, false);
  delay(3000);
  showMessage("its consequences", 1, true);
  showMessage("have been a", 2, false);
  delay(3000);
  showMessage("disaster for the", 1, true);
  showMessage("Human race.", 2, false);
  delay(3000);
  showMessage("- Ted K, Una-", 1, true);
  showMessage("bomber Manifesto", 2, false);
  delay(3000);
  
  
}


#endif
