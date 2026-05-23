#ifndef COLACIRCULAR_H_INCLUDED
#define COLACIRCULAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../Proyecto/Errores.h"
#define MINIMO( X , Y ) ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )

typedef struct tnodo
{
    void* info;
    unsigned tamInfo;
    struct tnodo* sig;
} tNodoCola;

typedef tNodoCola* tCola;

void crearCola(tCola* c);
int colaLlena(const tCola* c, unsigned tamInfo);
int colaVacia(const tCola* c);
int encolar(tCola* c, const void* info, unsigned tamInfo);
int desencolar(tCola* c, void* info, unsigned tamBuffer);
void vaciarCola(tCola* c);
int verPrimero(const tCola* c, void* info, unsigned tamBuffer);
#endif // COLACIRCULAR_H_INCLUDED
