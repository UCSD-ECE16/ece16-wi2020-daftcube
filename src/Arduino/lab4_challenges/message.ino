#if OTHER_CHALLENGES
// ==== Message VARs ====== //
char in_text[64];                // Character buffer
int in_text_index = 0;

// ==== Message CODE ====== //
void receiveMessage() {
  if (serialAvailable() > 0) { 
    
    
    char incomingChar = serialRead(); // read byte from serial
    if (incomingChar == 10){
      

      //showMessage("                   ", 1, false); // Clear line
      //showMessage(in_text, 1, true);

      printToScreen(extractStringFromMessage(in_text, in_text_index));
      
      in_text_index = 0;
      memset(in_text,0,20); // this will clear the in_text buffer
    }
    else{
      in_text[in_text_index] = incomingChar;
      in_text_index++;
    }
  }
}

int sampling_rate = 50; //sampling rate in Hz
unsigned long sampling_delay = calcSamplingDelay(sampling_rate); //microseconds between samples
unsigned long last_sample_time = 0; //microsecond of last sample

bool sending_data = false; //to send data?


void sendData() {
    if(sending_data){
        if( micros() > (last_sample_time + sampling_delay) ){
            last_sample_time = micros();
            readADC();
            printADC();
        }
    }
}

void checkMessage(){
  String message = String(in_text); // converts in_text into a string
  
  if (message == "start data" && !sending_data)
  {
    sending_data = true;
    //delay(1000);
  }
  else if (message == "stop data" && sending_data)
  {
    sending_data = false;
  }
}


long calcSamplingDelay(long sampling_rate){
    return 1000000 / sampling_rate;
}

#endif
