/*
 * CreatureDefinitionFileManager.h
 *
 *  Created on: Jan 14, 2011
 *      Author: Ryan Maloney
 */

#ifndef CREATUREDEFINITIONFILEMANAGER_H_
#define CREATUREDEFINITIONFILEMANAGER_H_

#include <irrlicht.h>
#include "util/ResourceManager.h"
#include "entities/builders/CreatureDefinition.h"
#include "entities/builders/CreatureSet.h"

class CreatureDefinitionFileManager
{
public:
  virtual ~CreatureDefinitionFileManager();
  static CreatureSet* PopulateCreatureSet(ResourceManager* resourceManager,
      irr::core::stringc resourceName);
private:
  CreatureDefinitionFileManager();
};

#endif /* CREATUREDEFINITIONFILEMANAGER_H_ */
