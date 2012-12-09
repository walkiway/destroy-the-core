/*
 * GameLayer.h
 *
 *  Created on: Nov 4, 2010
 *      Author: Ryan Maloney
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include <irrlicht.h>
#include "util/ResourceManager.h"
#include "world/HexMap.h"
#include "CombatEngine.h"

class GameLayer: public irr::scene::ISceneNode
{
public:
  GameLayer(HexMap* map, ResourceManager* resourceManager,
      irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr,
      irr::s32 id);
  virtual ~GameLayer();
  virtual void OnRegisterSceneNode();
  virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
  virtual irr::u32 getMaterialCount() const;
  virtual void render();

private:
  irr::core::aabbox3d<irr::f32> _boundingBox;
  HexMap* _hexMap;
  CombatEngine* _combatEngine;
};

#endif /* GAMELAYER_H_ */
