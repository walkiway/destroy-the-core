/*
 * HexMapSceneNode.h
 *
 *  Created on: Dec 16, 2010
 *      Author: ryan
 */

#ifndef HEXMAPSCENENODE_H_
#define HEXMAPSCENENODE_H_

#include <irrlicht.h>
#include <ISceneNode.h>
#include "world/HexMap.h"
#include "util/ResourceManager.h"
#include "entities/Creature.h"
#include "util/CoordinateTranslator.h"

class HexMapSceneNode: public irr::scene::ISceneNode
{
public:
  HexMapSceneNode(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr,
      irr::s32 id);
  virtual ~HexMapSceneNode();
  virtual void OnRegisterSceneNode();
  virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
  virtual void render();
  void Initialize(HexMap* map, ResourceManager* resourceManager);

private:
  ///Important note: this method will modify the input creature object, stamping
  ///it with the id of the scene node created for it.
  irr::scene::IBillboardSceneNode* AddCreature(Creature*, bool);
  void AddTile(irr::core::vector2d<irr::s32>, HexTile* hexTile);
  irr::core::aabbox3d<irr::f32> _boundingBox;
  int idGenerator;
  CoordinateTranslator* coordinateTranslator;
};


#endif /* HEXMAPSCENENODE_H_ */
