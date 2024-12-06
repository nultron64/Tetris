#include "Grid.hpp"
#include "colors.hpp"
#include <raylib.h>

Grid::Grid()
{
    numRows = 20;
    numCols = 10;

    leftPad=10; topPad=10;

    reset();
}

void Grid::reset()
{
    for(int row=0; row<numRows; row++) {
        for(int col=0; col<numCols; col++) {
            grid[row][col] = 0;
        }
    }
}

void Grid::drawGrid()
{
    int tCellSize=cellSize+cellGap; // total cell size = cell size + gap size
    
    for(int row=0; row<numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            // DrawRectangle(leftPad+tCellSize*col, topPad+tCellSize*row, cellSize, cellSize, colors[grid[row][col]]);
            Rectangle rec = {(float)leftPad+tCellSize*col, (float)topPad+tCellSize*row, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(rec, bordRad, 0, colors[grid[row][col]]);
        }
    }
}

