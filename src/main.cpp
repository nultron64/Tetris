#include <raylib.h>
#include <iostream>
#include "game.hpp"

int main()
{
    Color darkBlue = {44, 44, 127, 255};
    Color lightBlue = {59, 85, 162, 255};
    Color fadeBlue = {19, 75, 112, 255};

    const int screenWidth = 522;
    const int screenHeight = 660;

    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Font bruceForeverFont = LoadFont("fonts/bruce-forever-font/BruceForeverRegular-X3jd2.ttf");

    Game game;
    Block& block = game.currBlock;

    char scoreText[10];
    double prevTime = GetTime();
    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (IsKeyPressed(KEY_LEFT)) {
            game.moveLeft();
        }
        else if (IsKeyPressed(KEY_RIGHT)) {
            game.moveRight();
        }
        else if (IsKeyPressed(KEY_UP)) {
            game.rotate();
        }
        else if (IsKeyPressed(KEY_DOWN)) {
            game.moveDown();
        }
        else if (IsKeyPressed(KEY_R)) {
            game.rotate();
        }
        else if (IsKeyPressed(KEY_W)) {
            block.posy--;
        }
        if (GetTime()-prevTime>=0.4) {
            game.moveDown();
            prevTime=GetTime();
        }

        game.update();
        Rectangle rec;
        Vector2 pos;

        ClearBackground(darkBlue);

        // Next block place
        rec = {357, 293, 138, 138};
        DrawRectangleRounded(rec, 0.1, 0, fadeBlue);
        rec = {362, 298, 128, 128};
        DrawRectangleRounded(rec, 0.05, 0, lightBlue);

        game.draw();

        // Drawing Score
        const char* text = "SCORE";
        pos = {366, 35};
        DrawTextEx(bruceForeverFont, text, pos, 28, 2, WHITE);

        rec = {355, 70, 145, 40};
        DrawRectangleRounded(rec, 0.2, 0, lightBlue);

        sprintf(scoreText, "%d", game.score);
        itoa(game.score, scoreText, 10);
        Vector2 scoreTextSize = MeasureTextEx(bruceForeverFont, scoreText, 32, 2);
        pos.x = 430-scoreTextSize.x/2;
        pos.y = 90-scoreTextSize.y/2;
        DrawTextEx(bruceForeverFont, scoreText, pos, 32, 2, WHITE);
        // score - end

        // Drawing "NEXT"
        text = "NEXT";
        pos = {375, 230};
        DrawTextEx(bruceForeverFont, text, pos, 28, 2, WHITE);
        // "NEXT" -end
        EndDrawing();
    }

    UnloadFont(bruceForeverFont);
    CloseWindow();
    return 0;
}