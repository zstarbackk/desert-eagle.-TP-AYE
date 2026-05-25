#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

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
    tTipoActor tipoActor;
    unsigned idActor;
    tDireccion direccion;
    unsigned cantidad;
} tMovimiento;

typedef struct
{
    tDireccion direccion;
    unsigned cantidad;
}tMovimientoHistorico;

tMovimiento crearMovimientoJugador(unsigned idJugador, tDireccion direccion,unsigned cantidad);
tMovimiento crearMovimientoBandido(unsigned idBandido, tDireccion direccion, unsigned cantidad);
tMovimientoHistorico crearMovimientoHistorico(tDireccion,unsigned cantidad);

#endif // MOVIMIENTO_H_INCLUDED
