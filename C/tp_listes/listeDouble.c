#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "listeDouble.h"
#include "types.h"

void initList(t_list *li){
    *li=NULL;
}

int isEmpty(t_list li) {
    return (li==NULL);
}

t_list concatList(t_list src, t_list dst) {
    t_list l = src;
    while (!(isEmpty(l->suiv))) {
        l = l->suiv;
    }
    l->suiv = dst;
    dst->prec = l;
    return src;
}

void printList(t_list li) {
    t_list l = li;
    int len = 0;
    if (isEmpty(l)) {
        printf("Empty list.\n");
    }
    while (!(isEmpty(l))) {
        if (len % 25 == 0) {
            printf("\n");
        }
        printPers(*getData(l));
        l = l->suiv;
        len++;
    }
    printf("\n");
}

void printListV2(t_list li) {
    t_list l = li;
    if (isEmpty(l)) {
        printf("Empty list.\n");
    }
    while (!(isEmpty(l))) {
        printPers(*(l->pdata));
        l = getNextCell(l);
    }
    printf("\n");
}

void printChain(t_list li) {
    t_list l = li;
    while (!(isEmpty(l))) {
        if (l->prec != NULL && l->suiv != NULL) {
            printf("| ");
            printPers(*((l->prec)->pdata));
            printf(" <- ");
            printPers(*(l->pdata));
            printf(" -> ");
            printPers(*((l->suiv)->pdata));
            printf(" |");
        } else {
            if (l->suiv == NULL) {
                printf("| ");
                printPers(*(l->pdata));
                printf(" <- ");
                printPers(*((l->prec)->pdata));
                printf(" -> NULL");
            } else {
                if (l->prec == NULL) {
                    printf("| NULL <- ");
                    printPers(*(l->pdata));
                    printf(" -> ");
                    printPers(*((l->suiv)->pdata));
                    printf(" |");
                }
            }
        }
        l = l->suiv;
    }
}

int countBytes(t_list li) {
    t_list l = li;
    int count = 0;
    while (!(isEmpty(l))) {
        count += sizeof(l);
        l = l->suiv;
    }
    return count;
}

int countCells(t_list li) {
    t_list l = li;
    int count = 0;
    while (!(isEmpty(l))) {
        l = l->suiv;
        count++;
    }
    return count;
}

void printListState(t_list li) {
    printf("\n\n##### State of the List #####\n");
    printf("Size : %d | Len : %d |\nStruct >> ", countBytes(li), countCells(li));
    printChain(li);
    printf("List : ");
    printList(li);
    printf("##########\n");
}

t_list addFirst(t_list li, t_person data) {
    t_cellule *cell = (t_cellule *)malloc(sizeof(t_cellule));
    cell->pdata = (t_person *)malloc(sizeof(t_person));
    *(cell->pdata) = data;
    if (li==NULL) {
        cell->suiv = NULL;
        cell->prec = NULL;
    } else {
        cell->suiv = li;
        cell->prec = NULL;
        li->prec = cell;
    }
    return cell;
}

t_list addLast(t_list li, t_person data) {
    if (isEmpty(li)) {
        addFirst(li, data);
    } else {
        t_cellule *cell = (t_cellule *)malloc(sizeof(t_cellule));
        cell->pdata = (t_person *)malloc(sizeof(t_person));
        *(cell->pdata) = data;
        t_list l = li;
        while (!(isEmpty(l->suiv))) {
            l = l->suiv;
        }
        l->suiv = cell;
        cell->suiv = NULL;
        cell->prec = l;
    }
    return li;
}

t_list addNth(t_list li, t_person data, int pos) {
    if (pos < 0) {
        printf("Error : Negative value.");
    } else {
        if (pos == 0) {
            li = addFirst(li, data);
        } else {
            if (pos >= countCells(li)) {
                li = addLast(li, data);
            } else {
                t_cellule *cell = (t_cellule *)malloc(sizeof(t_cellule));
                cell->pdata = (t_person *)malloc(sizeof(t_person));
                *(cell->pdata) = data;
                t_list l = li;
                while (pos > 0) {
                    l = l->suiv;
                    pos--;
                }
                cell->suiv = l;
                cell->prec = l->prec;
                (cell->prec)->suiv = cell;
                (cell->suiv)->prec = cell;
            }
        }
    }
    return li;
}

t_list remFirst(t_list li) {
    if (isEmpty(li)) {
        printf("List already empty.\n");
    } else {
        t_list l = li;
        li = li->suiv;
        free(l);
    }
    return li;
}

t_list remLast(t_list li) {
    if (isEmpty(li)) {
        printf("List already empty.\n");
    } else {
        t_list l = li;
        while (!(isEmpty(l->suiv))) {
            l = l->suiv;
        }
        (l->prec)->suiv = NULL;
        free(l);
    }
    return li;
}

t_list remNth(t_list li, int pos) {
    if (isEmpty(li)) {
        printf("List already empty.\n");
    } else {
        if (pos == 0) {
            li = remFirst(li);
        } else {
            if (pos >= countCells(li)) {
                li = remLast(li);
            } else {
                t_list l = li;
                while (pos > 0) {
                    l = l->suiv;
                    pos--;
                }
                (l->prec)->suiv = l->suiv;
                (l->suiv)->prec = l->prec;
                free(l);
            }
        }
    }
    return li;
}

t_list *getFirstCell(t_list li) {
    return li;
}

t_list *getLastCell(t_list li) {
    t_list l = li;
    while (!(isEmpty(l->suiv))) {
        l = l->suiv;
    }
    return l;
}

t_list *getNextCell(t_list li) {
    return li->suiv;
}

t_list *getPrevCell(t_list li) {
    return li->prec;
}

t_person *getData(t_list li) {
    return li->pdata;
}

void swapData(t_list src, t_list dst) {
    t_person tmp = *(getData(src));
    *(src->pdata) = *(getData(dst));
    *(dst->pdata) = tmp;
}

bool fcompare(t_person p1, t_person p2, bool (*fcomp) (t_person dataA, t_person dataB)) {
    return fcomp(p1, p2);
}

int countOcc(t_list li, t_person personTcomp) {
    t_list l = li;
    int count = 0;
    while (!(isEmpty(getNextCell(l)))) {
        if (fcompare(*getData(getNextCell(l)), personTcomp, comp_masse_AinfB)) {
            count++;
        }
        l = getNextCell(l);
    }
    return count;
}

void makeTp_liste() {
    t_list li;
    initList(&li);
    /*
    li = addFirst(li, 10);
    li = addLast(li, 7);
    li = addLast(li, 5);
    li = addNth(li, 1, 2);
    printf("*** Function ADD Test ***\n");
    printList(li);
    //printChain(li);
    printf("*** Function REM Test ***\n");
    //
    t_list l1;
    initList(&l1);
    l1 = remFirst(l1);
    li = remLast(li);
    //
    li = remNth(li, 2);
    printList(li);
    t_list l1 = getFirstCell(li);
    t_list l2 = getLastCell(li);
    t_list l3 = getNextCell(li);
    t_list l4 = getPrevCell(li->suiv);
    printf("GetFirstCell %d, val : %d\n", l1, printPers(*(l1->pdata)));
    printf("GetLastCell %d, val : %d\n", l2, printPers(*(l2->pdata)));
    printf("GetNextCell %d, val : %d\n", l3, printPers(*(l3->pdata)));
    printf("GetPrevCell %d, val : %d\n", l4, printPers(*(l4->pdata)));

    li = addFirst(li, 4);
    swapData(li, li->suiv);
    printListState(li);

    t_list li2;
    initList(&li2);
    li2 = addFirst(li2, 21);
    li2 = addFirst(li2, 22);
    li2 = addFirst(li2, 23);
    li2 = addFirst(li2, 24);
    printListState(li2);
    li = concatList(li, li2);
    printListState(li);

    printf("Occurences de 5 : %d\n", countOcc(li, 5));

    free(li);
    free(li2);
    */
}



/*

#
#
#
#
#

*/


t_list fillRandValueList(t_list li, int len) {
    while (len > 0) {
        li = addFirst(li, getPersAlea(len));
        len--;
    }
    return li;
}

void setNext(t_list src, t_list dst) {
    src->suiv = dst;
}

void setPrev(t_list src, t_list dst) {
    src->prec = dst;
}

void doubleChainSort(t_list li, bool (*fcomp) (t_person p1, t_person p2)) {
    int tmp;
    t_list min;
    for (t_list current = li; !(isEmpty(getNextCell(current))); current=getNextCell(current)) {
        min = current;
        for (t_list j = getNextCell(current); !(isEmpty(getNextCell(j))); j=getNextCell(j)) {
            if (fcomp(*getData(j), *getData(min))) {
                min = j;
            }
        }
        swapData(current, min);
    }
}


void make_tp3() {
    t_list li;
    initList(&li);
    li = fillRandValueList(li, 1000);
    printListState(li);
    clock_t now = clock();
    //doubleChainSort(li);
    clock_t then = clock();
    printListState(li);
    printf("Tri effectue en %.3f(s)", ((double)then - now)/CLOCKS_PER_SEC);
    free(li);
}

/*
*
*
*
*
*/

t_list makeListNelt(int size) {
    t_list li;
    initList(&li);
    for (int i=0; i<size; i++) {
        addFirst(li, getPersAlea(i+1));
    }
    return li;
}


void make_tp4() {
    t_person anyPerson = getPersAlea(25);
    t_list li;
    initList(&li);
    li = fillRandValueList(li, 10);
    printPers(anyPerson);
    int occ = countOcc(li, anyPerson);
    printf("Occ : %d\n", occ);
    doubleChainSort(li, comp_masse_AinfB);
    printListState(li);
    free(li);
}
