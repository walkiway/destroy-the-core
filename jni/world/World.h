/*
 * World.h
 *
 *  Created on: Nov 7, 2010
 *      Author: ryan
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <irrlicht.h>

class World
{
public:
  World();
  virtual ~World();

private:
  irr::core::stringc* _name;

//  +(NSArray*) monstersInWorld
//
//  +(NSArray*) mobsInWorld:(int)worldNum;
//
//  +(NSArray*) respawnsInWorld:(int) worldNum;
//
//  +(int) bossLevelForWorld:(int) worldNum;
//
//  +(NSString*) musicForWorld:(int)worldNum Level:(int) levelNum;
//
//  +(int) numberOfWorlds;
//
//  +(int) numberOfLevelsInWorld:(int) worldNum;
//
//  +(NSString*) tilesetForWorld:(int) worldNum;

};

#endif /* WORLD_H_ */
