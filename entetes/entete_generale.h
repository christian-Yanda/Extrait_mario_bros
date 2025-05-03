#ifndef ENTETE_GENERALE_H_INCLUDED
#define ENTETE_GENERALE_H_INCLUDED

/**** DEFINE
    DEFINI LA LARGEUR ET LA HAUTEUR DE L'ECRAN */
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 550
#define TILE_SIZE 32
#define MAP_WIDTH 80  // Carte plus grande
#define MAP_HEIGHT 25
#define VIEW_WIDTH (LARGEUR_ECRAN / TILE_SIZE)
#define VIEW_HEIGHT (HAUTEUR_ECRAN /  TILE_SIZE)
#define PLAYER_WIDTH TILE_SIZE
#define PLAYER_HEIGHT TILE_SIZE
#define PLAYER_SPEED 2
/******************************/

/** INCLUSION DES BIBLIOTHEQUES GENERALES **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <stdbool.h>
#include "joueur.h"

/** structure map */
typedef struct MAP MAP;
struct MAP{
    int map_width; // largeur map
    int map_height;  // hauteur map
    int* matrice_tuile;
    SDL_Rect* recTile; // rectangle de tile 
};
#ifndef TYPEDEF_MAP_DEFINED
#define TYPEDEF_MAP_DEFINED
typedef struct  MAP MAP;
#endif


/** PROTOTYPE DES FONCTIONS GENERALES **/
int initialistaion (SDL_Window** window, SDL_Renderer** renderer);// CREATION DE LA FENETRE ET L'INITIALISATION DE LA SDL
int loadMap(const char *filename , MAP* map); /** FONCTION DE LECTURE DU FICHIER DU FICHIER DE NIVEAU **/
void renderMap(SDL_Renderer* renderer, MAP* map, CAMERA* camera); /** FONCTION AFFICHAGE MAP **/
int getTile(MAP* map, int x, int y);// recuperation du tile
void freeWord (MAP* map);// liberation des tiles
void drawRect (SDL_Renderer* renderer , SDL_Rect* rect); // fonction dessin rectangle
void updateEvent (int* exitGame , player* joueur); // Gestion des evenements


#endif // ENTETE_GENERALE_H_INCLUDED