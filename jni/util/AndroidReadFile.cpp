/*
 * AndroidReadFile.h
 *
 *  Created on: Nov 1, 2010
 *      Author: Ryan Maloney
 */
#include "AndroidReadFile.h"
#include <android/log.h>

using namespace irr;
using namespace io;
using namespace core;

#define  LOG_TAG    "AndroidReadFile"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

AndroidReadFile::AndroidReadFile(const char* fileNameArg, FILE* fileParam,
    long offsetParam, long fileLengthParam) :
  fileName(fileNameArg), file(fileParam), offset(offsetParam), fileSize(
      fileLengthParam)
{
  OpenFile();
}

AndroidReadFile::~AndroidReadFile()
{
  if (file)
  {
    fclose(file);
  }
}

s32 AndroidReadFile::read(void* buffer, u32 sizeToRead)
{
  //LOGI("Reading: %d", sizeToRead);
  return (s32) fread(buffer, 1, sizeToRead, file);
}

int AndroidReadFile::read(void* buffer, int sizeToRead)
{
  return (s32) fread(buffer, 1, sizeToRead, file);
}

bool AndroidReadFile::seek(long finalPos, bool relativeMovement)
{
  //LOGI("Seeking.  Using relative movement: %s", (relativeMovement) ? "true" : "false");
  bool result = false;
  if (relativeMovement)
  {
    result = fseek(file, finalPos, SEEK_CUR);
  }
  else
  {
    //Reset file pointer to start of record
    fseek(file, offset, SEEK_SET);
    //Then seek to final position from the start of the asset file
    result = fseek(file, finalPos, SEEK_CUR);
  }

  return result;
}

long AndroidReadFile::getSize() const
{
  return fileSize;
}

long AndroidReadFile::getPos() const
{
  return ftell(file);
}

const path& AndroidReadFile::getFileName() const
{
  //LOGI("Someone is asking for filename %s", fileName.c_str());
  return fileName;
}

void AndroidReadFile::OpenFile()
{
  if (file)
  {
    fseek(file, offset, SEEK_SET);
  }
}

FILE* AndroidReadFile::GetUnderlyingFile()
{
  fseek(file, offset, SEEK_SET);
  return file;
}

long AndroidReadFile::GetUnderlyingFileOffset()
{
  return offset;
}

long AndroidReadFile::GetUnderlyingFileLength()
{
  return length;
}
