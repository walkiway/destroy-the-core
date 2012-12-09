/*
 * CreatureDefinition.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: Ryan Maloney
 */

#include "CreatureDefinition.h"

using namespace irr;
using namespace core;

CreatureDefinition::CreatureDefinition()
{
  // TODO Auto-generated constructor stub

}

CreatureDefinition::~CreatureDefinition()
{
  // TODO Auto-generated destructor stub
}

void CreatureDefinition::SetWorldName(stringc worldName)
{
  this->worldName = worldName;
}

stringc CreatureDefinition::GetWorldName()
{
  return worldName;
}

void CreatureDefinition::SetName(stringc name)
{
  this->name = name;
}

stringc CreatureDefinition::GetName()
{
  return name;
}

int CreatureDefinition::GetWidth()
{
  return width;
}

void CreatureDefinition::SetWidth(int width)
{
  this->width = width;
}

int CreatureDefinition::GetHeight()
{
  return height;
}

void CreatureDefinition::SetHeight(int height)
{
  this->height = height;
}

int CreatureDefinition::GetAtlasIndex()
{
  return atlasIndex;
}

void CreatureDefinition::SetAtlasIndex(int atlasIndex)
{
  this->atlasIndex = atlasIndex;
}

int CreatureDefinition::GetIndexLength()
{
  return indexLength;
}

void CreatureDefinition::SetIndexLength(int indexLength)
{
  this->indexLength = indexLength;
}

int CreatureDefinition::GetLifeMeter(void)
{
  return lifeMeter;
}

void CreatureDefinition::SetLifeMeter(int lifeMeter)
{
  this->lifeMeter = lifeMeter;
}

int CreatureDefinition::GetMaxLifeMeter()
{
  return maxLifeMeter;
}

void CreatureDefinition::SetMaxLifeMeter(int maxLifeMeter)
{
  this->maxLifeMeter = maxLifeMeter;
}
