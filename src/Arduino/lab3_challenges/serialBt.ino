#define USE_BLUETOOTH false
#define USE_SERIAL_PORT true
#define BAUD_RATE 115200

#if USE_BLUETOOTH

#include "BluetoothSerial.h"
BluetoothSerial SerialBt;

#endif

void setupSerial()
{
  #if USE_BLUETOOTH
  SerialBt.begin(BAUD_RATE);
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
  SerialBt.println(msg);
  #endif

  #if USE_SERIAL_PORT
  Serial.println(msg);
  #endif
}
