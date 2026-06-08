#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "Tablero.h"
#include "Movimiento.h"

#define TAM_NICKNAME 50

typedef struct tJugador
{
    unsigned idJugador;
    char nickname[TAM_NICKNAME];
    int vidas;
    int puntaje;
    int protegidoPorOasis;
    int pierdeTurno;
    tCursorDC posicionActual;
    unsigned cantMovimientos;
    tLista historialMovimientos;
} tJugador;
void accionCambiarTieneJugador(void* dato, void* ctx);
void inicializarEstadoJugador(tJugador* jugador, unsigned vidasInicio, tCursorDC inicio);
int generarMovimientoJugador(tJugador* jugador,const tTablero* tablero, unsigned dado,tMovimiento* mov,tDireccion dir);
void mostrarMovimientoHistorico(const void* info, unsigned tamInfo);
void mostrarMovimientoHistorico(const void* info, unsigned tamInfo);
void mostrarHistorialJugador(tJugador* jugador);

#endif // JUGADOR_H_INCLUDED



