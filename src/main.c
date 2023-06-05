#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "orbiting_body.h"
#include "gravitating_body.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 900
#define MIN_ORBITING_BODY_RADIUS 0.1
#define MAX_ORBITING_BODY_RADIUS 4.0
#define ORBIT_SPEED 10.0
#define GRAVITY_STRENGTH 1

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("brrr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window creation error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer creation error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    srand(time(NULL));

    int center_x = SCREEN_WIDTH / 2;
    int center_y = SCREEN_HEIGHT / 2;

    const int NUM_ORBITING_BODIES = 5024;
    OrbitingBody orbitingBodies[NUM_ORBITING_BODIES];
    for (int i = 0; i < NUM_ORBITING_BODIES; ++i)
    {

        OrbitingBody body;
        double r;

        body.angle = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;

        // random number between 0.0 and 1.0
        r = (double)rand() / (double)RAND_MAX;
        // with a bias towards smaller bodies
        r = pow(r, 20);
        body.radius = r * MAX_ORBITING_BODY_RADIUS + MIN_ORBITING_BODY_RADIUS;

        r = (double)rand() / (double)RAND_MAX;
        // shift r so its between 0.1 and 0.9 use within
        double within = 0.2;
        r = r * (1.0 - within * 2.0) + within;
        double x = r * SCREEN_WIDTH;
        r = (double)rand() / (double)RAND_MAX;
        r = r * (1.0 - within * 2.0) + within;
        double y = r * SCREEN_HEIGHT;
        body.initialX = x;
        body.initialY = y;

        double dist_to_center = sqrt(pow(x - center_x, 2) + pow(y - center_y, 2));

        // random number between -0.1 and 1.0
        r = (double)rand() / (double)RAND_MAX * 1.1 - 0.1;
        double speed = r * ORBIT_SPEED;

        // speed is proportional to the distance to the center, and the radius of the body
        double radius_penalty = 1.0 / (body.radius * 0.001);
        double dist_penalty = 1.0 / ((dist_to_center * dist_to_center) * 1000.0);
        body.speed = speed * radius_penalty * dist_penalty;

        body.distanceToCenter = dist_to_center;

        orbitingBodies[i] = body;
    }

    const int NUM_GRAVITATING_BODIES = 5;
    GravitatingBody gravitatingBodies[NUM_GRAVITATING_BODIES];
    for (int i = 0; i < NUM_GRAVITATING_BODIES; ++i)
    {
        GravitatingBody body;
        body.initialX = ((double)rand() / (double)RAND_MAX) * (SCREEN_WIDTH - 200) + 100;
        body.initialY = ((double)rand() / (double)RAND_MAX) * (SCREEN_HEIGHT - 200) + 100;
        body.isAttracted = rand() % 2; // Randomly set if the body is attracted to the center

        gravitatingBodies[i] = body;
    }

    int isRunning = 1;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUM_ORBITING_BODIES; ++i)
        {
            OrbitingBody *body = &orbitingBodies[i];
            orbiting_body_step(body, center_x, center_y, ORBIT_SPEED);
            orbiting_body_draw(body, renderer);
        }

        for (int i = 0; i < NUM_GRAVITATING_BODIES; ++i)
        {
            GravitatingBody *body = &gravitatingBodies[i];
            gravitating_body_step(body, center_x, center_y, GRAVITY_STRENGTH);
            gravitating_body_draw(body, renderer, center_x, center_y, GRAVITY_STRENGTH);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
