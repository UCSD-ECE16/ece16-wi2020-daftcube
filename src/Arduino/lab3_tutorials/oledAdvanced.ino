/*
 * OLED_ADVANCED
 * 
 * A more organized and effective version of OLED for rendering text.
 * This library simulates a scrolling terminal, where each new message
 * pushes the previous ones down the screen.
 * 
 * Incompatible with daftDrawLib.
 */

#if OLED_ADVANCED

#include <Wire.h> 
#include "U8x8lib.h"

#define OLED_RESET 4 // this value resets the OLED

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(OLED_RESET);
bool OledAdvanced_wasInitialized = false;
String OledAdvanced_previousMessages[3];


/*
 * void setupOled()
 * 
 * The setup function for the OLEDAdvanced module.
 */
void setupOled()
{
  u8x8.begin();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setPowerSave(0);

  u8x8.setCursor(0, 0);
  u8x8.print("INITIALIZED!");
}

/*
 * clearScreenAndText()
 * 
 * Wipes the screen, clearing all lines and text history.
 */
void clearScreenAndText()
{
  OledAdvanced_previousMessages[0] = "";
  OledAdvanced_previousMessages[1] = "";
  OledAdvanced_previousMessages[2] = "";

  u8x8.clearDisplay();
}

/*
 * printToScreen(String str)
 * 
 * Prints the given string of text to the display and adds it to the text history.
 */
void printToScreen(String str)
{
  // Push back messages
  String temp = OledAdvanced_previousMessages[1];
  OledAdvanced_previousMessages[1] = OledAdvanced_previousMessages[0];
  OledAdvanced_previousMessages[2] = temp;

  // Insert in front
  OledAdvanced_previousMessages[0] = str;

  // Draw messages
  u8x8.clearDisplay();
  
  for(int i = 0; i < 3; i++)
  {
    u8x8.setCursor(0, 2-i);
    u8x8.print(OledAdvanced_previousMessages[i]);
  }
}

#endif
