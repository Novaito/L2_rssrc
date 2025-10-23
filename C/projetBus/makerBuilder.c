#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "makerBuilder.h"
#include "ligneBus.h"
#include "listeDouble.h"

/* Thomas */

//builder
Tstation *inputStation(int idStation) {
    int posX, posY, c;

    char nomStation[52];
    nomStation[0] = '\n'; // A la lecture initiale le \n n'est pas ignore et donne son incidence sur les autres fscanf, donc on le rajoute ici
    nomStation[1] = '\0';

    printf("Entrez le nom de la station : ");
    scanf(" %50[^\n]", nomStation + 1);
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Entrez la position x : ");
    scanf("%d", &posX);
    printf("Entrez la position y : ");
    scanf("%d", &posY);
    while ((c = getchar()) != '\n' && c != EOF) { }

    return creeArret(posX, posY, nomStation, idStation);
}

bool isKeepBuilding(char *otherStation) {
    printf("Ajouter un arret ? (il est recommende d'ajouter au moins 2 arrets --- (y/n) --- : ");
    scanf("%s[^n]", otherStation);
    return (*otherStation == 'y');
}

void writeLignes(Treseau *r) {
    char *filename = "station_ligneDeBus.data";
    FILE * fp;
    fp = fopen(filename, "w");

    int nbLigne = getNbLigne(r);
    fprintf(fp, "--%d\n", nbLigne);
    for (int i = 1; i <= nbLigne; i++) {
        writeHeadersLigne(fp, getNthLigne(r, i));
        writeStations(fp, getDepartListeStation(getNthLigne(r, i)));
        fprintf(fp, "::%d\n", getIdLigne(getNthLigne(r, i)));
    }
    fclose(fp);
}

void writeHeadersLigne(FILE * fp, TligneBus *l) {
    int nbStations = getNbStations(getDepartListeStation(l));
    fprintf(fp, "%d:%d", getIdLigne(l), nbStations);
    fprintf(fp, "%s;\n", getNomLigne(l));
}

void writeStations(FILE * fp, TlisteStation station) {
    TlisteStation st = station;
    while (!(listeVide(st))) {
        if (!isTroncon(getPtrData(st))) {
            fprintf(fp, "&\n%d;", getIdStation(getPtrData(st)));
            fprintf(fp, "%s;\n", getNomStation(getPtrData(st)));
            fprintf(fp, "%d %d;\n", getPosXStation(getPtrData(st)), getPosYStation(getPtrData(st)));
        }
        st = getNextCell(st);
    }
}

void makeLigne(Treseau *r) {
    // Penser � trier la liste !!
    TlisteStation newLigne;

    initListe(&newLigne);

    int dst;
    int idLigne = getNextIdLigne(r);
    int c;

    char *nomLigne = (char *)malloc(sizeof(char) * 7);
    nomLigne[0] = '\n';
    nomLigne[1] = '\0';
    printf("\n --> Entrez le nom de la ligne : ");
    scanf(" %5[^\n]", nomLigne + 1); // Il faut decaler l'indice
    while ((c = getchar()) != '\n' && c != EOF) { } // Ignorer le \n pour eviter les autres scanf le recupere

    int idStation = getNewIdStation(r);
    char *otherStation = (char *)malloc(sizeof(char)); // y/n pour continuer ou arreter

    Tstation *firstStation;
    firstStation = inputStation(idStation);
    newLigne = ajoutEnTete(newLigne, firstStation);

    while (isKeepBuilding(otherStation)) {
        Tstation *arr;
        Tstation *lastStation = getPtrData(getptrLastCell(newLigne));
        Tstation *troncon = (Tstation *)malloc(sizeof(Tstation));

        idStation++;
        arr = inputStation(idStation);
        dst = getDistStations(lastStation, arr);
        troncon = creeTroncon(idLigne, lastStation, arr, dst, dst);
        newLigne = ajoutEnFin(newLigne, troncon);
        newLigne = ajoutEnFin(newLigne, arr);
    }
    creeLigneBus(nomLigne, newLigne, idLigne, r);
    writeLignes(r);

    free(otherStation);
    free(nomLigne);
}

//reader
void readStations(FILE * fp, Tstation *tabStation, int idLigne, int nbStation) {
    int index = nbStation-1; // Bout du tableau pour pouvoir construire la liste de la station en 0(1)
    char *line = (char *)malloc(sizeof(char) * 8);
    char *nomStation = (char *)malloc(sizeof(char) * 50);
    int posX, posY, idStation;

    fscanf(fp, "%s", line);
    while (*line == '&') {
        fscanf(fp, "%d;", &idStation);
        fscanf(fp, "%[^;];", nomStation);
        fscanf(fp, "%d %d;", &posX, &posY);
        Tstation *station = creeArret(posX, posY, nomStation, idStation);
        tabStation[index] = *station;
        index--;

        fscanf(fp, "%s", line);
        if (*line != '&') {
            break;
        }
    }
    free(line);
    free(nomStation);
}

TlisteStation readLigneBus(FILE * fp, char *nomLigne) {
    TlisteStation newLigne;
    initListe(&newLigne);
    Tstation *firstStation = (Tstation *)malloc(sizeof(Tstation));

    int idLigne, nbStation, dst;
    char *idLigneRead = (char *)malloc(sizeof(char) * 2);
    char *nbStationRead = (char *)malloc(sizeof(char) * 2);
    fscanf(fp, "%[^:]:%s", idLigneRead, nbStationRead);
    fscanf(fp, "%[^;];", nomLigne);
    idLigne = strtol(idLigneRead, NULL, 10);
    nbStation = strtol(nbStationRead, NULL, 10);
    Tstation *tabStation = (Tstation *)malloc(sizeof(Tstation) * nbStation);
    readStations(fp, tabStation, idLigne, nbStation);

    *firstStation = tabStation[0];
    newLigne = ajoutEnTete(newLigne, firstStation);
    for (int i=1; i<nbStation; i++) {
        Tstation *dep = (Tstation *)malloc(sizeof(Tstation));
        Tstation *arr = (Tstation *)malloc(sizeof(Tstation));
        Tstation *troncon = (Tstation *)malloc(sizeof(Tstation));

        *arr = tabStation[i-1];
        *dep = tabStation[i];
        dst = getDistStations(dep, arr);
        troncon = creeTroncon(idLigne, dep, arr, dst, dst);
        newLigne = ajoutEnTete(newLigne, troncon);     // on peut ajouter en t�te et donc rendre
        newLigne = ajoutEnTete(newLigne, dep);        // la complexit� en O(1)
    }

    free(idLigneRead);
    free(nbStationRead);
    free(tabStation);
    return newLigne;
}

Treseau *buildReseauLigne() {
    Treseau *r;
    char *filename = "station_ligneDeBus.data";
    char *nomLigne = (char *)malloc(sizeof(char) * 6);

    int nbLigne;
    FILE * fp;
    fp = fopen(filename, "r");
    fscanf(fp, "--%d", &nbLigne);
    if (fp == NULL) {
        printf("Error : Loading file unsuccessful.");
        exit(EXIT_FAILURE);
    }

    initReseau(&r, nbLigne);

    TlisteStation newLigne;
    int i = 0;
    while (!feof(fp)) {
        initListe(&newLigne);
        newLigne = readLigneBus(fp, nomLigne);
        creeLigneBus(nomLigne, newLigne, getIdLigneTroncon(getPtrData(getNextCell(newLigne))), r);

        i++;
        if (i == nbLigne) {
            fscanf(fp, "%s", nomLigne); // Un retour chariot est fait automatiquement s'il y en a pas avant la fin du fichier
        }

    }

    free(nomLigne);

    fclose(fp);
    return r;
}
