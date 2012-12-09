/*
 * DestroyTheCoreRenderer.cpp
 *
 *  Created on: Nov 25, 2010
 *      Author: Ryan Maloney
 */
#define  LOG_TAG    "DestroyTheCoreRenderer"

#include "DestroyTheCoreRenderer.h"
#include <stdio.h>
#include <irrlicht.h>
#include "Game.h"
#include "util/LoggingMacros.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//Initialize global device, driver and event receiver
IrrlichtDevice* g_Device = NULL;
IVideoDriver* g_Driver = NULL;

void Java_com_errantgames_DestroyTheCoreRenderer_nativeInitGL(JNIEnv* env,
    jobject thiz)
{
  LOGI("Invoking native nativeInitGL()");
}

void Java_com_errantgames_DestroyTheCoreRenderer_nativeResize(JNIEnv* env,
    jobject thiz, jint width, jint height)
{
  LOGE("Invoking native nativeResize(), requested width is %d and height is %d.", (int)width, (int)height);

  //NOTE: There are two distinct cases here that each use the same logic. The first is one where the this resize
  //is being called because the resolution has actually changed. In this situation the driver needs to be created anew
  //because the resolution cannot be changed dynamically. The second occurs when this method is called because the game
  //has been paused and is now being resumed and moved to the front. In this case the resoultion hasn't changed and the
  //driver is still valid so all we need to do is reload the textures. The problem is that the custom SceneNodes are pointing
  //at now invalid texture objects and there is no efficient way to iterate through all of them to reload all the textures.
  //Thus we resort to the rebuild.

  //If there is an existing device, delete it before recreate
  if (NULL != g_Device)
  {
    g_Device->drop();
  }

  int windowWidth = (int) width;
  int windowHeight = (int) height;

  SIrrlichtCreationParameters parameters;
  parameters.AntiAlias = 0;
  parameters.Bits = 32;
  parameters.ZBufferBits = 32;
  parameters.DriverType = video::EDT_OGLES1;
  parameters.Fullscreen = true;
  parameters.Stencilbuffer = false;
  parameters.Vsync = false;
  parameters.WindowSize = dimension2d<u32> (windowWidth, windowHeight);
  parameters.Doublebuffer = true;

  g_Device = createDeviceEx(parameters);
  g_Driver = g_Device->getVideoDriver();
  g_Driver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT);

  LOGI("Created Device: r=%d width=%d height=%d", g_Device, windowWidth, windowHeight);

  LOGI("Retrieved driver r=%d", g_Driver);

  if (!g_Device)
  {
    LOGE("Unable to retrieve a device.");
  }
  if (!g_Driver)
  {
    LOGE("Unable to retrieve a video driver.");
  }

  if (g_Device && g_Driver)
  {
    //Load (or Reload if already loaded) game
    Load(windowWidth, windowHeight);
  }

}

void Java_com_errantgames_DestroyTheCoreRenderer_nativeGetStatus(JNIEnv* env,
    jobject thiz, jobject status)
{
  //LOGI("Invoking native nativeGetStatus()");
}

void Java_com_errantgames_DestroyTheCoreRenderer_nativeSendEvent(JNIEnv* env,
    jobject thiz, jobject event)
{
  LOGI("Invoking native nativeSendEvent()");
}

void Java_com_errantgames_DestroyTheCoreRenderer_nativeDrawIteration(
    JNIEnv* env, jobject thiz)
{
  Update();
  Render();
}
