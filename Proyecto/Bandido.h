#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED
#define MAX_MOVIMIENTO_BANDIDO 3
#include "Tablero.h"
#include "Movimiento.h"
typedef struct tJugador tJugador;
typedef struct tBandido
{
    int idBandido;
    tPosicion posicionActual;  //Apunta al nodo de la lista en el que se encuentra el bandido
    int activo;
} tBandido;

void inicializarBandido(tBandido * bandido,unsigned idBandido, tPosicion posicion);
void desactivarBandido(tBandido* bandido);
tBandido* buscarBandidoPorId(tLista* bandidos,unsigned idBandido);
tMovimiento generarMovimientoBandido(const tBandido* bandido, const tJugador* jugador, const tTablero* tablero);
#endif // BANDIDO_H_INCLUDED
