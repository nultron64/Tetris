#include "block.hpp"

Block::Block()
{
    randomize();
}

void Block::draw()
{
    int leftPad=10, topPad=10;
    for(int i=0; i<4; i++){ for(int j=0; j<4; j++) {
        if (blocks[id][rot][i][j]==0) continue;
        if (posy+i<0) continue;
        // DrawRectangle(leftPad+tCellSize*col, topPad+tCellSize*row, cellSize, cellSize, colors[grid[row][col]]);
        Rectangle rec = {(float)leftPad+tCellSize*(posx+j), (float)topPad+tCellSize*(posy+i), (float)cellSize, (float)cellSize};
        DrawRectangleRounded(rec, bordRad, 0, colors[color]);
    }}
}

void Block::rotate(int dir)
{
    rot = (rot+dir+4)%4;
    // adding 4 doesn't make any change to result if the (root+dir) is +ve
    // we need +4 if (root+dir) is -ve
}

void Block::randomize()
{
    id = GetRandomValue(0, 6);
    rot = GetRandomValue(0, 3);
    color = GetRandomValue(1, 7);
}

void Block::copyValues(Block& Other)
{
    id = Other.id;
    rot = Other.rot;
    color = Other.color;
}