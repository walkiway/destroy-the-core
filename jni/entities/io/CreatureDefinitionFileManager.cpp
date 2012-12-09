/*
 * CreatureDefinitionFileManager.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: Ryan Maloney
 */

#define LOG_TAG "CreatureDefinitionFileManager"

#include "CreatureDefinitionFileManager.h"
#include <irrXML.h>
#include "util/ResourceBundle.h"
#include "util/AndroidReadFile.h"
#include "util/LoggingMacros.h"

CreatureDefinitionFileManager::CreatureDefinitionFileManager()
{
  // TODO Auto-generated constructor stub

}

CreatureDefinitionFileManager::~CreatureDefinitionFileManager()
{
  // TODO Auto-generated destructor stub
}

CreatureSet* CreatureDefinitionFileManager::PopulateCreatureSet(
    ResourceManager* resourceManager, irr::core::stringc resourceName)
{
  LOGI("At the top of the populate tile definition set method");

  CreatureSet* creatureSet = NULL;

  ResourceBundle* resourceBundle = resourceManager->GetResourceBundle(
      "Creatures");

  if (NULL != resourceBundle)
  {
    AndroidReadFile* androidReadFile = resourceBundle->Find(resourceName);

    if (NULL != androidReadFile)
    {
      irr::io::IrrXMLReader* reader = irr::io::createIrrXMLReader(
          androidReadFile, false);

      if (NULL != reader)
      {
        bool readingWorldName = false;
        bool readingResource = false;
        bool readingWidth = false;
        bool readingHeight = false;

        irr::core::stringc worldName("");
        irr::core::stringc resourceName("");
        int spriteWidth = 0;
        int spriteHeight = 0;

        while (reader->read())
        {
          switch (reader->getNodeType())
          {
          case irr::io::EXN_TEXT:
            if (readingWorldName)
            {
              worldName.append(reader->getNodeData());
            }
            else if (readingResource)
            {
              resourceName.append(reader->getNodeData());
            }
            else if (readingWidth)
            {
              sscanf(reader->getNodeData(), "%d", &spriteWidth);
            }
            else if (readingHeight)
            {
              sscanf(reader->getNodeData(), "%d", &spriteHeight);
            }
            break;
          case irr::io::EXN_ELEMENT:
            if (0 == strcmp("world-name", reader->getNodeName()))
            {
              readingWorldName = true;
            }
            else if (0 == strcmp("resource-file", reader->getNodeName()))
            {
              readingResource = true;
            }
            else if (0 == strcmp("width", reader->getNodeName()))
            {
              readingWidth = true;
            }
            else if (0 == strcmp("height", reader->getNodeName()))
            {
              readingHeight = true;
            }
            else if (0 == strcmp("creature", reader->getNodeName()))
            {
              LOGD("Creating creature definition");
              if (NULL == creatureSet)
              {
                creatureSet = new CreatureSet(worldName, resourceName);
                creatureSet->SetSpriteWidth(spriteWidth);
                creatureSet->SetSpriteHeight(spriteHeight);
              }

              irr::core::stringc name(reader->getAttributeValue("name"));
              bool aiControlled = false;
              if (0 == strcmp("true", reader->getAttributeValue("ai")))
              {
                aiControlled = true;
              }

              LOGD("Creature name is %s, it is ai controlled: %d",
                  name.c_str(), aiControlled);

              int index = 0;
              int indexLength = 0;
              irr::core::stringc
                  indexString(reader->getAttributeValue("index"));
              irr::core::stringc indexLengthString(
                  reader->getAttributeValue("indexLength"));

              LOGD("String values are %s and %s", indexString.c_str(),
                  indexLengthString.c_str());

              sscanf(indexString.c_str(), "%d", &index);
              sscanf(indexLengthString.c_str(), "%d", &indexLength);

              LOGD("Index values are %d and length %d", index, indexLength);

              int lifeMeter = 0;
              irr::core::stringc lifeMeterString(
                  reader->getAttributeValue("lifeMeter"));
              LOGD("String value for life meter is: %s", lifeMeterString.c_str());
              sscanf(lifeMeterString.c_str(), "%d", &lifeMeter);

              int maxLifeMeter = 0;
              irr::core::stringc maxLifeMeterString(
                  reader->getAttributeValue("maxLifeMeter"));
              LOGD("String value for max life meter is: %s", maxLifeMeterString.c_str());
              sscanf(maxLifeMeterString.c_str(), "%d", &maxLifeMeter);

              CreatureDefinition* creatureDefinition = new CreatureDefinition();
              creatureDefinition->SetName(name);
              creatureDefinition->SetAtlasIndex(index);
              creatureDefinition->SetIndexLength(indexLength);
              creatureDefinition->SetWidth(spriteWidth);
              creatureDefinition->SetHeight(spriteHeight);
              creatureDefinition->SetWorldName(worldName);
              creatureDefinition->SetLifeMeter(lifeMeter);
              creatureDefinition->SetMaxLifeMeter(maxLifeMeter);

              creatureSet->Add(creatureDefinition);
            }
            break;
          case irr::io::EXN_ELEMENT_END:
            if (0 == strcmp("world-name", reader->getNodeName()))
            {
              readingWorldName = false;
            }
            else if (0 == strcmp("resource-file", reader->getNodeName()))
            {
              readingResource = false;
            }
            else if (0 == strcmp("width", reader->getNodeName()))
            {
              readingWidth = false;
            }
            else if (0 == strcmp("height", reader->getNodeName()))
            {
              readingHeight = false;
            }
            break;
          }
        }

        delete reader;
      }
      else
      {
        LOGE("Unable to create an xml reader from resource %s",
            resourceName.c_str());
      }
    }
    else
    {
      LOGE("Unable to get read file wrapper file for %s", resourceName.c_str());
    }
  }
  else
  {
    LOGE("Unable to find resource %s", resourceName.c_str());
  }

  return creatureSet;
}
