#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include "../Bibliotecas/TdaListaDinamica.h"
#include "Partida.h"
#include "Archivos.h"
#include "Juego.h"
#include <stdio.h>
#include <string.h>
typedef struct{
    unsigned idJugador;
    char nickname[TAM_NICKNAME];
    unsigned total;
}tRanking;

int cargarRanking(FILE *archivo, tLista *lista);
int listarTopJugadores(const tLista * lista, int cant);
void sumarPuntos(void *registro, const void* infoPartida);
int cmpIndiceJugadorPorId(const void* a, const void* b);
int cmpRankingPorPuntos(const void* a, const void* b);

#endif // RANKING_H_INCLUDED
