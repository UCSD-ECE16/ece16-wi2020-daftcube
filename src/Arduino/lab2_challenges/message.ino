#if OTHER_CHALLENGES
// ==== Message VARs ====== //
char in_text[64];                // Character buffer
int in_text_index = 0;

// ==== Message CODE ====== //
void receiveMessage() {
  if (Serial.available() > 0) { 
    char incomingChar = Serial.read(); // read byte from serial
    if (incomingChar == 13){

      showMessage("                   ", 1, false); // Clear line
      showMessage(in_text, 1, false);
      in_text_index = 0;
      memset(in_text,0,20); // this will clear the in_text buffer
    }
    else{
      in_text[in_text_index] = incomingChar;
      in_text_index++;
    }
  }
}
#endif
