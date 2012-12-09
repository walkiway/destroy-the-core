/*
 * Creature.h
 *
 *  Created on: Jan 13, 2011
 *      Author: Ryan Maloney
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <irrlicht.h>
#include "entities/builders/CreatureDefinition.h"

class Creature
{
public:
  Creature(CreatureDefinition* definition, irr::core::position2d<irr::s32> spawnPoint);
  virtual ~Creature();

  ///These are calculated on each call so that buffs etc. are taken into account.
  virtual int GetAttackPower(void);
  virtual int GetDefensePower(void);

  void IncreaseLifeMeter(int value);
  void DecreaseLifeMeter(int value);

  bool IsAlive(void);

  void SetSpawnPoint(irr::core::position2d<irr::s32> point);
  irr::core::position2d<irr::s32> GetSpawnPoint();

  void SetPosition(irr::core::position2d<irr::s32> point);
  irr::core::position2d<irr::s32> GetPosition();

  void SetName(irr::core::stringc);
  irr::core::stringc GetName();

  int GetWidth(void);
  void SetWidth(int);

  int GetHeight(void);
  void SetHeight(int);

  int GetSceneNodeId(void);
  void SetSceneNodeId(int);

  int GetLifeMeter(void);
  int GetMaxLifeMeter(void);

  //Acessors only
  irr::core::stringc GetTextureName();

private:
  irr::core::position2d<irr::s32> spawnPoint;
  irr::core::position2d<irr::s32> position;
  irr::core::stringc name;
  irr::core::stringc worldName;
  int width;
  int height;
  int atlasIndex;
  int indexLength;
  int lifeMeter;
  int maxLifeMeter;
  int sceneNodeId;
  //TODO: This is a holdover for how random tiles are handled for map tiles.
  //Handle this differently should we add animations.  For now this will be 0.
  int atlasIndexOffset;
};

#endif /* CREATURE_H_ */
