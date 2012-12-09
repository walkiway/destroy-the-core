/*
 * CreatureDefinition.h
 *
 *  Created on: Jan 14, 2011
 *      Author: Ryan Maloney
 */

#ifndef CREATUREDEFINITION_H_
#define CREATUREDEFINITION_H_

#include <irrlicht.h>

class CreatureDefinition
{
public:
  CreatureDefinition();
  virtual ~CreatureDefinition();

  void SetName(irr::core::stringc);
  irr::core::stringc GetName();

  void SetWorldName(irr::core::stringc);
  irr::core::stringc GetWorldName();

  int GetWidth(void);
  void SetWidth(int);

  int GetHeight(void);
  void SetHeight(int);

  int GetAtlasIndex(void);
  void SetAtlasIndex(int);

  int GetIndexLength(void);
  void SetIndexLength(int);

  int GetLifeMeter(void);
  void SetLifeMeter(int);

  int GetMaxLifeMeter(void);
  void SetMaxLifeMeter(int);

private:
  irr::core::stringc name;
  irr::core::stringc worldName;
  int width;
  int height;
  int atlasIndex;
  int indexLength;
  int lifeMeter;
  int maxLifeMeter;
};

#endif /* CREATUREDEFINITION_H_ */
