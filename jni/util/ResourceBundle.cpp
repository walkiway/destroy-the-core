#include "ResourceBundle.h"
#include <string.h>
#include <android/log.h>

#define  LOG_TAG    "ResourceBundle"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace irr;
using namespace core;

ResourceBundle::ResourceBundle(stringc bundleRoot) : bundleRootName(bundleRoot)
{
}

ResourceBundle::~ResourceBundle()
{
}

void ResourceBundle::Add(AndroidReadFile* androidReadFile)
{
  resourceList.push_front(androidReadFile);
}

AndroidReadFile* ResourceBundle::Find(stringc resourceName)
{
  list<AndroidReadFile*>::Iterator begin = resourceList.begin();
  list<AndroidReadFile*>::Iterator end = resourceList.end();

  AndroidReadFile* androidReadFile = NULL;

  for(; begin != end; begin++)
  {
    LOGD("Comparing %s and %s...", (*begin)->getFileName().c_str(), resourceName.c_str());
    if (0 == strcmp((*begin)->getFileName().c_str(), resourceName.c_str()))
    {
      LOGD("Found Match");
      androidReadFile = *begin;
      break;
    }
  }

  return androidReadFile;
}


