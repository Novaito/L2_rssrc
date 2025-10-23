#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "ligneBus.h"
#include "listeDouble.h"

void initReseau(Treseau **r, int size) {
    *r = (Treseau *)malloc(sizeof(Treseau));
    (*r)->tabOfLigne = (TligneBus **)malloc(sizeof(TligneBus *) * size);
    (*r)->size = 0;
    (*r)->maxSize = size;
}

Tbus creeBus( int idBus, TlisteStation start ){
    Tbus myBus = (Tbus)malloc(sizeof(Typebus));
    myBus->idBus = idBus;
    busSurStation( myBus, start, depart_vers_arrivee);
    busSurLigneX ( myBus, getIdLigneTroncon(getPtrData(getNextTroncon(start))));
    setNbTour(myBus, 0);
    return myBus;
}


Tstation *creeArret( int posX, int posY, char* nomStation, int idStation){
    Tstation* newStation = (Tstation*)malloc(sizeof(Tstation));

    newStation->arret_ou_troncon = ARRET;

    //champs utiles si ARRET
    newStation->posX = posX;
    newStation->posY = posY;
    strcpy(newStation->nomStation, nomStation);
    newStation->idStation = idStation;

    //champs non utiles si ARRET
    newStation->depart = NULL;
    newStation->arrivee = NULL;
    newStation->coutTemps = 0;
    newStation->coutDistance = 0;
    newStation->idLigneBus= -1;  //id inexistant
    newStation->nbCorrespondances = 0;
    initCoutMaintenance(newStation);
    initDerniereMaintenance(newStation);
    return newStation;
}

Tstation *creeTroncon(int idLigneBus, Tstation* depart, Tstation *arrivee, int coutTemps, int coutDistance){
    Tstation* newStation = (Tstation*)malloc(sizeof(Tstation));

    newStation->arret_ou_troncon = TRONCON;

    //champs non utiles si TRONCON
    newStation->posX = 0;
    newStation->posY = 0;
    strcpy(newStation->nomStation, "");
    newStation->idStation = -1;  //id inexistant

    //champs utiles si TRONCON
    newStation->idLigneBus=idLigneBus;
    newStation->depart = depart;
    newStation->arrivee = arrivee;
    newStation->coutTemps = coutTemps;
    newStation->coutDistance = coutDistance;
    initCoutMaintenance(newStation);
    initDerniereMaintenance(newStation);
    return newStation;
}

void afficheConsoleLigneBus( TlisteStation l){
    afficheListe(l);
}

TlisteStation getNextStation( TlisteStation l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                    if (ligneBusVide( getNextCell(l) )) return NULL;  //nous sommes sur un terminus
                    else return getNextCell( getNextCell( l ) );  //le prochain arret est dans 2 cellules dans la liste, la cellule suivaante �tant un TRONCON
            }
            else return getNextCell( l );  //si on est sur un TRONCON alors la prochaine cellule est la prochaine station (ARRET)
    }
}

TlisteStation getNextTroncon( TlisteStation l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                return getNextCell(l);  //la prochaine cellule est un TRONCON, peut �tre �gale � NULL si on est sur un terminus
            }
            else{
                    printf("\n(getNextTroncon) erreur algo, on est deja sur un troncon");
                    return l;  //on retourne le troncon actuel
            }
    }
}

TlisteStation getPreviousStation( TlisteStation l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                    if (ligneBusVide( getPrevCell(l) )) return NULL;  //nous sommes sur un terminus
                    return getPrevCell( getPrevCell( l ) );  //le prochain arret est dans 2 cellules dans la liste, la cellule suivaante �tant un TRONCON
            }
            else return getPrevCell( l );  //si on est sur un TRONCON alors la prochaine cellule est la prochaine station (ARRET)
    }
}

bool ligneBusVide( TlisteStation l){
    return listeVide( l );
}

int getPosXListeStation( TlisteStation myStationInListe ){
    return getPosXStation(getPtrData(myStationInListe));
}

int getPosYListeStation( TlisteStation myStationInListe ){
    return getPosYStation(getPtrData(myStationInListe));
}

int getMaxIdStation(TligneBus *l) {
    int id;
    TlisteStation ligne = getDepartListeStation(l);
    int max = getIdStation(getPtrData(ligne));
    while (!(listeVide(ligne))) {
        if (isArret(getPtrData(ligne))) {
            id = getIdStation(getPtrData(ligne));
            if (id > max) max = id;
        }
        ligne = getNextCell(ligne);
    }
    return max;
}

int getNewIdStation(Treseau *r) {
    int max;
    int newId = getMaxIdStation(getNthLigne(r, 1));
    printf("Nb lignes : %d", getNbLigne(r));
    for (int i=2; i <= getNbLigne(r); i++) {
        max = getMaxIdStation(getNthLigne(r, i));
        if (max > newId) newId = max;
    }
    return newId+1;
}

int getNextIdLigne(Treseau *r){
    if(getNbLigne(r) == 0){
        return 0;
    }
    return getIdLigne(getTabOfLigne(r)[getNbLigne(r) - 1]) + 1;
}

void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation);


void busSurStation( Tbus myBus, TlisteStation myStation, TsensParcours sens){

    //Exemple encapsulation: on a pr�f�r� les fonctions setteurs � un acc�s direct aux champs

    setPositionSurLaLigneDeBus( myBus, myStation);
    //myBus->positionSurLaLigneDeBus = myStation;  //interdit

    setSensParcours( myBus, sens);
    //myBus->sensParcours = sens;

    setPosXBus( myBus, getPosXListeStation( myStation ) );
    //myBus->posXBus = getPosXListeStation( myStation );

    setPosYBus( myBus, getPosYListeStation( myStation ) );
    //myBus->posYBus = getPosYListeStation( myStation );

    //idem : on passe ci-dessous par les getteurs et non par un acc�s direct via les champs
    printf("\nBus id%d est en (x = %d, y = %d) sur la ligne %d, station %s", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(myStation)));
}

void busSurLigneX( Tbus myBus, int idLigneX ){
    setIdLigneBus(myBus, idLigneX);
    setNbTour(myBus, 0);
}

TlisteStation stationSuivantePourLeBus(Tbus myBus){
    TlisteStation prochaineStation;
    if (getSensParcours(myBus)==depart_vers_arrivee) prochaineStation = getNextStation(getActualStation(myBus));
    else prochaineStation = getPreviousStation(getActualStation(myBus));
    return prochaineStation;
}

void afficheCoordonneesBus( Tbus myBus ){
    char *nomProchaineStation;
    TlisteStation prochaineStation = stationSuivantePourLeBus(myBus);

    if (ligneBusVide(prochaineStation)) printf("\nBus id: %d est en (x = %d, y = %d) ligne %d, derniere station %s (Terminus)", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(getActualStation(myBus))));
    else {
            nomProchaineStation = getNomStation(getPtrData(prochaineStation));
            printf("\nBus id: %d est en (x = %d, y = %d) ligne %d, derniere station %s, prochaine station %s", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(getActualStation(myBus))), nomProchaineStation);
    }
}


//Cr�er ci-dessous vos fonctions

/* Thomas */
int lerp(int valDep, int valArr, float *t) {
    return (1 - *t) * valDep + (*t * valArr);
}

/* Thomas */
void deplaceBus(Tbus myBus, TsensParcours sens_deplacement, float deltaTime, float *t, Treseau* r) {
    TlisteStation dest;
    int xdep, ydep, xarr, yarr, newPosX, newPosY;
    if (sens_deplacement == depart_vers_arrivee) dest = getNextStation(getActualStation(myBus));
    else{
        if(sens_deplacement == arrivee_vers_depart){
            dest = getPreviousStation(getActualStation(myBus));
        }else{
            return;
        }
    }

    if (ligneBusVide(dest)) {
        *t = 0.;
        //printf("\nBus id%d est au terminus de la ligne %d sur la station id=%d %s", getIdBus(myBus), getIdLigneActuelleDuBus(myBus),getIdStation(getPtrData(getActualStation(myBus))),getNomStation(getPtrData(getActualStation(myBus))));
    } else {
        xdep = getPosXStation(getPtrData(getActualStation(myBus)));
        ydep = getPosYStation(getPtrData(getActualStation(myBus)));
        xarr = getPosXListeStation(dest);
        yarr = getPosYListeStation(dest);

        if (*t >= 1.) {
            *t = 0.;
            setActualStation(myBus, dest);
            TligneBus* ligne = getLigneBus(r, getIdLigneActuelleDuBus(myBus));
            if(getDepartListeStation(ligne) == getArriveeListeStation(ligne) && getDepartListeStation(ligne) == dest){
                setNbTour(myBus, getNbTour(myBus) + 1);
                printf("\nLe bus a effectue sa boucle numero %d\n", getNbTour(myBus));
                setSensParcours(myBus, stopped);
            }
            printf("\nLe Bus id%d arrive sur la station id%d %s",getIdBus(myBus),getIdStation(getPtrData(getActualStation(myBus))),getNomStation(getPtrData(getActualStation(myBus))));
        } else {
            newPosX = lerp(xdep, xarr, t);
            newPosY = lerp(ydep, yarr, t);

            setPosXBus(myBus, newPosX);
            setPosYBus(myBus, newPosY);
        }
        *t += deltaTime; // incrémentation de t pour le deplacement du bus entre 2 arret
    }
}

//operations sur les lignes
void creerLigneDeDeuxLignes(Treseau *r, TligneBus *a, TligneBus *b){
    TlisteStation newLigne;
    initListe(&newLigne);

    int id = getNextIdLigne(r);

    TlisteStation currentB = getArriveeListeStation(b);

    newLigne = ajoutEnTete(newLigne, getPtrData(currentB));
    addCorresp(getPtrData(currentB));

    Tstation* startStation;
    Tstation* endStation;
    int dst;



    //Sur la ligne B
    while(!listeVide(getPrevCell(currentB))){

        startStation = getPtrData(getPrevCell(getPrevCell(currentB)));
        endStation = getPtrData(currentB);

        dst = getDistStations(startStation, endStation);

        newLigne = ajoutEnTete(newLigne, creeTroncon(id, startStation, endStation, dst, dst));

        newLigne = ajoutEnTete(newLigne, startStation);
        addCorresp(startStation);

        currentB = getPrevCell(getPrevCell(currentB));

    }

    //Jonction des deux lignes
    TlisteStation currentA = getArriveeListeStation(a);

    startStation = getPtrData(currentA);
    endStation = getPtrData(currentB);

    dst = getDistStations(startStation, endStation);

    newLigne = ajoutEnTete(newLigne, creeTroncon(id, startStation, endStation, dst, dst));

    newLigne = ajoutEnTete(newLigne, startStation);
    addCorresp(startStation);


    //La ligne A
    while(!listeVide(getPrevCell(currentA))){

        startStation = getPtrData(getPrevCell(getPrevCell(currentA)));
        endStation = getPtrData(currentA);

        dst = getDistStations(startStation, endStation);

        newLigne = ajoutEnTete(newLigne, creeTroncon(id, startStation, endStation, dst, dst));

        newLigne = ajoutEnTete(newLigne, startStation);
        addCorresp(startStation);

        currentA = getPrevCell(getPrevCell(currentA));

    }

    creeLigneBus("name", newLigne, id, r);
}

void addCorresp(Tstation* s){
    s->nbCorrespondances++;
}

void removeCorresp(Tstation* s){
    s->nbCorrespondances--;
}

bool surUneLigneAuMoins(Tstation* s){
    return s->nbCorrespondances > 0;
}

void stationSupprDeLigne(Tstation *s){
    if(s->arret_ou_troncon == TRONCON){
        freeStation(s);
    }else{
        if(!surUneLigneAuMoins(s)){
            freeStation(s);
        }
    }
}

void removeStationLigneBus(TligneBus *l, int num){
    int i = 0;
    bool end = false;
    bool estCirculaire = getDepartListeStation(l) == getArriveeListeStation(l);
    TlisteStation current = getDepartListeStation(l);

    //Cas ou l'on souhaite supprimer la première station
    if(num == 0 && !estCirculaire){

        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);
        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);

        setDepartListeStation(l, current);
        return;

    }

    if(estCirculaire){
        i =-1;
        current = getPrevCell(getPrevCell(current));
    }

    while(i < num-1 && !end){

        current = getNextCell(getNextCell(current));
        i++;

        if(listeVide(getNextCell(getNextCell(getNextCell(current))))){
            end = true;
        }
    }

    if(end){

        setArriveeListeStation(l, current);

        current = getNextCell(current);

        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);
        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);
        return;

    }else{

        current = getNextCell(current);
        bool changeDepArr = false;

        if(getArriveeListeStation(l) == getNextCell(current)){
            changeDepArr = true;
        }

        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);
        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);
        stationSupprDeLigne(getPtrData(current));
        current = suppEnTete(current);

        int dst = getDistStations(getPtrData(getPrevCell(current)), getPtrData(current));
        current = ajoutEnTete(current, creeTroncon(getIdLigne(l), getPtrData(getPrevCell(current)), getPtrData(current), dst, dst));

        if(changeDepArr){
            setDepartListeStation(l, getNextCell(current));
            setArriveeListeStation(l, getNextCell(current));
        }
    }
}


void rendreCirculaire(TligneBus* l){
    TlisteStation dep = getDepartListeStation(l);
    TlisteStation arr = getArriveeListeStation(l);

    if( dep != arr){
        int dst = getDistStations(getPtrData(arr), getPtrData(dep));
        TlisteStation temp = ajoutEnTete(dep, creeTroncon(getIdLigne(l), getPtrData(arr), getPtrData(dep), dst, dst));

        setNext(arr, temp);
        setPrev(temp, arr);

        setArriveeListeStation(l, dep);
    }
}


//fonctions du reseau
void addLigneBus(Treseau *r, TligneBus *l){

    if(getNbLigne(r) == getMaxSizeTabOfLigne(r)){
        setMaxSizeTabOfLigne(r, getMaxSizeTabOfLigne(r) * 2);
        TligneBus **newTab = (TligneBus **)malloc(sizeof(TligneBus *) * getMaxSizeTabOfLigne(r));

        for(int i = 0; i < getNbLigne(r); i++){
            newTab[i] = getTabOfLigne(r)[i];
        }

        free(getTabOfLigne(r));

        setTabOfLigne(r, newTab);
    }
    (getTabOfLigne(r))[getNbLigne(r)] = l;
    setNbLigne(r ,getNbLigne(r) + 1);
}

void creeLigneBus(char *nom, TlisteStation listeStation, int id, Treseau *r){
    TligneBus *ligneBus = (TligneBus *)malloc(sizeof(TligneBus));

    ligneBus->nomLigne = (char *)malloc(sizeof(char) * (strlen(nom) + 10));

    strcpy(ligneBus->nomLigne, nom);

    ligneBus->depart = listeStation;

    ligneBus->arrivee = getptrLastCell(listeStation);

    ligneBus->idLigneBus = id;

    addLigneBus(r, ligneBus);

}

TligneBus *getLigneBus(Treseau *r, int id){
    int min = 0;
    int max = getNbLigne(r);

    int moy = (max - min) / 2 + min;

    while(getIdLigne(getTabOfLigne(r)[moy]) != id ){

        if(getIdLigne(getTabOfLigne(r)[moy]) < id){
            min = moy;
        }else{
            max = moy;
        }

        moy = (max - min) / 2 + min;

    }

    return getTabOfLigne(r)[moy];

}

Tbus *creeBusPourChaqueLigne(Treseau* r, int *size){
    *size = getNbLigne(r);
    //*size = 2;
    Tbus* busTab = (Tbus*)malloc(sizeof(Tbus ) * (*size));
    for(int i = 0; i < *size; i++){
        busTab[i] = creeBus(i, getDepartListeStation(getNthLigne(r, i+1)));
    }
    return busTab;
}

Tbus *creeNbBus(Treseau* r, int size){
    Tbus* busTab = (Tbus*)malloc(sizeof(Tbus ) * (size));
    for(int i = 0; i < size; i++){
        busTab[i] = creeBus(i, getDepartListeStation(getNthLigne(r, i+1)));
    }
    return busTab;
}

Tbus getNthBus(Tbus* bus, int num){
    return bus[num];
}

void floatTabToZero(float *tab, int size){
    for(int i = 0;i < size; i++){
        tab[i] = 0.;
    }
}

//Free
void freeStation(Tstation* station){
    free(station->dateDerniereMaintenance);
    free(station);
}

void freeTlisteStation(TlisteStation l){

    TlisteStation current = l;

    while(!listeVide(getNextCell(current)) && getNextCell(current) != l){
        stationSupprDeLigne(getPtrData(current));
        current = getNextCell(current);
        unAllocCel(getPrevCell(current));
    }
    stationSupprDeLigne(getPtrData(current));
    unAllocCel(current);

}
void freeLigneBus(TligneBus* l){
    freeTlisteStation(getDepartListeStation(l));
    free(l);
}
void freeReseau(Treseau *r){
    for(int i = 0; i < getNbLigne(r); i++){
        freeLigneBus(getNthLigne(r, i+1));
    }
    free(r);
}

void freeBus(Tbus bus){
    free(bus);
}
void freeBusTab(Tbus* busTab, int size){
    for(int i = 0; i < size; i++){
        freeBus(busTab[i]);
    }
    free(busTab);
}
