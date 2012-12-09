/*
 * ResoureManager.h
 *
 *  Created on: Nov 3, 2010
 *      Author: Ryan Maloney
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "ResourceBundle.h"
#include <irrlicht.h>

class ResourceManager
{
public:
  ResourceManager();
  virtual ~ResourceManager();
  ResourceBundle* GetResourceBundle(irr::core::stringc resourceBundleName);

private:
  irr::core::map<irr::core::stringc, ResourceBundle*> resourceBundleMap;

};

#endif /* RESOURCEMANAGER_H_ */
