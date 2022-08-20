#include "raylib.h"

struct AnimationData
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float updateTime, runningTime;
};

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
    AnimationData scarfyData
    {
        { 0.0, 0.0, ( scarfy.width / 6.0f ), ( scarfy.height * 1.0F ) },                              // Rectangle rectangle
        { windowWidth/2 - scarfyData.rectangle.width/2, windowHeight - scarfyData.rectangle.height }, // Vector2 position
        { 0 },                                                                                        // int frame
        { 1.0 / 12.0 },                                                                               // float updateTime
        { 0.0 }                                                                                       // float runningTime
    };
    
    bool isInAir{false};
    
    // hazard variables
    // nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimationData for nebula
    AnimationData nebulaData
    {
        { 0.0, 0.0, ( nebula.width / 8.0f ), ( nebula.height/8.0f ) }, // Rectangle rectangle
        { windowWidth, windowHeight - nebula.height / 8.0f },          // Vector2 position
        { 0 },                                                         // int frame
        { 1.0 / 12.0 },                                                // float updateTime
        { 0.0 }                                                        // float runningTime
    };

    AnimationData nebula2Data
    {
        { 0.0, 0.0, ( nebula.width / 8.0f ), ( nebula.height/8.0f ) }, // Rectangle rectangle
        { windowWidth + 300, windowHeight - nebula.height/8.0f },      // Vector2 position
        { 0 },                                                         // int frame
        { 1.0 / 16.0 },                                                // float updateTime     
        { 0.0 }                                                        // float runningTime
    };

    int nebulaVelocity{-300}; // nebula X velocity in pixels per second
    
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
        if(scarfyData.position.y >= windowHeight - scarfyData.rectangle.height)
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
        scarfyData.position.y += velocity * deltaTime;

        // update the player's animation
        if(!isInAir)
        {
            // update the running time
            scarfyData.runningTime += deltaTime;
            if(scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;

                // update animation frame
                scarfyData.rectangle.x = scarfyData.frame * scarfyData.rectangle.width;
                scarfyData.frame++;
                if(scarfyData.frame>5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        // update nebula position
        nebulaData.position.x += nebulaVelocity * deltaTime;

        // update the second nebula's position
        nebula2Data.position.x += nebulaVelocity * deltaTime;

        // update the nebula's running time
        nebulaData.runningTime +=deltaTime;

        // update the nebula's animation
        if(nebulaData.runningTime >= nebulaData.updateTime)
        {
            nebulaData.runningTime = 0.0;

            // update animation frame
            nebulaData.rectangle.x = nebulaData.frame * nebulaData.rectangle.width;
            nebulaData.frame++;
            if(nebulaData.frame > 7)
            {
                nebulaData.frame = 0;
            }
        }

        // update the nebula's running time
        nebula2Data.runningTime += deltaTime;

        // update the nebula's animation
        if(nebula2Data.runningTime >= nebula2Data.updateTime)
        {
            nebula2Data.runningTime = 0.0;

            // update animation frame
            nebula2Data.rectangle.x = nebula2Data.frame * nebula2Data.rectangle.width;
            nebula2Data.frame++;
            if(nebula2Data.frame > 7)
            {
                nebula2Data.frame = 0;
            }
        }

        // Draw nebula
        DrawTextureRec(nebula, nebulaData.rectangle, nebulaData.position, WHITE);
        // draw second nebula
        DrawTextureRec(nebula, nebula2Data.rectangle, nebula2Data.position, WHITE);

        // Draw the player character
        DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.position, WHITE);
       
        // STOP DRAWING WINDOW
        EndDrawing();
    }

    //unload the texture, shutting things down properly
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}