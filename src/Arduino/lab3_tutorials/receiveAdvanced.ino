#if RECEIVE_ADVANCED

#define MESSAGE_HISTORY 16
#define BAUD_RATE 115200
#define CHAR_DELIMITER 13

struct serialMessage ReceiveAdvanced_messageHistory[MESSAGE_HISTORY];

int ReceiveAdvanced_currentPositionInBuffer;
char ReceiveAdvanced_buffer[BUFFER_SIZE];

int ReceiveAdvanced_nextMessageId = 0;

/*
 * Sets up the Serial connection.
 */
void setupReceive()
{
  Serial.begin(BAUD_RATE);
}


/*
 * nonblockingReceive()
 * 
 * Conducts a non-blocking serial read operation.
 * 
 * RETURNS:
 *  TRUE, if a complete message was received this iteration.
 *  FALSE, if a complete message was not received during this iteration.
 */
bool nonblockingReceive()
{
  while(Serial.available() > 0)
  {
    char incomingChar = Serial.read();
    Serial.print(incomingChar);
    ReceiveAdvanced_currentPositionInBuffer++;

    if (ReceiveAdvanced_currentPositionInBuffer < BUFFER_SIZE) 
    {
      ReceiveAdvanced_buffer[ReceiveAdvanced_currentPositionInBuffer] = incomingChar;
      
      // If the character is the delimiter, create a new message!
      if (incomingChar == CHAR_DELIMITER)
      {
        // Create message!
        struct serialMessage receivedMessage;
        memcpy(receivedMessage.buff, ReceiveAdvanced_buffer, sizeof(ReceiveAdvanced_buffer));
        receivedMessage.actualBuffSize = ReceiveAdvanced_currentPositionInBuffer + 1;
        receivedMessage.id = ReceiveAdvanced_nextMessageId++; // Increment nextId by 1 to prepare for the next message.

        // Add message to history!
        addSerialMessageToHistory(receivedMessage);
        
        // Now that the message is saved in a struct, we can clear our reading variables.
        resetSerialVariables();

        //printDebug(receivedMessage);
  
        // We got the message, return true!
        return true;
      }
    }
    // If the buffer is full, and we didn't reach a delimiter, this message is malformed and must be destroyed.
    else
    {
      resetSerialVariables();
    }
  }

  return false;
}

/*
 * Adds the given serial message to the internal history.
 */
void addSerialMessageToHistory(struct serialMessage msg)
{  
  // Push back all
  for (int i = (MESSAGE_HISTORY - 1); i > 0; i--)
  {
    ReceiveAdvanced_messageHistory[i] = ReceiveAdvanced_messageHistory[i - 1];
  }
  
  // Add new to the history buffer.
  ReceiveAdvanced_messageHistory[0] = msg;
}

/*
 * resetSerialVariables()
 * 
 * Resets variables that read the incoming data so that they
 * can read another message.
 */
void resetSerialVariables()
{
  ReceiveAdvanced_currentPositionInBuffer = 0;
  memset(ReceiveAdvanced_buffer, 0, sizeof(ReceiveAdvanced_buffer));
}

/*
 * getMostRecentMessage() 
 * 
 * Returns the most recent serial message received.
 */
struct serialMessage getMostRecentMessage()
{ 
  for(int i = 0; i < 8; i++)
  {
    printDebug (ReceiveAdvanced_messageHistory[i]);
  }
  
  return ReceiveAdvanced_messageHistory[0];
}


void printDebug(struct serialMessage msg)
{
  Serial.println("---");
  Serial.print("MSG: ");
  Serial.println(msg.id);
  for(int i = 0; i < 128; i++)
  {
    Serial.print(msg.buff[i]);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.println("---");
}
#endif
