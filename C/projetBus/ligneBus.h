#ifndef LIGNEBUS_H_INCLUDED
#define LIGNEBUS_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

Tbus creeBus( int idBus, TlisteStation start );
Tstation *creeArret( int posX, int posY, char* nomStation, int idStation);
Tstation *creeTroncon( int idLigneBus, Tstation* depart, Tstation *arrivee, int coutTemps, int coutDistance);

void afficheConsoleLigneBus( TlisteStation l);

TlisteStation getNextStation( TlisteStation l);
TlisteStation getNextTroncon( TlisteStation l);
TlisteStation getPreviousStation( TlisteStation l);
bool ligneBusVide( TlisteStation l);

int getPosXListeStation( TlisteStation myStationInListe );
int getPosYListeStation( TlisteStation myStationInListe );

int getMaxIdStation(TligneBus *l);
int getNewIdStation(Treseau *r);
int getNextIdLigne(Treseau *r);

void busSurStation( Tbus myBus, TlisteStation myStation, TsensParcours sens);
void busSurLigneX( Tbus myBus, int idLigneX );
TlisteStation stationSuivantePourLeBus(Tbus myBus);

void afficheCoordonneesBus( Tbus myBus );

// ****   Lister ci-dessous vos fonctions  ****

int lerp(int valDep, int valArr, float *t); // permet de calculer la position entre 2 points selon un coefficient donné
//renseigne incX et incY pour le d�placement du sprite dans le main, ET modifie la position du bus qd il atteint les coord X Y de la station d'arriv�e
void deplaceBus(Tbus myBus, TsensParcours sens_deplacement, float deltaTime, float *t, Treseau *r);

//operations sur les lignes
void creerLigneDeDeuxLignes(Treseau *r, TligneBus *a, TligneBus *b);// Cree une nouvelle ligne a partir de deux lignes déjà existantes

void addCorresp(Tstation* s);// Incrémente le nombre de correspondance d'une station

void removeCorresp(Tstation* s); //décrémente le nombre de correspondance d'une station

bool surUneLigneAuMoins(Tstation* s); // renvoie true si une station appartient à au moins une ligne

void stationSupprDeLigne(Tstation *s); //Enleve une correspondance à une station. Si la station n'est plus sur aucune ligne elle est supprimée et désalouée

void removeStationLigneBus(TligneBus *l, int num); //Supprime une station d'une ligne de bus

void rendreCirculaire(TligneBus* l); //Relie le terminus d'une ligne à son départ afin de la rendre circulaire

//reseau
void initReseau(Treseau **r, int size); //Initialise un réseau de bus. Il sera stocké dans un tableau qui double de taille si la taille limite est dépassée
void addLigneBus(Treseau *r, TligneBus *l); // ajoute une ligne au réseau de bus
void creeLigneBus(char *nom, TlisteStation listeStation, int id, Treseau *r); // cree une ligne de bus et l'ajoute au réseau
TligneBus *getLigneBus(Treseau *r, int id); //Renvoie la ligne de bus avec l'id demandé

//bus tab
Tbus* creeBusPourChaqueLigne(Treseau* r, int *size); //renvoie un tableau de bus avec un bus sur chaque ligne
Tbus *creeNbBus(Treseau* r, int size); //Cree un tableau de n bus avec les bus sur les premieres lignes: bus 1 sur ligne 1, bus 2 sur ligne 2, etc...
Tbus getNthBus(Tbus* bus, int num); //renvoie le n-ième bus dans le réseau;

void floatTabToZero(float *tab, int size);//Prend un tableau de float et met chaque élément a 0

//Free
void freeStation(Tstation* station);
void freeTlisteStation(TlisteStation l);
void freeLigneBus(TligneBus* l);
void freeReseau(Treseau *r);

void freeBus(Tbus bus);
void freeBusTab(Tbus* busTab, int size);

#endif // LIGNEBUS_H_INCLUDED
