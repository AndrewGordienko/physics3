#ifndef GRAVITATING_BODY_H
#define GRAVITATING_BODY_H

#include <SDL.h>

typedef struct {
    double initialX;
    double initialY;
    int isAttracted;
} GravitatingBody;

void gravitating_body_step(GravitatingBody* body, int centerX, int centerY, double strength);
void gravitating_body_draw(GravitatingBody* body, SDL_Renderer* renderer, int centerX, int centerY, double strength);

#endif
