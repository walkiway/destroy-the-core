#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <irrlicht.h>
#include "util/ResourceManager.h"
#include "util/CoordinateTranslator.h"
#include "states/GameGraph.h"

void Load(int resolutionWidth, int resolutionHeight);
void Update();
void Render();
void Resize(int width, int height);

extern GameGraph* g_GameGraph; // Initialized in Game.cpp
extern irr::IrrlichtDevice* g_Device; //Initialized in RoguelikeRenderer
extern irr::video::IVideoDriver* g_Driver; //Initialized in RoguelikeRenderer
extern ResourceManager* g_OhrResourceManager; //Initialized in Roguelike

#endif
