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
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 450;
    // window variables
    //const int windowDimensions[0]{512}, windowDimensions[1]{450};
    const char * title = "Dapper Dasher!";
    // INITIALIZE THE WINDOW
    InitWindow(windowDimensions[0], windowDimensions[1], title);

    // gravity variables
    const int gravity{ 1'000 }; // accelleration due to gravity in (pixels per second ) per second
    const int jumpVelocity { -600 }; // this is in pixels per second
    int velocity { 0 }; // this is in pixels per second

    // player variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimationData scarfyData
    {
        { 0.0, 0.0, ( scarfy.width / 6.0f ), ( scarfy.height * 1.0F ) },                              // Rectangle rectangle
        { windowDimensions[0]/2 - scarfyData.rectangle.width/2, windowDimensions[1] - scarfyData.rectangle.height }, // Vector2 position
        { 0 },                                                                                        // int frame
        { 1.0 / 12.0 },                                                                               // float updateTime
        { 0.0 }                                                                                       // float runningTime
    };
    
    bool isInAir{false};
    
    // hazard variables
    // nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimationData for nebula
    AnimationData nebulae[3] {};

    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebula.width / 8.0f;
        nebulae[i].rectangle.height = nebula.height / 8.0f;
        nebulae[i].position.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].position.x = windowDimensions[0];
    nebulae[1].position.x = windowDimensions[0] + 300;
    nebulae[2].position.x = windowDimensions[0] + 600;
    

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
        if(scarfyData.position.y >= windowDimensions[1] - scarfyData.rectangle.height)
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
        nebulae[0].position.x += nebulaVelocity * deltaTime;

        // update the second nebula's position
        nebulae[1].position.x += nebulaVelocity * deltaTime;

        // update the nebula's running time
        nebulae[0].runningTime +=deltaTime;

        // update the nebula's animation
        if(nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;

            // update animation frame
            nebulae[0].rectangle.x = nebulae[0].frame * nebulae[0].rectangle.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }


        

        // update the nebula's running time
        nebulae[1].runningTime += deltaTime;

        // update the nebula's animation
        if(nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;

            // update animation frame
            nebulae[1].rectangle.x = nebulae[1].frame * nebulae[1].rectangle.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        // Draw nebula
        DrawTextureRec(nebula, nebulae[0].rectangle, nebulae[0].position, WHITE);
        // draw second nebula
        DrawTextureRec(nebula, nebulae[1].rectangle, nebulae[1].position, WHITE);

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