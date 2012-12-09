/*
 * HexMap.cpp
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */

#define LOG_TAG "HexMap"

#include "HexMap.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;

HexMap::HexMap(dimension2d<int> dimensions, stringc world) :
  _mapDimensions(dimensions), _world(world)
{
  _tileData = new HexTile**[dimensions.Width];

  for (int col = 0; col < dimensions.Width; col++)
  {
    _tileData[col] = new HexTile*[dimensions.Height];
  }

  for (int x = 0; x < dimensions.Width; x++)
  {
    for (int y = 0; y < dimensions.Height; y++)
    {
      _tileData[x][y] = NULL;
    }
  }

  coordTranslator = NULL;
}

HexMap::~HexMap()
{
  if (NULL != _tileData)
  {
    //The Map class is responsible for also deleting its tiles.
    int x, y;

    for (x = 0; x < _mapDimensions.Width; x++)
    {
      for (y = 0; y < _mapDimensions.Height; y++)
      {
        delete (_tileData[x][y]);
      }
    }

    delete (_tileData);
    _tileData = NULL;
  }
}

CoordinateTranslator* HexMap::GetCoordinateTranslator()
{
  if (NULL == coordTranslator && NULL != _tileData[0][0])
  {
    HexTile* ht = _tileData[0][0];
    coordTranslator = new CoordinateTranslator(ht);
  }

  return coordTranslator;
}

HexTile* HexMap::GetTileAt(vector2d<int> point)
{
  return _tileData[point.X][point.Y];
}

void HexMap::AddTileAt(HexTile* tile, vector2d<int> point)
{
  LOGD("Attempting to add a tile at point (%d, %d)", point.X, point.Y);
  if (point.X < _mapDimensions.Width && point.Y < _mapDimensions.Height)
  {
    _tileData[point.X][point.Y] = tile;
    LOGD("Successfully added tile at point (%d, %d)", point.X, point.Y);
  }
  else
  {
    LOGE("Failed to add tile because the point specified is outside the bounds of the map.");
  }
}

stringc HexMap::GetWorld()
{
  return _world;
}

void HexMap::SetTextureFilename(stringc textureFilename)
{
  _textureFilename = textureFilename;
}

dimension2d<int> HexMap::GetMapDimensions()
{
  return _mapDimensions;
}

stringc HexMap::GetTextureFilename()
{
  return _textureFilename;
}

void HexMap::AddMonster(Monster* creature)
{
  monsters.push_front(creature);
}

list<Monster*>::Iterator HexMap::GetFirstMonster(void)
{
  return monsters.begin();
}

list<Monster*>::Iterator HexMap::GetLastMonster(void)
{
  return monsters.end();
}

void HexMap::SetPlayerCharacter(PlayerCharacter* pc)
{
  this->playerCharacter = pc;
}

PlayerCharacter* HexMap::GetPlayerCharacter(void)
{
  return this->playerCharacter;
}
