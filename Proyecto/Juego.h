#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <ctype.h>
#include "Jugador.h"
#include "Archivos.h"
#include "Tablero.h"
#include "Partida.h"
#include "indiceJugador.h"
#include "Ranking.h"
#include "../Bibliotecas/colaCircular.h"
#define ARCH_JUGADORES "Archivos/jugadores.dat"
#define ARCH_JUGADORES_IDX "Archivos/jugadores.idx"
#define ARCH_CONFIGURACION "Archivos/config.txt"
#define ARCH_CARAVANA "Archivos/caravana.txt"
#define ARCH_PARTIDAS "Archivos/partidas.dat"
#define TOTAL_RANKING 10
#define ARCH_AYUDA "Archivos/ayuda.txt"

int ingresarJugador(tJugador *jugador, tArbol *indiceJugador);
tResultadoPartida inicializarPartida(tJugador* jugador,tTablero* tablero, tConfig *config);
int prepararTurno(tJugador* jugador,tTablero* tablero, tCola *colaMovimientos);
int procesarMovimientos(tCola* cola, tJugador* jugador, tTablero* tablero);
tResultadoPartida jugarPartida(tJugador* jugador, tTablero* tablero, tConfig * config);
void finalizarPartida(tJugador* jugador, tResultadoPartida resultado);
int mostrarRanking(int cant);

void mostrarMenu(tJugador *jugador, tTablero *tablero, tConfig *config);
#endif // JUEGO_H_INCLUDED
