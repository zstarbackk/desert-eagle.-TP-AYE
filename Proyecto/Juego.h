#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <ctype.h>
#include "Jugador.h"
#include "Archivos.h"
#include "Tablero.h"
#include "../Bibliotecas/colaCircular.h"
#define TAM_NICKNAME 30
#define ARCH_JUGADORES "Archivos/jugadores.dat"
#define ARCH_CONFIGURACION "Archivos/config.txt"
#define ARCH_CARAVANA "Archivos/caravana.txt"

typedef enum
{
    PARTIDA_EN_CURSO,
    PARTIDA_GANADA,
    PARTIDA_PERDIDA,
    PARTIDA_ERROR
} tResultadoPartida;

int ingresarJugador(tJugador *jugador);
void mostrarMenu(tJugador *jugador, tTablero *tablero, tConfig *config);
tResultadoPartida inicializarPartida(tJugador* jugador,tTablero* tablero, tConfig *config);
int prepararTurno(tJugador* jugador,tTablero* tablero, tCola *colaMovimientos);
int procesarMovimientos(tCola* cola, tJugador* jugador, tTablero* tablero);
tResultadoPartida jugarPartida(tJugador* jugador, tTablero* tablero, tConfig * config);
void finalizarPartida(tJugador* jugador, tResultadoPartida resultado);
#endif // JUEGO_H_INCLUDED
