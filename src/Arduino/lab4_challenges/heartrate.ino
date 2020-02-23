

MAX30105 particleSensor;
int HR_Data;

//Setup to sense a nice looking saw tooth on the plotter
byte ledBrightness = 37; //Options: 0=Off to 255=50mA
byte sampleAverage = 2; //Options: 1, 2, 4, 8, 16, 32
byte ledMode = 1; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
int sampleRate = 3200; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
int pulseWidth = 411; //Options: 69, 118, 215, 411
int adcRange = 4096; //Options: 2048, 4096, 8192, 16384 (12 BITS)

void setupHR(){
  // Initialize sensor
  // Don’t need to include the plotting part of the code
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}

void readHR() {
  HR_Data = particleSensor.getRed();//get IR pulse data
}

int getHR()
{
  return HR_Data;
}
