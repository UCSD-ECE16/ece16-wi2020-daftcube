/*
 * serialMessage.h
 * 
 * Defines a structure used by the receiveAdvanced library
 */

#define BUFFER_SIZE 128

typedef struct serialMessage
{
  int id;
  int actualBuffSize;
  char buff[BUFFER_SIZE];
};
