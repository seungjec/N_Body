#include "gravity.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ORENGES 3
#define MAX_GREENS 1
#define MAX_PURPLES 1
#define MAX_GRAYS 1

float GetDistance(int x, int y)
{
    return (float)sqrt(x * x + y * y);
}

int main(int argc, char** argv)
{
    int window_w = 800;
    int window_h = 600;

    const int FPS = 50;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart, frameTime;
    double dt = 0.1;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        "N-Body Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_w, window_h, false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    SDL_Event event;

    // Gravity
    //DATA* data = (DATA*)malloc(sizeof(DATA));
    Vector2D centerPos(window_w, window_h);
    int NMass = MAX_ORENGES;
    NBODY* pNbody = (NBODY*)malloc(sizeof(NBODY) * NMass);
    InitNbody(pNbody, NMass, centerPos);

    //free(data);
     
    
    // Texture
    SDL_Surface* tmpSurface;

    tmpSurface = IMG_Load("assets/background.png");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    tmpSurface = IMG_Load("assets/purple.png");
    SDL_Texture* OrengeTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    tmpSurface = IMG_Load("assets/green.png");
    SDL_Texture* GreenTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    tmpSurface = IMG_Load("assets/purple.png");
    SDL_Texture* PurpleTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    tmpSurface = IMG_Load("assets/gray.png");
    SDL_Texture* GrayTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    // End of Texture

    // Rectangle
    SDL_Rect backgroundRect{ 0,0,window_w,window_h };
    SDL_Rect OrengeRect[MAX_ORENGES]{};
    SDL_Rect GreenRect[MAX_GREENS]{};
    SDL_Rect PurpleRect[MAX_PURPLES]{};
    SDL_Rect GrayRect[MAX_GRAYS]{};

    SDL_Point OrengeDir[MAX_ORENGES]{};
    SDL_Point GreenDir[MAX_GREENS]{};
    SDL_Point GrayDir[MAX_GRAYS]{};
    SDL_Point PurpleDir[MAX_PURPLES]{};

    Uint32 tex_format;
    int tex_access, tex_w, tex_h;

    SDL_QueryTexture(OrengeTexture, &tex_format, &tex_access, &tex_w, &tex_h);
    for (int i = 0; i < MAX_ORENGES; i++)
    {
        OrengeRect[i].w = tex_w;
        OrengeRect[i].h = tex_h;
    }
    SDL_QueryTexture(GreenTexture, &tex_format, &tex_access, &tex_w, &tex_h);
    for (int i = 0; i < MAX_GREENS; i++)
    {
        GreenRect[i].w = tex_w;
        GreenRect[i].h = tex_h;
    }
    SDL_QueryTexture(PurpleTexture, &tex_format, &tex_access, &tex_w, &tex_h);
    for (int i = 0; i < MAX_PURPLES; i++)
    {
        PurpleRect[i].w = tex_w;
        PurpleRect[i].h = tex_h;
    }
    SDL_QueryTexture(GrayTexture, &tex_format, &tex_access, &tex_w, &tex_h);
    for (int i = 0; i < MAX_GRAYS; i++)
    {
        GrayRect[i].w = tex_w;
        GrayRect[i].h = tex_h;
    }
    // End of Rectangle

    // dummy variables
    Uint32 nCountFrame = 0;

    //int nBulletSpeed = 10;
    //int nEnemySpeed = 3;
    //int nTowerSpeed = 5;
    //int nEnemyRate = 30;
    //int nEnemyIdx = 0;
    //int nFireRate = 3;
    //int nTowerReload = 100;
    //int nBulletIdx = 0;
    //int nMaxRange = 100;
    //int numBullets = 0;

    //int key_dir_left = 0;
    //int key_dir_right = 0;
    //int key_dir_up = 0;
    //int key_dir_down = 0;


    // Main Loop
    while (isRunning)
    {
        // Get Ticks
        frameStart = (Uint32)SDL_GetTicks64();

        // Get Event
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        /* Keyboard event */
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            }
            break;
        }

        // Update
        if (pNbody != NULL)
        {
            calAcceleration(pNbody, NMass);
            calSpeed(pNbody, NMass, dt);
            calPosition(pNbody, NMass, dt);
            //printVector(pNbody, NMass);
        }
        
        // Move Mass
        if (pNbody != NULL)
        {
            for (int i = 0; i < MAX_ORENGES; i++)
            {
                OrengeRect[i].x = (pNbody+i)->fPosition.x;
                OrengeRect[i].y = (pNbody+i)->fPosition.y;
            }
            //GreenRect[0].x = (pNbody + 1)->fPosition.x;
            //GreenRect[0].y = (pNbody + 1)->fPosition.y;
            //PurpleRect[0].x = (pNbody + 2)->fPosition.x;
            //PurpleRect[0].y = (pNbody + 2)->fPosition.y;
        }

        // Render
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);
        for (int i = 0; i < MAX_ORENGES; i++)
        {
            SDL_RenderCopy(renderer, OrengeTexture, NULL, &OrengeRect[i]);
        }
        //for (int i = 0; i < MAX_GREENS; i++)
        //{
        //    SDL_RenderCopy(renderer, GreenTexture, NULL, &GreenRect[i]);
        //}
        //for (int i = 0; i < MAX_PURPLES; i++)
        //{
        //    SDL_RenderCopy(renderer, PurpleTexture, NULL, &PurpleRect[i]);
        //}
        SDL_RenderPresent(renderer);

        // Control iteration time for Specific FPS
        frameTime = (Uint32)SDL_GetTicks64() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        if (frameTime > 0)
        {
            //printf("FPS : %d\n", (int)(1/(((Uint32)SDL_GetTicks64() - frameStart) / 1000.f)));
        }

        nCountFrame++;
    }

    if (pNbody != NULL)
    {
        free(pNbody);
    }
    // Close SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
