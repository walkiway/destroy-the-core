/*
 * PlayerCharacter.h
 *
 *  Created on: Jan 20, 2011
 *      Author: Ryan Maloney
 */

#ifndef PLAYERCHARACTER_H_
#define PLAYERCHARACTER_H_

#include "Creature.h"
#include <irrlicht.h>

class PlayerCharacter: public Creature
{
public:
  PlayerCharacter(CreatureDefinition* definition, irr::core::position2d<
      irr::s32> spawnPoint);
  virtual ~PlayerCharacter();
};

#endif /* PLAYERCHARACTER_H_ */
