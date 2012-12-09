/*
 * CameraAnimator.cpp
 *
 *  Created on: Jan 21, 2011
 *      Author: Ryan Maloney
 */

#define LOG_TAG "CameraAnimator"
#include "CameraAnimator.h"
#include "util/LoggingMacros.h"
#include "util/CoordinateTranslator.h"

using namespace irr;
using namespace core;
using namespace scene;

CameraAnimator::CameraAnimator(vector3df spawnPoint, int cameraHeight,
    int cameraWidth, int mapHeight, int mapWidth, PlayerCharacter* player,
    CoordinateTranslator* coordTrans) :
  pc(player), ct(coordTrans)
{
  this->cameraHeight = cameraHeight;
  this->cameraWidth = cameraWidth;
  this->mapHeight = mapHeight;
  this->mapWidth = mapWidth;
  position.X = spawnPoint.X;
  position.Y = spawnPoint.Y;
  zAxis = spawnPoint.Z;
  cameraTilesCalculated = false;
}

CameraAnimator::~CameraAnimator()
{

}

ISceneNodeAnimator* CameraAnimator::createClone(ISceneNode* node,
    ISceneManager* newManager)
{
  return new CameraAnimator(vector3df(position.X, position.Y, zAxis),
      cameraHeight, cameraWidth, mapHeight, mapWidth, pc, ct);
}

void CameraAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
  ICameraSceneNode* camera = static_cast<ICameraSceneNode*> (node);
  if (NULL != camera)
  {
    int x = pc->GetPosition().X;
    int y = pc->GetPosition().Y;

    vector3df newPos = ct->TranslateMapCoords(position2d<s32> (x, y), zAxis);
    camera->setPosition(newPos);

    //Reset z depth to zero for target.
    //TODO: This is hardcoded at -1, make this configurable on creature class.
    newPos.Z = -1.0;
    camera->setTarget(newPos);
    camera->updateAbsolutePosition();
  }
}

bool CameraAnimator::isEventReceiverEnabled() const
{
  return false;
}

ESCENE_NODE_ANIMATOR_TYPE CameraAnimator::getType() const
{
  return ESNAT_UNKNOWN;
}

bool CameraAnimator::hasFinished(void) const
{
  return false;
}
