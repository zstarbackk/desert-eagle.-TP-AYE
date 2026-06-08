#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <ctype.h>
#include "Jugador.h"
#include "Archivos.h"
#include "Tablero.h"
#include "Partida.h"
#include "Bandido.h"
#include "indiceJugador.h"
#include "Ranking.h"
#include "../Bibliotecas/colaCircular.h"
#define ARCH_JUGADORES "Archivos/jugadores.dat"
#define ARCH_JUGADORES_IDX "Archivos/indiceJugadores.idx"
#define ARCH_CONFIGURACION "Archivos/config.txt"
#define ARCH_CARAVANA "Archivos/caravana.txt"
#define ARCH_PARTIDAS "Archivos/partidas.dat"
#define TOTAL_RANKING 10
#define ARCH_AYUDA "Archivos/ayuda.txt"

int ingresarJugador(tJugador* jugador, tArbol* indiceJugador);

void generarNickname(char* nombre, char* nickname, unsigned tam);
void mostrarJugadoresEncontrados(const void* dato, unsigned inc);
int seleccionarJugador(int cantidad);
void altaNuevoJugador(FILE* archivo, char* nombre, tJugador* jugador, tArbol* indice);

tResultadoPartida inicializarPartida(tJugador* jugador, tTablero* tablero, tConfig* config);

int puedeRetroceder(const tJugador* jugador, unsigned pasos);
tDireccion pedirDireccion(const tJugador* jugador, unsigned dado);

int prepararTurno(tJugador* jugador, tTablero* tablero, tCola* colaMovimientos);
int procesarMovimientos(tCola* cola, tJugador* jugador, tTablero* tablero);

void aplicarEvento(tJugador* jugador, tCursorDC posicion);

void interceptarJugador(tJugador* jugador,const tBandido* bandido, tCursorDC posicionIntercepcion,tTablero* tablero);

tResultadoPartida jugarPartida(tJugador* jugador, tTablero* tablero, tConfig* config);

void finalizarPartida(tJugador* jugador, tResultadoPartida resultado);

int mostrarRanking(int cant);

void mostrarMenu(tJugador* jugador, tTablero* tablero, tConfig* config);

int mostrarRanking(int cant);

void mostrarMenu(tJugador *jugador, tTablero *tablero, tConfig *config);
#endif // JUEGO_H_INCLUDED
