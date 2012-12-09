LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog -lGLESv1_CM

LOCAL_MODULE    := destroythecore

OHR_JNI_LAYER = DestroyTheCore.cpp DestroyTheCoreRenderer.cpp InputSource.cpp CombatEngine.cpp
OHR_UTIL = util/AndroidReadFile.cpp util/ResourceBundle.cpp util/ResourceManager.cpp util/CoordinateTranslator.cpp
OHR_WORLD = world/HexMap.cpp world/HexTile.cpp 
OHR_WORLD_BUILDERS = world/builders/MapBuilder.cpp world/builders/PreFabbedRoom.cpp world/builders/HexTileDefinition.cpp world/builders/HexTileSet.cpp
OHR_WORLD_IO = world/io/MapFileManager.cpp world/io/PreFabbedFileManager.cpp world/io/TileDefinitionFileManager.cpp
OHR_GAME = Game.cpp
OHR_LAYERS = view/MonsterAnimator.cpp view/PlayerCharacterAnimator.cpp view/GameLayer.cpp view/HexMapSceneNode.cpp view/CameraAnimator.cpp
OHR_INPUT = input/EventReceiver.cpp
OHR_ENTITIES = entities/Monster.cpp entities/PlayerCharacter.cpp entities/Creature.cpp entities/builders/CreatureSet.cpp entities/builders/CreatureDefinition.cpp entities/io/CreatureDefinitionFileManager.cpp
OHR_STATE = states/GameGraph.cpp states/WorldState.cpp states/RunningState.cpp
OHR_UI = ui/StatBox.cpp ui/HeadsUpDisplay.cpp ui/MessageWindow.cpp

LOCAL_SRC_FILES := \
     $(OHR_JNI_LAYER) \
     $(OHR_UTIL) \
     $(OHR_WORLD) \
     $(OHR_WORLD_BUILDERS) \
     $(OHR_WORLD_IO) \
     $(OHR_STATE) \
     $(OHR_LAYERS) \
     $(OHR_ENTITIES) \
     $(OHR_UI) \
     $(OHR_GAME) 
     
LOCAL_AAPT_FLAGS := -0 .anim -0 .dat

LOCAL_C_INCLUDES += $(NDK_ROOT)/sources/irrlichtandroid/project/include

LOCAL_STATIC_LIBRARIES := irrlicht

include $(BUILD_SHARED_LIBRARY)

include $(NDK_ROOT)/sources/irrlichtandroid/project/jni/Android.mk






