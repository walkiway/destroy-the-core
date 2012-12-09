/*
 * GameGraph.cpp
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "GameGraph"
#include "GameGraph.h"
#include "states/WorldState.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace gui;
using namespace video;

GameGraph::GameGraph(IrrlichtDevice* dev, IVideoDriver* dr, ResourceManager* rm) :
  StateGraph<GameGraph, SEvent> (this), device(dev), resourceManager(rm),
      driver(dr), resolutionWidth(0), resolutionHeight(0)
{
  device->setEventReceiver(this);
}

GameGraph::~GameGraph()
{
  device->setEventReceiver(NULL);
}

void GameGraph::Reload(irr::IrrlichtDevice* dev, irr::video::IVideoDriver* irrDriver)
{
  dev->setEventReceiver(this);
  device = dev;
  driver = irrDriver;
  OnReload();
}

bool GameGraph::OnEvent(const SEvent& event)
{
  this->HandleEvent(event);
}

IVideoDriver* GameGraph::GetDriver(void)
{
  return driver;
}

ISceneManager* GameGraph::GetSceneManager()
{
  return device->getSceneManager();
}

ISceneCollisionManager* GameGraph::GetSceneCollisionManager(void)
{
  return device->getSceneManager()->getSceneCollisionManager();
}

CoordinateTranslator* GameGraph::GetCoordinateTranslator(void)
{
  CoordinateTranslator* ct = NULL;
  WorldState* ws = static_cast<WorldState*> (GetWorldState());

  if (NULL != ws)
  {
    ct = ws->GetCurrentMap()->GetCoordinateTranslator();
  }

  return ct;
}

IGUIEnvironment* GameGraph::GetUserInterface()
{
  return device->getGUIEnvironment();
}

IVideoDriver* GameGraph::GetVideoDriver()
{
  return device->getVideoDriver();
}

ITimer* GameGraph::GetTimer()
{
  return device->getTimer();
}

IrrlichtDevice* GameGraph::GetDevice()
{
  return device;
}

ResourceManager* GameGraph::GetResourceManager()
{
  return const_cast<ResourceManager*> (resourceManager);
}

void GameGraph::AddGameState(irr::core::stringc name, State<GameGraph,
    irr::SEvent>* state)
{
  States.push_back(SState(name, state));
}

void GameGraph::SetResolutionWidth(int width)
{
  resolutionWidth = width;
}

int GameGraph::GetResoultionWidth()
{
  return resolutionWidth;
}

void GameGraph::SetResolutionHeight(int height)
{
  resolutionHeight = height;
}

int GameGraph::GetResolutionHeight()
{
  return resolutionHeight;
}

list<stringw*>& GameGraph::GetMessageQueue()
{
  list<stringw*>& ref = messageQueue;
  return ref;
}


