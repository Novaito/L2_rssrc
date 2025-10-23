#include <stdio.h>
#include <stdlib.h>

#include "listeSort.h"
#include "listeDouble.h"


int getNbrCellFiltered(TlisteStation l, bool (*ffilter)(Tstation *station)) {
    int size = 0;

    T_liste current = l;


    bool looped;
    while(!listeVide(current) && !looped){
        if(ffilter(getPtrData(current))){
            size++;
        }
        current = getNextCell(current);

        if(current == l){
            looped = true;
        }
    }

    return size;

}

Tstation **getTstationTab(TlisteStation l, int *size, bool (*ffilter)(Tstation *station)){
    *size = getNbrCellFiltered(l, ffilter);

    Tstation **tab = (Tstation **)malloc(sizeof(Tstation *) * (*size));

    T_liste current = l;

    int i = 0;
    bool looped = false;

    while(!listeVide(current) && !looped){

        if(ffilter(getPtrData(current))){

            tab[i] = getPtrData(current);

            i++;
        }


        current = getNextCell(current);

        if(current == l){
            looped = true;
        }
    }

    return tab;

}

void fusionTab(Tstation **tab, int start, int middle, int end, bool (*fcomp)(Tstation *a, Tstation *b)){
    int size = end - start + 1;

    Tstation **temp = (Tstation **)malloc(sizeof(Tstation *) * size);


    int ptrFirstTab = start;
    int ptrSecondtab = middle;
    int i = 0;



    while(ptrFirstTab < middle && ptrSecondtab <= end){
        if(fcomp(tab[ptrFirstTab], tab[ptrSecondtab])){
            temp[i] = tab[ptrFirstTab];
            i++;
            ptrFirstTab++;
        }else{
            temp[i] = tab[ptrSecondtab];
            i++;
            ptrSecondtab++;
        }
    }

    while(ptrFirstTab < middle){
        temp[i] = tab[ptrFirstTab];
        i++;
        ptrFirstTab++;
    }

    while(ptrSecondtab <= end){
        temp[i] = tab[ptrSecondtab];
        i++;
        ptrSecondtab++;
    }

    for(int j = 0; j < size; j++){
        tab[start + j] = temp[j];
    }

    free(temp);

}

void triFusion(Tstation **tab, int start, int end, bool (*fcomp)(Tstation *a, Tstation *b)){
    if(start != end){
        int middle = (end - start)/ 2;
        triFusion(tab, start, start + middle, fcomp);
        triFusion(tab, start + middle + 1, end, fcomp);
        fusionTab(tab, start, start + middle + 1, end, fcomp);
    }
}

void triFusionListStation(TlisteStation l, bool (*fcomp)(Tstation *a, Tstation *b), bool (*ffilter)(Tstation *station)){
    int size;
    Tstation **tab = getTstationTab(l, &size, ffilter);

    triFusion(tab, 0, size - 1, fcomp);

    for(int i = 0; i < size; i++){
        if(i>0) printf("\n |");
        afficheStation(tab[i]);
    }
}

