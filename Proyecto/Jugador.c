#include "Jugador.h"

void inicializarEstadoJugador(tJugador * jugador,unsigned vidasInicio, tPosicion inicio)
{
    jugador->vidas=vidasInicio;
    jugador->puntaje=0,
    jugador->protegidoPorOasis=0;
    jugador->pierdeTurno=0;
    jugador->cantMovimientos=0;
    crearLista(&jugador->historialMovimientos);
    jugador->posicionActual=inicio;
}
