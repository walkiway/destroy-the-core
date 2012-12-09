/*
 * HexTileDefinition.h
 *
 * This utlity class captures all of the tile definition metadata
 * for a single tile definition entry contained in the tile definition
 * file.  The information captured therein is intended to fully define a hex tile.
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */

#ifndef HEXTILEDEFINITION_H_
#define HEXTILEDEFINITION_H_

#include <irrlicht.h>

class HexTileDefinition
{
public:
  HexTileDefinition(irr::core::stringc name, char mapLegendSymbol);
  HexTileDefinition(HexTileDefinition* tileDefinition);
  virtual ~HexTileDefinition();

  //There is only an accessor for the map legend symbol,
  //this cannot be changed programmatically! The risk
  //would be that the map generated from a save would
  //be unusable because the arbitrary symbols would not
  //map to an existing tile set definition file.
  char GetMapLegendSymbol();

  //Mutators/Accessors
  void SetWorldName(irr::core::stringc name);
  irr::core::stringc GetWorldName();

  void SetName(irr::core::stringc name);
  irr::core::stringc GetName();

  int GetAtlasIndex();
  void SetAtlasIndex(int atlasIndex);

  int GetTileIndexLength();
  void SetTileIndexLength(int tileIndexLength);

  void SetAtlasIndexOffset(int newOffset);
  int GetAtlasIndexOffset();

  void SetTraversable(bool isTraversable);
  bool IsTraversable();

  float GetWidth();
  void SetWidth(float);

  float GetHeight();
  void SetHeight(float);

  float GetH();
  float GetSideLength();
  float GetR();
  void CalculateIntermediateValues();

private:
  irr::core::stringc _name;
  irr::core::stringc _worldName;
  char _mapLegendSymbol;
  int _atlasIndex;
  int _tileIndexLength;
  int _atlasIndexOffset;
  bool _isTraversable;
  float _sideLength;
  float _width;
  float _height;
  float _r;
  float _h;
};

#endif /* HEXTILEDEFINITION_H_ */
