/*
 * GameGraph.h
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */

#ifndef GAMEGRAPH_H_
#define GAMEGRAPH_H_

#include <IEventReceiver.h>
#include "util/StateGraph.h"
#include "util/ResourceManager.h"
#include <irrlicht.h>
#include "util/CoordinateTranslator.h"

class GameGraph: public StateGraph<GameGraph, irr::SEvent> ,
    public irr::IEventReceiver
{
public:
  GameGraph(irr::IrrlichtDevice* dev, irr::video::IVideoDriver* driver,
      ResourceManager* rm);
  virtual ~GameGraph();

  void Reload(irr::IrrlichtDevice* dev, irr::video::IVideoDriver* driver);
  irr::video::IVideoDriver* GetDriver(void);
  irr::scene::ISceneManager* GetSceneManager(void);
  irr::scene::ISceneCollisionManager* GetSceneCollisionManager(void);
  irr::gui::IGUIEnvironment* GetUserInterface(void);
  irr::video::IVideoDriver* GetVideoDriver(void);
  irr::ITimer* GetTimer(void);
  irr::IrrlichtDevice* GetDevice(void);
  ResourceManager* GetResourceManager(void);
  CoordinateTranslator* GetCoordinateTranslator(void);
  void AddGameState(irr::core::stringc name,
      State<GameGraph, irr::SEvent>* state);

  void SetResolutionWidth(int);
  int GetResoultionWidth(void);

  void SetResolutionHeight(int);
  int GetResolutionHeight(void);

  irr::core::list<irr::core::stringw*>& GetMessageQueue(void);

  ///This method is to capture events from the irrlicht IEventReceiver interface
  ///and redirect them to our own methods.
  virtual bool OnEvent(const irr::SEvent& event);

private:
  irr::IrrlichtDevice* device;
  irr::video::IVideoDriver* driver;
  ResourceManager* resourceManager;
  int resolutionWidth;
  int resolutionHeight;
  irr::core::list<irr::core::stringw*> messageQueue;

  struct SState
  {
    SState(irr::core::stringc name, State<GameGraph, irr::SEvent>* state = NULL) :
      Name(name), StateVal(state)
    {
    }

    bool operator<(const SState& other) const
    {
      return Name < other.Name;
    }

    irr::core::stringc Name;
    State<GameGraph, irr::SEvent>* StateVal;
  };

  irr::core::array<SState> States;

};

#endif /* GAMEGRAPH_H_ */
