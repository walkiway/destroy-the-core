/*
 * HexTileSet.h
 *
 *  Created on: Dec 16, 2010
 *      Author: ryan
 */

#ifndef HEXTILESET_H_
#define HEXTILESET_H_

#include <irrlicht.h>
#include "world/builders/HexTileDefinition.h"
#include "util/ResourceManager.h"

class HexTileSet
{
public:
  HexTileSet(irr::core::stringc worldName, irr::core::stringc resourceName);
  virtual ~HexTileSet();

  //Add an existing tiledefinition to the TileSet.  Once a TileDefinition
  //has been added memory management responsibility passes to this TileSet.
  void Add(HexTileDefinition* tileDefinition);

  //Return the tile definition identified by the supplied legend symbol, e.g. '@'
  HexTileDefinition* GetByLegendSymbol(char legendSymbol);

  //Return the tile definition identified by the supplied name, e.g. wall-upper-left-corner
  HexTileDefinition* GetByName(irr::core::stringc tileName);

  //The number of tiles in this tileset.
  int GetNumberOfTiles();

  //Register all of the textures associated with the contained tiles with irrlicht.
  bool RegisterTileTextures(irr::video::IVideoDriver* videoDriver, ResourceManager* resourceManager);

  //Acessors only
  irr::core::stringc GetWorldName();
  irr::core::stringc GetResourceName();

  void SetTileWidth(float);
  float GetTileWidth();
  void SetTileHeight(float);
  float GetTileHeight();

private:
  //The name of the world this tile set is associated with.
  irr::core::stringc _worldName;

  //The name of the resource file containing the tilesheet, e.g. tilesheet.png
  irr::core::stringc _resourceName;

  //Tile definitions keyed by name.  This means that tiles
  //contained in one set must be uniquely named.
  irr::core::map<irr::core::stringc, HexTileDefinition*> _tileDefinitionsName;

  //Tile definitions keyed by legend symbol.  This means that tiles
  //contained in one set must each have a unique legend symbol.
  irr::core::map<char, HexTileDefinition*> _tileDefinitionsLegend;

  float _tileWidth;

  float _tileHeight;
};

#endif /* HEXTILESET_H_ */
