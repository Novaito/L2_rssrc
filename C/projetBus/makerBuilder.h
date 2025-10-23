#ifndef MAKERBUILDER_H_INCLUDED
#define MAKERBUILDER_H_INCLUDED

#include <stdio.h>
#include "types.h"

//builder ligne
void makeLigne(Treseau *r); // Construit une ligne que l'on veut ajouter
bool isKeepBuilding(char *otherStation); // Verifie pour un ajout supplementaire d'un arret
Tstation *inputStation(int idStation); // Recupere les informations necessaire a la creation d'un arret

//builder fichier
void writeLignes(Treseau *r); // Reecrit toutes les lignes du reseau updated
void writeHeadersLigne(FILE * fp, TligneBus *l); // Ecrit l'entete de la ligne : id, nb de station et nom
void writeStations(FILE * fp, TlisteStation station); // Ecrit toutes les stations de la ligne

//reader
void readStations(FILE * fp, Tstation *tabStation, int idLigne, int nbStation); // Lis toutes les stations d'une ligne pour l'inserer dans tabStation
TlisteStation readLigneBus(FILE * fp, char *nomLigne);     // Renvoie une seule ligne dans la progression de la lecture du fichier data
Treseau *buildReseauLigne();          // Renvoie un tableau de lignes



#endif // MAKERBUILDER_H_INCLUDED
