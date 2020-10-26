#include "Model.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

float* Model::readModel(const char* path, int &cv)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        std::cout << "File not opened" << std::endl;
    }
    int i = 0;

    int n = 0;
    int m = 0;

    if (fscanf(f, "%d %d\n", &n, &m) == EOF)
    {
        std::cout << "Error of reading" << std::endl;
    }

    float *arr = new float[n*m];

    while(!feof(f))
    {
        fscanf(f, "%f", &arr[i]);
        i+=1;
    }
    cv = i;
    std::cout << sizeof(arr) << " " << cv << std::endl;
    fclose(f);
    return arr;
}