#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "orbiting_body.h"
#include "gravitating_body.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define ORBIT_RADIUS 200.0
#define ORBIT_SPEED 0.01
#define GRAVITY_STRENGTH 1

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("brrr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer creation error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    srand(time(NULL));

    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    const int NUM_ORBITING_BODIES = 10;
    OrbitingBody orbitingBodies[NUM_ORBITING_BODIES];
    for (int i = 0; i < NUM_ORBITING_BODIES; ++i) {
        OrbitingBody body;
        body.angle = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;
        body.radius = 20.0;

        body.initialX = ((double)rand() / (double)RAND_MAX) * (SCREEN_WIDTH - 200) + 100;
        body.initialY = ((double)rand() / (double)RAND_MAX) * (SCREEN_HEIGHT - 200) + 100;

        body.distanceToCenter = sqrt(pow(body.initialX - centerX, 2) + pow(body.initialY - centerY, 2));

        orbitingBodies[i] = body;
    }

    const int NUM_GRAVITATING_BODIES = 5;
    GravitatingBody gravitatingBodies[NUM_GRAVITATING_BODIES];
    for (int i = 0; i < NUM_GRAVITATING_BODIES; ++i) {
        GravitatingBody body;
        body.initialX = ((double)rand() / (double)RAND_MAX) * (SCREEN_WIDTH - 200) + 100;
        body.initialY = ((double)rand() / (double)RAND_MAX) * (SCREEN_HEIGHT - 200) + 100;
        body.isAttracted = rand() % 2;  // Randomly set if the body is attracted to the center

        gravitatingBodies[i] = body;
    }

    int isRunning = 1;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUM_ORBITING_BODIES; ++i) {
            OrbitingBody* body = &orbitingBodies[i];
            orbiting_body_step(body, centerX, centerY, ORBIT_SPEED);
            orbiting_body_draw(body, renderer);
        }

        for (int i = 0; i < NUM_GRAVITATING_BODIES; ++i) {
            GravitatingBody* body = &gravitatingBodies[i];
            gravitating_body_step(body, centerX, centerY, GRAVITY_STRENGTH);
            gravitating_body_draw(body, renderer, centerX, centerY, GRAVITY_STRENGTH);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
