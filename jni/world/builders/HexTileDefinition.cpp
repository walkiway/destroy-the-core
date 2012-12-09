/*
 * HexTileDefinition.cpp
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */
#define LOG_TAG "HexTileDefinition"

#include "HexTileDefinition.h"
#include "math.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;

HexTileDefinition::HexTileDefinition(stringc name, char mapLegendSymbol) :
  _name(name), _mapLegendSymbol(mapLegendSymbol)
{

}
HexTileDefinition::HexTileDefinition(HexTileDefinition* tileDefinition)
{
  _name = tileDefinition->GetName();
  _worldName = tileDefinition->GetWorldName();
  _atlasIndex = tileDefinition->GetAtlasIndex();
  _mapLegendSymbol = tileDefinition->GetMapLegendSymbol();
  _atlasIndexOffset = tileDefinition->GetAtlasIndexOffset();
  _tileIndexLength = tileDefinition->GetTileIndexLength();
  _isTraversable = tileDefinition->IsTraversable();
}

HexTileDefinition::~HexTileDefinition()
{
}

float HexTileDefinition::GetSideLength()
{
  return _sideLength;
}

void HexTileDefinition::CalculateIntermediateValues()
{
  _r = _width / 2.0;
  _sideLength = _r / (cos(30.0 * M_PI / 180.0));
  _h = (_height - _sideLength) / 2.0;

  LOGI("Calculated Hex Values sidelength: %f, h=%f, r=%f, height=%f, width=%f", _sideLength, _h, _r, _height, _width);
}

float HexTileDefinition::GetWidth()
{
  return _width;
}

void HexTileDefinition::SetWidth(float width)
{
  _width = width;
}

float HexTileDefinition::GetHeight()
{
  return _height;
}

void HexTileDefinition::SetHeight(float height)
{
  _height = height;
}

float HexTileDefinition::GetH()
{
  return _h;
}

float HexTileDefinition::GetR()
{
  return _r;
}

void HexTileDefinition::SetWorldName(stringc newName)
{
  _worldName = newName;
}

stringc HexTileDefinition::GetWorldName()
{
  return _worldName;
}

void HexTileDefinition::SetName(stringc newName)
{
  _name = newName;
}

stringc HexTileDefinition::GetName()
{
  return _name;
}

int HexTileDefinition::GetAtlasIndex()
{
  return _atlasIndex;
}

void HexTileDefinition::SetAtlasIndex(int atlasIndex)
{
  _atlasIndex = atlasIndex;
}

char HexTileDefinition::GetMapLegendSymbol()
{
  return _mapLegendSymbol;
}

int HexTileDefinition::GetTileIndexLength()
{
  return _tileIndexLength;
}

void HexTileDefinition::SetTileIndexLength(int tileIndexLength)
{
  _tileIndexLength = tileIndexLength;
}

void HexTileDefinition::SetTraversable(bool isTraversable)
{
  _isTraversable = isTraversable;
}

bool HexTileDefinition::IsTraversable()
{
  return _isTraversable;
}

int HexTileDefinition::GetAtlasIndexOffset()
{
  return _atlasIndexOffset;
}

void HexTileDefinition::SetAtlasIndexOffset(int newOffset)
{
  _atlasIndexOffset = newOffset;
}
