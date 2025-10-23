#include <stdio.h>
#include <stdlib.h>
#include "listeDouble.h"
#include "myTab.h"
/*
t_tab *initTab(int size) {
    t_tab *t = (t_tab *)malloc(sizeof(t_tab));
    t->len = size;
    t->tab = (t_person *)malloc(sizeof(t_person) * t->len);
    return t;
}

void printTab(t_tab *t) {
    printf("##### Your TAB #####");
    for (int i=0; i<t->len; i++) {
        if (i%25==0) {
            printf("\n");
        }
        printf("%3d ", t->tab[i]);
    }
    printf("\nLen : %d\n##########", t->len);
}

t_list ListToTab(t_list li, t_tab *t) {
    t_list l = li;
    int i = t->len-1;
    while (!isEmpty(getNextCell(l))) {
        l = l->suiv;
    }
    while (!isEmpty(l)) {
        t_list tmp = l;
        t->tab[i] = getData(l);
        l = l->prec;
        free(tmp);
        i--;
    }
    initList(&li);
    return li;
}

t_list TabToList(t_tab *t) {
    t_list li;
    initList(&li);
    for (int i=t->len-1; i>=0; i--) {
        li = addFirst(li, t->tab[i]);
    }
    return li;
}

void selectSort(t_tab *t) {
    int current, min, j, tmp;
    for (current = 0; current < t->len; current++) {
        min = current;
        for (j = current; j < t->len; j++) {
            if (t->tab[j] < t->tab[min]) {
                min = j;
            }
            tmp = t->tab[current];
            t->tab[current] = t->tab[min];
            t->tab[min] = tmp;
        }
    }
}

t_list sortList(t_list li) {
    t_tab *t = initTab(countCells(li));
    li = ListToTab(li, t);
    selectSort(t);
    li = TabToList(t);
    free(t);
    return li;
}


void make_tp2() {
    srand(time(NULL));

    t_list li;
    initList(&li);
    li = fillRandValueList(li, 1000);
    //printListState(li);

    t_tab *t = initTab(countCells(li));
    li = ListToTab(li, t);
    //printListState(li);
    t_list l = TabToList(t);
    printListState(l);
    free(t);
    time_t now = time(NULL);
    li = sortList(li);
    time_t then = time(NULL);
    printf("List sorted in %.2f s !", difftime(then, now));
    free(li);

}

*/
