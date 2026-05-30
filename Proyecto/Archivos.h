#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#include <stdio.h>
#include "Jugador.h"
#include "Partida.h"
typedef struct
{
    int idJugador;
    char nickname[30];
} tJugadorArchivo;

unsigned obtenerPosicionJugador(FILE *archivo, const char *nickname);
int buscarJugador(FILE *archivo, const char *nickname, tJugador *jugador);
void darDeAltaJugador(FILE *archivo, const char *nickname, tJugador *jugador);
unsigned obtenerUltimoIdJugador(FILE *archivo);
unsigned obtenerUltimoIdPartida(FILE* archivo);
int guardarPartida(const char* nombreArchivo, const tJugador* jugador, tResultadoPartida resultado);

#endif // ARCHIVOS_H_INCLUDED
