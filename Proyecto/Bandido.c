#include "Bandido.h"
#include "Jugador.h"
#include <stdlib.h>

void inicializarBandido(tBandido* bandido, unsigned idBandido, tCursorDC posicion)
{
    bandido->idBandido = idBandido;
    bandido->activo = 1;
    bandido->posicionActual = posicion;
}

 void accionDesactivarBandido(void* dato, void* ctx)
{
    tBandido* bandido = (tBandido*)dato;

    (void)ctx;

    bandido->activo = 0;
}
 void accionActualizarPosicionBandido(void* dato, void* ctx)
{
    tBandido* bandido = (tBandido*)dato;
    tCursorDC* nuevaPosicion = (tCursorDC*)ctx;

    bandido->posicionActual = *nuevaPosicion;
}
void accionCambiarIdBandido(void* dato, void* ctx)
{
    tCasillero* cas = (tCasillero*)dato;
    unsigned* idBandido = (unsigned*)ctx;

    cas->idBandido = *idBandido;
}

int cmpBandidoPorId(const void* clave, const void* dato)
{
    const unsigned* idBuscado = (const unsigned*)clave;
    const tBandido* bandido = (const tBandido*)dato;

    if(*idBuscado > bandido->idBandido)
        return 1;

    if(*idBuscado < bandido->idBandido)
        return -1;

    return 0;
}


int distanciaAdelante(tCursorDC origen, tCursorDC destino, unsigned cantidadCasilleros)
{
    unsigned distancia = 0;
    tCursorDC actual = origen;

    while(!mismoCursorDC(actual, destino) && distancia < cantidadCasilleros)
    {
        actual = siguienteDC(actual);
        distancia++;
    }

    return distancia;
}

tDireccion decidirDireccionBandido(const tBandido* bandido, const tCursorDC posJugador, const tTablero* tablero)
{
    int adelante, atras;

    adelante = distanciaAdelante(bandido->posicionActual,posJugador,tablero->cantidadCasilleros);

    atras = (tablero->cantidadCasilleros - adelante) % tablero->cantidadCasilleros;

    if(adelante <= atras)
        return ADELANTE;

    return ATRAS;
}

tMovimiento generarMovimientoBandido(const tBandido* bandido, const tJugador* jugador, const tTablero* tablero)
{
    unsigned cantidadInicial;
    unsigned cantidad;
    unsigned i;
    tDireccion dir;
    tCursorDC destino;
    tCasillero cas;
    int ret;

    dir = decidirDireccionBandido(bandido, jugador->posicionActual, tablero);

    cantidadInicial = rand() % MAX_MOVIMIENTO_BANDIDO + 1;

    for(i = 0; i < MAX_MOVIMIENTO_BANDIDO; i++)
    {
        /*
            Se prueba primero una cantidad aleatoria.
            Si esa cantidad hace que el bandido termine en INICIO o SALIDA,
            se prueban las demás cantidades posibles manteniendo la misma dirección.
        */
        cantidad = ((cantidadInicial - 1 + i) % MAX_MOVIMIENTO_BANDIDO) + 1;

        if(dir == ADELANTE)
            destino = avanzarNDC(bandido->posicionActual, cantidad);
        else
            destino = retrocederNDC(bandido->posicionActual, cantidad);

        ret = verActualDC(destino, &cas, sizeof(tCasillero));

        if(ret != EXITO)
        {
            // se queda en el lugar
            return crearMovimiento(ACTOR_BANDIDO, bandido->idBandido, bandido->posicionActual, bandido->posicionActual, dir);
        }

        /*
            El bandido puede pasar por INICIO o SALIDA durante el recorrido,
            pero no puede terminar su movimiento en esos casilleros.
        */
        if(cas.tipoEvento != INICIO && cas.tipoEvento != SALIDA)
        {
            return crearMovimiento(ACTOR_BANDIDO,bandido->idBandido, bandido->posicionActual,destino,dir);
        }
    }

       // Si ninguna cantidad genera un destino válido,el bandido queda quieto.

    return crearMovimiento(ACTOR_BANDIDO, bandido->idBandido, bandido->posicionActual, bandido->posicionActual, dir);
}

void ajustarDestinoBandido(tMovimiento* mov)
{
    tCasillero cas;
    tCursorDC destino;
    unsigned intentos = 0;

    if(verActualDC(mov->destino, &cas, sizeof(tCasillero)) != EXITO)
    {
        mov->destino = mov->origen;
        return;
    }

    //Si el destino original no tiene bandido,no hace falta ajustar.

    if(cas.idBandido == 0)
        return;

    destino = mov->destino;

    //Si el destino ya fue ocupado por otro bandido al procesar la cola,busca una nueva casilla en la misma dirección.

    while(intentos < MAX_MOVIMIENTO_BANDIDO)
    {
        if(mov->direccion == ADELANTE)
            destino = siguienteDC(destino);
        else
            destino = anteriorDC(destino);

        if(verActualDC(destino, &cas, sizeof(tCasillero)) != EXITO)
        {
            mov->destino = mov->origen; //queda igual
            return;
        }

        if(cas.idBandido == 0 && cas.tipoEvento != INICIO && cas.tipoEvento != SALIDA)
        {
            mov->destino = destino;
            return;
        }

        intentos++;
    }

    //Si no se encontró una alternativa válida,el bandido queda en su origen.

    mov->destino = mov->origen;
}

