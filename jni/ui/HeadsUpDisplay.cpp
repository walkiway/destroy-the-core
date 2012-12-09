/*
 * HeadsUpDisplay.cpp
 *
 *  Created on: May 30, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "HeadsUpDisplay"
#include "HeadsUpDisplay.h"
#include "ui/StatBox.h"
#include "ui/MessageWindow.h"
#include "util/LoggingMacros.h"
#include <irrArray.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

HeadsUpDisplay::HeadsUpDisplay(IGUIEnvironment* environment,
    IGUIElement* parent, s32 id, const rect<s32>& rectangle,
    PlayerCharacter* pc, list<stringw*>& messageQueue) :
  IGUIElement(EGUIET_ELEMENT, environment, parent, id, rectangle), hero(pc)
{
  //Debugging code
  //  staticText = game->GetUserInterface()->addStaticText(L"FPS:", rect<s32> (400,
  //      60, 450, 60 + 32));
  //  staticText->setOverrideColor(SColor(255, 255, 255, 255));
  //GUI update
  // stringw str = " FPS: ";
  //  str += (s32) game->GetDriver()->getFPS();
  //  str.trim();
  //
  //  staticText->setText(str.c_str());

  //Add a stat box.
  IGUIElement* statBox = new StatBox(Environment, this, 22215467,
      rect<s32> (10, 10, 80, 75), hero);
  bringToFront(statBox);
  statBox->setVisible(true);
  statBox->setEnabled(true);
  statBox->setSubElement(true);
  statBox->drop();
  statBox = NULL;

  //Calculate rect based on current layout (portrait vs landscape)
  int ulX = rectangle.LowerRightCorner.X - 180;
  int ulY = 10;
  int lrX = rectangle.LowerRightCorner.X - 10;
  int lrY = 75;

  IGUIElement* messageWindow = new MessageWindow(Environment, this, 22215468,
      rect<s32> (ulX, ulY, lrX, lrY), messageQueue, 5);
  bringToFront(messageWindow);
  messageWindow->setVisible(true);
  messageWindow->setEnabled(true);
  messageWindow->setSubElement(true);
  messageWindow->drop();
  messageWindow = NULL;
}

HeadsUpDisplay::~HeadsUpDisplay()
{
  // TODO Auto-generated destructor stub
}

void HeadsUpDisplay::draw()
{
  IGUIElement::draw();
}
