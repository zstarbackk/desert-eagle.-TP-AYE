#include "Bandido.h"


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

tBandido* buscarBandidoPorId(tLista* bandidos,unsigned idBandido)
{
    tPosicion actual;
    tBandido* bandido;

    actual=*bandidos;

    while(actual)
    {
        bandido=(tBandido*)actual->info;
        if(bandido->idBandido==idBandido)
            return bandido;
        actual= actual->sig;
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
int distanciaAtras(const tPosicion origen,const tPosicion destino)
{
    int distancia=0;
    tPosicion actual=origen;
    while(actual!=destino)
    {
        actual=actual->ant;
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

