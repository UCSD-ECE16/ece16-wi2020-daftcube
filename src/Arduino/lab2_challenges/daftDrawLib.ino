#include <Wire.h> 
#include "U8x8lib.h"

#define OLED_RESET 4 // this value resets the OLED

#define SCREEN_TILE_WIDTH 16
#define SCREEN_TILE_HEIGHT 4

#define SCREEN_PIXEL_WIDTH 128
#define SCREEN_PIXEL_HEIGHT 32

#define SINGLETILE_PIXEL_WIDTH 8
#define SINGLETILE_PIXEL_HEIGHT 8

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(OLED_RESET);

/****************************************************************/
// Variables
/****************************************************************/

// Buffers use pixel widths because the u8x8 represents the vertical units of each
// column as the bits packed into a single uint8_t.
uint8_t screenBuffer[SCREEN_TILE_HEIGHT][SCREEN_PIXEL_WIDTH];
uint8_t pendingFlushBuffer[SCREEN_TILE_HEIGHT][SCREEN_PIXEL_WIDTH];

/****************************************************************/
// Main Functions
/****************************************************************/

/*
 * void DaftDrawLib_initDisplay()
 * 
 * Conducts all initialization tasks for the given screen.
 */
void DaftDrawLib_initDisplay()
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setCursor(0, 0);
}

/*
 * DaftDrawLib_setLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
 * 
 * Sets all of the pixels in the line from (x0, y0) to (x1, y1) to the given state.
 * 
 * An implementation of the Bresenham's Line Algorithm. Implemented from pseudocode on Wikipedia.
 */
void DaftDrawLib_setLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, bool onState)
{
  if (abs(y1 - y0) < abs(x1 - x0))
  {
    if (x0 > x1)
    {
      DaftDrawLib_setLine_low(x1, y1, x0, y0, onState);
    }
    else
    {
      DaftDrawLib_setLine_low(x0, y0, x1, y1, onState);
    }
  }
  else
  {
    if (y0 > y1)
    {
      DaftDrawLib_setLine_high(x1, y1, x0, y0, onState);
    }
    else
    {
      DaftDrawLib_setLine_high(x0, y0, x1, y1, onState);
    }
  }
}

void DaftDrawLib_setLine_low(int16_t x0, int16_t y0, int16_t x1, int16_t y1, bool onState)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  
  // Flip for negative grade.
  if (dy < 0)
  {
    yi = -1;
    dy = -dy;
  }

  float D = 2*dy - dx;
  int y = y0;

  for (int x = x0; x <= x1; x++)
  {
    DaftDrawLib_setPixel(x, y, onState);

    if (D > 0)
    {
      y = y + yi;
      D = D - 2*dx;
    }

    D = D + 2*dy;
  }
}

void DaftDrawLib_setLine_high(int16_t x0, int16_t y0, int16_t x1, int16_t y1, bool onState)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  
  // Flip for negative grade.
  if (dx < 0)
  {
    xi = -1;
    dx = -dx;
  }

  float D = 2*dx - dy;
  int x = x0;

  for (int y = y0; y <= y1; y++)
  {
    DaftDrawLib_setPixel(x, y, onState);

    if (D > 0)
    {
      x = x + xi;
      D = D - 2*dy;
    }

    D = D + 2*dx;
  }
}

/*
 * DaftDrawLib_setPixel(uint8_t x, uint8_t y, bool onState)
 * 
 * If the pixel lies out of the defined bounds, the change will not be
 * rendered.
 */
void DaftDrawLib_setPixel(uint8_t x, uint8_t y, bool onState)
{
  // Only render stuff that is in bounds.
  if (
    x < 0 || SCREEN_PIXEL_WIDTH <= x ||
    y < 0 || SCREEN_PIXEL_HEIGHT <= y
  )
  {
    return;
  }

  // Create the byte that represents our change. We can accomplish this by shifting 1
  //

  uint8_t delta = 1 << (y % SINGLETILE_PIXEL_HEIGHT);
  

  // Calculate the entry to modify in screen space.
  // We convert y in screen coordinates t
  if (onState)
  {
    // For turning on a pixel, OR ensures all data + new data is consistent.
    pendingFlushBuffer[DaftDrawLib_ScreenToTileCoordinateY(y)][x] |= delta;
  }
  else
  {
    pendingFlushBuffer[DaftDrawLib_ScreenToTileCoordinateY(y)][x] ^= delta;
  }
}

/*
 * void DaftDrawLib_clear()
 * 
 * Resets every pixel on the screen to its off state. Does not flush, however.
 */
void DaftDrawLib_clear()
{
  // Reset every pixel.
  for(uint8_t yTile = 0; yTile < SCREEN_TILE_HEIGHT; yTile++)
  {
    for(uint8_t xScreen = 0; xScreen < SCREEN_PIXEL_WIDTH; xScreen++)
    {
      pendingFlushBuffer[yTile][xScreen] = 0;
    }
  }
}

/*
 * void DaftDrawLib_flush()
 * 
 * Flushes all of the pending changes to the OLED screen.
 * Optimizes the flushed info so that only tiles that changed are updated,
 * increasing performance.
 */
void DaftDrawLib_flush()
{
  for(uint8_t yTile = 0; yTile < SCREEN_TILE_HEIGHT; yTile++)
  {
    for(uint8_t xScreen = 0; xScreen < SCREEN_PIXEL_WIDTH; xScreen += 8)
    {
      bool hasChanged = false;
      
      // Scan each row, column by column for changes. If even one column has changed, the tile has changed.
      for(uint8_t b = 0; b < 8; b++)
      {
        // Cache x coordinate
        uint8_t xCoord = xScreen + b;
        
        if (pendingFlushBuffer[yTile][xCoord] != screenBuffer[yTile][xCoord])
        {
          hasChanged = true;
          screenBuffer[yTile][xCoord] = pendingFlushBuffer[yTile][xCoord];
        }
      }

      // If this tile changed, push the actual change to the u8x8.
      if (hasChanged)
      {
        /*
        Serial.print("Has Changed: ");
        Serial.print(xScreen);
        Serial.print(" ");
        Serial.println(yTile);
        */
        
        uint8_t bufferToWrite[8] = {
          screenBuffer[yTile][xScreen],
          screenBuffer[yTile][xScreen + 1],
          screenBuffer[yTile][xScreen + 2],
          screenBuffer[yTile][xScreen + 3],
          screenBuffer[yTile][xScreen + 4],
          screenBuffer[yTile][xScreen + 5],
          screenBuffer[yTile][xScreen + 6],
          screenBuffer[yTile][xScreen + 7]
        };

        u8x8.drawTile(DaftDrawLib_ScreenToTileCoordinateX(xScreen), yTile, 1, bufferToWrite);
      }
    }
  }
}

/****************************************************************/
// Math Functions
/****************************************************************/

/*
 * uint8_t DaftDrawLib_ScreenToTileCoordinateX(uint8_t tileCoordinateX)
 * 
 * Returns the tile coordinate that the given screen coordinate lies on.
 */
uint8_t DaftDrawLib_ScreenToTileCoordinateX(uint8_t screenCoordinateX)
{
  return screenCoordinateX / SINGLETILE_PIXEL_WIDTH;
}

/*
 * uint8_t DaftDrawLib_ScreenToTileCoordinateY(uint8_t tileCoordinateY)
 * 
 * Returns the tile coordinate that the given screen coordinate lies on.
 */
uint8_t DaftDrawLib_ScreenToTileCoordinateY(uint8_t screenCoordinateY)
{
  return screenCoordinateY / SINGLETILE_PIXEL_HEIGHT;
}


/*
 * uint8_t DaftDrawLib_TileToScreenCoordinateX(uint8_t screenCoordinateX)
 * 
 * Returns the screen coordinate that the given tile coordinate lies on.
 */
 uint8_t DaftDrawLib_TileToScreenCoordinateX(uint8_t tileCoordinateX)
{
  return tileCoordinateX * SINGLETILE_PIXEL_WIDTH;
}

/*
 * uint8_t DaftDrawLib_TileToScreenCoordinateX(uint8_t screenCoordinateX)
 * 
 * Returns the screen coordinate that the given tile coordinate lies on.
 */
 uint8_t DaftDrawLib_TileToScreenCoordinateY(uint8_t tileCoordinateY)
{
  return tileCoordinateY * SINGLETILE_PIXEL_HEIGHT;
}
