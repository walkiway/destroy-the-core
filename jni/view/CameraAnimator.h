/*
 * CameraAnimator.h
 *
 *  Created on: Jan 21, 2011
 *      Author: Ryan Maloney
 */

#ifndef CAMERAANIMATOR_H_
#define CAMERAANIMATOR_H_

#include <ISceneNodeAnimator.h>
#include <irrlicht.h>
#include "entities/PlayerCharacter.h"
#include "util/CoordinateTranslator.h"

class CameraAnimator: public irr::scene::ISceneNodeAnimator
{
public:
  CameraAnimator(irr::core::vector3df cameraPosition, int cameraHeight,
      int cameraWidth, int mapHeight, int mapWidth, PlayerCharacter* pc,
      CoordinateTranslator* ct);
  virtual ~CameraAnimator();
  virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
  virtual irr::scene::ISceneNodeAnimator* createClone(
      irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
  virtual bool isEventReceiverEnabled() const;
  virtual irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const;
  virtual bool hasFinished(void) const;

private:
  irr::core::position2d<irr::s32> position;
  PlayerCharacter* pc;
  CoordinateTranslator* ct;
  float zAxis;
  int cameraHeight;
  int cameraWidth;
  int mapHeight;
  int mapWidth;
  irr::core::position2d<irr::s32> cameraTiles;
  int widthOffset;
  int heightOffset;
  bool cameraTilesCalculated;
};

#endif /* CAMERAANIMATOR_H_ */
