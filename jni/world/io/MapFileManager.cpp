/*
 * MapFileManager.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: Ryan Maloney
 */
#define  LOG_TAG    "MapFileManager"

#include "MapFileManager.h"
#include "util/LoggingMacros.h"
#include "world/HexTile.h"

using namespace irr;
using namespace core;
using namespace video;

MapFileManager::MapFileManager(IVideoDriver* videoDriver,
    ResourceManager* resourceManager) :
  _driver(videoDriver), _resourceManager(resourceManager)
{

}

MapFileManager::~MapFileManager()
{
  // TODO Auto-generated destructor stub
}

HexMap* MapFileManager::Populate(stringc filename, stringc world)
{
  return Populate(filename, world, true);
}

HexMap* MapFileManager::Populate(stringc filename, stringc world,
    bool readDimensionFromFile)
{
  HexMap* createdMap;

  ResourceBundle* resourceBundle = _resourceManager->GetResourceBundle("Maps");
  AndroidReadFile* androidReadFile = resourceBundle->Find(filename);

  if (NULL != androidReadFile)
  {
    LOGD("Found file %s, attempting to load Map object from it...", filename.c_str());
    FILE* file = androidReadFile->GetUnderlyingFile();

    if (NULL != file)
    {
      //Map values
      dimension2d<int> dimensions;
      stringc textureFilename = "";

      //Loop values
      long bytesToRead = androidReadFile->getSize();
      char* line = NULL;
      int presentLine = 1;

      //Parsing values
      bool dimensionsLoaded = false;
      bool processingTileDictionary = false;
      bool processingMapLayout = false;
      int numberOfTileDictionaryEntries = 0;
      map<char, HexTileDefinition*> tileKeyMap;
      int mapLineCount = 0;

      LOGD("Building map from file with %i bytes", bytesToRead);

      while (bytesToRead > 1)
      {
        LOGD("Bytes left to read: %i", bytesToRead);
        line = new char[bytesToRead];
        fgets(line, bytesToRead, file);
        bytesToRead -= strlen(line);

        LOGV(line);

        //Ignore blank lines
        if (NULL == line || strcmp("", line) == 0 || strcmp("\n", line) == 0)
        {
          LOGV("Skipping a line that is null, empty or consists only of an endline");
          continue;
        }
        //First line is dimensions although this value is not mandatory.
        if (readDimensionFromFile && !dimensionsLoaded)
        {
          ParseDimensionFromLine(line, dimensions);
          createdMap = new HexMap(dimensions, world);
          dimensionsLoaded = true;
        }
        //Second thing that should appear is the texture filename.
        else if (0 == strcmp("", textureFilename.c_str()))
        {
          textureFilename.append(line);
          textureFilename.trim();
        }
        //Next up is a line containing a count of all the tile dictionary entries.
        else if (!processingTileDictionary)
        {
          sscanf(line, "%d", &numberOfTileDictionaryEntries);
          processingTileDictionary = true;
        }
        //Build the tile legend from the file.
        else if (!processingMapLayout && processingTileDictionary)
        {
          //Key off the first symbol of the row down in the next block
          LOGD("Parsing tile legend line %d...", numberOfTileDictionaryEntries);
          char key;
          HexTileDefinition* tileToAdd = ParseTileFromLine(line, key);
          tileKeyMap.insert(key, tileToAdd);
          if (0 == --numberOfTileDictionaryEntries)
          {
            LOGV("All tiles have been processed, setting flag to handle map layout processing.");
            processingMapLayout = true;
          }
        }
        //Reading map layout
        else if (processingMapLayout)
        {
          char* mapSymbol = line;
          LOGV("Processing map line %s", line);
          int xPosition = 0;
          while (*mapSymbol != '\n' && *mapSymbol != '\0')
          {
            LOGV("Processing map symbol %c into the table.", *mapSymbol);
            vector2d<int> point(xPosition, mapLineCount);
            HexTileDefinition* tileDefinition =
                tileKeyMap.find(*mapSymbol)->getValue();

            if (NULL != tileDefinition)
            {
              HexTile* tile = new HexTile(tileDefinition->GetName(), world,
                  tileDefinition->GetMapLegendSymbol(), point);
              tile->SetAtlasIndex(tileDefinition->GetAtlasIndex());
              tile->SetTileIndexLength(tileDefinition->GetTileIndexLength());
              tile->SetTraversable(tileDefinition->IsTraversable());
              createdMap->AddTileAt(tile, point);
            }
            else
            {
              LOGE("Tile could not be found for id %c in the dictionary.", *mapSymbol);
            }

            xPosition++;
            mapSymbol++;
          }
          mapLineCount++;
        }

        delete (line);
        line = NULL;
        presentLine++;
      }

      //BEGIN: Clean up tile key map
      map<char, HexTileDefinition*>::Iterator tileKeyDefIterator =
          tileKeyMap.getIterator();

      while (!tileKeyDefIterator.atEnd())
      {
        map<char, HexTileDefinition*>::Node* node = tileKeyDefIterator.getNode();
        if (NULL != node && NULL != node->getValue())
        {
          delete (node->getValue());
        }
        else
        {
          LOGE("An entry in the temporary map is null or the image contained therein is null.  This is a potential resource leak!");
        }
        tileKeyDefIterator++;
      }

      tileKeyMap.clear();
      //END: Cleanup

      createdMap->SetTextureFilename(textureFilename);

      if (!PopulateTileImages(createdMap))
      {
        LOGE("An error occurred while attempting to create tile images from the tilesheet. This is unrecoverable.");
        createdMap = NULL;
      }
    }
    else
    {
      LOGE("Underlying file for resource %s is null.", filename.c_str());
    }
  }
  else
  {
    LOGE("Unable to find the map file name %s", filename.c_str());
  }

  return createdMap;
}

bool MapFileManager::PopulateTileImages(HexMap* newlyCreatedMap)
{
  bool result = false;

  //STEP 1: Build an atlas index of all the images needed for textures from the backing file.
  LOGI("Initializing tile images from file %s", newlyCreatedMap->GetTextureFilename().c_str());

  ResourceBundle* mapResourceBundle = _resourceManager->GetResourceBundle(
      "Maps");

  //WARNING: Early returns here!  I don't normally like this but the alternative is
  //huge if/else blocks.
  if (NULL == mapResourceBundle)
  {
    LOGE("Could not find the Maps resource bundle in the resource manager.");
    return false;
  }

  if (NULL == _driver)
  {
    LOGE("The video driver is null.  Since this is needed for creating images this is unrecoverable.");
    return false;
  }
  //END WARNING

  IImage* image = _driver->createImageFromFile(mapResourceBundle->Find(
      newlyCreatedMap->GetTextureFilename()));

  int totalTileCountScope;

  if (NULL == image)
  {
    LOGE("Unable to load image associated with map png file.");
  }
  else
  {
    LOGD("Image size is %d x %d", image->getDimension().Width, image->getDimension().Height);

    //Tiles are identified by an atlas index which tells the system which image in a tilesheet
    //numbered starting from 0 in the upper left corner and proceeding width first belongs
    //to a tile.
    map<int, IImage*> tileAtlasImageIndexMap;

    int tilesPerRow = image->getDimension().Width / 40;
    int tilesPerColumn = image->getDimension().Height / 40;

    const int totalTileCount = tilesPerRow * tilesPerColumn;
    totalTileCountScope = totalTileCount;

    int atlasIndex = 0;
    position2d<s32> position(0, 0);
    //TODO: It might be worth pulling the tile dimensions into a configuration file or #Define at the very least.
    dimension2d<u32> dimensions(40, 40);

    //Indices for the tilesheets increase breatdth first then depth.
    for (int y = 0; y < tilesPerColumn; y++)
    {
      for (int x = 0; x < tilesPerRow; x++)
      {
        IImage* imageTile = _driver->createImage(image->getColorFormat(),
            dimensions);
        rect<s32> sourceRect(x * 40, y * 40, (x * 40) + 40, (y * 40) + 40);

        image->copyTo(imageTile, position, sourceRect);

        if (NULL != imageTile)
        {
          LOGD("Image of tile being associated with the atlasIndex %d is %d x %d", atlasIndex, imageTile->getDimension().Width, imageTile->getDimension().Height);
          tileAtlasImageIndexMap.set(atlasIndex, imageTile);
        }
        else
        {
          LOGE("Unable to properly cut out a tile at upper left (%d, %d)", sourceRect.UpperLeftCorner.X, sourceRect.UpperLeftCorner.Y);
        }

        atlasIndex++;
      }
    }

    LOGD("Dropping no longer needed image.");
    image->drop();
    image = NULL;

    //STEP 2: Iterate over map's tiles and fetch their image from the atlasIndexMap
    dimension2d<int> mapDimensions = newlyCreatedMap->GetMapDimensions();
    stringc worldName = newlyCreatedMap->GetWorld();
    for (int x = 0; x < mapDimensions.Width; x++)
    {
      for (int y = 0; y < mapDimensions.Height; y++)
      {
        HexTile* tile = newlyCreatedMap->GetTileAt(vector2d<s32> (x, y));

        if (NULL != tile)
        {
          stringc textureName(worldName);
          textureName.append("-");
          textureName.append(tile->GetName());

          if (NULL == _driver->getTexture(textureName))
          {
            LOGI("Texture named %s is not registered with the driver.  Registering.", textureName.c_str());

            int tileAtlasIndex = tile->GetAtlasIndex();

            //For tiles that are random in a series
            if (tile->GetTileIndexLength() > 0)
            {
              //First, choose which in the series to use.
              LOGE("Generating random atlas index starting from %d with a possibility of %d values.", tileAtlasIndex, tile->GetTileIndexLength());
              tileAtlasIndex = rand() % tile->GetTileIndexLength()
                  + tile->GetAtlasIndex();
              LOGE("Random result: %d", tileAtlasIndex);

              //Calculate how many spaces it is offset from the atlas index originally specified.
              int atlasIndexOffset = tileAtlasIndex - tile->GetAtlasIndex();

              char tileIndex[5];
              textureName.append("-");
              sprintf(tileIndex, "%d", atlasIndexOffset);
              textureName.append(tileIndex);
              textureName.trim();

              LOGI("Updating tile's Atlast Index Offset to %d", atlasIndexOffset);
              tile->SetAtlasIndexOffset(atlasIndexOffset);

              //Check again here because up to this point the tile would have had a
              //generic tile name, i.e. ground, instead of a fully qualified one.  If so,
              //skip and move to the next value.
              if (NULL != _driver->getTexture(textureName))
              {
                continue;
              }

            }

            map<int, IImage*>::Node* node = tileAtlasImageIndexMap.find(
                tileAtlasIndex);
            if (NULL != node)
            {
              IImage* textureResource = node->getValue();
              if (NULL != textureResource)
              {
                LOGD("Started registering %s.", textureName.c_str());
                _driver->addTexture(textureName, textureResource);
                LOGD("Finished registering %s.", textureName.c_str());
              }
              else
              {
                LOGE("The image created for texture named %s is null or corrupted.", textureName.c_str());
              }
            }
            else
            {
              LOGE("The map backed with texture file %s seems to have a gap at (%d, %d) where no tile exists.", newlyCreatedMap->GetTextureFilename().c_str(), x, y);
            }
          }
        }
        else
        {
          LOGI(
              "No image found for the index %d associated with tile named %s."
              "Given the set up of the file, this is probably normal.",
              tile->GetAtlasIndex(), tile->GetName().c_str());
        }
      }
    }

    LOGD("Beginning clean up of temporary resources used for tile texture resource initialization.");

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
        LOGE("An entry in the temporary map is null or the image contained therein is null.  This is a potential resource leak!");
      }
      mapIterator++;
    }
    tileAtlasImageIndexMap.clear();

    LOGD("Tile texture resource cleanup complete.");

    result = true;
  }

  return result;
}

void MapFileManager::ParseDimensionFromLine(char* line,
    dimension2d<int>& dimensions)
{
  int xDimension = 0;
  int yDimension = 0;
  char* sizeToken = strtok(line, ",");
  while (NULL != sizeToken)
  {
    if (0 == xDimension)
    {
      LOGD("Attempting to scan sizeToken for x dimension (%s)...", sizeToken);
      sscanf(sizeToken, "%d", &xDimension);
      LOGD("Success");
    }
    else
    {
      LOGD("Attempting to scan sizeToken for y dimension (%s)...", sizeToken);
      sscanf(sizeToken, "%d", &yDimension);
      LOGD("Success");
    }

    //Using NULL tells it to continue tokinizing from last point
    sizeToken = strtok(NULL, ",");
  }
  LOGD("Dimensions for map: (%d by %d)", xDimension, yDimension);
  dimensions.Width = xDimension;
  dimensions.Height = yDimension;
}

HexTileDefinition* MapFileManager::ParseTileFromLine(char* line,
    char& dictionaryKey)
{
  HexTileDefinition* newTile = NULL;

  //Temp tile values
  stringc tileName = "";
  int tileTraversable = -1;
  int tileAtlasIndex = -1;
  int tileIndexLength = -1;
  vector2d<int> position;
  position.X = 0;
  position.Y = 0;

  //looping values
  bool dictKeyParsed = false;
  bool tileNameParsed = false;

  LOGV("Tokenizing the line %s", line);

  char* sizeToken = strtok(line, ",");

  LOGV("First token is %s", sizeToken);

  while (NULL != sizeToken && "\n" != sizeToken)
  {
    //First value that appears is the key used in the map
    if (!dictKeyParsed)
    {
      LOGV("ParseTileFromLine: Setting key to %s", sizeToken);
      dictionaryKey = *sizeToken;
      dictKeyParsed = true;
    }
    //Second, the tile name
    else if (!tileNameParsed)
    {
      LOGV("ParseTileFromLine: Setting tile name to %s", sizeToken);
      tileName.append(sizeToken);
      tileNameParsed = true;
    }
    //Third, tile traversable value
    else if (-1 == tileTraversable)
    {
      sscanf(sizeToken, "%d", &tileTraversable);
    }
    //Fourth, atlas index
    else if (-1 == tileAtlasIndex)
    {
      sscanf(sizeToken, "%d", &tileAtlasIndex);
    }
    //Fifth
    else if (-1 == tileIndexLength)
    {
      sscanf(sizeToken, "%d", &tileIndexLength);
    }

    //Using NULL tells it to continue tokinizing from last point
    sizeToken = strtok(NULL, ",");

    LOGV("New token is %s", sizeToken);
  }

  newTile = new HexTileDefinition(tileName, dictionaryKey);
  newTile->SetAtlasIndex(tileAtlasIndex);
  newTile->SetTileIndexLength(tileIndexLength);

  if (tileTraversable == 1)
  {
    newTile->SetTraversable(true);
  }
  else
  {
    newTile->SetTraversable(false);
  }

  return newTile;
}
