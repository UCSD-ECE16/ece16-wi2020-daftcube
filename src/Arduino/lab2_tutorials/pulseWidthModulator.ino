#if PULSE_WIDTH_MODULATOR


// setting PWM properties
const int pwmFrequency = 5000;
const int pwmChannel = 0;
const int pwmBitResolution = 8;

void setup()
{
  // configure PWM functionalities
  ledcSetup(pwmChannel, pwmFrequency, pwmBitResolution);
    
  // attach the pwmChannel to the outputGPIO to be controlled
  ledcAttachPin(LED_BUILTIN, pwmChannel);
}

void loop()
{
  delay(100);
  ledcWrite(pwmChannel, 0);//ledcWrite will write the value to the pwmChannel
  delay(100);
  ledcWrite(pwmChannel, 127);
  delay(100);
  ledcWrite(pwmChannel, 255);
  delay(100);
  ledcWrite(pwmChannel, 127);
}

#endif
