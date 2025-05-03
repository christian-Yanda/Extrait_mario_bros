#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

  // DEFINE
  #define gravite 0.35
  #define force_saut 10


#include "entete_generale.h" // inclusin de bibliotheques generales

// STUCTURE PLAYER
/* cette structure gere tout ce qui concerne le personnage du jeu*/
struct  player
{
    int playerX;
    int playerY;
    int playerW;
    int playerH;

    SDL_Rect rectPerso; // rectangle du personnage 
    char nomJoueur; // nom du joueur
    int nbVie; // nombre de vie 
    float vx,vy; // vitesse horizontale et verticale
    bool isJump; // variable booleenne pour le gerer le saut
    bool mouveGauche; // deplacement gauche 
    bool mouveDroite; // deplacement droite;
};
typedef struct player player;

// STRUCTURE CAMEREA 
struct CAMERA{ 
  int cameraX;
  int cameraY;
};
typedef struct  CAMERA CAMERA;

struct MAP;
#ifndef TYPEDEF_MAP_DEFINED
#define TYPEDEF_MAP_DEFINED
typedef struct  MAP MAP;
#endif


player* initPlayer(float x, float y, float w, float h); // fonction d'initialisation player
void drawPlayer (SDL_Renderer* renderer , player* joueur, CAMERA* camera); // Dessin player
void freePlayer(player* joueur); // Liberation du Player
void jump ( player* joueur); // Saut
void updatePlayer (player* joueur, SDL_Renderer* renderer, MAP* map, CAMERA* camera); // Update Player
void initCamera (int* cameraX, int* cameraY); // initialisation de la camera du jeu
//
void updateCamera(CAMERA* camera, player* joueur, MAP* map);

#endif // JOUEUR_H_INCLUDED