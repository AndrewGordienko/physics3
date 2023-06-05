#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "orbiting_body.h"
#include <math.h>


void orbiting_body_step(OrbitingBody* body, int centerX, int centerY, double speed) {
    body->angle += speed;
    body->initialX = centerX + body->distanceToCenter * cos(body->angle);
    body->initialY = centerY + body->distanceToCenter * sin(body->angle);
}

void orbiting_body_draw(OrbitingBody* body, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    filledCircleColor(renderer, (int)body->initialX, (int)body->initialY, (int)body->radius, 0xFFFFFFFF);
}
