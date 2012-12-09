/*
 * Monster.h
 *
 *  Created on: Feb 25, 2011
 *      Author: Ryan Maloney
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include "Creature.h"
#include <irrlicht.h>

class Monster: public Creature
{
public:
  Monster(CreatureDefinition* definition,
      irr::core::position2d<irr::s32> spawnPoint);
  virtual ~Monster();
};

#endif /* MONSTER_H_ */
