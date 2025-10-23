#ifndef RESEAU_H_INCLUDED
#define RESEAU_H_INCLUDED

#include <stdbool.h>
#include "types.h"

//init
void initReseau(Treseau **r);

//comp
bool isReseauVide(Treseau *r);

//getter
TligneBus **getTabOfLigne(Treseau *r);
int getNbLigne(Treseau *r);
int getMaxSizeTabOfLigne(Treseau *r);
int getNextIdLigne(Treseau *r);

//setter
void setTabOfLigne(Treseau *r, TligneBus **tab);
void setNbLigne(Treseau *r, int size);
void setMaxSizeTabOfLigne(Treseau *r, int maxSize);

#endif // RESEAU_H_INCLUDED
