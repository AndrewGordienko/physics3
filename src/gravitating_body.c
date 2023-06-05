#include "gravitating_body.h"
#include <math.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void gravitating_body_step(GravitatingBody* body, int centerX, int centerY, double strength) {
    if (body->isAttracted) {
        double dx = centerX - body->initialX;
        double dy = centerY - body->initialY;
        double distance = sqrt(dx * dx + dy * dy);
        double directionX = dx / distance;
        double directionY = dy / distance;

        body->initialX += directionX * strength * distance;
        body->initialY += directionY * strength * distance;
    }
}

void gravitating_body_draw(GravitatingBody* body, SDL_Renderer* renderer, int centerX, int centerY, double strength) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    filledCircleColor(renderer, (int)body->initialX, (int)body->initialY, (int)strength, 0xFFFFFFFF);
}
