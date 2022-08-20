#include "raylib.h"

int main()
{
    // WINDOW VARIABLES
    const int windowWidth{512}, windowHeight{450};
    const char * title = "Dapper Dasher!";
    // INITIALIZE THE WINDOW
    InitWindow(windowWidth, windowHeight, title);

    // player variables
    const int playerWidth{50}, playerHeight{80}, gravity{1}, jumpVelocity{-22};
    int posY{windowHeight - playerHeight}, velocity{0};

    bool isInAir{false};


    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // START DRAWING WINDOW
        BeginDrawing();
        ClearBackground(WHITE);


        // ground check
        if(posY >= windowHeight - playerHeight)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity
            velocity += gravity;
            isInAir = true;
        }
        
        // jump
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // update position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, playerWidth, playerHeight, BLUE);
        
        
        
        
        
        
        
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    CloseWindow();
}