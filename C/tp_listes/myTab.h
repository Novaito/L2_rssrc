#ifndef MYTAB_H_INCLUDED
#define MYTAB_H_INCLUDED
#include "listeDouble.h"

typedef struct {
    int len;
    t_person *tab;
} t_tab;

t_tab *initTab(int len);
void printTab(t_tab *t);
t_list ListToTab(t_list li, t_tab *t);
t_list TabToList(t_tab *t);

void selectSort(t_tab *t);
t_list sortList(t_list li);
void make_tp2();

#endif // MYTAB_H_INCLUDED
