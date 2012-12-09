/*
 * HexTileSet.cpp
 *
 *  Created on: Dec 16, 2010
 *      Author: Ryan Maloney
 */
#define LOG_TAG "HexTileSet"

#include "HexTileSet.h"
#include "util/LoggingMacros.h"
#include <math.h>

using namespace irr;
using namespace core;
using namespace video;

HexTileSet::HexTileSet(stringc worldName, stringc resourceName) :
      _worldName(worldName), _resourceName(resourceName)
{
}

HexTileSet::~HexTileSet()
{
  map<stringc, HexTileDefinition*>::Iterator iterator =
      _tileDefinitionsName.getIterator();
  while (!iterator.atEnd())
  {
    map<stringc, HexTileDefinition*>::Node* node = iterator.getNode();
    delete node->getValue();
  }

  _tileDefinitionsName.clear();
  _tileDefinitionsLegend.clear();
}

int HexTileSet::GetNumberOfTiles()
{
  return _tileDefinitionsName.size();
}

void HexTileSet::Add(HexTileDefinition* tileDefinition)
{
  tileDefinition->SetWorldName(_worldName);
  _tileDefinitionsName.insert(tileDefinition->GetName(), tileDefinition);
  _tileDefinitionsLegend.insert(tileDefinition->GetMapLegendSymbol(),
      tileDefinition);
}

HexTileDefinition* HexTileSet::GetByLegendSymbol(char legendSymbol)
{
  HexTileDefinition* tileDef = NULL;
  map<char, HexTileDefinition*>::Node* node = _tileDefinitionsLegend.find(
      legendSymbol);
  if (NULL != node)
  {
    tileDef = node->getValue();
  }

  return tileDef;
}

HexTileDefinition* HexTileSet::GetByName(irr::core::stringc tileName)
{
  HexTileDefinition* tileDef = NULL;
  map<stringc, HexTileDefinition*>::Node* node = _tileDefinitionsName.find(
      tileName);

  if (NULL != node)
  {
    tileDef = node->getValue();
  }

  return tileDef;
}

bool HexTileSet::RegisterTileTextures(IVideoDriver* videoDriver,
    ResourceManager* resourceManager)
{
  bool result = false;

  //STEP 1: Build an atlas index of all the images needed for textures from the backing file.
  LOGI("Initializing tile images from file %s", _resourceName.c_str());

  ResourceBundle* mapResourceBundle = resourceManager->GetResourceBundle(
      "Tiles");

  //WARNING: Early returns here!  I don't normally like this but the alternative is
  //huge if/else blocks.
  if (NULL == mapResourceBundle)
  {
    LOGE("Could not find the Tiles resource bundle in the resource manager.");
    return false;
  }

  if (NULL == videoDriver)
  {
    LOGE(
        "The video driver is null.  Since this is needed for creating images this is unrecoverable.");
    return false;
  }
  //END WARNING

  IImage* image = videoDriver->createImageFromFile(mapResourceBundle->Find(
      _resourceName));

  int totalTileCountScope;

  if (NULL == image)
  {
    LOGE("Unable to load image associated with map png file.");
  }
  else
  {
    LOGD("Image size is %d x %d", image->getDimension().Width,
        image->getDimension().Height);

    //Tiles are identified by an atlas index which tells the system which image in a tilesheet
    //numbered starting from 0 in the upper left corner and proceeding width first belongs
    //to a tile.
    map<int, IImage*> tileAtlasImageIndexMap;

    int rTileWidth = ceil(_tileWidth);
    int rTileHeight = ceil(_tileHeight);
    int tilesPerRow = image->getDimension().Width / rTileWidth;
    int tilesPerColumn = image->getDimension().Height / rTileHeight;

    const int totalTileCount = tilesPerRow * tilesPerColumn;
    totalTileCountScope = totalTileCount;

    int atlasIndex = 0;
    position2d<s32> position(0, 0);
    //TODO: Round up to nearest power of 2
    dimension2d<u32> dimensions(64, 64);

    //Indices for the tilesheets increase breatdth first then depth.
    for (int y = 0; y < tilesPerColumn; y++)
    {
      for (int x = 0; x < tilesPerRow; x++)
      {
        IImage* imageTile = videoDriver->createImage(image->getColorFormat(),
            dimensions);
        imageTile->fill(image->getPixel(0,0));
        rect<s32> sourceRect(x * rTileWidth, y * rTileHeight, (x * rTileWidth)
            + rTileWidth, (y * rTileHeight) + rTileHeight);

        image->copyTo(imageTile, position, sourceRect);

        if (NULL != imageTile)
        {
          LOGD(
              "Image of tile being associated with the atlasIndex %d is %d x %d",
              atlasIndex, imageTile->getDimension().Width,
              imageTile->getDimension().Height);
          tileAtlasImageIndexMap.set(atlasIndex, imageTile);
        }
        else
        {
          LOGE("Unable to properly cut out a tile at upper left (%d, %d)",
              sourceRect.UpperLeftCorner.X, sourceRect.UpperLeftCorner.Y);
        }

        atlasIndex++;
      }
    }

    LOGD("Dropping no longer needed image.");
    image->drop();
    image = NULL;

    //STEP 2: Iterate over tiles in this set and fetch their image from the atlasIndexMap
    map<stringc, HexTileDefinition*>::Iterator tileMapIterator =
        _tileDefinitionsName.getIterator();

    while (!tileMapIterator.atEnd())
    {
      map<stringc, HexTileDefinition*>::Node* node = tileMapIterator.getNode();
      HexTileDefinition* tileDefinition = node->getValue();

      stringc textureName(_worldName);
      textureName.append("-");
      textureName.append(tileDefinition->GetName());

      if (NULL == videoDriver->getTexture(textureName))
      {
        LOGI(
            "Texture named %s is not registered with the driver.  Registering.",
            textureName.c_str());

        //Tiles can have a length greater than 0 which means
        //including the starting index x grab the next LENGTH tiles
        for (int i = 0; i < tileDefinition->GetTileIndexLength(); i++)
        {
          int tileAtlasIndex = tileDefinition->GetAtlasIndex() + i;

          if (tileDefinition->GetTileIndexLength() > 1)
          {
            char tileIndex[5];
            sprintf(tileIndex, "%d", tileAtlasIndex);
            stringc incrTextureName(_worldName);
            incrTextureName.append("-");
            incrTextureName.append(tileDefinition->GetName());
            incrTextureName.append("-");
            incrTextureName.append(tileIndex);
            incrTextureName.trim();

            textureName = incrTextureName;
          }

          map<int, IImage*>::Node* node = tileAtlasImageIndexMap.find(
              tileAtlasIndex);
          if (NULL != node)
          {
            IImage* textureResource = node->getValue();
            if (NULL != textureResource)
            {
              LOGI("Started registering %s.", textureName.c_str());
              videoDriver->addTexture(textureName, textureResource);
              LOGI("Finished registering %s.", textureName.c_str());
            }
            else
            {
              LOGE(
                  "The image created for texture named %s is null or corrupted.",
                  textureName.c_str());
            }
          }
        }
      }
      tileMapIterator++;
    }

    //STEP 3: Clean up
    //For all entries remaining in the map, delete the image as they were unused.
    map<int, IImage*>::Iterator mapIterator =
        tileAtlasImageIndexMap.getIterator();

    while (!mapIterator.atEnd())
    {
      map<int, IImage*>::Node* node = mapIterator.getNode();
      if (NULL != node && NULL != node->getValue())
      {
        node->getValue()->drop();
      }
      else
      {
        LOGE(
            "An entry in the temporary map is null or the image contained therein is null.  This is a potential resource leak!");
      }
      mapIterator++;
    }
    tileAtlasImageIndexMap.clear();

    LOGD("Tile texture resource cleanup complete.");

    result = true;
  }

  return result;
}

stringc HexTileSet::GetResourceName()
{
  return _resourceName;
}

stringc HexTileSet::GetWorldName()
{
  return _worldName;
}

void HexTileSet::SetTileWidth(float tileWidth)
{
  _tileWidth = tileWidth;
}

float HexTileSet::GetTileWidth()
{
  return _tileWidth;
}

void HexTileSet::SetTileHeight(float tileHeight)
{
  _tileHeight = tileHeight;
}

float HexTileSet::GetTileHeight()
{
  return _tileHeight;
}
