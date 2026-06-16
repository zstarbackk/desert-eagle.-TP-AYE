#ifndef PARTIDA_H_INCLUDED
#define PARTIDA_H_INCLUDED
#include "Jugador.h"

typedef enum
{
    PARTIDA_EN_CURSO,
    PARTIDA_GANADA,
    PARTIDA_PERDIDA,
    PARTIDA_ERROR
} tResultadoPartida;

typedef struct
{
    char nickname[TAM_NICKNAME];
    unsigned idPartida;
    unsigned idJugador;
    unsigned puntaje;
    unsigned cantMovimientos;
    tResultadoPartida resultado;
}tPartida;

void crearPartida(tPartida* partida, unsigned idPartida, const tJugador* jugador, tResultadoPartida resultado);
#endif // PARTIDA_H_INCLUDED
