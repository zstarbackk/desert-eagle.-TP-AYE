#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Errores.h"

int TirarDado(void);
int AbrirArchivo(FILE**,const char*,const char*);
int trozarLinea(char *, char **, char **);

#endif // UTILS_H_INCLUDED
