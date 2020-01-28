#if ACCEL
// ==== Message VARs ====== //
char in_text[64];                // Character buffer
int in_text_index = 0;

// ==== Message CODE ====== //
void receiveMessage(){
  if (Serial.available() > 0) { 
    char incomingChar = Serial.read(); // read byte from serial
    if (incomingChar == 13){
      //show the in_text with show message
      //reset the in_text index back to 0
      memset(in_text,0,20); // this will clear the in_text buffer
    }
    else{
      //assign in_text[index] to the incoming char
      //increment the index
    }
  }
}
#endif
