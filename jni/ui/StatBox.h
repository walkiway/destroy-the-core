/*
 * StatBox.h
 *
 * This UI element represents the character's status, containing present health
 * levels, the character's name and the name of the current world.
 *  Created on: Apr 28, 2011
 *      Author: Ryan Maloney
 */

#ifndef STATBOX_H_
#define STATBOX_H_

#include <irrlicht.h>
#include <IGUIElement.h>
#include "entities/PlayerCharacter.h"

class StatBox: public irr::gui::IGUIElement
{
public:
  StatBox(irr::gui::IGUIEnvironment* environment,
      irr::gui::IGUIElement* parent, irr::s32 id,
      const irr::core::rect<irr::s32>& rectangle, PlayerCharacter* pc);
  virtual ~StatBox();
  virtual void draw();

private:
  PlayerCharacter* hero;
};

#endif /* STATBOX_H_ */
