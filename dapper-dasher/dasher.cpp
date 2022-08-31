#include "raylib.h"

struct AnimationData
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float updateTime, runningTime;
};

bool isOnGround(AnimationData data, int windowHeight)
{
    return data.position.y >= windowHeight - data.rectangle.height;
}

AnimationData updateAnimationData(AnimationData data, float deltaTime, int maxFrameValue)
{
    // update running time
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //update animation frame
        data.rectangle.x = data.frame * data.rectangle.width;
        data.frame++;
        if(data.frame > maxFrameValue)
        {
            data.frame = 0;
        }
    }
    return data;
}

void MoveBackground(Texture2D texture, float speed, float &xVariable, float deltaTime)
{
    xVariable -= speed * deltaTime;
    if( xVariable <= - texture.width * 2 )
    {
        xVariable = 0.0;
    }

    // draw the background
    Vector2 positionOne{xVariable, 0.0};
    DrawTextureEx( texture, positionOne, 0.0, 2.0, WHITE );
    Vector2 positionTwo{xVariable + texture.width * 2, 0.0};
    DrawTextureEx( texture, positionTwo, 0.0, 2.0, WHITE );
}

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
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

    const int sizeOfNebulae{6};
    // AnimationData for nebula
    AnimationData nebulae[sizeOfNebulae] {};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebula.width / 8.0f;
        nebulae[i].rectangle.height = nebula.height / 8.0f;
        nebulae[i].position.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].position.x = windowDimensions[0] + (i*300);
    }

    float finishLinePosition{ nebulae[sizeOfNebulae-1].position.x + 300 };

    int nebulaVelocity{-250}; // nebula X velocity in pixels per second
    
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float backgroundX{};

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float midgroundX{};

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float foregroundX{};

    bool collision{};

    // Set the target FPS
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float deltaTime{ GetFrameTime() };

        // START DRAWING WINDOW
        BeginDrawing();
        ClearBackground(WHITE);

        MoveBackground(background, 20, backgroundX, deltaTime);
        MoveBackground(midground, 40, midgroundX, deltaTime);
        MoveBackground(foreground, 80, foregroundX, deltaTime);

        // ground check
        if(isOnGround(scarfyData, windowDimensions[1]))
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
            scarfyData = updateAnimationData(scarfyData, deltaTime, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update nebula position
            nebulae[i].position.x += nebulaVelocity * deltaTime;
        }

        // update finish line position
        finishLinePosition += nebulaVelocity * deltaTime;

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimationData(nebulae[i], deltaTime, 7);
        }   

        for (AnimationData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebulaRectangle { nebula.position.x + pad, nebula.position.y + pad, nebula.rectangle.width - (2 * pad), nebula.rectangle.height- (2 * pad) };
            Rectangle scarfyRectangle { scarfyData.position.x, scarfyData.position.y, scarfyData.rectangle.width, scarfyData.rectangle.height };

            if(CheckCollisionRecs(nebulaRectangle, scarfyRectangle))
            {
                collision = true;
            }
        }

        if(collision)
        {
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
        }
        else if (scarfyData.position.x >= finishLinePosition)
        {
            DrawText("You Win!", windowDimensions[0]/4, windowDimensions[1]/2, 40, GREEN);
        }
        else
        {
            for (int i = 0; i < sizeOfNebulae; i++)
            {
            // Draw nebula
            DrawTextureRec(nebula, nebulae[i].rectangle, nebulae[i].position, WHITE);
            }
        
            // Draw the player character
            DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.position, WHITE);
        }

        // STOP DRAWING WINDOW
        EndDrawing();
    }

    //unload the texture, shutting things down properly
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}