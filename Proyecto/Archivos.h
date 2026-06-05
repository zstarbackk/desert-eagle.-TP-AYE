#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#include <stdio.h>
#include "Jugador.h"
#include "Partida.h"
#define MAX_JUGADORES 100

typedef struct
{
    int idJugador;
    char nombre[TAM_NICKNAME];
    char nickname[TAM_NICKNAME];
} tJugadorArchivo;

int buscarJugadoresPorNombre(FILE* archivo, char* nombre, tLista* resultados);
unsigned obtenerPosicionJugador(FILE *archivo, const char *nickname);
int buscarJugador(FILE *archivo, const char *nickname, tJugador *jugador);
void darDeAltaJugador(FILE *archivo,const char* nombre, const char *nickname, tJugador *jugador);
unsigned obtenerUltimoIdJugador(FILE *archivo);
unsigned obtenerUltimoIdPartida(FILE* archivo);
int guardarPartida(const char* nombreArchivo, const tJugador* jugador, tResultadoPartida resultado);

#endif // ARCHIVOS_H_INCLUDED
