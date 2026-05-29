#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "Jugador.h"
#include "Archivos.h"
#include "Tablero.h"
#include "../Bibliotecas/colaCircular.h"
#define TAM_NICKNAME 30
#define ARCH_JUGADORES "Archivos/jugadores.dat"
#define ARCH_CONFIGURACION "Archivos/config.txt"

int ingresarJugador(tJugador *jugador);
void mostrarMenu(tJugador *jugador, tConfig *config);
int inicializarPartida(tJugador* jugador,tTablero* tablero, tConfig *config);
int prepararTurno(tJugador* jugador,tTablero* tablero, tCola *colaMovimientos);
#endif // JUEGO_H_INCLUDED
