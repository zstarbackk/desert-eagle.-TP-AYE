#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "Tablero.h"
#include "Movimiento.h"

typedef struct
{
    int idJugador;
    char nickname[30];
    int vidas;
    int puntaje;
    int protegidoPorOasis;
    int pierdeTurno;
    tNodo *posicionActual;
    unsigned cantMovimientos;
} tJugador;

typedef struct
{
    tDireccion dreccion;
    int cantidad;
}tMovimientoHistorico;

#endif // JUGADOR_H_INCLUDED
