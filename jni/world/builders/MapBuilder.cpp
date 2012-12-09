/*
 * MapBuilder.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: Ryan Maloney
 */

#include "MapBuilder.h"
#include "world/HexTile.h"

using namespace irr;
using namespace core;

MapBuilder::MapBuilder()
{
  // TODO Auto-generated constructor stub

}

MapBuilder::~MapBuilder()
{
  // TODO Auto-generated destructor stub
}

void MapBuilder::Initialize()
{
  //TODO: Fill this out with prefab rooms.
}

HexMap* ConstructNewAlg(irr::core::dimension2d<int> mapSize,
    HexTileSet* tileSet)
{
  char map[mapSize.Width][mapSize.Height];
//  HexMap* map = new HexMap(mapSize, tileSet->GetWorldName());
//  map->SetTextureFilename(tileSet->GetResourceName());
//
//  const int maxX = mapSize.Width - 1;
//  const int maxY = mapSize.Height - 1;
//
//  for (int x = 0; x < mapSize.Width; x++)
//  {
//    for (int y = 0; y < mapSize.Height; y++)
//    {
//      HexTileDefinition* tileDefinition = NULL;
//
//      tileDefinition = tileSet->GetByName("wall-outer-upper-right-corner");
//
//      vector2d<int> point(x, y);
//      HexTile* tile = new HexTile(tileDefinition, point);
//      map->AddTileAt(tile, point);
//    }
//  }
//
//  return map;
  return NULL;
}

HexMap* MapBuilder::Construct(dimension2d<int> mapSize, HexTileSet* tileSet)
{
  HexMap* map = new HexMap(mapSize, tileSet->GetWorldName());
  map->SetTextureFilename(tileSet->GetResourceName());

  const int maxX = mapSize.Width - 1;
  const int maxY = mapSize.Height - 1;

  for (int x = 0; x < mapSize.Width; x++)
  {
    for (int y = 0; y < mapSize.Height; y++)
    {
      HexTileDefinition* tileDefinition = NULL;

      if (0 == (y % 2))
      {
        tileDefinition = tileSet->GetByName("ground");
      }
      else
      {
        tileDefinition = tileSet->GetByName("wall-outer-lower-left-corner");
      }
//      //We are on the left most edge
//      if (0 == x)
//      {
//        //We are at the left upper corner
//        if (0 == y)
//        {
//          tileDefinition = tileSet->GetByName("wall-outer-upper-right-corner");
//        }
//        //We are the left lower corner
//        else if (maxY == y)
//        {
//          tileDefinition = tileSet->GetByName("wall-outer-lower-left-corner");
//        }
//        //Standard left wall tile
//        else
//        {
//          tileDefinition = tileSet->GetByName("wall-outer-left");
//        }
//      }
//      //We are on the right most edge
//      else if (maxX == x)
//      {
//        //We are at the right upper corner
//        if (0 == y)
//        {
//          tileDefinition = tileSet->GetByName("wall-outer-upper-right-corner");
//        }
//        //We are the right lower corner
//        else if (maxY == y)
//        {
//          tileDefinition = tileSet->GetByName("wall-outer-lower-right-corner");
//        }
//        else
//        {
//          tileDefinition = tileSet->GetByName("wall-outer-right");
//        }
//      }
//      else if (0 == y)
//      {
//        //Corners will be drawn under the x check
//        tileDefinition = tileSet->GetByName("wall-outer-top");
//      }
//      else if (maxY == y)
//      {
//        //Corners will be drawn under the x check
//        tileDefinition = tileSet->GetByName("wall-outer-bottom");
//      }
//      else
//      {
//        tileDefinition = tileSet->GetByName("ground");
//      }

      vector2d<int> point(x, y);

      HexTile* tile = new HexTile(tileDefinition, point);
      map->AddTileAt(tile, point);
    }
  }

  return map;
}
