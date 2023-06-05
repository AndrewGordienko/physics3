#include <SDL2_gfxPrimitives.h>

#ifndef ORBITING_BODY_H
#define ORBITING_BODY_H

typedef struct
{
    double angle;
    double initialX;
    double initialY;
    double distanceToCenter;
    double radius;
    double speed;
} OrbitingBody;

void orbiting_body_step(OrbitingBody *body, int centerX, int centerY, double speed);
void orbiting_body_draw(OrbitingBody *body, SDL_Renderer *renderer);

#endif
