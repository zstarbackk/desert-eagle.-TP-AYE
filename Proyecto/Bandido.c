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
    tNodoL* actual;
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

int distanciaAdelante(tPosicion origen, tPosicion destino)
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
int distanciaAtras(tPosicion origen, tPosicion destino)
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

tDireccion decidirDireccionBandido(tBandido* bandido, tPosicion posJugador)
{
    int adelante=distanciaAdelante(bandido->posicionActual,posJugador);
    int atras=distanciaAtras(bandido->posicionActual,posJugador);
    if(adelante<=)
        return ADELANTE;
    return ATRAS;
}
