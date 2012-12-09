/*
 * CoordinateTranslator.cpp
 *
 *  Created on: Jan 20, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "CoordinateTranslator"
#include "CoordinateTranslator.h"
#include "util/LoggingMacros.h"
#include <math.h>

using namespace irr;
using namespace core;

CoordinateTranslator::CoordinateTranslator(HexTile* hexTile)
{
  if (NULL != hexTile)
  {
    LOGV("HexTile information[R: %f, H: %f, SideLength: %f]", hexTile->GetR(), hexTile->GetH(), hexTile->GetSideLength());
    r = hexTile->GetR();
    h = hexTile->GetH();
    sideLength = hexTile->GetSideLength();
    tileHeight = hexTile->GetHeight();
    tileWidth = hexTile->GetWidth();
  }
}

CoordinateTranslator::~CoordinateTranslator()
{
  // TODO Auto-generated destructor stub
}

vector3df CoordinateTranslator::TranslateMapCoords(position2d<s32> mapCoord,
    float height)
{
  LOGD("About to translate values for tile with width %f and height %f. h is %f", tileWidth, tileHeight, h);

  bool isInEvenRow = (mapCoord.Y % 2 == 0) ? true : false;
  float ulWorldX = 0.0;
  float ulWorldY = 0.0;

  if (isInEvenRow)
  {
    ulWorldX = (mapCoord.X * 1.0) * tileWidth;
  }
  else
  {

    ulWorldX = ((mapCoord.X * 1.0) * tileWidth) + r;
  }

  ulWorldY = (-1.0 * mapCoord.Y) * (tileHeight - h);

  LOGD("Translated map coordinate (%d, %d) to screen (%f, %f %f)", mapCoord.X, mapCoord.Y, ulWorldX, ulWorldY, height);

  return vector3df(ulWorldX, ulWorldY, height);
}

position2d<s32> CoordinateTranslator::TranslateScreenCoords(f32 x, f32 y)
{
  position2d<s32> arrayCoord;

  arrayCoord.X = (x + 32.0f) / tileWidth;
  arrayCoord.Y = (-1 * y) / (tileHeight - h); //y axis is inverted
  LOGE("Array coord detected as (%d, %d) before correction.", arrayCoord.X, arrayCoord.Y);

  //Calculating the relative x position requires first finding wherein the specific tile
  //the click would fall IF the map's upper left corner was flush with 0,0 in the world.
  //This is not the case as 0,0 falls in the middle of the tile so the relative X
  //must be shifted left by r. In fact, this situation is made more complicated by the fact that
  //for compliance with opengl ES the texture containing each tile is sized up to the next greatest
  //power of 2 which is at present set to 64. So we first need to shift our calculation by 32 - r
  //TODO If tile sizes change and disrupt this number FIX
  float sectionRelativeXPixel = 32.0f - fabs(x - (arrayCoord.X * tileWidth));
  float sectionRelativeYPixel = 32.0f - fabs(
      y - (arrayCoord.Y * (tileHeight - h) * -1.0));

  LOGE("World point of click: (%f, %f)", x, y);
  LOGE("Section relative pixel coords (%f, %f)", sectionRelativeXPixel, sectionRelativeYPixel);

  //This is the slope of the top two sides of the hexagon tile.
  float hexGradient = h / r;

  bool isInEvenRow = (arrayCoord.Y % 2 == 0) ? true : false;
  if (isInEvenRow)
  {
    //We know the map coordinate affected so now we are dealing with a tile
    //on an even row.  The hex will not be fully inscribed within this area
    //instead it will look like this:
    // ____
    // |/\|
    // |  |
    // ----
    //This means the hit box has dimensions of width = tile width and height = (h + sidelength)
    //The task, then, is to identify where the relative coordinates calculated above fall within this hit box.
    //If they are in the upper left or right they belong
    //1) If it falls into the bottom area of the section we are checking. If so we have the right coordinate.
    //2) If it falls in the upper left area of the section check to see if it is within the current hex.
    //If not, it belongs to a hex that is one row up and one column to the left.
    //3) If it falls in the upper right area of the section see if it is within the current hex.
    //If not, it belongs to a hex that is one row up and but within the same column.

    //To accomplish this, calculate the maximum y value for the x that will still be contained
    //in the main hex.
    LOGE("Comparing %f with %f.  h is %f and hexGradient is %f",sectionRelativeYPixel, (h - sectionRelativeXPixel * hexGradient), h, hexGradient);
    if (sectionRelativeXPixel >= r / 2)
    {
      //We are on the right side of the hit box. The hit box is the upper right corner of the hit tile
      //already identified and has dimensions r x h. In order to determine the value of y for the
      //specified x use y = mx + b. Assume b is 0 as the top of the hexagon represent 0,0 and multiply
      //it by the value of the sectionRelativeXPixel halved (we are only considering one side of the hexagon at a time)
      //If greater, is it on other tile, if less than or equal consider it to be on the existing tile.
      if (sectionRelativeYPixel < ((sectionRelativeXPixel / 2) * hexGradient))
      {
        LOGE("'A' row, upper right hit detected, changing array coords from (%d x %d) to (%d x %d).", arrayCoord.X, arrayCoord.Y, arrayCoord.X, arrayCoord.Y - 1);
        arrayCoord.Y--;
      }
      else
      {
        LOGE("'A' row, lower half detected, not changing array coords (%d x %d)", arrayCoord.X, arrayCoord.Y);
      }
    }
    else
    {
      //For this calculation, the origin is still at the top of the hexagon so this means the line
      //starts at the point whre the upper left side and the left side meet and
      //now crosses the y axis at h so our y = mx + b so our equation is now, for a given X, y = -1*gradient*sectionRelativeX + h.
      if (sectionRelativeYPixel < ((-1 * hexGradient * sectionRelativeXPixel) + h))
      {
        LOGE("'A' row, upper left hit detected, changing array coords from (%d x %d) to (%d x %d).", arrayCoord.X, arrayCoord.Y, arrayCoord.X - 1, arrayCoord.Y - 1);
        arrayCoord.X--;
        arrayCoord.Y--;
      }
      else
      {
        LOGE("'A' row, lower half detected, not changing array coords (%d x %d)", arrayCoord.X, arrayCoord.Y);
      }
    }
  }
  else
  {
    //Otherwise it looks like the following.  If it is in the right section, the calculated array coords are accurate.
    //If it is in the left, subtract one from x, otherwise subtract one from y.
    //    _____
    //    |\ /|
    //    | | |
    //    | | |
    //    -----
    if (sectionRelativeXPixel > r)
    {
      LOGE("'B' type hit, on the right side as %f is greater than %f", sectionRelativeXPixel, r);
      //Left Side
      if (sectionRelativeYPixel < (2 * h - sectionRelativeXPixel - hexGradient))
      {
        LOGE("'B' type hit is on the upper right as %f is less than %f", sectionRelativeYPixel, (2 * h - sectionRelativeXPixel - hexGradient));
        //Top right
        arrayCoord.Y--;
      }
      else
      {
        //Bottom right.  Leave values as is.
        LOGE("'B' type hit is on the bottom right as %f is greater than %f", sectionRelativeYPixel, (2 * h - sectionRelativeXPixel - hexGradient));
      }
    }
    else
    {
      LOGE("'B' type hit, on the left side as %f is less than %f", sectionRelativeXPixel, r);
      //Right Side
      if (sectionRelativeYPixel < (sectionRelativeXPixel * hexGradient))
      {
        //Top left
        arrayCoord.Y--;
      }
      else
      {
        //Bottom left
        arrayCoord.X--;
      }
    }
  }

  return arrayCoord;
}

position2d<s32> CoordinateTranslator::CalculateTilesInCameraView(
    int cameraWidth, int cameraHeight)
{
  int tileWidths = (cameraWidth / (2.0 * r));
  int tileHeights = (cameraHeight / ((2.0 * h) + sideLength));

  return position2d<s32> (tileWidths, tileHeights);
}
