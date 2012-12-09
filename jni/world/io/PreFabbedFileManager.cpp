/*
 * PreFabbedFileManager.cpp
 *
 *  Created on: Dec 5, 2010
 *      Author: Ryan Maloney
 */
#define LOG_TAG "PreFabbedFileManager"

#include "PreFabbedFileManager.h"
#include "util/LoggingMacros.h"
#include "world/builders/PreFabbedRoom.h"

using namespace irr;
using namespace core;

PreFabbedFileManager::PreFabbedFileManager(ResourceManager* resourceManager) :
  _resourceManager(resourceManager)
{
  // TODO Auto-generated constructor stub

}

PreFabbedFileManager::~PreFabbedFileManager()
{
  // TODO Auto-generated destructor stub
}

void PreFabbedFileManager::Populate(irr::core::stringc filename,
    MapBuilder* mapBuilder)
{
  ResourceBundle* resourceBundle = _resourceManager->GetResourceBundle("Maps");
  AndroidReadFile* androidReadFile = resourceBundle->Find(filename);

  if (NULL != androidReadFile)
  {
    LOGD("Found file %s, attempting to load Map object from it...",
        filename.c_str());
    FILE* file = androidReadFile->GetUnderlyingFile();

    if (NULL != file)
    {
      //Weighted appearance values. As a room is being built there are three numbers assigned
      //one for each world.  These are used to determine the likelihood of a room appearing
      //within a given world.  The way it works is that the room is created and then
      //pointers equal to the number specified by the weight value are added to each World's
      //room list.
      int weightBanditHole = 0;
      int weightDungeon = 0;
      int weightHell = 0;

      //Loop values
      long bytesToRead = androidReadFile->getSize();
      char* line = NULL;
      int presentLine = 1;
      bool encounteredRoomBoundary = false;
      PreFabbedRoom* currentPreFabbedRoom = NULL;

      //Breadcrumb flags.  The lines appear in a specific order in the configuration
      //file and these flags help us keep track of where we are in the process.
      bool parsingWeightedValues;

      LOGD("Building map from file with %i bytes", bytesToRead);

      while (bytesToRead > 1)
      {
        //Get the new line for parsing
        LOGD("Bytes left to read: %i", bytesToRead);
        line = new char[bytesToRead];
        fgets(line, bytesToRead, file);
        bytesToRead -= strlen(line);

        LOGV(line);

        //Ignore blank lines
        if (NULL == line || strcmp("", line) == 0 || strcmp("\n", line) == 0)
        {
          LOGV("Encountered a line that is null, empty or consists only of an endline.  This marks the beginning of a new room");
          encounteredRoomBoundary = true;
          continue;
        }

        //We are looking at the first line of the new room
        if (encounteredRoomBoundary)
        {
          //If we just finished constructing a prefabbed room add it to the appropriate collection.
          //Then assign a newly created room to the pointer.
          if (NULL != currentPreFabbedRoom)
          {
            //TODO: ADD TO MAP
            currentPreFabbedRoom = new PreFabbedRoom();
            parsingWeightedValues = true;
          }
        }

        //We are in the process of building a pre-fabbed room, continue parsing.
        if (parsingWeightedValues)
        {
          PopulateWorldWeights(line, weightBanditHole, weightDungeon,
              weightHell);
        }

        //Delete parsed line
        delete (line);
        line = NULL;
        presentLine++;
      }
    }
  }
}

void PreFabbedFileManager::PopulateWorldWeights(char* line,
    int& banditWorldWeight, int& dungeonWorldWeight, int& hellWorldWeight)
{
  list<stringc> worldWeightValues;

  //First break the line up into its constiuent parts.
  char* worldWeightToken = strtok(line, ",");
  while (NULL != worldWeightToken)
  {
    worldWeightValues.push_front(stringc(worldWeightToken));

    //Using NULL tells it to continue tokinizing from last point
    worldWeightToken = strtok(NULL, ",");
  }

  if (worldWeightValues.size() > 0)
  {
    list<stringc>::Iterator worldWeightIterator = worldWeightValues.begin();
    list<stringc>::Iterator worldWeightIteratorTail = worldWeightValues.end();
    list<stringc> parts;

    for (; worldWeightIterator != worldWeightIteratorTail; worldWeightIterator++)
    {
      parts.clear();
      //Ignore empty tokens and do not include the delimiter itself in the returned strings.
      (*worldWeightIterator).split<list<stringc> > (parts, ":", 1, true, false);
      if (parts.size() == 2)
      {
        if ((*parts.begin()).equals_ignore_case("Bandit Hole"))
        {
          sscanf((*parts.end()).c_str(), "%d", banditWorldWeight);
          LOGD("Read in bandit hole world weight %d", banditWorldWeight);
        }
        else if ((*parts.begin()).equals_ignore_case("Dungeon"))
        {
          sscanf((*parts.end()).c_str(), "%d", dungeonWorldWeight);
          LOGD("Read in bandit hole world weight %d", dungeonWorldWeight);
        }
        else if ((*parts.begin()).equals_ignore_case("Hell"))
        {
          sscanf((*parts.end()).c_str(), "%d", hellWorldWeight);
          LOGD("Read in bandit hole world weight %d", hellWorldWeight);
        }
      }
      else
      {
        LOGE("Split the following world weight %s token using the ':' delimiter but split resulted in %d parts instead of 2.", (*worldWeightIterator).c_str(), parts.size());
      }
    }
  }
  else
  {
    LOGE("No world weights found while parsing a pre fabbed room.  The specific room cannot be identified.");
  }
}
