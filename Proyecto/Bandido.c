#include "Bandido.h"
#include "Jugador.h"

void inicializarBandido(tBandido * bandido,unsigned idBandido, tPosicion posicion)
{
    bandido->idBandido=idBandido;
    bandido->activo=1;
    bandido->posicionActual= posicion;
}

void desactivarBandido(tBandido* bandido)
{
    bandido->activo=0;
}

tBandido* buscarBandidoPorId(tLista* bandidos, unsigned idBandido)
{
    tBandido* bandido;

    while(*bandidos)
    {
        bandido = (tBandido*)(*bandidos)->info;

        if(bandido->idBandido == idBandido)
            return bandido;

        bandidos = &(*bandidos)->sig;
    }

    return NULL;
}
int distanciaAdelante(const tPosicion origen, const tPosicion destino)
{
    int distancia=0;
    tPosicion actual=origen;
    while(actual!=destino)
    {
        actual=actual->sig;
        distancia++;
    }
    return distancia;
}

tDireccion decidirDireccionBandido(const tBandido* bandido,const tPosicion posJugador,const tTablero *tablero)
{
    int adelante=distanciaAdelante(bandido->posicionActual,posJugador);
    int atras=(tablero->cantidadCasilleros-adelante)% tablero->cantidadCasilleros;
    if(adelante<= atras)
        return ADELANTE;
    return ATRAS;
}

tMovimiento generarMovimientoBandido(const tBandido* bandido, const tJugador* jugador, const tTablero* tablero)
{
    unsigned cantidadInicial;
    unsigned cantidad;
    unsigned i;
    tDireccion dir;
    tPosicion destino;
    tCasillero* cas;

    dir = decidirDireccionBandido(bandido, jugador->posicionActual, tablero);

    cantidadInicial = rand() % MAX_MOVIMIENTO_BANDIDO + 1;

    for(i = 0; i < MAX_MOVIMIENTO_BANDIDO; i++)
    {
        cantidad = ((cantidadInicial - 1 + i) % MAX_MOVIMIENTO_BANDIDO) + 1;

        destino = bandido->posicionActual;

        if(dir == ADELANTE)
        {
            unsigned pasos = cantidad;

            while(pasos--)
                destino = destino->sig;
        }
        else
        {
            unsigned pasos = cantidad;

            while(pasos--)
                destino = destino->ant;
        }

        cas = (tCasillero*)destino->info;

        if(cas->tipoEvento != INICIO &&
           cas->tipoEvento != SALIDA &&
           cas->idBandido == 0)
        {
            return crearMovimiento(ACTOR_BANDIDO,
                                   bandido->idBandido,
                                   bandido->posicionActual,
                                   destino);
        }
    }

    return crearMovimiento(ACTOR_BANDIDO,
                           bandido->idBandido,
                           bandido->posicionActual,
                           bandido->posicionActual);
}

