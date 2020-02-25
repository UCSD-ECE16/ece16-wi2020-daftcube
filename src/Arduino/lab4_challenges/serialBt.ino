#define USE_BLUETOOTH false
#define USE_SERIAL_PORT true
#define BAUD_RATE 230400

#if USE_BLUETOOTH

#include "BluetoothSerial.h"
BluetoothSerial SerialBt;

#endif

void setupSerial()
{
  #if USE_BLUETOOTH
  SerialBt.begin("Not-A-Supercomputer");
  #endif

  #if USE_SERIAL_PORT
  Serial.begin(BAUD_RATE);
  #endif
}

void printlnSerial(int msg)
{
  #if USE_BLUETOOTH
  SerialBt.println(msg);
  #endif

  #if USE_SERIAL_PORT
  Serial.println(msg);
  #endif
}

void printlnSerial(String msg)
{
  #if USE_BLUETOOTH
  SerialBt.println(msg);
  #endif

  #if USE_SERIAL_PORT
  Serial.println(msg);
  #endif
}

void printSerial(int msg)
{
  #if USE_BLUETOOTH
  SerialBt.print(msg);
  #endif

  #if USE_SERIAL_PORT
  Serial.print(msg);
  #endif
}

void printSerial(String msg)
{
  #if USE_BLUETOOTH
  SerialBt.print(msg);
  #endif

  #if USE_SERIAL_PORT
  Serial.print(msg);
  #endif
}

char serialRead()
{
  #if USE_SERIAL_PORT
  return Serial.read();
  #endif
  
  #if USE_BLUETOOTH
  return SerialBt.read();
  #endif
}

int serialAvailable()
{
  #if USE_SERIAL_PORT
  return Serial.available();
  #endif
  
  #if USE_BLUETOOTH
  return SerialBt.available();
  #endif
}
