#include "raylib.h"

int main()
{

    // VARIABLES
    // window
    const int windowWidth{512}, windowHeight{450};
    const char * title = "Dapper Dasher!";
    // gravity
    const int gravity{1'000}; // accelleration due to gravity in (pixels per second ) per second
    const int jumpVelocity{-600}; // this is in pixels per second
    int velocity{0}; // this is in pixels per second

    // INITIALIZE THE WINDOW
    InitWindow(windowWidth, windowHeight, title);

    // player
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRectangle;
    scarfyRectangle.width = scarfy.width/6;
    scarfyRectangle.height = scarfy.height;
    scarfyRectangle.x = 0;
    scarfyRectangle.y = 0;
    Vector2 scarfyPosition;
    scarfyPosition.x = windowWidth/2 - scarfyRectangle.width/2;
    scarfyPosition.y = windowHeight - scarfyRectangle.height;
    // gameplay
    bool isInAir{false};
    // END VARIABLES

    
    // Set the target FPS
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float deltaTime{ GetFrameTime() };
        
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
            velocity += gravity * deltaTime;
            isInAir = true;
        }
        
        // jump
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // update Y position
        scarfyPosition.y += velocity * deltaTime;

        // Draw the player character
        DrawTextureRec(scarfy, scarfyRectangle, scarfyPosition, WHITE);
       
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    //unload the texture, shutting things down properly
    UnloadTexture(scarfy);
    CloseWindow();
}