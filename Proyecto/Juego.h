#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "Jugador.h"
#include "Archivos.h"
#include "Config.h"
#define TAM_NICKNAME 30
#define ARCH_JUGADORES "Archivos/jugadores.dat"
#define ARCH_CONFIGURACION "Archivos/config.txt"

int ingresarJugador(tJugador *jugador);
void mostrarMenu(tJugador *jugador, tConfig *config);

#endif // JUEGO_H_INCLUDED
