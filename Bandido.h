#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED

#include "Tablero.h"
#include "Estructuras/listaDobleCircular.h"

typedef struct tBandido
{
    int idBandido;
    tNodo *posicionActual;  //Apunta al nodo de la lista en el que se encuentra el bandido
    int activo;
} tBandido;

#endif // BANDIDO_H_INCLUDED
