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

int main(){

    std::string path = "/";
    struct dirent *directory;
    DIR *pdirectory;
    struct stat fileinfo;

    pdirectory = opendir(path.c_str());
    if (pdirectory == NULL)
    {
            printf("Error: Unable to open directory\n");
            exit(0);
    }
    printf("%s\n",path.c_str());
    while ((directory = readdir(pdirectory)) != NULL)
    {
        std::string spath = path + '/' + directory->d_name;
        if (!stat(spath.c_str(), &fileinfo))
        {
            if (S_ISREG(fileinfo.st_mode))
            {
              printf("File Name:             %s\n",directory->d_name);
              printf("File Size:             %d bytes\n",fileinfo.st_size);
              printf("Type = %d\n", fileinfo.st_mode);
            }
            else if(S_ISDIR(fileinfo.st_mode)){
              printf("Dir Name:              %s\n",directory->d_name);
              printf("Dir Size:              %d bytes\n",fileinfo.st_size);
            }
        }
    }
        closedir(pdirectory);
   }
