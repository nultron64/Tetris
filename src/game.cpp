#include "game.hpp"
#include <iostream> //temp

Game::Game()
{
    reset();
    currBlock.posx=4;
    currBlock.posy=-4;

    nextBlock.posx=11;
    nextBlock.posy=9;
}

void Game::draw()
{
    grid.drawGrid();
    currBlock.draw();
    nextBlock.draw();

}

void Game::rotate()
{
    if (onPause) return;
    // rotate -> if overlap, rotate back return
    // rotate -> if out of left/right border, try to translate, if overlaps, rotate back, return
    currBlock.rotate();
    // std::cout << isOverlapping() << std::endl;
    if (isOverlapping()) {
        // std::cout << "Here 1" << std::endl;
        currBlock.rotate(-1);
    }
    else {
        int posx_save = currBlock.posx;
        while (isOverLeft()) {
            currBlock.posx++;
            if (isOverlapping()) {
                currBlock.rotate(-1);
                currBlock.posx = posx_save;
                return;
            }
        }
        while (isOverRight()) {
            currBlock.posx--;
            if (isOverlapping()) {
                currBlock.rotate(-1);
                currBlock.posx = posx_save;
                return;
            }
        }
    }
}

int Game::isOverLeft()
{
    // check from left side
    for(int j=0; j<4; j++) {
        int flag = 0;
        for(int i=0; i<4; i++) {
            flag += blocks[currBlock.id][currBlock.rot][i][j];
        }
        if (flag) {
            if (currBlock.posx+j<0){
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

int Game::isOverRight()
{
    // check from right side
    for(int j=3; j>=0; j--) {
        int flag = 0;
        for(int i=0; i<4; i++) {
            flag += blocks[currBlock.id][currBlock.rot][i][j];
        }
        if (flag) {
            if (currBlock.posx+j>=grid.numCols) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

void Game::moveLeft()
{
    if (onPause) return;
    // change pox, check if over left, if true - roll back change
    currBlock.posx--;
    if (isOverlapping() || isOverLeft()) currBlock.posx++;
}

void Game::moveRight()
{
    if (onPause) return;
    // change pox, check if over left, if true - roll back change
    currBlock.posx++;
    if (isOverlapping() || isOverRight()) currBlock.posx--;
}

int Game::isOverlapping()
{
    // check if the curr block is overlapping with grid or -
    // - if curr block goes over the bottom border

    // checks from bottom to top
    for(int i=3; i>=0; i--) {
        for(int j=0; j<4; j++) {
            if (blocks[currBlock.id][currBlock.rot][i][j]==0) continue;
            if (currBlock.posy+i>=grid.numRows) return 1;
            if ((0<=currBlock.posx+j && currBlock.posx+j<grid.numCols)
               && (0<=currBlock.posy+i && currBlock.posy+i<grid.numRows)
               && grid.grid[currBlock.posy+i][currBlock.posx+j]) {
                return 1;
            }
        }
    }
    return 0;
}

void Game::moveDown()
{
    if (onPause) return;
    currBlock.posy++;
    if (isOverlapping()) {
        currBlock.posy--;
        handleBlockLanding();
    }
}

void Game::pause()
{
    onPause = 1;
    lastPauseTime = GetTime();
}

void Game::update()
{
    if (!onPause) return;

    if (GetTime()-lastPauseTime>=0.7) {
        onPause=0;
        for(int i=0; i<grid.numRows; i++) {
            int flag = 1;
            for (int j=0; j<grid.numCols; j++) {
                if (grid.grid[i][j]==0) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                for(int k=i; k>0; k--) { // k is used as i 
                    for(int j=0; j<grid.numCols; j++) {
                        grid.grid[k][j] = grid.grid[k-1][j];
                    }
                }
                for(int j=0; j<grid.numCols; j++) {
                    grid.grid[0][j] = 0;
                }
                score++;
            }
        }
    }
}

void Game::handleBlockLanding()
{
    writeCurrBlockToGrid();

    for(int i=0; i<grid.numRows; i++) {
        int flag = 1;
        for(int j=0; j<grid.numCols; j++) {
            if (grid.grid[i][j]==0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            for(int j=0; j<grid.numCols; j++) {
                if (grid.grid[i][j]) grid.grid[i][j] += 7;
            }
            pause(); // will be called again and again many times, but no problem
        }
    }

    if (isGameOver()) {
        std::cout << "Game Over" << std::endl;
        reset();
    }

    currBlock.copyValues(nextBlock);
    currBlock.posx = 4;
    currBlock.posy = -4;
    nextBlock.randomize();
}

void Game::writeCurrBlockToGrid()
{
    for(int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (blocks[currBlock.id][currBlock.rot][i][j]){
                grid.grid[currBlock.posy+i][currBlock.posx+j] = currBlock.color;
            }
        }
    }
}

int Game::isGameOver()
{
    for(int j=0; j<grid.numCols; j++) {
        if (grid.grid[0][j]) return 1;
    }
    return 0;
}

void Game::reset()
{
    score = 0;
    grid.reset();
    currBlock.randomize();
    nextBlock.randomize();
}