#if FADING_BUZZER

// setting PWM properties
const int pwmFrequency = 5000;
const int pwmChannel = 3;
const int pwmBitResolution = 8;

// MOTOR VARs
int motorPin = 5;
int accelZ = A0;

void setup()
{
  setupMotor();
  DaftDrawLib_initDisplay();
  Serial.begin(9600);
}

void loop()
{
  buzzMotor(255);
  delay(1000);
  buzzMotor(127);
  delay(1000);
  buzzMotor(0);
  delay(1000);
}

// ========== Motor Code =========//

void setupMotor(){
  ledcSetup(pwmChannel, pwmFrequency, pwmBitResolution);
  ledcAttachPin(motorPin, pwmChannel);
  ledcAttachPin(LED_BUILTIN, pwmChannel);
}

void buzzMotor(int buzzPower){
  ledcWrite(pwmChannel, buzzPower);
}


#endif
