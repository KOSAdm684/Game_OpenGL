#include "Model.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    
    for (i = 0; i < n * m; i += m)
    {
        float x = arr[i];
        float y = arr[i + 1];
        arr[i] = x * cos(-M_PI_2) - y * sin(-M_PI_2);
        arr[i + 1] = x * sin(-M_PI_2) + y * cos(-M_PI_2);
    }
    
    fclose(f);
    return arr;
}