#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "entete_generale.h"

int collisionHorizontale(SDL_Renderer* renderer, SDL_Rect* rectangle, MAP* map, CAMERA* camera); // collision horizontale
int collisionVerticale(SDL_Renderer* renderer, SDL_Rect* rectangle, MAP* map, CAMERA* camera, player* joueur); // collision  verticale

#endif // COLLISION_H_INCLUDED
