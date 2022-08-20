#include "raylib.h"

int main()
{
    // window variables
    const int windowWidth{512}, windowHeight{450};
    const char * title = "Dapper Dasher!";
    // INITIALIZE THE WINDOW
    InitWindow(windowWidth, windowHeight, title);

    // gravity variables
    const int gravity{ 1'000 }; // accelleration due to gravity in (pixels per second ) per second
    const int jumpVelocity { -600 }; // this is in pixels per second
    int velocity { 0 }; // this is in pixels per second

    // player variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRectangle { 0.0, 0.0, scarfy.width/6, scarfy.height };
    Vector2 scarfyPosition { windowWidth/2 - scarfyRectangle.width/2, windowHeight - scarfyRectangle.height };

    // hazard variables
    // nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRectangle { 0.0, 0.0, nebula.width/8, nebula.height/8 };
    Vector2 nebulaPosition{ windowWidth, windowHeight - nebulaRectangle.height };

    int nebulaVelocity{-600}; // nebula X velocity in pixels per second

    // gameplay variables
    bool isInAir{false};
    int frame{}; //animation frame
    const float updateTime{1.0/12.0}; // amount of time before we update the animation frame
    float runningTime{};
    
    // Set the target FPS
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float deltaTime{ GetFrameTime() };

        // update the running time
        runningTime += deltaTime;

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

        // update nebula position
        nebulaPosition.x += nebulaVelocity * deltaTime;

        // update scarfy's Y position
        scarfyPosition.y += velocity * deltaTime;


        if(!isInAir)
        {
            if(runningTime >= updateTime)
            {
                runningTime = 0.0;

                // update animation frame
                scarfyRectangle.x = frame * scarfyRectangle.width;
                frame++;
                if(frame>5)
                {
                    frame = 0;
                }
            }
        }
        // Draw nebula
        DrawTextureRec(nebula, nebulaRectangle, nebulaPosition, WHITE);

        // Draw the player character
        DrawTextureRec(scarfy, scarfyRectangle, scarfyPosition, WHITE);
       
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    //unload the texture, shutting things down properly
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}