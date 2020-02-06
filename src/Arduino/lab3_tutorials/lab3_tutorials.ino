#define DAFT_DRAW_LIB false
#define OLED_ADVANCED true
#define RECEIVE_ADVANCED true

// --------------------------------------------------------------------------
// Below is a struct used throughout the code. This is here because of
// really bad Arduino compiling ordering.
// --------------------------------------------------------------------------

#include "receiveAdvancedStruct.h"
#define BUFFER_SIZE 128
struct serialMessage {
  int id;
  int actualBuffSize;
  char buff[BUFFER_SIZE];
};

// --------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  setupOled();
  setupReceive();
}

int t = 0;

void loop() {
  if (nonblockingReceive())
  {
    struct serialMessage newestMsg = getMostRecentMessage();
    printToScreen(newestMsg.buff);
  }
}
