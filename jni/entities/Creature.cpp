/*
 * Creature.cpp
 *
 *  Created on: Jan 13, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "Creature"

#include "Creature.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;

Creature::Creature(CreatureDefinition* definition,
    position2d<irr::s32> spawnPoint) :
  spawnPoint(spawnPoint), position(spawnPoint)
{
  name = definition->GetName();
  width = definition->GetWidth();
  height = definition->GetHeight();
  worldName = definition->GetWorldName();
  atlasIndex = definition->GetAtlasIndex();
  indexLength = definition->GetIndexLength();
  lifeMeter = definition->GetLifeMeter();
  maxLifeMeter = definition->GetMaxLifeMeter();
}

Creature::~Creature()
{
  // TODO Auto-generated destructor stub
}

stringc Creature::GetTextureName()
{
  stringc fullyQualifiedTileName(worldName);
  fullyQualifiedTileName.append("-");
  fullyQualifiedTileName.append(name);

  //If this tile has more than one potential graphic,
  //the texture name will be qualified by its offset
  //where 0 coutns as a valid offset.
  if (indexLength > 1)
  {
    char spriteIndexOffset[5];
    sprintf(spriteIndexOffset, "%d", atlasIndexOffset);
    fullyQualifiedTileName.append("-");
    fullyQualifiedTileName.append(spriteIndexOffset);
    LOGD("Fully qualified name has been adjusted for offset %s",
        fullyQualifiedTileName.c_str());
  }

  return fullyQualifiedTileName;
}

int Creature::GetAttackPower(void)
{
  return 1;
}

int Creature::GetDefensePower(void)
{
  return 0;
}

void Creature::IncreaseLifeMeter(int value)
{
  lifeMeter += value;
}

void Creature::DecreaseLifeMeter(int value)
{
  lifeMeter -= value;
}

int Creature::GetLifeMeter()
{
  return lifeMeter;
}

int Creature::GetMaxLifeMeter()
{
  return maxLifeMeter;
}

bool Creature::IsAlive(void)
{
  return (lifeMeter > 0);
}

void Creature::SetSpawnPoint(position2d<s32> point)
{
  this->spawnPoint = point;
}

position2d<s32> Creature::GetSpawnPoint()
{
  return spawnPoint;
}

void Creature::SetName(stringc name)
{
  this->name = name;
}

stringc Creature::GetName()
{
  return name;
}

int Creature::GetWidth()
{
  return width;
}

void Creature::SetWidth(int width)
{
  this->width = width;
}

int Creature::GetHeight()
{
  return height;
}

void Creature::SetHeight(int height)
{
  this->height = height;
}

void Creature::SetPosition(position2d<s32> point)
{
  this->position = point;
}

position2d<s32> Creature::GetPosition()
{
  return this->position;
}

int Creature::GetSceneNodeId()
{
  return this->sceneNodeId;
}

void Creature::SetSceneNodeId(int sceneNodeId)
{
  this->sceneNodeId = sceneNodeId;
}
