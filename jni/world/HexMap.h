/*
 * HexMap.h
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */

#ifndef HEXMAP_H_
#define HEXMAP_H_

#include <irrlicht.h>
#include "HexTile.h"
#include "entities/Creature.h"
#include "entities/Monster.h"
#include "entities/builders/CreatureSet.h"
#include "entities/PlayerCharacter.h"
#include "util/CoordinateTranslator.h"

class HexMap
{
public:
  HexMap(irr::core::dimension2d<int> dimensions, irr::core::stringc world);
  virtual ~HexMap(void);
  void SetTextureFilename(irr::core::stringc textureFilename);
  irr::core::dimension2d<int> GetMapDimensions();
  irr::core::stringc GetTextureFilename(void);
  void AddTileAt(HexTile* tile, irr::core::vector2d<int> point);
  HexTile* GetTileAt(irr::core::vector2d<int> point);
  irr::core::stringc GetWorld(void);
  void AddMonster(Monster* creature);
  irr::core::list<Monster*>::Iterator GetFirstMonster(void);
  irr::core::list<Monster*>::Iterator GetLastMonster(void);
  void SetPlayerCharacter(PlayerCharacter*);
  PlayerCharacter* GetPlayerCharacter(void);
  CoordinateTranslator* GetCoordinateTranslator(void);

private:
  irr::core::dimension2d<int> _mapDimensions;
  irr::core::stringc _textureFilename;
  irr::core::stringc _world;
  HexTile*** _tileData;
  PlayerCharacter* playerCharacter;
  CoordinateTranslator* coordTranslator;
  irr::core::list<Monster*> monsters;
//  irr::core::list<Creature*> creatures;
};
#endif /* HEXMAP_H_ */
