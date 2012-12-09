/*
 * MonsterAnimator.cpp
 *
 *  Created on: Feb 25, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "MonsterAnimator"

#include "MonsterAnimator.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;
using namespace scene;

MonsterAnimator::MonsterAnimator(Monster* monster, CoordinateTranslator* ct) :
  monster(monster), coordinateTranslator(ct)
{
}

MonsterAnimator::~MonsterAnimator()
{
}

ISceneNodeAnimator* MonsterAnimator::createClone(ISceneNode* node,
    ISceneManager* newManager)
{
  return new MonsterAnimator(monster, coordinateTranslator);
}

void MonsterAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
  if (monster->IsAlive())
  {
    node->setPosition(coordinateTranslator->TranslateMapCoords(monster->GetPosition(), node->getPosition().Z));
  }
  else
  {
    LOGE("MONSTER IS DEAD");
  }
}
