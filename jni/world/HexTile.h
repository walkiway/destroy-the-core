/*
 * HexTile.h
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */

#ifndef HEXTILE_H_
#define HEXTILE_H_

#include <irrlicht.h>
#include "world/builders/HexTileDefinition.h"

class HexTile
{
public:
  HexTile(HexTileDefinition* tileDefinition, irr::core::vector2d<int> location);
  HexTile(irr::core::stringc name, irr::core::stringc world,
      char mapLegendSymbol, irr::core::vector2d<int> location);

  virtual ~HexTile();

  //Accessors only, these fields should only be set upon construction.
  char GetMapLegendSymbol();
  irr::core::stringc GetName();
  irr::core::stringc GetTextureName();

  //Accessors/Mutators
  float GetH();
  float GetR();
  float GetWidth();
  float GetHeight();
  float GetSideLength();
  void SetTraversable(bool);
  void SetAtlasIndexOffset(int newOffset);

  int GetAtlasIndex();
  void SetAtlasIndex(int atlasIndex);

  int GetTileIndexLength();
  void SetTileIndexLength(int tileIndexLength);



private:
  irr::core::vector2d<int> _location;
  irr::core::stringc _name;
  irr::core::stringc _textureName;
  irr::core::stringc _world;
  char _mapLegendSymbol;
  bool _isTraversable;
  int _atlasIndex;
  int _tileIndexLength;
  int _atlasIndexOffset;
  float _width;
  float _height;
  float _r;
  float _h;
  float _sideLength;
};

class Tile
{
public:

};

#endif /* HEXTILE_H_ */
