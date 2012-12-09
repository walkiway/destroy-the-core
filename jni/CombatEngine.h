/*
 * CombatEngine.h
 *
 *  Created on: Mar 13, 2011
 *      Author: Ryan Maloney
 */

#ifndef COMBATENGINE_H_
#define COMBATENGINE_H_

#include "entities/Creature.h"
#include <irrlicht.h>

class CombatEngine
{
public:
  CombatEngine();
  virtual ~CombatEngine();
  void ResolveCombat(Creature* initiator, Creature* defender, irr::core::list<irr::core::stringw*>& messageQueue);
};

#endif /* COMBATENGINE_H_ */
