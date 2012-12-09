/*
 * TileDefinitionFileManager.h
 *
 * This class manages reading a tile definition file and parsing the comments.
 * Depending on the contents of the file, parsing will be delegated to one of two
 * methods, either Standard tile parsing or Hex tile parsing.  Standard tiles
 * are square.
 *
 *  Created on: Dec 12, 2010
 *      Author: Ryan Maloney
 */

#ifndef TILEDEFINITIONFILEMANAGER_H_
#define TILEDEFINITIONFILEMANAGER_H_

#include <irrlicht.h>
#include "util/ResourceManager.h"
#include "world/builders/HexTileSet.h"

class TileDefinitionFileManager
{
public:
  TileDefinitionFileManager();
  virtual ~TileDefinitionFileManager();

  //Using the supplied resource manager, this method will find the
  //appropriate resource bundle and find the resource identified by
  //the supplied resource name within that bundle. This resource
  //should be a tile definition file.  It then loads the tile definition file
  //and parses the information out to generate a set of HexTileDefinitions.
  static HexTileSet* PopulateHexTileDefinitionSet(ResourceManager* resourceManager,
      irr::core::stringc resourceName);
};

#endif /* TILEDEFINITIONFILEMANAGER_H_ */
