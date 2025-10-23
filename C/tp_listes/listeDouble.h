#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED
#include "types.h"

typedef struct t_cell {
    struct t_cell *suiv;
    struct t_cell *prec;
    t_person *pdata;
} t_cellule;
typedef t_cellule *t_list;

void initList(t_list *li);
t_list concatList(t_list src, t_list dst);
int countCells(t_list li);
int countBytes(t_list li);
int isEmpty(t_list li);
void printList(t_list li);
void printListV2(t_list li);
void printChain(t_list li);
void printListState(t_list li);
t_list addFirst(t_list li, t_person data);
t_list addLast(t_list li, t_person data);
t_list addNth(t_list li, t_person data, int pos);
t_list remFirst(t_list li);
t_list remLast(t_list li);
t_list remNth(t_list li, int pos);
t_list *getFirstCell(t_list li);
t_list *getLastCell(t_list li);
t_list *getNextCell(t_list li);
t_list *getPrevCell(t_list li);
t_person *getData(t_list li);
void swapData(t_list src, t_list dst);
t_cellule *findCell(t_list li, t_person dataSearch);
int countOcc(t_list li, t_person dataSearch);

void makeTp_liste();

t_list fillRandValueList(t_list li, int len);
void doubleChainSort(t_list li, bool (*fcomp) (t_person p1, t_person p2));
void swapPtr(t_list j, t_list min);
void setNext(t_list src, t_list dst);
void setPrev(t_list src, t_list dst);

void make_tp3();

t_list makeListNelt(int size);
bool fcompare(t_person p1, t_person p2, bool (*fcomp) (t_person dataA, t_person dataB));

void make_tp4();

#endif // LISTEDOUBLE_H_INCLUDED
