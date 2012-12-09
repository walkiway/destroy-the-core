/*
 * HexMapSceneNode.cpp
 *
 *  Created on: Dec 16, 2010
 *      Author: ryan
 */

#define  LOG_TAG    "HexMapSceneNode"
#include "HexMapSceneNode.h"
#include "util/LoggingMacros.h"
#include "world/HexTile.h"
#include "world/HexMap.h"
#include "view/PlayerCharacterAnimator.h"
#include "view/MonsterAnimator.h"
#include "util/CoordinateTranslator.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

HexMapSceneNode::HexMapSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id) :
  ISceneNode(parent, mgr, id)
{
  idGenerator = 777;
  coordinateTranslator = NULL;
  setPosition(vector3df(0.0f, 0.0f, 0.0f));
}

HexMapSceneNode::~HexMapSceneNode()
{
  // TODO Auto-generated destructor stub
}

void HexMapSceneNode::Initialize(HexMap* map, ResourceManager* resourceManager)
{
  setMaterialFlag(video::EMF_LIGHTING, false);
  setMaterialFlag(video::EMF_ANTI_ALIASING, false);
  setMaterialFlag(video::EMF_BILINEAR_FILTER, false);

  LOGI("Initialize bounding box from map dimensions( %d x %d)",
      map->GetMapDimensions().Width, map->GetMapDimensions().Height);
  _boundingBox.addInternalPoint(vector3df(0, 0, 0));
  _boundingBox.addInternalPoint(
      vector3df(0, -1 * map->GetMapDimensions().Height, 0));
  _boundingBox.addInternalPoint(vector3df(map->GetMapDimensions().Width, 0, 0));
  _boundingBox.addInternalPoint(
      vector3df(map->GetMapDimensions().Width,
          -1 * map->GetMapDimensions().Height, 0));

  coordinateTranslator = map->GetCoordinateTranslator();

  IVideoDriver* driver = SceneManager->getVideoDriver();

  for (int y = 0; y < map->GetMapDimensions().Height; y++)
  {
    for (int x = 0; x < map->GetMapDimensions().Width; x++)
    {
      vector2d<s32> mapCoord(x, y);
      HexTile* tile = map->GetTileAt(mapCoord);

      if (NULL != tile)
      {
        position2d<s32> upperLeft(x, y);
        AddTile(mapCoord, tile);
      }
      else
      {
        LOGE("Missing tile at (%d, %d)", x, y);
      }
    }
  }

  list<Monster*>::Iterator begin = map->GetFirstMonster();
  list<Monster*>::Iterator end = map->GetLastMonster();

  for (; begin != end; begin++)
  {
    if ((*begin)->IsAlive())
    {
      AddCreature(*begin, true);
    }
  }

  if (map->GetPlayerCharacter()->IsAlive())
  {
    AddCreature(map->GetPlayerCharacter(), false);
  }
}

void HexMapSceneNode::render()
{
  LOGV("Rendering HexMapSceneNode - nothing to draw!");
}

void HexMapSceneNode::OnRegisterSceneNode()
{
  if (IsVisible)
  {
    SceneManager->registerNodeForRendering(this);
  }

  ISceneNode::OnRegisterSceneNode();
}

const aabbox3d<f32>& HexMapSceneNode::getBoundingBox() const
{
  return _boundingBox;
}

IBillboardSceneNode* HexMapSceneNode::AddCreature(Creature* creature,
    bool isMonster)
{
  IBillboardSceneNode* creatureNode = NULL;

  ITexture* texture = SceneManager->getVideoDriver()->getTexture(
      creature->GetTextureName());

  if (NULL == texture)
  {
    LOGE("Unable to find a  texture for the name %s", creature->GetTextureName().c_str());
  }
  else
  {
    creatureNode = SceneManager->addBillboardSceneNode(
        this,
        dimension2d<f32> (texture->getSize().Width, texture->getSize().Height),
        coordinateTranslator->TranslateMapCoords(creature->GetSpawnPoint(),
            -1.0), ++idGenerator);

    //STAMP creature object with scene node id for fast removal later.
    creature->SetSceneNodeId(idGenerator);

    creatureNode->setMaterialTexture(0,
        SceneManager->getVideoDriver()->getTexture(creature->GetTextureName()));
    SMaterial& material = creatureNode->getMaterial(0);
    material.AntiAliasing = false;
    material.BackfaceCulling = true;
    material.FogEnable = false;
    material.Lighting = false;
    creatureNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    creatureNode->setMaterialFlag(video::EMF_LIGHTING, false);
    creatureNode->setMaterialFlag(video::EMF_ANTI_ALIASING, false);
    creatureNode->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);

    if (isMonster)
    {
      MonsterAnimator* ma = new MonsterAnimator(
          static_cast<Monster*> (creature), coordinateTranslator);
      creatureNode->addAnimator(ma);
    }
    else
    {
      PlayerCharacterAnimator* pcNode = new PlayerCharacterAnimator(
          static_cast<PlayerCharacter*> (creature), coordinateTranslator);
      creatureNode->addAnimator(pcNode);
    }
  }

  return creatureNode;
}

void HexMapSceneNode::AddTile(vector2d<s32> mapCoord, HexTile* hexTile)
{
  LOGD("Creating HexTileSceneNode with center at map coordinate (%d, %d) from tile with height %f and width %f", mapCoord.X, mapCoord.Y, hexTile->GetHeight(), hexTile->GetWidth());
  LOGD("Loading texture named %s",hexTile->GetTextureName().c_str());

  ITexture* tileTexture = SceneManager->getVideoDriver()->getTexture(
      hexTile->GetTextureName());

  if (NULL == tileTexture)
  {
    LOGE("Unable to find a tile texture for the name %s", hexTile->GetTextureName().c_str());
  }
  else
  {
    dimension2d<u32> textureSize = tileTexture->getSize();

    vector3df position = coordinateTranslator->TranslateMapCoords(mapCoord, 0.0);
    IBillboardSceneNode* tileNode = SceneManager->addBillboardSceneNode(this,
        dimension2d<f32> (textureSize.Width, textureSize.Height),
        position, ++idGenerator);

    LOGD("Creating tile of size %f x %f at %f, %f", textureSize.Width, textureSize.Height, position.X, position.Y);

    tileNode->setMaterialTexture(0, tileTexture);
    SMaterial& material = tileNode->getMaterial(0);
    material.AntiAliasing = false;
    material.BackfaceCulling = true;
    material.FogEnable = false;
    material.Lighting = false;
    tileNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
    tileNode->setMaterialFlag(video::EMF_LIGHTING, false);
    tileNode->setMaterialFlag(video::EMF_ANTI_ALIASING, false);
    tileNode->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);
  }
}
