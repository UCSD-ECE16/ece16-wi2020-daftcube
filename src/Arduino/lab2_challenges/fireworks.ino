/*
 * FIREWORKS!
 * 
 * By Owen Bartolf
 * 
 */

#if FIREWORKS

#define DEBUG_SERIAL false

#define FRAMES_PER_SECOND 30  // Framerate
#define DELTA_TIME .0333      // 1 Second / Framerate

#define PERSISTENT_COUNT 5

#define MAX_SUBEMITTERS_PER_FIREWORK 20
#define MIN_SUBEMITTERS_PER_FIREWORK 10

#define MIN_FIREWORK_SPAWN_X 32
#define MAX_FIREWORK_SPAWN_X 96

#define MIN_FIREWORK_EXPLOSION_FORCE 1280
#define MAX_FIREWORK_EXPLOSION_FORCE 1280
#define DIVIDE_BY_FIREWORK_EXPLOSION_FORCE 100

#define MIN_FIREWORK_RELOAD_TIME 1000
#define MAX_FIREWORK_RELOAD_TIME 4000
#define DIVIDE_BY_FIREWORK_RELOAD_TIME 1000

#define MIN_SUBPARTICLE_TIME_TO_LIVE 500
#define MAX_SUBPARTICLE_TIME_TO_LIVE 1500
#define DIVIDE_BY_SUBPARTICLE_TIME_TO_LIVE 1000

#define MIN_FIREWORK_LATERAL_VELOCITY -9
#define MAX_FIREWORK_LATERAL_VELOCITY 9
#define MIN_FIREWORK_VERTICAL_VELOCITY 1280
#define MAX_FIREWORK_VERTICAL_VELOCITY 1680
#define DIVIDE_BY_FIREWORK_VERTICAL_VELOCITY 100

#define TRAIL_LENGTH 4

#define GRAVITY 4.0

struct FireworksParticle
{
  // Contains current pos + trailing pos
  float posX[TRAIL_LENGTH];
  float posY[TRAIL_LENGTH];
  int trailingParticlesCount;

  // Velocity
  float velocityX;
  float velocityY;

  // State
  int state; // 0 = flight, 1 = invisible
  float timer; // timer for waiting / invisible
  
  // Visual
  bool hasSparkle; // If we should render sparkles for sub-emitter.
};

struct FireworksParticle particles[PERSISTENT_COUNT];
struct FireworksParticle subParticles[PERSISTENT_COUNT * MAX_SUBEMITTERS_PER_FIREWORK];



/* ========================================================== */
// Main Program Logic
/* ========================================================== */

void setup()
{
  // Initialize display
  DaftDrawLib_initDisplay();

  // Initialize LEDC
  setupLightFx();

#if DEBUG_SERIAL
  Serial.begin(74880);
#endif

  // Initialize all particles
  setupFireworksAnSubParticles();
}

void loop()
{
  // Refresh screen.
  DaftDrawLib_clear();

  // Process Light Fx
  processLight();
    
  // Process and draw all particles and sub particles.
  for (int i = 0; i < PERSISTENT_COUNT; i++)
  {
    runFireworkStateMachine(i);
    serialOutFireworkState(i);
    drawFirework(i);
  }
  for (int i = 0; i < (PERSISTENT_COUNT * MAX_SUBEMITTERS_PER_FIREWORK); i++)
  {
    runSubEmitterStateMachine(i);
    drawSubParticle(i);
    
  }

  // Update the screen.
  DaftDrawLib_flush();
  
  delay(1000 / FRAMES_PER_SECOND); // 30 FPS
}

/* ========================================================== */
// LED Light FX
/* ========================================================== */

float ledTimer = 0;

#define LIGHT_FX_PIN 27
#define LIGHT_FX_FLASH_DURATION .5

#define LED_FX_CHANNEL 3
#define LED_FX_FREQUENCY 5000
#define LED_FX_PWM_BIT_RESOLUTION 8

void setupLightFx()
{
  ledcSetup(LED_FX_CHANNEL, LED_FX_FREQUENCY, LED_FX_PWM_BIT_RESOLUTION);
  ledcAttachPin(LIGHT_FX_PIN, LED_FX_CHANNEL);
  ledcAttachPin(5, LED_FX_CHANNEL);
}

// Hopefully not really...
void explodeLight()
{
  ledTimer = LIGHT_FX_FLASH_DURATION;
}

// Processes the light
void processLight()
{
  ledcWrite(LED_FX_CHANNEL, map( LIGHT_FX_FLASH_DURATION * 1000, 0, 255, 0, ((int)(ledTimer * 1000)) ));
  ledTimer -= DELTA_TIME;
  if (ledTimer <= 0)
  {
    ledTimer = 0;
  }
}

/* ========================================================== */
// Firework Logic
/* ========================================================== */

/*
 * void setupFireworksAnSubParticles()
 * 
 * Configures all particles so that they are ready for use in the rest of the program.
 */
void setupFireworksAnSubParticles()
{
  // Initialize particles
  for(int i = 0; i < PERSISTENT_COUNT; i++)
  {
    particles[i].state = 1;
    particles[i].timer = (float)random(100,3000) / 1000;
  }

  // Initialize subparticles
  for(int i = 0; i < PERSISTENT_COUNT; i++)
  {
    particles[i].state = 1;
  }
}

/* 
 *  int getIndexOfUnusedSubEmitter()
 *  
 *  Returns the index of a subemitter that is not being used at the moment.
 *  Returns -1 if no such index exists.
 */
int getIndexOfUnusedSubEmitter()
{
  // Linear search.
  for (int i = 0; i < (PERSISTENT_COUNT * MAX_SUBEMITTERS_PER_FIREWORK); i++)
  {
    // If invisible...
    if (subParticles[i].state == 1)
    {
      return i;
    }
  }

  return -1;
}

/*
 * Draws a firework going upwares.
 */
void drawFirework(int index)
{
  // If flying
  if (particles[index].state == 0)
  {
    DaftDrawLib_setPixel( floor(particles[index].posX[0]), floor(particles[index].posY[0]), true );
  }
  
}

/*
 * Draws a firework going upwares.
 */
void drawSubParticle(int index)
{
  // If flying
  if (subParticles[index].state == 0)
  {
    // Render trail
    for (int i = 1; i < TRAIL_LENGTH; i++)
    {
      DaftDrawLib_setLine( floor(subParticles[index].posX[i-1]), floor(subParticles[index].posY[i-1]), floor(subParticles[index].posX[i]), floor(subParticles[index].posY[i]), true );
    }
  }
}

void serialOutFireworkState(int index)
{
  #if DEBUG_SERIAL
  Serial.print("{ Firework ");
  Serial.print(index);
  Serial.print(", State ");
  Serial.print(particles[index].state);
  Serial.print(", Timer ");
  Serial.print(particles[index].timer);
  Serial.print(", X ");
  Serial.print(particles[index].posX[0]);
  Serial.print(", Y ");
  Serial.print(particles[index].posY[0]);
  Serial.print(", VelX ");
  Serial.print(particles[index].velocityX);
  Serial.print(", VelY ");
  Serial.print(particles[index].velocityY);
  Serial.println("}");
  #endif
}

void serialOutSubParticleState(int index)
{
  #if DEBUG_SERIAL
  Serial.print("{ SubParticle ");
  Serial.print(index);
  Serial.print(", State ");
  Serial.print(subParticles[index].state);
  Serial.print(", Timer ");
  Serial.print(subParticles[index].timer);
  Serial.print(", X ");
  Serial.print(subParticles[index].posX[0]);
  Serial.print(", Y ");
  Serial.print(subParticles[index].posY[0]);
  Serial.print(", VelX ");
  Serial.print(subParticles[index].velocityX);
  Serial.print(", VelY ");
  Serial.print(subParticles[index].velocityY);
  Serial.println("}");
  #endif
}

/*
 * 
 */
void runFireworkStateMachine(int index)
{
  // Run timer down
  particles[index].timer -= DELTA_TIME;

  switch(particles[index].state)
  {
    case 0: // Flight

      // Fly!
      moveFirework(index, false);

      // Time's up, EXPLODE!
      if (particles[index].timer <= 0)
      {
        // Set time as reload time
        particles[index].timer = (float)(random(MIN_FIREWORK_RELOAD_TIME, MAX_FIREWORK_RELOAD_TIME)) / DIVIDE_BY_FIREWORK_RELOAD_TIME;

        detonateFirework(index);
        
        // Transition state!
        particles[index].state = 1;
      }
    
      break;
    case 1: // Invisible

      // If Time's up, reload.
      if (particles[index].timer <= 0)
      {
        // Transition
        particles[index].state = 0;
  
        // CONFIGURE NEW FIREWORK
        createNewFirework(index);
      }
      
      break;
  }
}


void runSubEmitterStateMachine(int index)
{
    // Run timer down
  subParticles[index].timer -= DELTA_TIME;

  switch(subParticles[index].state)
  {
    case 0: // Flight

      // Fly!
      moveSubParticle(index, true);

      // Send State
      serialOutSubParticleState(index);

      // Time's up, dissipate!
      if (subParticles[index].timer <= 0)
      {
        
        // Transition state!
        subParticles[index].state = 1;
      }
    
      break;
    case 1: // Invisible

      // Do nothing, wait to be polled by detonation!
      
      break;
  }
}


void createNewFirework(int index)
{
  // Set trailing particle emitter count
  particles[index].trailingParticlesCount = random(MIN_SUBEMITTERS_PER_FIREWORK, MAX_SUBEMITTERS_PER_FIREWORK);

  // Reset position
  particles[index].posX[0] = (float)random(MIN_FIREWORK_SPAWN_X, MAX_FIREWORK_SPAWN_X);
  particles[index].posY[0] = (float)0;

  particles[index].velocityX = (float)random(MIN_FIREWORK_LATERAL_VELOCITY, MAX_FIREWORK_LATERAL_VELOCITY);
  particles[index].velocityY = ((float)random(MIN_FIREWORK_VERTICAL_VELOCITY, MAX_FIREWORK_VERTICAL_VELOCITY)) / DIVIDE_BY_FIREWORK_VERTICAL_VELOCITY;

  // Detonation Range is based on velocity; this calculates the detonation time for when we get to apoapsis.
  particles[index].timer = -particles[index].velocityY / (-GRAVITY) ;
  //particles[index].timer = 1000;

  particles[index].state = 0; // FLIGHT READY!
}

void detonateFirework(int index)
{
  // Detonate LED
  explodeLight();
  
  // Spawn sub-emitters
  for (int i = 0; i < particles[index].trailingParticlesCount; i++)
  {
    // Get sub-emitter.
    int subEmitterIndex = getIndexOfUnusedSubEmitter();

    // If no more are avaliable, break; we can't spawn more sub-emitters.
    if (subEmitterIndex == -1) { break; }

    // Get a random velocity angle
    float randomTheta = ((float)random(0, 6283)) / 1000;
    float randomScalar = ((float)random(MIN_FIREWORK_EXPLOSION_FORCE, MAX_FIREWORK_EXPLOSION_FORCE)) / DIVIDE_BY_FIREWORK_EXPLOSION_FORCE;

    subParticles[subEmitterIndex].velocityX = cos(randomTheta) * randomScalar;
    subParticles[subEmitterIndex].velocityY = sin(randomTheta) * randomScalar;

    // Reset trail
    for (int i = 1; i < TRAIL_LENGTH; i++)
    {
      subParticles[subEmitterIndex].posX[i] = particles[index].posX[0];
      subParticles[subEmitterIndex].posY[i] = particles[index].posX[0];
    }

    subParticles[subEmitterIndex].posX[0] = particles[index].posX[0];
    subParticles[subEmitterIndex].posY[0] = particles[index].posY[0];

    subParticles[subEmitterIndex].trailingParticlesCount = TRAIL_LENGTH;

    subParticles[subEmitterIndex].timer = (float)(random(MIN_SUBPARTICLE_TIME_TO_LIVE, MAX_SUBPARTICLE_TIME_TO_LIVE)) / DIVIDE_BY_SUBPARTICLE_TIME_TO_LIVE;

    // Fire!
    subParticles[subEmitterIndex].state = 0;
  }
}

void moveFirework(int index, bool calculateTrail)
{
  // Remember last position for trail
  float lastPosX = particles[index].posX[0];
  float lastPosY = particles[index].posY[0];
  
  // Acceleration!
  particles[index].velocityY -= (GRAVITY * DELTA_TIME); // GRAVITY ACCELERATION IN M/S^2!

  // Translation!
  particles[index].posX[0] += particles[index].velocityX * DELTA_TIME;
  particles[index].posY[0] += particles[index].velocityY * DELTA_TIME;
  
  if (calculateTrail)
  {
    for (int i = 1; i < particles[index].trailingParticlesCount; i++)
    {
      // Save for swap
      float toSwapX = particles[index].posX[i];
      float toSwapY = particles[index].posY[i];

      // Store previous values in this node.
      particles[index].posX[i] = lastPosX;
      particles[index].posY[i] = lastPosY;

      lastPosX = toSwapX;
      lastPosY = toSwapY;
    }
  }
}

void moveSubParticle(int index, bool calculateTrail)
{
  // Remember last position for trail
  float lastPosX = subParticles[index].posX[0];
  float lastPosY = subParticles[index].posY[0];
  
  // Acceleration!
  subParticles[index].velocityY -= (GRAVITY * 2 * DELTA_TIME); // GRAVITY ACCELERATION IN M/S^2!

  // Translation!
  subParticles[index].posX[0] += subParticles[index].velocityX * DELTA_TIME;
  subParticles[index].posY[0] += subParticles[index].velocityY * DELTA_TIME;
  
  if (calculateTrail)
  {
    for (int i = 1; i < subParticles[index].trailingParticlesCount; i++)
    {
      // Save for swap
      float toSwapX = subParticles[index].posX[i];
      float toSwapY = subParticles[index].posY[i];

      // Store previous values in this node.
      subParticles[index].posX[i] = lastPosX;
      subParticles[index].posY[i] = lastPosY;

      lastPosX = toSwapX;
      lastPosY = toSwapY;
    }
  }
}

/* ========================================================== */
// Math
/* ========================================================== */

#define EPSILON .001

/* almostEquals
 * 
 * Returns true if the difference between the two non-precise floating point values is
 * within an arbitrary epsilon of equality.
 */
float almostEquals(float a, float b)
{
  return abs(a - b) < EPSILON;
}

#endif
