#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

#include "../Bibliotecas/listaDobleCircular.h"

typedef enum
{
    ADELANTE = 'F',
    ATRAS = 'B'
} tDireccion;

typedef enum
{
    ACTOR_JUGADOR,
    ACTOR_BANDIDO
} tTipoActor;

typedef struct
{
    tTipoActor actor;
    unsigned idActor;
    tCursorDC origen;
    tCursorDC destino;
    tDireccion direccion;
} tMovimiento;

typedef struct
{
    tDireccion direccion;
    unsigned cantidad;
} tMovimientoHistorico;

tMovimiento crearMovimiento(tTipoActor tipo,unsigned id, tCursorDC origen, tCursorDC destino, tDireccion direccion);
tMovimientoHistorico crearMovimientoHistorico(tDireccion direccion, unsigned cantidad);

#endif // MOVIMIENTO_H_INCLUDED


