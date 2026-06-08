#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED

#define MAX_MOVIMIENTO_BANDIDO 4

#include "Tablero.h"
#include "Movimiento.h"

typedef struct tJugador tJugador;

typedef struct tBandido
{
    unsigned idBandido;
    tCursorDC posicionActual;
    int activo;
} tBandido;

void inicializarBandido(tBandido* bandido, unsigned idBandido, tCursorDC posicion);
void accionDesactivarBandido(void* dato, void* ctx);
void accionActualizarPosicionBandido(void* dato, void* ctx);
void accionCambiarIdBandido(void* dato, void* ctx);
int cmpBandidoPorId(const void* clave, const void* dato);
tDireccion decidirDireccionBandido(const tBandido* bandido, const tCursorDC posJugador, const tTablero* tablero);
tMovimiento generarMovimientoBandido(const tBandido* bandido, const tJugador* jugador, const tTablero* tablero);
void ajustarDestinoBandido(tMovimiento* mov);

#endif // BANDIDO_H_INCLUDED

