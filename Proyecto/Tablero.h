#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "../Bibliotecas/listaDobleCircular.h"

typedef tNodoListaDC * tPosicion;
typedef struct tBandido tBandido; //Solo informa que existe el tipo de datos para evitar dependencias circulares entre headers
typedef enum
{
    DESPEJADO,
    INICIO,
    SALIDA,
    PREMIO,
    VIDA_EXTRA,
    OASIS,
    TORMENTA
} tTipoEvento;  //Asigna valores distintos a cada evento estático para no hacer muchos defines

typedef struct
{
    tTipoEvento tipoEvento;
    int tieneJugador;
    int numeroCasillero;
    tBandido *bandido;  //Si hay un bandido en el casillero, permite pasarlo a inactivo directamente
} tCasillero;

#endif // TABLERO_H_INCLUDED
