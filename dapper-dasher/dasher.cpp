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
    Rectangle scarfyRectangle { 0.0, 0.0, (scarfy.width/6.0f), (scarfy.height * 1.0F) };
    Vector2 scarfyPosition { windowWidth/2 - scarfyRectangle.width/2, windowHeight - scarfyRectangle.height };

    bool isInAir{false};
    int playerFrame{}; // player animation frame
    const float playerUpdateTime{ 1.0 / 12.0 }; // amount of time before we update the player animation frame
    float playerRunningTime{};
    
    // hazard variables
    // nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRectangle { 0.0, 0.0, (nebula.width / 8.0f), (nebula.height/8.0f) };
    Vector2 nebulaPosition{ windowWidth, windowHeight - nebulaRectangle.height };

    Rectangle nebula2Rectangle { 0.0, 0.0, (nebula.width / 8.0f), (nebula.height/8.0f) };
    Vector2 nebula2Position {windowWidth+300, windowHeight - nebulaRectangle.height};

    int nebulaVelocity{-300}; // nebula X velocity in pixels per second

    int nebulaFrame{};
    const float nebulaUpdateTime{ 1.0 / 12.0 };
    float nebulaRunningTime{};

    int nebula2Frame{};
    const float nebula2UpdateTime{1.0/16.0};
    float nebula2RunningTime{};
    
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
        
        // update scarfy's Y position
        scarfyPosition.y += velocity * deltaTime;

        // update the player's animation
        if(!isInAir)
        {
            // update the running time
            playerRunningTime += deltaTime;
            if(playerRunningTime >= playerUpdateTime)
            {
                playerRunningTime = 0.0;

                // update animation frame
                scarfyRectangle.x = playerFrame * scarfyRectangle.width;
                playerFrame++;
                if(playerFrame>5)
                {
                    playerFrame = 0;
                }
            }
        }

        // update nebula position
        nebulaPosition.x += nebulaVelocity * deltaTime;

        // update the second nebula's position
        nebula2Position.x += nebulaVelocity * deltaTime;

        // update the nebula's running time
        nebulaRunningTime +=deltaTime;

        // update the nebula's animation
        if(nebulaRunningTime >= nebulaUpdateTime)
        {
            nebulaRunningTime = 0.0;

            // update animation frame
            nebulaRectangle.x = nebulaFrame * nebulaRectangle.width;
            nebulaFrame++;
            if(nebulaFrame > 7)
            {
                nebulaFrame = 0;
            }
        }

        // update the nebula's running time
        nebula2RunningTime += deltaTime;

        // update the nebula's animation
        if(nebula2RunningTime >= nebula2UpdateTime)
        {
            nebula2RunningTime = 0.0;

            // update animation frame
            nebula2Rectangle.x = nebula2Frame * nebula2Rectangle.width;
            nebula2Frame++;
            if(nebula2Frame > 7)
            {
                nebula2Frame = 0;
            }
        }

        // Draw nebula
        DrawTextureRec(nebula, nebulaRectangle, nebulaPosition, WHITE);
        // draw second nebula
        DrawTextureRec(nebula, nebula2Rectangle, nebula2Position, WHITE);

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