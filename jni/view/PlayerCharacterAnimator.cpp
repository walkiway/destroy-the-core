/*
 * PlayerCharacterAnimator.cpp
 *
 *  Created on: Jan 20, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "PlayerCharacterAnimator"
#include "PlayerCharacterAnimator.h"
#include "entities/PlayerCharacter.h"
#include "util/LoggingMacros.h"
#include "util/CoordinateTranslator.h"

using namespace irr;
using namespace core;
using namespace scene;

PlayerCharacterAnimator::PlayerCharacterAnimator(PlayerCharacter* playerChar,
    CoordinateTranslator* ct) :
  pc(playerChar), coordinateTranslator(ct)
{
}

PlayerCharacterAnimator::~PlayerCharacterAnimator()
{

}

ISceneNodeAnimator* PlayerCharacterAnimator::createClone(ISceneNode* node,
    ISceneManager* newManager)
{
  return new PlayerCharacterAnimator(pc, coordinateTranslator);
}

void PlayerCharacterAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
  if (pc->IsAlive())
  {
    node->setPosition(coordinateTranslator->TranslateMapCoords(
        pc->GetPosition(), node->getPosition().Z));
  }
  else
  {  }
}
