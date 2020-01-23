#if SERIAL_READ
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)
  {
    //char incomingChar = Serial.read();
    //Serial.print(incomingChar);

    int incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
#endif
