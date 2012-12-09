/*
 * CombatEngine.cpp
 *
 *  Created on: Mar 13, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "CombatEngine"

#include "CombatEngine.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;

CombatEngine::CombatEngine()
{
  // TODO Auto-generated constructor stub

}

CombatEngine::~CombatEngine()
{
  // TODO Auto-generated destructor stub
}

void CombatEngine::ResolveCombat(Creature* initiator, Creature* defender, list<stringw*>& messageQueue)
{
  //EARLY RETURN WARNING!
  if ((NULL == initiator) || (NULL == defender))
  {
    return;
  }
  //This is an odd case and indicative of a problem so log it.
  if (!initiator->IsAlive() || !defender->IsAlive())
  {
    return;
  }

  //TODO: Determine hit % to see if initiator hits the defender.
  //For now we assume 100% hit chance
  bool doesHit = true;

  //If initiator made contact
  if (doesHit)
  {
    //Determine the amout of damage inflicted based on the initiators attack power
    //and compare it to the initiators->defense power.  Subtract the difference from the defenders
    //life meter.
    int difference = initiator->GetAttackPower() - defender->GetDefensePower();
    defender->DecreaseLifeMeter(difference);

    //Add a message to the global message queue
    stringw* msg = new stringw(initiator->GetName());
    msg->append(" does ");
    msg->append(stringw(difference));
    msg->append(" to ");
    msg->append(defender->GetName());
    messageQueue.push_back(msg);
  }
  else
  {
    //Add a message to the global message queue
    stringw* msg = new stringw(initiator->GetName());
    msg->append(" misses ");
    msg->append(defender->GetName());
    messageQueue.push_back(msg);
  }
}
