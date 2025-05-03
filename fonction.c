#include "entetes/entete_generale.h"
#include "entetes/joueur.h"


/** Initialisation SDL
creation de la fenetre */
int initialistaion (SDL_Window** window, SDL_Renderer** renderer)
{
    // Initialisation du systeme video de la SDL
    if ( 0 !=  SDL_Init(SDL_INIT_VIDEO))// test si initialisation a reussi
    {
        fprintf(stderr, "Erreur SDL_Init: %s", SDL_GetError());
        return -1;
    }
                            
    // Creation de la fenetre et du rendu de la fenetre
    // test si creation de la fenetre et du rendu a reussi
    if ( 0 != SDL_CreateWindowAndRenderer(LARGEUR_ECRAN,HAUTEUR_ECRAN, SDL_WINDOW_RESIZABLE,window, renderer))
    {
        fprintf(stderr,"Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }                     
    return 0;
}

/** FONCTION DE LECTURE DU FICHIER DU FICHIER DE NIVEAU **/
int loadMap(const char *filename , MAP* map) {

    FILE *file = fopen(filename, "r");
    // verification si le fichier de niveau n'a pas pu etre ouvert ouvert
    if (!file) {
    printf("Erreur: Impossible d'ouvrir le fichier de carte.\n");
        return 0;
    }
    
    // LECTURE TAILLE DE LA MATRICE DE LA MAP ( LARGEUR ET HAUTEUR DE LA MAP)
    // ET TEST SI LA TAILLE DE LA MATRICE A PU ETRE RECUPEREE
    if ( fscanf(file, "%d %d",&map->map_width,&map->map_height) != 2){
        fprintf(stderr, "Erreur lecture des dimensions");
        return 0;
    }
    
    printf("\n"); // SAUT DE LIGNE
    printf(" widht : %d et height : %d", map->map_width, map->map_height);
    
    // LECTURE DE LA MATRICE DES TUILES
    map->matrice_tuile = (int*) malloc(map->map_width * map->map_height * sizeof(int) ); // allocation pour les valeurs de chaque tiles 
    map->recTile = malloc (sizeof(SDL_Rect) * map->map_width * map->map_height); // allocation pour les rectangle des tiles
    
    for (int y = 0 ; y < map->map_height; y++){
        for (int x  = 0; x < map->map_width; x++){
            if ( fscanf(file, "%d", &map->matrice_tuile[ y * map->map_width + x]) != 1){
                fprintf(stderr, "Erreur lecture niveauf");
            }
            else{
                map->recTile[ y * map->map_width + x].x = x * TILE_SIZE;
                map->recTile[ y * map->map_width + x].y = y * TILE_SIZE;
                map->recTile[ y * map->map_width + x].h = TILE_SIZE;
                map->recTile[ y * map->map_width + x].w = TILE_SIZE; 
            }
        }
    }

    fclose(file);
    return 1;
}


// recuperation du tile
int getTile(MAP* map, int x, int y){
    return map->matrice_tuile [y* map->map_width + x];
}
// liberation des tiles
void freeWord (MAP* map)
{
    free(map->matrice_tuile);
    free(map);
}

// AFFICHAGE DE TUILES 
void renderMap(SDL_Renderer* renderer, MAP* map, CAMERA* camera) {
    for (int y = 0; y < VIEW_HEIGHT; y++) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            int tileX = x + camera->cameraX / TILE_SIZE;
            if (tileX < map->map_width) {
                if ( getTile(map, tileX, y) != 0){
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderDrawRect(renderer, &map->recTile[ y * map->map_width + x]);
                }  
            }                             
        }
    }
    // Rectangle rouge pour visualiser la zone de scrolling
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect scrollRect = {LARGEUR_ECRAN / 4, 0, LARGEUR_ECRAN / 2, HAUTEUR_ECRAN};
    SDL_RenderDrawRect(renderer, &scrollRect); 
}

// Gestion des evenements
/*
    cette fonction gerer les evenements lies aux entrees du joueur
    ( chaque appui sur une touche specifique du clavier decleche un certain comportement du personnge et de son environnement)
*/
void updateEvent(int* exitGame, player* joueur) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    *exitGame = 0;
                }
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    joueur->mouveDroite = true;
                    joueur->vx = PLAYER_SPEED; // Utiliser une vitesse constante
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    joueur->mouveGauche = true;
                    joueur->vx = -PLAYER_SPEED; // Vitesse négative pour aller à gauche
                }
                if (event.key.keysym.sym == SDLK_SPACE && !joueur->isJump) {
                    joueur->isJump = true;
                    jump(joueur);
                }
                break;

            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    joueur->mouveDroite = false;
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    joueur->mouveGauche = false;
                }
                break;
        }
    }
}