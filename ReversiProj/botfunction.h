#include "estado.h"

#ifndef PROJ_BOTFUNCTION_H
#define PROJ_BOTFUNCTION_H

int contaPontos (ESTADO *e,int x, int y);
int maxplay (ESTADO *e, int *x, int *y, int nivel, int orig, int alpha, int beta);


#endif //PROJ_BOTFUNCTION_H
