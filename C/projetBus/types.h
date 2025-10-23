#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#include <stdbool.h>

typedef enum {janvier=1, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre} month;
typedef enum {lundi=1, mardi, mercredi, jeudi, vendredi, samedi, dimanche} day;
typedef struct {
    int y;
    month m;
    day d;
} t_date;

typedef enum type_noeud {ARRET, TRONCON} TypeNoeud;

typedef struct T_station { //repr�sente UN TRONCON (entre deux arr�ts) ou UN ARRET (cad une station de la ligne de bus)

    TypeNoeud arret_ou_troncon;

    //donn�es utiles si le Noeud est un TRONCON
    int idLigneBus;                    //num�ro de la ligne de bus par laquelle on arrive sur la station
    struct T_station* depart;          // pointeurs sur les stations de d�part et d'arriv�e du tron�on
    struct T_station* arrivee;
    int coutTemps;                     // co�t en temps de parcours (en secondes)
    int coutDistance;                  // co�t en distance (en m�tres)
    int tempsCumule, distanceCumule;   // champs utiles pour d�terminer le meilleur itin�raire

    //donn�es utiles si le Noeud est un ARRET
    int posX, posY;                    //coordonn�es sur le plan de la ville
    char nomStation[30];
    int idStation;                     //num�ro unique et non li�e � une ligne, une ligne de bus �tant constitu�e d'une suite de d'id stations: exemple : 3  - 7 - 1 - 5
    int nbCorrespondances;


    //champs utiles pour les tris
    int coutMaintenance;                //en Kilo euro, une valeur entre 10 et 100  (A VOUS DE GERER)
    t_date *dateDerniereMaintenance;      //t_date est � d�finir, doit permettre de stocker une date jour/mois/ann�e, y mettre une date al�atoire (A VOUS DE GERER)

    //struct T_station* correspondances; //�gale � NULL si pas de correspondance, sinon �gale � une liste de TRONCONS
    //int coutCumule;                    //pour le calcul du plus court chemin, algo de Djikstra

} Tstation;


//type pour la liste doublement chain�e, utilis� daans listeDouble.h/.c
typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    Tstation *pdata;              //attention � faire un malloc sur ce champ avant de s'en servir
} T_cellule;
typedef T_cellule* T_liste;


//Une liste de stations  (bas�e sur listeDouble.h/.c)
typedef T_liste TlisteStation;  //T_liste et TlisteStation sont �quivalents, cad pointeur sur Tcellule

//une ligne de bus
typedef struct{
    int idLigneBus;  //donn�e qui sera dupliqu�e dans chaque troncon de la ligne (pour aider au debugage et pour aider � la gestion des correspondances)
    char *nomLigne;
    TlisteStation depart;   //peut etre parcouru dans les deux sens
    TlisteStation arrivee;
} TligneBus;

typedef enum{ depart_vers_arrivee, arrivee_vers_depart, stopped} TsensParcours;

typedef struct{
    int idBus;
    TlisteStation positionSurLaLigneDeBus;  //la derniere station atteinte (dans la liste) du bus est dans le champ pdata, stock� dans un Tcellule
    int posXBus, posYBus;                   //coord du bus pixel par pixel pour les trajets
    int idLigneBusActuelle;                 //un bus suit une ligne de bus � un instant t et peut en changer
    TsensParcours sensParcours;
    int nbTour;
} Typebus;

typedef Typebus *Tbus;

// Le type Treseau qui permet de stocker toutes les lignes de bus
typedef struct{
    TligneBus **tabOfLigne;
    int size;
    int maxSize;
} Treseau;

//affichage
void afficheStation( Tstation *station );
void afficheStations(TlisteStation stations);
void printDate(t_date *d);
void printTab(Tstation *tabStation, int nbStation);

//init
void initDerniereMaintenance( Tstation *myStation);
void initCoutMaintenance( Tstation *myStation );

//Comparaison
bool isBissextile(int y);
bool coutMaintenanceAsupB(Tstation *a, Tstation *b);
bool dateDerniereMaintenanceAinfB(Tstation *a, Tstation *b);
bool isGreaterThan(int a, int b);

//Getteurs
int getIdStation( Tstation *myStation );
char *getNomStation( Tstation *myStation);
int getPosXStation( Tstation *myStation );
int getPosYStation( Tstation *myStation );
int getIdLigneTroncon(Tstation *myStation);
TypeNoeud getTypeNoeud(Tstation *myStation);
t_date *getDerniereMaintenance( Tstation *myStation );
int getCoutMaintenance( Tstation *myStation );
int getDistStations(Tstation *srcStation, Tstation *dstStation);
int getNbStations(TlisteStation stations);

int getDayInMonth( int m, int y );
day getDay(t_date *date);
month getMonth(t_date *date);
int getYear(t_date *date);

int getPosXBus( Tbus myBus );
int getPosYBus( Tbus myBus );
int getIdBus( Tbus myBus );
int getIdLigneActuelleDuBus( Tbus myBus );
TsensParcours getSensParcours(Tbus myBus);
TlisteStation getActualStation( Tbus myBus );
int getIdLigneBus(Tbus myBus);
int getNbTour(Tbus myBus);

TligneBus **getTabOfLigne(Treseau *r);
TligneBus *getNthLigne(Treseau *r, int nth);
int getNbLigne(Treseau *r);
int getMaxSizeTabOfLigne(Treseau *r);

int getIdLigne(TligneBus *l);
char *getNomLigne(TligneBus *l);


TlisteStation getDepartListeStation(TligneBus *l);
TlisteStation getArriveeListeStation(TligneBus *l);

//Setteurs
void setActualStation( Tbus myBus, TlisteStation arrivalStation );
void setPosXBus(Tbus myBus, int newX);
void setPosYBus(Tbus myBus, int newY);
void setIdLigneBus(Tbus myBus, int idLigne);
void setSensParcours(Tbus myBus, TsensParcours sens );
void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation);
void setNbTour(Tbus myBus, int nb);
void setCoutMaintenance(Tstation *myStation, int cout);
void setDerniereMaintenance(Tstation *myStation, int d, int m, int y);

void setNomLigne(TligneBus *l, char *nomLigne);
void setTabOfLigne(Treseau *r, TligneBus **tab);
void setNbLigne(Treseau *r, int size);
void setMaxSizeTabOfLigne(Treseau *r, int maxSize);

void setDepartListeStation(TligneBus *l, TlisteStation depart);
void setArriveeListeStation(TligneBus *l, TlisteStation arrivee);


//Filtres
bool isReseauVide(Treseau *r);
bool isTroncon(Tstation* station);
bool isArret(Tstation* station);
bool isArretOrTroncon(Tstation* station);



#endif // TYPES_H_INCLUDED
