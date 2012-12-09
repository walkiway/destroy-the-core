/*
 * AndroidReadFile.h
 *
 *  Created on: Nov 1, 2010
 *      Author: Ryan Maloney
 */
#ifndef __ANDROID_READ_FILE_H_INCLUDED__
#define __ANDROID_READ_FILE_H_INCLUDED__

#include <irrlicht.h>
#include <stdio.h>
#include <irrString.h>

class AndroidReadFile: public irr::io::IReadFile, public irr::io::IFileReadCallBack
{
public:

  AndroidReadFile(const char* fileName, FILE* file, long offset,
      long fileLength);

  ~AndroidReadFile();

  //! Reads an amount of bytes from the file.
  /** \param buffer Pointer to buffer where read bytes are written to.
   \param sizeToRead Amount of bytes to read from the file.
   \return How many bytes were read. */
  irr::s32 read(void* buffer, irr::u32 sizeToRead);

  //! Reads an amount of bytes from the file.
  /** \param buffer: Pointer to buffer where to read bytes will be written to.
  \param sizeToRead: Amount of bytes to read from the file.
  \return Returns how much bytes were read. */
  int read(void* buffer, int sizeToRead);

  //! Changes position in file
  /** \param finalPos Destination position in the file.
   \param relativeMovement If set to true, the position in the file is
   changed relative to current position. Otherwise the position is changed
   from beginning of file.
   \return True if successful, otherwise false. */
  bool seek(long finalPos, bool relativeMovement = false);

  //! Get size of file.
  /** \return Size of the file in bytes. */
  long getSize() const;

  //! Get the current position in the file.
  /** \return Current position in the file in bytes. */
  long getPos() const;

  //! Get name of file.
  /** \return File name as zero terminated character string. */
  const irr::io::path& getFileName() const;

  FILE* GetUnderlyingFile();

  long GetUnderlyingFileSize();

  long GetUnderlyingFileOffset();

  long GetUnderlyingFileLength();

private:
  void OpenFile();
  FILE* file;
  long fileSize;
  long offset;
  long length;
  irr::core::stringc fileName;
};
#endif
