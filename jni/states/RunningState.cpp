/*
 * RunningState.cpp
 *
 *  Created on: Mar 15, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "RunningState"

#include "RunningState.h"
#include "util/LoggingMacros.h"
#include "ui/HeadsUpDisplay.h"
#include "states/WorldState.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;
using namespace video;

RunningState::RunningState() :
  _combatEngine(NULL), _hexMap(NULL), hero(NULL)
{
  _combatEngine = NULL;
}

RunningState::~RunningState()
{
}

void RunningState::OnEnter(GameGraph* game)
{
  //Initialize the states map and hero pointers. Neither of this should change until this state
  //changes and OnEnter is called again.
  WorldState* worldState = static_cast<WorldState*> (game->GetWorldState());
  if (NULL != worldState)
  {
    hero = worldState->GetHero();
    _hexMap = worldState->GetCurrentMap();
  }

  rect<s32> hudArea(0, 0, game->GetResoultionWidth(),
      game->GetResolutionHeight());
  IGUIElement * hud = new HeadsUpDisplay(game->GetUserInterface(),
      game->GetUserInterface()->getRootGUIElement(), 217822167, hudArea, hero, game->GetMessageQueue());
  hud->setEnabled(true);
  hud->setVisible(true);
  hud->drop();
  hud = NULL;
}

void RunningState::OnLeave(GameGraph* entity)
{

}

void RunningState::OnUpdate(GameGraph* game)
{
  if (NULL != hero && hero->IsAlive() && _userActions.size() > 0)
  {
    //The player has chosen to act on their turn. Pull the latest action off the event queue for processing.
    UserAction latestAction = PopLatestUserAction();
    //Determine if the action should be construed as an attack or a move.  If the player
    //has moved in the direction of a hex or to a hex that does not contain a monster it is a move.
    //Otherwise an attack has been initiated.
    position2d<s32> currentPosition = hero->GetPosition();

    switch (latestAction.Type)
    {
    case MoveUp:
      currentPosition.Y--;
      break;
    case MoveDown:
      currentPosition.Y++;
      break;
    case MoveLeft:
      currentPosition.X--;
      break;
    case MoveRight:
      currentPosition.X++;
      break;
    case MoveToLocation:
      currentPosition.X = latestAction.MoveToLocation.MapX;
      currentPosition.Y = latestAction.MoveToLocation.MapY;
      break;
    };
//    HexTile* tile = _hexMap->GetTileAt(currentPosition);
//    if ( (NULL == tile)
//        || tile->)
//    {}
    if (currentPosition.X < 0 || currentPosition.X
        >= _hexMap->GetMapDimensions().Width)
    {
      currentPosition.X = hero->GetPosition().X;
    }
    else if (currentPosition.Y < 0 || currentPosition.Y
        >= _hexMap->GetMapDimensions().Height)
    {
      currentPosition.Y = hero->GetPosition().Y;
    }

    //Check to see if any monsters are at that position.
    Monster* attackTarget = NULL;
    list<Monster*>::Iterator begin = _hexMap->GetFirstMonster();
    list<Monster*>::Iterator end = _hexMap->GetLastMonster();

    for (; begin != end; begin++)
    {
      if ((*begin)->IsAlive() && (*begin)->GetPosition() == (currentPosition))
      {
        attackTarget = *begin;
        break;
      }
    }

    //If so, attack
    if (NULL != attackTarget)
    {
      _combatEngine->ResolveCombat(hero, attackTarget, game->GetMessageQueue());

      if (!attackTarget->IsAlive())
      {
        ISceneNode* sn = game->GetSceneManager()->getSceneNodeFromId(
            attackTarget->GetSceneNodeId(), NULL);
        if (NULL != sn)
        {
          sn->removeAnimators();
          sn->remove();
          sn->drop();
          sn = NULL;
        }
        else
        {
          LOGE("Could not find scene node with id %d", attackTarget->GetSceneNodeId());
        }
      }
    }
    else
    {
      //Otherwise just move:
      hero->SetPosition(currentPosition);

      //Add message to global message queue.
      list<stringw*>& mq = game->GetMessageQueue();
      stringw* msg = new stringw("Hero is moving to ");
      msg->append(stringw(currentPosition.X));
      msg->append(",");
      msg->append(stringw(currentPosition.Y));
      mq.push_back(msg);
    }

    //Now update monsters, send in hero's location to save searching.  Each monster will figure out
    //if it is aware of the hero and/or has LOS.
    begin = _hexMap->GetFirstMonster();

    for (; begin != end; begin++)
    {
      if ((*begin)->IsAlive())
      {
        //TODO: Replace with a far more robust AI
        position2d<s32> heroPos = hero->GetPosition();
        position2d<s32> monsterPos = (*begin)->GetPosition();
        if ((abs(heroPos.X - monsterPos.X) <= 1) && (abs(
            heroPos.Y - monsterPos.Y) <= 1))
        {
          _combatEngine->ResolveCombat((*begin), hero, game->GetMessageQueue());
          if (!hero->IsAlive())
          {
            monsterPos = heroPos;
            ISceneNode* sn = game->GetSceneManager()->getSceneNodeFromId(
                hero->GetSceneNodeId(), NULL);
            if (NULL != sn)
            {
              sn->removeAnimators();
              sn->remove();
              sn->drop();
              sn = NULL;
            }
            else
            {
              LOGE("Could not find scene node with id %d", hero->GetSceneNodeId());
            }
          }
        }
        else
        {
          int random = rand() % 5;
          //Move Randomly
          switch (random)
          {
          case 0:
            monsterPos.X++;
            break;

          case 1:
            monsterPos.Y++;
            break;

          case 2:
            monsterPos.X++;
            monsterPos.Y++;
            break;

          case 3:
            monsterPos.X--;
            break;

          case 4:
            monsterPos.Y--;
            break;

          case 5:
            monsterPos.X--;
            monsterPos.Y--;
            break;
          }

          if ((monsterPos.X < 0) || (monsterPos.X
              >= _hexMap->GetMapDimensions().Width))
          {
            monsterPos.X = (*begin)->GetPosition().X;
          }
          else if ((monsterPos.Y < 0) || (monsterPos.Y
              >= _hexMap->GetMapDimensions().Height))
          {
            monsterPos.Y = (*begin)->GetPosition().Y;
          }
        }
        (*begin)->SetPosition(monsterPos);
      }
    }
  }
  else
  {
    //The player is not using their turn yet.  This turn is NOT skipped, the world waits for the player.
  }
}

void RunningState::OnReload(GameGraph* game)
{
  //Reload HUD, use the existing hero pointer without repulling from the current world state
  //as this will not have changed on a reload.
  rect<s32> hudArea(0, 0, game->GetResoultionWidth(),
      game->GetResolutionHeight());
  LOGE("LOWER RIGHT IS : %d Game res width is %d", hudArea.LowerRightCorner.X, game->GetResoultionWidth());
  IGUIElement * hud = new HeadsUpDisplay(game->GetUserInterface(),
      game->GetUserInterface()->getRootGUIElement(), 217815467, hudArea, hero, game->GetMessageQueue());
  hud->setEnabled(true);
  hud->setVisible(true);
  hud->drop();
  hud = NULL;
}

bool RunningState::OnEvent(GameGraph* entity, SEvent event)
{
  LOGD("Receving event...");

  if (irr::EET_KEY_INPUT_EVENT == event.EventType && event.KeyInput.PressedDown)
  {
    LOGD("Key input event received, Key Code is %x", event.KeyInput.Key);

    UserAction userAction;

    switch (event.KeyInput.Key)
    {
    case KEY_UP:
      userAction.Type = MoveUp;
      break;
    case KEY_DOWN:
      userAction.Type = MoveDown;
      break;
    case KEY_LEFT:
      userAction.Type = MoveLeft;
      break;
    case KEY_RIGHT:
      userAction.Type = MoveRight;
      break;
    };

    _userActions.push_front(userAction);
  }
  else if (irr::EET_TOUCH_EVENT == event.EventType)
  {
    UserAction userAction;
    userAction.Type = MoveToLocation;
    userAction.MoveToLocation.MapX = event.TouchEvent.MapX;
    userAction.MoveToLocation.MapY = event.TouchEvent.MapY;
    _userActions.push_front(userAction);
  }

  return false;
}

UserAction RunningState::GetLatestUserAction()
{
  list<UserAction>::Iterator firstElement = _userActions.begin();
  return *firstElement;
}

UserAction RunningState::PopLatestUserAction()
{
  list<UserAction>::Iterator firstElement = _userActions.begin();
  UserAction userAction = *firstElement;
  _userActions.erase(firstElement);
  return userAction;
}
