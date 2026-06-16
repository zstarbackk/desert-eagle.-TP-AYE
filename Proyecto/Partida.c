#include "Partida.h"


void crearPartida(tPartida* partida, unsigned idPartida, const tJugador* jugador, tResultadoPartida resultado)
{
    partida->idPartida = idPartida;
    partida->idJugador = jugador->idJugador;
    partida->puntaje = jugador->puntaje;
    partida->cantMovimientos = jugador->cantMovimientos;
    partida->resultado = resultado;
    strcpy(partida->nickname,jugador->nickname);
}
