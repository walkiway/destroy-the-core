/*
 * MessageWindow.h
 *
 *  Created on: Jun 1, 2011
 *      Author: Ryan Maloney
 */

#ifndef MESSAGEWINDOW_H_
#define MESSAGEWINDOW_H_

#include <IGUIElement.h>
#include <irrlicht.h>
#include <irrArray.h>
#include <IGUIStaticText.h>

class MessageWindow: public irr::gui::IGUIElement
{
public:
  MessageWindow(irr::gui::IGUIEnvironment* environment,
      irr::gui::IGUIElement* parent, irr::s32 id,
      const irr::core::rect<irr::s32>& rectangle,
      irr::core::list<irr::core::stringw*>& mQueue, int bufferSize);
  virtual ~MessageWindow();
  virtual void draw();

private:
  irr::core::list<irr::core::stringw*>& messageQueue;
  irr::core::array<irr::core::stringw*> internalMessageBuffer;
  int bufferSize;
  irr::core::array<irr::gui::IGUIStaticText*> internalTextRows;
};

#endif /* MESSAGEWINDOW_H_ */
