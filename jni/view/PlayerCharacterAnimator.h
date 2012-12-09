/*
 * PlayerCharacterAnimator.h
 *
 *  Created on: Jan 20, 2011
 *      Author: ryan
 */

#ifndef PLAYERCHARACTERANIMATOR_H_
#define PLAYERCHARACTERANIMATOR_H_
#include <irrlicht.h>
#include "entities/PlayerCharacter.h"
#include "util/CoordinateTranslator.h"

class PlayerCharacterAnimator: public irr::scene::ISceneNodeAnimator
{
public:
  PlayerCharacterAnimator(PlayerCharacter*, CoordinateTranslator*);

  virtual ~PlayerCharacterAnimator();

  virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);

  virtual irr::scene::ISceneNodeAnimator* createClone(
      irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);

private:
  PlayerCharacter* pc;
  CoordinateTranslator* coordinateTranslator;
};

#endif /* PLAYERCHARACTERANIMATOR_H_ */
