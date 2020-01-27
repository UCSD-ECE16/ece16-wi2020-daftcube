#if FADING_BUZZER

// setting PWM properties
const int pwmFrequency = 5000;
const int pwmChannel = 3;
const int pwmBitResolution = 8;

// MOTOR VARs
int motorPin = 5;

void setup()
{
  setupMotor();
  DaftDrawLib_initDisplay();
  Serial.begin(9600);
  
}

int pixelX = 0;
int pixelY = 0;
bool state = true;

void loop()
{
  for(int x = 0; x < 128; x++)
  {
    for(int y = 0; y < SCREEN_PIXEL_HEIGHT; y++)
    {    
      DaftDrawLib_setPixel(x, y, state);
      DaftDrawLib_flush();
    }
    
  }

  Serial.println("Flipping state!");
  state = !state;
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
