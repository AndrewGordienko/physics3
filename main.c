#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define ORBIT_RADIUS 200.0
#define ORBIT_SPEED 0.01
#define GRAVITY_STRENGTH 0.5

typedef struct {
    double angle;
    double initialX;
    double initialY;
    double distanceToCenter;
    double radius;
    int isAttracted;  // Flag to indicate if the body is attracted to the center
} Shape;

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

    const int NUM_SHAPES = 10;
    Shape shapes[NUM_SHAPES];
    for (int i = 0; i < NUM_SHAPES; ++i) {
        Shape shape;
        shape.angle = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;
        shape.radius = 20.0;
        shape.isAttracted = rand() % 2;  // Randomly set if the body is attracted to the center

        shape.initialX = ((double)rand() / (double)RAND_MAX) * (SCREEN_WIDTH - 200) + 100;
        shape.initialY = ((double)rand() / (double)RAND_MAX) * (SCREEN_HEIGHT - 200) + 100;

        shape.distanceToCenter = sqrt(pow(shape.initialX - centerX, 2) + pow(shape.initialY - centerY, 2));

        shapes[i] = shape;
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

        for (int i = 0; i < NUM_SHAPES; ++i) {
            Shape* shape = &shapes[i];

            shape->angle += ORBIT_SPEED;
            shape->initialX = centerX + shape->distanceToCenter * cos(shape->angle);
            shape->initialY = centerY + shape->distanceToCenter * sin(shape->angle);

            if (shape->isAttracted) {
                double dx = centerX - shape->initialX;
                double dy = centerY - shape->initialY;
                double distance = sqrt(dx * dx + dy * dy);
                double directionX = dx / distance;
                double directionY = dy / distance;

                shape->initialX += directionX * GRAVITY_STRENGTH * distance;
                shape->initialY += directionY * GRAVITY_STRENGTH * distance;
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            filledCircleColor(renderer, (int)shape->initialX, (int)shape->initialY, (int)shape->radius, 0xFFFFFFFF);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
