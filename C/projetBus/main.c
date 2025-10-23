//BORDAS NOE
//NEUPONT THOMAS

#include "SDL.h"
#include "maSDL.h"
#include "SDL_VSYNC.h"

//#include "types.h"
#include "ligneBus.h"
#include "makerBuilder.h"
#include "listeSort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    //Random time init
    srand(time(NULL));

    //SDL
    //f�netre dans windows
    SDL_Window *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    //la texture (charg�e dans la ram de la carte graphique) target representant tout le jeu
    SDL_Renderer* gRenderer = NULL;

    //Les textures, le type Ltexture est d�fini dans SDL_VSYNC.h
    LTexture gSpriteBus;
    LTexture gSpriteArretBus;

    //Start up SDL and create window
	if( !init(&gWindow,&gRenderer) )  //initialise la fenetre SDL et charge UNE texture
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadAnimation(&gSpriteBus, gRenderer, "./data/4bus.png")
            || !loadSprite(&gSpriteArretBus, gRenderer, "./data/arret_bus_50x27.png"))
        {
			fprintf(stdout,"�chec de chargement du sprite (%s)\n",SDL_GetError());
		}
		else
		{
        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^
        //message("Welcome in BusProject","Ceci est un point de depart de votre future interface de vos lignes de Bus");
        //message("et fin","ECHAP->quitter, + vos touches + D/V pour sauvegarer/restaurer un bus et le reseau de lignes");
        message("Controles", "Fleches du haut et du bas pour changer la direction\nFleche de gauche et droite pour changer le premier bus de ligne\nA pour ajouter une ligne");

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
        /*                                                                    */
        /**********************************************************************/

        Treseau *r = buildReseauLigne();
        printf("########## Reseau Builded ##########\n      ---                   ---\n");

        /*
        creerLigneDeDeuxLignes(r, getLigneBus(r, 1), getLigneBus(r, 3));
        rendreCirculaire(getLigneBus(r, 7));
        removeStationLigneBus(getLigneBus(r, 7), 0);
        removeStationLigneBus(getLigneBus(r, 2), 1);
        */


        printf("Affichage des stations dans l'ordre decroissant des couts\n");
        triFusionListStation(getDepartListeStation(getLigneBus(r, 1)), coutMaintenanceAsupB, isTroncon);
        printf("\n---------------------------------------------\n");
        printf("Affichage des stations dans l'ordre croissant des dernieres maintenances\n");
        triFusionListStation(getDepartListeStation(getLigneBus(r, 2)), dateDerniereMaintenanceAinfB, isArret);
        printf("\n---------------------------------------------\n");


        //cr�ation d'un (seul) bus
        TligneBus *ligne = getNthLigne(r, 1);
        //Tbus bus1 = creeBus(1, getDepartListeStation(getNthLigne(r, 1)));

        int nbBus = 3;
        //Tbus* busTab = creeBusPourChaqueLigne(r, &nbBus);

        Tbus* busTab = creeNbBus(r, nbBus);

        //Current animation frame
        int frame = 0;

        //affiche et initialise le sprite du bus au d�part

        for(int i = 0; i < nbBus; i++){
            Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( getNthBus(busTab, i) ), getPosYBus( getNthBus(busTab, i) ), getIdFrame(frame));
        }


        // boucle principale du jeu
        SDL_Event event;
        int cont = 1;
        float deltaTime = 0.01;
        float *tabT = (float *)malloc(sizeof(float) * nbBus);

        int nthLigne = 1;


        while ( cont != 0 ){

                /***********************************************************************/
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE "JEU"
                /*                                                                     */
                /***********************************************************************/

                while (SDL_PollEvent(&event)) {

                        if (event.type == SDL_QUIT) {
                                cont = 0;
                        }

                        //les touches sont lues en Qwerty
                        if (event.type == SDL_KEYUP) {
                                if ( event.key.keysym.sym == SDLK_UP ){
                                        floatTabToZero(tabT, nbBus);
                                        printf("\nTouche UP, sens deplacement depart vers terminus\n");
                                        for(int i = 0; i < nbBus; i++){
                                            setSensParcours(getNthBus(busTab, i), depart_vers_arrivee );
                                        }

                                }
                                if ( event.key.keysym.sym == SDLK_DOWN ){
                                        floatTabToZero(tabT, nbBus);
                                        printf("\nTouche DOWN, sens deplacement terminus vers depart\n");
                                        for(int i = 0; i < nbBus; i++){
                                            setSensParcours(getNthBus(busTab, i), arrivee_vers_depart );
                                        }                                }
                                if ( event.key.keysym.sym == SDLK_a ) {
                                        printf("\nTouche A, Ajout d'une ligne au reseau\n");
                                        makeLigne(r);
                                }
                                if ( event.key.keysym.sym == SDLK_RIGHT ){
                                        *tabT = 0.;
                                        if (nthLigne < getNbLigne(r)) nthLigne++;
                                        else nthLigne = 1;

                                        ligne = getNthLigne(r, nthLigne);
                                        printf("\nTouche RIGHT, Bus au depart de la ligne %s\n", getNomLigne(ligne));
                                        busSurStation(getNthBus(busTab, 0), getDepartListeStation(ligne), depart_vers_arrivee);
                                        busSurLigneX(getNthBus(busTab, 0), getIdLigne(ligne));
                                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( getNthBus(busTab, 0) ), getPosYBus( getNthBus(busTab, 0) ), getIdFrame(frame));
                                }
                                if ( event.key.keysym.sym == SDLK_LEFT ) {
                                        *tabT = 0.;
                                        if (nthLigne > 1) nthLigne--;
                                        else nthLigne = getNbLigne(r);

                                        ligne = getNthLigne(r, nthLigne);
                                        printf("\nTouche LEFT, Bus au depart de la ligne %s\n", getNomLigne(ligne));
                                        busSurStation(getNthBus(busTab, 0), getDepartListeStation(ligne), depart_vers_arrivee);
                                        busSurLigneX(getNthBus(busTab, 0), getIdLigne(ligne));
                                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( getNthBus(busTab, 0) ), getPosYBus( getNthBus(busTab, 0) ), getIdFrame(frame));
                                }
                                if ( event.key.keysym.sym == SDLK_ESCAPE ){
                                        printf("\nTouche ECHAP");
                                        cont = 0;  //sortie de la boucle
                                }
                        }
                }

                //affichage du jeu � chaque tour

                //on efface toute la fen�tre
                efface_fenetre_texture(gRenderer);

                //D�placement de sprite du bus sur la texture
                for(int i = 0; i < nbBus; i++){
                    deplaceBus(getNthBus(busTab, i), getSensParcours(getNthBus(busTab, i)), deltaTime, tabT+i, r);
                    //Deplace_Sprite(&gSpriteBus, gRenderer, incXDeplSpriteBus1, incYDeplSpriteBus1, getIdFrame(frame));
                    Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus(getNthBus(busTab, i)), getPosYBus(getNthBus(busTab, i)), getIdFrame(frame));
                }

                //r�affichage � chaque tour de toutes les stations
                DessineAllLignes(r, gSpriteArretBus, gRenderer);

                //affichage de la texture ainsi mis � jour
                maj_fenetre_texture(gRenderer);

                SDL_Delay(1); //valeur du d�lai modifiable en fonction de votre CPU
                ++frame;
            }
        //fin boucle du jeu
        free(tabT);
        freeBusTab(busTab, nbBus);
        freeReseau(r);

        }
	}



	//Free resources and close SDL
	free_Ltexture(&gSpriteBus);
	free_Ltexture(&gSpriteArretBus);
	close(gWindow, gRenderer);

    return 0;
}
