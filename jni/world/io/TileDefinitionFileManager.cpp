/*
 * TileDefinitionFileManager.cpp
 *
 *  Created on: Dec 12, 2010
 *      Author: Ryan Maloney
 */
#define LOG_TAG "TileDefinitionFileManager"

#include "TileDefinitionFileManager.h"
#include <irrXML.h>
#include "util/ResourceBundle.h"
#include "util/AndroidReadFile.h"
#include "util/LoggingMacros.h"
#include "world/builders/HexTileDefinition.h"

TileDefinitionFileManager::TileDefinitionFileManager()
{
}

TileDefinitionFileManager::~TileDefinitionFileManager()
{
}

HexTileSet* TileDefinitionFileManager::PopulateHexTileDefinitionSet(
    ResourceManager* resourceManager, irr::core::stringc resourceName)
{
  LOGI("At the top of the populate tile definition set method");

  HexTileSet* tileSet = NULL;

  ResourceBundle* resourceBundle = resourceManager->GetResourceBundle("Tiles");

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
        bool readingTileResource = false;
        bool hexTileSet = false;
        bool readingTileWidth = false;
        bool readingTileHeight = false;

        irr::core::stringc worldName("");
        float tileWidth = 0.0f;
        float tileHeight = 0.0f;

        while (reader->read())
        {
          switch (reader->getNodeType())
          {
          case irr::io::EXN_TEXT:
            if (readingWorldName)
            {
              worldName.append(reader->getNodeData());
            }
            else if (readingTileResource)
            {
              tileSet = new HexTileSet(worldName,
                  irr::core::stringc(reader->getNodeData()));
            }
            else if (readingTileWidth)
            {
              sscanf(reader->getNodeData(), "%f", &tileWidth);
            }
            else if (readingTileHeight)
            {
              sscanf(reader->getNodeData(), "%f", &tileHeight);
            }
            break;
          case irr::io::EXN_ELEMENT:
            if (0 == strcmp("tileset", reader->getNodeName()))
            {
              if (0 == strcmp("true", reader->getAttributeValue("hex")))
              {
                hexTileSet = true;
              }
            }
            else if (0 == strcmp("world-name", reader->getNodeName()))
            {
              readingWorldName = true;
            }
            else if (0 == strcmp("resource-file", reader->getNodeName()))
            {
              readingTileResource = true;
            }
            else if (0 == strcmp("width", reader->getNodeName()))
            {
              readingTileWidth = true;
            }
            else if (0 == strcmp("height", reader->getNodeName()))
            {
              readingTileHeight = true;
            }
            else if (0 == strcmp("tile", reader->getNodeName()))
            {
              LOGD("Creating tile definition");

              irr::core::stringc name(reader->getAttributeValue("name"));
              irr::core::stringc symbol(reader->getAttributeValue("symbol"));
              LOGD("Tile name is %s symbol is %c", name.c_str(), symbol[0]);

              int index = 0;
              int indexLength = 0;
              irr::core::stringc
                  indexString(reader->getAttributeValue("index"));
              irr::core::stringc indexLengthString(
                  reader->getAttributeValue("indexLength"));

              LOGD("String values are %s and %s", indexString.c_str(), indexLengthString.c_str());

              sscanf(indexString.c_str(), "%d", &index);
              sscanf(indexLengthString.c_str(), "%d", &indexLength);

              LOGD("Index values are %d and length %d", index, indexLength);

              HexTileDefinition* tileDefinition = new HexTileDefinition(name,
                  symbol[0]);

              tileDefinition->SetAtlasIndex(index);
              tileDefinition->SetTileIndexLength(indexLength);
              tileDefinition->SetWidth(tileWidth);
              tileDefinition->SetHeight(tileHeight);
              tileDefinition->CalculateIntermediateValues();
              tileSet->SetTileHeight(tileDefinition->GetHeight());
              tileSet->SetTileWidth(tileDefinition->GetWidth());

              if (0 == strcmp("true", reader->getAttributeValue("traversable")))
              {
                tileDefinition->SetTraversable(true);
              }
              else
              {
                tileDefinition->SetTraversable(false);
              }

              tileSet->Add(tileDefinition);
            }
            break;
          case irr::io::EXN_ELEMENT_END:
            if (0 == strcmp("world-name", reader->getNodeName()))
            {
              readingWorldName = false;
            }
            else if (0 == strcmp("resource-file", reader->getNodeName()))
            {
              readingTileResource = false;
            }
            else if (0 == strcmp("width", reader->getNodeName()))
            {
              readingTileWidth = false;
            }
            else if (0 == strcmp("height", reader->getNodeName()))
            {
              readingTileHeight = false;
            }
            break;
          }
        }

        delete reader;
      }
      else
      {
        LOGE("Unable to create an xml reader from resource %s", resourceName.c_str());
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

  return tileSet;
}
