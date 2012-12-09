/*
 * MonsterAnimator.h
 *
 *  Created on: Feb 25, 2011
 *      Author: Ryan Maloney
 */

#ifndef MONSTERANIMATOR_H_
#define MONSTERANIMATOR_H_

#include <ISceneNodeAnimator.h>
#include "entities/Monster.h"
#include <irrlicht.h>
#include "util/CoordinateTranslator.h"

class MonsterAnimator: public irr::scene::ISceneNodeAnimator
{
public:
  MonsterAnimator(Monster*, CoordinateTranslator*);
  virtual ~MonsterAnimator();
  virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
  virtual irr::scene::ISceneNodeAnimator* createClone(
      irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
private:
  Monster* monster;
  CoordinateTranslator* coordinateTranslator;
};

#endif /* MONSTERANIMATOR_H_ */
