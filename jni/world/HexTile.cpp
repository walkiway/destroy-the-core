/*
 * HexTile.cpp
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */
#define LOG_TAG "HexTile"
#include "HexTile.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;
using namespace video;

HexTile::HexTile(stringc name, stringc world, char mapLegendSymbol, vector2d<
    int> location) :
  _name(name), _world(world), _mapLegendSymbol(mapLegendSymbol), _location(
      location)
{
  _tileIndexLength = 0;
  _atlasIndexOffset = 0;
}

HexTile::HexTile(HexTileDefinition* tileDefinition, vector2d<int> location) :
  _location(location)
{
  _name = tileDefinition->GetName();
  _world = tileDefinition->GetWorldName();
  _mapLegendSymbol = tileDefinition->GetMapLegendSymbol();
  _tileIndexLength = tileDefinition->GetTileIndexLength();
  _atlasIndex = tileDefinition->GetAtlasIndex();
  _width = tileDefinition->GetWidth();
  _height = tileDefinition->GetHeight();

  int tileAtlasIndex = tileDefinition->GetAtlasIndex();

  if (tileDefinition->GetTileIndexLength() > 1)
  {
    //First, choose which in the series to use.
    LOGV(
        "Generating random atlas index starting from %d with a possibility of %d values.",
        tileAtlasIndex, tileDefinition->GetTileIndexLength());

    tileAtlasIndex = rand() % tileDefinition->GetTileIndexLength()
        + tileDefinition->GetAtlasIndex();

    LOGV("Random result: %d", tileAtlasIndex);

    //Calculate how many spaces it is offset from the atlas index originally specified.
    _atlasIndexOffset = tileAtlasIndex - tileDefinition->GetAtlasIndex();
  }
  else
  {
    _atlasIndexOffset = 0;
  }

  _r = tileDefinition->GetR();
  _h = tileDefinition->GetH();
  _sideLength = tileDefinition->GetSideLength();
}

HexTile::~HexTile()
{
}

float HexTile::GetH()
{
  return _h;
}

float HexTile::GetR()
{
  return _r;
}

float HexTile::GetSideLength()
{
  return _sideLength;
}

stringc HexTile::GetTextureName()
{
  stringc fullyQualifiedTileName(_world);
  fullyQualifiedTileName.append("-");
  fullyQualifiedTileName.append(_name);

  //If this tile has more than one potential graphic,
  //the texture name will be qualified by its offset
  //where 0 coutns as a valid offset.
  if (_tileIndexLength > 1)
  {
    char tileIndexOffset[5];
    sprintf(tileIndexOffset, "%d", _atlasIndexOffset);
    fullyQualifiedTileName.append("-");
    fullyQualifiedTileName.append(tileIndexOffset);
    LOGD("Fully qualified name has been adjusted for offset %s",
        fullyQualifiedTileName.c_str());
  }

  return fullyQualifiedTileName;
}
void HexTile::SetAtlasIndexOffset(int newOffset)
{
  _atlasIndexOffset = newOffset;
}

stringc HexTile::GetName()
{
  return _name;
}

void HexTile::SetAtlasIndex(int atlasIndex)
{
  _atlasIndex = atlasIndex;
}

char HexTile::GetMapLegendSymbol()
{
  return _mapLegendSymbol;
}

int HexTile::GetAtlasIndex()
{
  return _atlasIndex;
}

int HexTile::GetTileIndexLength()
{
  return _tileIndexLength;
}

void HexTile::SetTileIndexLength(int tileIndexLength)
{
  _tileIndexLength = tileIndexLength;
}

void HexTile::SetTraversable(bool isTraversable)
{
  _isTraversable = isTraversable;
}

float HexTile::GetWidth()
{
  return _width;
}

float HexTile::GetHeight()
{
  return _height;
}
