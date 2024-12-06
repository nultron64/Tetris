#pragma once

#include <raylib.h>

class Cell
{
public:
    int cellSize;
    int cellGap;
    int tCellSize;
    float bordRad; // border radius

    Cell() 
    {
        cellSize = 30;
        cellGap = 2;
        tCellSize = cellSize+cellGap; // total cellsize;
        bordRad = 0.128;
    }
};