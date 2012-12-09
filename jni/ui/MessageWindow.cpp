/*
 * MessageWindow.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: Ryan Maloney
 */
#define LOG_TAG "MessageWindow"
#include "MessageWindow.h"
#include "util/LoggingMacros.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;

MessageWindow::MessageWindow(IGUIEnvironment* environment, IGUIElement* parent,
    s32 id, const rect<s32>& rectangle, list<stringw*>& mQueue, int bufferSize) :
  IGUIElement(EGUIET_ELEMENT, environment, parent, id, rectangle),
      messageQueue(mQueue), bufferSize(bufferSize)
{
  internalMessageBuffer.reallocate(bufferSize);
  internalTextRows.reallocate(bufferSize);
  int ulX = rectangle.UpperLeftCorner.X + 1;
  int lrX = rectangle.LowerRightCorner.X - 1;
  int rowHeight = rectangle.getHeight() / bufferSize;

  int i;
  for (i = 0; i < bufferSize; i++)
  {
    //Initialize static text fields
    int ulY = rectangle.UpperLeftCorner.Y + (i * rowHeight);
    int lrY = ulY + rowHeight;
    rect<s32> textRect = rect<s32> (ulX, ulY, lrX, lrY);
    internalTextRows[i] = environment->addStaticText(L"", textRect);
    internalTextRows[i]->setOverrideColor(SColor(255, 255, 255, 255));

    //Initialize values in internal message buffer;
    internalMessageBuffer[i] = NULL;
  }
}

MessageWindow::~MessageWindow()
{
  // TODO Auto-generated destructor stub
}

void MessageWindow::draw()
{
  if (isVisible())
  {
    IGUISkin *guiSkin = Environment->getSkin();

    //Always draw stat box outine
    guiSkin->draw2DRectangle(this, SColor(100, 0, 0, 0), getAbsolutePosition());

    //Check to see if there are messages to pull from the queue
    if (messageQueue.size() > 0)
    {
      //Pull message from the head.
      list<stringw*>::Iterator head = messageQueue.begin();
      stringw* message = *head;
      if (NULL != message)
      {
        //Delete the oldest message from this widgets internal buffer
        //if it is already at capacity.
        if (internalMessageBuffer.size() >= bufferSize)
        {
          stringw* messageToDelete = internalMessageBuffer[0];
          if (NULL != messageToDelete)
          {
            delete messageToDelete;
            internalMessageBuffer.erase(0);
          }
        }

        //Push the latest buffer onto the back of the internal message buffer.
        internalMessageBuffer.push_back(message);

        //Erase the entry from the global message queue now that it has been consumed
        messageQueue.erase(head);
      }
    }

    int i;
    for (i = 0; i < bufferSize; i++)
    {
      stringw* message = internalMessageBuffer[i];
      if (NULL != message)
      {
        //        LOGE("The internal messagw buffer has the following message at index %d: %ls", i, message->c_str());
        internalTextRows[i]->setText(message->c_str());
      }
      else
      {
        internalTextRows[i]->setText(L"");
      }
    }

    //Call base class
    IGUIElement::draw();
  }
}
