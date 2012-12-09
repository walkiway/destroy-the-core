/*
 * WorldState.h
 *
 * When the system enters a particular world state, the world state should
 * construct all of the necessary maps and monsters from the various resources sent
 * to the system.  When a world state leaves, that means it is being replaced
 * by another world and all resources should be returned.
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */

#ifndef WORLDSTATE_H_
#define WORLDSTATE_H_

#include "util/State.h"
#include "states/GameGraph.h"
#include <irrlicht.h>
#include "world/HexMap.h"
#include "util/CoordinateTranslator.h"
#include "entities/PlayerCharacter.h"
#include "entities/builders/CreatureSet.h"
#include "world/builders/HexTileSet.h"

class WorldState: public State<GameGraph, irr::SEvent>
{
public:
  WorldState();
  virtual ~WorldState();

  ///Upon entering a world state build all of the necessary maps and populate accordingly.
  virtual void OnEnter(GameGraph* entity);

  ///Remove all resources used and destroy created maps.
  virtual void OnLeave(GameGraph* entity);

  ///Reload all resources
  virtual void OnReload(GameGraph* entity);

  ///Render scene.
  virtual void OnUpdate(GameGraph* entity);

  HexMap* GetCurrentMap(void);

  PlayerCharacter* GetHero(void);

protected:
  PlayerCharacter* hero;
  HexMap* currentMap;
  CoordinateTranslator* coordinateTranslator;

private:
  CreatureSet* heroSet;
  CreatureSet* monsterSet;
  HexTileSet* tileSet;
};

#endif /* WORLDSTATE_H_ */
