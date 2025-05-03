#include "entetes/entete_generale.h"


// collision horizontale
int collisionHorizontale(SDL_Renderer* renderer, SDL_Rect* rectangle, MAP* map, CAMERA* camera) {
    int xmin, ymin, xmax, ymax;

    // Ajuster la position du rectangle par rapport à la caméra
    int adjustedX = rectangle->x - camera->cameraX;

    xmin = adjustedX / TILE_SIZE;
    ymin = rectangle->y / TILE_SIZE;
    xmax = (adjustedX + rectangle->w - 1) / TILE_SIZE;
    ymax = (rectangle->y + rectangle->h - 1) / TILE_SIZE;

    // Parcourir les tuiles qui pourraient être en collision
    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            // Vérifie si la tuile existe et si c'est un obstacle
            if (getTile(map, x, y) != 0) {
                SDL_Rect tileRect = map->recTile[y * map->map_width + x];

                // Vérifie l'intersection avec le rectangle du joueur
                if (SDL_HasIntersection(rectangle, &tileRect)) {
                    // Collision détectée, gérer la collision
                    if (rectangle->x + rectangle->w <= tileRect.x + (tileRect.w / 2)) {
                        // Collision à droite
                        rectangle->x = tileRect.x - rectangle->w; // Ajuste la position
                    } else {
                        // Collision à gauche
                        rectangle->x = tileRect.x + tileRect.w; // Ajuste la position
                    }

                    // Optionnel : dessiner une indication de collision
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &tileRect);
                    return 1; // Collision détectée
                }
            }
        }
    }
    return 0; // Pas de collision
}


// collision  verticale
int collisionVerticale (SDL_Renderer* renderer,SDL_Rect* rectangle, MAP* map, CAMERA* camera, player* joueur)
{
    int xmin,ymin,xmax,ymax;

    // Ajuster la position du rectangle par rapport à la caméra
    int adjustedX = rectangle->x - camera->cameraX;

        xmin = (rectangle->x) / TILE_SIZE;
        ymin = (rectangle->y) / TILE_SIZE;
        xmax = ((rectangle->x) + rectangle->w -1)/ TILE_SIZE;
        ymax = ((rectangle->y) + rectangle->h -1)/ TILE_SIZE;

    for ( int y = ymin; y<=ymax; y++)
    {
        for (int x=xmin ;x<=xmax; x++)
        {
            if (SDL_HasIntersection(rectangle,&map->recTile[ y * map->map_width + x]) && getTile(map,x,y))
            {
                if (rectangle->y+rectangle->h >= map->recTile[ y * map->map_width + x].y &&
                    rectangle->y+rectangle->h <= map->recTile[ y * map->map_width + x].y + (map->recTile[ y * map->map_width + x].h/2))
                {
                    rectangle->y = map->recTile[ y * map->map_width + x].y - rectangle->h;
                    SDL_SetRenderDrawColor(renderer,200,33,200,255);
                    SDL_RenderFillRect(renderer,&map->recTile[ y * map->map_width + x]);

                    return 1;
                }

                if (rectangle->y <= map->recTile[ y * map->map_width + x].y + map->recTile[ y * map->map_width + x].h)
                {
                    rectangle->y = map->recTile[ y * map->map_width + x].y + map->recTile[ y * map->map_width + x].h;
                    joueur->vy = 0;
                    //puts("vrai H\n");
                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
                    SDL_RenderFillRect(renderer,&map->recTile[ y * map->map_width + x]);

                    return 2;
                }
            }
        }
    }

    // Raegistement en haut
    // apres collision en haut
    if (rectangle->y < 0)
    {
        rectangle->y = 0;
        joueur->vy = 0;
    }

    return 0;
}

