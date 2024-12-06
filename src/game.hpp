#pragma once
#include "Grid.hpp"
#include "block.hpp"
#include <iostream> // temp

class Game
{
    Grid grid;
    Block currBlock;
    Block nextBlock;
    int onPause; // whether the game is currently on pause or not
    double lastPauseTime;

public:
    int score;

    Game();
    void draw();
    void rotate();
    int isOverLeft(); // returns 1 if the block is out of left border
    int isOverRight();// returns 1 if the block is out of right border
    void moveLeft();
    void moveRight();
    void moveDown();

    void pause();
    void update(); // game is paused for some time when a full line is detected, this function un-pauses the game after sometime, then clears the lines

    int isOverlapping(); // check if the curr block is overlapping with grid of if curr block goes over the bottom border   

    void handleBlockLanding(); // call this once the block lands
    void writeCurrBlockToGrid(); // this is called when curr block reaches end, the current block cells will be saved in the the grid
    int isGameOver(); // returns 1 if game over

    void reset();
    friend int main(); //temp
};