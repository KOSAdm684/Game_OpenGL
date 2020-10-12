#include "DirectoryReader.h"

#include <locale>
#include <codecvt>
#include <string>

// "костыль", чтобы наш codecvt имел публичный деструктор,
// как того требует wstring_convert
template<class Facet>
struct deletable_facet : Facet
{
    template<class ...Args>
    deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
    ~deletable_facet() {}
};

// constractor
DirectoryReader::DirectoryReader(std::wstring path)
{
  this->path = path;
}

std::wstring DirectoryReader::Read(std::vector<FileItemInfo> &items){

  // convertong from wstrong to string
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;
  std::string pathString = converter.to_bytes(path);

  pdirectory = opendir(pathString.c_str());
  if (pdirectory == NULL)
  {
      printf("Error: Unable to open directory\n");
      exit(0);
  }

  while ((directory = readdir(pdirectory)) != NULL)
  {
      FileItemInfo info;

      std::string spath;
      std::string dName(directory->d_name);
      // exclude . and ..
      if(!dName.compare(".") || !dName.compare("..")){
        continue;
      }

      // form full path
      if(pathString.compare("/") != 0)
        spath = pathString + "/" + dName;
      else
        spath = pathString + dName;

      //
      if (!stat(spath.c_str(), &fileinfo))
      {
        info.name = converter.from_bytes(dName);
        info.size = fileinfo.st_size;
        if (S_ISREG(fileinfo.st_mode))
        {
          info.type = 0;
          items.push_back(info);

        }
        else if(S_ISDIR(fileinfo.st_mode)){
          info.type = 1;
          items.push_back(info);
        }
      }
  }
      closedir(pdirectory);
  return path;
}
