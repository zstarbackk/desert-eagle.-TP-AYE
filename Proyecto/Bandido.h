#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED

#include "Tablero.h"

typedef struct tBandido
{
    int idBandido;
    tPosicion posicionActual;  //Apunta al nodo de la lista en el que se encuentra el bandido
    int activo;
} tBandido;

#endif // BANDIDO_H_INCLUDED
