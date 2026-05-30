#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
#include "../Bibliotecas/listaDobleCircular.h"
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
    tTipoActor actor;
    unsigned idActor;
    tPosicion origen;
    tPosicion destino;
    tDireccion direccion;
} tMovimiento;

typedef struct
{
    tDireccion direccion;
    unsigned cantidad;
}tMovimientoHistorico;

tMovimiento crearMovimiento(tTipoActor tipo ,unsigned id, tPosicion origen,tPosicion destino,tDireccion direccion);
tMovimientoHistorico crearMovimientoHistorico(tDireccion,unsigned cantidad);

#endif // MOVIMIENTO_H_INCLUDED
