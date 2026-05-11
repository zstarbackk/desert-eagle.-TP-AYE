#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "Tablero.h"
//#include "TDAListaDoble.h"

typedef struct
{
    int idJugador;
    char nickname[30];
    int vidas;
    int puntaje;
    int protegidoPorOasis;
    int pierdeTurno;
    //tNodoLista *posicionActual;
} tJugador;

#endif // JUGADOR_H_INCLUDED
