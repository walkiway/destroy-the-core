/*
 * ResoureManager.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: ryan
 */

#include "ResourceManager.h"

using namespace irr;
using namespace core;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
  if (!resourceBundleMap.empty())
  {
    map<stringc, ResourceBundle*>::Iterator iterator =
        resourceBundleMap.getIterator();
    while (!iterator.atEnd())
    {
      map<stringc, ResourceBundle*>::Node* node = iterator.getNode();
      ResourceBundle* resourceBundle = node->getValue();
      if (NULL != resourceBundle)
      {
        delete (resourceBundle);
      }
      iterator++;
    }

    resourceBundleMap.clear();
  }
}

ResourceBundle* ResourceManager::GetResourceBundle(stringc resourceBundleName)
{
  ResourceBundle* resourceBundle = NULL;

  map<stringc, ResourceBundle*>::Node* node = resourceBundleMap.find(resourceBundleName);
  if (NULL == node)
  {
   resourceBundle = new ResourceBundle(resourceBundleName);
   resourceBundleMap.insert(resourceBundleName, resourceBundle);
  }
  else
  {
    resourceBundle = node->getValue();
  }
  return resourceBundle;
}
