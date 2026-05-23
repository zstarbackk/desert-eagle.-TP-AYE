#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#include <stdio.h>
#include "Jugador.h"

typedef struct
{
    int idJugador;
    char nickname[30];
} tJugadorArchivo;

int obtenerPosicionJugador(FILE *archivo, const char *nickname);
int buscarJugador(FILE *archivo, const char *nickname, tJugador *jugador);
void darDeAltaJugador(FILE *archivo, const char *nickname, tJugador *jugador);
int obtenerUltimoId(FILE *archivo);

#endif // ARCHIVOS_H_INCLUDED
