#define  LOG_TAG    "Game"

#include "Game.h"
#include "view/GameLayer.h"
#include "util/LoggingMacros.h"
#include "states/GameGraph.h"
#include "states/WorldState.h"
#include "states/RunningState.h"
#include "view/CameraAnimator.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//Initialize global declarations
ISceneCollisionManager* g_ISceneCollisionManager = NULL;
CoordinateTranslator* g_CoordinateTranslator = NULL;
GameGraph* g_GameGraph = NULL;

//Two cameras, one to support landscape the other to support
//portrait. Only one is active at any given time.
ICameraSceneNode* landscapeCamera = NULL;
ICameraSceneNode* portraitCamera = NULL;

//Forward declaration of a helper method used to create the two camera types.
void CreateCamera(int width, int height, vector3df position, vector3df target);

void Load(int resolutionWidth, int resolutionHeight)
{
  //The game is being freshly initialized, create a default graph.
  if (NULL == g_GameGraph)
  {
    srand(time(NULL));

    g_GameGraph = new GameGraph(g_Device, g_Driver, g_OhrResourceManager);
    g_GameGraph->SetResolutionWidth(resolutionWidth);
    g_GameGraph->SetResolutionHeight(resolutionHeight);

    //TODO: This is for testing, should actually display a title screen and prompt user
    //for action loading world either from a save file or creating anew.
    WorldState* worldState = new WorldState();
    RunningState* runningState = new RunningState();
    g_GameGraph->SetWorldState(worldState);
    g_GameGraph->AddGameState("running", runningState);
    g_GameGraph->SetCurrentState(runningState);
    worldState->OnEnter(g_GameGraph);
    runningState->OnEnter(g_GameGraph);
  }
  else
  {
    //The game graph has already been loaded. Update its resolution settings and
    //tell it to reload with the new device and driver.
    g_GameGraph->SetResolutionWidth(resolutionWidth);
    g_GameGraph->SetResolutionHeight(resolutionHeight);
    g_GameGraph->Reload(g_Device, g_Driver);
  }

  //Initialze SceneManager position
  g_GameGraph->GetSceneManager()->getRootSceneNode()->setPosition(
      vector3df(0.0f, 0.0f, 0.0f));

  vector3df position(0.000000f, 0.000000f, -4.000000f);
  vector3df target(0.000000f, 0.000000f, -1.000000f);

  //Create portrait and landscape camera
  CreateCamera(resolutionWidth, resolutionHeight, position, target);

  //Select the appropriate one for use
  if (resolutionWidth > resolutionHeight)
  {
    g_GameGraph->GetSceneManager()->setActiveCamera(landscapeCamera);
  }
  else
  {
    g_GameGraph->GetSceneManager()->setActiveCamera(portraitCamera);
  }
}

void Update()
{
  g_GameGraph->OnUpdate();
}

void Render()
{
  g_Driver->beginScene(true, true, video::SColor(0, 100, 100, 100));

  g_GameGraph->GetSceneManager()->drawAll();
  g_GameGraph->GetUserInterface()->drawAll();

  g_Driver->endScene();
}

void CreateCamera(int width, int height, vector3df position, vector3df target)
{
  //Build camera
  ISceneManager* sm = g_GameGraph->GetSceneManager();
  WorldState* worldState =
      static_cast<WorldState*> (g_GameGraph->GetWorldState());
  HexMap* hm = worldState->GetCurrentMap();

  if (NULL != sm)
  {
    if (NULL != hm)
    {
      ICameraSceneNode* orthoCam = sm->addCameraSceneNode(
          sm->getRootSceneNode(), position, target);

      matrix4 projMat;
      projMat.buildProjectionMatrixOrthoLH(width, height, -5, 5);
      orthoCam->setProjectionMatrix(projMat, true);
      orthoCam->bindTargetAndRotation(true);
      if (orthoCam->isOrthogonal())
      {
        CameraAnimator* cameraAnim = new CameraAnimator(position, width,
            height, hm->GetMapDimensions().Height,
            hm->GetMapDimensions().Width, worldState->GetHero(),
            hm->GetCoordinateTranslator());
        orthoCam->addAnimator(cameraAnim);
        cameraAnim->drop();
        cameraAnim = NULL;

        if (width > height)
        {
          LOGI("Creating a landscape camera.");
          landscapeCamera = orthoCam;
        }
        else
        {
          LOGI("Creating a portrait camera");
          portraitCamera = orthoCam;
        }
      }
      else
      {
        LOGE("The created camera is not orthoganol, something is wrong with the perspective matrix.");
      }
    }
    else
    {
      LOGE("The hex map created in the WorldState is NULL.");
    }
  }
  else
  {
    LOGE("The scene manager cannot be loaded from the device.");
  }
}
