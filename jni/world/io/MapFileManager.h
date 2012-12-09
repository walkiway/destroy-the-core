/*
 * MapFileManager.h
 *
 *  This class handles reading a Map object in from an appropriately formatted file.  It is also
 *  responsible for creating this file from information supplied by the MapBuilder class.  This is an
 *  important distinction to note as this class is responsible solely for parsing files and gluing pieces
 *  together while the logic for actually generating a map using a mix of pre-fabbed and randomly
 *  generated rooms lies with the MapBuilder class.
 *
 *  Created on: Nov 6, 2010
 *      Author: Ryan Maloney
 */

#ifndef MAPFILEMANAGER_H_
#define MAPFILEMANAGER_H_

#include <irrlicht.h>
#include "world/HexMap.h"
#include "util/ResourceManager.h"
#include "world/builders/HexTileDefinition.h"

class MapFileManager
{
public:
  MapFileManager(irr::video::IVideoDriver* videoDriver,
      ResourceManager* resourceManager);
  virtual ~MapFileManager();

  //Create a map object from an appropriately formatted file.
  HexMap* Populate(irr::core::stringc filename, irr::core::stringc world);

private:
  //Create a map object with a flag indicating whether or not the file
  //contains map dimension information.  This appears to be optional.
  HexMap* Populate(irr::core::stringc filename, irr::core::stringc world,
      bool readDimensionsFromFile);

  //This helper method parses a map dimension from a line pulled from the map file.
  void ParseDimensionFromLine(char* line,
      irr::core::dimension2d<int>& dimensions);

  //Build a tile object from its constiuent parts contained on one single line.
  HexTileDefinition* ParseTileFromLine(char* line, char& dictionaryKey);

  //Populate all tiles in a map with the IImage instances that are to serve as
  //a texture source.
  bool PopulateTileImages(HexMap* newlyCreatedMap);

  //The global instance of the resource manager the MapFileManager can use to find
  //texture resources specified in the configuration file.
  ResourceManager* _resourceManager;

  //The global instance of the irrlicht video driver.
  irr::video::IVideoDriver* _driver;
};

#endif /* MAPFILEMANAGER_H_ */
