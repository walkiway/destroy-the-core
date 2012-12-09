/*
 * GameLayer.cpp
 *
 *  Created on: Nov 4, 2010
 *      Author: Ryan Maloney
 */

#define  LOG_TAG    "GameLayer"

#include "GameLayer.h"
#include <irrlicht.h>
#include "util/LoggingMacros.h"
#include "HexMapSceneNode.h"
#include "entities/Monster.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GameLayer::GameLayer(HexMap* map, ResourceManager* resourceManager,
    ISceneNode* parent, ISceneManager* mgr, s32 id) :
  irr::scene::ISceneNode(parent, mgr, id)
{
  setPosition(vector3df(0.0, 0.0, 0.0));
  _combatEngine = new CombatEngine();
  _hexMap = map;
  _boundingBox.addInternalPoint(vector3df(0, 0, 0));
  _boundingBox.addInternalPoint(vector3df(0, -1
      * map->GetMapDimensions().Height, 0));
  _boundingBox.addInternalPoint(vector3df(map->GetMapDimensions().Width, 0, 0));
  _boundingBox.addInternalPoint(vector3df(map->GetMapDimensions().Width, -1
      * map->GetMapDimensions().Height, 0));
  HexMapSceneNode* mapSceneNode = new HexMapSceneNode(this, SceneManager, 7);
  LOGV("Initializing MapSceneNode");
  mapSceneNode->Initialize(map, resourceManager);
  mapSceneNode->drop();
  mapSceneNode = NULL;
}

GameLayer::~GameLayer()
{
  // TODO Auto-generated destructor stub
}

void GameLayer::render()
{
}

void GameLayer::OnRegisterSceneNode()
{
  if (IsVisible)
  {
    SceneManager->registerNodeForRendering(this);
  }

  ISceneNode::OnRegisterSceneNode();
}

const aabbox3d<f32>& GameLayer::getBoundingBox() const
{
  return _boundingBox;
}

u32 GameLayer::getMaterialCount() const
{
  return 1;
}
