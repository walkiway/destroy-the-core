/*
 * HeadsUpDisplay.h
 *
 *  Created on: May 30, 2011
 *      Author: Ryan Maloney
 */

#ifndef HEADSUPDISPLAY_H_
#define HEADSUPDISPLAY_H_

#include <IGUIElement.h>
#include "irrlicht.h"
#include "entities/PlayerCharacter.h"

class HeadsUpDisplay: public irr::gui::IGUIElement
{
public:
  HeadsUpDisplay(irr::gui::IGUIEnvironment* environment,
      irr::gui::IGUIElement* parent, irr::s32 id,
      const irr::core::rect<irr::s32>& rectangle, PlayerCharacter* hero, irr::core::list<irr::core::stringw*>& messageQueue);
  virtual ~HeadsUpDisplay();
  virtual void draw();

private:
  PlayerCharacter* hero;
};

#endif /* HEADSUPDISPLAY_H_ */
