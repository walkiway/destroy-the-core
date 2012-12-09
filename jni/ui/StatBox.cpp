/*
 * StatBox.cpp
 *
 *  Created on: Apr 28, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "StatBox"
#include "StatBox.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

StatBox::StatBox(IGUIEnvironment* environment, IGUIElement* parent, s32 id,
    const rect<s32>& rectangle, PlayerCharacter* pc) :
  IGUIElement(EGUIET_ELEMENT, environment, parent, id, rectangle), hero(pc)
{
}

StatBox::~StatBox()
{
  // TODO Auto-generated destructor stub
}

void StatBox::draw()
{
  if ( isVisible() )
  {
    //Calculate what percentage of life the hero has left.
    float percentageAlive = (hero->GetLifeMeter() * 1.0) / (hero->GetMaxLifeMeter() * 1.0);
    LOGD("Percentage alive is: %f", percentageAlive);

    //Take that same percentage of the health bar's total length and display the
    //same percentage.
    int value = floor( (60.0 * percentageAlive) + 0.5);
    //The bar starts at 15 so add the total length to that value
    int xValue = (value > 0) ? value + 15 : 0;

    IGUISkin *guiSkin = Environment->getSkin();
    //Stat box outine
    guiSkin->draw2DRectangle(this, SColor(255, 255, 255, 255), rect<s32>(10, 10, 80, 35));
    //Life Meter
    guiSkin->draw2DRectangle(this, SColor(255, 255, 0, 0), rect<s32>(15, 15, xValue, 20));
    //Magic Meter
    guiSkin->draw2DRectangle(this, SColor(255, 0, 0, 255), rect<s32>(15, 25, 75, 30));

    //Call Base class
    IGUIElement::draw();
  }
}
