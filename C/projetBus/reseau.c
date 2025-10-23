#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "reseau.h"
#include "ligneBus.h"
#include "listeDouble.h"


bool isReseauVide(Treseau *r) {
    return (r->size == 0);
}
