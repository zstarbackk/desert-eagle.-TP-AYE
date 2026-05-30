#include "Jugador.h"

void inicializarEstadoJugador(tJugador * jugador,unsigned vidasInicio, tPosicion inicio)
{
    tCasillero* cas = (tCasillero*)inicio->info;

    jugador->vidas=vidasInicio;
    jugador->puntaje=0,
    jugador->protegidoPorOasis=0;
    jugador->pierdeTurno=0;
    jugador->cantMovimientos=0;
    crearLista(&jugador->historialMovimientos);
    jugador->posicionActual=inicio;

    cas->tieneJugador = 1;
}

int generarMovimientoJugador( tJugador * jugador, const tTablero *tablero, unsigned dado, tMovimiento *mov, tDireccion dir)
{
    tPosicion actual=jugador->posicionActual;
    unsigned pasosAdelante=0;
    unsigned pasosAtras=0;
    tMovimientoHistorico movHist;
    while(dado--)
    {
        if(actual==tablero->fin)
            dir=ATRAS;
        if(dir ==ADELANTE)
        {
            actual=actual->sig;
            pasosAdelante++;
        }
        else
        {
            actual=actual->ant;
            pasosAtras++;
        }
    }

    if(pasosAdelante)
    {
        movHist=crearMovimientoHistorico(ADELANTE,pasosAdelante);
        if(insertarAlFinal(&jugador->historialMovimientos,&movHist,sizeof(movHist))!=EXITO)
            return ERROR_MEMORIA;
    }
    if(pasosAtras)
    {
        movHist=crearMovimientoHistorico(ATRAS,pasosAtras);
        insertarAlFinal(&jugador->historialMovimientos,&movHist,sizeof(movHist));
    }
    jugador->cantMovimientos++;
    *mov=crearMovimiento(ACTOR_JUGADOR,jugador->idJugador,jugador->posicionActual,actual,dir);
    return EXITO;
}

void mostrarMovimientoHistorico(const void* info, unsigned tamInfo)
{
    tMovimientoHistorico* mov = (tMovimientoHistorico*)info;

    printf("%c%u ", mov->direccion, mov->cantidad);
}

void mostrarHistorialJugador(tJugador* jugador)
{
    printf("Historial de movimientos: ");

    if(listaVacia(&jugador->historialMovimientos))
        printf("sin movimientos");
    else
        mapLista(&jugador->historialMovimientos, mostrarMovimientoHistorico);

    printf("\n");
}

