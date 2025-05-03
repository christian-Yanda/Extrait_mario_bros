#include "entetes/entete_generale.h"
#include "entetes/joueur.h"

int main (int argc , char** argv)
{
    // variables
    SDL_Window* window = NULL; // pour la fenetre
    SDL_Renderer* renderer = NULL; // pour le rendu
    int exitGame = 1;// controle booucle du programme
    SDL_Event event; // controle des evenement la gestion des evenement
    player* joueur = initPlayer(50, HAUTEUR_ECRAN - 6 - (32*3), TILE_SIZE, TILE_SIZE); // initialisation du personnga
    MAP* map = malloc(sizeof(MAP));
    CAMERA camera ; // cette variable gere la camera du jeu

        // initialisation de la camera du jeu
        initCamera(&camera.cameraX, &camera.cameraY);
        printf("cameraX : %d et cameraY : %d", camera.cameraX, camera.cameraY);
   
    // initialisation de la sdl et creation de la fenetre et de son rendu
        if (initialistaion(&window,&renderer) !=0)
            goto debut;
 
    // chargement du fichier de niveau
    if (!loadMap("src/niveaux/niveau_1.txt", map)) {
        return 1;
    }

    printf("\n"); // SAUT DE LIGNE
    printf("\n");

    /*.
      AFFICHAGE DE LA MATRICE DE TUILES 
    for (int y = 0; y < map->map_height; y++) {
        for (int x = 0; x < map->map_width; x++) {
            printf("%d ", map->matrice_tuile[y * map->map_width + x]);
        }
        printf("\n");
    } */
 
 // Boucle principale du jeu
 while (exitGame) {

   updateEvent(&exitGame, joueur);
   updatePlayer(joueur, renderer, map, &camera);
   updateCamera(&camera, joueur,map);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderMap(renderer, map, &camera);
    drawPlayer(renderer,joueur,&camera);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}
 
debut:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    freeWord(map);
 
    return 0;
} 