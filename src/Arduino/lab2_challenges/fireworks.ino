/*
 * FIREWORKS!
 * 
 * By Owen Bartolf
 * 
 */

#if FIREWORKS

#define FRAMES_PER_SECOND 30  // Framerate
#define DELTA_TIME .0333      // 1 Second / Framerate

#define PERSISTENT_COUNT 4

#define MAX_SUBEMITTERS_PER_FIREWORK 10
#define MIN_SUBEMITTERS_PER_FIREWORK 5

#define MIN_FIREWORK_SPAWN_X 0
#define MAX_FIREWORK_SPAWN_X 128

#define MIN_FIREWORK_RELOAD_TIME 250
#define MAX_FIREWORK_RELOAD_TIME 1000
#define DIVIDE_BY_FIREWORK_RELOAD_TIME 1000

#define MIN_SUBPARTICLE_TIME_TO_LIVE 500
#define MAX_SUBPARTICLE_TIME_TO_LIVE 1500
#define DIVIDE_BY_SUBPARTICLE_TIME_TO_LIVE 1000

#define MIN_FIREWORK_LATERAL_VELOCITY -5
#define MAX_FIREWORK_LATERAL_VELOCITY 5
#define MIN_FIREWORK_VERTICAL_VELOCITY 24
#define MAX_FIREWORK_VERTICAL_VELOCITY 41

#define TRAIL_LENGTH 10

#define GRAVITY -.8

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
  int timer; // timer for waiting / invisible
  
  // Visual
  bool hasSparkle; // If we should render sparkles for sub-emitter.
};

struct FireworksParticle particles[PERSISTENT_COUNT];
struct FireworksParticle subParticles[PERSISTENT_COUNT * MAX_SUBEMITTERS_PER_FIREWORK];

/* ========================================================== */
// Clock
/* ========================================================== */



/* ========================================================== */
// Main Program Logic
/* ========================================================== */

void setup()
{
  // Initialize all particles
}

void loop()
{

  
  delay(1000 / FRAMES_PER_SECOND); // 30 FPS
}



/* ========================================================== */
// Firework Logic
/* ========================================================== */

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
  particles[index].velocityY = (float)random(MIN_FIREWORK_LATERAL_VELOCITY, MAX_FIREWORK_LATERAL_VELOCITY);

  // Detonation Range is based on velocity; this calculates the detonation time for when we get to apoapsis.
  particles[index].timer = -particles[index].velocityY / (GRAVITY) ;

  particles[index].state = 0; // FLIGHT READY!
}

void detonateFirework(int index, float posX, float posY)
{
  // Spawn sub-emitters
  for (int i = 0; i < particles[index].trailingParticlesCount; i++)
  {
    // Get sub-emitter.
    int subEmitterIndex = getIndexOfUnusedSubEmitter();

    // If no more are avaliable, break; we can't spawn more sub-emitters.
    if (subEmitterIndex == -1) { break; }

    // Get a random velocity angle
    float randomTheta = random(0, 6283) / 1000;
    float randomScalar = (float)random(MIN_FIREWORK_LATERAL_VELOCITY, MAX_FIREWORK_LATERAL_VELOCITY);

    subParticles[i].velocityX = cos(randomTheta) * randomScalar;
    subParticles[i].velocityY = sin(randomTheta) * randomScalar;

    // Reset trail
    for (int i = 0; i < TRAIL_LENGTH; i++)
    {
      subParticles[i].posX = 0;
      subParticles[i].posY = 0;
    }

    subParticles[i].posX = posX;
    subParticles[i].posY = posY;

    subParticles[i].trailingParticlesCount = TRAIL_LENGTH;

    subParticles[i].timer = (float)(random(MIN_SUBPARTICLE_TIME_TO_LIVE, MAX_SUBPARTICLE_TIME_TO_LIVE)) / DIVIDE_BY_SUBPARTICLE_TIME_TO_LIVE;

    // Fire!
    subParticles[i].state = 0;
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
  subParticles[index].velocityY -= (GRAVITY * DELTA_TIME); // GRAVITY ACCELERATION IN M/S^2!

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
