#include "raylib.h"

int main()
{
    // WINDOW VARIABLES
    const int windowWidth{512}, windowHeight{450};
    const char * title = "Dapper Dasher!";
    // INITIALIZE THE WINDOW
    InitWindow(windowWidth, windowHeight, title);

    // rectangle dimensions
    const int width{50}, height{80};
    int posY{windowHeight - height}, velocity{0};



    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // START DRAWING WINDOW
        BeginDrawing();
        ClearBackground(WHITE);

        if(IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }

        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        
        
        
        
        
        
        
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    CloseWindow();
}