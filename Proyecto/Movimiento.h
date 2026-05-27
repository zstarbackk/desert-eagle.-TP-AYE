#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
#include "Tablero.h"
typedef enum
{
    ADELANTE='F',
    ATRAS='B'
} tDireccion;
typedef enum
{
    ACTOR_JUGADOR,
    ACTOR_BANDIDO
} tTipoActor;        // Asigna un valor diferente a cada opcion

typedef struct
{
    tTipoActor Actor;
    unsigned idActor;
    tPosicion origen;
    tPosicion destino;
} tMovimiento;

typedef struct
{
    tDireccion direccion;
    unsigned cantidad;
}tMovimientoHistorico;

tMovimiento crearMovimiento(tTipoActor tipo ,unsigned id, tPosicion origen,tPosicion destino);

tMovimientoHistorico crearMovimientoHistorico(tDireccion,unsigned cantidad);

#endif // MOVIMIENTO_H_INCLUDED
