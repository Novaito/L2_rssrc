#include <stdio.h>
#include <stdlib.h>

#include "listeDouble.h"


//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(T_liste *l){
*l=NULL;
}


bool listeVide( T_liste l){
    return (l==NULL);
}

void afficheListe( T_liste l){
    T_liste courant = l;
    while (courant!=NULL){
        afficheStation(courant->pdata);  //fourni par types.h
        courant=courant->suiv;
    }
}

T_liste ajoutEnTete(T_liste l, Tstation* mydata){
    T_liste nouv = (T_liste)malloc(sizeof(struct T_cell));

    //CHANGEMENT par rapport à la partie2 d'updago
    //nouv->pdata = (int*)malloc(sizeof(int)); ATTENTION PLUS DE RECOPIE de mydata, donc plus d'allocation mémoire sur ce champ

    //SIMPLE BRANCHEMENT EN MEMOIRE ENTRE POINTEURS (SUR LA STATION EXISTANTE)
    nouv->pdata=mydata;

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;  //sécurise la présence de NULL sur le champ suiv, au cas où le ptr l n'aurait pas été  initialisé correctement via initListe
        nouv->prec = NULL;
    }
    else  // la lste n'etait pas vide, on doit donc faire les branchements
    {
        nouv->suiv = l;
        if(!listeVide(l->prec)){
            nouv->prec = l->prec;
            nouv->prec->suiv = nouv;
        }else{
            nouv->prec = NULL;
        }

        l->prec = nouv;
    }
    return nouv;
}

T_liste ajoutEnFin(T_liste l, Tstation* mydata){
    T_liste nouv, courant=l;  //remarque: pas de malloc si on appelle ajoutEnTete

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        return ajoutEnTete(l, mydata);
    }
    else  // la liste n'etant pas vide,déplacment sur la derniere cellule, malloc et branchements
    {
        while (courant->suiv != NULL){
            courant=courant->suiv;
        }
        nouv = (T_liste)malloc(sizeof(struct T_cell));
        nouv->pdata=mydata;

        nouv->suiv = NULL;
        nouv->prec = courant;
        courant->suiv = nouv;
    }
    return l;  //la tête d'origine, qui n'a pas changé
}

Tstation* getPtrData(T_liste l){
    if (l==NULL)
    {
        printf("\nERREUR ptr pdata non alloué");
        return NULL;
    }
    else
    {
        return l->pdata;
    }
}

T_liste getNextCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->suiv;
    }
}

T_liste getPrevCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->prec;
    }
}



//A vous la suite si besoin

T_liste getptrFirstCell(T_liste l) {
    return l;
}

T_liste getptrLastCell(T_liste l) {

    if(listeVide(l)){
        return NULL;
    }

    T_liste li = l;
    while (!(listeVide(getNextCell(li)))) {
        li = getNextCell(li);
    }
    return li;
}

int getNbreCell(T_liste l){

    if(listeVide(l)){
        return 0;
    }

    int count = 0;
    T_liste current = l;
    bool looped = false;
    while(!listeVide(current) && !looped){
        current = current->suiv;
        count++;
        if(current == l){
            looped = true;
        }
    }

    return count;
}

void setPtrData(T_liste l, Tstation *mydata){
    l->pdata = mydata;
}

void unAllocCel(T_liste l){
    //free(l->pdata);
    free(l);
    //TODO a compléter
}

T_liste suppEnTete(T_liste l){
    if(listeVide(l)|| listeVide(l->suiv)){
        return NULL;
    }
    T_liste toReturn = l->suiv;
    if(listeVide(l->prec)){
        l->suiv->prec = NULL;
    }else{
        l->suiv->prec = l->prec;
        l->prec->suiv = l->suiv;
    }
    unAllocCel(l);
    return toReturn;
}

T_liste suppEnFin(T_liste l){
    if(listeVide(l) || listeVide(l->suiv)){
        return NULL;
    }

    T_liste next = l;

    while (!listeVide(next->suiv->suiv)){
        next = next->suiv;
    }
    unAllocCel(next->suiv);
    next->suiv = NULL;

    return l;
}

T_liste suppEnN(T_liste l, int pos){

    if(listeVide(l)){
        return l;
    }

    if(pos == 0){
        l = suppEnTete(l);
        return l;

    }

    int i = 0;
    T_liste next = l;


    while (!listeVide(next->suiv) && i < pos){
        next = next->suiv;
        i++;
    }

    if(listeVide(next->suiv)){
        return suppEnFin(l);
    }

    next->prec->suiv = next->suiv;
    next->suiv->prec = next->prec;

    unAllocCel(next);

    return l;

}


void setNext(T_liste l, T_liste next){
    l->suiv = next;
}


void setPrev(T_liste l, T_liste prev){
    l->prec = prev;
}

