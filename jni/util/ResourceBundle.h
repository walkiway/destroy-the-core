#ifndef __RESOURCE_BUNDLE_H_INCLUDED__
#define __RESOURCE_BUNDLE_H_INCLUDED__

#include "AndroidReadFile.h"
#include <string.h>
#include <irrlicht.h>
#include <irrList.h>

class ResourceBundle
{
public:
  ResourceBundle(irr::core::stringc bundleRoot);
  ~ResourceBundle();
  void Add(AndroidReadFile* androidReadFile);
  AndroidReadFile* Find(irr::core::stringc resourceName);

private:
  irr::core::list<AndroidReadFile*> resourceList;
  irr::core::stringc bundleRootName;
};

#endif
