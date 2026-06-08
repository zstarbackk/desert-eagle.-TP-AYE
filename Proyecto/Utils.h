#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Errores.h"

int tirarDado(void);
int abrirArchivo(FILE**,const char*,const char*);
int trozarLinea(char *, char **, char **);
void pausar(void);
#endif // UTILS_H_INCLUDED
