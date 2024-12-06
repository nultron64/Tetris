#pragma once
#include "Cell.hpp"
#include "colors.hpp"

extern int blocks[7][4][4][4];

class Block : Cell
{
public:
    Block();
    void draw();
    void rotate(int dir=1); // direction =1 for clock-wise, -1 for anti
	void randomize(); // like reset. randomizes id, rot, color
	void copyValues(Block& Other); // copies id, rot, color

public: // change this to private
    int id; // id for the type of block. value: 0-6
    int posx, posy; // position value: 0-9, 0-19
    int rot; // rotation value: 0-3
    int color; // value: 1-7, 0 for empty

    friend class Game;
};