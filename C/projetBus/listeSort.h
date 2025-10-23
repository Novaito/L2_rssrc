#ifndef LISTESORT_H_INCLUDED
#define LISTESORT_H_INCLUDED

#include "listeDouble.h"
#include "types.h"

//Renvoie le nombre de cellules correspondant au filtre en paramètre
int getNbrCellFiltered(TlisteStation l, bool (*ffilter)(Tstation *station));

//Stocke les stations dans un tableau afin de faciliter le tri par la suite
Tstation **getTstationTab(TlisteStation l, int *size, bool (*ffilter)(Tstation *station));

//Algorithme de tri fusion avec une fonction de comparaison en paramètre

void fusionTab(Tstation **tab, int start, int middle, int end, bool (*fcomp)(Tstation *a, Tstation *b));

void triFusion(Tstation **tab, int start, int end, bool (*fcomp)(Tstation *a, Tstation *b));

void triFusionListStation(TlisteStation l, bool (*fcomp)(Tstation *a, Tstation *b), bool (*ffilter)(Tstation *station));

#endif // LISTESORT_H_INCLUDED
