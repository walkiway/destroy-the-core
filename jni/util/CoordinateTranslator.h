/*
 * CoordinateTranslator.h
 *
 *  Created on: Jan 20, 2011
 *      Author: Ryan Maloney
 */

#ifndef COORDINATETRANSLATOR_H_
#define COORDINATETRANSLATOR_H_
#include <irrlicht.h>
#include "world/HexTile.h"

class CoordinateTranslator
{
public:
  CoordinateTranslator(HexTile*);
  virtual ~CoordinateTranslator();
  irr::core::vector3df TranslateMapCoords(irr::core::position2d<irr::s32>,
      float);
  irr::core::position2d<irr::s32> TranslateScreenCoords(irr::f32 x, irr::f32 y);
  irr::core::position2d<irr::s32> CalculateTilesInCameraView(int cameraWidth, int cameraHeight);
private:
  float r;
  float h;
  float sideLength;
  float tileWidth;
  float tileHeight;
};

#endif /* COORDINATETRANSLATOR_H_ */
