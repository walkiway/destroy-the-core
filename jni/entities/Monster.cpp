/*
 * Monster.cpp
 *
 *  Created on: Feb 25, 2011
 *      Author: Ryan Maloney
 */

#include "Monster.h"

using namespace irr;
using namespace core;

Monster::Monster(CreatureDefinition* definition, position2d<s32> spawnPoint) :
  Creature(definition, spawnPoint)
{
}

Monster::~Monster()
{
}

