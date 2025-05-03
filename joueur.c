#include "entetes/entete_generale.h"
#include "entetes/joueur.h"
#include "entetes/collision.h"

// fonction d'initialisation player
player* initPlayer(float x, float y, float w, float h)
{
    player* joueur = malloc(sizeof(player));

    if ( joueur != NULL )
    {
        joueur->playerX = x;
        joueur->playerY = y;
        joueur->playerW = w;
        joueur->playerH = h;
        joueur->vx = 0;
        joueur->vy = 0;
        joueur->mouveDroite = false;
        joueur->mouveGauche = false;
        joueur->isJump = false;
        
        return joueur;
    }

    else
        return NULL;
}

// Liberation du Player
void freePlayer(player* joueur)
{
    free(joueur);
}

// Saut
void jump ( player* joueur)
{
    if ( joueur->isJump)
        joueur->vy = - force_saut;
}

// fonction dessin rectangle
void drawRect (SDL_Renderer* renderer , SDL_Rect* rect)
{
    SDL_RenderDrawRect(renderer,rect);
}

// Dessin player
void drawPlayer (SDL_Renderer* renderer ,player* joueur, CAMERA* camera)
{
    SDL_Rect playerRect = {joueur->playerX- camera->cameraX, joueur->playerY, PLAYER_WIDTH, PLAYER_HEIGHT};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &playerRect);

    joueur->rectPerso = playerRect;
}

// Update Player
void updatePlayer(player* joueur, SDL_Renderer* renderer, MAP* map, CAMERA* camera) {

    SDL_Rect recTest = {joueur->playerX, joueur->playerY, joueur->playerW, joueur->playerH}; // Rectangle de test pour les collisions et le déplacement du personnage en horizontale
    SDL_SetRenderDrawColor(renderer, 0,233,200,255);
    SDL_Rect recTest1 = {joueur->playerX, joueur->playerY, joueur->playerW, joueur->playerH};// Rectangle de test pour les collisions et le déplacement du personnage en verticale
    
    // Déplacement vers la droite
    if (joueur->mouveDroite) {
        recTest.x += joueur->vx;

        // test si collision horizontale            
        if(collisionHorizontale(renderer, &recTest, map, camera) == 0)
        {
            SDL_SetRenderDrawColor(renderer, 200,233,0,255);
            joueur->playerX = recTest.x;
            recTest1 = joueur->rectPerso;
        }
        printf(" *Cam:%d__PosX:%d__PosY:%d__RectTest:%d* ", camera->cameraX, joueur->playerX,joueur->playerY, recTest.x);
        printf("\n");
    }

    // Déplacement vers la gauche
    if (joueur->mouveGauche) {
        recTest.x += joueur->vx;

        // test si collision horizontale            
        if(collisionHorizontale(renderer, &recTest, map, camera) == 0)
        {
            SDL_SetRenderDrawColor(renderer, 200,233,0,255);
            joueur->playerX = recTest.x;
            recTest1 = joueur->rectPerso;
        }
        printf(" *Cam:%d__PosX:%d__PosY:%d__RectTest:%d* ", camera->cameraX, joueur->playerX,joueur->playerY, recTest.x);
        printf("\n");
    }

   
}
//-------------------------------------------------------

/////////////////////////////////////////////////////////
        // Geston de la camera du jeu 
// initialisation de la camera du jeu
void initCamera (int* cameraX, int* cameraY){
    *cameraX = 0; // cameraX a zero
    *cameraY = 0; // cameraY a zero
}

void updateCamera(CAMERA* camera, player* joueur, MAP* map) {
    // Défilement à droite
    if (joueur->mouveDroite && joueur->playerX > camera->cameraX + (LARGEUR_ECRAN / 2)) {
        camera->cameraX += joueur->vx;
        if (camera->cameraX > (map->map_width - VIEW_WIDTH) * TILE_SIZE) {
            camera->cameraX = (map->map_width - VIEW_WIDTH) * TILE_SIZE;
        }
    }
    
    // Défilement à gauche
    if (joueur->mouveGauche && joueur->playerX < camera->cameraX + (LARGEUR_ECRAN / 3)) {
        camera->cameraX -= PLAYER_SPEED;
        if (camera->cameraX < 0) {
            camera->cameraX = 0;
        }
    }

    // Empêcher la caméra de sortir des limites de la carte
    if (camera->cameraX < 0) {
        camera->cameraX = 0;
    }
    if (camera->cameraX > (map->map_width - VIEW_WIDTH) * TILE_SIZE) {
        camera->cameraX = (map->map_width - VIEW_WIDTH) * TILE_SIZE;
    }
}
//------------------------------------------------------------------
