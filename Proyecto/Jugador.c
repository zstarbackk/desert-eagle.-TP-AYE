#include "Jugador.h"

 void accionCambiarTieneJugador(void* dato, void* ctx)
{
    tCasillero* cas = (tCasillero*)dato;
    int* valor = (int*)ctx;

    cas->tieneJugador = *valor;
}

void inicializarEstadoJugador(tJugador* jugador, unsigned vidasInicio, tCursorDC inicio)
{
    int tieneJugador = 1;
    jugador->vidas = vidasInicio;
    jugador->puntaje = 0;
    jugador->protegidoPorOasis = 0;
    jugador->pierdeTurno = 0;
    jugador->cantMovimientos = 0;
    crearLista(&jugador->historialMovimientos);
    jugador->posicionActual = inicio;

    modificarActualDC(inicio, accionCambiarTieneJugador, &tieneJugador);
}

int generarMovimientoJugador(tJugador* jugador, const tTablero* tablero,unsigned dado,tMovimiento* mov, tDireccion dir)
{
    tCursorDC actual = jugador->posicionActual;
    unsigned pasosAdelante = 0;
    unsigned pasosAtras = 0;
    tMovimientoHistorico movHist;
    int ret;

    while(dado--)
    {
        if(mismoCursorDC(actual, tablero->fin))
            dir = ATRAS;

        if(dir == ADELANTE)
        {
            actual = siguienteDC(actual);
            pasosAdelante++;
        }
        else
        {
            actual = anteriorDC(actual);
            pasosAtras++;
        }
    }

    if(pasosAdelante)
    {
        movHist = crearMovimientoHistorico(ADELANTE, pasosAdelante);

        ret = insertarAlFinal(&jugador->historialMovimientos, &movHist, sizeof(movHist));
        if(ret != EXITO)
            return ERROR_MEMORIA;
    }

    if(pasosAtras)
    {
        movHist = crearMovimientoHistorico(ATRAS, pasosAtras);

        ret = insertarAlFinal(&jugador->historialMovimientos, &movHist, sizeof(movHist));
        if(ret != EXITO)
            return ERROR_MEMORIA;
    }

    jugador->cantMovimientos++;

    *mov = crearMovimiento(ACTOR_JUGADOR,jugador->idJugador,jugador->posicionActual,actual,dir);

    return EXITO;
}

 void mostrarMovimientoHistorico(const void* info, unsigned tamInfo)
{
    const tMovimientoHistorico* mov = (const tMovimientoHistorico*)info;

    printf("|%c%u|", mov->direccion, mov->cantidad);

}

void mostrarHistorialJugador(tJugador* jugador)
{
    printf("Historial de movimientos: ");

    if(listaVacia(&jugador->historialMovimientos))
        printf("sin movimientos");
    else
        mostrarLista(&jugador->historialMovimientos,mostrarMovimientoHistorico);
    printf("\n");
}

