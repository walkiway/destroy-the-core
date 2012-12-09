/*
 * WorldState.cpp
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "WorldState"

#include "WorldState.h"
#include "util/LoggingMacros.h"
#include "util/ResourceManager.h"
#include "entities/builders/CreatureDefinition.h"
#include "entities/io/CreatureDefinitionFileManager.h"
#include "world/builders/MapBuilder.h"
#include "world/io/TileDefinitionFileManager.h"
#include "view/GameLayer.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

WorldState::WorldState()
{
  hero = NULL;
}

WorldState::~WorldState()
{
  // TODO Auto-generated destructor stub
}

void WorldState::OnEnter(GameGraph* game)
{
  IVideoDriver* driver = game->GetVideoDriver();
  ResourceManager* resourceManager = game->GetResourceManager();
  ISceneManager* sceneManager = game->GetSceneManager();

  //1) BUILD HERO
  heroSet = CreatureDefinitionFileManager::PopulateCreatureSet(resourceManager,
      "heroes.amr");

  if (NULL != heroSet)
  {
    if (!heroSet->RegisterTextures(driver, resourceManager))
    {
      LOGE("Unable to read in textures for creature set!");
    }
    else
    {
      LOGI("A creature set with %d creatures was populated from the resource.",
          heroSet->GetNumberOfCreatures());
      CreatureDefinition* creatureDefinition = heroSet->GetByName("hero");
      if (NULL != creatureDefinition)
      {
        LOGI("The creature definition has been found and has the name %s",
            creatureDefinition->GetName().c_str());
        hero = new PlayerCharacter(creatureDefinition, position2d<s32> (0, 0));
        if (NULL != hero)
        {
          LOGI("Hero created with H x W (%d x %d)!", hero->GetWidth(),
              hero->GetHeight());
          ITexture* heroTexture = driver->getTexture(hero->GetTextureName());

          if (NULL != heroTexture)
          {
            LOGD("Hero created succesfully");
          }
          else
          {
            LOGE("Unable to load hero texture named %s",
                hero->GetTextureName().c_str());
          }
        }
        else
        {
          LOGE("Failed to create hero!");
        }
      }
      else
      {
        LOGE(
            "An error occurred while attempting to pull the creature named %s from the creature set.",
            "hero");
      }
    }
  }
  else
  {
    LOGE(
        "An error occured while attempting to populate a creature set from the supplied resource.");
  }

  //2) BUILD MONSTER SET
  Monster* skeleton = NULL;

  monsterSet = CreatureDefinitionFileManager::PopulateCreatureSet(
      resourceManager, "monsters.amr");

  if (NULL != monsterSet)
  {
    if (!monsterSet->RegisterTextures(driver, resourceManager))
    {
      LOGE("Unable to read in textures for monster set!");
    }
    else
    {
      LOGI("A monster set with %d monsters was populated from the resource.", monsterSet->GetNumberOfCreatures());
      CreatureDefinition* monsterDefinition = monsterSet->GetByName("skeleton");
      if (NULL != monsterDefinition)
      {
        LOGI("The monster definition has been found and has the name %s", monsterDefinition->GetName().c_str());
        skeleton = new Monster(monsterDefinition, vector2d<s32> (4, 4));
        if (NULL != skeleton)
        {
          LOGI("Skeleton successfully created!");
        }
        else
        {
          LOGE("Failed to create skeleton!");
        }
      }
      else
      {
        LOGE("An error occurred while attempting to pull the creature named %s from the creature set.", "hero");
      }
    }
  }
  else
  {
    LOGE("An error occured while attempting to populate a creature set from the supplied resource.");
  }

  //3) BUILD MAP
  tileSet = TileDefinitionFileManager::PopulateHexTileDefinitionSet(
      resourceManager, "latest.amr");

  if (NULL != tileSet)
  {
    LOGI("The tile set contains %d tiles.", tileSet->GetNumberOfTiles());
    LOGI("Tile width %f Tile height %f.", tileSet->GetTileWidth(), tileSet->GetTileHeight());
    tileSet->RegisterTileTextures(driver, resourceManager);
    LOGI("Registered tile textures.");

    MapBuilder mapBuilder;
    LOGI("Building map...");
    currentMap = mapBuilder.Construct(dimension2d<int> (10, 10), tileSet);
    LOGI("Adding hero...");
    currentMap->SetPlayerCharacter(hero);
    LOGI("Adding skeleton...");
    currentMap->AddMonster(skeleton);
    LOGI("Map completed!");

    //Set global coordinate translator reference
    coordinateTranslator = currentMap->GetCoordinateTranslator();

    driver->setTransform(ETS_WORLD, matrix4());
    driver->setTransform(ETS_VIEW, matrix4());

    //Build game layer and hard code wih map
    if (NULL != currentMap)
    {
      LOGI("Map:\nDimensions(%d, %d)\nTextureName: %s", currentMap->GetMapDimensions().Width, currentMap->GetMapDimensions().Height, currentMap->GetTextureFilename().c_str());
      GameLayer* gameLayer = new GameLayer(currentMap,
          game->GetResourceManager(),
          game->GetSceneManager()->getRootSceneNode(), game->GetSceneManager(),
          1234);
    }
  }
  else
  {
    LOGE("The TileSet could not be loaded and, accordingly, a map could not be constructed.");
  }
}

void WorldState::OnLeave(GameGraph* entity)
{
}

void WorldState::OnUpdate(GameGraph* entity)
{
}

void WorldState::OnReload(GameGraph* game)
{
  IVideoDriver* driver = game->GetVideoDriver();
  ResourceManager* resourceManager = game->GetResourceManager();
  ISceneManager* sceneManager = game->GetSceneManager();

  if (!heroSet->RegisterTextures(driver, resourceManager))
  {
    LOGE("Unable to register heros textures on reload for world.");
  }

  if (!monsterSet->RegisterTextures(driver, resourceManager))
  {
    LOGE("Unable to register monster textures on reload for world.");
  }

  if (tileSet->RegisterTileTextures(driver, resourceManager))
  {
    coordinateTranslator = currentMap->GetCoordinateTranslator();
    driver->setTransform(ETS_WORLD, matrix4());
    driver->setTransform(ETS_VIEW, matrix4());
    //Build game layer and hard code wih map
    if (NULL != currentMap)
    {
      LOGI("Map:\nDimensions(%d, %d)\nTextureName: %s", currentMap->GetMapDimensions().Width, currentMap->GetMapDimensions().Height, currentMap->GetTextureFilename().c_str());
      GameLayer* gameLayer = new GameLayer(currentMap,
          game->GetResourceManager(),
          game->GetSceneManager()->getRootSceneNode(), game->GetSceneManager(),
          1234);
    }
  }
  else
  {
    LOGE("Unable to register tile textures on reload for world.");
  }
}

HexMap* WorldState::GetCurrentMap()
{
  return const_cast<HexMap*> (currentMap);
}

PlayerCharacter* WorldState::GetHero(void)
{
  return const_cast<PlayerCharacter*> (hero);
}
