/*
 * MapBuilder.h
 *
 *  Created on: Nov 9, 2010
 *      Author: Ryan Maloney
 */

#ifndef MAPBUILDER_H_
#define MAPBUILDER_H_

#include <irrlicht.h>
#include "world/HexMap.h"
#include "HexTileSet.h"

class MapBuilder
{
public:
  MapBuilder();
  virtual ~MapBuilder();

  ///
  //Pulls all of the pre-fabbed rooms into memory such that they can,
  //based on weighted random pulls, be used to create new random maps.
  //Should only be called once per MapBuilder instance and an internal
  //flag will enforce this.
  ///
  void Initialize();

  HexMap* Construct(irr::core::dimension2d<int> mapSize, HexTileSet* tileSet);

  HexMap* ConstructNewAlg(irr::core::dimension2d<int> mapSize, HexTileSet* tileSet);
private:
  bool _initialized;
};

#endif /* MAPBUILDER_H_ */
