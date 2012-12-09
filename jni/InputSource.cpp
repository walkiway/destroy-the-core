/*
 * InputSource.cpp
 *
 *  Created on: Nov 24, 2010
 *      Author: Ryan Maloney
 */
#define LOG_TAG "InputSource"

#include <irrlicht.h>
#include "InputSource.h"
#include "util/LoggingMacros.h"
#include "Game.h"

using namespace irr;
using namespace core;
void Java_com_errantgames_input_InputSource_nativeKeyPress(JNIEnv* env,
    jobject thiz, jint keySymbol)
{
  LOGV("Native key press detected, symbol %x", keySymbol);

  if (NULL != g_GameGraph->GetDevice())
  {
    SEvent irrevent;
    irrevent.EventType = EET_KEY_INPUT_EVENT;
    irrevent.KeyInput.Key = (EKEY_CODE) keySymbol;
    irrevent.KeyInput.PressedDown = true;
    g_GameGraph->GetDevice()->postEventFromUser(irrevent);
  }
  else
  {
    LOGE("Unable to post keyboard event to receiver because device is null.");
  }
}

void Java_com_errantgames_input_InputSource_nativeKeyRelease(JNIEnv* env,
    jobject thiz, jint keySymbol)
{
  LOGV("Native key press detected, symbol %x", keySymbol);
  if (NULL != g_GameGraph->GetDevice())
  {
    SEvent irrevent;
    irrevent.EventType = EET_KEY_INPUT_EVENT;
    irrevent.KeyInput.Key = (EKEY_CODE) keySymbol;
    irrevent.KeyInput.PressedDown = false;
    g_GameGraph->GetDevice()->postEventFromUser(irrevent);
  }
  else
  {
    LOGE("Unable to post keyboard event to receiver because device is null.");
  }
}

void Java_com_errantgames_input_InputSource_nativeTouchPressDown(JNIEnv* env,
    jobject thiz, jfloat x, jfloat y)
{
  LOGV("Logging native touch press down event at %f x %f", x, y);
  if (NULL != g_GameGraph->GetDevice())
  {

    if (NULL == g_GameGraph->GetSceneCollisionManager())
    {
      LOGE("Collision manager is null!");
    }
    else
    {
      LOGE("Raw touch event coordinates (%f, %f)");

      line3d<f32> ray = g_GameGraph->GetSceneCollisionManager()->getRayFromScreenCoordinates(
          vector2d<s32> (x, y));
      LOGE("Touch event coords translated to world coordinates (%f, %f)", ray.end.X, ray.end.Y);

      position2d<s32> arrayCoord =
          g_GameGraph->GetCoordinateTranslator()->TranslateScreenCoords(ray.end.X, ray.end.Y);
      LOGE("Touch event translated to map coords (%f, %f)");

      SEvent irrevent;
      irrevent.EventType = EET_TOUCH_EVENT;
      irrevent.TouchEvent.Type = PRESS_DOWN;
      irrevent.TouchEvent.X = x;
      irrevent.TouchEvent.Y = y;
      irrevent.TouchEvent.WorldX = ray.end.X;
      irrevent.TouchEvent.WorldY = ray.end.Y;
      irrevent.TouchEvent.MapX = arrayCoord.X;
      irrevent.TouchEvent.MapY = arrayCoord.Y;
      g_GameGraph->GetDevice()->postEventFromUser(irrevent);
    }
  }
  else
  {
    LOGE("Unable to post touch event to receiver because device is null.");
  }
}
