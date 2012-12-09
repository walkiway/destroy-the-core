/*
 * PlayerCharacter.cpp
 *
 *  Created on: Jan 20, 2011
 *      Author: Ryan Maloney
 */

#define LOG_TAG "PlayerCharacter"
#include "PlayerCharacter.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;

PlayerCharacter::PlayerCharacter(CreatureDefinition* definition,
    position2d<s32> spawnPoint) :
  Creature(definition, spawnPoint)
{
}

PlayerCharacter::~PlayerCharacter()
{
}
