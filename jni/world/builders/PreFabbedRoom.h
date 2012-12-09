/*
 * PreFabbedRoom.h
 *
 * A prefabbed room as configured int he prefabbed-rooms configuration file.  These
 * rooms are the building blocks used by the MapBuilder to create maps for a given world.
 *
 *  Created on: Dec 7, 2010
 *      Author: Ryan Maloney
 */

#ifndef PREFABBEDROOM_H_
#define PREFABBEDROOM_H_
#include <irrlicht.h>

class PreFabbedRoom
{
public:
  PreFabbedRoom();
  virtual ~PreFabbedRoom();

private:
  int _weightBanditHole;
  int _weightDungeon;
  int _weightHell;
  int _unconnectedDoorLocations;
  int _connectedDoorLocations;
  irr::core::vector2d<int> _stairsUpLocation;
  irr::core::vector2d<int> _stairsDownLocation;
  irr::core::vector2d<int> _lockedDoorLocation;
  irr::core::vector2d<int> _shopkeeperLocation;
  irr::core::vector2d<int> _itemLockerLocation;
  irr::core::list<irr::core::vector2d<int> > _tileLocations;
  irr::core::list<irr::core::vector2d<int> > _treasureLocations;
  int _neighbors;
  irr::core::recti _boundingBox;
  irr::core::list<irr::core::vector2d<int> > _mobLocations;
  //@synthesize rangeOfMobsToUse;
};

#endif /* PREFABBEDROOM_H_ */
