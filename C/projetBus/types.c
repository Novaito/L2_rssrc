#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "listeDouble.h"

#define COUT_MIN 10
#define COUT_MAX 100

void afficheStation( Tstation *station){
    if (station == NULL){
        printf("\nerreur station non allou�e!\n");
    }
    else{
        if (station->arret_ou_troncon == ARRET){
            printf("\nSTATION idStation: %d, Station : %s, posX = %d, posY = %d, coutMaint = %d, dateDerMaint = ", station->idStation, station->nomStation, station->posX, station->posY, station->coutMaintenance);
            printDate(station->dateDerniereMaintenance);
        }
        else{ //alors le noeud est un tron�on
            printf("\n\nTRONCON idLigneBus: %d, temps: %d sec, distance a parcourir: %d metres, coutMaint = %d, dateDerMaint = ", station->idLigneBus, station->coutTemps, station->coutDistance, station->coutMaintenance);
            printDate(station->dateDerniereMaintenance);
            afficheStation(station->depart);
            afficheStation(station->arrivee);
            printf("\nfin tron�on\n");
        }
    }
}

void afficheStations(TlisteStation stations) {
    TlisteStation st = stations;
    while (!(listeVide(st))) {
        afficheStation(getPtrData(st));
        st = getNextCell(st);
    }
}

void printDate(t_date *d){
    printf("%d/%d/%d", getDay(d), getMonth(d), getYear(d));
}

void printTab(Tstation *tabStation, int nbStation) {
    Tstation *station = (Tstation *)malloc(sizeof(Tstation));
    for (int i=0; i<nbStation; i++) {
        *station = tabStation[i];
        afficheStation(station);
    }
    free(station);
}

//init
/* Thomas */
void initDerniereMaintenance(Tstation *myStation) {
    myStation->dateDerniereMaintenance = (t_date *)malloc(sizeof(t_date));
    int rand_month = (rand() % 12 + 1);
    int rand_year = (rand() % (2025 - 1999 + 1) + 1999);
    int day = getDayInMonth(rand_month, rand_year);
    day = rand() % day + 1;
    setDerniereMaintenance(myStation, day, rand_month, rand_year);
}

/* Thomas */
void initCoutMaintenance(Tstation *myStation) {
    setCoutMaintenance(myStation, (rand() % (COUT_MAX - COUT_MIN + 1) + COUT_MIN));
}

//Comparaison
/* Thomas */
bool isBissextile(int y) {
    return ((y%4 == 0) && !(y%100 == 0));
}

bool coutMaintenanceAsupB(Tstation *a, Tstation *b){
    return getCoutMaintenance(a) > getCoutMaintenance(b);
}

bool dateDerniereMaintenanceAinfB(Tstation *a, Tstation *b){
    if(getYear(getDerniereMaintenance(a)) != getYear(getDerniereMaintenance(b))){
        return getYear(getDerniereMaintenance(a)) < getYear(getDerniereMaintenance(b));
    }
    if(getMonth(getDerniereMaintenance(a)) != getMonth(getDerniereMaintenance(b))){
        return getMonth(getDerniereMaintenance(a)) < getMonth(getDerniereMaintenance(b));
    }
    return getDay(getDerniereMaintenance(a)) < getDay(getDerniereMaintenance(b));

}

bool isGreaterThan(int a, int b) {
    return (a > b);
}

// Getteurs

int getIdStation( Tstation *myStation){
    return myStation->idStation;
}

char *getNomStation( Tstation *myStation){
    return myStation->nomStation;
}

int getPosXStation( Tstation *myStation ){
    return myStation->posX;
}
int getPosYStation( Tstation *myStation ){
    return myStation->posY;
}

int getIdLigneTroncon(Tstation *myStation){
    //une station n'est pas li�e � une ligne, seulement le troncon
    if (getTypeNoeud(myStation)==TRONCON)
        return myStation->idLigneBus;
    else{
        printf("\n(getIdLigneTroncon) Erreur algo, vous n etes pas sur un troncon");
        return -1;
    }
}

TypeNoeud getTypeNoeud(Tstation *myStation){
    return myStation->arret_ou_troncon;
}

int getCoutMaintenance(Tstation *myStation) {
    return myStation->coutMaintenance;
}

t_date *getDerniereMaintenance(Tstation *myStation) {
    return myStation->dateDerniereMaintenance;
}

int getNbStations(TlisteStation stations) {
    int count = 0;
    TlisteStation st = stations;
    while (!listeVide(st)) {
        if (isArret(getPtrData(st))) {
            count++;
        }
        st = getNextCell(st);
    }
    return count;
}

/* Thomas */
int getDayInMonth(int m, int y) {
    switch (m) {
        case 1:
            return 31;
        case 2:
            if (isBissextile(y)) {
                return 29;
            } else {
                return 28;
            }
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
    }
    return -1;
}

day getDay(t_date *date) {
    return date->d;
}

month getMonth(t_date *date) {
    return date->m;
}

int getYear(t_date *date) {
    return date->y;
}

int getPosXBus( Tbus myBus ){
    return myBus->posXBus;
}
int getPosYBus( Tbus myBus ){
    return myBus->posYBus;
}
int getIdBus( Tbus myBus ){
    return myBus->idBus;
}
int getIdLigneActuelleDuBus( Tbus myBus ){
    return myBus->idLigneBusActuelle;
}

int getIdLigneBus(Tbus myBus){
    return myBus->idLigneBusActuelle;
}

int getNbTour(Tbus myBus){
    return myBus->nbTour;
}

TligneBus **getTabOfLigne(Treseau *r){
    return r->tabOfLigne;
}

TligneBus *getNthLigne(Treseau *r, int nth) {
    return getTabOfLigne(r)[nth-1];
}

int getNbLigne(Treseau *r){
    return r->size;
}

int getMaxSizeTabOfLigne(Treseau *r){
    return r->maxSize;
}

int getIdLigne(TligneBus *l){
    return l->idLigneBus;
}

char *getNomLigne(TligneBus *l) {
    return l->nomLigne;
}

TsensParcours getSensParcours(Tbus myBus){
    return myBus->sensParcours;
}

int getDistStations(Tstation *srcStation, Tstation *dstStation) {
    int srcX = getPosXStation(srcStation);
    int srcY = getPosYStation(srcStation);
    int dstX = getPosXStation(dstStation);
    int dstY = getPosYStation(dstStation);
    return sqrt((dstX - srcX)*(dstX - srcX) + (dstY - srcY)*(dstY - srcY));
}

TlisteStation getDepartListeStation(TligneBus *l){
    return l->depart;
}

TlisteStation getArriveeListeStation(TligneBus *l){
    return l->arrivee;
}

TlisteStation getActualStation( Tbus myBus ){
    return myBus->positionSurLaLigneDeBus;
}

// Setteurs

void setActualStation( Tbus myBus, TlisteStation arrivalStation ){
    myBus->positionSurLaLigneDeBus = arrivalStation;
}

void setPosXBus(Tbus myBus, int newX){
    myBus->posXBus = newX;
}

void setPosYBus(Tbus myBus, int newY){
    myBus->posYBus = newY;
}

void setIdLigneBus(Tbus myBus, int idLigne){
    myBus->idLigneBusActuelle = idLigne;
}

void setSensParcours(Tbus myBus, TsensParcours sens ){
    myBus->sensParcours = sens;
}

void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation){
    myBus->positionSurLaLigneDeBus = myStation;
}

void setNbTour(Tbus myBus, int nb){
    myBus->nbTour = nb;
}

/* Thomas */
void setCoutMaintenance(Tstation *myStation, int cout) {
    if (cout >= COUT_MIN && cout <= COUT_MAX) {
        myStation->coutMaintenance = cout;
    }
}

/* Thomas */
void setDerniereMaintenance(Tstation *myStation, int d, int m, int y) {
    if (m >= 1 && m <= 12) {
        int d_temp = getDayInMonth(m, y);
        if (d >= 1 && d <= d_temp) {
            myStation->dateDerniereMaintenance->d = d;
        } else {
            printf("WARNING : %d n'est pas valide, %d est mis par defaut !", d, d_temp);
            myStation->dateDerniereMaintenance->d = d_temp;
        }
        myStation->dateDerniereMaintenance->m = m;
    } else {
        printf("ERREUR : setting derniereMaintenance");
    }
    myStation->dateDerniereMaintenance->y = y;
}

void setTabOfLigne(Treseau *r, TligneBus **tab){
    r->tabOfLigne = tab;
}

void setNbLigne(Treseau *r, int size){
    r->size = size;
}

void setMaxSizeTabOfLigne(Treseau *r, int maxSize){
    r->maxSize = maxSize;
}

void setDepartListeStation(TligneBus *l, TlisteStation depart){
    l->depart = depart;
}
void setArriveeListeStation(TligneBus *l, TlisteStation arrivee){
    l->arrivee = arrivee;
}


//Filtres

bool isReseauVide(Treseau *r) {
    return (r->size == 0);
}

bool isTroncon(Tstation* station){
    return getTypeNoeud(station) == TRONCON;
}

bool isArret(Tstation* station){
    return getTypeNoeud(station) == ARRET;
}

bool isArretOrTroncon(Tstation* station){
    return isTroncon(station) || isArret(station);
}

