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
    tPosicion posicionActual;
    unsigned cantMovimientos;
    tLista historialMovimientos;
} tJugador;

void inicializarEstadoJugador(tJugador * jugador,unsigned vidasInicio, tPosicion inicio);
int generarMovimientoJugador(tJugador * jugador, const tTablero *tablero, unsigned dado, tMovimiento *mov, tDireccion);
void mostrarMovimientoHistorico(const void* info, unsigned tamInfo);
void mostrarHistorialJugador(tJugador* jugador);


#endif // JUGADOR_H_INCLUDED
