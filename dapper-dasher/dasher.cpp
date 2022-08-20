#include "raylib.h"

int main()
{
    // WINDOW VARIABLES
    const int windowWidth{512}, windowHeight{450};
    const char * title = "Dapper Dasher!";
    // INITIALIZE THE WINDOW
    InitWindow(windowWidth, windowHeight, title);

    // gravity variables
    const int gravity{1}, jumpVelocity{-22};
    int velocity{0};


    // player variables.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRectangle;
    scarfyRectangle.width = scarfy.width/6;
    scarfyRectangle.height = scarfy.height;
    scarfyRectangle.x = 0;
    scarfyRectangle.y = 0;
    Vector2 scarfyPosition;
    scarfyPosition.x = windowWidth/2 - scarfyRectangle.width/2;
    scarfyPosition.y = windowHeight - scarfyRectangle.height;

    bool isInAir{false};


    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // START DRAWING WINDOW
        BeginDrawing();
        ClearBackground(WHITE);


        // ground check
        if(scarfyPosition.y >= windowHeight - scarfyRectangle.height)
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
        scarfyPosition.y += velocity;

        DrawTextureRec(scarfy, scarfyRectangle, scarfyPosition, WHITE);
        
        
        
        
        
        
        
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    //unload the texture, shutting things down properly
    UnloadTexture(scarfy);
    CloseWindow();
}