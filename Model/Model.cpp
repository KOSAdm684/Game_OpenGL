#include "Model.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

TankModel Model::readTankModel(const char* path)
{
    TankModel tm;
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        std::cout << "File not opened" << std::endl;
    }
    int i = 0;

    if (fscanf(f, "%d %d %d\n", &tm.cvBody, &tm.cvTower, &tm.countParams) == EOF)
    {
        std::cout << "Error of reading" << std::endl;
    }
    if (fscanf(f, "%f %f\n", &tm.offsetBodyX, &tm.offsetBodyY) == EOF)
    {
        std::cout << "Error of reading" << std::endl;
    }

    tm.vertices = new float[(tm.cvBody + tm.cvTower) * tm.countParams];

    while(!feof(f))
    {
        fscanf(f, "%f", &tm.vertices[i]);
        i+=1;
    }
    fclose(f);
    return tm;
}

GunShellModel Model::readGunShellModel(const char* path)
{
    GunShellModel gsm;
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        std::cout << "File not opened" << std::endl;
    }
    int i = 0;

    if (fscanf(f, "%d %d\n", &gsm.cv, &gsm.countParams) == EOF)
    {
        std::cout << "Error of reading" << std::endl;
    }

    gsm.vertices = new float[gsm.cv * gsm.countParams];

    while(!feof(f))
    {
        fscanf(f, "%f", &gsm.vertices[i]);
        i+=1;
    }
    fclose(f);
    return gsm;
}