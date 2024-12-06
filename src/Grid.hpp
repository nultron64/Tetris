#pragma once
#include <raylib.h>
#include "cell.hpp"

class Grid : Cell
{
public:
    int grid[20][10];

    Grid();
    void reset();
    void drawGrid();

private:
    int numRows;
    int numCols;

    int leftPad, topPad;

    friend class Game;
};