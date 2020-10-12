#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <iterator>
#include <vector>
#include <fstream>
#include <string.h>

struct FileItemInfo
{
    std::wstring name;
    unsigned long size;
    int type;
};

#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

class DirectoryReader
{

private:
  std::wstring path;
  struct dirent *directory;
  DIR *pdirectory;
  struct stat fileinfo;

public:
  float fontColor[3];
  float background[3];

  std::wstring Read(std::vector<FileItemInfo> &items);

  // constractor
  DirectoryReader(std::wstring path);
};

#endif
