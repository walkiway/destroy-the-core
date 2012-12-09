/*
 * PreFabbedFileManager.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Ryan Maloney
 */

#ifndef PREFABBEDFILEMANAGER_H_
#define PREFABBEDFILEMANAGER_H_

#include "world/builders/MapBuilder.h"
#include "util/ResourceManager.h"

class PreFabbedFileManager
{
public:
  PreFabbedFileManager(ResourceManager* resourceManager);
  virtual ~PreFabbedFileManager();

  //Populates the "pre fabbed room" buckets in the supplied MapBuilder instance.
  void Populate(irr::core::stringc filename, MapBuilder* mapBuilder);

private:
  void PopulateWorldWeights(char* line, int& banditWorldWeight, int& dungeonWorldWeight, int& hellWorldWeight);
  ResourceManager* _resourceManager;
};

#endif /* PREFABBEDFILEMANAGER_H_ */
