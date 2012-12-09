/*
 * RunningState.h
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */

#ifndef RUNNINGSTATE_H_
#define RUNNINGSTATE_H_

#include "util/State.h"
#include "states/GameGraph.h"
#include <irrlicht.h>
#include "world/HexMap.h"
#include "CombatEngine.h"
#include "entities/PlayerCharacter.h"

enum UserActionType
{
  MoveUp, MoveDown, MoveLeft, MoveRight, MoveToLocation
};

struct MoveUpAction
{
};
struct MoveDown
{
};
struct MoveLeft
{
};
struct MoveRight
{
};
struct MoveToLocation
{
  int MapX;
  int MapY;
};

struct UserAction
{
  UserActionType Type;
  union
  {
    struct MoveUpAction MoveUp;
    struct MoveDown MoveDown;
    struct MoveLeft MoveLeft;
    struct MoveRight MoveRight;
    struct MoveToLocation MoveToLocation;
  };
};

class RunningState: public State<GameGraph, irr::SEvent>
{
public:
  RunningState();
  virtual ~RunningState();

  virtual void OnEnter(GameGraph* entity);
  virtual void OnLeave(GameGraph* entity);
  virtual void OnUpdate(GameGraph* entity);
  virtual bool OnEvent(GameGraph* entity, irr::SEvent event);
  virtual void OnReload(GameGraph* entity);

private:
  UserAction GetLatestUserAction();
  UserAction PopLatestUserAction();
  irr::core::list<UserAction> _userActions;
  CombatEngine* _combatEngine;
  HexMap* _hexMap;
  PlayerCharacter* hero;
};

#endif /* RUNNINGSTATE_H_ */
