/*
 * CreatureSet.h
 *
 *  Created on: Jan 14, 2011
 *      Author: Ryan Maloney
 */

#ifndef CREATURESET_H_
#define CREATURESET_H_

#include "CreatureDefinition.h"
#include "util/ResourceManager.h"
#include <irrlicht.h>

class CreatureSet
{
public:
  CreatureSet(irr::core::stringc worldName, irr::core::stringc resourceName);
  virtual ~CreatureSet();

  //Add an existing CreatureDefinition to the CreatureSet.  Once a CreatureDefintion
  //has been added memory management responsibility passes to this CreatureSet.
  void Add(CreatureDefinition*);

  //Return the tile definition identified by the supplied name, e.g. wall-upper-left-corner
  CreatureDefinition* GetByName(irr::core::stringc);

  //Register all of the textures associated with the contained sprites with irrlicht.
  bool RegisterTextures(irr::video::IVideoDriver* videoDriver, ResourceManager* resourceManager);

  int GetSpriteWidth();
  void SetSpriteWidth(int);

  int GetSpriteHeight();
  void SetSpriteHeight(int);

  //Acessors only
  irr::core::stringc GetWorldName();
  irr::core::stringc GetResourceName();
  unsigned int GetNumberOfCreatures();

private:
  //The name of the world this creature set is associated with.
  irr::core::stringc _worldName;

  //The name of the resource file containing the tilesheet, e.g. tilesheet.png
  irr::core::stringc _resourceName;

  //Tile definitions keyed by name.  This means that tiles
  //contained in one set must be uniquely named.
  irr::core::map<irr::core::stringc, CreatureDefinition*> _creatures;

  int spriteWidth;
  int spriteHeight;
};

#endif /* CREATURESET_H_ */
