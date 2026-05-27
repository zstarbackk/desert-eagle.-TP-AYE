#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED

#include "Tablero.h"

typedef struct tBandido
{
    int idBandido;
    tPosicion posicionActual;  //Apunta al nodo de la lista en el que se encuentra el bandido
    int activo;
} tBandido;

void inicializarBandido(tBandido * bandido,unsigned idBandido, tPosicion posicion);
void desactivarBandido(tBandido* bandido);
tBandido* buscarBandidoPorId(tLista* bandidos,unsigned idBandido);
tPosicion calcularDestinoBandido(const tBandido *bandido, const tTablero *tablero,tDireccion, unsigned cantidad);
#endif // BANDIDO_H_INCLUDED
