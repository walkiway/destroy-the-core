/*
 * DestroyTheCore.cpp
 *
 *  Created on: Nov 25, 2010
 *      Author: Ryan Maloney
 */

#define  LOG_TAG    "DestroyTheCore"

#include "DestroyTheCore.h"
#include <unistd.h>
#include <irrlicht.h>
#include "Game.h"
#include "util/ResourceBundle.h"
#include "world/io/MapFileManager.h"
#include "util/LoggingMacros.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

stringc* apkFilePathC = NULL;
ResourceManager* g_OhrResourceManager = NULL;


void Java_com_errantgames_DestroyTheCore_nativeSetApkPath(JNIEnv* env,
    jobject thiz, jstring apkFilePath)
{
  jboolean blnIsCopy;

  const char* temp = env->GetStringUTFChars(apkFilePath, &blnIsCopy);

  const int stringLength = strlen(temp) + 1;
  char newString[stringLength];
  strcpy(newString, temp);

  apkFilePathC = new stringc(newString);

  LOGI("Attempting to open the .apk file %s", apkFilePathC->c_str() );

  FILE* testOpen = fopen(apkFilePathC->c_str(), "rb");

  if (NULL != testOpen)
  {
    LOGI(".apk file successfully opened.");
  }
  else
  {
    LOGE(".apk file failed to open.");
  }

  env->ReleaseStringUTFChars(apkFilePath, temp);
}

void Java_com_errantgames_DestroyTheCore_nativeAddResource(JNIEnv* env,
    jobject thiz, jstring resourceBundle, jstring resourceName,
    jlong startOffset, jlong fileLength)
{
  LOGI("Invoking native nativeAddResource()");

  AndroidReadFile* androidReadFile = NULL;

  //All files are read as offsets into the apk file instead of as discrete files.
  LOGD("Attempting to open apk file %s...", apkFilePathC->c_str());
  FILE* apkFile = fopen(apkFilePathC->c_str(), "rb"); //fdopen(myfd, "rb");
  LOGD("Finished attempt to open apk file %s", apkFilePathC->c_str());

  if (NULL != apkFile)
  {
    jboolean blnIsCopy;

    const char* resourceBundleCstring = env->GetStringUTFChars(resourceBundle,
        &blnIsCopy);
    const char* resourceNameCstring = env->GetStringUTFChars(resourceName,
        &blnIsCopy);

    ResourceBundle* resourceBundleFile =
        g_OhrResourceManager->GetResourceBundle(resourceBundleCstring);

    LOGI("Creating AndroidReadFile with file length %i...", (long)fileLength);
    androidReadFile = new AndroidReadFile(resourceNameCstring, apkFile,
        startOffset, (long) fileLength);
    resourceBundleFile->Add(androidReadFile);
    LOGI("New AndroidReadFile has been added to the ResourceManager");

    env->ReleaseStringUTFChars(resourceBundle, resourceBundleCstring);
    env->ReleaseStringUTFChars(resourceName, resourceNameCstring);
  }
  else
  {
    LOGE("Could not open the apk file at %s so resoures will not be loaded.", apkFilePathC->c_str());
  }

}

void Java_com_errantgames_DestroyTheCore_nativeOnCreate(JNIEnv* env,
    jobject thiz)
{
  LOGD("Invoking native nativeOnCreate()");
  g_OhrResourceManager = new ResourceManager();
}

void Java_com_errantgames_DestroyTheCore_nativeOnPause(JNIEnv* env,
    jobject thiz)
{
  LOGE("Invoking native nativeOnPause()");
}

void Java_com_errantgames_DestroyTheCore_nativeOnResume(JNIEnv* env,
    jobject thiz)
{
  LOGI("Invoking native nativeOnResume()");
}

void Java_com_errantgames_DestroyTheCore_nativeOnDestroy(JNIEnv* env,
    jobject thiz)
{
  LOGI("Invoking native nativeOnDestroy()");
}
