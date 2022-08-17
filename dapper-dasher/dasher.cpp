#include "raylib.h"

int main()
{
    // WINDOW DIMENSIONS
    const int windowWidth{512}, windowHeight{450};
    const char * title = "Dapper Dasher!";

    // INITIALIZE THE WINDOW
    InitWindow(windowWidth, windowHeight, title);



    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // START DRAWING WINDOW
        BeginDrawing();
        ClearBackground(WHITE);
        
        
        
        
        
        
        
        
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    CloseWindow();
}